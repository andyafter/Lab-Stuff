#ifndef UNITYSERVER_H
#define UNITYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThread>
#include "unityconnection.h"
#include "unityconnections.h"

class UnityServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit UnityServer(QObject *parent = 0);
    ~UnityServer();

    virtual bool listen(const QHostAddress &address, quint16 port );
    virtual void close();
    virtual qint16 port();

signals:
    void accepting(qintptr handle, UnityConnection *connection);
    void finished();

protected:
    QThread *m_thread;
    UnityConnections *m_connections;
    virtual void incomingConnection(qintptr handle); // qint64, qHandle, qintptr, uint
    virtual void accept(qintptr descriptor, UnityConnection *connection);

public slots:
    void complete();

};

#endif // UNITYSERVER_H
