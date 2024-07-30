#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    isTracing = 0;
    isRemote = 0;
}

Controller::~Controller()
{
    if(isTracing)
    {
        stopTrace();
    }
}

QString Controller::getCurrentJson()
{
    QJsonObject filteredRules = currentRules;
    QJsonObject::iterator it = filteredRules.begin();
    QJsonDocument doc(filteredRules);
    QByteArray t = doc.toJson();
    QString str(t);
    return str;
}

void Controller::changeRuleDisplayFilter(int rule, bool state)
{
    ruleDisplayFilter[rule] = state;
    emit currentRuleChanged();
}

void Controller::createDefaultRule(int option)
{
    QFile file("./default.json");
    QJsonObject table;
    QString temp;
    for(int i = 0; i <= 453; i++)
    {
        temp = QString::number(i);
        QJsonArray temparr;
        temparr.append(QJsonValue(""));
        temparr.append(QJsonValue(""));
        temparr.append(QJsonValue(0));
        temparr.append(QJsonValue(""));
        if(!Watcher::seccomp_force_enable_calls(i))
        {
            temparr[0] = QJsonValue(option);
            table.insert(temp, temparr);
        }
        else
        {
            temparr[0] = QJsonValue(JAIL_SYS_CALL_PASS_FOREVER);
            table.insert(temp, temparr);
        }
    }
    QJsonDocument doc(table);
    QByteArray json = doc.toJson();
    if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
    file.write(json);
    file.close();
}

int Controller::setRule(QString path)
{
    if(path.isEmpty())
    {
        return 0;
    }
    QUrl rule_url(path);
    QString localPath = rule_url.toLocalFile();
    loadRule(localPath);
    return 1;
}

void Controller::loadRule(QString path)
{
    QFile file(path);
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(json);
    currentRules = doc.object();
    currentRulePath = path;
    emit currentRuleChanged();
}

QJsonArray Controller::checkRule(int n)
{
    QString key;
    key = QString::number(n);
    qDebug() << key;
    if(currentRules.contains(key))
    {
        QJsonValue val = currentRules.value(key);
        return val.toArray();
    }
    else
    {
        QJsonValue val = JAIL_SYS_CALL_ABORT_FOREVER;
        QJsonArray arr;
        arr.append(val);
        arr.append(QJsonValue(""));
        arr.append(QJsonValue(0));
        arr.append(QJsonValue(""));
        return arr;
    }
}

int Controller::updateRule(int n, int option, QString script)
{
    QString nr = QString::number(n);
    if(Watcher::seccomp_force_enable_calls(n)) return 0;
    if(currentRules.contains(nr))
    {
        QJsonArray arr = currentRules[nr].toArray();
        if(option < 5)
        {
            arr[0] = option;
            arr[1] = QJsonValue("");
        }
        else
        {
            QByteArray qba = script.toUtf8();
            QString script_base64 = qba.toBase64();
            //QJsonArray temp = {5, script_base64};
            arr[0] = 5;
            arr[1] = QJsonValue(script_base64);
        }
        currentRules[nr] = arr;
        emit currentRuleChanged();
        return 1;
    }
    else
    {
        return 0;
    }
}

int Controller::updateExitRule(int n, int option, long newReval)
{
    QString nr = QString::number(n);
    if(Watcher::seccomp_force_enable_calls(n)) return 0;
    if(currentRules.contains(nr))
    {
        QJsonArray arr = currentRules[nr].toArray();
        arr[2] = option;
        if(option != JAIL_SYS_CALL_EXIT_CHANGE)
        {
            arr[3] = QJsonValue("");
        }
        else
        {
            qint64 v = newReval;
            arr[3] = QJsonValue(v);
        }
        currentRules[nr] = arr;
        emit currentRuleChanged();
        return 1;
    }
    else
    {
        return 0;
    }
}


QString Controller::qmlFSN(int nr)
{
    return Controller::findSyscallName(nr);
}

