#include <QCoreApplication>
#include "component/subcontroller.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //argv[1]:port
    qDebug() << "start listen on port:" << argv[1];
    SubController subController(QString(argv[1]).toInt());
    return a.exec();
}
