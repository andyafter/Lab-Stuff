#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>

class MyServer : public QTcpServer
{
public:
    MyServer();
};

#endif // MYSERVER_H