void Controller::saveCurrentRule(QString saveAs)
{
    if(saveAs.isEmpty())//save
    {
        QFile file(currentRulePath);
        QJsonDocument doc(currentRules);
        QByteArray json = doc.toJson();
        if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
        file.write(json);
        file.close();
    }
    else//save as
    {
        QUrl rule_url(saveAs);
        QString localPath = rule_url.toLocalFile();
        QFile file(localPath);
        QJsonDocument doc(currentRules);
        QByteArray json = doc.toJson();
        if(!file.open(QFile::WriteOnly | QFile::Truncate))file.open(QFile::WriteOnly);
        file.write(json);
        file.close();
    }
}

int Controller::haveCurrentRule()
{
    return !currentRules.isEmpty();
}

void Controller::drawProcTree(int pid)
{
    QByteArray output;
    QProcess p;
    p.start("pstree", QStringList() << "-p" << "-U" << QString::number(pid));
    p.waitForFinished();
    output = p.readAllStandardOutput();
    p.close();
    QString procTree(output);
    emit qmlDrawProcTree(procTree);
}

void Controller::startInject(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc)
{
    emit startInjector(pid, nr, arg1, arg2, arg3, arg4, arg5, arg6, argc);
}
int Controller::startTrace(QString path, QString args)
{
    if(!haveCurrentRule())
    {
        return 0;//no rules
    }
    isTracing = 1;
    emit isTracingchanged(isTracing);
    finishmunmap = checkRule(SCMP_SYS(munmap))[0].toInt() == JAIL_SYS_CALL_PASS_FOREVER ?1:0;
    QStringList list = args.split(" ");
    if(!isRemote)
    {
        thread = new QThread;
        watcher = new Watcher(0);
        watcher->moveToThread(thread);
        connect(thread, &QThread::finished, watcher, &Watcher::deleteLater);
        connect(watcher, &Watcher::destroyed, thread, &QThread::deleteLater);
        connect(this, &Controller::threadQuit, thread, &QThread::terminate);
        thread->start();
        connect(this, &Controller::st, watcher, &Watcher::createPuppet);
        connect(watcher, &Watcher::catchSyscall, this, &Controller::notifySyscall);
        connect(watcher, &Watcher::sendPeekData, this, &Controller::notifyPeekData);
        connect(watcher, &Watcher::writeLog, this, &Controller::sendLog);
        connect(watcher, &Watcher::sendStop, this, &Controller::stopTrace);
        connect(watcher, &Watcher::createProcTree, this, &Controller::drawProcTree);
        connect(this, &Controller::startInjector, watcher, &Watcher::injector);
        connect(this, &Controller::pushEvent, watcher, &Watcher::dealNow);
        connect(watcher, &Watcher::handleSyscallExit, this, &Controller::notifySyscallExit);
        emit st(path, list, currentRules);
    }
    else
    {
        qDebug() << "remote tracing..";
        QString endPoint = path.split(" ").at(0), realPath = path.split(" ").at(1);
        qDebug() << endPoint << realPath;
        myTcpSocket = new MyTcpSocket(0, 0);
        connect(myTcpSocket, &MyTcpSocket::myReadyRead, this, &Controller::readDataFromSocket);
        connect(this, &Controller::sendDataToServerR, myTcpSocket, &MyTcpSocket::writeSlotR);
        myTcpSocket->connectToHost(endPoint.split(":").at(0), endPoint.split(":").at(1).toInt());
        if(myTcpSocket->waitForConnected(5000))//5s
        {
            qDebug() << "connected";
            DataPackage pkg;
            pkg.type = COMMAND_TO_REMOTE_START_TRACE;
            QDataStream out(&pkg.data, QIODevice::WriteOnly);
            out << realPath << list << currentRules;
            emit sendDataToServerR(pkg);
        }
        else
        {
            myTcpSocket->deleteLater();
        }
    }
    return 1;
}

