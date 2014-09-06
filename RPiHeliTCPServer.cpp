#include "RPiHeliTCPServer.h"
#include <QDataStream>
#include <QTimer>
#include "rpi_serial.h"
#include <QDomDocument>

RPIHelicopterServer::RPIHelicopterServer(QString xfn,QObject *parent) :
    QTcpServer (parent)  {
    starttime = QDateTime::currentDateTime();
    xmlFileName = xfn;
    connect(this,SIGNAL(newConnection()),this,SLOT(connectionMade()));
    qDebug() << "Raspberry Pi Server Class Opened!";
    servo =0;
    servo = new rpi_servo(); //(RPI_SERVER);
    compass = new rpi_sensor_compass(rpi_sensor_compass::SENSOR_MODE_SERVER);
    //if (!compass->test()) exit(0);
    gps =new rpi_sensor_gps(rpi_sensor_compass::SENSOR_MODE_SERVER);
    gpsd.setMaster(gps);
    //if (!gps->test()) exit(0);
    //accelerometer = new rpi_sensor_acc(rpi_sensor_acc::SENSOR_MODE_SERVER);
    //if (!accelerometer->test()) exit(0);
    //gyroscope = new rpi_sensor_gyro(rpi_sensor_gyro::SENSOR_MODE_SERVER);
    //if (!gyroscope->test()) exit(0);
    bpressure = new rpi_sensor_pressure(rpi_sensor_pressure::SENSOR_MODE_SERVER);
    //if (!bpressure->test()) exit(0);
    settings["noUltraSonicSensors"] = 4;


    //zeroTime = QDateTime::currentDateTime();
    imu9dof = new rpi_imu_9dof(rpi_device::SENSOR_MODE_SERVER,starttime);
    //serialimu = new rpi_Serial(this,"/dev/ttyUSB0",imu9dof);
    serialimu = new rpi_Serial(this,"/dev/ttyAMA0",imu9dof);
    //serialimu->sPort->write("v");


    qDebug() << "imu loaded";

    timer =0;
    qDebug() << "Serial Started";
    //rpiserial = new rpi_Serial(parent,&starttime);
    //rpiserial->setCompass(compass);
    //rpiserial->setPressure(bpressure);
    //rpiserial->setAccelerometer(accelerometer);
    //rpiserial->setGyroscope(gyroscope);
    //rpiserial->run();
    

    //loadConfig();
    //accelerometer->setAcceleration(0,0,0,QDateTime::currentDateTime());
    //gyroscope->setAcceleration(0,0,0,QDateTime::currentDateTime());
    /*
    //saveConfig();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(sendSensorData()));
    timer->start(1000);
    */
}

void RPIHelicopterServer::sendSensorData() {
    qDebug() << "sendSensorData";
    //return;
    //sendCommand(RPI_SENSOR_ACC);
    //accelerometer->setAcceleration(1,0,0,QDateTime::currentDateTime());
}

RPIHelicopterServer::~RPIHelicopterServer() {
    delete servo;
    servo =0;
    timer->stop();
    delete timer;
    timer =0;
}

void RPIHelicopterServer::resetControls() {
	if(controls.size() > 0) controls[0]->setValue(128);
	if(controls.size() > 1) controls[1]->setValue(128);
}


