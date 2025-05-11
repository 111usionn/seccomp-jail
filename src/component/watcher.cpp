#include "watcher.h"

bool trashcan = 0;
bool Watcher::seccomp_force_enable_calls(int i)
{
    if(i != SCMP_SYS(read) && i != SCMP_SYS(write) && i != SCMP_SYS(exit) && i != SCMP_SYS(sigreturn) && i != SCMP_SYS(seccomp) && i != SCMP_SYS(ptrace) && i != SCMP_SYS(close) /*&& i!= SCMP_SYS(mmap) && i!= SCMP_SYS(fork) && i!= SCMP_SYS(clone) && i!= SCMP_SYS(vfork)*/)
    {
        return 0;
    }
    return 1;
}

Watcher::Watcher(bool mode, QObject *parent)
    : QObject{parent}
{
    endFlag = 1;
    blockSig = 1;
    blockSig_exit = 1;
    addroffset = 0;
    deref_offset = 1;
    settings.enableLDPRELOAD = 1;
    isSub = mode;
    procs_stopped = 0;
    func_selecter = 1;
}

int Watcher::gethookoffset()
{
    int tempoffset = addroffset;
    addroffset += 3;
    addroffset %= 255;
    return tempoffset;
}

void Watcher::StopAllProcess(int curr_pid)
{
    procs_stopped = true;
    int pid;
    siginfo_t info;
    memset(&info, 0, sizeof(info));
    for(auto it = survived_procs.begin(); it != survived_procs.end(); it++){
        pid = *it;
        if(pid == curr_pid)continue;
        waitid(P_PID, pid, &info, WSTOPPED | WNOHANG | WNOWAIT);
        if(info.si_pid == 0)//need to send sigstop
        {
            syscall(SYS_tkill, pid, SIGSTOP);
            waitid(P_PID, pid, &info, WSTOPPED | WNOHANG | WNOWAIT);
            if(WSTOPSIG(info.si_status) == SIGSTOP)//normal situation
            {
                waitpid(pid, 0, 0);
            }
            else
            {
                need_suppress_sigstop.insert(pid);
            }
        }
    }
}

void Watcher::ContinueAllProcess()
{
    if(STOP_MODE == NON_STOP)return;
    if(func_selecter)
    {
        ContinueAllProcessToExit();
    }
    else
    {

        RestartAllProcess();
    }
}

