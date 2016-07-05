#include "Compare.h"



Compare::Compare() {
	
}

Compare::Compare(char* nameSampleFile, char* nameGTFile) {
	makeComparison(nameSampleFile, nameGTFile);
}

Compare::~Compare()
{
}



/***makeComparison:********************************************
Given two folders (one in ./Samples and other./GT) as arguments, the method will initiate
the comparison process.
	- Step one is to access the info.bin file in every folder
*******************************************************************/

void Compare::makeComparison(char* nameSampleFile, char* nameGTFile) {

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

	bool checkSample = false;
	bool checkGT = false;
	//pathSGTFile = new char[200];
	//pathSampleFile = new char[200];

	//Check if the given sample name exist
	char *directory = "./Samples/";
	char *dataFile = "info.bin";
	char finalname[200];
	strcpy_s(finalname, directory);
	strcat_s(finalname, nameSampleFile);
	strcat_s(finalname, "/");
	pathSampleFile = finalname;
	//strcpy_s(pathSampleFile, finalname);  // init the path to folder
	strcat_s(finalname, dataFile);
	//strcat_s(finalname, jointName);
	checkSample = Compare::checkFileExistence(finalname);
	if (checkSample) {
		SampleFile = ifstream(finalname);
		cout << "the Samples file exists " << checkSample << endl;
	}
	else {
		//ERROR CODE
		cout << "The file in Samples does not exist." << endl;
	}
		

	//Check if the given gt name exist
	directory = "./GT/";
	//dataFile = "info.bin";
	strcpy_s(finalname, directory);
	strcat_s(finalname, nameGTFile);
	strcat_s(finalname, "/");
	pathSGTFile = finalname; // init the path to folder

	strcat_s(finalname, dataFile);
	//strcat_s(finalname, jointName);
	checkGT = Compare::checkFileExistence(finalname);
	if (checkGT) {
		GTFile = ifstream(finalname);
		cout << "the GT file exists " << checkGT << endl;
	}
	else {
		//ERROR CODE
		cout << "The file in GT does not exist." << endl;
	}
		

	// If both are found
	if (checkGT && checkSample) {

		if (GetJointSelection()) {
			cout << "Joint selection completed";
			GTFile.close();
			SampleFile.close();

			// CONTINUE WITH THE VALUE EXTRACTION FROM FILE TO ARRAY


			// THEN MAKE THE COMPARISON BETWEEN THE 2 ARRAYS
		}


		
	}
	else {
		//ERROR CODE
		cout << "Comparison Process terminated."  << endl;
	}

	// CASE files were not closed properly
	GTFile.close();
	SampleFile.close();


}

/***GetJointSelection:********************************************
		-First we have to read the details of both:
		-Extract data from both info.bin files
		-Find if they are represented by the same joints
*******************************************************************/

bool Compare::GetJointSelection() {

	inProcess = true;

	Cost = 0;
	JointSelection = new bool[NITE_JOINT_COUNT]();
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		JointSelection[i] = false;

	bool *JointSelectionConfirmation = new bool[NITE_JOINT_COUNT]();
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		JointSelectionConfirmation[i] = false;


	string   line;
	int JointSelect;
	int count = 0;
	string  data;

	int type, isthere;

	while (getline(GTFile, line))
	{
		int elementCount = 0;
		std::stringstream   linestream(line);
		while (getline(linestream, data, ';')) {
			if (elementCount == 0)
				type = stoi(data);
			else {
				isthere = stoi(data);
				elementCount = 0;
			}
				
			elementCount++;
		}	

		if (isthere == 1) {
			JointSelection[type] = true;
			cout << "DETECTED DOC TYPE: " << type << endl;
		}

		else
			JointSelection[type] = false;

	}


	while (getline(SampleFile, line))
	{
		int elementCount = 0;
		std::stringstream   linestream(line);
		while (getline(linestream, data, ';')) {
			if (elementCount == 0)
				type = stoi(data);
			else {
				isthere = stoi(data);
				elementCount = 0;
			}
				
			elementCount++;
		}
		if (isthere == 1) {
			JointSelectionConfirmation[type] = true;
			cout << "DETECTED DOC TYPE: " << type << endl;
		}

		else
			JointSelectionConfirmation[type] = false;
	}

	bool check = true;
	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if (JointSelection[i] != JointSelectionConfirmation[i]) {
			check = false;
			//ERROR CODE
			cout << "DETECTED ERROR:  represented joints mismatch" << endl;
			cout << "Were the names correctly inserted?" << endl;
			break;
		}
	}

	return check;
	
}

/***checkFileExistence:***************************************
Support Function that will tell us if a file with a certain name already exists.
Might cause unnecessary slow-down
******************************************************************/
bool Compare::checkFileExistence(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

/***SetFromNTSkeleton:********************************************
Copy a NTSkeleton from another already existing.
Just mimic all parameter´s values
*******************************************************************/


