#include "SequentialUserCapture.h"


/*
LIST TO DO:

- CHECK AND CREATE EXCEPTIONS FOR MULTIPLE BODIES -> ID based
- START ON GESTURE / INPUT / COUNTDOWN
- WHEN NO MORE BODIES AT SCENE/ USER UNDETECTED FOR A NUMBER OF FRAMES -> change ID

*/



/*     15 total
HEAD
LEFT_ELBOW
LEFT_FOOT
LEFT_HAND
LEFT_HIP
LEFT_KNEE
LEFT_SHOULDER
NECK
RIGHT_ELBOW
RIGHT_FOOT
RIGHT_HAND
RIGHT_HIP
RIGHT_KNEE
RIGHT_SHOULDER
TORSO
*/


/*STRUCTS
typedef struct   // OVERRIDE???
{
public:

	JointType jointType;
	NitePoint3f position;
	float positionConfidence;
	NiteQuaternion orientation;
	float orientationConfidence;
} NTSkeletonJoint;


typedef struct : public Skeleton
{
public:
	NTSkeletonJoint joints[NITE_JOINT_COUNT];
	//NiteSkeletonState state;
	SkeletonState state;
} NTSkeleton;

*/


/*******************
SKELETON:
**********************/

NTSkeleton::NTSkeleton() {
	// IDEALLY you want this list to be outside the Object
	// Create a List of the possible Joints

	joints = new NTSkeletonJoint[NITE_JOINT_COUNT]();
	state = NITE_SKELETON_NONE;
	//state = nite::SKELETON_NONE;
	
	JointList = new JointType[NITE_JOINT_COUNT]();
	JointList[0] = JOINT_HEAD;
	JointList[1] = JOINT_LEFT_ELBOW;
	JointList[2] = JOINT_LEFT_FOOT;
	JointList[3] = JOINT_LEFT_HAND;
	JointList[4] = JOINT_LEFT_HIP;
	JointList[5] = JOINT_LEFT_KNEE;
	JointList[6] = JOINT_LEFT_SHOULDER;
	JointList[7] = JOINT_NECK;
	JointList[8] = JOINT_RIGHT_ELBOW;
	JointList[9] = JOINT_RIGHT_FOOT;
	JointList[10] = JOINT_RIGHT_HAND;
	JointList[11] = JOINT_RIGHT_HIP;
	JointList[12] = JOINT_RIGHT_KNEE;
	JointList[13] = JOINT_RIGHT_SHOULDER;
	JointList[14] = JOINT_TORSO;

	for (int count = 0; count < NITE_JOINT_COUNT; count++) {
		joints[count].jointType = JointList[count];
	}

}


NTSkeleton::~NTSkeleton() {

}

/***ConversionStateSkelly2Nite:************************************

	Convert from "SkeletonState" to "NiteSkeletonState"
	required to avoid linker errors.
*******************************************************************/

NiteSkeletonState NTSkeleton::ConversionStateSkelly2Nite(SkeletonState status) {
	NiteSkeletonState theStatus;
	switch (status) {
	case(SKELETON_NONE):
		theStatus = NITE_SKELETON_NONE;
		break;

	case(SKELETON_CALIBRATING):
		theStatus = NITE_SKELETON_CALIBRATING;
		break;

	case(SKELETON_TRACKED):
		theStatus = NITE_SKELETON_TRACKED;
		break;


		// ... MORE STATES REQUIRED


	default:
		theStatus = NITE_SKELETON_NONE;
	}
		
	return theStatus;

}


/* GetJointLocationInArray:

In our storing method
*/
int NTSkeleton::GetJointLocationInArray(JointType theJointType) {
	for (int counter = 0; counter < NITE_JOINT_COUNT; counter++) {
		if (joints[counter].jointType == theJointType)
			return counter;
	}
	return -1;
}


/*
setJointAt:
Given a skeleton and the concrete joint we want to set.
*/
void NTSkeleton::setJointAt( Skeleton *theSkeleton, JointType theJointType) {
	//NTSkeletonJoint AJoint = NTSkeletonJoint();
	int locationInArray = GetJointLocationInArray(theJointType);
	joints[locationInArray].SetJoint(theSkeleton->getJoint(theJointType));

}



