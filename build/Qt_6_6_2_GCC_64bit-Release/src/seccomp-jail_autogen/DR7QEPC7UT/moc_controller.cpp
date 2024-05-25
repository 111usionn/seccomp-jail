/****************************************************************************
** Meta object code from reading C++ file 'controller.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/component/controller.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSControllerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSControllerENDCLASS = QtMocHelpers::stringData(
    "Controller",
    "st",
    "",
    "path",
    "args",
    "r",
    "showSyscall",
    "pid",
    "status",
    "syscall_name",
    "nr",
    "arg1",
    "arg2",
    "arg3",
    "arg4",
    "arg5",
    "arg6",
    "showPeekData",
    "num",
    "data",
    "strData",
    "writeLog",
    "syscallinfo",
    "action",
    "showLog",
    "log",
    "currentRuleChanged",
    "isTracingchanged",
    "newval",
    "qmlDrawProcTree",
    "tree",
    "startInjector",
    "argc",
    "threadQuit",
    "pushEvent",
    "mask",
    "nextMove",
    "blockSig",
    "extraOption",
    "startTrace",
    "stopTrace",
    "notifySyscall",
    "seccomp_data",
    "stopBlocking",
    "option",
    "blockState",
    "arg",
    "sendLog",
    "setRule",
    "loadRule",
    "createDefaultRule",
    "checkRule",
    "n",
    "updateRule",
    "saveCurrentRule",
    "saveAs",
    "notifyPeekData",
    "haveCurrentRule",
    "changeRuleDisplayFilter",
    "rule",
    "state",
    "getCurrentJson",
    "qmlFSN",
    "drawProcTree",
    "startInject",
    "getCommand"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSControllerENDCLASS_t {
    uint offsetsAndSizes[132];
    char stringdata0[11];
    char stringdata1[3];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[5];
    char stringdata5[2];
    char stringdata6[12];
    char stringdata7[4];
    char stringdata8[7];
    char stringdata9[13];
    char stringdata10[3];
    char stringdata11[5];
    char stringdata12[5];
    char stringdata13[5];
    char stringdata14[5];
    char stringdata15[5];
    char stringdata16[5];
    char stringdata17[13];
    char stringdata18[4];
    char stringdata19[5];
    char stringdata20[8];
    char stringdata21[9];
    char stringdata22[12];
    char stringdata23[7];
    char stringdata24[8];
    char stringdata25[4];
    char stringdata26[19];
    char stringdata27[17];
    char stringdata28[7];
    char stringdata29[16];
    char stringdata30[5];
    char stringdata31[14];
    char stringdata32[5];
    char stringdata33[11];
    char stringdata34[10];
    char stringdata35[5];
    char stringdata36[9];
    char stringdata37[9];
    char stringdata38[12];
    char stringdata39[11];
    char stringdata40[10];
    char stringdata41[14];
    char stringdata42[13];
    char stringdata43[13];
    char stringdata44[7];
    char stringdata45[11];
    char stringdata46[4];
    char stringdata47[8];
    char stringdata48[8];
    char stringdata49[9];
    char stringdata50[18];
    char stringdata51[10];
    char stringdata52[2];
    char stringdata53[11];
    char stringdata54[16];
    char stringdata55[7];
    char stringdata56[15];
    char stringdata57[16];
    char stringdata58[24];
    char stringdata59[5];
    char stringdata60[6];
    char stringdata61[15];
    char stringdata62[7];
    char stringdata63[13];
    char stringdata64[12];
    char stringdata65[11];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSControllerENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSControllerENDCLASS_t qt_meta_stringdata_CLASSControllerENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "Controller"
        QT_MOC_LITERAL(11, 2),  // "st"
        QT_MOC_LITERAL(14, 0),  // ""
        QT_MOC_LITERAL(15, 4),  // "path"
        QT_MOC_LITERAL(20, 4),  // "args"
        QT_MOC_LITERAL(25, 1),  // "r"
        QT_MOC_LITERAL(27, 11),  // "showSyscall"
        QT_MOC_LITERAL(39, 3),  // "pid"
        QT_MOC_LITERAL(43, 6),  // "status"
        QT_MOC_LITERAL(50, 12),  // "syscall_name"
        QT_MOC_LITERAL(63, 2),  // "nr"
        QT_MOC_LITERAL(66, 4),  // "arg1"
        QT_MOC_LITERAL(71, 4),  // "arg2"
        QT_MOC_LITERAL(76, 4),  // "arg3"
        QT_MOC_LITERAL(81, 4),  // "arg4"
        QT_MOC_LITERAL(86, 4),  // "arg5"
        QT_MOC_LITERAL(91, 4),  // "arg6"
        QT_MOC_LITERAL(96, 12),  // "showPeekData"
        QT_MOC_LITERAL(109, 3),  // "num"
        QT_MOC_LITERAL(113, 4),  // "data"
        QT_MOC_LITERAL(118, 7),  // "strData"
        QT_MOC_LITERAL(126, 8),  // "writeLog"
        QT_MOC_LITERAL(135, 11),  // "syscallinfo"
        QT_MOC_LITERAL(147, 6),  // "action"
        QT_MOC_LITERAL(154, 7),  // "showLog"
        QT_MOC_LITERAL(162, 3),  // "log"
        QT_MOC_LITERAL(166, 18),  // "currentRuleChanged"
        QT_MOC_LITERAL(185, 16),  // "isTracingchanged"
        QT_MOC_LITERAL(202, 6),  // "newval"
        QT_MOC_LITERAL(209, 15),  // "qmlDrawProcTree"
        QT_MOC_LITERAL(225, 4),  // "tree"
        QT_MOC_LITERAL(230, 13),  // "startInjector"
        QT_MOC_LITERAL(244, 4),  // "argc"
        QT_MOC_LITERAL(249, 10),  // "threadQuit"
        QT_MOC_LITERAL(260, 9),  // "pushEvent"
        QT_MOC_LITERAL(270, 4),  // "mask"
        QT_MOC_LITERAL(275, 8),  // "nextMove"
        QT_MOC_LITERAL(284, 8),  // "blockSig"
        QT_MOC_LITERAL(293, 11),  // "extraOption"
        QT_MOC_LITERAL(305, 10),  // "startTrace"
        QT_MOC_LITERAL(316, 9),  // "stopTrace"
        QT_MOC_LITERAL(326, 13),  // "notifySyscall"
        QT_MOC_LITERAL(340, 12),  // "seccomp_data"
        QT_MOC_LITERAL(353, 12),  // "stopBlocking"
        QT_MOC_LITERAL(366, 6),  // "option"
        QT_MOC_LITERAL(373, 10),  // "blockState"
        QT_MOC_LITERAL(384, 3),  // "arg"
        QT_MOC_LITERAL(388, 7),  // "sendLog"
        QT_MOC_LITERAL(396, 7),  // "setRule"
        QT_MOC_LITERAL(404, 8),  // "loadRule"
        QT_MOC_LITERAL(413, 17),  // "createDefaultRule"
        QT_MOC_LITERAL(431, 9),  // "checkRule"
        QT_MOC_LITERAL(441, 1),  // "n"
        QT_MOC_LITERAL(443, 10),  // "updateRule"
        QT_MOC_LITERAL(454, 15),  // "saveCurrentRule"
        QT_MOC_LITERAL(470, 6),  // "saveAs"
        QT_MOC_LITERAL(477, 14),  // "notifyPeekData"
        QT_MOC_LITERAL(492, 15),  // "haveCurrentRule"
        QT_MOC_LITERAL(508, 23),  // "changeRuleDisplayFilter"
        QT_MOC_LITERAL(532, 4),  // "rule"
        QT_MOC_LITERAL(537, 5),  // "state"
        QT_MOC_LITERAL(543, 14),  // "getCurrentJson"
        QT_MOC_LITERAL(558, 6),  // "qmlFSN"
        QT_MOC_LITERAL(565, 12),  // "drawProcTree"
        QT_MOC_LITERAL(578, 11),  // "startInject"
        QT_MOC_LITERAL(590, 10)   // "getCommand"
    },
    "Controller",
    "st",
    "",
    "path",
    "args",
    "r",
    "showSyscall",
    "pid",
    "status",
    "syscall_name",
    "nr",
    "arg1",
    "arg2",
    "arg3",
    "arg4",
    "arg5",
    "arg6",
    "showPeekData",
    "num",
    "data",
    "strData",
    "writeLog",
    "syscallinfo",
    "action",
    "showLog",
    "log",
    "currentRuleChanged",
    "isTracingchanged",
    "newval",
    "qmlDrawProcTree",
    "tree",
    "startInjector",
    "argc",
    "threadQuit",
    "pushEvent",
    "mask",
    "nextMove",
    "blockSig",
    "extraOption",
    "startTrace",
    "stopTrace",
    "notifySyscall",
    "seccomp_data",
    "stopBlocking",
    "option",
    "blockState",
    "arg",
    "sendLog",
    "setRule",
    "loadRule",
    "createDefaultRule",
    "checkRule",
    "n",
    "updateRule",
    "saveCurrentRule",
    "saveAs",
    "notifyPeekData",
    "haveCurrentRule",
    "changeRuleDisplayFilter",
    "rule",
    "state",
    "getCurrentJson",
    "qmlFSN",
    "drawProcTree",
    "startInject",
    "getCommand"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSControllerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      31,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,  200,    2, 0x06,    1 /* Public */,
       6,   10,  207,    2, 0x06,    5 /* Public */,
      17,    4,  228,    2, 0x06,   16 /* Public */,
      21,    9,  237,    2, 0x06,   21 /* Public */,
      24,    1,  256,    2, 0x06,   31 /* Public */,
      26,    0,  259,    2, 0x06,   33 /* Public */,
      27,    1,  260,    2, 0x06,   34 /* Public */,
      29,    1,  263,    2, 0x06,   36 /* Public */,
      31,    9,  266,    2, 0x06,   38 /* Public */,
      33,    0,  285,    2, 0x06,   48 /* Public */,
      34,   13,  286,    2, 0x06,   49 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      39,    2,  313,    2, 0x0a,   63 /* Public */,
      40,    0,  318,    2, 0x0a,   66 /* Public */,
      41,    3,  319,    2, 0x0a,   67 /* Public */,
      43,    3,  326,    2, 0x0a,   71 /* Public */,
      47,    1,  333,    2, 0x0a,   75 /* Public */,
      48,    1,  336,    2, 0x0a,   77 /* Public */,
      49,    1,  339,    2, 0x0a,   79 /* Public */,
      50,    1,  342,    2, 0x0a,   81 /* Public */,
      51,    1,  345,    2, 0x0a,   83 /* Public */,
      53,    2,  348,    2, 0x0a,   85 /* Public */,
      54,    1,  353,    2, 0x0a,   88 /* Public */,
      54,    0,  356,    2, 0x2a,   90 /* Public | MethodCloned */,
      56,    3,  357,    2, 0x0a,   91 /* Public */,
      57,    0,  364,    2, 0x0a,   95 /* Public */,
      58,    2,  365,    2, 0x0a,   96 /* Public */,
      61,    0,  370,    2, 0x0a,   99 /* Public */,
      62,    1,  371,    2, 0x0a,  100 /* Public */,
      63,    1,  374,    2, 0x0a,  102 /* Public */,
      64,    9,  377,    2, 0x0a,  104 /* Public */,
      65,   13,  396,    2, 0x0a,  114 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::QJsonObject,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,   10,   11,   12,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long, QMetaType::QString,    7,   18,   19,   20,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,    7,   22,   11,   12,   13,   14,   15,   16,   23,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   28,
    QMetaType::Void, QMetaType::QString,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Int,    7,   10,   11,   12,   13,   14,   15,   16,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,   10,   11,   12,   13,   14,   15,   16,   35,   36,   37,   38,

 // slots: parameters
    QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 42,    7,    8,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   44,   45,   46,
    QMetaType::Void, QMetaType::QString,   25,
    QMetaType::Int, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Int, QMetaType::Int,   52,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   52,   44,
    QMetaType::Void, QMetaType::QString,   55,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long,    7,   18,   19,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   59,   60,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Int,    7,   10,   11,   12,   13,   14,   15,   16,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    7,    8,   10,   11,   12,   13,   14,   15,   16,   35,   36,   37,   38,

       0        // eod
};

