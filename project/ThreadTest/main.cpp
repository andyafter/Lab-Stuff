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
#include <QtMath>

using namespace std;

void kmeans(QVector<QVector<float>> points){
    // consider only k==2
    int K = 2;

    // whether the function converges
    float distort = 1;

    // centers and cluster points
    QVector<QVector<float>> centers(K);
    QVector<QVector<float>> clusters(K);     // cluster is only the center position and how many points are there

    // this process should be generalized if you do k>2
    // c1 and c2 will later be used to store how many markers are there in a class(which is dirty but I prefer not to declaire too many variables)
    int c1 = qrand() % points.length();
    int c2 = qrand() % points.length();

    while(c2==c1){    // dirty stuff
        c2 = qrand();
    }

    centers[0] = points[c1];
    centers[1] = points[c2];

    qDebug() << centers;
    // initialize centers and find functions to erase everything from qvector

    for(int i=0; i<K; ++i){
        for(int j=0; j<4; ++j){
            clusters[i].append(0.0);
        }
    }

    float lastSumDis = 0.0;

    while(distort > 0){
        // get new centers
        float sumDis = 0;
        for(int i=0; i<points.length(); ++i){
            float dis1 = 0, dis2 = 0;
            for(int j=0; j<3; ++j){
                dis1 += qPow(points[i][j]-centers[0][j], 2);
                dis2 += qPow(points[i][j]-centers[1][j], 2);
            }
            if(dis1 < dis2){
                for(int j=0; j<3; ++j)
                    clusters[0][j] += points[i][j];
                clusters[0][3] += 1;
                sumDis += dis1;
                qDebug() << "distance 1" << dis1 << dis2;
            }
            else{
                for(int j=0; j<3; ++j)
                    clusters[1][j] += points[i][j];
                clusters[1][3] += 1;
                sumDis += dis2;
                qDebug() << "distance 2" << dis1 << dis2;
            }
        }
        // calculate average centers
        for(int i=0; i<K; ++i)
            for(int j=0; j<3; ++j)
                if(clusters[i][3]>0)
                    centers[i][j] = clusters[i][j] /clusters[i][3];

        qDebug() << clusters;

        // set the cluster centers to 0
        for(int i=0; i<K; ++i){
            for(int j=0; j<4; ++j){
                clusters[i][j] = 0;
            }
        }
        distort = qPow(sumDis - lastSumDis, 2);
        lastSumDis = sumDis;
        qDebug() << centers;
        qDebug() << points;
    }

    qDebug() << clusters << centers;
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

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    kmeans(points);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
    //return 0;
}
