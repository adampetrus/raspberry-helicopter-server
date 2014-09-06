#ifndef RPI_SERIAL_H_
#define RPI_SERIAL_H_
#include <QObject>
#include "qextserialport.h"
#include <QThread>
#include <QTimer>
#include <QDateTime>

//const double math_pi();


class rpi_imu_9dof;

QByteArray reverseHexArray(QByteArray s);

//class rpi_sensor_compass;
//class rpi_sensor_acc;
//class rpi_sensor_gyro;
class rpi_Serial;
class SerialWorker : public QObject
{
    Q_OBJECT
    QThread workerThread;
public:
    SerialWorker(rpi_Serial *sM);
public slots:
    void doWork(const QString &parameter) ;

signals:
    void resultReady(const QString &result);
private:
    rpi_Serial *serialManager;
};


class rpi_Serial : public QObject //QThread /*QTimer*/
{
    Q_OBJECT;
public:
    QextSerialPort *sPort;
    //float *quat;
    //float *euler;
    //int *gyro;
    //int *accel;
    //int *magn;

    rpi_Serial(QObject *parent=0,QString pName = "/dev/ttyAMA0",rpi_imu_9dof *i=0,QDateTime *t=0,QThread *th=0);
    ~rpi_Serial();
    QTimer *timer;
    //QString portName;
   enum FREEIMUCMDS {
        IMU_VERSION = 'v', IMU_CALIBRATION = 'c', IMU_CALIBRATION_V ='C' ,IMU_BINARY = 'b', 
        IMU_RAW = 'r' , IMU_QUAT = 'q', IMU_RPI = 'z'
    };

   QString versionIMUText();
private:
   //Worker *worker;
   QThread workerThread;

 
public slots:
    void run();
    void getSensorValues();
    void setPortName(QString p);
    void setupSerialPort();
    void onReadyRead();
    void onDsrChanged(bool status);
    //void setCompass(rpi_sensor_compass *c);
    //void setAccelerometer(rpi_sensor_acc *a);
    //void setGyroscope(rpi_sensor_gyro *g);
    void setIMU9DOF(rpi_imu_9dof* i);
    void imuProcessVersion();
    void imuProcessCalib();
    void imuProcessRaw();
    void imuProcessQuant();
    void imuProcessBinary();
    void imuProcessRPIData(QByteArray qData);
    void imuCommand(char c=IMU_RPI);
    void transmitText(QByteArray t);

    void handleResults(const QString &);
    void stopCollecting();

public:
    void ReadSerial();


private:
    int quatSignalCount;
    bool loopRequest;
    rpi_imu_9dof *imu;
    //float *quat;
    QString portName;
    bool okToCollect;
    QByteArray buffer;
    char currentCmd;
    QDateTime *starttime;
    int ultrasonicsize;
    //rpi_sensor_compass *compass;
    //rpi_sensor_acc *accelerometer;
    //rpi_sensor_gyro *gyroscope;
    QThread *processThread;
    QString versionimutext;


    //rpi_sensor_ultrasonic **ultrasonic;
    //rpi_sensor_pressure *bpressure;
signals:
    void operate(const QString &);
} ;


class thread_rpi_serial : public QThread {
    Q_OBJECT;
public:
    thread_rpi_serial(QString pName,rpi_imu_9dof *i);
    ~thread_rpi_serial();
    void run();

    float* quat;
    rpi_Serial *imu;
    rpi_imu_9dof *imu9dof;
public slots:
    void onComplete();
private:
    QString portName;
};


#endif
