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

    /*entry*/
    int nextMove;
    int blockSig;
    int extraOption;

    /*exit*/
    int blockSig_exit;
    int nextMove_exit;
    long newReval;

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
    void handleSyscallExit(int pid, int nr, long syscallreval, int trash = -1);
    void send_user_movement_observer_pid(int pid);
public slots:
    void createPuppet(const QString path, QStringList args, QJsonObject r, bool all_stop_mode_enabled);
    int proactiveInterrupt(int pid);
    void proactiveRestart(int pid);
    void injector(int pid, int nr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6, int argc);
    void dealNow(bool mode, int pid, int status, int nr, QString arg1, QString arg2, QString arg3, QString arg4, QString arg5, QString arg6, int mask, int nextMove, int blockSig, int extraOption);
private:
    int child_pid;
    unsigned long set_trap(int pid, int option, unsigned long addr);
    QString findSyscallName(int nr);
    QString generateAction(int nm, int eo);
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
    enum {
        NON_STOP,
        ALL_STOP
    }STOP_MODE;
    QSet<int>survived_procs;

    //ALL_STOP ONLY
    void StopAllProcess(int curr_pid);
    void ContinueAllProcess();
    void ContinueAllProcessToExit();
    void RestartAllProcess();
    QSet<int>procs_need_solve_sigstop;
    bool procs_stopped;
    QMap<int, int>Pending_Procs, need_inject_signal;
    QSet<int>need_restart, need_suppress_sigstop, need_user_confirmation, need_ptrace_listen;
    bool func_selecter;
};

#endif // WATCHER_H
