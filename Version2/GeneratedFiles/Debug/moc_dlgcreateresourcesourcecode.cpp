/****************************************************************************
** Meta object code from reading C++ file 'dlgcreateresourcesourcecode.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dlg/dlgcreateresourcesourcecode.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlgcreateresourcesourcecode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DlgCreateResourceSourceCode_t {
    QByteArrayData data[11];
    char stringdata[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgCreateResourceSourceCode_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgCreateResourceSourceCode_t qt_meta_stringdata_DlgCreateResourceSourceCode = {
    {
QT_MOC_LITERAL(0, 0, 27),
QT_MOC_LITERAL(1, 28, 38),
QT_MOC_LITERAL(2, 67, 0),
QT_MOC_LITERAL(3, 68, 22),
QT_MOC_LITERAL(4, 91, 26),
QT_MOC_LITERAL(5, 118, 22),
QT_MOC_LITERAL(6, 141, 16),
QT_MOC_LITERAL(7, 158, 6),
QT_MOC_LITERAL(8, 165, 24),
QT_MOC_LITERAL(9, 190, 22),
QT_MOC_LITERAL(10, 213, 19)
    },
    "DlgCreateResourceSourceCode\0"
    "SlotPBSelectVersionControllHostClicked\0"
    "\0SlotRBFromLocalClicked\0"
    "SlotRBFromRepertoryClicked\0"
    "SlotRBFromExistClicked\0SlotAddBuildRule\0"
    "nIndex\0SlotPBSelectExistClicked\0"
    "SlotPBLocalPathClicked\0SlotPBCreateClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgCreateResourceSourceCode[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    1,   58,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DlgCreateResourceSourceCode::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DlgCreateResourceSourceCode *_t = static_cast<DlgCreateResourceSourceCode *>(_o);
        switch (_id) {
        case 0: _t->SlotPBSelectVersionControllHostClicked(); break;
        case 1: _t->SlotRBFromLocalClicked(); break;
        case 2: _t->SlotRBFromRepertoryClicked(); break;
        case 3: _t->SlotRBFromExistClicked(); break;
        case 4: _t->SlotAddBuildRule((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SlotPBSelectExistClicked(); break;
        case 6: _t->SlotPBLocalPathClicked(); break;
        case 7: _t->SlotPBCreateClicked(); break;
        default: ;
        }
    }
}

const QMetaObject DlgCreateResourceSourceCode::staticMetaObject = {
    { &DlgBase::staticMetaObject, qt_meta_stringdata_DlgCreateResourceSourceCode.data,
      qt_meta_data_DlgCreateResourceSourceCode,  qt_static_metacall, 0, 0}
};


const QMetaObject *DlgCreateResourceSourceCode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgCreateResourceSourceCode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgCreateResourceSourceCode.stringdata))
        return static_cast<void*>(const_cast< DlgCreateResourceSourceCode*>(this));
    return DlgBase::qt_metacast(_clname);
}

int DlgCreateResourceSourceCode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = DlgBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
