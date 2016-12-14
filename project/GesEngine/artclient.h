#ifndef ARTCLIENT_H
#define ARTCLIENT_H

#include <QObject>
#include <QUdpSocket>

class ARTClient : public QObject
{
    Q_OBJECT
public:
    explicit ARTClient(QObject *parent = 0);

signals:

public slots:
    void readyRead();

protected:
    QUdpSocket *socket;
};

#endif // ARTCLIENT_H
