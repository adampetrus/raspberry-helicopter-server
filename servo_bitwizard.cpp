#include <stdint.h>
#include "rpi_log.h"
#include "rpi_control.h"
#include <QDateTime>
#include <QDomDocument>
#include <QDebug>
#include "bw_spi_8bit.h"


int test_spi() {
const char *device = "/dev/spidev0.0";
bw_spi_8bit  a20(device,0x86,0x23,0x0);
   for (int val=0;val<=0xFF;val+=0x20) {
        a20.setValue(val);
        sleep(1);
    }
return 0;
}

//const int test_spi_value = test_spi();

bool rpi_control::setValue(uint v){
	qDebug() << device_v << addr_v << node_v ;

	//device_v = "/dev/spidev0.0";
	//node_v = 0x20;
	//addr_v = 0x86;

//const char *device = "/dev/spidev0.0";

    //qDebug() << "Set Servo" << v;
    //qDebug() << "Set Servo" << device_v;

    value_v =v;


    printf("0x%x,0x%x,0x%x\n",addr_v,node_v,value_v);

    bw_spi_8bit  controlspi1(device_v.toStdString().c_str(),addr_v ,node_v,value_v);

    //bw_spi_8bit  controlspi1("/dev/spidev0.0",0x86 ,0x23);
	//qDebug() << controlspi1.device() ;

    controlspi1.setValue(value_v);
/*
    bw_spi_8bit  controlspi2(device_v.toStdString().c_str(),addr_v,0x21,value_v);
    controlspi2.setValue(value_v);

    bw_spi_8bit  controlspi3(device_v.toStdString().c_str(),addr_v,0x22,value_v);
    controlspi3.setValue(value_v);

    bw_spi_8bit  controlspi4(device_v.toStdString().c_str(),addr_v,0x23,value_v);
    controlspi4.setValue(value_v);



    bw_spi_8bit  controlspi5(device_v.toStdString().c_str(),addr_v,0x24,value_v);
    controlspi5.setValue(value_v);

    bw_spi_8bit  controlspi6(device_v.toStdString().c_str(),addr_v,0x25,value_v);
    controlspi6.setValue(value_v);

    bw_spi_8bit  controlspi7(device_v.toStdString().c_str(),addr_v,0x26,value_v);
    controlspi7.setValue(value_v);

*/


    return true;
}
