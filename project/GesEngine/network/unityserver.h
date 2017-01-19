#ifndef UNITYSERVER_H
#define UNITYSERVER_H

#include <QObject>

class UnityServer : public QObject
{
    Q_OBJECT
public:
    explicit UnityServer(QObject *parent = 0);

signals:

public slots:
};

#endif // UNITYSERVER_H