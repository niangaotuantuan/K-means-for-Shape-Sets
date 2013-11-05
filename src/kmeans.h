
#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
using namespace std;

struct DataPoint {
     vector<double> coords;
     double weight;
     DataPoint(const vector<double> & ,double);
     DataPoint(){};
     string print();
};


class Cluster {
public:
     Cluster(const DataPoint &);
private:
     vector<DataPoint> _points;
     DataPoint _centroid;
public:
     void updateCentroid();
     void setCentroid(const DataPoint&);
     DataPoint getCentroid();
     void push(const DataPoint &);
     void clear();
};


class Kmeans {
public:
     Kmeans(int number_of_cluster,const vector<DataPoint>&);
     
private:
     vector<DataPoint> _data_set;
     vector<Cluster> _clusters;
     int _number_of_clusters;
     
public:
     void perform(double);
     double totalWeight();
     void print();
private:
     void _initialize();
     void _performIter();
     int _findNearestCluster(const DataPoint &);
     void _updateCentroids();
     void _clearClusters();
     vector<DataPoint> _getCentroids();
     

};





#endif