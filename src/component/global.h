#ifndef GLOBAL_H
#define GLOBAL_H

#endif // GLOBAL_H

#define JAIL_SYS_CALL_PASS 0
#define JAIL_SYS_CALL_ABORT 1
#define JAIL_SYS_CALL_NOTIFY 2
#define JAIL_SYS_CALL_PASS_FOREVER 3
#define JAIL_SYS_CALL_ABORT_FOREVER 4
#define JAIL_SYS_CALL_CUSTOM 5

#define JAIL_SYS_CALL_EXIT_DEFAULT 0
#define JAIL_SYS_CALL_EXIT_CHANGE 1
#define JAIL_SYS_CALL_EXIT_NOTIFY 2

#define SYSMSG_STOP_BLOCKING 0
#define SYSMSG_KEEP_BLOCKING 1
#define SYSMSG_DEAL_LATER 2
#define SYSMSG_PEEK_ADDR 4
#define SYSMSG_KEEP_ORIG_REVAL 5
#define SYSMSG_CHANGE_REVAL 6

#define COMMAND_TO_REMOTE_START_TRACE 0
#define COMMAND_TO_REMOTE_STOP_BLOCKING 1
#define COMMAND_TO_REMOTE_RUN_SCRIPT 2
#define COMMAND_TO_REMOTE_PUSH_EVENT 3
#define COMMAND_TO_REMOTE_STOP_BLOCKING_EXIT 4

#define COMMAND_FROM_REMOTE_CATCHSYSCALL 0
#define COMMAND_FROM_REMOTE_SENDPEEKDATA 1
#define COMMAND_FROM_REMOTE_WRITELOG 2
#define COMMAND_FROM_REMOTE_SENDSTOP 3
#define COMMAND_FROM_REMOTE_CREATEPROCTREE 4
#define COMMAND_FROM_REMOTE_RESULT_OF_SCRIPT 5
#define COMMAND_FROM_REMOTE_HANDLESYSCALLEXIT 6

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
#include <QJsonArray>
#include <QCoreApplication>
#include <QDateTime>
#include <QFile>
#include <sys/user.h>
#include "mytcpserver.h"
#include "mytcpsocket.h"

#ifndef STRUCTS
#define STRUCTS
struct syscall_info{
    enum {
        ENTRY,
        EXIT
    }mode;
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
struct DataPackage {
    int type;
    QByteArray data;
};
#endif
