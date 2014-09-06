#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <QMap>
#include <QCoreApplication>
#include <QVariant>
#include "rpi_log.h"
#include "rpi_sensors.h"
#include "rpi_servo.h"
#include "rpi_serial.h"
#include "rpi_control.h"
#include "gps_device.h"
#include <QList>
#include <QDataStream>
#include <QByteArray>
#include <QDateTime>



#ifndef RPIHELITCPSERVER_H
#define RPIHELITCPSERVER_H

/*QFile file("in.txt");
if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

QTextStream in(&file);
while (!in.atEnd()) {
    QString line = in.readLine();
    process_line(line);
}*/

class RPIHelicopterServer : public QTcpServer //, public QCoreApplication
{
    Q_OBJECT
    enum RPI_MESSAGES{ RPI_SERVO_STEER = 1001,RPI_SERVO_MOTOR ,
                       RPI_SENSOR_ACC = 2001,
                       RPI_SENSOR_COMPASS = 3001,
                       RPI_SENSOR_GPS = 4001,
                       RPI_SENSOR_PRESSURE = 5001,
                       RPI_SENSOR_ULTRASONIC_1 =6001,
                       RPI_SENSOR_ULTRASONIC_2,
                       RPI_SENSOR_ULTRASONIC_3,
                       RPI_SENSOR_ULTRASONIC_4,
                       RPI_SENSOR_ULTRASONIC_5,
                       RPI_SENSOR_ULTRASONIC_6,
                       RPI_SENSOR_ULTRASONIC_7,
                       RPI_SENSOR_ULTRASONIC_8,
                       RPI_RECEIVED_COMPLETE =10001
                     };
public:
    explicit RPIHelicopterServer(QString xfn,QObject *parent = 0);
    ~RPIHelicopterServer();
    QList<QTcpSocket*> sockets;
    rpi_Serial *rpiserial;
    rpi_servo *servo;
    QMap <QString,QVariant> settings;
    void sendXml(QString x);
    QDateTime zeroTime;

public slots:
    void connectionMade();
    void readRequest();
    void sendSensorData();
    void sendCommand(int type);
    void readXGPS();
    void processRequest(QDomElement &elem);
    void processRequest(rpi_request &r);
    void loadConfig();
    void saveConfig();
    void setUltrasonicSensors();
    void processFastMessage(QByteArray &da);
    void processReadXml(QString xml);
    void resetControls(); 
    quint16 getBlockSize(int g);
private:
    gps_device gpsd;
    QTimer *timer ;
    QDateTime starttime;
    QString xmlFileName;
    rpi_sensor_compass *compass;
    rpi_sensor_gps *gps;
    //rpi_sensor_acc *accelerometer;
    //rpi_sensor_gyro *gyroscope;
    rpi_Serial *serialimu;
    rpi_imu_9dof *imu9dof;
    rpi_sensor_pressure *bpressure;
    QList <rpi_sensor_ultrasonic *> ultraSonicSensors;
    QList <rpi_control *> controls;
    QList<QByteArray> receiveSocketDataArray;
    //QList<QDataStream*> receiveSocketStream;
    QList<quint16> receiveSocketBlockSize;
    
};

#endif // RPIHELITCPSERVER_H
