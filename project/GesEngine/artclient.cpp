#inlcude <QString>

#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){
    QHostAddress *art = new QHostAddress("192.168.1.110");  // art address

    socket = new QUdpSocket(this);
    socket->bind(*art,5002);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void ARTClient::readyRead(){
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress *sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(),Buffer.size(), sender, &senderPort);
    if(Buffer.size()>0 && sender->toString() == "192.168.1.100"){
        qDebug()<<"message from" <<sender->toString();
        qDebug()<<"message port" <<senderPort;
        qDebug()<<"message:" <<Buffer;
    }
}

void ARTClient::extractMarkers(QString frame){
  qInfo() << "Here inside the extractMarkers." << endl;
}
