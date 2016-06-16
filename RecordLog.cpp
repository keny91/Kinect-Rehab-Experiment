#include "RecordLog.h"



RecordLog::RecordLog()
{
	char* newName = new char[14];
	newName = "OutReport.bin";
	name = newName;
	aSkeleton = Skeleton();
	isRecording = false;

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
}


RecordLog::RecordLog(char* theName)
{

	cout << "" << endl;
	//char* postfix = ".bin";
	char* postfix = ".txt";
	char *newName = new char();
	strcpy_s(newName, strlen(theName)+1,theName);
	strcat_s(newName, strlen(newName) + strlen(postfix)+1,postfix);
	//memccpy(newName, theName);
	//memccpy(newName, postfix);

	name = newName;
	aSkeleton = Skeleton();
	isRecording = false;

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

}

RecordLog::~RecordLog()
{

}


void RecordLog::StartRecording() {
	theFile.open(name, ios::out);
	theFile << "FileBeggining" << endl;
	isRecording = true;

}

void RecordLog::StopRecording() {
	theFile.close();
	isRecording = false;
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

	3 frame info- endl
	3 position - 4 orientation -2 confidence

*******************************************************************/
void RecordLog::InsertRegisterSkeleton(Skeleton theSkeleton, int frame, int BodyID) {
	//frame check here...
	theFile << frame << ";" <<BodyID << ";" << theSkeleton.getState() << endl;
	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		theFile << theSkeleton.getJoint(JointList[i]).getPosition().x << ";" << theSkeleton.getJoint(JointList[i]).getPosition().z;
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getOrientation().x << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().y << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().z << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().w;
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getPositionConfidence() << ";" << theSkeleton.getJoint(JointList[i]).getOrientationConfidence() << endl;
		//endl
	}
}



/***InsertRegisterNTSkeleton:************************************
Similar process to InsertRegisterSkeleton but adapted to
a different class input.
*******************************************************************/
//void RecordLog::InsertRegisterNTSkeleton(NTSkeleton theSkeleton) {

//}


/***ConversionStateSkelly2Nite:************************************
Convert from "SkeletonState" to "NiteSkeletonState"
required to avoid linker errors.
*******************************************************************/
void RecordLog::StartReading() {
	theFile.open(name, ios::in);
	//getline
	
	theFile << "FileBeggining" << endl;
}

/***ReadFrameRegister:************************************
Read a whole set of joints allocated in the same frame
*******************************************************************/
void RecordLog::ReadFrameRegister() {
	char splitter = ';';
	string line;
	//while(std::getline(file, line)){
	getline(theFile, line);

	// work
	std::stringstream linestream(line);
	std::vector<std::string> tokens;
	for (std::string each; std::getline(linestream, each, splitter); tokens.push_back(each));


	// Each token has a value
	//does this read the final segment? -> before endl?

	//DEBUGG TO FIND OUT



	//theFile.open(name, ios::in);
	//getline
	//theFile << "FileBeggining" << endl;
}


/***EndReading:************************************
Close the file
*******************************************************************/
void RecordLog::EndReading() {	
	theFile.close();
}



/***CreateEvaluationReport:************************************
Create a log specifiyng the data from the evaluation between 
Ground Truth and the performance
*******************************************************************/
void RecordLog::CreateEvaluationReport() {
	theFile.close();
}