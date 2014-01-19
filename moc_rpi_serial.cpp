/****************************************************************************
** Meta object code from reading C++ file 'rpi_serial.h'
**
** Created: Mon Jan 13 20:17:45 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "rpi_serial.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rpi_serial.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_rpi_Serial[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   17,   17,   17, 0x0a,
      18,   17,   17,   17, 0x0a,
      36,   57,   17,   17, 0x0a,
      59,   17,   17,   17, 0x0a,
      77,   17,   17,   17, 0x0a,
      91,  110,   17,   17, 0x0a,
     117,   57,   17,   17, 0x0a,
     151,  183,   17,   17, 0x0a,
     185,  219,   17,   17, 0x0a,
     221,  263,   17,   17, 0x0a,
     267,  290,   17,   17, 0x0a,
     292,   17,  309,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_rpi_Serial[] = {
    "rpi_Serial\0run()\0\0getSensorValues()\0"
    "setPortName(QString)\0p\0setupSerialPort()\0"
    "onReadyRead()\0onDsrChanged(bool)\0"
    "status\0setPressure(rpi_sensor_pressure*)\0"
    "setCompass(rpi_sensor_compass*)\0c\0"
    "setAccelerometer(rpi_sensor_acc*)\0a\0"
    "setUltraSonic(int,rpi_sensor_ultrasonic*)\0"
    "i,s\0setUltraSonicSize(int)\0s\0"
    "ultraSonicSize()\0int\0"
};

void rpi_Serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        rpi_Serial *_t = static_cast<rpi_Serial *>(_o);
        switch (_id) {
        case 0: _t->run(); break;
        case 1: _t->getSensorValues(); break;
        case 2: _t->setPortName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setupSerialPort(); break;
        case 4: _t->onReadyRead(); break;
        case 5: _t->onDsrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setPressure((*reinterpret_cast< rpi_sensor_pressure*(*)>(_a[1]))); break;
        case 7: _t->setCompass((*reinterpret_cast< rpi_sensor_compass*(*)>(_a[1]))); break;
        case 8: _t->setAccelerometer((*reinterpret_cast< rpi_sensor_acc*(*)>(_a[1]))); break;
        case 9: _t->setUltraSonic((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< rpi_sensor_ultrasonic*(*)>(_a[2]))); break;
        case 10: _t->setUltraSonicSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: { int _r = _t->ultraSonicSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData rpi_Serial::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject rpi_Serial::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_rpi_Serial,
      qt_meta_data_rpi_Serial, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &rpi_Serial::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *rpi_Serial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *rpi_Serial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_rpi_Serial))
        return static_cast<void*>(const_cast< rpi_Serial*>(this));
    return QObject::qt_metacast(_clname);
}

int rpi_Serial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