void RPIHelicopterServer::connectionMade() {
    qDebug() << "Connection Made";
    qDebug() << hasPendingConnections();
    QTcpSocket *h = nextPendingConnection();
    //receiveSocketBlockSize[sockets.size()] = 0;
    sockets << h;
    receiveSocketBlockSize << 0;
    
    //receiveSocketStream << *in;

    receiveSocketDataArray << QByteArray();
    //QDataStream* in(sockets[g]);
    //in->setVersion(QDataStream::Qt_4_0);
    
    connect(h,SIGNAL(readyRead()),this,SLOT(readRequest()));
    connect(h,SIGNAL(disconnected()),this,SLOT(resetControls()));

    QList<int> requestOnConnect;
    requestOnConnect //<< rpi_request::REQUEST_ACCELEROMETER
                     //   << rpi_request::REQUEST_GYROSCOPE
                     //   << rpi_request::REQUEST_COMPASS
                     //   << rpi_request::REQUEST_PRESSSURE
                     //   << rpi_request::REQUEST_GPS
                     //   << rpi_request::REQUEST_ULTRASONIC_LIST_SIZE
                        << rpi_request::REQUEST_CONTROL_LIST_SIZE;
    for (int k=0;k<requestOnConnect.size();k++) {
        rpi_request r(requestOnConnect[k]);
        processRequest(r);

    }
}

void RPIHelicopterServer::processRequest(QDomElement &elem) {
    rpi_request r(rpi_request::REQUEST);
    r.readDomElement(elem);
    processRequest(r);
}


void RPIHelicopterServer::processRequest(rpi_request &r) {
    switch (r.type()) {
        /*case rpi_request::REQUEST_ACCELEROMETER :  {
            sendXml(accelerometer->toXML());
            break;
        }*/
        /*case rpi_request::REQUEST_GYROSCOPE :  {
            sendXml(gyroscope->toXML());
            break;
        }*/
        case rpi_request::REQUEST_COMPASS :  {
            sendXml(compass->toXML());
            break;
        }
        case rpi_request::REQUEST_GPS :  {
            sendXml(gps->toXML());
            break;
        }
        case rpi_request::REQUEST_PRESSSURE :  {
            sendXml(bpressure->toXML());
            break;
        }
        /*case rpi_request::REQUEST_ULTRASONIC :  {
            //sendXml(accelerometer->toXML());
            if (!r.reply().size()) return;
            int k =r.reply().first().toInt();
            if (ultraSonicSensors.size() < k)
            {
                ultraSonicSensors[k]->setId(k);
                sendXml(ultraSonicSensors[k]->toXML());
            }
            break;
        }*/
            case rpi_request::REQUEST_CONTROL :  {
        //sendXml(accelerometer->toXML());
            if (!r.reply().size()) return;
            int k =r.reply().first().toInt();
            if (controls.size() < k)
            {
                controls[k]->setId(k);
                sendXml(controls[k]->toXML());
            }
            break;
    }
        case rpi_request::REQUEST_ULTRASONIC_LIST_SIZE :  {
            r.reply() << QString("%1").arg(ultraSonicSensors.size());
            sendXml(r.toXML());
            break;
        }
        case rpi_request::REQUEST_CONTROL_LIST_SIZE :  {
            qDebug() << "request_controls";
            r.reply() << QString("%1").arg(controls.size());
            sendXml(r.toXML());

            for(int k=0;k<controls.size();k++) {
                sendXml(controls[k]->toXML());
            }


            break;
        }

        case rpi_request::REQUEST_INSERT_CONTROL :  {
            rpi_control *n = new rpi_control();
            int id = controls.size();
            n->setId(id);
            controls << n;
            sendXml(n->toXML());
            break;
        }
        case rpi_request::REQUEST_INSERT_ULTRASONIC :  {
            return;
            /*rpi_sensor_ultrasonic *u =
            new rpi_sensor_ultrasonic(rpi_sensor_ultrasonic::SENSOR_MODE_CLIENT
                                      ,accelerometer->ZeroTime() );
            int id = ultraSonicSensors.size();
            u->setId(id);
            ultraSonicSensors << u;
            sendXml(u->toXML());*/
            break;
        }

        case rpi_request::REQUEST_REMOVE_CONTROL :  {
            break;
        }
        case rpi_request::REQUEST_REMOVE_ULTRASONIC :  {
            break;
        }
        case rpi_request::REQUEST_SAVE_CONFIG :  {
            saveConfig();
            sendXml(r.toXML());
            break;
        }
        //case rpi_request::REPLY{
        
        //}
        default : {break;}
    }

}

