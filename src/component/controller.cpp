#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    isTracing = 0;
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
        if(!Watcher::seccomp_force_enable_calls(i))
        {
            table.insert(temp, option);
        }
        else
        {
            table.insert(temp, JAIL_SYS_CALL_PASS_FOREVER);
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
    if(currentRules.contains(key))
    {
        QJsonValue val = currentRules.value(key);
        if(val.isArray())
        {
            return val.toArray();
        }
        else
        {
            QJsonArray arr;
            arr.append(val);
            return arr;
        }
    }
    else
    {
        QJsonValue val = JAIL_SYS_CALL_ABORT_FOREVER;
        QJsonArray arr;
        arr.append(val);
        return arr;
    }
}

int Controller::updateRule(int n, int option, QString script)
{
    QString nr = QString::number(n);
    if(Watcher::seccomp_force_enable_calls(n)) return 0;
    if(currentRules.contains(nr))
    {
        if(option < 5)
        currentRules[nr] = option;
        else
        {
            QByteArray qba = script.toUtf8();
            QString script_base64 = qba.toBase64();
            QJsonArray temp = {5, script_base64};
            currentRules[nr] = temp;
        }
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
    QProcess p;
    p.start("pstree", QStringList() << "-p" << "-U" << QString::number(pid));
    p.waitForFinished();
    QByteArray output = p.readAllStandardOutput();
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
    thread = new QThread;
    watcher = new Watcher;
    watcher->moveToThread(thread);
    connect(thread, &QThread::finished, watcher, &Watcher::deleteLater);
    connect(watcher, &Watcher::destroyed, thread, &QThread::deleteLater);
    connect(this, &Controller::threadQuit, thread, &QThread::terminate);
    QStringList list = args.split(" ");
    //connect
    thread->start();
    connect(this, &Controller::st, watcher, &Watcher::createPuppet);
    connect(watcher, &Watcher::catchSyscall, this, &Controller::notifySyscall);
    connect(watcher, &Watcher::sendPeekData, this, &Controller::notifyPeekData);
    connect(watcher, &Watcher::writeLog, this, &Controller::sendLog);
    connect(watcher, &Watcher::sendStop, this, &Controller::stopTrace);
    connect(watcher, &Watcher::createProcTree, this, &Controller::drawProcTree);
    connect(this, &Controller::startInjector, watcher, &Watcher::injector);
    connect(this, &Controller::pushEvent, watcher, &Watcher::dealNow);
    emit st(path, list, currentRules);
    return 1;
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

void Controller::getCommand(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption)
{
    emit pushEvent(pid, status, nr, arg1, arg2, arg3, arg4, arg5, arg6, mask, nextMove, blockSig, extraOption);
}


void Controller::notifySyscall(int pid, int status, seccomp_data data, QList<QString> dargs)
{
    QString sname;
    if(!finishmunmap)
    {
        stopBlocking(2, SYSMSG_STOP_BLOCKING, 0);
        if(data.nr == SCMP_SYS(munmap))
        {
            finishmunmap = 1;
        }
    }
    else
    {
        QJsonArray ja = checkRule(data.nr);
        int resp_type = ja[0].toInt();
        REJUDGE:
        switch(resp_type)
        {
        case JAIL_SYS_CALL_PASS:
            stopBlocking(1, SYSMSG_STOP_BLOCKING, 1);
            break;
        case JAIL_SYS_CALL_ABORT:
            stopBlocking(0, SYSMSG_STOP_BLOCKING, 1);
            break;
        case JAIL_SYS_CALL_NOTIFY:
            sname = findSyscallName(data.nr);
            emit showSyscall(pid, status, sname, data.nr, QString::number(data.args[0]), QString::number(data.args[1]), QString::number(data.args[2]), QString::number(data.args[3]), QString::number(data.args[4]), QString::number(data.args[5]));
            stopBlocking(0, SYSMSG_DEAL_LATER, 0);
            break;
        case JAIL_SYS_CALL_PASS_FOREVER:
            stopBlocking(2, SYSMSG_STOP_BLOCKING, 0);
            break;
        case JAIL_SYS_CALL_CUSTOM:
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

void Controller::stopBlocking(int option, int blockState, int arg)
{
    watcher->nextMove = option;
    watcher->extraOption = arg;
    watcher->blockSig = blockState;
}

void Controller::sendLog(QString log)
{
    emit showLog(log);
}

void Controller::stopTrace()
{
    isTracing = 0;
    emit isTracingchanged(isTracing);
    watcher->endFlag = 0;
    emit threadQuit();
}