void Controller::readDataFromSocket(QByteArray qba)
{
    QDataStream in(&qba, QIODevice::ReadOnly);
    struct DataPackage temp;
    in >> temp.type >> temp.data;
    QDataStream iN(&temp.data, QIODevice::ReadOnly);
    if(temp.type == COMMAND_FROM_REMOTE_CATCHSYSCALL)
    {
        int pid, status;
        seccomp_data data;
        QList<QString> dargs;
        iN >> pid >> status >> data.nr >> data.args[0] >> data.args[1] >> data.args[2] >> data.args[3] >> data.args[4] >> data.args[5] >> data.args[6] >> dargs;
        notifySyscall(pid, status, data, dargs);
    }
    else if(temp.type == COMMAND_FROM_REMOTE_SENDPEEKDATA)
    {
        int pid, num;
        qint64 data;
        iN >> pid >> num >> data;
        notifyPeekData(pid, num, data);
    }
    else if(temp.type == COMMAND_FROM_REMOTE_WRITELOG)
    {
        QString log;
        iN >> log;
        sendLog(log);
    }
    else if(temp.type == COMMAND_FROM_REMOTE_CREATEPROCTREE)
    {
        QString procTree;
        iN >> procTree;
        emit qmlDrawProcTree(procTree);
    }
    else if(temp.type == COMMAND_FROM_REMOTE_SENDSTOP)
    {
        stopTrace();
    }
    else if(temp.type == COMMAND_FROM_REMOTE_RESULT_OF_SCRIPT)
    {
        int exit_code, pid, status;
        seccomp_data data;
        QList<QString> dargs;
        iN >> exit_code >> pid >> status >> data.nr >> data.args[0] >> data.args[1] >> data.args[2] >> data.args[3] >> data.args[4] >> data.args[5] >> data.args[6] >> dargs;
        notifySyscall(pid, status, data, dargs, exit_code);
    }
    else if(temp.type == COMMAND_FROM_REMOTE_HANDLESYSCALLEXIT)
    {
        int pid, nr;
        qint64 reval;
        iN >> pid >> nr >> reval;
        notifySyscallExit(pid, nr, reval);
    }
}

QString Controller::findSyscallName(int nr)
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

void Controller::getCommand(bool mode, int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption)
{
    if(!isRemote)
    {
        emit pushEvent(mode, pid, status, nr, arg1, arg2, arg3, arg4, arg5, arg6, mask, nextMove, blockSig, extraOption);
    }
    else
    {
        DataPackage pkg;
        pkg.type = COMMAND_TO_REMOTE_PUSH_EVENT;
        QDataStream out(&pkg.data, QIODevice::WriteOnly);
        out << mode << pid << status << nr << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << mask << nextMove << blockSig << extraOption;
        emit sendDataToServerR(pkg);
    }
}


void Controller::notifySyscall(int pid, int status, seccomp_data data, QList<QString> dargs, int remote_script_resp)
{
    QString sname;
    if(!finishmunmap)
    {
        stopBlocking(isRemote, 2, SYSMSG_STOP_BLOCKING, 0);
        if(data.nr == SCMP_SYS(munmap))
        {
            finishmunmap = 1;
        }
    }
    else
    {
        QJsonArray ja = checkRule(data.nr);
        int resp_type = remote_script_resp == -1?ja[0].toInt():remote_script_resp;
        REJUDGE:
        switch(resp_type)
        {
        case JAIL_SYS_CALL_PASS:
            stopBlocking(isRemote, 1, SYSMSG_STOP_BLOCKING, 1);
            break;
        case JAIL_SYS_CALL_ABORT:
            stopBlocking(isRemote, 0, SYSMSG_STOP_BLOCKING, 1);
            break;
        case JAIL_SYS_CALL_NOTIFY:
            sname = findSyscallName(data.nr);
            emit showSyscall(pid, status, sname, data.nr, QString::number(data.args[0]), QString::number(data.args[1]), QString::number(data.args[2]), QString::number(data.args[3]), QString::number(data.args[4]), QString::number(data.args[5]));
            stopBlocking(isRemote, 0, SYSMSG_DEAL_LATER, 0);
            break;
        case JAIL_SYS_CALL_PASS_FOREVER:
            stopBlocking(isRemote, 2, SYSMSG_STOP_BLOCKING, 0);
            break;
        case JAIL_SYS_CALL_CUSTOM:
            if(!isRemote)
            {
                QProcess script;
                QString command;
                command += "SJ_PID=" + QString::number(pid);
                for(int i = 0; i < 6; i++)
                {
                    command += " SJ_ARG" + QString::number(i+1) + "=" + QString::number(data.args[i]);
                }
                script.start("bash");
                script.waitForStarted();
                QByteArray qba = (command + "\n").toUtf8();
                script.write(qba.data());
                script.waitForBytesWritten();
                for(int i = 0; i < 6; i++)
                {
                    QString cmd = "SJ_DARG" + QString::number(i+1) + "=$(cat <<EOF" + "\n";
                    qba = cmd.toUtf8();
                    script.write(qba.data());
                    script.waitForBytesWritten();

                    QString t = dargs[i] + "\n";
                    qba = t.toUtf8();
                    script.write(qba.data());
                    script.waitForBytesWritten();

                    script.write("EOF\n");
                    script.waitForBytesWritten();

                    script.write(")\n");
                    script.waitForBytesWritten();
                }
                command = ja[1].toString();
                qba.clear();
                qba = QByteArray::fromBase64(command.toLatin1());
                qba.append('\n');
                script.write(qba.data());
                script.waitForFinished();
                resp_type = script.exitCode();
                qDebug() << "resp_type:" << resp_type;
                goto REJUDGE;
            }
            else
            {
                DataPackage pkg;
                pkg.type = COMMAND_TO_REMOTE_RUN_SCRIPT;
                QDataStream out(&pkg.data, QIODevice::WriteOnly);
                out << ja[1].toString() << pid << status << data.nr << data.args[0] << data.args[1] << data.args[2] << data.args[3] << data.args[4] << data.args[5] << dargs;
                emit sendDataToServerR(pkg);
            }
        }
    }
}