quint16 RPIHelicopterServer::getBlockSize(int g) {
     quint16 rblockSize =0;
     quint16 *blockSize_ptr =0;
     char charBlockSize[3];
     charBlockSize[0] = receiveSocketDataArray[g][0];
     charBlockSize[1] = receiveSocketDataArray[g][1];
     rblockSize = quint16(charBlockSize[0]) << 8 | quint16(charBlockSize[1]) ;
	qDebug() << "blockSize" << rblockSize;
     return rblockSize;
}


void RPIHelicopterServer::readRequest() {
    qDebug() << "Server Read From Client"; 
    //waitForReadyRead(-1);
    quint16 blockSize =0;
    qDebug() << "Socket Size" << sockets.size();
    for (int g=0;g<sockets.size();g++) {
           QDataStream in(sockets[g]);
           in.setVersion(QDataStream::Qt_4_0);
	   
           
           //qDebug() << "Reading";
           //qDebug() << "incoming" <<  sockets[g]->bytesAvailable();
           
           const int readSize = sockets[g]->bytesAvailable();
           char* tmp =new char[readSize+1];
           in.readRawData(tmp,readSize);
           
           //qDebug() << tmp;
           
           receiveSocketDataArray[g].append(tmp,readSize);
           qDebug() << "cache"  << receiveSocketDataArray[g].size();         
           //while (sockets[g]->bytesAvailable() > (int)sizeof(quint16)) {
           //qDebug() << "Reading";
           //in >> blockSize;
           
           if (!receiveSocketDataArray[g].size()) continue; 

           //blockSize_ptr = (quint16*) charBlockSize;
           //quint16 blockSize2 = quint16(charBlockSize[1]) << 8 | quint16(charBlockSize[0]) ;
           blockSize = getBlockSize(g);
           if(blockSize==0) {
            receiveSocketDataArray[g].clear();
            continue;
           }
           
           //qDebug() << blockSize1 << blockSize2;
           
           bool checkData = true;
           
           while(checkData) {
                checkData = false;
                //qDebug() << "Block Size:" << blockSize;

		

                if (blockSize+2<=receiveSocketDataArray[g].size() && (blockSize!=0) )  {

		QByteArray messagePacket = receiveSocketDataArray[g].mid(6,blockSize-5);
		//qDebug() << "Remove" << blockSize+2 << blockSize << "from" << receiveSocketDataArray[g].size();
		receiveSocketDataArray[g].remove(0,blockSize+2);
		//qDebug() << "Remove" << blockSize+2 << blockSize << "from" << receiveSocketDataArray[g].size();
			
		
		if(blockSize == 12) {
			processFastMessage(messagePacket);	
		}else{
			//for(int f=0;f<10;f++) qDebug() << f << messagePacket[f];
			//for(int f=messagePacket.size() -10;f<messagePacket.size();f++) qDebug() << f << messagePacket[f];
			
			processReadXml(messagePacket);
                }
		}
		if (!receiveSocketDataArray[g].size()) continue;
		blockSize = getBlockSize(g);
		//qDebug() << "New Block Size:" << blockSize;
                if ( (blockSize<=receiveSocketDataArray[g].size() ) && (blockSize!=0))  checkData = true;
                
                
                
        
           
           }
           
        
        }
    }
           //while (sockets[g]->bytesAvailable() < blockSize)
           //    sockets[g]->waitForBytesWritten();
           //qDebug() << "Reading" << blockSize;
/*
            if (blockSize < 5) {
            
            qDebug() << "Fast Message" ;    
            
            }else{


           qDebug() << "end of current message";
           }
           qDebug() << "flush socket";
          //sockets[g]->flush();
           }
            
}*/

