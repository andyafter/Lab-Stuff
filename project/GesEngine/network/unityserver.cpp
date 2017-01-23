#include "unityserver.h"

UnityServer::UnityServer(QObject *parent) : QTcpServer(parent)
{
    qDebug() << this << " created " << QThread::currentThread();
}

UnityServer::~UnityServer()
{
    qDebug() << this << " destroyed ";
}

bool UnityServer::listen(const QHostAddress &address, quint16 port)
{
    if(!QTcpServer::listen(address, port)) return false;

    m_thread = new QThread(this);
    m_connections = new UnityConnections();

    connect(m_thread, &QThread::started, m_connections, &UnityConnections::start, Qt::QueuedConnection);
    connect(this, &UnityServer::accepting, m_connections, &UnityConnections::accept, Qt::QueuedConnection);
    // hey, stop all the connections, now!!!
    connect(this, &UnityServer::finished, m_connections, &UnityConnections::quit, Qt::QueuedConnection);
    connect(m_connections, &UnityConnections::finished, this, &UnityServer::complete, Qt::QueuedConnection);

    // threading done correctly in qt(read this article)
    m_connections->moveToThread(m_thread);
    m_thread->start(); // the first connect gets trigerred instantly

    return true;
}

void UnityServer::close()
{
    qDebug() << this << " closing server ";
    emit finished(); // the finish connect will be triggered
    QTcpServer::close();

}

qint16 UnityServer::port()
{
    if(!isListening()){
        return this->serverPort();
    }
    else{
        return 1000;
    }
}

void UnityServer::incomingConnection(qintptr descriptor)
{
    qDebug() << this << " attempting to accept connection " << descriptor;
    UnityConnection *connection = new UnityConnection(); // this is no parent this time(no this)
    // out on the heap by itself

    accept(descriptor, connection);

}

void UnityServer::accept(qintptr descriptor, UnityConnection *connection)
{
    qDebug() << this << " accepting the connection " << descriptor;
    connection->moveToThread(m_thread);
    emit accepting(descriptor, connection);
}

void UnityServer::complete()
{
    if(!m_thread){
        qWarning() << this << " exiting complete there was no thread! ";
        return;
    }

    qDebug() << this << " complete called, detroying thread";
    delete m_connections;

    qDebug() << this << " quiting thread" ;
    m_thread->quit();
    m_thread->wait();

    delete m_thread;

    qDebug() << this << " complete ";
}

void UnityServer::artClientData(QString data)
{
    qDebug() << "test success" << data;
}
