#ifndef GESSERVER_H
#define GESSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class GesServer : public QObject
{
    Q_OBJECT
public:
    explicit GesServer(QObject *parent = 0);

signals:

public slots:
    // seems that this function was defined inside qt and it is a signal
    void newConnection();

    void stopConnection();

private:
    QTcpServer *server;
    bool conStop;

};

#endif // GESSERVER_H