void RPIHelicopterServer::processReadXml(QString xml) {

           //QString xml;
           //in >> xml;
           QDomDocument xmlDoc;
           xmlDoc.setContent(xml);

           QDomElement docElem = xmlDoc.documentElement();

           //qDebug() << "received: "<< docElem.tagName() << xml;
           if (docElem.tagName() == "request") {
               processRequest(docElem);
           }else if (docElem.tagName() == "Gyroscope") {
               //gyroscope->readDomElement(docElem);
           }else if (docElem.tagName() == "Accelerometer") {
               //accelerometer->readDomElement(docElem);
           }else if (docElem.tagName() == "Compass") {
                compass->readDomElement(docElem);
           }else if (docElem.tagName() == "GPS") {
                gps->readDomElement(docElem);
           }else if (docElem.tagName() == "Pressure") {
                bpressure->readDomElement(docElem);
           }else if (docElem.tagName() == "Control") {
               rpi_control *temp = new rpi_control;
               temp->readDomElement(docElem);
               if (temp->id()<controls.size()) {
                   rpi_control *temp2 = controls[temp->id()];
                   controls[temp->id()] = temp;
                   temp = temp2;
               }
               delete temp;
           }
           }


void RPIHelicopterServer::readXGPS() {

}

void RPIHelicopterServer::setUltrasonicSensors() {

}

void RPIHelicopterServer::sendCommand(int type) {
        for (int g=0;g<sockets.size();g++) {
            if (sockets[g]->state() == QAbstractSocket::ConnectedState)  {
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                //QTextStream out(&block,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_4_0);
                out << (quint16)0;
                //out << (quint16)type;
                switch (type) {
                    case RPI_SENSOR_ACC : {
                        //qDebug()
                        //out << accelerometer->toXML(true,false);
                        //out << .toLocal8Bit().toHex();
                        break;}
                    case RPI_SENSOR_COMPASS : { break;}
                    case RPI_SENSOR_GPS : { break;}
                    case RPI_SENSOR_PRESSURE : { break;}
                    case RPI_SENSOR_ULTRASONIC_1 : { break;}
                    case RPI_SENSOR_ULTRASONIC_2 : { break;}
                    case RPI_SENSOR_ULTRASONIC_3 : { break;}
                    case RPI_SENSOR_ULTRASONIC_4 : { break;}
                    case RPI_SENSOR_ULTRASONIC_5 : { break;}
                    case RPI_SENSOR_ULTRASONIC_6 : { break;}
                    case RPI_SENSOR_ULTRASONIC_7 : { break;}
                    case RPI_SENSOR_ULTRASONIC_8 : { break;}
                    default : { break; }
                }
                out.device()->seek(0);
                qint64 sizeBlock = (quint16)(block.size() - sizeof(quint16));
                //qDebug() << "BlockSize" << QString("%1").arg(sizeBlock);
                out << (quint16)(block.size() - sizeof(quint16));
                sockets[g]->write(block);
                sockets[g]->flush();
            }else{
                QTcpSocket *tg = sockets[g];
                //receiveSocketStream *rg = receiveSocketStream[g];
                //delete rg;
                delete tg;
                receiveSocketDataArray.removeAt(g);
                sockets.removeAt(g);
                //receiveSocketStream.removeAt(g);
                g--;
            }
        }
}


void RPIHelicopterServer::sendXml(QString x) {
        for (int g=0;g<sockets.size();g++) {
            if (sockets[g]->state() == QAbstractSocket::ConnectedState)  {
                QByteArray block;
                QDataStream out(&block, QIODevice::WriteOnly);
                //QTextStream out(&block,QIODevice::WriteOnly);
                out.setVersion(QDataStream::Qt_4_0);
                out << (quint16)0;
                //out << (quint16)type;
                out << x;
                out.device()->seek(0);
                qint64 sizeBlock = (quint16)(block.size() - sizeof(quint16));
                //qDebug() << "BlockSize" << QString("%1").arg(sizeBlock);
                out << (quint16)(block.size() - sizeof(quint16));
                sockets[g]->write(block);
                sockets[g]->flush();
            }
        }
}

