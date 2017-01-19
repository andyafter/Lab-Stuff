#include "unityconnection.h"

UnityConnection::UnityConnection(QObject *parent) : QObject(parent)
{
    qDebug() << this << "Created!";
}

UnityConnection::~UnityConnection()
{
    qDebug() << this << "Destroyed!";

}

void UnityConnection::setSocket(QTcpSocket *socket)
{
    m_socket = socket;
    connect(m_socket, &QTcpSocket::connected, this, &UnityConnection::connected);
    connect(m_socket, &QTcpSocket::disconnected, this, &UnityConnection::disconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &UnityConnection::readyRead);
    connect(m_socket, &QTcpSocket::bytesWritten, this, &UnityConnection::bytesWritten);
    connect(m_socket, &QTcpSocket::stateChanged, this, &UnityConnection::stateChanged);
    // this line is a little tricky since you need to consider C++ cast problems
    // somehow it works this way
    connect(m_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QTcpSocket::error), this, &UnityConnection::error);
}

QTcpSocket *UnityConnection::get_socket()
{
    if(!sender()) return 0;
    return static_cast<QTcpSocket*>(sender());
}

void UnityConnection::connected()
{

}

void UnityConnection::disconnected()
{

}

void UnityConnection::readyRead()
{

}

void UnityConnection::bytesWritten(qint64)
{

}

void UnityConnection::stateChanged(QAbstractSocket::SocketState socketState)
{

}

void UnityConnection::error(QAbstractSocket::SocketError socketError)
{

}
