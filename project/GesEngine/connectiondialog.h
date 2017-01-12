#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QDebug>

#include "artclient.h"

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
    connectART(QString address, int port);

private:
    Ui::ConnectionDialog *ui;
    ARTClient aclient;
};

#endif // CONNECTIONDIALOG_H
