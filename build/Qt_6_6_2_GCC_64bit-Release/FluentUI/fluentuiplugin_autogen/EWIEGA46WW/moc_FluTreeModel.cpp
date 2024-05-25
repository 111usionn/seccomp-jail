/****************************************************************************
** Meta object code from reading C++ file 'FluTreeModel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../FluentUI/FluTreeModel.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FluTreeModel.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSFluTreeNodeENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFluTreeNodeENDCLASS = QtMocHelpers::stringData(
    "FluTreeNode",
    "depth",
    "",
    "isExpanded",
    "data",
    "hasChildren",
    "hasNextNodeByIndex",
    "index",
    "checked",
    "hideLineFooter"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFluTreeNodeENDCLASS_t {
    uint offsetsAndSizes[20];
    char stringdata0[12];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[5];
    char stringdata5[12];
    char stringdata6[19];
    char stringdata7[6];
    char stringdata8[8];
    char stringdata9[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFluTreeNodeENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFluTreeNodeENDCLASS_t qt_meta_stringdata_CLASSFluTreeNodeENDCLASS = {
    {
        QT_MOC_LITERAL(0, 11),  // "FluTreeNode"
        QT_MOC_LITERAL(12, 5),  // "depth"
        QT_MOC_LITERAL(18, 0),  // ""
        QT_MOC_LITERAL(19, 10),  // "isExpanded"
        QT_MOC_LITERAL(30, 4),  // "data"
        QT_MOC_LITERAL(35, 11),  // "hasChildren"
        QT_MOC_LITERAL(47, 18),  // "hasNextNodeByIndex"
        QT_MOC_LITERAL(66, 5),  // "index"
        QT_MOC_LITERAL(72, 7),  // "checked"
        QT_MOC_LITERAL(80, 14)   // "hideLineFooter"
    },
    "FluTreeNode",
    "depth",
    "",
    "isExpanded",
    "data",
    "hasChildren",
    "hasNextNodeByIndex",
    "index",
    "checked",
    "hideLineFooter"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFluTreeNodeENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       4,   65, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x102,    5 /* Public | MethodIsConst  */,
       3,    0,   57,    2, 0x102,    6 /* Public | MethodIsConst  */,
       4,    0,   58,    2, 0x102,    7 /* Public | MethodIsConst  */,
       5,    0,   59,    2, 0x102,    8 /* Public | MethodIsConst  */,
       6,    1,   60,    2, 0x02,    9 /* Public */,
       8,    0,   63,    2, 0x102,   11 /* Public | MethodIsConst  */,
       9,    0,   64,    2, 0x02,   12 /* Public */,

 // methods: parameters
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::QVariantMap,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Int,    7,
    QMetaType::Bool,
    QMetaType::Bool,

 // properties: name, type, flags
       4, QMetaType::QVariantMap, 0x00015401, uint(-1), 0,
       1, QMetaType::Int, 0x00015401, uint(-1), 0,
       3, QMetaType::Bool, 0x00015401, uint(-1), 0,
       8, QMetaType::Bool, 0x00015401, uint(-1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject FluTreeNode::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSFluTreeNodeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFluTreeNodeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSFluTreeNodeENDCLASS_t,
        // property 'data'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::true_type>,
        // property 'depth'
        QtPrivate::TypeAndForceComplete<int, std::true_type>,
        // property 'isExpanded'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // property 'checked'
        QtPrivate::TypeAndForceComplete<bool, std::true_type>,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FluTreeNode, std::true_type>,
        // method 'depth'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'isExpanded'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'data'
        QtPrivate::TypeAndForceComplete<QVariantMap, std::false_type>,
        // method 'hasChildren'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'hasNextNodeByIndex'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'checked'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'hideLineFooter'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>
    >,
    nullptr
} };

