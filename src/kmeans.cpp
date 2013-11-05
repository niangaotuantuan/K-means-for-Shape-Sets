#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <sstream>
#include <cmath>
#include <string>
#include "kmeans.h"

using namespace std;


DataPoint::DataPoint(const vector<double> & vv, double w): coords(vv), weight(w)
{}

string DataPoint::print()
{
    stringstream s;
    for (int i=0; i<coords.size(); ++i)
        s << coords[i] << " ";
    s << "\t: " << weight;
    return s.str();
}


double locdistance(const DataPoint &p1, const DataPoint &p2)
{
    assert(p1.coords.size() == p2.coords.size());

    double res=0;
    for (int i=0; i<p1.coords.size(); ++i)
    {
        res += pow(p1.coords[i] - p2.coords[i], 2.0);
    }
    return res;

    return 0.0;
}

bool evaluateCond(const vector<DataPoint> &old_centroids,
                  const vector<DataPoint> &new_centroids, double error)
{
    assert(old_centroids.size() == new_centroids.size());

    for (int i=0; i<old_centroids.size(); ++i)
    {
        if (sqrt(locdistance(old_centroids[i], new_centroids[i])) >= error)
            return false;
    }
    return true;
}

Cluster::Cluster(const DataPoint& centroid): _centroid(centroid){}

void Cluster::push(const DataPoint &p)
{
    _points.push_back(p);
}

void Cluster::updateCentroid()
{
    vector<double> zero(_centroid.coords.size(),0.0);
    DataPoint new_centroid(zero,0.0);
    for (int j=0; j<_points.size(); ++j)
    {
        for (int i=0; i<_points[j].coords.size(); ++i)
        {
            new_centroid.coords[i] += _points[j].coords[i] / (double)_points.size();
        }
        new_centroid.weight += _points[j].weight;
    }
    _centroid = new_centroid;
}

void Cluster::clear()
{
    _points.clear();
}

Kmeans::Kmeans(int number_of_cluster,const vector<DataPoint>& data_set)
    : _data_set(data_set), _number_of_clusters(number_of_cluster)
{
    _initialize();

}

DataPoint Cluster::getCentroid()
{
    return _centroid;
}

void Kmeans::_initialize()
{
    for (size_t i=0; i<_number_of_clusters; ++i)
    {
        int centroid_id = rand() % (int)_data_set.size();
        _clusters.push_back(_data_set[centroid_id]);
    }
}

void Kmeans::perform(double error)
{
    int counter=0;
    bool done = true;
    do
    {
        cout << "\niteration " << ++counter;
        vector<DataPoint> old_centroids = _getCentroids();
        _performIter();
        vector<DataPoint> new_centroids = _getCentroids();
        done = evaluateCond(old_centroids, new_centroids, error);
    } while (!done);

}

vector<DataPoint> Kmeans::_getCentroids()
{
    vector<DataPoint> res ;
    for (int i=0; i<_clusters.size(); ++i)
    {
        res.push_back(_clusters[i].getCentroid());
    }
    return res;
}

void Kmeans::_performIter()
{
    _clearClusters();
    for (int j=0; j<_data_set.size(); ++j)
    {
        _clusters[_findNearestCluster(_data_set[j])].push(_data_set[j]);
    }
    _updateCentroids();

}
void Kmeans::_clearClusters()
{
    for (int i=0; i<_clusters.size(); ++i)
    {
        _clusters[i].clear();
    }
}

int Kmeans::_findNearestCluster(const DataPoint &p)
{
    int nearest_cluster_id = -1;
    double nearest_dist = 1e16;
    for (int cluster_id=0; cluster_id<_clusters.size(); ++cluster_id)
    {
        double cur_dist = locdistance(p,_clusters[cluster_id].getCentroid());
        if (cur_dist < nearest_dist)
        {
            nearest_dist = cur_dist;
            nearest_cluster_id = cluster_id;
        }
    }
    return nearest_cluster_id;
}

void Kmeans::_updateCentroids()
{
    for (int i=0; i<_clusters.size(); ++i)
    {
        _clusters[i].updateCentroid();
    }
}

double Kmeans::totalWeight()
{
    double res=0;
    for (int i=0; i<_clusters.size(); ++i)
    {
        res += _clusters[i].getCentroid().weight;
    }
    return res;
}

void Kmeans::print()
{
	cout << "\n\n The k-means clustering results are as follows, [centroid, weight]" << endl;
    for (int i=0; i<_clusters.size(); ++i)
    {
        cout << "\n\n" << _clusters[i].getCentroid().print() << endl;
    }
}
