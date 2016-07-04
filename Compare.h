#pragma once


#ifndef COMPARE_H
#define COMPARE_H

#define NITE_JOINT_COUNT 15

#include <iostream>
#include <fstream>
#include "NiTE.h"
#include <string>
#include <vector>
#include <sstream>

class Compare
{
public:
	Compare(char* nameSample, char* nameGT);
	~Compare();
	void initInfo();
	void GetJointSelection();
	bool CheckJointCompatibility();

private:
	long Cost;
	bool * JointSelection;
	char*SampleName;  // name of the folder inside samples
	char*GTName;	// name of the folder storing the GT joint logs
	char*path;
	// other possible values here
};

#endif // COMPARE_H