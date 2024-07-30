#include "subcontroller.h"

SubController::SubController(int port, QObject *parent)
    : QObject{parent}
{
    serverThread = new QThread;
    server = new MyTcpServer;
    server->moveToThread(serverThread);
    connect(this, &SubController::serverStartListen, server, &MyTcpServer::startListen);
    connect(server, &MyTcpServer::createSocket, this, &SubController::onCreateSocket);
    serverThread->start();
    emit serverStartListen(port);
}

void SubController::onCreateSocket(int hd)
{
    socketThread = new QThread;
    socket = new MyTcpSocket(1, hd);
    socket->moveToThread(socketThread);
    connect(socket, &MyTcpSocket::myReadyRead, this, &SubController::readData);
    connect(this, &SubController::sendDataToServerR, socket, &MyTcpSocket::writeSlotR);
    socketThread->start();
}

void SubController::readData(QByteArray qba)
{
    QDataStream in(&qba, QIODevice::ReadOnly);
    struct DataPackage temp;
    in >> temp.type >> temp.data;
    QDataStream iN(&temp.data, QIODevice::ReadOnly);
    qDebug() << temp.type;
    if(temp.type == COMMAND_TO_REMOTE_START_TRACE)
    {
        watcherThread = new QThread();
        watcher = new Watcher(1);
        watcher->moveToThread(watcherThread);
        connect(watcherThread, &QThread::finished, watcher, &Watcher::deleteLater);
        connect(watcher, &Watcher::destroyed, watcherThread, &QThread::deleteLater);
        connect(this, &SubController::threadQuit, watcherThread, &QThread::terminate);
        watcherThread->start();

        connect(this, &SubController::st, watcher, &Watcher::createPuppet);

        connect(watcher, &Watcher::catchSyscall,
                [=](int pid, int status, seccomp_data data, QList<QString> dargs)
                {
                    DataPackage pkg;
                    pkg.type = COMMAND_FROM_REMOTE_CATCHSYSCALL;
                    QDataStream out(&pkg.data, QIODevice::WriteOnly);
                    out << pid << status << data.nr << data.args[0] << data.args[1] << data.args[2] << data.args[3] << data.args[4] << data.args[5] << dargs;
                    emit sendDataToServerR(pkg);
                });

        connect(watcher, &Watcher::sendPeekData,
                [=](int pid, int num, long data)
                {
                    DataPackage pkg;
                    pkg.type = COMMAND_FROM_REMOTE_SENDPEEKDATA;
                    QDataStream out(&pkg.data, QIODevice::WriteOnly);
                    qint64 data64 = data;
                    out << pid << num << data64;
                    emit sendDataToServerR(pkg);
                });

        connect(watcher, &Watcher::writeLog,
                [=](QString log)
                {
                    DataPackage pkg;
                    pkg.type = COMMAND_FROM_REMOTE_WRITELOG;
                    QDataStream out(&pkg.data, QIODevice::WriteOnly);
                    out << log;
                    emit sendDataToServerR(pkg);
                });

        connect(watcher, &Watcher::sendStop,
                [=]()
                {
                    DataPackage pkg;
                    pkg.type = COMMAND_FROM_REMOTE_SENDSTOP;
                    emit sendDataToServerR(pkg);
                    watcher->endFlag = 0;
                    emit threadQuit();
                });
        connect(watcher, &Watcher::createProcTree,
                [=](int pid)
                {
                    QByteArray output;
                    QProcess p;
                    p.start("pstree", QStringList() << "-p" << "-U" << QString::number(pid));
                    p.waitForFinished();
                    output = p.readAllStandardOutput();
                    p.close();
                    QString procTree(output);

                    DataPackage pkg;
                    pkg.type = COMMAND_FROM_REMOTE_CREATEPROCTREE;
                    QDataStream out(&pkg.data, QIODevice::WriteOnly);
                    out << procTree;
                    emit sendDataToServerR(pkg);
                });
        connect(this, &SubController::startInjector, watcher, &Watcher::injector);
        connect(this, &SubController::pushEvent, watcher, &Watcher::dealNow);
        QString path;
        QStringList args;
        QJsonObject rules;
        iN >> path >> args >> rules;
        emit st(path, args, rules);
    }
    else if(temp.type == COMMAND_TO_REMOTE_STOP_BLOCKING)
    {
        int option, blockState, arg;
        iN >> option >> blockState >> arg;
        qDebug() << "stopblocking";
        watcher->nextMove = option;
        watcher->extraOption = arg;
        watcher->blockSig = blockState;
    }
    else if(temp.type == COMMAND_TO_REMOTE_RUN_SCRIPT)
    {
        QString code;
        int pid, status;
        seccomp_data data;
        QList<QString> dargs;
        iN >> code >> pid >> status >> data.nr >> data.args[0] >> data.args[1] >> data.args[2] >> data.args[3] >> data.args[4] >> data.args[5] >> data.args[6] >> dargs;
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
        command = code;
        qba.clear();
        qba = QByteArray::fromBase64(command.toLatin1());
        qba.append('\n');
        script.write(qba.data());
        script.waitForFinished();
        int exit_code = script.exitCode();

        DataPackage pkg;
        pkg.type = COMMAND_FROM_REMOTE_RESULT_OF_SCRIPT;
        QDataStream out(&pkg.data, QIODevice::WriteOnly);
        out << exit_code << pid << status << data.nr << data.args[0] << data.args[1] << data.args[2] << data.args[3] << data.args[4] << data.args[5] << dargs;
        emit sendDataToServerR(pkg);
    }
    else if(temp.type == COMMAND_TO_REMOTE_PUSH_EVENT)
    {
        qDebug() << 456;
        int pid, status, nr;
        QString arg1, arg2, arg3, arg4, arg5, arg6;
        int mask, nextMove, blockSig, extraOption;
        bool mode;
        iN >> mode >> pid >> status >> nr >> arg1 >> arg2 >> arg3 >> arg4 >> arg5 >> arg6 >> mask >> nextMove >> blockSig >> extraOption;
        emit pushEvent(mode, pid, status, nr, arg1, arg2, arg3, arg4, arg5, arg6, mask, nextMove, blockSig, extraOption);
    }
}

void SubController::stopBlocking(int option, int blockState, int arg)
{
    watcher->nextMove = option;
    watcher->extraOption = arg;
    watcher->blockSig = blockState;
}
