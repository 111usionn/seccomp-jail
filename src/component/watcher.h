#ifndef WATCHER_H
#define WATCHER_H

#include <QObject>
#include <signal.h>
#include "global.h"
class Watcher : public QObject
{
    Q_OBJECT
public:
    explicit Watcher(bool mode, QObject *parent = nullptr);
    int endFlag;
    int nextOperation;
    int nextMove;
    int blockSig;
    int extraOption;
    static bool seccomp_force_enable_calls(int i);
signals:
    void catchSyscall(int pid, int status, seccomp_data a, QList<QString>dargs, int trash = -1);
    void sendPeekData(int pid, int num, long data);
    void writeLog(QString log);
    void sendStop();
    void processStopped(int pid);
    void processRestarted(int pid);
    void createProcTree(int pid);
    void sendStdOutput(QString msg);

public slots:
    void createPuppet(const QString path, QStringList args, QJsonObject r) __attribute__((optimize("-O0")));
    int proactiveInterrupt(int pid);
    void proactiveRestart(int pid);
    void injector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc) __attribute__((optimize("-O0")));
    void dealNow(int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
private:
    unsigned long set_trap(int pid, int option, unsigned long addr);
    QString findSyscallName(int nr);
    user_regs_struct regs_bak;
    long code_bak, normal_code_bak;
    size_t libcAddr;
    int injectedPid;
    QQueue<syscall_info>notified_events;
    QMap<int, syscall_info>inject_events;
    QMap<int, bool>has_trap;
    QMap<int, long>orig_codes;
    QMap<int, user_regs_struct>orig_regs;
    QMap<int, bool>need_recover;
    Settings settings;
    void waiting_for_inject(int pid);
    int addroffset;
    int gethookoffset();
    int deref_offset;
    bool isSub;
    QFile *input, *output;
};

#endif // WATCHER_H