void Watcher::ContinueAllProcessToExit()
{
    //synchronize all process to the same status that a single PTRACE_CONT can restart them.
    func_selecter ^= 1;
    for(auto it = Pending_Procs.begin(); it != Pending_Procs.end(); it++)
    {
        int notifypid = it.key();
        int status = it.value();
        emit processStopped(notifypid);
        __ptrace_syscall_info si;
        seccomp_data data;
        memset(&data, 0, sizeof(data));
        memset(&si, 0, sizeof(si));
        ptrace(PTRACE_GET_SYSCALL_INFO, notifypid, sizeof(si), &si);
        if(status >> 8 != (SIGTRAP | (PTRACE_EVENT_EXEC<<8)))
        {
            data.nr = si.seccomp.nr;
            data.args[0] = si.seccomp.args[0];
            data.args[1] = si.seccomp.args[1];
            data.args[2] = si.seccomp.args[2];
            data.args[3] = si.seccomp.args[3];
            data.args[4] = si.seccomp.args[4];
            data.args[5] = si.seccomp.args[5];
        }
        else
        {
            data.nr = SCMP_SYS(execve);
        }
        QString darg[6];
        for(int i = 0; i <= 5; i++)
        {
            for(int j = 0; j < deref_offset; j++)
            {
                long result = ptrace(PTRACE_PEEKDATA, notifypid, data.args[i] + j * 8, NULL);
                darg[i] += QString::number(result, 16).toUpper();
            }
        }
        QList<QString> dargs;
        for(int i = 0; i <= 5; i++)
        {
            dargs.append(darg[i]);
        }
        emit catchSyscall(notifypid, status, data, dargs);
        while(blockSig)
        {
            trashcan ^= 1;
        }
        blockSig = SYSMSG_KEEP_BLOCKING;
        QString action = generateAction(nextMove, extraOption);
        waiting_for_inject(notifypid);
        QString log;
        if(nextMove != 2)log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(notifypid) + " nr: " + QString::number(data.nr) + "(" +
                  findSyscallName(data.nr) + ")" +
                  " arg1: " + QString::number(data.args[0]) + " arg2: " + QString::number(data.args[1]) + " arg3: " + QString::number(data.args[2]) + " arg4: " + QString::number(data.args[3]) +
                  " arg5: " + QString::number(data.args[4]) + " arg6: " + QString::number(data.args[5]) + " action: " + action;
        int isexec = 0;
        if(data.nr == SCMP_SYS(execve))isexec = 1;
        bool catch_reval = 0;
        if(!nextMove)
        {
            catch_reval = 1;
            ptrace(PTRACE_POKEUSER, notifypid, 8 * ORIG_RAX, -1);
            ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
            waitpid(notifypid, 0, 0);
        }
        else if(nextMove != 2)
        {
            catch_reval = 1;
            int isfork = 0;
            if(data.nr != SCMP_SYS(fork) && data.nr != SCMP_SYS(vfork) && data.nr != SCMP_SYS(clone))
                ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
            else
            {
                isfork = 1;
                catch_reval = 0;
                ptrace(PTRACE_CONT, notifypid, 0, 0);
            }
            waitpid(notifypid, &status, 0);
            if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_FORK<<8)))
            {
                pid_t new_proc_pid = 0;
                int new_status;
                ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                waitpid(new_proc_pid, &new_status, 0);
                qDebug() << "parent:" << notifypid << "child:" << new_proc_pid;
                //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                //ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                survived_procs.insert(new_proc_pid);
                //ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
            }
            else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)))
            {
                pid_t new_proc_pid = 0;
                int new_status;
                ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                waitpid(new_proc_pid, &new_status, 0);
                //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                //ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                survived_procs.insert(new_proc_pid);
                //ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
            }
            else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)))
            {
                pid_t new_proc_pid = 0;
                int new_status;
                ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                waitpid(new_proc_pid, &new_status, 0);
                //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                //ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                survived_procs.insert(new_proc_pid);
                //ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
            }
            if(isfork || isexec)
            {
                emit createProcTree(child_pid);
            }
            if(isexec)catch_reval = 0;
        }
        if(catch_reval)
        {
            long syscallreval = ptrace(PTRACE_PEEKUSER, notifypid, 8 * RAX, 0);
            emit handleSyscallExit(notifypid, data.nr, syscallreval);
            while(blockSig_exit)
            {
                trashcan ^= 1;
                if(blockSig_exit == SYSMSG_DEAL_LATER)
                {
                    break;
                }
            }
            if(blockSig_exit == SYSMSG_DEAL_LATER)
            {
                need_user_confirmation.insert(notifypid);
                QString reval = " returnval: not decided";
                log += reval;
            }
            else
            {
                QString reval = " returnval: ";
                if(nextMove_exit == SYSMSG_KEEP_ORIG_REVAL)
                {
                    reval += QString::number(syscallreval);
                }
                else if(nextMove_exit == SYSMSG_CHANGE_REVAL)
                {
                    ptrace(PTRACE_POKEUSER, notifypid, 8 * RAX, newReval);
                    reval += QString::number(newReval);
                }
                log += reval;
            }
            blockSig_exit = SYSMSG_KEEP_BLOCKING;
        }
        else
        {
            if(isexec)
            {
                emit createProcTree(child_pid);
            }
        }
        if(nextMove != 2)emit writeLog(log);
        emit processRestarted(notifypid);
    }
    if(need_user_confirmation.empty())
    {
        RestartAllProcess();
    }
}

void Watcher::RestartAllProcess()
{
    func_selecter ^= 1;
    for(auto it = survived_procs.begin(); it != survived_procs.end(); it++)
    {
        int pid = *it;
        if(need_ptrace_listen.contains(pid))//group-stop
        {
            ptrace(PTRACE_LISTEN, pid, 0, 0);
            need_ptrace_listen.remove(pid);
        }
        else if(need_inject_signal.contains(pid))//signal-delivery-stop
        {
            ptrace(PTRACE_CONT, pid, 0, need_inject_signal[pid]);
            need_inject_signal.remove(pid);
        }
        else//normal
        {
            ptrace(PTRACE_CONT, pid, 0, 0);
        }
    }
    procs_stopped = false;//at last
}

int Watcher::proactiveInterrupt(int pid)
{
    return ptrace(PTRACE_INTERRUPT, pid, 0, 0);
}

void Watcher::proactiveRestart(int pid)
{
    if(!ptrace(PTRACE_CONT, pid, 0, 0))
    {
        emit processRestarted(pid);
    }
}

void Watcher::dealNow(bool mode, int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption)
{
    syscall_info temp;
    temp.mode = mode?syscall_info::ENTRY:syscall_info::EXIT;
    temp.pid = pid;
    temp.status = status;
    temp.nr = nr;
    temp.args[0] = arg1.toLong();
    temp.args[1] = arg2.toLong();
    temp.args[2] = arg3.toLong();
    temp.args[3] = arg4.toLong();
    temp.args[4] = arg5.toLong();
    temp.args[5] = arg6.toLong();
    temp.mask = mask;
    temp.nextMove = nextMove;
    temp.blockSig = blockSig;
    temp.extraOption = extraOption;
    notified_events.enqueue(temp);
}