Q_CONSTINIT const QMetaObject Controller::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSControllerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSControllerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSControllerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Controller, std::true_type>,
        // method 'st'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        QtPrivate::TypeAndForceComplete<QJsonObject, std::false_type>,
        // method 'showSyscall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'showPeekData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'writeLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'showLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'currentRuleChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'isTracingchanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'qmlDrawProcTree'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'startInjector'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'threadQuit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'pushEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'startTrace'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'stopTrace'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'notifySyscall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<seccomp_data, std::false_type>,
        // method 'stopBlocking'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'sendLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'setRule'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'loadRule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'createDefaultRule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'checkRule'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateRule'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'saveCurrentRule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'saveCurrentRule'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'notifyPeekData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        // method 'haveCurrentRule'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'changeRuleDisplayFilter'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'getCurrentJson'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'qmlFSN'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'drawProcTree'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'startInject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'getCommand'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void Controller::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Controller *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->st((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[3]))); break;
        case 1: _t->showSyscall((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[10]))); break;
        case 2: _t->showPeekData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4]))); break;
        case 3: _t->writeLog((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        case 4: _t->showLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->currentRuleChanged(); break;
        case 6: _t->isTracingchanged((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->qmlDrawProcTree((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->startInjector((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        case 9: _t->threadQuit(); break;
        case 10: _t->pushEvent((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[12])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[13]))); break;
        case 11: { int _r = _t->startTrace((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->stopTrace(); break;
        case 13: _t->notifySyscall((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<seccomp_data>>(_a[3]))); break;
        case 14: _t->stopBlocking((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 15: _t->sendLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: { int _r = _t->setRule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 17: _t->loadRule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->createDefaultRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 19: { int _r = _t->checkRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->updateRule((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->saveCurrentRule((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 22: _t->saveCurrentRule(); break;
        case 23: _t->notifyPeekData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3]))); break;
        case 24: { int _r = _t->haveCurrentRule();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->changeRuleDisplayFilter((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 26: { QString _r = _t->getCurrentJson();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 27: { QString _r = _t->qmlFSN((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->drawProcTree((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 29: _t->startInject((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        case 30: _t->getCommand((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[12])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[13]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Controller::*)(QString , QStringList , QJsonObject );
            if (_t _q_method = &Controller::st; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Controller::*)(int , int , QString , int , QString , QString , QString , QString , QString , QString );
            if (_t _q_method = &Controller::showSyscall; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Controller::*)(int , int , long , QString );
            if (_t _q_method = &Controller::showPeekData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Controller::*)(int , QString , QString , QString , QString , QString , QString , QString , int );
            if (_t _q_method = &Controller::writeLog; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Controller::*)(QString );
            if (_t _q_method = &Controller::showLog; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Controller::*)();
            if (_t _q_method = &Controller::currentRuleChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Controller::*)(bool );
            if (_t _q_method = &Controller::isTracingchanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Controller::*)(QString );
            if (_t _q_method = &Controller::qmlDrawProcTree; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Controller::*)(int , int , long , long , long , long , long , long , int );
            if (_t _q_method = &Controller::startInjector; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Controller::*)();
            if (_t _q_method = &Controller::threadQuit; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (Controller::*)(int , int , int , QString , QString , QString , QString , QString , QString , int , int , int , int );
            if (_t _q_method = &Controller::pushEvent; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject *Controller::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Controller::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSControllerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Controller::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 31)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 31;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 31)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 31;
    }
    return _id;
}

// SIGNAL 0
void Controller::st(QString _t1, QStringList _t2, QJsonObject _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Controller::showSyscall(int _t1, int _t2, QString _t3, int _t4, QString _t5, QString _t6, QString _t7, QString _t8, QString _t9, QString _t10)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t10))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Controller::showPeekData(int _t1, int _t2, long _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Controller::writeLog(int _t1, QString _t2, QString _t3, QString _t4, QString _t5, QString _t6, QString _t7, QString _t8, int _t9)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Controller::showLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Controller::currentRuleChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Controller::isTracingchanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Controller::qmlDrawProcTree(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void Controller::startInjector(int _t1, int _t2, long _t3, long _t4, long _t5, long _t6, long _t7, long _t8, int _t9)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void Controller::threadQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void Controller::pushEvent(int _t1, int _t2, int _t3, QString _t4, QString _t5, QString _t6, QString _t7, QString _t8, QString _t9, int _t10, int _t11, int _t12, int _t13)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t8))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t9))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t10))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t11))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t12))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t13))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
