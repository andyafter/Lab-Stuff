#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->conStopBtn->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

ConnectionDialog::~ConnectionDialog()
{
    emit on_stop();
    delete ui;
}

void ConnectionDialog::on_conStartBtn_clicked()
{
    // connect(&aclient, &ARTClient::on_number, this, &ConnectionDialog::connectART);
    connect(this, &ConnectionDialog::on_stop, &aclient, &ARTClient::stopRead);
    //connect(this, &ConnectionDialog::sendToUnity, &aclient, &ARTClient::sendUnity);

    connect(&aclient, &ARTClient::refreshMarkers, &m_server, &UnityServer::artClientData);
    QFuture<void> test = QtConcurrent::run(&this->aclient, &ARTClient::startReading);

    // protect the procedure
    ui->conStartBtn->setEnabled(false);
    ui->conStopBtn->setEnabled(true);
    ui->pushButton->setEnabled(true);

    if(m_server.listen(QHostAddress::Any, 1234)){
        qDebug() << this << " server started ";
    }
    else{
        qCritical() << m_server.errorString();
    }
}

void ConnectionDialog::on_conStopBtn_clicked()
{
    emit on_stop();
    ui->conStartBtn->setEnabled(true);
    ui->conStopBtn->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void ConnectionDialog::connectART(QString address, int port)
{
    //ui->lineEdit->setText(address + "haha" + QString(port));
    // save this function for some input from hand
}

void ConnectionDialog::on_pushButton_clicked()
{
    emit aclient.refreshMarkers("from push button event");
}
