#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <cstring>
#include "watcher.h"
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    static QString findSyscallName(int nr);

signals:
    void st(QString path, QStringList args, QJsonObject r);
    void showSyscall(int pid, int status, QString syscall_name, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6);
    void showSyscallExit(int pid, QString syscall_name, int nr, QString reval);
    void showPeekData(int pid, int num, long data, QString strData);
    void writeLog(int pid, QString syscallinfo, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int action);
    void showLog(QString log);
    void currentRuleChanged();
    void isTracingchanged(bool newval);
    void qmlDrawProcTree(QString tree);
    void startInjector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void threadQuit();
    void pushEvent(bool mode, int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
    void sendDataToServerR(DataPackage pkg);
public slots:
    int startTrace(QString path, QString args);
    void readDataFromSocket(QByteArray qba);
    void stopTrace();
    void notifySyscall(int pid, int status, seccomp_data data, QList<QString> dargs, int remote_script_resp = -1);
    //void stopBlocking(int option, int blockState);
    void sendLog(QString log);
    int setRule(QString path);
    void loadRule(QString path);
    void createDefaultRule(int option);
    QJsonArray checkRule(int n);
    int updateRule(int n, int option, QString script_base64 = "");
    int updateExitRule(int n, int option, long newReval = 0);
    void saveCurrentRule(QString saveAs = "");
    void notifyPeekData(int pid, int num, long data);
    int haveCurrentRule();
    void changeRuleDisplayFilter(int rule, bool state);
    QString getCurrentJson();
    QString qmlFSN(int nr);
    void drawProcTree(int pid);
    void startInject(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void getCommand(bool mode, int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
    void isRemote_setter(bool val);
    void notifySyscallExit(int pid, int nr, long syscallreval, int remote_script_resp = -1);

private:
    QThread* thread;
    Watcher* watcher;
    bool isTracing;
    int rules[500];
    QJsonObject currentRules;
    bool finishmunmap;
    QString currentRulePath;
    bool ruleDisplayFilter[5];
    MyTcpSocket* myTcpSocket;
    bool isRemote;
    void stopBlocking(bool mode, int option, int blockState, int arg);
    void stopBlockingExit(bool mode, int option, int blockState, long newval = 0);
};

#endif // CONTROLLER_H
