#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QDebug>

#include "artclient.h"
#include "unityserver.h"

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

signals:
    void on_stop();
    void sendToUnity(QString data);

private slots:
    void on_conStartBtn_clicked();

    void on_conStopBtn_clicked();

    void on_pushButton_clicked();

public slots:
    void connectART(QString address, int port);

private:
    Ui::ConnectionDialog *ui;
    ARTClient aclient;
    UnityServer m_server;
};

#endif // CONNECTIONDIALOG_H
