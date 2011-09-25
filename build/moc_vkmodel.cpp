/****************************************************************************
** Meta object code from reading C++ file 'vkmodel.h'
**
** Created: Sun Sep 25 19:47:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/models/vkmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vkmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VkModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,    9,    8,    8, 0x09,
      40,   34,    8,    8, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_VkModel[] = {
    "VkModel\0\0url\0slotUrlChanged(QUrl)\0"
    "reply\0slotFinished(QNetworkReply*)\0"
};

const QMetaObject VkModel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VkModel,
      qt_meta_data_VkModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VkModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VkModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VkModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VkModel))
        return static_cast<void*>(const_cast< VkModel*>(this));
    return QObject::qt_metacast(_clname);
}

int VkModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: slotUrlChanged((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 1: slotFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
