#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H

#include <QObject>
#include <QtNetwork>
#include "global.h"

class MyTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpSocket(int mode, qintptr handle, QObject *parent = nullptr);
    int num;
signals:
    void getNum(int n);
    void myReadyRead(QByteArray qba);

public slots:
    void readyReadSlot();
    void writeSlotR(DataPackage pkg);
protected slots:
    void serverDisconnected();
    void clientDisconnected();

private:
    QByteArray temp;
    quint32 header;
    int Mode;
    bool expectHeader;
};

#endif // MYTCPSOCKET_H
