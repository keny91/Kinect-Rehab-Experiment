

#ifndef DTW_H
#define DTW_H

#include <vector>
#include <utility>
#include <cmath>
#include <iostream>     // std::cout
#include <algorithm> 

using namespace std;

class dtw3d
{
public:
	double dtw3dcalulation(const std::vector<double>& t1, const std::vector<double>& t2);  //old implementation
	//dtw3d(std::vector<vector<double>>& t1, std::vector<vector<double>>& t2);
	dtw3d(float** t1, float** t2, int Sizet1, int sizet2);
	float dist(float x, float y);
	//double distV2(std::vector<double>&  V1, std::vector<double>& V2);
	float distV2(float* V1, float* V2, int sizeLenght);

	float theCost;
};

#endif // DTW_H