void Watcher::waiting_for_inject(int pid)
{
    if(has_trap.contains(pid))
    {
        if(has_trap.value(pid) == 1)
        {
            long rip = ptrace(PTRACE_PEEKUSER, pid, 8 * RIP, 0);
            long orig_code = ptrace(PTRACE_PEEKDATA, pid, rip, 0);
            orig_codes.insert(pid, orig_code);
            long code = orig_code;
            long cc = 0xcc;
            memcpy(&code, &cc, 1);
            ptrace(PTRACE_POKEDATA, pid, rip, code);
            has_trap.insert(pid, 0);
        }
    }
}

void Watcher::injector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc)
{
    if(proactiveInterrupt(pid))return;
    emit processStopped(pid);
    int status = 0;
    QTime s_time = QTime::currentTime();
    bool undone = 1;
    while(undone)
    {
        qDebug() << "123";
        waitpid(pid, &status, WNOHANG);
        if(status)break;
        sleep(1);
        if(s_time.secsTo(QTime::currentTime()) > 3)undone = 0;
    }
    if(status >> 8 != (SIGTRAP | (PTRACE_EVENT_STOP << 8)))
    {
        qDebug() << "asdf";
        syscall_info tempinfo = {syscall_info::ENTRY, 0, argc, nr, arg1, arg2, arg3, arg4, arg5, arg6};
        //                       /*      useless      *//*                 useful                   */
        inject_events.insert(pid, tempinfo);
        has_trap.insert(pid, 1);
        //push event
        return;
    }
    char* buf;
    char* end;
    char mapfile[0x100];
    sprintf(mapfile, "/proc/%d/maps", pid);
    FILE* fd = fopen(mapfile, "r");
    buf = (char*) malloc(0x100);
    do{
        fgets(buf, 0x100, fd);
    } while(!strstr(buf, settings.enableLDPRELOAD?"libhookhere.":"libc.") || !strstr(buf, "xp "));
    end = strchr(buf, '-');
    libcAddr = strtol(buf, &end, 16);
    injectedPid = pid;
    fclose(fd);
    user_regs_struct regs;
    ptrace(PTRACE_GETREGS, pid, 0, &regs_bak);
    memcpy(&regs, &regs_bak, sizeof(struct user_regs_struct));
    long code;
    code_bak = ptrace(PTRACE_PEEKTEXT, pid, libcAddr, 0);
    code = code_bak;
    long hook = 0xcc050f;
    memcpy(&code, &hook, 3);
    ptrace(PTRACE_POKETEXT, pid, libcAddr, code);
    regs.rax = nr;
    if(argc > 0)regs.rdi = arg1;
    if(argc > 1)regs.rsi = arg2;
    if(argc > 2)regs.rdx = arg3;
    if(argc > 3)regs.rcx = arg4;
    if(argc > 4)regs.r8 = arg5;
    if(argc > 5)regs.r9 = arg6;
    regs.rip = libcAddr;
    ptrace(PTRACE_SETREGS, pid, 0, &regs);
    proactiveRestart(pid);
}

