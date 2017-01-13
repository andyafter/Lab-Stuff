#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){

    readStop = false;
    // not sure if it is the best practice to put the initialization of socket here
    QHostAddress *art = new QHostAddress("192.168.1.110");  // art address
    socket = new QUdpSocket(this);
    socket->bind(*art,5002);
    connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()));
}

ARTClient::~ARTClient()
{

}

void ARTClient::startReading()
{
    while(!readStop){
        qDebug()<<"From Thread";
        emit on_number("fthread",1);
        QThread::currentThread()->msleep(100);
        readyRead();
    }
}

void ARTClient::extractMarkers(QString frame)
{
    qInfo() << "Here inside the extractMarkers." << endl;
}

void ARTClient::gestureLearning()
{
    // analysis and extract fearures from real time data
    /* You can have multiple layers of gestures. If you do 
       so you need multiple functions and multiple events. 
       The scheduling of these gestures might come in handy.
     */
}

void ARTClient::broadCaseGestureEvent()
{
     // when a gesture is detected, trigered to send a signal to something else
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

void ARTClient::stopRead()
{
    readStop = true;
}