void FluTreeNode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FluTreeNode *>(_o);
        (void)_t;
        switch (_id) {
        case 0: { int _r = _t->depth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->isExpanded();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { QVariantMap _r = _t->data();
            if (_a[0]) *reinterpret_cast< QVariantMap*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->hasChildren();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->hasNextNodeByIndex((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->checked();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->hideLineFooter();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FluTreeNode *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = _t->data(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->depth(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->isExpanded(); break;
        case 3: *reinterpret_cast< bool*>(_v) = _t->checked(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *FluTreeNode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FluTreeNode::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFluTreeNodeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int FluTreeNode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSFluTreeModelENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSFluTreeModelENDCLASS = QtMocHelpers::stringData(
    "FluTreeModel",
    "QML.Element",
    "QML.AddedInVersion",
    "65281",
    "dataSourceSizeChanged",
    "",
    "columnSourceChanged",
    "removeRows",
    "row",
    "count",
    "insertRows",
    "QList<FluTreeNode*>",
    "data",
    "getRow",
    "setRow",
    "setData",
    "setDataSource",
    "QList<QMap<QString,QVariant>>",
    "collapse",
    "expand",
    "getNode",
    "FluTreeNode*",
    "refreshNode",
    "checkRow",
    "checked",
    "hitHasChildrenExpanded",
    "allExpand",
    "allCollapse",
    "selectionModel",
    "dataSourceSize",
    "columnSource",
    "QList<QVariantMap>"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSFluTreeModelENDCLASS_t {
    uint offsetsAndSizes[64];
    char stringdata0[13];
    char stringdata1[12];
    char stringdata2[19];
    char stringdata3[6];
    char stringdata4[22];
    char stringdata5[1];
    char stringdata6[20];
    char stringdata7[11];
    char stringdata8[4];
    char stringdata9[6];
    char stringdata10[11];
    char stringdata11[20];
    char stringdata12[5];
    char stringdata13[7];
    char stringdata14[7];
    char stringdata15[8];
    char stringdata16[14];
    char stringdata17[30];
    char stringdata18[9];
    char stringdata19[7];
    char stringdata20[8];
    char stringdata21[13];
    char stringdata22[12];
    char stringdata23[9];
    char stringdata24[8];
    char stringdata25[23];
    char stringdata26[10];
    char stringdata27[12];
    char stringdata28[15];
    char stringdata29[15];
    char stringdata30[13];
    char stringdata31[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSFluTreeModelENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSFluTreeModelENDCLASS_t qt_meta_stringdata_CLASSFluTreeModelENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "FluTreeModel"
        QT_MOC_LITERAL(13, 11),  // "QML.Element"
        QT_MOC_LITERAL(25, 18),  // "QML.AddedInVersion"
        QT_MOC_LITERAL(44, 5),  // "65281"
        QT_MOC_LITERAL(50, 21),  // "dataSourceSizeChanged"
        QT_MOC_LITERAL(72, 0),  // ""
        QT_MOC_LITERAL(73, 19),  // "columnSourceChanged"
        QT_MOC_LITERAL(93, 10),  // "removeRows"
        QT_MOC_LITERAL(104, 3),  // "row"
        QT_MOC_LITERAL(108, 5),  // "count"
        QT_MOC_LITERAL(114, 10),  // "insertRows"
        QT_MOC_LITERAL(125, 19),  // "QList<FluTreeNode*>"
        QT_MOC_LITERAL(145, 4),  // "data"
        QT_MOC_LITERAL(150, 6),  // "getRow"
        QT_MOC_LITERAL(157, 6),  // "setRow"
        QT_MOC_LITERAL(164, 7),  // "setData"
        QT_MOC_LITERAL(172, 13),  // "setDataSource"
        QT_MOC_LITERAL(186, 29),  // "QList<QMap<QString,QVariant>>"
        QT_MOC_LITERAL(216, 8),  // "collapse"
        QT_MOC_LITERAL(225, 6),  // "expand"
        QT_MOC_LITERAL(232, 7),  // "getNode"
        QT_MOC_LITERAL(240, 12),  // "FluTreeNode*"
        QT_MOC_LITERAL(253, 11),  // "refreshNode"
        QT_MOC_LITERAL(265, 8),  // "checkRow"
        QT_MOC_LITERAL(274, 7),  // "checked"
        QT_MOC_LITERAL(282, 22),  // "hitHasChildrenExpanded"
        QT_MOC_LITERAL(305, 9),  // "allExpand"
        QT_MOC_LITERAL(315, 11),  // "allCollapse"
        QT_MOC_LITERAL(327, 14),  // "selectionModel"
        QT_MOC_LITERAL(342, 14),  // "dataSourceSize"
        QT_MOC_LITERAL(357, 12),  // "columnSource"
        QT_MOC_LITERAL(370, 18)   // "QList<QVariantMap>"
    },
    "FluTreeModel",
    "QML.Element",
    "QML.AddedInVersion",
    "65281",
    "dataSourceSizeChanged",
    "",
    "columnSourceChanged",
    "removeRows",
    "row",
    "count",
    "insertRows",
    "QList<FluTreeNode*>",
    "data",
    "getRow",
    "setRow",
    "setData",
    "setDataSource",
    "QList<QMap<QString,QVariant>>",
    "collapse",
    "expand",
    "getNode",
    "FluTreeNode*",
    "refreshNode",
    "checkRow",
    "checked",
    "hitHasChildrenExpanded",
    "allExpand",
    "allCollapse",
    "selectionModel",
    "dataSourceSize",
    "columnSource",
    "QList<QVariantMap>"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSFluTreeModelENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       2,   14, // classinfo
      17,   18, // methods
       2,  169, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // classinfo: key, value
       1,    0,
       2,    3,

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  120,    5, 0x06,    3 /* Public */,
       6,    0,  121,    5, 0x06,    4 /* Public */,

 // methods: name, argc, parameters, tag, flags, initial metatype offsets
       7,    2,  122,    5, 0x02,    5 /* Public */,
      10,    2,  127,    5, 0x02,    8 /* Public */,
      13,    1,  132,    5, 0x02,   11 /* Public */,
      14,    2,  135,    5, 0x02,   13 /* Public */,
      15,    1,  140,    5, 0x02,   16 /* Public */,
      16,    1,  143,    5, 0x02,   18 /* Public */,
      18,    1,  146,    5, 0x02,   20 /* Public */,
      19,    1,  149,    5, 0x02,   22 /* Public */,
      20,    1,  152,    5, 0x02,   24 /* Public */,
      22,    1,  155,    5, 0x02,   26 /* Public */,
      23,    2,  158,    5, 0x02,   28 /* Public */,
      25,    1,  163,    5, 0x02,   31 /* Public */,
      26,    0,  166,    5, 0x02,   33 /* Public */,
      27,    0,  167,    5, 0x02,   34 /* Public */,
      28,    0,  168,    5, 0x02,   35 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    8,    9,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,    8,   12,
    QMetaType::QObjectStar, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::QVariantMap,    8,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 17,   12,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    0x80000000 | 21, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    8,   24,
    QMetaType::Bool, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QVariant,

 // properties: name, type, flags
      29, QMetaType::Int, 0x00015003, uint(0), 0,
      30, 0x80000000 | 31, 0x0001500b, uint(1), 0,

       0        // eod
};

Q_CONSTINIT const QMetaObject FluTreeModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractItemModel::staticMetaObject>(),
    qt_meta_stringdata_CLASSFluTreeModelENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSFluTreeModelENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_metaTypeArray<
        // property 'dataSourceSize'
        int,
        // property 'columnSource'
        QList<QVariantMap>,
        // Q_OBJECT / Q_GADGET
        FluTreeModel,
        // method 'dataSourceSizeChanged'
        void,
        // method 'columnSourceChanged'
        void,
        // method 'removeRows'
        void,
        int,
        int,
        // method 'insertRows'
        void,
        int,
        const QList<FluTreeNode*> &,
        // method 'getRow'
        QObject *,
        int,
        // method 'setRow'
        void,
        int,
        QVariantMap,
        // method 'setData'
        void,
        QList<FluTreeNode*>,
        // method 'setDataSource'
        void,
        QList<QMap<QString,QVariant>>,
        // method 'collapse'
        void,
        int,
        // method 'expand'
        void,
        int,
        // method 'getNode'
        FluTreeNode *,
        int,
        // method 'refreshNode'
        void,
        int,
        // method 'checkRow'
        void,
        int,
        bool,
        // method 'hitHasChildrenExpanded'
        bool,
        int,
        // method 'allExpand'
        void,
        // method 'allCollapse'
        void,
        // method 'selectionModel'
        QVariant
    >,
    nullptr
} };

void FluTreeModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FluTreeModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataSourceSizeChanged(); break;
        case 1: _t->columnSourceChanged(); break;
        case 2: _t->removeRows((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 3: _t->insertRows((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<FluTreeNode*>>>(_a[2]))); break;
        case 4: { QObject* _r = _t->getRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QObject**>(_a[0]) = std::move(_r); }  break;
        case 5: _t->setRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QVariantMap>>(_a[2]))); break;
        case 6: _t->setData((*reinterpret_cast< std::add_pointer_t<QList<FluTreeNode*>>>(_a[1]))); break;
        case 7: _t->setDataSource((*reinterpret_cast< std::add_pointer_t<QList<QMap<QString,QVariant>>>>(_a[1]))); break;
        case 8: _t->collapse((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->expand((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: { FluTreeNode* _r = _t->getNode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< FluTreeNode**>(_a[0]) = std::move(_r); }  break;
        case 11: _t->refreshNode((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->checkRow((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 13: { bool _r = _t->hitHasChildrenExpanded((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->allExpand(); break;
        case 15: _t->allCollapse(); break;
        case 16: { QVariant _r = _t->selectionModel();
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<FluTreeNode*> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<FluTreeNode*> >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QMap<QString,QVariant>> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FluTreeModel::*)();
            if (_t _q_method = &FluTreeModel::dataSourceSizeChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FluTreeModel::*)();
            if (_t _q_method = &FluTreeModel::columnSourceChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QVariantMap> >(); break;
        }
    }  else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<FluTreeModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->_dataSourceSize; break;
        case 1: *reinterpret_cast< QList<QVariantMap>*>(_v) = _t->_columnSource; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<FluTreeModel *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0:
            if (_t->_dataSourceSize != *reinterpret_cast< int*>(_v)) {
                _t->_dataSourceSize = *reinterpret_cast< int*>(_v);
                Q_EMIT _t->dataSourceSizeChanged();
            }
            break;
        case 1:
            if (_t->_columnSource != *reinterpret_cast< QList<QVariantMap>*>(_v)) {
                _t->_columnSource = *reinterpret_cast< QList<QVariantMap>*>(_v);
                Q_EMIT _t->columnSourceChanged();
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    } else if (_c == QMetaObject::BindableProperty) {
    }
}

const QMetaObject *FluTreeModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FluTreeModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSFluTreeModelENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QAbstractItemModel::qt_metacast(_clname);
}

int FluTreeModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FluTreeModel::dataSourceSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FluTreeModel::columnSourceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
