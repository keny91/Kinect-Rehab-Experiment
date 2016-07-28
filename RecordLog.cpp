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
/*
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

	JointList = new JointType[NITE_JOINT_COUNT]();
	JointList[0] = JOINT_HEAD;
	JointList[1] = JOINT_NECK;
	JointList[2] = JOINT_LEFT_SHOULDER;
	JointList[3] = JOINT_RIGHT_SHOULDER;
	JointList[4] = JOINT_LEFT_ELBOW;
	JointList[5] = JOINT_RIGHT_ELBOW;
	JointList[6] = JOINT_LEFT_HAND;
	JointList[7] = JOINT_RIGHT_HAND;
	JointList[8] = JOINT_TORSO;
	JointList[9] = JOINT_LEFT_HIP;
	JointList[10] = JOINT_RIGHT_HIP;
	JointList[11] = JOINT_LEFT_KNEE;
	JointList[12] = JOINT_RIGHT_KNEE;
	JointList[13] = JOINT_LEFT_FOOT;
	JointList[14] = JOINT_RIGHT_FOOT;


	JointSelection = new bool[NITE_JOINT_COUNT]();
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		JointSelection[i] = false;

	//recordPostFix = false;
	//Init Folders
	InitFolders();
}


RecordLog::RecordLog(char* theName, bool recordPost)
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
	JointList[1] = JOINT_NECK;
	JointList[2] = JOINT_LEFT_SHOULDER;
	JointList[3] = JOINT_RIGHT_SHOULDER;
	JointList[4] = JOINT_LEFT_ELBOW;
	JointList[5] = JOINT_RIGHT_ELBOW;
	JointList[6] = JOINT_LEFT_HAND;
	JointList[7] = JOINT_RIGHT_HAND;
	JointList[8] = JOINT_TORSO;
	JointList[9] = JOINT_LEFT_HIP;
	JointList[10] = JOINT_RIGHT_HIP;
	JointList[11] = JOINT_LEFT_KNEE;
	JointList[12] = JOINT_RIGHT_KNEE;
	JointList[13] = JOINT_LEFT_FOOT;
	JointList[14] = JOINT_RIGHT_FOOT;
	recordPostFix = recordPost;

	// There is a correspondance between JointSelection and JointList
	JointSelection = new bool[NITE_JOINT_COUNT]();
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		JointSelection[i] = false;

	//Init Folders
	InitFolders();

}

RecordLog::~RecordLog()
{

}


/***InitFolders:**************************************
Create Required folders for the project structures
*****************************************************/
void RecordLog::InitFolders() {
	FileHandler::CreateFolder("./GT");
	FileHandler::CreateFolder("./Samples");
}




void RecordLog::StartRecording() {
	theFile.open(name, ios::out);
	theFile << "                 " << endl;
	isRecording = true;
	elapsedFrames = 0;

}

void RecordLog::StopRecording() {
	theFile << "FileEnding" << endl;
	
	

	//Set the first line to the number of frames

	theFile.clear();
	theFile.seekg(0, ios::beg);
	theFile << elapsedFrames;
	theFile.close();

	//Reset values
	isRecording = false;
	elapsedFrames = 0;
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
		theFile << theSkeleton.getJoint(JointList[i]).getPosition().x << ";" << theSkeleton.getJoint(JointList[i]).getPosition().y <<";" << theSkeleton.getJoint(JointList[i]).getPosition().z << ";";
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getOrientation().x << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().y << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().z << ";" << theSkeleton.getJoint(JointList[i]).getOrientation().w << ";";
		//NO endl
		theFile << theSkeleton.getJoint(JointList[i]).getPositionConfidence() << ";" << theSkeleton.getJoint(JointList[i]).getOrientationConfidence() << endl;
		//endl
	}
	elapsedFrames++;
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


/***Enable/DisableRecordingOfJoint:************************************
Decide and toogle which joints will be used to represent a gesture
*******************************************************************/
void RecordLog::EnableRecordingOfJoint(JointType theType) {

	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if(JointList[i] == theType)
			JointSelection[i] = true;
	}
		
}

void RecordLog::DisableRecordingOfJoint(JointType theType) {

	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if (JointList[i] == theType)
			JointSelection[i] = false;
	}

}

