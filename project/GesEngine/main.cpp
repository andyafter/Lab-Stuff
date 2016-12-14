#include "mainwindow.h"
#include "artclient.h"
#include <QApplication>

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    ARTClient server;
    while(1){
        server.readyRead();
    }
    server.readyRead();
    return a.exec();
}
