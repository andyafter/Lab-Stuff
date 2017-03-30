#include "artclient.h"

ARTClient::ARTClient(QObject *parent) : QObject(parent){

    readStop = false;
    srand(time(NULL));
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
    //qDebug() << temp.length();
    //qDebug() << data;
    //qDebug() << temp;
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
    int K, max_iterations;
    K = 2;
    max_iterations = 100;
    QVector<float> handPos ;
    // handPos = kmeans(markers);
    // qDebug() << handPos;

    for(int i = 0; i<markers.length(); i++){
        center[0] += markers[i][0];
        center[1] += markers[i][1];
        center[2] += markers[i][2];
    }
    center[0] = center[0] / float(markers.length());
    center[1] = center[1] / float(markers.length());
    center[2] = center[2] / float(markers.length());

    handCenter = center;


    // previous grabbing detection
    float adis = 0;
    int n = 0;

    for(int i =0; i<markers.length()-1;i++){
        for(int j = i; j<markers.length();j++){
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
        // qDebug() << "grab!";
        // messageToUnity += "grab ";
    }

    // center = handPos;  // result from kmeans
    handPos = handCenter;
    center = handCenter; // average ball position
    qDebug() << handPos;
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

QVector<float> ARTClient::kmeans(QVector<QVector<float>> points){

    if(points.length()<=1){
        QVector<float> none(3);
        none[0] = 1111111;
        return none;
    }
    // consider only k==2
    int K = 2;
    // whether the function converges
    float distort = 1;

    // centers and cluster points
    QVector<QVector<float>> centers(K);
    QVector<QVector<float>> clusters(K);     // cluster is only the center position and how many points are there

    QVector<float> result;
    // this process should be generalized if you do k>2
    // c1 and c2 will later be used to store how many markers are there in a class(which is dirty but I prefer not to declaire too many variables)
    int c1 = rand() % points.length();
    int c2 = rand() % points.length();
    qDebug() << points.length();
    while(c2==c1){    // dirty stuff
        c2 = rand() % points.length();
        // using time directly as the random number
        if(c2==0){
            c2 = (c1+1) % points.length();
        }
    }

    centers[0] = points[c1];
    centers[1] = points[c2];

    // initialize centers and find functions to erase everything from qvector
    for(int i=0; i<K; ++i){
        for(int j=0; j<4; ++j){
            clusters[i].append(0.0);
        }
    }
    float lastSumDis = 0.0;

    while(distort > 0){
        // get new centers
        float sumDis = 0;
        int num1 = 0, num2 = 0;
        for(int i=0; i<points.length(); ++i){
            float dis1 = 0, dis2 = 0;
            for(int j=0; j<3; ++j){
                dis1 += qPow(points[i][j]-centers[0][j], 2);
                dis2 += qPow(points[i][j]-centers[1][j], 2);
            }
            if(dis1 < dis2){
                for(int j=0; j<3; ++j)
                    clusters[0][j] += points[i][j];
                clusters[0][3] += 1;
                sumDis += dis1;
                num1 ++;
            }
            else{
                for(int j=0; j<3; ++j)
                    clusters[1][j] += points[i][j];
                clusters[1][3] += 1;
                sumDis += dis2;
                num2 ++;
            }
        }
        // calculate average centers
        for(int i=0; i<K; ++i)
            for(int j=0; j<3; ++j)
                if(clusters[i][3]>0)
                    centers[i][j] = clusters[i][j] /clusters[i][3];

        // here is dirty code, the one with less markers are the glove
        if(num1 < num2){
            result = centers[1];
        }
        else{
            result = centers[0];
        }
        //qDebug()<<num1<<num2;
        // set the cluster centers to 0
        for(int i=0; i<K; ++i){
            for(int j=0; j<4; ++j){
                clusters[i][j] = 0;
            }
        }
        distort = qPow(sumDis - lastSumDis, 2);
        lastSumDis = sumDis;

    }

    return result;
}