/***CreateGestureLog:***************************************
Read a whole set of joints allocated in the same frame
******************************************************************/
void RecordLog::CreateGestureLog(char* FileName, bool GT, Point3f RelativePoint) {
	char * FolderName;
	char directory[200];
	if (GT)
		FolderName = "./GT/";
	else
		FolderName = "./Samples/";

	//mkdir("c:/myfolder");
	strcpy_s(directory, FolderName);  // ./Samples/
	strcat_s(directory, FileName);	// ./Samples/exercise1
			// ./Samples/exercise1/

	//Create folder
	if (_mkdir(directory) ||
		ERROR_ALREADY_EXISTS == GetLastError())
		cout << "Created Directory: " << directory << endl;

	strcat_s(directory, "/"); // ./Samples/exercise1/
	cout << "the path is: " << directory << endl;

	char copyOutputLogNewPath[100];
	char* copyOutputLog = "OutputLog.txt";
	strcpy_s(copyOutputLogNewPath, directory);
	strcat_s(copyOutputLogNewPath, copyOutputLog);
	cout << "the path for outputlogis: " << copyOutputLogNewPath << endl;

	//Copy Output.txt to folder

	/* CHANGE CODE IN THE FUTURE
	ifstream src("./OutputLog.txt", std::ios::binary);
	ofstream dest(copyOutputLogNewPath, std::ios::binary);
	*/ 


	ifstream src("./OutputLog.txt"); //PROBLEM - Sometimes crashes?!
	ofstream dest(copyOutputLogNewPath);

	dest << src.rdbuf();
	src.close();
	dest.close();

	strcpy_s(copyOutputLogNewPath, directory);
	char* datafilename = "info.bin";
	strcat_s(copyOutputLogNewPath, datafilename);
	cout << "the path to data: " << copyOutputLogNewPath << endl;
	//Create a file with the joint info
	ofstream datafile(copyOutputLogNewPath);

	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if (JointSelection[i]) {
			datafile << i << ";" << 1 << endl; // 1 PER LINE
			SeparateSingleJoint(JointList[i], directory,RelativePoint,false, true, false, false);
			cout << "Created Joint Type log: " << JointList[i] << endl;
		}
		else
			datafile << i << ";" << 0 << endl; 
	}

	datafile.close();
/*
	ifstream outfile(FileName);
	string  line;
	std::string  data;
	getline(outfile, line);
	std::stringstream   linestream(line);
	bool onetime = true;
	//cout << line << endl;

	while (getline(linestream, data, ';')) {
		//linestream >> frames;
		if (onetime) {
			*rows = stoi(data);
			onetime = false;
		}
		else {
			*cols = stoi(data);

		}
	}
	outfile.close();

	*/
}


/***checkFileExistence:***************************************
Support Function that will tell us if a file with a certain name already exists.
Might cause unnecessary slow

******************************************************************/
bool checkFileExistence(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}


