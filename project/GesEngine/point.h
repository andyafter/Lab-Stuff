#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Point
{
private:
    int id_point, id_cluster;
    vector<double> values;
    int total_values;
    string name;

public:
    Point(int id_point, vector<double>& values, string name = "");

    Point();

    int getID();

    void setCluster(int id_cluster);

    int getCluster();

    double getValue(int index);

    int getTotalValues();

    void addValue(double value);

    string getName();
};

#endif // POINT_H
