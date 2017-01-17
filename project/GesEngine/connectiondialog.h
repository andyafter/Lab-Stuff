#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QDebug>

#include "artclient.h"
//#include "gesserver.h"

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

private slots:
    void on_conStartBtn_clicked();

    void on_conStopBtn_clicked();

public slots:
    void connectART(QString address, int port);

private:
    Ui::ConnectionDialog *ui;
    ARTClient aclient;
    // GesServer ges;
};

#endif // CONNECTIONDIALOG_H