/***SetFromNTSkeleton:********************************************
	Copy a NTSkeleton from another already existing.
	Just mimic all parameter´s values
*******************************************************************/

void NTSkeleton::CopyFromNTSkeleton(NTSkeleton *theSkeleton) {
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		joints[i].CopyFromNTSkeletonJoint(theSkeleton->joints[i]);
	state = NITE_SKELETON_NONE;
	

}



/*
SetSkelletonNull:
Clear the data in a skeleton.
*/
void NTSkeleton::SetSkelletonNull() {
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		joints[i].ClearJoint();
	state = NITE_SKELETON_NONE;
}





/*********************
	SKELETON_JOINT:	  
**********************/

/* Empty Constructor*/
NTSkeletonJoint::NTSkeletonJoint() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	orientation.x = 0;
	orientation.y = 0;
	orientation.z = 0;
	orientation.w = 0;

}

void NTSkeletonJoint::SetJointPosition(NitePoint3f pos, float conf) {
	position = pos;
	positionConfidence = conf;
}

void NTSkeletonJoint::SetJointOrientation(NiteQuaternion ori, float conf) {
	orientationConfidence = conf;
	orientation = ori;
}

void NTSkeletonJoint::SetJoint(SkeletonJoint theJoint) {
	jointType = theJoint.getType();
	SetJointOrientation(theJoint.getOrientation(), theJoint.getOrientationConfidence());
	SetJointPosition(theJoint.getPosition(), theJoint.getPositionConfidence());
}



/***CopyFromNTSkeletonJoint:********************************************
Copies Orientation, Position, Confidences from
another NTSkeletonJoint to the one from where it´s called 
*******************************************************************/
void NTSkeletonJoint::CopyFromNTSkeletonJoint(NTSkeletonJoint theSJoint) {
	if (jointType == theSJoint.jointType) {
		position.x = theSJoint.position.x;
		position.y = theSJoint.position.y;
		position.z = theSJoint.position.z;

		orientation.x = theSJoint.orientation.x;
		orientation.y = theSJoint.orientation.y;
		orientation.z = theSJoint.orientation.z;
		orientation.w = theSJoint.orientation.w;
		orientationConfidence = theSJoint.orientationConfidence;
		positionConfidence = theSJoint.positionConfidence;

	}
	else {
		// ERROR MESSAGE HERE
	}
}


/***ClearJoint:***************************************************
Clears Orientation, Position, Confidences
BUT NOT TYPE of the Joint
*******************************************************************/

void NTSkeletonJoint::ClearJoint() {
	position.x = 0;
	position.y = 0;
	position.z = 0;

	orientation.x = 0;
	orientation.y = 0;
	orientation.z = 0;
	orientation.w = 0;
	orientationConfidence = -1;
	positionConfidence = -1;

}



NTSkeletonJoint::~NTSkeletonJoint() {

}






/***************************************
SequentialUserCapture
****************************************/ 


// Empty Constructor
SequentialUserCapture::SequentialUserCapture(){
	numberOfCapturedElements = 0; 
	PresentElement = -1;
	//NTSkeleton* Skelly = new NTSkeleton;
	//Skelly->joints[0].position.x = 3;   // IT WORKS0
	StoredSkeletons = NULL;
	LifeSpan = -1;
	ID = -11111;
}


