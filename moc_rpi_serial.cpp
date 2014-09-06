/****************************************************************************
** Meta object code from reading C++ file 'rpi_serial.h'
**
** Created: Wed Aug 27 20:52:11 2014
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
static const uint qt_meta_data_SerialWorker[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   34,   41,   41, 0x05,

 // slots: signature, parameters, type, tag, flags
      42,   58,   41,   41, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SerialWorker[] = {
    "SerialWorker\0resultReady(QString)\0"
    "result\0\0doWork(QString)\0parameter\0"
};

void SerialWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialWorker *_t = static_cast<SerialWorker *>(_o);
        switch (_id) {
        case 0: _t->resultReady((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->doWork((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialWorker::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialWorker,
      qt_meta_data_SerialWorker, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialWorker::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialWorker))
        return static_cast<void*>(const_cast< SerialWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void SerialWorker::resultReady(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_rpi_Serial[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   28,   28,   28, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   28,   28,   28, 0x0a,
      35,   28,   28,   28, 0x0a,
      53,   74,   28,   28, 0x0a,
      76,   28,   28,   28, 0x0a,
      94,   28,   28,   28, 0x0a,
     108,  127,   28,   28, 0x0a,
     134,  160,   28,   28, 0x0a,
     162,   28,   28,   28, 0x0a,
     182,   28,   28,   28, 0x0a,
     200,   28,   28,   28, 0x0a,
     216,   28,   28,   28, 0x0a,
     234,   28,   28,   28, 0x0a,
     253,  283,   28,   28, 0x0a,
     289,  306,   28,   28, 0x0a,
     308,   28,   28,   28, 0x2a,
     321,  346,   28,   28, 0x0a,
     348,   28,   28,   28, 0x0a,
     371,   28,   28,   28, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_rpi_Serial[] = {
    "rpi_Serial\0operate(QString)\0\0run()\0"
    "getSensorValues()\0setPortName(QString)\0"
    "p\0setupSerialPort()\0onReadyRead()\0"
    "onDsrChanged(bool)\0status\0"
    "setIMU9DOF(rpi_imu_9dof*)\0i\0"
    "imuProcessVersion()\0imuProcessCalib()\0"
    "imuProcessRaw()\0imuProcessQuant()\0"
    "imuProcessBinary()\0imuProcessRPIData(QByteArray)\0"
    "qData\0imuCommand(char)\0c\0imuCommand()\0"
    "transmitText(QByteArray)\0t\0"
    "handleResults(QString)\0stopCollecting()\0"
};

void rpi_Serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        rpi_Serial *_t = static_cast<rpi_Serial *>(_o);
        switch (_id) {
        case 0: _t->operate((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->run(); break;
        case 2: _t->getSensorValues(); break;
        case 3: _t->setPortName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setupSerialPort(); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->onDsrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setIMU9DOF((*reinterpret_cast< rpi_imu_9dof*(*)>(_a[1]))); break;
        case 8: _t->imuProcessVersion(); break;
        case 9: _t->imuProcessCalib(); break;
        case 10: _t->imuProcessRaw(); break;
        case 11: _t->imuProcessQuant(); break;
        case 12: _t->imuProcessBinary(); break;
        case 13: _t->imuProcessRPIData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 14: _t->imuCommand((*reinterpret_cast< char(*)>(_a[1]))); break;
        case 15: _t->imuCommand(); break;
        case 16: _t->transmitText((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 17: _t->handleResults((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 18: _t->stopCollecting(); break;
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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void rpi_Serial::operate(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_thread_rpi_serial[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   31,   31,   31, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_thread_rpi_serial[] = {
    "thread_rpi_serial\0onComplete()\0\0"
};

void thread_rpi_serial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        thread_rpi_serial *_t = static_cast<thread_rpi_serial *>(_o);
        switch (_id) {
        case 0: _t->onComplete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData thread_rpi_serial::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject thread_rpi_serial::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_thread_rpi_serial,
      qt_meta_data_thread_rpi_serial, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &thread_rpi_serial::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *thread_rpi_serial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *thread_rpi_serial::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_thread_rpi_serial))
        return static_cast<void*>(const_cast< thread_rpi_serial*>(this));
    return QThread::qt_metacast(_clname);
}

int thread_rpi_serial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
