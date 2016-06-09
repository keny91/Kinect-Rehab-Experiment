#include "RecordLog.h"



RecordLog::RecordLog()
{
	char* newName = new char[14];
	newName = "OutReport.bin";
	name = newName;
}


RecordLog::RecordLog(char* theName)
{

	cout << "" << endl;
	char* postfix = ".bin";
	char *newName = new char(strlen(postfix) + strlen(theName) + 1);
	strcpy(newName, theName);
	strcat(newName, postfix);
	name = newName;

}

RecordLog::~RecordLog()
{

}


void RecordLog::StartRecording() {
	theFile.open(name, ios::out);
	theFile << "FileBeggining" << endl;

}

void RecordLog::StopRecording() {
	theFile.close();
}



/***InsertRegisterSkeleton:***************************************************
We register the position, orientation and confidences of every joint in the skeleton.

The order of joints stored follows:

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

The
	(FRAME_CHECK)?
	FRAME;ID;SKELETON_STATE
	JOINT_TYPE;JOINT_POSITION.X;...;JOINT_ORIENTATION.X;...;POS_CONFIDENCE;ORI_CONFIDENCE
	...
	(FRAME_CHECK)


*******************************************************************/
void RecordLog::InsertRegisterSkeleton(Skeleton theSkeleton, int frame, int BodyID) {
	//frame check here...
	theFile << frame << ";" <<BodyID << ";" << theSkeleton.getState() << endl;
	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		theFile << theSkeleton.getJoint(JointList[i]).getPosition().x << ";" << theSkeleton.getJoint().getPosition().y << ";" << theSkeleton.getJoint().getPosition().z;
		//NO endl
		theFile << theSkeleton.getJoint().getPosition().x << ";" << theSkeleton.getJoint().getPosition().y << ";" << theSkeleton.getJoint().getPosition().z;
	}
	
	theFile
}

void RecordLog::InsertRegisterNTSkeleton(NTSkeleton theSkeleton) {

}