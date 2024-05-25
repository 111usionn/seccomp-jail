/****************************************************************************
** Meta object code from reading C++ file 'watcher.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/component/watcher.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'watcher.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSWatcherENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSWatcherENDCLASS = QtMocHelpers::stringData(
    "Watcher",
    "catchSyscall",
    "",
    "pid",
    "status",
    "seccomp_data",
    "a",
    "sendPeekData",
    "num",
    "data",
    "writeLog",
    "log",
    "sendStop",
    "processStopped",
    "processRestarted",
    "createProcTree",
    "createPuppet",
    "path",
    "args",
    "r",
    "proactiveInterrupt",
    "proactiveRestart",
    "injector",
    "nr",
    "arg1",
    "arg2",
    "arg3",
    "arg4",
    "arg5",
    "arg6",
    "argc",
    "dealNow",
    "mask",
    "nextMove",
    "blockSig",
    "extraOption"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSWatcherENDCLASS_t {
    uint offsetsAndSizes[72];
    char stringdata0[8];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[7];
    char stringdata5[13];
    char stringdata6[2];
    char stringdata7[13];
    char stringdata8[4];
    char stringdata9[5];
    char stringdata10[9];
    char stringdata11[4];
    char stringdata12[9];
    char stringdata13[15];
    char stringdata14[17];
    char stringdata15[15];
    char stringdata16[13];
    char stringdata17[5];
    char stringdata18[5];
    char stringdata19[2];
    char stringdata20[19];
    char stringdata21[17];
    char stringdata22[9];
    char stringdata23[3];
    char stringdata24[5];
    char stringdata25[5];
    char stringdata26[5];
    char stringdata27[5];
    char stringdata28[5];
    char stringdata29[5];
    char stringdata30[5];
    char stringdata31[8];
    char stringdata32[5];
    char stringdata33[9];
    char stringdata34[9];
    char stringdata35[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSWatcherENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSWatcherENDCLASS_t qt_meta_stringdata_CLASSWatcherENDCLASS = {
    {
        QT_MOC_LITERAL(0, 7),  // "Watcher"
        QT_MOC_LITERAL(8, 12),  // "catchSyscall"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 3),  // "pid"
        QT_MOC_LITERAL(26, 6),  // "status"
        QT_MOC_LITERAL(33, 12),  // "seccomp_data"
        QT_MOC_LITERAL(46, 1),  // "a"
        QT_MOC_LITERAL(48, 12),  // "sendPeekData"
        QT_MOC_LITERAL(61, 3),  // "num"
        QT_MOC_LITERAL(65, 4),  // "data"
        QT_MOC_LITERAL(70, 8),  // "writeLog"
        QT_MOC_LITERAL(79, 3),  // "log"
        QT_MOC_LITERAL(83, 8),  // "sendStop"
        QT_MOC_LITERAL(92, 14),  // "processStopped"
        QT_MOC_LITERAL(107, 16),  // "processRestarted"
        QT_MOC_LITERAL(124, 14),  // "createProcTree"
        QT_MOC_LITERAL(139, 12),  // "createPuppet"
        QT_MOC_LITERAL(152, 4),  // "path"
        QT_MOC_LITERAL(157, 4),  // "args"
        QT_MOC_LITERAL(162, 1),  // "r"
        QT_MOC_LITERAL(164, 18),  // "proactiveInterrupt"
        QT_MOC_LITERAL(183, 16),  // "proactiveRestart"
        QT_MOC_LITERAL(200, 8),  // "injector"
        QT_MOC_LITERAL(209, 2),  // "nr"
        QT_MOC_LITERAL(212, 4),  // "arg1"
        QT_MOC_LITERAL(217, 4),  // "arg2"
        QT_MOC_LITERAL(222, 4),  // "arg3"
        QT_MOC_LITERAL(227, 4),  // "arg4"
        QT_MOC_LITERAL(232, 4),  // "arg5"
        QT_MOC_LITERAL(237, 4),  // "arg6"
        QT_MOC_LITERAL(242, 4),  // "argc"
        QT_MOC_LITERAL(247, 7),  // "dealNow"
        QT_MOC_LITERAL(255, 4),  // "mask"
        QT_MOC_LITERAL(260, 8),  // "nextMove"
        QT_MOC_LITERAL(269, 8),  // "blockSig"
        QT_MOC_LITERAL(278, 11)   // "extraOption"
    },
    "Watcher",
    "catchSyscall",
    "",
    "pid",
    "status",
    "seccomp_data",
    "a",
    "sendPeekData",
    "num",
    "data",
    "writeLog",
    "log",
    "sendStop",
    "processStopped",
    "processRestarted",
    "createProcTree",
    "createPuppet",
    "path",
    "args",
    "r",
    "proactiveInterrupt",
    "proactiveRestart",
    "injector",
    "nr",
    "arg1",
    "arg2",
    "arg3",
    "arg4",
    "arg5",
    "arg6",
    "argc",
    "dealNow",
    "mask",
    "nextMove",
    "blockSig",
    "extraOption"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSWatcherENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   86,    2, 0x06,    1 /* Public */,
       7,    3,   93,    2, 0x06,    5 /* Public */,
      10,    1,  100,    2, 0x06,    9 /* Public */,
      12,    0,  103,    2, 0x06,   11 /* Public */,
      13,    1,  104,    2, 0x06,   12 /* Public */,
      14,    1,  107,    2, 0x06,   14 /* Public */,
      15,    1,  110,    2, 0x06,   16 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    3,  113,    2, 0x0a,   18 /* Public */,
      20,    1,  120,    2, 0x0a,   22 /* Public */,
      21,    1,  123,    2, 0x0a,   24 /* Public */,
      22,    9,  126,    2, 0x0a,   26 /* Public */,
      31,   13,  145,    2, 0x0a,   36 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long,    3,    8,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::QJsonObject,   17,   18,   19,
    QMetaType::Int, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Long, QMetaType::Int,    3,   23,   24,   25,   26,   27,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,   23,   24,   25,   26,   27,   28,   29,   32,   33,   34,   35,

       0        // eod
};

