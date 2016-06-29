#pragma once


#ifndef RecordLog_H
#define RecordLog_H


#include <stdio.h>
//#include "SequentialUserCapture.h"
#include <iostream>
#include <fstream>
#include "NiTE.h"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2
using namespace std;
using namespace nite;

class RecordLog
{
public:

	RecordLog();
	RecordLog(char* name);
	~RecordLog();
	bool isRecording;
	int elapsedFrames;
	void StartRecording();
	void StopRecording();
	void InsertRegisterSkeleton(Skeleton theSkeleton, int frameint, int BodyID);
	//void InsertRegisterNTSkeleton(NTSkeleton theSkeleton);

	void StartReading();
	float**  ReadFrameRegisterToArray(string nameFile); // LINE BY LINE?
	void EndReading();
	void CreateEvaluationReport();
	void SeparateSingleJoint(JointType theType, bool recordPosition, bool recordOrientation, bool recordConfidence);
	Skeleton aSkeleton;

private:
	fstream theFile;
	char*name;
	JointType *JointList;
};

#endif // RecordLog_H