void Watcher::createPuppet(const QString path, QStringList args, QJsonObject r, bool all_stop_mode_enabled)
{
    int pp[2];
    pipe(pp);
    pid_t user_movement_observer_pid = fork();
    if(user_movement_observer_pid == 0)
    {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        qDebug() << "observer on";
        while(1)pause();
    }
    else
    {
        child_pid = fork();
        if(child_pid == 0)//child
        {
            //setenv("LD_PRELOAD","./libhookhere.so", 1);
            int buffer;
            close(pp[1]);
            //sleep(1);
            /*QByteArray qpath = path.toLatin1();
            char *cpath = NULL;
            cpath = strdup(qpath.data());
            char *cargs[150];
            for(int i = 0; i < args.size(); i++)
            {
                QString qstrtemp = args[i];
                QByteArray qbatemp = qstrtemp.toLatin1();
                cargs[i] = strdup(qbatemp.data());
            }
            cargs[args.size()] = NULL;*/
            QString t = path;
            qDebug() << args.size();
            if(!(args.size() == 1 && args[0] == ""))
            for(int i = 0; i < args.size(); i++)
            {
                t += " " + args[i];
            }
            QByteArray qpath = t.toLatin1();
            char *cpath = NULL;
            cpath = strdup(qpath.data());
            scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
            for(int i = 0; i <= 453 ; i++)
            {
                if(i != SCMP_SYS(execve))
                    if(!seccomp_force_enable_calls(i))
                    {
                        QString key;
                        key = QString::number(i);
                        int v;
                        if(r.contains(key))
                        {
                            QJsonValue val = r.value(key);
                            if(val.isArray())
                            {
                                QJsonArray arr = val.toArray();
                                v = arr[0].toInt();
                            }
                            else
                            {
                                v = val.toInt();
                            }
                        }
                        else
                        {
                            v = JAIL_SYS_CALL_ABORT_FOREVER;
                        }
                        if(v == JAIL_SYS_CALL_ABORT_FOREVER)
                        {
                            seccomp_rule_add(ctx, SCMP_ACT_ERRNO(i), i, 0);
                        }
                        else if(v != JAIL_SYS_CALL_PASS_FOREVER)
                        {
                            seccomp_rule_add(ctx, SCMP_ACT_TRACE(i), i, 0);
                        }
                    }
            }
            seccomp_load(ctx);
            read(pp[0], &buffer, sizeof(buffer));
            //execvp(cpath, cargs);
            qDebug() << cpath;
            execl("/bin/sh", "sh", "-c", cpath, NULL);
            return;//not reachable
        }
        else
        {
            emit send_user_movement_observer_pid(user_movement_observer_pid);
            survived_procs.insert(child_pid);
            if(all_stop_mode_enabled)STOP_MODE = ALL_STOP;
            else STOP_MODE = NON_STOP;
            close(pp[0]);
            int buffer = 1;
            unsigned long ptrace_mask = PTRACE_O_TRACESECCOMP | PTRACE_O_EXITKILL | PTRACE_O_TRACEEXEC | PTRACE_O_TRACEEXIT;

            int clones[3] = {SCMP_SYS(clone), SCMP_SYS(fork), SCMP_SYS(vfork)};
            unsigned long cmasks[3] = {PTRACE_O_TRACECLONE, PTRACE_O_TRACEFORK, PTRACE_O_TRACEVFORK | PTRACE_O_TRACEVFORKDONE};
            for(int i = 0; i < 3; i ++)
            {
                QString key;
                key = QString::number(clones[i]);
                int v = JAIL_SYS_CALL_PASS_FOREVER;
                if(r.contains(key))
                {
                    QJsonValue val = r.value(key);
                    if(val.isArray())
                    {
                        QJsonArray arr = val.toArray();
                        v = arr[0].toInt();
                    }
                    else
                    {
                        v = val.toInt();
                    }
                }
                if(v != JAIL_SYS_CALL_PASS_FOREVER && v != JAIL_SYS_CALL_ABORT_FOREVER)
                {
                    ptrace_mask = ptrace_mask | cmasks[i];
                }
            }
            ptrace(PTRACE_SEIZE, child_pid, 0,  ptrace_mask);
            write(pp[1], &buffer, sizeof(buffer));
            while(endFlag)
            {
                QCoreApplication::processEvents();
                if(!notified_events.isEmpty())
                {
                    syscall_info info = notified_events.dequeue();
                    if(info.mode == syscall_info::ENTRY)
                    {
                        if(info.blockSig == SYSMSG_PEEK_ADDR)
                        {
                            for(int i = 0; i <= info.extraOption; i++)
                            {
                                long result;
                                result = ptrace(PTRACE_PEEKDATA, info.pid, info.args[nextMove] + i * 8, NULL);
                                emit sendPeekData(info.pid, i, result);
                            }
                        }
                        else
                        {
                            waiting_for_inject(info.pid);
                            long args[7] = {info.nr, info.args[0], info.args[1], info.args[2], info.args[3], info.args[4], info.args[5]};
                            int des[7] = {8 * ORIG_RAX, 8 * RDI, 8 * RSI, 8 * RCX, 8 * RDX, 8 * R8, 8 * R9};
                            for(int i = 0; i < 6; i++)
                            {
                                if(((info.mask >> i) & 1))
                                {
                                    ptrace(PTRACE_POKEUSER, info.pid, des[i], args[i]);
                                }
                            }

                            QString action = generateAction(info.nextMove, info.extraOption);

                            QString log;
                            if(info.nextMove != 2)log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(info.pid) + " nr: " + QString::number(info.nr) + "(" +
                                      findSyscallName(info.nr) + ")" +
                                      " arg1: " + QString::number(info.args[0]) + " arg2: " + QString::number(info.args[1]) + " arg3: " + QString::number(info.args[2]) + " arg4: " + QString::number(info.args[3]) +
                                      " arg5: " + QString::number(info.args[4]) + " arg6: " + QString::number(info.args[5]) + " action: " + action;
                            int isexec = 0;
                            if(info.nr == SCMP_SYS(execve))isexec = 1;
                            bool catch_reval = 0;
                            if(!info.nextMove)
                            {
                                catch_reval = 1;
                                ptrace(PTRACE_POKEUSER, info.pid, 8 * ORIG_RAX, -1);
                                ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                                waitpid(info.pid, 0, 0);
                            }
                            else if(info.nextMove != 2)
                            {
                                catch_reval = 1;
                                int isfork = 0;
                                if(info.nr == SCMP_SYS(execve))ptrace(PTRACE_CONT, info.pid, 0, 0);
                                else if(info.nr != SCMP_SYS(fork) && info.nr != SCMP_SYS(vfork) && info.nr != SCMP_SYS(clone))
                                    ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                                else
                                {
                                    isfork = 1;
                                    ptrace(PTRACE_CONT, info.pid, 0, 0);
                                }
                                int status = 0;
                                waitpid(info.pid, &status, 0);
                                if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_FORK<<8)))
                                {
                                    pid_t new_proc_pid = 0;
                                    int new_status;
                                    ptrace(PTRACE_GETEVENTMSG, info.pid, 0, &new_proc_pid);
                                    waitpid(new_proc_pid, &new_status, 0);
                                    //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                                    ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                                    survived_procs.insert(new_proc_pid);
                                    ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                                }
                                else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)))
                                {
                                    pid_t new_proc_pid = 0;
                                    int new_status;
                                    ptrace(PTRACE_GETEVENTMSG, info.pid, 0, &new_proc_pid);
                                    waitpid(new_proc_pid, &new_status, 0);
                                    //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                                    ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                                    survived_procs.insert(new_proc_pid);
                                    ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                                }
                                else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)))
                                {
                                    pid_t new_proc_pid = 0;
                                    int new_status;
                                    ptrace(PTRACE_GETEVENTMSG, info.pid, 0, &new_proc_pid);
                                    waitpid(new_proc_pid, &new_status, 0);
                                    //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                                    ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                                    survived_procs.insert(new_proc_pid);
                                    ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                                }
                                if(isfork || isexec)
                                {
                                    emit createProcTree(child_pid);
                                }
                                if(isfork)
                                {
                                    waitpid(info.pid, 0, 0);
                                }
                                if(isexec)catch_reval = 0;
                            }
                            if(catch_reval)
                            {
                                long syscallreval = ptrace(PTRACE_PEEKUSER, info.pid, 8 * RAX, 0);
                                emit handleSyscallExit(info.pid, info.nr, syscallreval);
                                while(blockSig_exit)
                                {
                                    if(blockSig_exit == SYSMSG_DEAL_LATER)
                                    {
                                        break;
                                    }
                                }
                                if(blockSig_exit == SYSMSG_DEAL_LATER)
                                {
                                    qDebug() << "deal later";
                                    QString reval = " returnval: not decided";
                                    log += reval;
                                }
                                else
                                {
                                    QString reval = " returnval: ";
                                    if(nextMove_exit == SYSMSG_KEEP_ORIG_REVAL)
                                    {
                                        reval += QString::number(syscallreval);
                                    }
                                    else if(nextMove_exit == SYSMSG_CHANGE_REVAL)
                                    {
                                        ptrace(PTRACE_POKEUSER, info.pid, 8 * RAX, newReval);
                                        reval += "was changed to " + QString::number(newReval);
                                    }
                                    log += reval;
                                    if(STOP_MODE == NON_STOP)ptrace(PTRACE_CONT, info.pid, 0, 0);
                                    else need_user_confirmation.remove(info.pid);
                                }
                                blockSig_exit = SYSMSG_KEEP_BLOCKING;
                            }
                            else
                            {
                                if(STOP_MODE == NON_STOP)ptrace(PTRACE_CONT, info.pid, 0, 0);
                                else need_user_confirmation.remove(info.pid);
                                if(isexec)
                                {
                                    emit createProcTree(child_pid);
                                }
                            }
                            if(nextMove != 2)emit writeLog(log);
                            if(need_user_confirmation.empty())ContinueAllProcess();
                            emit processRestarted(info.pid);
                        }
                    }
                    else
                    {
                        waiting_for_inject(info.pid);
                        QString reval = " reval";
                        if(info.mask)
                        {
                            ptrace(PTRACE_POKEUSER, info.pid, 8 * RAX, info.args[0]);
                            reval += " was changed to: ";
                        }
                        QString log;
                        log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(info.pid) + " nr: " + QString::number(info.nr) + "(" +
                              findSyscallName(info.nr) + "_EXIT" + ")" + reval + QString::number(info.args[0]);
                        emit writeLog(log);
                        if(STOP_MODE == NON_STOP)ptrace(PTRACE_CONT, info.pid, 0, 0);
                    }
                    continue;
                }
                int status = 0;
                int notifypid = waitpid(-1, &status, __WALL);
                if(notifypid == -1)break;
                if(notifypid == user_movement_observer_pid && WSTOPSIG(status) == SIGRTMAX - 1)//user has made a move
                {
                    ptrace(PTRACE_CONT, user_movement_observer_pid, 0, 0);
                    continue;
                }

                if((status >> 8 == (SIGTRAP | (PTRACE_EVENT_SECCOMP<<8))) || (status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXEC<<8))))
                {
                    emit processStopped(notifypid);
                    __ptrace_syscall_info si;
                    seccomp_data data;
                    memset(&data, 0, sizeof(data));
                    memset(&si, 0, sizeof(si));
                    ptrace(PTRACE_GET_SYSCALL_INFO, notifypid, sizeof(si), &si);
                    if(status >> 8 != (SIGTRAP | (PTRACE_EVENT_EXEC<<8)))
                    {
                        data.nr = si.seccomp.nr;
                        data.args[0] = si.seccomp.args[0];
                        data.args[1] = si.seccomp.args[1];
                        data.args[2] = si.seccomp.args[2];
                        data.args[3] = si.seccomp.args[3];
                        data.args[4] = si.seccomp.args[4];
                        data.args[5] = si.seccomp.args[5];
                    }
                    else
                    {
                        data.nr = SCMP_SYS(execve);
                    }
                    QString darg[6];
                    for(int i = 0; i <= 5; i++)
                    {
                        for(int j = 0; j < deref_offset; j++)
                        {
                            long result = ptrace(PTRACE_PEEKDATA, notifypid, data.args[i] + j * 8, NULL);
                            darg[i] += QString::number(result, 16).toUpper();
                        }
                    }
                    QList<QString> dargs;
                    for(int i = 0; i <= 5; i++)
                    {
                        dargs.append(darg[i]);
                    }
                    emit catchSyscall(notifypid, status, data, dargs);
                    while(blockSig)
                    {
                        trashcan ^= 1;
                        if(blockSig == SYSMSG_DEAL_LATER)
                        {
                            break;
                        }
                    }
                    if(blockSig == SYSMSG_DEAL_LATER)
                    {
                        qDebug() << "deal later";
                        if(STOP_MODE == ALL_STOP)
                        {
                            need_user_confirmation.insert(notifypid);
                            if(!procs_stopped)StopAllProcess(notifypid);
                        }
                        blockSig = SYSMSG_KEEP_BLOCKING;
                        continue;
                    }
                    blockSig = SYSMSG_KEEP_BLOCKING;

                    if(STOP_MODE == ALL_STOP && procs_stopped)
                    {
                        Pending_Procs.insert(notifypid, status);
                        continue;//continue the following step when all user notifications were done
                    }

                    QString action = generateAction(nextMove, extraOption);

                    waiting_for_inject(notifypid);
                    QString log;
                    if(nextMove != 2)log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(notifypid) + " nr: " + QString::number(data.nr) + "(" +
                              findSyscallName(data.nr) + ")" +
                              " arg1: " + QString::number(data.args[0]) + " arg2: " + QString::number(data.args[1]) + " arg3: " + QString::number(data.args[2]) + " arg4: " + QString::number(data.args[3]) +
                              " arg5: " + QString::number(data.args[4]) + " arg6: " + QString::number(data.args[5]) + " action: " + action;
                    int isexec = 0;
                    if(data.nr == SCMP_SYS(execve))isexec = 1;
                    bool catch_reval = 0;
                    bool isvfork = 0;
                    int isfork = 0;
                    if(!nextMove)
                    {
                        catch_reval = 1;
                        ptrace(PTRACE_POKEUSER, notifypid, 8 * ORIG_RAX, -1);
                        ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                        waitpid(notifypid, 0, 0);
                    }
                    else if(nextMove != 2)
                    {
                        catch_reval = 1;

                        if(data.nr != SCMP_SYS(fork) && data.nr != SCMP_SYS(vfork) && data.nr != SCMP_SYS(clone) && data.nr != SCMP_SYS(clone3))
                            ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                        else
                        {
                            isfork = 1;
                            ptrace(PTRACE_CONT, notifypid, 0, 0);
                        }
                        waitpid(notifypid, &status, 0);
                        if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_FORK<<8)))
                        {
                            catch_reval = 0;
                            pid_t new_proc_pid = 0;
                            int new_status;
                            ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                            waitpid(new_proc_pid, &new_status, 0);
                            qDebug() << "parent:" << notifypid << "child:" << new_proc_pid;
                            //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                            ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                            survived_procs.insert(new_proc_pid);
                            ptrace(PTRACE_CONT, notifypid, 0, 0);
                        }
                        else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)))
                        {
                            isvfork = 1;
                            catch_reval = 0;
                            pid_t new_proc_pid = 0;
                            int new_status;
                            ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                            waitpid(new_proc_pid, &new_status, 0);
                            //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                            ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                            survived_procs.insert(new_proc_pid);
                            ptrace(PTRACE_CONT, notifypid, 0, 0);
                        }
                        else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)))
                        {
                            catch_reval = 0;
                            pid_t new_proc_pid = 0;
                            int new_status;
                            ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                            waitpid(new_proc_pid, &new_status, 0);
                            //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                            ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                            survived_procs.insert(new_proc_pid);
                            ptrace(PTRACE_CONT, notifypid, 0, 0);
                        }
                        if(isfork || isexec)
                        {
                            emit createProcTree(child_pid);
                        }
                        if(isfork)
                        {
                            //waitpid(notifypid, 0, 0);
                        }
                        if(isexec)catch_reval = 0;
                    }
                    if(catch_reval)
                    {
                        long syscallreval = ptrace(PTRACE_PEEKUSER, notifypid, 8 * RAX, 0);
                        emit handleSyscallExit(notifypid, data.nr, syscallreval);
                        while(blockSig_exit)
                        {
                            trashcan ^= 1;
                            if(blockSig_exit == SYSMSG_DEAL_LATER)
                            {
                                break;
                            }
                        }
                        if(blockSig_exit == SYSMSG_DEAL_LATER)
                        {
                            if(STOP_MODE == ALL_STOP)
                            {
                                need_user_confirmation.insert(notifypid);
                                if(!procs_stopped)StopAllProcess(notifypid);
                            }
                            QString reval = " returnval: not decided";
                            log += reval;
                        }
                        else
                        {
                            QString reval = " returnval: ";
                            if(nextMove_exit == SYSMSG_KEEP_ORIG_REVAL)
                            {
                                reval += QString::number(syscallreval);
                            }
                            else if(nextMove_exit == SYSMSG_CHANGE_REVAL)
                            {
                                ptrace(PTRACE_POKEUSER, notifypid, 8 * RAX, newReval);
                                reval += QString::number(newReval);
                            }
                            log += reval;
                            ptrace(PTRACE_CONT, notifypid, 0, 0);
                        }
                        blockSig_exit = SYSMSG_KEEP_BLOCKING;
                    }
                    else
                    {
                        if(!isvfork && !isfork)ptrace(PTRACE_CONT, notifypid, 0, 0);
                        if(isexec)
                        {
                            emit createProcTree(child_pid);
                        }
                    }
                    if(nextMove != 2)emit writeLog(log);
                    emit processRestarted(notifypid);
                }
                else if(status >>8 == (SIGTRAP | (PTRACE_EVENT_VFORK_DONE<<8)) )
                {
                    ptrace(PTRACE_CONT, notifypid, 0, 0);
                    /*ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                    waitpid(notifypid, 0, 0);
                    QString log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(notifypid) + " vfork_done";
                    long syscallreval = ptrace(PTRACE_PEEKUSER, notifypid, 8 * RAX, 0);
                    emit handleSyscallExit(notifypid, SCMP_SYS(vfork), syscallreval);
                    while(blockSig_exit)
                    {
                        trashcan ^= 1;
                        if(blockSig_exit == SYSMSG_DEAL_LATER)
                        {
                            break;
                        }
                    }
                    if(blockSig_exit == SYSMSG_DEAL_LATER)
                    {
                        if(STOP_MODE == ALL_STOP)
                        {
                            need_user_confirmation.insert(notifypid);
                            if(!procs_stopped)StopAllProcess(notifypid);
                        }
                        QString reval = " returnval: not decided";
                        log += reval;
                    }
                    else
                    {
                        QString reval = " returnval: ";
                        if(nextMove_exit == SYSMSG_KEEP_ORIG_REVAL)
                        {
                            reval += QString::number(syscallreval);
                        }
                        else if(nextMove_exit == SYSMSG_CHANGE_REVAL)
                        {
                            ptrace(PTRACE_POKEUSER, notifypid, 8 * RAX, newReval);
                            reval += QString::number(newReval);
                        }
                        log += reval;
                        ptrace(PTRACE_CONT, notifypid, 0, 0);
                    }
                    blockSig_exit = SYSMSG_KEEP_BLOCKING;*/
                }
                else if(status >> 16 == PTRACE_EVENT_STOP)//group-stop
                {
                    if(STOP_MODE == ALL_STOP && procs_stopped)
                    {
                        need_ptrace_listen.insert(notifypid);
                    }
                    else ptrace(PTRACE_LISTEN, notifypid, 0, 0);
                }
                else if(status >>8 == (SIGTRAP | (PTRACE_EVENT_EXIT<<8)) )
                {
                    if(STOP_MODE == NON_STOP)
                    {
                        ptrace(PTRACE_CONT, notifypid, 0, 0);
                        survived_procs.remove(notifypid);
                    }
                }
                else if(WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP)//int3
                {
                    if(orig_codes.contains(notifypid))//trapped
                    {
                        //recover code
                        long rip = ptrace(PTRACE_PEEKUSER, notifypid, 8 * RIP, 0);
                        ptrace(PTRACE_POKEDATA, notifypid, rip - 1, orig_codes.value(notifypid));
                        orig_codes.remove(notifypid);
                        //record regs
                        user_regs_struct tempregs;
                        ptrace(PTRACE_GETREGS, notifypid, 0, &tempregs);
                        orig_regs.insert(notifypid, tempregs);
                        user_regs_struct regs;
                        memcpy(&regs, &tempregs, sizeof(struct user_regs_struct));

                        char* buf;
                        char* end;
                        char mapfile[0x100];
                        sprintf(mapfile, "/proc/%d/maps", notifypid);
                        FILE* fd = fopen(mapfile, "r");
                        buf = (char*) malloc(0x100);
                        do{
                            fgets(buf, 0x100, fd);
                        } while(!strstr(buf, settings.enableLDPRELOAD?"libhookhere.":"libc.") || !strstr(buf, "xp "));
                        end = strchr(buf, '-');
                        size_t tempaddr;
                        if(!settings.enableLDPRELOAD)
                        {
                            libcAddr = strtol(buf, &end, 16);
                            tempaddr = libcAddr;
                        }
                        else
                        {
                            tempaddr = strtol(buf, &end, 16) + gethookoffset();
                        }
                        need_recover.insert(notifypid, 1);
                        fclose(fd);

                        long code;
                        code_bak = ptrace(PTRACE_PEEKTEXT, notifypid, tempaddr, 0);
                        code = code_bak;
                        long hook = 0xcc050f;
                        memcpy(&code, &hook, 3);
                        ptrace(PTRACE_POKETEXT, notifypid, tempaddr, code);
                        syscall_info tempinfo = inject_events.value(notifypid);
                        regs.rax = tempinfo.nr;
                        if(tempinfo.status > 0)regs.rdi = tempinfo.args[0];
                        if(tempinfo.status > 1)regs.rsi = tempinfo.args[1];
                        if(tempinfo.status > 2)regs.rdx = tempinfo.args[2];
                        if(tempinfo.status > 3)regs.rcx = tempinfo.args[3];
                        if(tempinfo.status > 4)regs.r8 = tempinfo.args[4];
                        if(tempinfo.status > 5)regs.r9 = tempinfo.args[5];
                        regs.rip = tempaddr;
                        ptrace(PTRACE_SETREGS, notifypid, 0, &regs);
                        if(STOP_MODE == NON_STOP || !procs_stopped)ptrace(PTRACE_CONT, notifypid, 0, 0);
                    }
                    else if(notifypid == injectedPid)//instant inject
                    {
                        ptrace(PTRACE_POKETEXT, notifypid, libcAddr, code_bak);
                        ptrace(PTRACE_SETREGS, notifypid, 0, &regs_bak);
                        if(STOP_MODE == NON_STOP || !procs_stopped)ptrace(PTRACE_CONT, notifypid, 0, 0);
                    }
                    else if(need_recover.value(notifypid) == 1)
                    {
                        if(!settings.enableLDPRELOAD)ptrace(PTRACE_POKETEXT, notifypid, libcAddr, code_bak);
                        user_regs_struct tempregs = orig_regs.value(notifypid);
                        tempregs.rip -= 1;
                        ptrace(PTRACE_SETREGS, notifypid, 0, &tempregs);
                        need_recover.insert(notifypid, 0);
                        if(STOP_MODE == NON_STOP || !procs_stopped)ptrace(PTRACE_CONT, notifypid, 0, 0);
                    }
                    emit processRestarted(notifypid);
                }
                else if(WIFSTOPPED(status))
                {
                    if(procs_stopped)
                    {
                        need_inject_signal[notifypid] = WSTOPSIG(status);
                    }
                    else if(STOP_MODE == ALL_STOP && WSTOPSIG(status) == SIGSTOP && need_suppress_sigstop.contains(notifypid))
                    {
                        ptrace(PTRACE_CONT, notifypid, 0, 0);
                        need_suppress_sigstop.remove(notifypid);
                    }
                    else ptrace(PTRACE_CONT, notifypid, 0, WSTOPSIG(status));
                }
            }
            emit sendStop();
        }
    }
}

QString Watcher::findSyscallName(int nr)
{
    QFile st("/usr/include/x86_64-linux-gnu/asm/unistd_64.h");
    st.open(QFile::ReadOnly);
    QTextStream in(&st);
    in.readLine();
    in.readLine();
    in.readLine();
    QString line, sname = "unknown", tname, snr;
    while(!in.atEnd())
    {
        line = in.readLine();
        tname = line.section(" ", 1, 1);
        snr = line.section(" ", 2, 2);
        int inr = snr.toInt();
        if(inr == nr)
        {
            sname = tname;
            break;
        }
    }
    st.close();
    return sname;
}

QString Watcher::generateAction(int nm, int eo)
{
    QString action;
    if(nm == 1)//pass
    {
        if(eo == 0)
        {
            action = "pass by user";
        }
        else if(eo == 1)
        {
            action = "pass according to rules";
        }
        else
        {
            action = "pass by user and add rule";
        }
    }
    else
    {
        if(eo == 0)
        {
            action = "abort by user";
        }
        else if(eo == 1)
        {
            action = "abort according to rules";
        }
        else
        {
            action = "abort by user and add rule";
        }
    }
    return action;
}
