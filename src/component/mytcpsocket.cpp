#include "mytcpsocket.h"

MyTcpSocket::MyTcpSocket(int mode, qintptr handle, QObject *parent) : QTcpSocket(parent)
{
    connect(this, &MyTcpSocket::readyRead, this, &MyTcpSocket::readyReadSlot);
    connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::deleteLater);
    Mode = mode;
    expectHeader = 1;
    if(mode)//0:client 1:server
    {
        setSocketDescriptor(handle);
        connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::serverDisconnected);
    }
    else
    {
        connect(this, &MyTcpSocket::disconnected, this, &MyTcpSocket::clientDisconnected);
    }
}

void MyTcpSocket::serverDisconnected()
{
    close();
}

void MyTcpSocket::clientDisconnected()
{
    close();
}

void MyTcpSocket::readyReadSlot()
{
    char tdata[10240];
    while(bytesAvailable() > 0)
    {
        QDataStream in(this);
        if(expectHeader)
        {
            if(bytesAvailable() < sizeof(quint32))break;
            expectHeader = 0;
            in >> header;
        }
        if(bytesAvailable() < header)break;
        QByteArray package;
        in.readRawData(tdata, header);
        QDataStream out(&package, QIODevice::WriteOnly);
        out.writeRawData(tdata, header);
        expectHeader = 1;
        emit myReadyRead(package);
    }
}

void MyTcpSocket::writeSlotR(DataPackage pkg)
{
    QByteArray header, body;
    QDataStream out_header(&header, QIODevice::WriteOnly);
    QDataStream out_body(&body, QIODevice::WriteOnly);
    out_body << pkg.type << pkg.data;
    out_header << (quint32)body.size();
    header.append(body);
    write(header);
}
