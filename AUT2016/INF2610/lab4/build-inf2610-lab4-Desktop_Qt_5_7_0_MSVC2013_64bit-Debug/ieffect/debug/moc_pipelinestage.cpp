/****************************************************************************
** Meta object code from reading C++ file 'pipelinestage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../inf2610-lab4-2.6/ieffect/pipelinestage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pipelinestage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PipelineStage_t {
    QByteArrayData data[12];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PipelineStage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PipelineStage_t qt_meta_stringdata_PipelineStage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PipelineStage"
QT_MOC_LITERAL(1, 14, 12), // "stateChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "newState"
QT_MOC_LITERAL(4, 37, 4), // "done"
QT_MOC_LITERAL(5, 42, 8), // "setState"
QT_MOC_LITERAL(6, 51, 5), // "state"
QT_MOC_LITERAL(7, 57, 4), // "cons"
QT_MOC_LITERAL(8, 62, 11), // "ImageQueue*"
QT_MOC_LITERAL(9, 74, 4), // "prod"
QT_MOC_LITERAL(10, 79, 4), // "name"
QT_MOC_LITERAL(11, 84, 4) // "rank"

    },
    "PipelineStage\0stateChanged\0\0newState\0"
    "done\0setState\0state\0cons\0ImageQueue*\0"
    "prod\0name\0rank"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PipelineStage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       4,   36, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,

 // properties: name, type, flags
       7, 0x80000000 | 8, 0x0009500b,
       9, 0x80000000 | 8, 0x0009500b,
      10, QMetaType::QString, 0x00095103,
      11, QMetaType::Int, 0x00095103,

       0        // eod
};

void PipelineStage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PipelineStage *_t = static_cast<PipelineStage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->done(); break;
        case 2: _t->setState((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PipelineStage::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PipelineStage::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PipelineStage::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PipelineStage::done)) {
                *result = 1;
                return;
            }
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< ImageQueue* >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        PipelineStage *_t = static_cast<PipelineStage *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< ImageQueue**>(_v) = _t->consQueue(); break;
        case 1: *reinterpret_cast< ImageQueue**>(_v) = _t->prodQueue(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->name(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->rank(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        PipelineStage *_t = static_cast<PipelineStage *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setConsQueue(*reinterpret_cast< ImageQueue**>(_v)); break;
        case 1: _t->setProdQueue(*reinterpret_cast< ImageQueue**>(_v)); break;
        case 2: _t->setName(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setRank(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject PipelineStage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PipelineStage.data,
      qt_meta_data_PipelineStage,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PipelineStage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PipelineStage::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PipelineStage.stringdata0))
        return static_cast<void*>(const_cast< PipelineStage*>(this));
    return QObject::qt_metacast(_clname);
}

int PipelineStage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void PipelineStage::stateChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PipelineStage::done()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
