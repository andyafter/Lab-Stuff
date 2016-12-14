#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost,5002);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void ARTClient::readyRead(){
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress *sender = new QHostAddress("127.0.0.1");
    quint16 senderPort = 5000;
    socket->readDatagram(Buffer.data(),Buffer.size(), sender, &senderPort);
    qDebug()<<"message from" <<sender->toString();
    qDebug()<<"message port" <<senderPort;
    qDebug()<<"message from" <<Buffer;

}
