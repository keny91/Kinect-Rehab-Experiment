#include "DTW3d.h"




#include "DTW3d.h"

namespace dwt3d {

	/*
	double dist(double x, double y, double z) {
		return sqrt(pow((x - y), 2));
	}
	*/

	double dist(double x, double y) {
		return sqrt(pow((x - y), 2));
	}

	// doesnt matter the size of both t1 and t2 as long as they are the same
	double dtw3d(const std::vector<double>& t1, const std::vector<double>& t2) {
		int m = t1.size();
		int n = t2.size();
		//int j = t3.size();

		// create cost matrix
		//double cost[m][n];


		int** cost = new int*[m];
		for (int i = 0; i < m; i++)
			cost[i] = new int[n];


		cost[0][0] = dist(t1[0], t2[0]);

		// calculate first row
		for (int i = 1; i < m; i++)
			cost[i][0] = cost[i - 1][0] + dist(t1[i], t2[0]);
		// calculate first column
		for (int j = 1; j < n; j++)
			cost[0][j] = cost[0][j - 1] + dist(t1[0], t2[j]);
		// fill matrix  (Accumulates cost?)
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				cost[i][j] = std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1]))
				+ dist(t1[i], t2[j]);

		return cost[m - 1][n - 1];
	}
/*
	for (int i = 0; i < row; i++)
		delete[] cost[i];
	delete[] cost;
	*/
}