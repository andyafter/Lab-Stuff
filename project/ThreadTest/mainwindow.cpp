#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    emit on_stop();
    delete ui;
}

void MainWindow::newNumber(QString name, int number)
{
    qDebug() << "From MainWindow: " << name << " " << number;
    ui->lineEdit->setText(name + " " + number);
}

void MainWindow::on_startBtn_clicked()
{
    //QT 5:
    connect(&mJob, &MyJob::on_number, this, &MainWindow::newNumber);
    connect(this, &MainWindow::on_stop, &mJob, &MyJob::stop);
    QFuture<void> test = QtConcurrent::run(&this->mJob, &MyJob::start, QString("kitten"));
}

void MainWindow::on_stopBtn_clicked()
{
    emit on_stop();
}
