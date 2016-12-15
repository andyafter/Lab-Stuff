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

    QHostAddress *sender = new QHostAddress("192.168.1.110");
    quint16 senderPort = 5002;
    socket->readDatagram(Buffer.data(),Buffer.size(), sender, &senderPort);
    qDebug()<<"message from" <<sender->toString();
    qDebug()<<"message port" <<senderPort;
    qDebug()<<"message from" <<Buffer;

}
