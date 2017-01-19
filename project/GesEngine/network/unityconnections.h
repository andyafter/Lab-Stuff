#ifndef UNITYCONNECTIONS_H
#define UNITYCONNECTIONS_H

#include <QObject>

class UnityConnections : public QObject
{
    Q_OBJECT
public:
    explicit UnityConnections(QObject *parent = 0);

signals:

public slots:
};

#endif // UNITYCONNECTIONS_H