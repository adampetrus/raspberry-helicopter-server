#include "rpi_serial.h"
#include <QDebug>
#include <QList>
#include <QStringList>
#include "qextserialenumerator.h"
#include <rpi_sensors.h>
#include <QDateTime>
#include <math.h>
#include <rpi_vector.h>

//const double double_pi_value = acos(0)*2.0;
//const double math_pi() { return double_pi_value; }




SerialWorker::SerialWorker(rpi_Serial *sM) {
    serialManager = sM;
}


void SerialWorker::doWork(const QString &parameter) {
    serialManager->ReadSerial();
    emit resultReady(parameter);
}




rpi_Serial::rpi_Serial(QObject *parent,QString pName,rpi_imu_9dof *i,QDateTime *s,QThread *th): QObject(parent){
    //quat = new float[4];
    //euler = new float[3];
    //accel = new int[3];
    //gyro = new int[3];
    //magn= new int[3];
    imu = i;
    sPort=0;
    timer =0;
    processThread = th;

    //if (processThread) moveToThread(processThread);

    //moveToThread(&worker);

    portName=pName;
    //compass =0;
    //accelerometer =0;
    //gyroscope =0;
    starttime=s;
    okToCollect = true;

    quatSignalCount =0;
    loopRequest = false;

    SerialWorker *worker = new SerialWorker(this);
    worker->moveToThread(&workerThread);
    connect(&workerThread,SIGNAL(finished()),worker,SLOT(deleteLater()));

    //connect(worker,SIGNAL(resultReady(QString)),this,SLOT(handleResults(QString)));
    workerThread.start();


    //timer = new QTimer(this);
    setupSerialPort();
    connect(this,SIGNAL(operate(QString)),worker,SLOT(doWork(QString)));
    //connect(timer, SIGNAL(timeout()), this, SLOT(getSensorValues()));
    //timer->start(1000);
   
}

void rpi_Serial::handleResults(const QString &r) {
    qDebug() << "hResult" <<r;
    loopRequest = true;
    /*qDebug() << loopRequest << quatSignalCount;
    if ((loopRequest) && (quatSignalCount)) {
    quatSignalCount=0;
    if (sPort->isOpen()) {
        qDebug() << "Transmit z0" ;
        sPort->write("z ");

    }
    }*/
}


rpi_Serial::~rpi_Serial(){  
    workerThread.quit();
    workerThread.wait();
    sPort->close();

    if (sPort) delete sPort;
    sPort =0;

    //delete [] quat;
    //delete [] euler;
    //delete [] gyro;
    //delete [] accel;
    //delete [] magn;

}


void rpi_Serial::run() {
    qDebug() << "qThread New Threadf Started";

    //setupSerialPort();
    quatSignalCount =0;
    loopRequest = true;



}
void rpi_Serial::getSensorValues(){
    //! [2]
    qint64 timefromStart;
    timefromStart= starttime->msecsTo(QDateTime::currentDateTime());
    //if (compass) {compass->setAngle(0,0);}*/

}

