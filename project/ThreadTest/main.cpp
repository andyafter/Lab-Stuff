#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "myjob.h"

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include <QTime>

using namespace std;

void kmeans(QVector<QVector<float>> points){
    // consider only k==2
    int K = 2;

    // whether the function converges
    float distort = -1;

    // centers and cluster points
    QVector<QVector<float>> centers(K);
    QVector<QVector<float>> centersTemp(K);     // storing the temporary values for
    QVector<QVector<QVector<float>>> clusters(K);

    // this process should be generalized if you do k>2
    // c1 and c2 will later be used to store how many markers are there in a class(which is dirty but I prefer not to declaire too many variables)
    int c1 = qrand() % points.length();
    int c2 = qrand() % points.length();

    while(c2==c1){    // dirty stuff
        c2 = qrand();
    }

    centers[0] = points[c1];
    centers[1] = points[c2];
    // initialize centers and find functions to erase everything from qvector
    for(int i=0; i<points.length(); ++i){
        float dis1, dis2 = 0;
        for(int i=0; i<points.length(); ++i){
            dis1 += (points[i][j]-centers[0][j])^2;
            dis2 += (points[i][j]-centers[1][j])^2;
        }
        if(dis1<dis2){

        }
        else{

        }
    }


}

int main(int argc, char *argv[])
{
    QVector<QVector<float>> points;
    QVector<float> p(3);
    p[0] = 1.0;
    p[1] = 1.0;
    p[2] = 1.0;
    points.append(p);

    p[0] = 2.0;
    p[1] = 2.0;
    p[2] = 2.0;
    points.append(p);

    p[0] = 3.0;
    p[1] = 3.0;
    p[2] = 1.0;
    points.append(p);

    p[0] = 4.0;
    p[1] = 3.0;
    p[2] = 2.0;
    points.append(p);

    p[0] = 5.0;
    p[1] = 1.0;
    p[2] = 2.0;
    points.append(p);

    p[0] = 1.0 + 1000;
    p[1] = 1.0;
    p[2] = 1.0;
    points.append(p);

    p[0] = 2.0 + 1000;
    p[1] = 2.0;
    p[2] = 2.0;
    points.append(p);

    p[0] = 3.0 + 1000;
    p[1] = 3.0;
    p[2] = 1.0;
    points.append(p);

    p[0] = 4.0 + 1000;
    p[1] = 3.0;
    p[2] = 2.0;
    points.append(p);

    p[0] = 5.0 + 1000;
    p[1] = 1.0;
    p[2] = 2.0;
    points.append(p);

    qDebug() << points;

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    for(int i=0; i<100; i++){
        qDebug() << qrand()% 10;
    }

    kmeans(points);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    //return 0;
}
