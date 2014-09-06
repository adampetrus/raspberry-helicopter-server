#ifndef RPI_GPS_DEVICE_H_
#define RPI_GPS_DEVICE_H_
#include <QCoreApplication>
#include <QThread>
#include <QTimer>


struct gps_data_t;

class rpi_sensor_gps;

class gps_device : public QThread {
    Q_OBJECT
public :
    gps_device();
    ~gps_device();
    void obtain(double& latitude,double& longitude,double& altitude,double &accurarcy);
    enum ConnectState { NOCONNECT =0, TIMEOUT =-1, NOFIX = 2, FIX =1 };
    int deviceConnectState;
    void setMaster(rpi_sensor_gps *m);
public slots:
    void obtainNextValue();


private :
    gps_data_t *gpsdata;
    rpi_sensor_gps *master;
    QTimer obtainTimer;
};


#endif
