#include "DTW3d.h"




	/*
	double dist(double x, double y, double z) {
		return sqrt(pow((x - y), 2));
	}
	*/

float dtw3d::dist(float x, float y) {
		return sqrt(pow((x - y), 2));
	}

	//double dtw3d::distV2(std::vector<double>&  V1, std::vector<double>& V2) {
	float dtw3d::distV2(float*  V1, float* V2, int sizeLenght){
		//int m = V1.size();
		//int n = V2.size();
		
		double* costs = new double[sizeLenght];
		//cout << m << "  and the other size is " << n << endl;
		//if (m == n) {
			for (int i = 0; i < sizeLenght; i++)
				costs[i]=dist(V1[i], V2[i]);
		//}			
		return sqrt(pow((costs[0]), 2) + pow((costs[1]), 2)+ pow((costs[2]), 2));
	}


	// doesnt matter the size of both t1 and t2 as long as they are the same
	double dtw3d::dtw3dcalulation(const std::vector<double>& t1, const std::vector<double>& t2) {
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





	// doesnt matter the size of both t1 and t2 as long as they are the same
	 //dtw3d::dtw3d( std::vector<vector<double>>& t1,  std::vector<vector<double>>& t2) {
	dtw3d::dtw3d(float** t1, float** t2, int sizet1, int sizet2) {
	//int m = t1.size();
	//int n = t2.size();
		int m = sizet1;
		int n = sizet2;
		//int j = t3.size();

		// create cost matrix
		//double cost[m][n];


		int** cost = new int*[m];
		for (int i = 0; i < m; i++)
			cost[i] = new int[n];


		cost[0][0] = distV2(t1[0], t2[0],3);

		// calculate first row
		for (int i = 1; i < m; i++)
			cost[i][0] = cost[i - 1][0] + distV2(t1[i], t2[0],3);
		// calculate first column
		for (int j = 1; j < n; j++)
			cost[0][j] = cost[0][j - 1] + distV2(t1[0], t2[j],3);
		// fill matrix  (Accumulates cost?)
		for (int i = 1; i < m; i++)
			for (int j = 1; j < n; j++)
				cost[i][j] = std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1]))
				+ distV2(t1[i], t2[j],3);

		theCost = cost[m - 1][n - 1];
		cout << theCost << "  is the cost." << endl;
	}

/*
	for (int i = 0; i < row; i++)
		delete[] cost[i];
	delete[] cost;
	*/
