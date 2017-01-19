#ifndef UNITYCONNECTION_H
#define UNITYCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class UnityConnection : public QObject
{
    Q_OBJECT
public:
    explicit UnityConnection(QObject *parent = 0);
    ~UnityConnection();

    virtual void setSocket(QTcpSocket *socket);

signals:

protected:
    QTcpSocket *m_socket;
    QTcpSocket *getSocket();

public slots:
    virtual void connected();
    virtual void disconnected();
    virtual void readyRead();
    virtual void bytesWritten(qint64 bytes);
    virtual void stateChanged(QAbstractSocket::SocketState socketState);
    virtual void error(QAbstractSocket::SocketError socketError);
};

#endif // UNITYCONNECTION_H
