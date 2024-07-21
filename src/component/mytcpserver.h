#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QtNetwork>
#include "global.h"

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr handle) override;

signals:
    void createSocket(int hd);

public slots:
    void startListen(int port);
    void stopListen();
};

#endif // MYTCPSERVER_H
