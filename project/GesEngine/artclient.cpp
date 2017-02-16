#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){

    readStop = false;
    // not sure if it is the best practice to put the initialization of socket here
    QHostAddress *art = new QHostAddress("192.168.1.110");  // art address
    socket = new QUdpSocket(this);
    socket->bind(*art,5002);
    //connect(socket, SIGNAL(readyRead()),this,SLOT(readyRead()));

    //server = new QTcpServer(this);
    //connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    /*
    if(!server->listen(QHostAddress::Any, 12345)){
        qDebug() << "Server could not start!";
    }
    else{
        qDebug() << "Server Started!";
    }*/
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
            qDebug()<<"From Thread";
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
    // it's better to use math tools like opencv for this part
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
        if(posString[2].toFloat()>2250){
            continue;
        }
        position.append(posString[0].toFloat());
        position.append(posString[1].toFloat());
        position.append(posString[2].toFloat());
        markers.append(position);
    }
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

QString ARTClient::features()
{
    QVector<float> center(3);
    // kmeans parameters
    int total_values, K, max_iterations, has_name;
    vector<Point> points;

    for(int i = 0; i<markers.length(); i++){
        center[0] += markers[i][0];
        center[1] += markers[i][1];
        center[2] += markers[i][2];
    }
    center[0] = center[0] / float(markers.length());
    center[1] = center[1] / float(markers.length());
    center[2] = center[2] / float(markers.length());

    // parameters initialization
    K = 2;
    total_values = 3;
    max_iterations = 200;
    has_name = 0;

    handCenter = center;

    float adis = 0;
    int n = 0;

    for(int i =0; i<markers.length()-1;i++){
        vector<double> values;
        // should make this into a rewrite function in Point
        values.push_back(markers[i][0]);
        values.push_back(markers[i][1]);
        values.push_back(markers[i][2]);
        Point p(i, values);
        points.push_back(i);
    }

    Kmeans kmeans(K, markers.length(), total_values, max_iterations);
    kmeans.run(points);

    for(int i =0; i<markers.length()-1;i++){
        for(int j =1; j<markers.length();j++){
            n++;
            float dis = 0;
            dis += (markers[i][0] - markers[j][0])*(markers[i][0] - markers[j][0]);
            dis += (markers[i][1] - markers[j][1])*(markers[i][1] - markers[j][1]);
            dis += (markers[i][2] - markers[j][2])*(markers[i][2] - markers[j][2]);
            adis += qSqrt(dis);
        }
    }
    adis = adis/n;

    QString messageToUnity = "";
    if(adis<80){
        qDebug() << "grab!";
        messageToUnity += "grab ";
    }
    messageToUnity += QString::number(center[0]);
    messageToUnity += " ";
    messageToUnity += QString::number(center[1]);
    messageToUnity += " ";
    messageToUnity += QString::number(center[2]);
    messageToUnity += " ";
    return messageToUnity;
}

void ARTClient::readyRead(){
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;

    socket->readDatagram(Buffer.data(),Buffer.size(), &sender, &senderPort);
    if(Buffer.size()>0 && sender.toString() == "192.168.1.100"){
        // Buffer will be where the data is stored
        rawData = Buffer;
        extractMarkers(rawData);
        QString messageToUnity = features();
        //qDebug() << messageToUnity;
        emit refreshMarkers(messageToUnity);
    }
}

void ARTClient::newConnection()
{
    // original plan for tcp
}


void ARTClient::stopRead()
{
    readStop = true;
}

void ARTClient::setRawData(const QString &value)
{
    rawData = value;
}

void ARTClient::sendUnity()
{
    //sockUnity->write("here is something");
    qDebug()<<"something haha";
}

QString ARTClient::getRawData() const
{
    return rawData;
}
