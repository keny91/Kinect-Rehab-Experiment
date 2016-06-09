#pragma once

#ifndef SkeletonJoint_H
#define SkeletonJoint_H


#include "Viewer.h"
using namespace nite;
#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2


// Skeleton Joints
class NTSkeletonJoint
{
public:

	JointType jointType;
	NitePoint3f position;
	float positionConfidence;
	NiteQuaternion orientation;
	float orientationConfidence;

	NTSkeletonJoint();
	~NTSkeletonJoint();
	void SetJointPosition(NitePoint3f pos, float conf);
	void SetJointOrientation(NiteQuaternion ori, float conf);
	void SetJoint(SkeletonJoint theJoint);
	void ClearJoint();
	void CopyFromNTSkeletonJoint(NTSkeletonJoint theSJoint);
	
};
#endif // SkeletonJoint_H





#ifndef Skeleton_H
#define Skeleton_H
	
#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2
#include "Viewer.h"
using namespace nite;

class NTSkeleton
{
public:

	NTSkeletonJoint* joints;
	NiteSkeletonState state;
	//SkeletonState state;
	JointType *JointList;

	int GetJointLocationInArray(JointType theJointType);
	void setJointAt(Skeleton*theSkeleton, JointType theJointTyper);
	NTSkeleton();
	~NTSkeleton();
	NiteSkeletonState NTSkeleton::ConversionStateSkelly2Nite(SkeletonState status);
	void SetSkelletonNull();
	void CopyFromNTSkeleton(NTSkeleton *theSkeleton);
};
#endif // Skeleton_H


#ifndef SequentialUserCapture_H
#define SequentialUserCapture_H


#define NITE_JOINT_COUNT 15
#define NITE_POSE_COUNT 2
#define KEY_FRAME 4
#define NUMBER_OF_FRAMES 7


#include "Viewer.h"
using namespace nite;
class SequentialUserCapture
{
public:
	SequentialUserCapture();
	SequentialUserCapture(int nElements, int focusedElement, int theId);
	~SequentialUserCapture();
	//struct NTSkeleton** StoredSkeletons;
	NTSkeleton** StoredSkeletons;
	NiteUserId id;
	int state;
	


protected:
	//JointType *JointList;
	void setUserSkeletonAt(int position, Skeleton *theSkeleton);
	
	NTSkeleton* getUserSkeletonAt(int position);
	void UpdateId(int newId);
	void CopySkeletonToPosition(int position, Skeleton *theSkeleton);
	void OnNextFrameArrival(Skeleton *theSkeleton);
	void SetSkelletonNullAt(int skeletonPost);
	

private:
	int numberOfCapturedElements;
	int PresentElement;
	SampleViewer * theViewer;
	//Skeleton ** StoredSkeletons;
	int LifeSpan;
	int ID;
	




};

#endif // SequentialUserCapture_H