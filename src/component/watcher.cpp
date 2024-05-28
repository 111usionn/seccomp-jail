#include "controller.h"

bool Watcher::seccomp_force_enable_calls(int i)
{
    if(i != SCMP_SYS(read) && i != SCMP_SYS(write) && i != SCMP_SYS(exit) && i != SCMP_SYS(sigreturn) && i != SCMP_SYS(seccomp) && i != SCMP_SYS(ptrace) && i != SCMP_SYS(close) /*&& i!= SCMP_SYS(mmap) && i!= SCMP_SYS(fork) && i!= SCMP_SYS(clone) && i!= SCMP_SYS(vfork)*/)
    {
        return 0;
    }
    return 1;
}

Watcher::Watcher(QObject *parent)
    : QObject{parent}
{
    endFlag = 1;
    blockSig = 1;
    addroffset = 0;
    settings.enableLDPRELOAD = 1;
}

int Watcher::gethookoffset()
{
    int tempoffset = addroffset;
    addroffset += 3;
    addroffset %= 255;
    return tempoffset;
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

void Watcher::dealNow(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption)
{
    syscall_info temp;
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
    int stat = 0;
    for(int i = 0; i < 1000 ; i++)
    {
        waitpid(pid, &stat, WNOHANG);
        if(stat)break;
    }
    if(stat >> 8 != (SIGTRAP | (PTRACE_EVENT_STOP<<8)))
    {
        syscall_info tempinfo = {0, argc, nr, arg1, arg2, arg3, arg4, arg5, arg6};
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
        qDebug () << buf;
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

void Watcher::createPuppet(const QString path, QStringList args, QJsonObject r)
{
    int pp[2];
    pipe(pp);
    pid_t child_pid = fork();
    if(child_pid == 0)//child
    {
        setenv("LD_PRELOAD","./libhookhere.so", 1);
        int buffer;
        close(pp[1]);
        //sleep(1);
        QByteArray qpath = path.toLatin1();
        char *cpath = NULL;
        cpath = strdup(qpath.data());
        char *cargs[150];
        for(int i = 0; i < args.size(); i++)
        {
            QString qstrtemp = args[i];
            QByteArray qbatemp = qstrtemp.toLatin1();
            cargs[i] = strdup(qbatemp.data());
        }
        cargs[args.size()] = NULL;
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
                    v = val.toInt();
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
        execvp(cpath, cargs);
        return;//not reachable
    }
    else
    {
        close(pp[0]);
        int buffer = 1;
        int ptrace_mask = PTRACE_O_TRACESECCOMP | PTRACE_O_EXITKILL | PTRACE_O_TRACEEXEC;

        int clones[3] = {SCMP_SYS(clone), SCMP_SYS(fork), SCMP_SYS(vfork)};
        int cmasks[3] = {PTRACE_O_TRACECLONE, PTRACE_O_TRACEFORK, PTRACE_O_TRACEVFORK};
        for(int i = 0; i < 3; i ++)
        {
            QString key;
            key = QString::number(clones[i]);
            int v = JAIL_SYS_CALL_PASS_FOREVER;
            if(r.contains(key))
            {
                QJsonValue val = r.value(key);
                v = val.toInt();
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
                    QString action;
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

                    if(info.nextMove == 1)//pass
                    {
                        if(info.extraOption == 0)
                        {
                            action = "pass by user";
                        }
                        else if(info.extraOption == 1)
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
                        if(info.extraOption == 0)
                        {
                            action = "abort by user";
                        }
                        else if(info.extraOption == 1)
                        {
                            action = "abort according to rules";
                        }
                        else
                        {
                            action = "abort by user and add rule";
                        }
                    }
                    QString log;
                    if(info.nextMove != 2)log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(info.pid) + " nr: " + QString::number(info.nr) + "(" + Controller::findSyscallName(info.nr) + ")" +
                              " arg1: " + QString::number(info.args[0]) + " arg2: " + QString::number(info.args[1]) + " arg3: " + QString::number(info.args[2]) + " arg4: " + QString::number(info.args[3]) +
                              " arg5: " + QString::number(info.args[4]) + " arg6: " + QString::number(info.args[5]) + " action: " + action;
                    if(info.status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXEC<<8)))
                    {
                        emit createProcTree(child_pid);
                    }
                    if(!info.nextMove)
                    {
                        ptrace(PTRACE_POKEUSER, info.pid, 8 * ORIG_RAX, -1);
                    }
                    else if(info.nextMove != 2)
                    {
                        int isfork = 0;
                        if(info.nr != SCMP_SYS(fork) && info.nr != SCMP_SYS(vfork) && info.nr != SCMP_SYS(clone))
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
                            ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                            emit createProcTree(child_pid);
                        }
                        else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)))
                        {
                            pid_t new_proc_pid = 0;
                            int new_status;
                            ptrace(PTRACE_GETEVENTMSG, info.pid, 0, &new_proc_pid);
                            waitpid(new_proc_pid, &new_status, 0);
                            //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                            ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                            ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                            emit createProcTree(child_pid);
                        }
                        else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)))
                        {
                            pid_t new_proc_pid = 0;
                            int new_status;
                            ptrace(PTRACE_GETEVENTMSG, info.pid, 0, &new_proc_pid);
                            waitpid(new_proc_pid, &new_status, 0);
                            //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                            ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                            ptrace(PTRACE_SYSCALL, info.pid, 0, 0);
                            emit createProcTree(child_pid);
                        }
                        if(isfork)
                        {
                            waitpid(info.pid, 0, 0);
                        }
                        long syscallreval = ptrace(PTRACE_PEEKUSER, info.pid, 8 * RAX, 0);
                        QString reval = " returnval: " + QString::number(syscallreval);
                        log += reval;
                    }
                    if(nextMove != 2)emit writeLog(log);
                    ptrace(PTRACE_CONT, info.pid, 0, 0);
                    emit processRestarted(info.pid);
                }
                continue;
            }
            int status = 0;
            int notifypid = waitpid(-1, &status, __WALL | WNOHANG);
            if(notifypid == -1)break;
            else if(notifypid == 0)
            {
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
                emit catchSyscall(notifypid, status, data);
                while(blockSig)
                {
                    if(blockSig == SYSMSG_PEEK_ADDR)
                    {
                        for(int i = 0; i <= extraOption; i++)
                        {
                            long result;
                            result = ptrace(PTRACE_PEEKDATA, notifypid, data.args[nextMove] + i * 8, NULL);
                            emit sendPeekData(notifypid, i, result);
                        }
                        blockSig = SYSMSG_KEEP_BLOCKING;
                    }
                    else if(blockSig == SYSMSG_DEAL_LATER)
                    {
                        break;
                    }
                }
                if(blockSig == SYSMSG_DEAL_LATER)
                {
                    qDebug() << "deal later";
                    blockSig = SYSMSG_KEEP_BLOCKING;
                    continue;
                }
                blockSig = SYSMSG_KEEP_BLOCKING;
                QString action;
                if(nextMove == 1)//pass
                {
                    if(extraOption == 0)
                    {
                        action = "pass by user";
                    }
                    else if(extraOption == 1)
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
                    if(extraOption == 0)
                    {
                        action = "abort by user";
                    }
                    else if(extraOption == 1)
                    {
                        action = "abort according to rules";
                    }
                    else
                    {
                        action = "abort by user and add rule";
                    }
                }
                waiting_for_inject(notifypid);
                QString log;
                if(nextMove != 2)log = QDateTime::currentDateTime().toString() + " pid: " + QString::number(notifypid) + " nr: " + QString::number(data.nr) + "(" + Controller::findSyscallName(data.nr) + ")" +
                          " arg1: " + QString::number(data.args[0]) + " arg2: " + QString::number(data.args[1]) + " arg3: " + QString::number(data.args[2]) + " arg4: " + QString::number(data.args[3]) +
                          " arg5: " + QString::number(data.args[4]) + " arg6: " + QString::number(data.args[5]) + " action: " + action;
                if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_EXEC<<8)))
                {
                    emit createProcTree(child_pid);
                }
                if(!nextMove)
                {
                    ptrace(PTRACE_POKEUSER, notifypid, 8 * ORIG_RAX, -1);
                }
                else if(nextMove != 2)
                {
                    int isfork = 0;
                    if(data.nr != SCMP_SYS(fork) && data.nr != SCMP_SYS(vfork) && data.nr != SCMP_SYS(clone))
                    ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                    else
                    {
                        isfork = 1;
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
                        ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                        ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                        emit createProcTree(child_pid);
                    }
                    else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_VFORK<<8)))
                    {
                        pid_t new_proc_pid = 0;
                        int new_status;
                        ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                        waitpid(new_proc_pid, &new_status, 0);
                        //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                        ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                        ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                        emit createProcTree(child_pid);
                    }
                    else if(status >> 8 == (SIGTRAP | (PTRACE_EVENT_CLONE<<8)))
                    {
                        pid_t new_proc_pid = 0;
                        int new_status;
                        ptrace(PTRACE_GETEVENTMSG, notifypid, 0, &new_proc_pid);
                        waitpid(new_proc_pid, &new_status, 0);
                        //ptrace(PTRACE_SETOPTIONS, new_proc_pid, 0,  ptrace_mask);
                        ptrace(PTRACE_CONT, new_proc_pid, 0, 0);
                        ptrace(PTRACE_SYSCALL, notifypid, 0, 0);
                        emit createProcTree(child_pid);
                    }
                    if(isfork)
                    {
                        waitpid(notifypid, 0, 0);
                    }
                    long syscallreval = ptrace(PTRACE_PEEKUSER, notifypid, 8 * RAX, 0);
                    QString reval = " returnval: " + QString::number(syscallreval);
                    log += reval;
                }
                if(nextMove != 2)emit writeLog(log);
                ptrace(PTRACE_CONT, notifypid, 0, 0);
                emit processRestarted(notifypid);
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
                    ptrace(PTRACE_CONT, notifypid, 0, 0);
                }
                else if(notifypid == injectedPid)//instant inject
                {
                    ptrace(PTRACE_POKETEXT, notifypid, libcAddr, code_bak);
                    ptrace(PTRACE_SETREGS, notifypid, 0, &regs_bak);
                    ptrace(PTRACE_CONT, notifypid, 0, 0);
                }
                else if(need_recover.value(notifypid) == 1)
                {
                    if(!settings.enableLDPRELOAD)ptrace(PTRACE_POKETEXT, notifypid, libcAddr, code_bak);
                    user_regs_struct tempregs = orig_regs.value(notifypid);
                    tempregs.rip -= 1;
                    ptrace(PTRACE_SETREGS, notifypid, 0, &tempregs);
                    need_recover.insert(notifypid, 0);
                    ptrace(PTRACE_CONT, notifypid, 0, 0);
                }
                emit processRestarted(notifypid);
            }
            else if(status >> 16 == PTRACE_EVENT_STOP)//group-stop
            {
                ptrace(PTRACE_LISTEN, notifypid, 0, 0);
            }
			else if(WIFSTOPPED(status))
			{
                ptrace(PTRACE_CONT, notifypid, 0, WSTOPSIG(status));
			}
        }
        emit sendStop();
    }
}
