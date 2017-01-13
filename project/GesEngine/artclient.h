#ifndef ARTCLIENT_H
#define ARTCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>
#include <QThread>
#include <QtConcurrent>

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

    QString getRawData() const;

    void setRawData(const QString &value);

signals:
    //// understand and change this function
    ///  seems no implementation of this function
    void on_number(QString name, int number);

public slots:
    // getting data from udp broadcast
    void readyRead();
    void stopRead();

protected:
    QUdpSocket *socket;

private:
    bool readStop;
    QString rawData;
};

#endif // ARTCLIENT_H
