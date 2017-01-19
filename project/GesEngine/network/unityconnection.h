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
    QTcpSocket *get_socket;

public slots:
    virtual void connected();
    virtual void disconnected();
    virtual void byteWritten(qint64);
    virtual void stateChanged(QAbstractSocket::SocketState socketState);
    virtual void error(QAbstractSocket::SocketError socketError);
};

#endif // UNITYCONNECTION_H
