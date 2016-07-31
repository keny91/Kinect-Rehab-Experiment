#pragma once


#ifndef COMPARE_H
#define COMPARE_H

#define NITE_JOINT_COUNT 15

#include <stdio.h>
//#include "SequentialUserCapture.h"
#include <iostream>
#include <fstream>
#include "NiTE.h"
#include <string>
#include <vector>
#include <sstream>
#include "DTW3d.h"
#include "RecordLog.h"

using namespace std;


//void ReadFrameRegisterToArray(char* nameFile, float ** theMatrix);

class Compare
{
public:
	Compare();
	Compare(char* nameSampleFile, char* nameGTFile);
	~Compare();
	void makeComparison(char* nameSampleFile, char* nameGTFile);
	bool GetJointSelection();
	void exitComparation();
	bool checkFileExistence(const char* name);
	
	void JointByJointCostCalculation();
	void GetLogDimensions(char* nameFile, int * rows, int* cols, Point3f theRelativePoint, float* RelativeDistance );
	//void ReadFrameRegisterToArrays(char* nameFile, float ** theMatrix);
	void GetReferenceMeasure(float value);
	void ApplyReferenceMeasure();

private:
	float Cost;
	bool * JointSelection;
	char*SampleName;  // name of the folder inside samples
	char*GTName;	// name of the folder storing the GT joint logs
	char*pathSampleFile;
	char*pathSGTFile;
	bool inProcess;
	ifstream GTFile;
	ifstream SampleFile;
	

	// other possible values here
};

#endif // COMPARE_H