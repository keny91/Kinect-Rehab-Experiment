#pragma once


#ifndef RecordLog_H
#define RecordLog_H


#include <stdio.h>
#include "SequentialUserCapture.h"
#include <iostream>
#include <fstream>

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
	void StartRecording();
	void StopRecording();
	void InsertRegisterSkeleton(Skeleton theSkeleton, int frameint, int BodyID);
	void InsertRegisterNTSkeleton(NTSkeleton theSkeleton);
	void ReadRegister(); // LINE BY LINE?

private:
	fstream theFile;
	char*name;

};

#endif // RecordLog_H