void RPIHelicopterServer::loadConfig(){
    QFile file("/etc/rpi_heli/rpi_config.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QDomDocument xmlDoc;
    xmlDoc.setContent(file.readAll());

    //qDebug() << "Restore Config:";
    //qDebug() << xmlDoc.toString();
    //qDebug() << "End Config";


    QDomElement elemDoc = xmlDoc.documentElement();
    qDebug() << "get element";
    int controlId =0;
    int ultrasonicId =0;
    QDomNode n = elemDoc.firstChild();
    while(!n.isNull()) {
        QDomElement f = n.toElement(); // try to convert the node to an element.
        //qDebug() << "Loading " << f.tagName();
        if(!f.isNull()) {
            /*if (f.tagName() == "Accelerometer") {

                accelerometer->readDomElement(f);
                accelerometer->reset();
            }
            else if (f.tagName() == "Gyroscope") {
                gyroscope->readDomElement(f);
                gyroscope->reset();
            }
            else */if (f.tagName() == "Compass") {
                compass->readDomElement(f);
            }
            else if (f.tagName() == "Pressure") {
                bpressure->readDomElement(f);
            }
            else if (f.tagName() == "GPS") {
                gps->readDomElement(f);
            }
            else if (f.tagName() == "Control") {
                rpi_control *c = new rpi_control;
                c->readDomElement(f);
                c->setId(controlId);
                c->reset();
                controls << c;
                controlId++;
                //*/
            }
            else if (f.tagName() == "Ultrasonic") {
                //rpi_sensor_ultrasonic *u = new rpi_sensor_ultrasonic(rpi_sensor_ultrasonic::SENSOR_MODE_SERVER,accelerometer->ZeroTime());
                //u->readDomElement(f);
                //ultraSonicSensors << u;
                //u->setId(ultrasonicId);
                //ultrasonicId++;
            }
        }
        n = n.nextSibling();
    }
}

void RPIHelicopterServer::saveConfig(){
    qDebug() << "saveConfig()";
    QDomDocument config("config");
    QDomElement root = config.createElement("config");
    config.appendChild(root);
    QDomElement accroot = config.createElement("Accelerometer");
    QDomElement gpsroot = config.createElement("GPS");
    QDomElement gyroroot = config.createElement("Gyroscope");
    QDomElement comproot = config.createElement("Compass");
    QDomElement presroot = config.createElement("Pressure");
    root.appendChild(accroot);
    root.appendChild(gpsroot);
    root.appendChild(gyroroot);
    root.appendChild(comproot);
    root.appendChild(presroot);

    //QDomDocument acc;
    //accelerometer->addtoDomDoc(config,accroot,false,true);
    //gyroscope->addtoDomDoc(config,gyroroot,false,true);
    compass->addtoDomDoc(config,comproot,false,true);
    bpressure->addtoDomDoc(config,presroot,false,true);
    gps->addtoDomDoc(config,gpsroot,false,true);
    //qDebug() << "save controls" << controls.size();
    for (int k=0;k<controls.size();k++) {
        //qDebug() << "saveConfig" << k;
        QDomElement controot = config.createElement("Control");
        root.appendChild(controot);
        controls[k]->addtoDomDoc(config,controot,true,true);
    }
    for (int k=0;k<ultraSonicSensors.size();k++) {
        QDomElement ultrroot = config.createElement("Ultrasonic");
        root.appendChild(ultrroot);
        ultraSonicSensors[k]->addtoDomDoc(config,ultrroot,false,true);
    }

    QFile file("/etc/rpi_heli/rpi_config.xml");
    if (!file.open(QIODevice::WriteOnly)) return;
    file.write(config.toByteArray());
}

void RPIHelicopterServer::processFastMessage(QByteArray &da) { 
	qDebug() << "Fast Message";
}



