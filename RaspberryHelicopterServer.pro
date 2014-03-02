#-------------------------------------------------
#
# Project created by QtCreator 2013-05-03T19:47:45
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       += network
QT       += xml

TARGET = RaspberryHelicopterServer
CONFIG   += console
CONFIG   -= app_bundle

win32{
LIBS += -LC:\qextserial\qextserialport-1.2rc\release -lQt5ExtSerialPort1
INCLUDEPATH += C:\qextserial\qextserialport-1.2rc\src
}
linux-g++{
INCLUDEPATH += /usr/include/qt4/QtExtSerialPort/
LIBS += -L/usr/lib/arm-linux-gnueabihf/ -lqextserialport

HEADERS += bw_spi_8bit.h
SOURCES += bw_spi_8bit.cpp
SOURCES += servo_bitwizard.cpp
DEFINES += BITWIZARD_SPI
}
#LIBS += -LC:\RaspberryHelicopter\common\build-raspberryPiCommon-Desktop_Qt_5_0_2_MinGW_32bit-Debug\debug\libraspberryPiCommon.a
#INCLUDEPATH +=C:\RaspberryHelicopter\common\raspberryPiCommon
INCLUDEPATH += ../../common/include/
TEMPLATE = app
HEADERS += RPiHeliTCPServer.h \
    rpi_serial.h

SOURCES += main.cpp \
    rpi_serial.cpp \
    rpi_servo.cpp 

SOURCES += RPiHeliTCPServer.cpp

INCLUDEPATH += ../raspberry-pi-helicopter-common/include/
HEADERS +=    ../raspberry-pi-helicopter-common/include/rpi_control.h \
    ../raspberry-pi-helicopter-common/include/rpi_sensors.h \
    ../raspberry-pi-helicopter-common/include/rpi_log.h \
    ../raspberry-pi-helicopter-common/include/rpi_vector.h \
    ../raspberry-pi-helicopter-common/include/rpi_device.h


SOURCES +=     ../raspberry-pi-helicopter-common/cpp/rpi_vector.cpp \
    ../raspberry-pi-helicopter-common/cpp/rpi_control.cpp \
    ../raspberry-pi-helicopter-common/cpp/rpi_log.cpp \
    ../raspberry-pi-helicopter-common/cpp/rpi_sensors.cpp \
    ../raspberry-pi-helicopter-common/cpp/rpi_device.cpp
