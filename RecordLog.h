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
#include <windows.h>
#include <direct.h>


#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2
using namespace std;
using namespace nite;


bool checkFileExistence(const char* name);

class RecordLog
{
public:

	RecordLog();
	RecordLog(char* name, bool recordPost = false);
	~RecordLog();
	bool isRecording;
	int elapsedFrames;
	void StartRecording();
	void StopRecording();
	void InsertRegisterSkeleton(Skeleton theSkeleton, int frameint, int BodyID);
	Point3f GetRelativePosition(SkeletonJoint Origin, SkeletonJoint Target);
	//void InsertRegisterNTSkeleton(NTSkeleton theSkeleton);

	void StartReading();
	void ReadFrameRegisterToArray(char* nameFile, float ** theMatrix); 
	void EndReading();
	void SeparateSingleJoint(JointType theType, char * directory,bool recordPostFix, bool recordPosition, bool recordOrientation, bool recordConfidence);
	void GetLogDimensions(char* nameFile, int * rows, int* cols);
	void CreateGestureLog(char* FileName, bool GT);
	void EnableRecordingOfJoint(JointType theType);
	void DisableRecordingOfJoint(JointType theType);
	void ChangeName(char* name);
	Skeleton aSkeleton;

private:
	void RecordLog::InitFolders();
	fstream theFile;
	char*name;
	bool * JointSelection;
	bool recordPostFix;
	JointType *JointList;
};

#endif // RecordLog_H