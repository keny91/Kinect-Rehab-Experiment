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
#include "FileHandler.h"


#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2
using namespace std;
using namespace nite;

//Additional Functions in AdditionalFunctions.cpp
bool checkFileExistence(const char* name);
char *Int2JointIndexing(int n);
Point3f GetRelativePosition(Point3f Origin, Point3f Target);
void ReadFrameRegisterToArray(char* nameFile, float ** theMatrix, bool alt);
//float GetDistanceBetweenJoints(nite::SkeletonJoint JointA, nite::SkeletonJoint JointB);

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
	//void InsertRegisterNTSkeleton(NTSkeleton theSkeleton);

	void StartReading();
	//void ReadFrameRegisterToArray(char* nameFile, float ** theMatrix); 
	void EndReading();
	void SeparateSingleJoint(JointType theType, char * directory, Point3f theRelativePoint, bool recordPostFix, bool recordPosition, bool recordOrientation, bool recordConfidence);
	void GetLogDimensions(char* nameFile, int * rows, int* cols, bool alt = true);
	void CreateGestureLog(char* FileName, bool GT, Point3f RelativePoint);
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