#include "Compare.h"



Compare::Compare() {
	Cost = 0;
}

Compare::Compare(char* nameSampleFile, char* nameGTFile) {
	Cost = 0;
	makeComparison(nameSampleFile, nameGTFile);
	JointByJointCostCalculation();
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
	pathSampleFile = new char[200];
	strcpy_s(finalname, directory);
	strcat_s(finalname, nameSampleFile);
	strcat_s(finalname, "/");
	memcpy(pathSampleFile, finalname, 200);  // init the path to folder
	//strcpy_s(pathSampleFile, finalname);
	//pathSampleFile = finalname;
	//strcpy_s(pathSampleFile, finalname);  
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
	pathSGTFile = new char[200];
	//pathSGTFile = finalname; // init the path to folder
	memcpy(pathSGTFile, finalname, 200);
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
			cout << "Joint selection completed" <<endl;
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

/***JointByJointCostCalculation:********************************************
	Warning this should always be run after completing the JointSelection array
-Extract data from both info.bin files
- Find if they are represented by the same joints
*******************************************************************/

void Compare::JointByJointCostCalculation() {

	float **theSamplesArray;
	float **theGTArray;

	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if (JointSelection[i]) {

			//Get the array of positions from both Sample and
			char *jointName = Int2JointIndexing(i);
			

			char* prefix = "Joint_";
			char* postfix = ".bin";

			char finalnGTdir[200];
			char finalnSamplesdir[200];

			// GT
			strcpy_s(finalnGTdir, pathSGTFile);
			strcat_s(finalnGTdir, prefix);
			strcat_s(finalnGTdir, jointName);
			strcat_s(finalnGTdir, postfix);

			int* cols = new int();
			int * rowsGT = new int();
			if (checkFileExistence(finalnGTdir)) {
				// If file found
				//1st get dimensions
				GetLogDimensions(finalnGTdir, rowsGT, cols);
				//float **theGTArray;
				//2nd initialize a matrix with the dimensions

				cout << "rowsGT: " << *rowsGT << endl;
				cout << "colsGT: " << *cols << endl;
				theGTArray = new float*[*rowsGT];
				for (int i = 0; i < *rowsGT; ++i) {
					theGTArray[i] = new float[*cols];
					for (int j = 0; j < *cols; j++) {
						theGTArray[i][j] = 0;
					}
				}
				//3rd get the array values
				ReadFrameRegisterToArray(finalnGTdir, theGTArray, true);

			}
			else {
				cout << "Error File Not found: " << finalnGTdir << endl;
				break;
			}



			// Samples
			strcpy_s(finalnSamplesdir, pathSampleFile);
			strcat_s(finalnSamplesdir, prefix);
			strcat_s(finalnSamplesdir, jointName);
			strcat_s(finalnSamplesdir, postfix);

//			int* cols = NULL;
			int * rowsSamples = new int();

			if (checkFileExistence(finalnGTdir)) {
				//1st get dimensions
				GetLogDimensions(finalnSamplesdir, rowsSamples, cols);
				//float **theSamplesArray;
				cout <<"rowsSamples: " << *rowsSamples << endl;
				cout << "colsSamples: " << *cols << endl;
				//2nd initialize a matrix with the dimensions
				theSamplesArray = new float*[*rowsSamples];
				for (int i = 0; i < *rowsSamples; ++i) {
					theSamplesArray[i] = new float[*cols];
					for (int j = 0; j < *cols; j++) {
						theSamplesArray[i][j] = 0;
					}
				}

				
				//3rd get the array values
				ReadFrameRegisterToArray(finalnSamplesdir, theSamplesArray,true);

			}
			else {
				cout << "Error File Not found: " << finalnSamplesdir << endl;
				break;
			}

			// Once both files are loaded proceed to do the comparison between arrays
			dtw3d* DTWObject = new dtw3d(theGTArray, theSamplesArray, *rowsGT, *rowsSamples);
			Cost += DTWObject->theCost;
			//delete DTWObject;  //dESTRUCTOR HAS TO BE MORE Complex
		}
	}
		 



}





/***GetLogDimensions:***************************************
Read a whole set of joints allocated in the same frame
******************************************************************/
void Compare::GetLogDimensions(char* nameFile, int * rows, int* cols) {

	ifstream outfile(nameFile);
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
}





/***GetJointSelection:********************************************
		-First we have to read the details of both:
		-Extract data from both info.bin files
		-Find if they are represented by the same joints
*******************************************************************/

bool Compare::GetJointSelection() {

	inProcess = true;

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