void rpi_Serial::setupSerialPort() {
    //bool nport = false;
    
QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    //! [1]
    QStringList portNames;
    qDebug() << "List of ports:";
    foreach (QextPortInfo info, ports) {
    portNames << info.portName;
    }
    qDebug() << portNames;
    setPortName(portName);
    versionimutext = "Not Connected";
    //setPortName("/dev/ttyUSB0");
    if (!portNames.contains(portName)) 
        { 
            qDebug() << portName << " does not exist"; 
            //return;
        }
    if (!sPort) { sPort = new QextSerialPort(portName, QextSerialPort::/*Polling*/EventDriven/**/);  
        //sPort->setBaudRate(BAUD115200);
        sPort->setBaudRate(BAUD57600);
        //sPort->setBaudRate(BAUD38400);
        //sPort->setBaudRate(BAUD19200);
        //sPort->setBaudRate(BAUD9600);
        //sPort->setBaudRate(BAUD4800);




        //sPort->setBaudRate(BAUD19200);
        sPort->setFlowControl(FLOW_OFF);
        sPort->setParity(PAR_NONE);
        sPort->setDataBits(DATA_8);
        sPort->setStopBits(STOP_1);
    
    
    }else{ }
    
    if (sPort->open(QIODevice::ReadWrite | QIODevice::Unbuffered ) == true) {
        qDebug("is open: %d", sPort->isOpen());
        //if (processThread) sPort->moveToThread(processThread);
        //sPort->moveToThread(&worker);
        connect(sPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
        connect(sPort, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)));
        if (!(sPort->lineStatus() & LS_DSR))
        //qDebug() << "warning: device is not turned on";
        qDebug() << "listening for data on" << sPort->portName();

        qDebug() << "send commands";

        //for some unknown reason it seems to take around two seconds to initalise
        // sleep function added to ensure measurement takes place
        //QThread::msleep(2000);
        //workerThread.wait(2000);

        versionimutext = "Unknown Device";
        //ReadSerial();
        //imuCommand('v');
        //sPort->write("v");
        //imuCommand(IMU_RPI);

        qDebug() << "send commands complete";
    }
    else {
        versionimutext=  "device failed to open:" + sPort->errorString();
        qDebug() << "device failed to open:" << sPort->errorString();
    }
    //worker.start();
    
}
void rpi_Serial::setPortName(QString p) {
    portName =p ;
}
void rpi_Serial::onReadyRead() {
     emit operate("ReadSerial");
}

void rpi_Serial::ReadSerial()
{


    QByteArray bytes;
    int a = sPort->bytesAvailable();
    bytes.resize(a);
    int i  = sPort->read(bytes.data(), bytes.size());
    //if (i != -1){ 
    //    
    //}
    QString retMsg = bytes;
    //qDebug() << "bytes read:" << bytes.size() << buffer.size();
    //qDebug() << "bytes:" << bytes << buffer;
    //qDebug() << "string:" << retMsg;
    buffer +=bytes;
    int foundNewLine = buffer.indexOf("\n",0);
    while (foundNewLine != -1) {
        //qDebug() << "Process" << buffer << foundNewLine << buffer.left(foundNewLine);
        imuProcessRPIData(buffer.left(foundNewLine));
        buffer.remove(0,foundNewLine+1);
        foundNewLine = buffer.indexOf("\n",0);
    }
}
void rpi_Serial::onDsrChanged(bool status)
{
    if (status)
        qDebug() << "device was turned on";
    else
        qDebug() << "device was turned off";
}
//void rpi_Serial::setCompass(rpi_sensor_compass *c) {compass=c;}
//void rpi_Serial::setAccelerometer(rpi_sensor_acc *a){accelerometer=a;}


void rpi_Serial::imuProcessVersion() {}
void rpi_Serial::imuProcessCalib() {}
void rpi_Serial::imuProcessRaw() {}
void rpi_Serial::imuProcessQuant() {}
void rpi_Serial::imuProcessBinary() {


}
/*
float decodeFloat(String inString) {
  byte [] inData = new byte[4];
  
  if(inString.length() == 8) {
    inData[0] = (byte) unhex(inString.substring(0, 2));
    inData[1] = (byte) unhex(inString.substring(2, 4));
    inData[2] = (byte) unhex(inString.substring(4, 6));
    inData[3] = (byte) unhex(inString.substring(6, 8));
  }
      
  int intbits = (inData[3] << 24) | ((inData[2] & 0xff) << 16) | ((inData[1] & 0xff) << 8) | (inData[0] & 0xff);
  return Float.intBitsToFloat(intbits);
}
*/


