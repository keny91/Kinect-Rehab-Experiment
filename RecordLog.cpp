#include "RecordLog.h"


/*
float SampleViewer::GetDistanceBetweenJoints(nite::SkeletonJoint JointA, nite::SkeletonJoint JointB) {
nite::Point3f pos1 = JointA.getPosition();
nite::Point3f pos2 = JointB.getPosition();

float xdif, ydif, zdif, dist;
xdif = pos1.x - pos2.x;
ydif = pos1.y - pos2.y;
zdif = pos1.z - pos2.z;
dist = sqrt(pow((xdif), 2) + pow((ydif), 2) + pow((zdif), 2));
return dist;
}
*/

//cout << "THE DISTANCE BETWEEN HANDS IS:"<<GetDistanceBetweenJoints(user.getSkeleton().getJoint(nite::JOINT_LEFT_HAND), user.getSkeleton().getJoint(nite::JOINT_RIGHT_HAND));
//RECORDING HERE
/*
if (theRecording->isRecording)
theRecording->InsertRegisterSkeleton(users[i].getSkeleton(), users[i].getId(), 1);
else if (GetDistanceBetweenJoints(users[i].getSkeleton().getJoint(nite::JOINT_LEFT_HAND), users[i].getSkeleton().getJoint(nite::JOINT_RIGHT_HAND))) {

}
*/

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

	//cout << "" << endl;
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
	theFile << "FileEnding" << endl;
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
		theFile << JointList[i] << ";";
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getPosition().x << ";" << theSkeleton.getJoint(JointList[i]).getPosition().y <<";" << theSkeleton.getJoint(JointList[i]).getPosition().z;
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getOrientation().x << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().y << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().z << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().w << ";";
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

/***SeparateSingleJoint:************************************
Convert from "SkeletonState" to "NiteSkeletonState"
required to avoid linker errors.
Order is:
FileBeggining
Frame/body/SkeletonState
Joint1: JointType/Positions(3)/Orientation(4)/confidences(2)
Joint2: ...
...
Frame/body/SkeletonState
...
*******************************************************************/
void RecordLog::SeparateSingleJoint(JointType theType) {

	if(!isRecording){

	float posx, posy, posz, orix, oriy, oriz, confpos, confori;
	int type;
	//JointType type;

	fstream file;
	//char *prefix = "Joint_"; 
	char *prefix = "./SingleJointRecord/Joint_";
	char* postfix = ".txt";
	char theName[30];
	itoa(theType, theName,10);  // MAY CRASH
	char *aName;
	char *finalname;
	//string theName = string(intStr);
	strcpy_s(aName, strlen(prefix) + 1, prefix);
	strcat_s(aName, strlen(prefix) + strlen(theName) + 1, theName);
	strcat_s(finalname, strlen(aName) + strlen(postfix) + 1, postfix);

	delete aName;

	//Open reading file
	theFile.open(name, ios::in);


	//Open new Writting file
	//theFile.open(finalname, ios::out);
	file.open(finalname, ios::out);
	//ifstream file("OutputLog.txt");


	// until we reach end of reading file
	
	string  line;

	while (getline(theFile, line)) {
		stringstream linestream(line);
		string data;

		getline(linestream, data, ';');
		linestream >> type >> posx >> posy >> posz >> orix >> oriy >> oriz >> confpos >> confori;


		if (theType == type) {
			theFile << posx << ";" << posy << ";" << posz <<endl;
			//NO endl
			/*
			theFile << theSkeleton.getJoint(JointList[i]).getOrientation().x << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().y << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().z << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().w << ";";
			//NO endl
			theFile << theSkeleton.getJoint(JointList[i]).getPositionConfidence() << ";" << theSkeleton.getJoint(JointList[i]).getOrientationConfidence() << endl;
			*/
		}
		
	}

	// close both
	theFile.close(); // <-- carefull that we are not writting at the time
	file.close();
	}

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