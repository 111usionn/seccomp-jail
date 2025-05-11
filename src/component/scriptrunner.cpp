#include "scriptrunner.h"

ScriptRunner::ScriptRunner() {}

int ScriptRunner::run(int pid, seccomp_data &data, QList<QString> &dargs, QString user_script)
{
    QProcess proc;
    QString command;
    command += "SJ_PID=" + QString::number(pid);
    for(int i = 0; i < 6; i++)
    {
        command += " SJ_ARG" + QString::number(i+1) + "=" + QString::number(data.args[i]);
    }
    proc.start("bash");
    proc.waitForStarted();
    QByteArray qba = (command + "\n").toUtf8();
    proc.write(qba.data());
    proc.waitForBytesWritten();
    for(int i = 0; i < 6; i++)
    {
        QString cmd = "SJ_DARG" + QString::number(i+1) + "=$(cat <<EOF" + "\n";
        qba = cmd.toUtf8();
        proc.write(qba.data());
        proc.waitForBytesWritten();

        QString t = dargs[i] + "\n";
        qba = t.toUtf8();
        proc.write(qba.data());
        proc.waitForBytesWritten();

        proc.write("EOF\n");
        proc.waitForBytesWritten();

        proc.write(")\n");
        proc.waitForBytesWritten();
    }
    command = user_script;
    qba.clear();
    qba = QByteArray::fromBase64(command.toLatin1());
    qba.append('\n');
    proc.write(qba.data());
    proc.waitForFinished();
    return proc.exitCode();
}
