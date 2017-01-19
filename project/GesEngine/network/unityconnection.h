#ifndef UNITYCONNECTION_H
#define UNITYCONNECTION_H

#include <QObject>

class UnityConnection : public QObject
{
    Q_OBJECT
public:
    explicit UnityConnection(QObject *parent = 0);

signals:

public slots:
};

#endif // UNITYCONNECTION_H