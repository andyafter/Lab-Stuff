#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectiondialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionHome_triggered()
{
    qDebug()<<"triggered!" ;
    ConnectionDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}
