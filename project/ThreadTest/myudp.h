#ifndef MYUDP_H
#define MYUDP_H

#include <QUdpSocket>


class MyUDP : public QObject
{
    Q_OBJECT
public:
    explicit MyUDP(QObject *parent = 0);

signals:

public slots:
};

#endif // MYUDP_H
