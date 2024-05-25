/****************************************************************************
** Meta object code from reading C++ file 'CircularReveal.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../src/component/CircularReveal.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CircularReveal.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSCircularRevealENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSCircularRevealENDCLASS = QtMocHelpers::stringData(
    "CircularReveal",
    "targetChanged",
    "",
    "radiusChanged",
    "imageChanged",
    "animationFinished",
    "handleGrabResult",
    "start",
    "w",
    "h",
    "center",
    "radius",
    "target",
    "QQuickItem*"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSCircularRevealENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[15];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[13];
    char stringdata5[18];
    char stringdata6[17];
    char stringdata7[6];
    char stringdata8[2];
    char stringdata9[2];
    char stringdata10[7];
    char stringdata11[7];
    char stringdata12[7];
    char stringdata13[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSCircularRevealENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSCircularRevealENDCLASS_t qt_meta_stringdata_CLASSCircularRevealENDCLASS = {
    {
        QT_MOC_LITERAL(0, 14),  // "CircularReveal"
        QT_MOC_LITERAL(15, 13),  // "targetChanged"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 13),  // "radiusChanged"
        QT_MOC_LITERAL(44, 12),  // "imageChanged"
        QT_MOC_LITERAL(57, 17),  // "animationFinished"
        QT_MOC_LITERAL(75, 16),  // "handleGrabResult"
        QT_MOC_LITERAL(92, 5),  // "start"
        QT_MOC_LITERAL(98, 1),  // "w"
        QT_MOC_LITERAL(100, 1),  // "h"
        QT_MOC_LITERAL(102, 6),  // "center"
        QT_MOC_LITERAL(109, 6),  // "radius"
        QT_MOC_LITERAL(116, 6),  // "target"
        QT_MOC_LITERAL(123, 11)   // "QQuickItem*"
    },
    "CircularReveal",
    "targetChanged",
    "",
    "radiusChanged",
    "imageChanged",
    "animationFinished",
    "handleGrabResult",
    "start",
    "w",
    "h",
    "center",
    "radius",
    "target",
    "QQuickItem*"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSCircularRevealENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       2,   64, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    3 /* Public */,
       3,    0,   51,    2, 0x06,    4 /* Public */,
       4,    0,   52,    2, 0x06,    5 /* Public */,
       5,    0,   53,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   54,    2, 0x0a,    7 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       7,    4,   55,    2, 0x02,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QPoint, QMetaType::Int,    8,    9,   10,   11,

 // properties: name, type, flags
      12, 0x80000000 | 13, 0x0001500b, uint(0), 0,
      11, QMetaType::Int, 0x00015003, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject CircularReveal::staticMetaObject = { {
    QMetaObject::SuperData::link<QQuickPaintedItem::staticMetaObject>(),
    qt_meta_stringdata_CLASSCircularRevealENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSCircularRevealENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSCircularRevealENDCLASS_t,
        // property 'target'
        QtPrivate::TypeAndForceComplete<QQuickItem*, std::true_type>,
        // property 'radius'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<CircularReveal, std::true_type>,
        // method 'targetChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'radiusChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'imageChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'animationFinished'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'handleGrabResult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'start'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void CircularReveal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CircularReveal *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->targetChanged(); break;
        case 1: _t->radiusChanged(); break;
        case 2: _t->imageChanged(); break;
        case 3: _t->animationFinished(); break;
        case 4: _t->handleGrabResult(); break;
        case 5: _t->start((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CircularReveal::*)();
            if (_t _q_method = &CircularReveal::targetChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CircularReveal::*)();
            if (_t _q_method = &CircularReveal::radiusChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CircularReveal::*)();
            if (_t _q_method = &CircularReveal::imageChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CircularReveal::*)();
            if (_t _q_method = &CircularReveal::animationFinished; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QQuickItem* >(); break;
        }
    }  else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CircularReveal *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QQuickItem**>(_v) = _t->_target; break;
        case 1: *reinterpret_cast< int*>(_v) = _t->_radius; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<CircularReveal *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->_target != *reinterpret_cast< QQuickItem**>(_v)) {
                _t->_target = *reinterpret_cast< QQuickItem**>(_v);
                Q_EMIT _t->targetChanged();
            }
            break;
        case 1:
            if (_t->_radius != *reinterpret_cast< int*>(_v)) {
                _t->_radius = *reinterpret_cast< int*>(_v);
                Q_EMIT _t->radiusChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *CircularReveal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CircularReveal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSCircularRevealENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QQuickPaintedItem::qt_metacast(_clname);
}

int CircularReveal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QQuickPaintedItem::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CircularReveal::targetChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CircularReveal::radiusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CircularReveal::imageChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void CircularReveal::animationFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
