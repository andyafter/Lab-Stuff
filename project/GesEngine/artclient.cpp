#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){

    readStop = false;
    // not sure if it is the best practice to put the initialization of socket here
    QHostAddress *art = new QHostAddress("192.168.1.110");  // art address
    socket = new QUdpSocket(this);
    socket->bind(*art,5002);
    //connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()));
}

ARTClient::~ARTClient()
{
    readStop = true;
}

void ARTClient::startReading()
{
    int n = 1;
    while(!readStop){
        if(n++%60==0){
            qDebug()<<"From Thread"<< n;
        }
        emit on_number("fthread",1);
        QThread::currentThread()->msleep(10);
        readyRead();
    }
}

void ARTClient::extractMarkers(QString frame)
{
    markers.clear();
    // this function converts the udp package to a list of marker positions
    QString data = frame.split('\n')[4];
    QStringList temp = data.split("][");
    for(int i =1;i<temp.length();++i){
        QVector<float> position;
        QStringList posString;
        if(temp[i].contains("] [")){
            posString = temp[i].split("] [")[0].split(" ");
        }
        else if(temp[i].contains("]\r")){
            posString = temp[i].split("]\r")[0].split(" ");
        }
        position.append(posString[0].toFloat());
        position.append(posString[1].toFloat());
        position.append(posString[2].toFloat());
        markers.append(position);
    }
    qDebug()<<markers;
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

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(Buffer.data(),Buffer.size(), &sender, &senderPort);
    if(Buffer.size()>0 && sender.toString() == "192.168.1.100"){
        //qDebug()<<"message from" <<sender.toString();
        //qDebug()<<"message port" <<senderPort;
        //qDebug()<<"message:" <<Buffer;
        rawData = Buffer;
        extractMarkers(rawData);
    }
}

void ARTClient::stopRead()
{
    readStop = true;
}

void ARTClient::setRawData(const QString &value)
{
    rawData = value;
}

QString ARTClient::getRawData() const
{
    return rawData;
}
