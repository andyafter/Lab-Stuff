#ifndef KMEANS_H
#define KMEANS_H

#include "cluster.h"

class KMeans
{    
private:
    int K; // number of clusters
    int total_values, total_points, max_iterations;
    vector<Cluster> clusters;
    int getIDNearestCenter(Point point);

public:
    KMeans();
    KMeans(int K, int total_points, int total_values, int max_iterations);
    void run(vector<Point> & points);

};

#endif // KMEANS_H
