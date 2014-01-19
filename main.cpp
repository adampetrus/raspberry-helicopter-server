#include <QCoreApplication>
#include "RPiHeliTCPServer.h"
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString xmlFilename = "piCopter.xml";
    if (argc > 1) {
        xmlFilename = argv[1];
    }
    qDebug() << "Filename XML" << xmlFilename;

    RPIHelicopterServer server(xmlFilename);
    qDebug() << "Raspberry Pi Helicopter Server";
    server.listen(QHostAddress::Any,1025);
    return a.exec();
}