/***SeparateSingleJoint:*******************************************
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
void RecordLog::SeparateSingleJoint(JointType theType, char* directory , Point3f theRelativePoint ,bool recordPostFix = false,bool recordPosition =true, bool recordOrientation=false, bool recordConfidence=false) {

	if(!isRecording){
		//int eq = theType;
		char *jointName = Int2JointIndexing(theType);


		int numColumns = 0;
		string   line;
		bool firstLine = true;
		bool firstFrameLine = true;
		int type, frames;
		int numberOfJoints = 15;
		int jointCount = 0;
		const  int floatelements = 9;
		float frameInfo[floatelements]; // posx, posy, posz, orix, oriy, oriz, oriw, confpos, confori;

		
		char *prefix = "Joint_";
		//char* postfix = ".txt";
		char* postfix = ".bin";
		//char theName[200];
		char finalname[200];
		char finalnameAlt[200];
		char*posPostfix = "_P";
		char*oriPostfix = "_O";
		char*confPostfix = "_C";
		char*AltPostfix = "Alt";
		int totalFrames;
		//ostringstream convert;
		//convert << theType;
		//char bname[200];
		//string bName = convert.str();
		//strcpy_s(theName, bName.c_str());

		strcpy_s(finalname, directory);
		strcat_s(finalname, prefix);
		strcat_s(finalname, jointName);

		

		//Only if we are recording postfix
		if(recordPostFix){
			if (recordPosition) {
				strcat_s(finalname, posPostfix);
			}
			
			if (recordOrientation) {
				strcat_s(finalname, oriPostfix);
			}

			if (recordConfidence){
				strcat_s(finalname, confPostfix);
			}
		}

		strcpy_s(finalnameAlt, finalname);
		strcat_s(finalnameAlt, AltPostfix);
		strcat_s(finalnameAlt, postfix);
		strcat_s(finalname, postfix);

		
		if (recordPosition) {
			numColumns = numColumns + 3;
		}

		if (recordOrientation) {
			numColumns = numColumns + 4;
		}

		if (recordConfidence) {
			numColumns = numColumns + 2;
		}


		//Open files

		ofstream infile(finalname);
		ofstream infileAlt(finalnameAlt);
		ifstream outfile("OutputLog.txt");
		//theFile.open(name, ios::in);
		//std::ofstream infile("./SingleJointRecord/InputLog.txt");


		/*works*/

		while (std::getline(outfile, line))
		{
			//cout << line << endl;
			std::stringstream   linestream(line);
			std::string         data;


			// First line in the doc - HAPPENS ONLY ONCE
			if (firstLine) {
				//std::getline(linestream, data);
				linestream >> frames;
				infile << frames << ";" << numColumns << endl;
				infileAlt << frames << ";" << numColumns << ";" << theRelativePoint.x << ";" << theRelativePoint.y << ";" << theRelativePoint.z << endl;
				//cout << frames << "HAPPENS ONLY ONCE" << endl;
				firstLine = false;
			}
			else {

				// (int bodyid/int frame/int bodystate)
				if (firstFrameLine) {
					firstFrameLine = false;
					// Do something?
				}
				//(int jointType/positions(3)/orientations(4)/confidences(2))
				else {
					int elementCount = 0;
					while (getline(linestream, data, ';')) {
						//linestream >> type;


						if (elementCount == 0)
							type = stoi(data);
						else {
							frameInfo[elementCount - 1] = stof(data);
						}
						elementCount++;

					}
					//cout << type << endl;
					if(type == theType){
						if(recordPosition){
						infile << frameInfo[0] << ";" << frameInfo[1] << ";" << frameInfo[2];
						//Point3f oriPosition = Point3f(frameInfo[0], frameInfo[1], frameInfo[2]);
						Point3f finalPosition = Point3f(frameInfo[0], frameInfo[1], frameInfo[2]);
						Point3f relativePosition = GetRelativePosition(theRelativePoint, finalPosition);
						infileAlt << relativePosition.x << ";" << relativePosition.y << ";" << relativePosition.z;
						}
						if (recordOrientation) {
							if (recordPosition) {
								infile << ";";
								
							}
								
							infile << frameInfo[3] << ";" << frameInfo[4] << ";" << frameInfo[5] << ";" << frameInfo[6];
							infileAlt << frameInfo[3] << ";" << frameInfo[4] << ";" << frameInfo[5] << ";" << frameInfo[6];
							
						}
						if (recordConfidence) {
							if (recordPosition || recordOrientation) {
								infile << ";";
								infileAlt << ";";
							}
								
							infile << frameInfo[7] << ";" << frameInfo[8];
							infileAlt << frameInfo[7] << ";" << frameInfo[8];
						}
							
						infile << endl;
						infileAlt << endl;
					}
					//std::getline(linestream, data, ';');
					//linestream >> posx >> posy >> val3 >> val4;
					//std::cout << posx << "--" << posy << "--" << val3 << "--" << val4 << endl;
					jointCount++;
					//cout << "jointcount= " << jointCount << endl;
					if (numberOfJoints - 1<jointCount) {
						jointCount = 0;
						firstFrameLine = true;
						//cout << "skipped --1 :" << endl;
					}
				}
			}
		}

		// Error Case
		if (!outfile.eof())
		{
			cerr << "Error when creating the Log!\n";
		}

		outfile.close();
		infile.close();
		infileAlt.close();
		}

}





/***GetLogDimensions:***************************************
Read a whole set of joints allocated in the same frame
******************************************************************/
void RecordLog::GetLogDimensions(char* nameFile, int * rows, int* cols, bool alt) {

	ifstream outfile(nameFile);
	string  line;
	std::string  data;
	getline(outfile, line);
	std::stringstream   linestream(line);
	bool onetime = true;
	bool error = false;
	Point3f theRelativePoint = Point3f();
		//cout << line << endl;

		if (alt) {
			//std::getline(linestream, data);
			bool onetime = true;
			bool secondtime = false;
			bool thirdTime = false;
			bool fouthTime = false;
			bool fifthTime = false;

			while (getline(linestream, data, ';')) {
				//linestream >> frames;
				if (onetime) {
					*rows = stoi(data);
					onetime = false;
					secondtime = true;

				}
				else if (secondtime) {
					*cols = stoi(data);
					secondtime = false;
					thirdTime = true;
				}
				else if (thirdTime) {
					theRelativePoint.x = stof(data);
					thirdTime = false;
					fouthTime = true;
				}
				else if (fouthTime) {
					theRelativePoint.y = stof(data);
					fouthTime = false;
					fifthTime = true;
				}
				else if (fifthTime) {
					theRelativePoint.z = stof(data);
					fifthTime = false;
				}
				else {

				}
			}


		}
		else{
			while (getline(linestream, data, ';')) {
				//linestream >> frames;
				if (onetime) {
					*rows = stoi(data);
					onetime = false;
				}
				else {
					*cols = stoi(data);

				}
			}
		}
	
	outfile.close();
}



/***EndReading:************************************
Close the file
*******************************************************************/
void RecordLog::EndReading() {	
	theFile.close();
}



