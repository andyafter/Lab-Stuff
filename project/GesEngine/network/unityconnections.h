#ifndef UNITYCONNECTIONS_H
#define UNITYCONNECTIONS_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QMap>
#include <QReadWriteLock>
#include <unityconnection.h>

class UnityConnections : public QObject
{
    Q_OBJECT
public:
    explicit UnityConnections(QObject *parent = 0);
    ~UnityConnections();

    virtual int count();

protected:
    QMap<QTcpSocket*, UnityConnection*> m_connection;
    void removeSocket(QTcpSocket *socket);

signals:
    void quitting();
    void finished();

public slots:
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void start();
    void quit();
    void accept(qintptr handle, UnityConnection *connection);
};

#endif // UNITYCONNECTIONS_H
