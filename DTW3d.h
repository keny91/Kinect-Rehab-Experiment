#include <vector>

#ifndef DTW_H
#define DTW_H

#include <vector>
#include <utility>
#include <cmath>
#include <iostream>     // std::cout
#include <algorithm> 

using namespace std;

namespace dtw3d {
	double DWT3d(const std::vector<double>& t1, const std::vector<double>& t2);
}

#endif