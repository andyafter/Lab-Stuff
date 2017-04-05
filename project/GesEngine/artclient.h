#ifndef ARTCLIENT_H
#define ARTCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QThread>
#include <QtConcurrent>
#include <QtMath>
#include <QTcpServer>
#include <QTcpSocket>

#include <QTime>
#include <QtMath>
#include <QDateTime>

#include <time.h>

#include "kmeans.h"

class ARTClient : public QObject
{
    Q_OBJECT
public:
    explicit ARTClient(QObject *parent = 0);
    ~ARTClient();
    // reading data from udp
    void startReading();
    // extract information from frame data
    void extractMarkers(QString frame);
    // here is where you implement algorithms
    void gestureLearning();
    // communicate with Unity project
    void broadCaseGestureEvent();
    // online feature analysis, delete later
    QString features();

    QString getRawData() const;

    void setRawData(const QString &value);

    void sendUnity();

    QVector<float> kmeans(QVector<QVector<float>> points);

signals:
    //// understand and change this function
    ///  seems no implementation of this function
    void on_number(QString name, int number);
    void refreshMarkers(QString data);

public slots:
    // getting data from udp broadcast
    void readyRead();
    void stopRead();
    void newConnection();

protected:
    QUdpSocket *socket;
    QTcpSocket *sockUnity;

private:
    bool readStop;
    QString rawData;
    QVector<QVector<float>> markers;
    QVector<QVector<float>> prevMarkers;
    QVector<float> handCenter;
    QTcpServer *server;
};

#endif // ARTCLIENT_H