void rpi_Serial::imuProcessRPIData(QByteArray qData) {
    qDebug() << "data to Process"<< qData << qData.size();
    //float quat[] = {0,0,0,0};
 /*   switch (qData.size()) {
        case 82 : {imu->setQuatFAccelIGyroIMagnIByHexMessage(qData);
                    quatSignalCount++;
                    loopRequest = true;
    //qDebug() << loopRequest << quatSignalCount;
                    if ((loopRequest) && (quatSignalCount)) {
                    quatSignalCount=0;
                    if (sPort->isOpen()) {
        //qDebug() << "Transmit z0" ;
                        sPort->write("z ");

                    }
                    }
            return;}
    default : {
        versionimutext = qData;
        return;
    }

     //qDebug() << quatSignalCount << quat[0] << quat[1] <<quat[2] << quat[3] ;


     //if ((quatSignalCount >= 32) && (loopRequest)) transmitText("q ");
}*/
    if (qData.size() == 82) {
        imu->setQuatFAccelIGyroIMagnIByHexMessage(qData);

    }else{
         versionimutext = qData;
    }


    quatSignalCount++;
    loopRequest = true;

    if ((loopRequest) && (quatSignalCount)) {
    quatSignalCount=0;
    if (sPort->isOpen()) {
        sPort->write("z ");
    }
    }


}

/*


void rpi_Serial::imuProcessRPIData() {

    qDebug() << buffer.size();
    
    qDebug() << buffer;
    float q[] = {0,0,0,0};
    int acc[] = {0,0,0};
    int gyro[] = {0,0,0};

    unsigned long recordedtimeStamp =    QByteArray::fromHex(reverseHexArray(buffer.mid(0,8))).toULong();
 qDebug() << recordedtimeStamp ;
    float quat[4];


	for (int k=1;k<5;k++) {
		QByteArray tmpq = reverseHexArray(buffer.mid(k*9,8));
		QByteArray tmpp = QByteArray::fromHex(tmpq);
		unsigned long  intbits = (tmpp[0] << 24) | ((tmpp[1] & 0xff) << 16) | ((tmpp[2] & 0xff) << 8) | (tmpp[3] & 0xff);
		
		float *tmpf = (float*)&intbits;
		
        quat[k-1] = *tmpf;//QByteArray::fromHex(tmpq).toFloat();
        qDebug() << k-1 << buffer.mid(k*9,8) << tmpq << quat[k-1] << *tmpf ;
	}
     

     qDebug() << quat[0] << quat[1] <<quat[2] << quat[3] ;
     buffer ="";
    
    
}*/

/*void rpi_Serial::setGyroscope(rpi_sensor_gyro *g) {
    gyroscope = g;
}*/

void rpi_Serial::imuCommand(char c) {


    if (sPort->isOpen() && sPort->isWritable()) {
        qDebug() << "Transmit z0" ;
        sPort->write(QByteArray(1,c) + " ");
    }
    return;
    buffer = "";
    currentCmd =c;
//    c ='v';;

    qDebug() << "sendCommand" << QByteArray(1,c) << "\n";
    sPort->write(QByteArray(1,c) + " \n");
    //sPort->write("\n");
    sPort->flush();

}

void rpi_Serial::transmitText(QByteArray t){
    quatSignalCount =0;
    if (sPort->isOpen()) {
        //qDebug() << "Transmit" << t;
        sPort->write(t);
        sPort->flush();

    }

}

void rpi_Serial::stopCollecting() {
    workerThread.quit();
    workerThread.wait();

    if (sPort->isOpen()) {
        sPort->close();
    }
}



QString rpi_Serial::versionIMUText() {
    return versionimutext;
}

void rpi_Serial::setIMU9DOF(rpi_imu_9dof *i) {
    imu = i;
}

thread_rpi_serial::thread_rpi_serial(QString pName,rpi_imu_9dof *i) : QThread() {
    quat = new float[4];
    connect(this,SIGNAL(finished()),this,SLOT(onComplete()));
    portName = pName;
    imu =0;
    imu9dof= i;
    start();

}


thread_rpi_serial::~thread_rpi_serial() {
    //exit();
    if (imu) delete imu;

}

void thread_rpi_serial::run() {

    imu= new rpi_Serial(0,portName,imu9dof,0,this);
    //imu->moveToThread(this);
    imu->run();
}

 void thread_rpi_serial::onComplete(){
     qDebug() << "Thread Complete";
 }


     void stopCollecting();



QString versionIMUText();
