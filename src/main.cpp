#include <iostream>
#include <cmath>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include "kmeans.h"

using namespace std;



void  giveRandPoints(vector<DataPoint>& res,int N,int D)
{
     srand (time_t(NULL));
     for (int i=0;i<N;++i)
          {
          DataPoint curp;
          for (int j=0;j<D;++j)
               {
               curp.coords.push_back(double(rand()) / double(RAND_MAX));
               }
          curp.weight=1.0;//(-1.0 + 2.0 * double(rand()) / double(RAND_MAX)) * 100.0;
          res.push_back(curp);
          
          }
}

/*TEST(kmeans_test,initial)
{
     int dim = 2;
     int N =1000;
     int clust_num = 9;
     vector<DataPoint> all_points;
     giveRandPoints(all_points,N, dim);
     Kmeans my_kmeans(clust_num,all_points);
     my_kmeans.perform(1e-15);
     my_kmeans.print();
     EXPECT_EQ(my_kmeans.totalWeight(),N);
}*/



int main(int argc, char**argv)
{
     int dim = 2;
     int N =600;
     int clust_num = 15;
	 double x;
     vector<DataPoint> all_points;

	 string dummy;
	 cout << "Begin Reading Data from R15.txt: ";
	 //cin >> dummy;
	 dummy = "R15.txt";
	 ifstream input;
	 input.open(dummy.c_str());
	 if(!input.is_open()) {
		cerr << "Sorry, but your file is in another castle\n";
	 }
	
	//Initialize reading data
	for (int i=0;i<N;++i){
          DataPoint curp;
          for (int j=0;j< dim;++j){
				input >> x;
                curp.coords.push_back(x);
          }
          curp.weight=1.0;//(-1.0 + 2.0 * double(rand()) / double(RAND_MAX)) * 100.0;
          all_points.push_back(curp);
          
    }
    // giveRandPoints(all_points,N, dim);
	
     Kmeans my_kmeans(clust_num,all_points);
     my_kmeans.perform(1e-15);
     my_kmeans.print();
	 system("pause");
     return 0;
}