void Controller::notifySyscallExit(int pid, int nr, long syscallreval)
{
    QString sname;
    QJsonArray ja = checkRule(nr);
    int resp_type = ja[2].toInt();
    qDebug() << ja[0] << ja[1] << ja[2] << ja[3];
    switch(resp_type)
    {
    case JAIL_SYS_CALL_EXIT_DEFAULT:
        stopBlockingExit(isRemote, SYSMSG_KEEP_ORIG_REVAL, SYSMSG_STOP_BLOCKING);
        break;
    case JAIL_SYS_CALL_EXIT_CHANGE:
        stopBlockingExit(isRemote, SYSMSG_CHANGE_REVAL, SYSMSG_STOP_BLOCKING, syscallreval);
        break;
    case JAIL_SYS_CALL_EXIT_NOTIFY:

        sname = findSyscallName(nr);
        emit showSyscallExit(pid, sname, nr, QString::number(syscallreval));
        stopBlockingExit(isRemote, 0, SYSMSG_DEAL_LATER);
        break;
    }
}

void Controller::notifyPeekData(int pid, int num, long data)
{
    char temp[9];
    temp[8] = '\0';
    memcpy(temp, &data, 8);
    QString qstrtemp(temp);
    emit showPeekData(pid, num, data, qstrtemp);
}

void Controller::stopBlocking(bool mode, int option, int blockState, int arg)
{
    if(!mode)
    {
        watcher->nextMove = option;
        watcher->extraOption = arg;
        watcher->blockSig = blockState;
    }
    else
    {
        DataPackage pkg;
        pkg.type = COMMAND_TO_REMOTE_STOP_BLOCKING;
        QDataStream out(&pkg.data, QIODevice::WriteOnly);
        out << option << blockState << arg;
        emit sendDataToServerR(pkg);
    }
}

void Controller::stopBlockingExit(bool mode, int option, int blockState, long newval)
{
    if(!mode)
    {
        watcher->nextMove_exit = option;
        watcher->blockSig_exit = blockState;
        watcher->newReval = newval;
    }
    else
    {
        DataPackage pkg;
        pkg.type = COMMAND_TO_REMOTE_STOP_BLOCKING_EXIT;
        QDataStream out(&pkg.data, QIODevice::WriteOnly);
        out << option << blockState << qint64(newval);
        emit sendDataToServerR(pkg);
    }
}

void Controller::sendLog(QString log)
{
    emit showLog(log);
}

void Controller::stopTrace()
{
    isTracing = 0;
    emit isTracingchanged(isTracing);
    if(!isRemote)
    {
        watcher->endFlag = 0;
        emit threadQuit();
    }
}

void Controller::isRemote_setter(bool val)
{
    isRemote = val;
}
