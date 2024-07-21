#ifndef SUBCONTROLLER_H
#define SUBCONTROLLER_H

#include <QObject>
#include "mytcpserver.h"
#include "mytcpsocket.h"
#include "watcher.h"
class SubController : public QObject
{
    Q_OBJECT
public:
    explicit SubController(int port, QObject *parent = nullptr);

signals:
    void serverStartListen(int port);
    void threadQuit();
    void st(QString path, QStringList args, QJsonObject r);
    void sendDataToServerR(DataPackage pkg);
    void startInjector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void pushEvent(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
public slots:
    void onCreateSocket(int hd);
    void readData(QByteArray qba);

private:
    QThread* serverThread, *socketThread, *watcherThread;
    MyTcpServer* server;
    MyTcpSocket* socket;
    Watcher* watcher;
    void stopBlocking(int option, int blockState, int arg);
};

#endif // SUBCONTROLLER_H
