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
    void showPeekData(int pid, int num, long data, QString strData);
    void writeLog(int pid, QString syscallinfo, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int action);
    void showLog(QString log);
    void currentRuleChanged();
    void isTracingchanged(bool newval);
    void qmlDrawProcTree(QString tree);
    void startInjector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void threadQuit();
    void pushEvent(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
public slots:
    int startTrace(QString path, QString args);
    void stopTrace();
    void notifySyscall(int pid, int status, seccomp_data data, QList<QString> dargs);
    //void stopBlocking(int option, int blockState);
    void stopBlocking(int option, int blockState, int arg);
    void sendLog(QString log);
    int setRule(QString path);
    void loadRule(QString path);
    void createDefaultRule(int option);
    QJsonArray checkRule(int n);
    int updateRule(int n, int option, QString script_base64 = "");
    void saveCurrentRule(QString saveAs = "");
    void notifyPeekData(int pid, int num, long data);
    int haveCurrentRule();
    void changeRuleDisplayFilter(int rule, bool state);
    QString getCurrentJson();
    QString qmlFSN(int nr);
    void drawProcTree(int pid);
    void startInject(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void getCommand(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
private:
    QThread* thread;
    Watcher* watcher;
    bool isTracing;
    int rules[500];
    QJsonObject currentRules;
    bool finishmunmap;
    QString currentRulePath;
    bool ruleDisplayFilter[5];
};

#endif // CONTROLLER_H
