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

	for (int i = 0; i < NITE_JOINT_COUNT; i++) {
		if (JointSelection[i]) {

			//Get the array of positions from both Sample and
			char *jointName;
			switch (i) {
			case 0:
				jointName = "HEAD";
				break;
			case 1:
				jointName = "NECK";
				break;
			case 2:
				jointName = "L_SHOULDER";
				break;
			case 3:
				jointName = "R_SHOULDER";
				break;
			case 4:
				jointName = "L_ELBOW";
				break;
			case 5:
				jointName = "R_ELBOW";
				break;
			case 6:
				jointName = "L_HAND";
				break;
			case 7:
				jointName = "R_HAND";
				break;
			case 8:
				jointName = "TORSO";
				break;
			case 9:
				jointName = "L_HIP";
				break;
			case 10:
				jointName = "R_HIP";
				break;
			case 11:
				jointName = "L_KNEE";
				break;
			case 12:
				jointName = "R_KNEE";
				break;
			case 13:
				jointName = "L_FOOT";
				break;
			case 14:
				jointName = "R_FOOT";
				break;
			default: //Optional
				jointName = "UNKNOWN";
			}

			char *prefix = "Joint_";
			char* postfix = ".bin";

			char finalnGTdir[200];
			char finalnSamplesdir[200];

			// GT
			strcpy_s(finalnGTdir, pathSGTFile);
			strcat_s(finalnGTdir, prefix);
			strcat_s(finalnGTdir, jointName);
			strcat_s(finalnGTdir, postfix);

			int* cols;
			int * rows;
			if (checkFileExistence(finalnGTdir)) {
				// If file found
				//1st get dimensions
				GetLogDimensions(finalnGTdir, rows, cols); 
				float **theGTArray;
				//2nd initialize a matrix with the dimensions
				theGTArray = new float*[*rows];		
				for (int i = 0; i < *rows; ++i)
					theGTArray[i] = new float[*cols];
				//3rd get the array values
				

			}
			else {
				cout << "Error File Not found: " << finalnGTdir << endl;
				break;
			}
			// Samples
			strcpy_s(finalnSamplesdir, pathSGTFile);
			strcat_s(finalnSamplesdir, prefix);
			strcat_s(finalnSamplesdir, jointName);
			strcat_s(finalnSamplesdir, postfix);

			if (checkFileExistence(finalnGTdir)) {
				//1st get dimensions
				GetLogDimensions(finalnSamplesdir, rows, cols);
				float **theSamplesArray;
				//2nd initialize a matrix with the dimensions
				theSamplesArray = new float*[*rows];
				for (int i = 0; i < *rows; ++i)
					theSamplesArray[i] = new float[*cols];
				//3rd get the array values


			}
			else {
				cout << "Error File Not found: " << finalnSamplesdir << endl;
				break;
			}
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




/***ReadFrameRegisterToArray:************************************
Read all the frame positions recorded in a file. All the frame positions will be stored in an array
that is easy to work with.

Inputs:
	-	declared float array
	-	declared float array
******************************************************************/
void Compare::ReadFrameRegisterToArray(char* nameFile, float ** theMatrix) {

	string  line;
	bool firstLine = true;
	bool error = false;
	int row, col = 0;
	int rowCount = 0, colCount = 0;

	float **theArray;
	// Needs to be initialized to avoid error?
	theArray = new float*[rowCount];
	for (int i = 0; i < rowCount; ++i)
		theArray[i] = new float[colCount];


	ifstream outfile(nameFile);
	while (std::getline(outfile, line))
	{
		//cout << line << endl;
		std::stringstream   linestream(line);
		std::string         data;


		// First line in the doc - HAPPENS ONLY ONCE
		if (firstLine) {
			//std::getline(linestream, data);
			bool onetime = true;
			while (getline(linestream, data, ';')) {
				//linestream >> frames;
				if (onetime) {
					rowCount = stoi(data);
					if (sizeof(theMatrix) == rowCount) {
						cout << "ERROR, Dimensions do not fit";
						error = true;
					}
					onetime = false;
				}
				else {
					colCount = stoi(data);
					if (sizeof(theMatrix[0]) == colCount) {

						cout << "ERROR, Dimensions do not fit";
						error = true;
					}

				}
			}
			if (error) {
				cout << "Exiting ReadFrameRegisterToArray()";
				break;
			}


			firstLine = false;
			cout << "firstLine passed" << endl;
		}
		else {
			row = 0;
			while (getline(linestream, data, ';')) {
				//linestream >> type;

				theMatrix[row][col] = stof(data);
				row++;

			}
			col++;
			//cout << col << endl;
		}
	}


	if (!outfile.eof())
	{
		cerr << "Error in reading file!\n";
	}
	outfile.close();
	cout << "finished   " << theMatrix[1][1] << endl;
	//return theArray;

}