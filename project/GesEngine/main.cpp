#include "mainwindow.h"
#include "artclient.h"

#include <QApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

#include <iostream>

using namespace std;

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    // ARTClient server;
    // while(1){
    //     server.readyRead();
    // }
    // server.readyRead();
    // ARTClient client;
    // client.extractMarkers("hello");
  
    return a.exec();
}
