#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
}

ConnectionDialog::~ConnectionDialog()
{
    emit on_stop();
    delete ui;
}

void ConnectionDialog::on_conStartBtn_clicked()
{
    connect(&aclient, &ARTClient::on_number, this, &ConnectionDialog::connectART);
    connect(this, &ConnectionDialog::on_stop, &aclient, &ARTClient::stopRead);
    //connect(this, &ConnectionDialog::sendToUnity, &aclient, &ARTClient::sendUnity);

    QFuture<void> test = QtConcurrent::run(&this->aclient, &ARTClient::startReading);
}

void ConnectionDialog::on_conStopBtn_clicked()
{
    emit on_stop();
}

void ConnectionDialog::connectART(QString address, int port)
{
    ui->lineEdit->setText(address + "haha" + QString(port));
}

void ConnectionDialog::on_pushButton_clicked()
{
    qDebug()<< "here is something else";
    emit sendToUnity();
}
