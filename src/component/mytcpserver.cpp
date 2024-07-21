#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer(parent)
{
}

void MyTcpServer::incomingConnection(qintptr handle)
{
    emit createSocket(handle);
}

void MyTcpServer::startListen(int port)
{
    listen(QHostAddress::Any, port);
}

void MyTcpServer::stopListen()
{
    close();
}
