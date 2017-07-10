/****************************************************************************
** Meta object code from reading C++ file 'dlgcreategit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dlgcreategit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlgcreategit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DlgCreateGit_t {
    QByteArrayData data[7];
    char stringdata[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DlgCreateGit_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DlgCreateGit_t qt_meta_stringdata_DlgCreateGit = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 15),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 16),
QT_MOC_LITERAL(4, 47, 19),
QT_MOC_LITERAL(5, 67, 7),
QT_MOC_LITERAL(6, 75, 10)
    },
    "DlgCreateGit\0SlotLocationSel\0\0"
    "SlotAddBuildRule\0SlotDeleteBuildRule\0"
    "SlotAdd\0SlotCancle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DlgCreateGit[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DlgCreateGit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DlgCreateGit *_t = static_cast<DlgCreateGit *>(_o);
        switch (_id) {
        case 0: _t->SlotLocationSel(); break;
        case 1: _t->SlotAddBuildRule(); break;
        case 2: _t->SlotDeleteBuildRule(); break;
        case 3: _t->SlotAdd(); break;
        case 4: _t->SlotCancle(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject DlgCreateGit::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DlgCreateGit.data,
      qt_meta_data_DlgCreateGit,  qt_static_metacall, 0, 0}
};


const QMetaObject *DlgCreateGit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DlgCreateGit::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DlgCreateGit.stringdata))
        return static_cast<void*>(const_cast< DlgCreateGit*>(this));
    return QDialog::qt_metacast(_clname);
}

int DlgCreateGit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
