#ifndef ARTCLIENT_H
#define ARTCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QString>

class ARTClient : public QObject
{
    Q_OBJECT
public:
    explicit ARTClient(QObject *parent = 0);
    void extractMarkers(QString frame);
    void gestureLearning();
    void emitGestureEvent();
signals:

public slots:
    void readyRead();

protected:
    QUdpSocket *socket;
};

#endif // ARTCLIENT_H
