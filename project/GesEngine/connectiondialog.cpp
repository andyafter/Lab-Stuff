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
    qDebug()<<"here is something!";
    connect(&aclient, &ARTClient::on_number, this, &ConnectionDialog::connectART);
    connect(this, &ConnectionDialog::on_stop, &aclient, &ARTClient::stopRead);
    QFuture<void> test = QtConcurrent::run(&this->aclient, &ARTClient::startReading);
}

void ConnectionDialog::on_conStopBtn_clicked()
{
    emit on_stop();
}

ConnectionDialog::connectART(QString address, int port)
{
    qDebug() << "From MainWindow: ";
    ui->lineEdit->setText(address + "haha" + QString(port));
}
