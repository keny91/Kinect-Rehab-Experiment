#include "SequentialUserCapture.h"


/*
LIST TO DO:

- CHECK AND CREATE EXCEPTIONS FOR MULTIPLE BODIES -> ID based
- START ON GESTURE / INPUT / COUNTDOWN
- WHEN NO MORE BODIES AT SCENE/ USER UNDETECTED FOR A NUMBER OF FRAMES -> change ID

*/



/***************************************
CONSTRUCTORS/DESTRUCTORS
****************************************/ 


// Empty Constructor
SequentialUserCapture::SequentialUserCapture(){
	numberOfCapturedElements = 0; 
	PresentElement = -1;
	StoredSkeletons = NULL;
	LifeSpan = -1;
	ID = -11111;
}


SequentialUserCapture::SequentialUserCapture(int nElements, int focusedElement)
{
	numberOfCapturedElements = nElements;
	PresentElement = focusedElement;
	LifeSpan = 0;
	StoredSkeletons = new Skeleton*[nElements];
	ID = -1;
	// initialize the array
	for (int i = 0; i < nElements; i++)
		StoredSkeletons[i] = new Skeleton();

}


//// THIS MIGHT CAUSE FAILURE
SequentialUserCapture::~SequentialUserCapture()
{
	if (numberOfCapturedElements>0)
		for (int i = 0; i < numberOfCapturedElements; i++)
			delete StoredSkeletons[i];

	delete StoredSkeletons;
}


/***************************************
GET & SET ATTRIBUTES
****************************************/



/* 
setUserSkeletonAt:
	Given a position in the Skeleton array

*/

void SequentialUserCapture::setUserSkeletonAt(int position, Skeleton* theSkeleton){
	StoredSkeletons[position] = theSkeleton;
}

Skeleton* SequentialUserCapture::getUserSkeletonAt(int position) {
	return StoredSkeletons[position];
}

void SequentialUserCapture::setJointAt(int position, Skeleton *theSkeleton, JointType theJointType) {
	StoredSkeletons[position]->getJoint(theJointType) = theSkeleton->getJoint(theJointType);
}


void SequentialUserCapture::UpdateId(int newId){


}