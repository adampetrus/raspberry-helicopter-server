#include "gps_device.h"
#include <gps.h>
#include "rpi_sensors.h"
#include <QDebug>


gps_device::gps_device() : QThread() {
    master =0;
    gpsdata = new struct gps_data_t;
    if(gps_open("localhost", "2947", gpsdata)<0){
        fprintf(stderr,"Could not connect to GPSd\n");
        //gpsdata =0;
        deviceConnectState =NOCONNECT;
        return;
    }
    gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);

    fprintf(stderr,"Waiting for gps lock.");
    //when status is >0, you have data.
    while(gpsdata->status==0){
        //block for up to .5 seconds
        if (gps_waiting(gpsdata, 500)){
            //dunno when this would happen but its an error
            if(gps_read(gpsdata)==-1){
                fprintf(stderr,"GPSd Error\n");
                gps_stream(gpsdata, WATCH_DISABLE, NULL);
                gps_close(gpsdata);
                deviceConnectState =TIMEOUT;
                break;
            }
            else{
                //status>0 means you have data
                if(gpsdata->status>0){
                    //sometimes if your GPS doesnt have a fix, it sends you data anyways
                    //the values for the fix are NaN. this is a clever way to check for NaN.
                    if(gpsdata->fix.longitude!=gpsdata->fix.longitude || gpsdata->fix.altitude!=gpsdata->fix.altitude){
                        fprintf(stderr,"Could not get a GPS fix.\n");
                        gps_stream(gpsdata, WATCH_DISABLE, NULL);
                        //gps_close(gpsdata);
                        deviceConnectState =NOFIX;
                    }
                    //otherwise you have a legitimate fix!
                    else
                        fprintf(stderr,"\n");
                }
                //if you don't have any data yet, keep waiting for it.
                //else
                    //fprintf(stderr,".");
            }
        }
        //apparently gps_stream disables itself after a few seconds.. in this case, gps_waiting returns false.
        //we want to re-register for updates and keep looping! we dont have a fix yet.
        else {
            gps_stream(gpsdata, WATCH_ENABLE | WATCH_JSON, NULL);
            deviceConnectState =1;
        }
        //just a sleep for good measure.
        //sleep(1);
    }

    connect(&obtainTimer, SIGNAL(timeout()), this, SLOT(obtainNextValue()));
    moveToThread(this);
    connect(this,SIGNAL(finished()),this,SLOT(deleteLater()));
    start();

    //connect(worker,SIGNAL(resultReady(QString)),this,SLOT(handleResults(QString)));


    obtainTimer.start(1000);

}


gps_device::~gps_device() {

    if ((deviceConnectState == FIX) ||(deviceConnectState == NOFIX) )  {
    gps_stream(gpsdata, WATCH_DISABLE, NULL);
    gps_close(gpsdata);
    }
    delete gpsdata;



}

void gps_device::obtain(double& latitude,double& longitude,double& altitude,double &accurarcy) {
    gps_stream(gpsdata, WATCH_DISABLE, NULL);
    fprintf(stderr,"Longitude: %lf\nLatitude: %lf\nAltitude: %lf\nAccuracy: %lf\n\n",
                gpsdata->fix.latitude, gpsdata->fix.longitude, gpsdata->fix.altitude,
                (gpsdata->fix.epx>gpsdata->fix.epy)?gpsdata->fix.epx:gpsdata->fix.epy);
    //*/
    latitude = gpsdata->fix.latitude;
    longitude = gpsdata->fix.longitude;
    altitude = gpsdata->fix.altitude;
    (gpsdata->fix.epx> gpsdata->fix.epy)? accurarcy = gpsdata->fix.epx: accurarcy = gpsdata->fix.epy ;
}


void gps_device::setMaster(rpi_sensor_gps *m) {master =m;}
void gps_device::obtainNextValue() {
    qDebug() << "obtainNextValue";
    if (!master) return;
    obtain(master->getLatitude(),master->getLongitude(),master->getHeight(),master->getAccuracy());


    //
}