Q_CONSTINIT const QMetaObject Watcher::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSWatcherENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSWatcherENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSWatcherENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Watcher, std::true_type>,
        // method 'catchSyscall'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<seccomp_data, std::false_type>,
        // method 'sendPeekData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<long, std::false_type>,
        // method 'writeLog'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'sendStop'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'processStopped'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'processRestarted'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'createProcTree'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'createPuppet'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList, std::false_type>,
        QtPrivate::TypeAndForceComplete<QJsonObject, std::false_type>,
        // method 'proactiveInterrupt'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'proactiveRestart'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'injector'
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
        // method 'dealNow'
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

void Watcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Watcher *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->catchSyscall((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<seccomp_data>>(_a[3]))); break;
        case 1: _t->sendPeekData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3]))); break;
        case 2: _t->writeLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sendStop(); break;
        case 4: _t->processStopped((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->processRestarted((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->createProcTree((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->createPuppet((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[3]))); break;
        case 8: { int _r = _t->proactiveInterrupt((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->proactiveRestart((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->injector((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<long>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[9]))); break;
        case 11: _t->dealNow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[7])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[9])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[10])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[11])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[12])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[13]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Watcher::*)(int , int , seccomp_data );
            if (_t _q_method = &Watcher::catchSyscall; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Watcher::*)(int , int , long );
            if (_t _q_method = &Watcher::sendPeekData; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Watcher::*)(QString );
            if (_t _q_method = &Watcher::writeLog; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Watcher::*)();
            if (_t _q_method = &Watcher::sendStop; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Watcher::*)(int );
            if (_t _q_method = &Watcher::processStopped; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Watcher::*)(int );
            if (_t _q_method = &Watcher::processRestarted; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Watcher::*)(int );
            if (_t _q_method = &Watcher::createProcTree; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *Watcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Watcher::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSWatcherENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Watcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Watcher::catchSyscall(int _t1, int _t2, seccomp_data _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Watcher::sendPeekData(int _t1, int _t2, long _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Watcher::writeLog(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Watcher::sendStop()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Watcher::processStopped(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Watcher::processRestarted(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Watcher::createProcTree(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
