#ifndef GLOBAL_H
#define GLOBAL_H

#endif // GLOBAL_H

#define JAIL_SYS_CALL_PASS 0
#define JAIL_SYS_CALL_ABORT 1
#define JAIL_SYS_CALL_NOTIFY 2
#define JAIL_SYS_CALL_PASS_FOREVER 3
#define JAIL_SYS_CALL_ABORT_FOREVER 4
#define SYSMSG_STOP_BLOCKING 0
#define SYSMSG_KEEP_BLOCKING 1
#define SYSMSG_DEAL_LATER 2
#define SYSMSG_PEEK_ADDR 4

#include <QDebug>
#include <QEventLoop>
#include <seccomp.h>
#include <QString>
#include <QQueue>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/reg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>
#include <QProcess>
#include <QThread>
#include <unistd.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <sys/user.h>

struct syscall_info{
    int pid;
    int status;
    int nr;
    long args[6];
    int mask;
    int nextMove;
    int blockSig;
    int extraOption;
};
struct Settings {
    bool enableLDPRELOAD;
};
