#include "gesserver.h"

GesServer::GesServer(QObject *parent) : QObject(parent)
{
    conStop = false;
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if(!server->listen(QHostAddress::Any, 1234)){
        qDebug() << "Server could not start!";
    }
    else{
        qDebug() << "Server Started!";
    }
}

void GesServer::newConnection()
{
    QTcpSocket *sock = server->nextPendingConnection();
    sock->write("hello world!!");
    sock->flush();
    sock->waitForBytesWritten(3000);
    sock->close();
}

void GesServer::stopConnection()
{
    conStop = true;
}
