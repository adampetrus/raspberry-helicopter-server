/****************************************************************************
** Meta object code from reading C++ file 'RPiHeliTCPServer.h'
**
** Created: Wed Aug 27 21:59:16 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RPiHeliTCPServer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RPiHeliTCPServer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RPIHelicopterServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   37,   37,   37, 0x0a,
      38,   37,   37,   37, 0x0a,
      52,   37,   37,   37, 0x0a,
      69,   86,   37,   37, 0x0a,
      91,   37,   37,   37, 0x0a,
     102,  131,   37,   37, 0x0a,
     136,  165,   37,   37, 0x0a,
     167,   37,   37,   37, 0x0a,
     180,   37,   37,   37, 0x0a,
     193,   37,   37,   37, 0x0a,
     216,  248,   37,   37, 0x0a,
     251,  275,   37,   37, 0x0a,
     279,   37,   37,   37, 0x0a,
     295,  313,  315,   37, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RPIHelicopterServer[] = {
    "RPIHelicopterServer\0connectionMade()\0"
    "\0readRequest()\0sendSensorData()\0"
    "sendCommand(int)\0type\0readXGPS()\0"
    "processRequest(QDomElement&)\0elem\0"
    "processRequest(rpi_request&)\0r\0"
    "loadConfig()\0saveConfig()\0"
    "setUltrasonicSensors()\0"
    "processFastMessage(QByteArray&)\0da\0"
    "processReadXml(QString)\0xml\0resetControls()\0"
    "getBlockSize(int)\0g\0quint16\0"
};

void RPIHelicopterServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RPIHelicopterServer *_t = static_cast<RPIHelicopterServer *>(_o);
        switch (_id) {
        case 0: _t->connectionMade(); break;
        case 1: _t->readRequest(); break;
        case 2: _t->sendSensorData(); break;
        case 3: _t->sendCommand((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->readXGPS(); break;
        case 5: _t->processRequest((*reinterpret_cast< QDomElement(*)>(_a[1]))); break;
        case 6: _t->processRequest((*reinterpret_cast< rpi_request(*)>(_a[1]))); break;
        case 7: _t->loadConfig(); break;
        case 8: _t->saveConfig(); break;
        case 9: _t->setUltrasonicSensors(); break;
        case 10: _t->processFastMessage((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->processReadXml((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->resetControls(); break;
        case 13: { quint16 _r = _t->getBlockSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< quint16*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RPIHelicopterServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RPIHelicopterServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_RPIHelicopterServer,
      qt_meta_data_RPIHelicopterServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RPIHelicopterServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RPIHelicopterServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RPIHelicopterServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RPIHelicopterServer))
        return static_cast<void*>(const_cast< RPIHelicopterServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int RPIHelicopterServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
