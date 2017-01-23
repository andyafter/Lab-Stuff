#include "unityconnections.h"

UnityConnections::UnityConnections(QObject *parent) : QObject(parent)
{
    qDebug() << this << "created";
}

UnityConnections::~UnityConnections()
{
    qDebug() << this << "destroyed";
}

int UnityConnections::count()
{
    QReadWriteLock lock;
    lock.lockForRead();
    int value = m_connection.count();
    lock.unlock();

    return value;
}

void UnityConnections::removeSocket(QTcpSocket *socket)
{
    if(!socket ) return;
    if(!m_connection.contains(socket)) return;

    qDebug() << this << " removing socket = " << socket;
    if(socket->isOpen()){
        qDebug() << this << " socket is open, attempting to close it" << socket;
        socket->disconnect();
        socket->close();
    }
    qDebug() << this << " delete socket " << socket;
    m_connection.remove(socket);
    socket->deleteLater();

    // for verifying whether the socket has been deleted
    qDebug() << this << " client count = " << m_connection.count();
}

void UnityConnections::disconnected()
{
    if(!sender()) return;
    qDebug()<< this << "disconnecting socket" << sender();

    QTcpSocket *socket = static_cast<QTcpSocket*> (sender());
    if(!socket) return;

    removeSocket(socket);
}

void UnityConnections::error(QAbstractSocket::SocketError socketError)
{
    if(!sender()) return;
    qDebug() << this << " error in socket " << sender() << " error = " << socketError;
}

void UnityConnections::start()
{
    qDebug() << this << " connections started on " << QThread::currentThread();
}

void UnityConnections::quit()
{
    if(!sender()) return;
    qDebug() << this << " connections quitting ";

    foreach(QTcpSocket *socket, m_connection.keys()){
        qDebug()<< this << " closing socket " << socket;
        removeSocket(socket);
    }
    qDebug() << this << "finishing";
    emit finished();
}

void UnityConnections::accept(qintptr handle, UnityConnection *connection)
{
    QTcpSocket *socket = new QTcpSocket(this);

    if(!socket->setSocketDescriptor(handle)){
        qWarning() << this << " could not accept connection" << handle;
        // if you cannot connect, delete it later
        connection->deleteLater();
        return;
    }
    connect(socket, &QTcpSocket::disconnected, this, &UnityConnections::disconnected);
    connect(socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &UnityConnections::error);

    connection->moveToThread(QThread::currentThread());
    connection->setSocket(socket);
    m_connection.insert(socket, connection);
    qDebug() << this << "clients = " << m_connection.count();
    emit socket->connected();
}

void UnityConnections::sendToAllConnections(QString data)
{
    QByteArray sendData;    // it has to be a bytearray
    sendData.append(data);
    QMap<QTcpSocket*, UnityConnection*>::iterator i;
    for (i = m_connection.begin(); i != m_connection.end(); ++i){
        i.key()->write(sendData);
    }
}