SequentialUserCapture::SequentialUserCapture(int nElements, int focusedElement)
{
	// initialize the array
	StoredSkeletons = new NTSkeleton *[nElements]();
	for (int i = 0; i < nElements; i++)
		StoredSkeletons[i] = new NTSkeleton();
	numberOfCapturedElements = nElements;
	PresentElement = focusedElement;
	LifeSpan = 0;
	
	ID = -1;
	
	/*
	JOINT_HEAD
	LEFT_ELBOW
	LEFT_FOOT
	LEFT_HAND
	LEFT_HIP
	LEFT_KNEE
	LEFT_SHOULDER
	NECK
	RIGHT_ELBOW
	RIGHT_FOOT
	RIGHT_HAND
	RIGHT_HIP
	RIGHT_KNEE
	RIGHT_SHOULDER
	TORSO
	

	// IDEALLY you want this list to be outside the Object
	// Create a List of the possible Joints

	JointList = new JointType[NITE_JOINT_COUNT]();
	JointList[0] = JOINT_HEAD;
	JointList[1] = JOINT_LEFT_ELBOW;
	JointList[2] = JOINT_LEFT_FOOT;
	JointList[3] = JOINT_LEFT_HAND;
	JointList[4] = JOINT_LEFT_HIP;
	JointList[5] = JOINT_LEFT_KNEE;
	JointList[6] = JOINT_LEFT_SHOULDER;
	JointList[7] = JOINT_NECK;
	JointList[8] = JOINT_RIGHT_ELBOW;
	JointList[9] = JOINT_RIGHT_FOOT;
	JointList[10] = JOINT_RIGHT_HAND;
	JointList[11] = JOINT_RIGHT_HIP;
	JointList[12] = JOINT_RIGHT_KNEE;
	JointList[13] = JOINT_RIGHT_SHOULDER;
	JointList[14] = JOINT_TORSO;
	*/

}


//// THIS MIGHT CAUSE FAILURE
SequentialUserCapture::~SequentialUserCapture()
{
	/*
	if (numberOfCapturedElements>0)
		for (int i = 0; i < numberOfCapturedElements; i++)
			delete StoredSkeletons[i];

	delete StoredSkeletons;
	*/
}


/***************************************
GET & SET ATTRIBUTES
****************************************/

/* 
setUserSkeletonAt:
	Given a position in the Skeleton array

*/


/*
void SequentialUserCapture::setUserSkeletonAt(int position, Skeleton* theSkeleton){
	StoredSkeletons[position] = theSkeleton;
}
*/


/***getUserSkeletonAt:***************************************************
Gets a NTSkeleton from the StoredSkeletons array
according to it´s position
*******************************************************************/
NTSkeleton* SequentialUserCapture::getUserSkeletonAt(int pos) {
	return StoredSkeletons[pos];
}


/***CopySkeleton:***************************************************
Get data from all joints of the previous skeleton
*******************************************************************/
void SequentialUserCapture::CopySkeletonToPosition(int SkeletonPos, Skeleton *theSkeleton) {
	for (int counter = 0; counter <NITE_JOINT_COUNT; counter++)
		StoredSkeletons[SkeletonPos]->setJointAt(theSkeleton, StoredSkeletons[SkeletonPos]->JointList[counter]);
	StoredSkeletons[SkeletonPos]->state = StoredSkeletons[SkeletonPos]->ConversionStateSkelly2Nite(theSkeleton->getState()); // convert from 
	
}


void SequentialUserCapture::setUserSkeletonAt(int SkeletonPos, Skeleton *theSkeleton) {
	CopySkeletonToPosition(SkeletonPos, theSkeleton);
}


void SequentialUserCapture::UpdateId(int newId){
	ID = newId;
}

void SequentialUserCapture::OnNextFrameArrival(Skeleton *theSkeleton) {


	// Take out the oldest frame to make room for a new one
	//if it exists
	if (StoredSkeletons[NUMBER_OF_FRAMES - 1]->state != NITE_SKELETON_NONE)
		//SET NULL INSTEAD OF DESTROY
		//delete StoredSkeletons[NUMBER_OF_FRAMES-1];
		//SetSkelletonNullAt(NUMBER_OF_FRAMES - 1);
		StoredSkeletons[(NUMBER_OF_FRAMES - 1)]->SetSkelletonNull();


	// shift from 0 to NUMBER_OF_FRAMES-2 -> +1 position
	// The first to shift is the 2nd Oldest to the oldest
	//position 0 not included
	for (int i = NUMBER_OF_FRAMES-1; i <= 1; i--) {
		StoredSkeletons[i]->CopyFromNTSkeleton(getUserSkeletonAt(i - 1));
	}

	//Get the new Skeleton coming to the 0 Position
	CopySkeletonToPosition(0, theSkeleton);

}



void SequentialUserCapture::SetSkelletonNullAt(int skeletonPost) {
	StoredSkeletons[skeletonPost]->SetSkelletonNull();
}