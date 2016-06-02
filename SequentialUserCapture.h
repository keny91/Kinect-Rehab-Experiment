#pragma once
#ifndef SequentialUserCapture_H
#define SequentialUserCapture_H

#include "Viewer.h"

using namespace nite;

class SequentialUserCapture
{

public:
	SequentialUserCapture();
	SequentialUserCapture(int nElements, int focusedElement);
	~SequentialUserCapture();

protected:
	void setUserSkeletonAt(int position, Skeleton *theSkeleton);
	void setJointAt(int position, Skeleton*theSkeleton, JointType theJointTyper);
	Skeleton* getUserSkeletonAt(int position);
	void UpdateId(int newId);

private:
	int numberOfCapturedElements;
	int PresentElement;
	SampleViewer * theViewer;
	Skeleton ** StoredSkeletons;
	int LifeSpan;
	int ID;
	




};

#endif // SequentialUserCapture_H