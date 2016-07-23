#include "RecordLog.h"



/***ReadFrameRegisterToArray:************************************
Read all the frame positions recorded in a file. All the frame positions will be stored in an array
that is easy to work with.
******************************************************************/
void ReadFrameRegisterToArray(char* nameFile, float ** theMatrix, bool alt) {
	string  line;
	bool firstLine = true;
	bool error = false;
	int row, col = 0;
	int rowCount = 0, colCount = 0;
	Point3f theRelativePoint = Point3f();

	float **theArray;
	// Needs to be initialized to avoid error?

	/*
	theArray = new float*[rowCount];
	for (int i = 0; i < rowCount; ++i)
	theArray[i] = new float[colCount];
	*/
	//cout << line << endl;
	std::string         data;

	ifstream outfile(nameFile);
	while (getline(outfile, line))
	{
		std::stringstream   linestream(line);
		// First line in the doc - HAPPENS ONLY ONCE
		if (firstLine) {
			//std::getline(linestream, data);


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
						rowCount = stoi(data);
						onetime = false;
						secondtime = true;

					}
					else if (secondtime) {
						colCount = stoi(data);
						secondtime = false;
						thirdTime = true;
					}
					else if (thirdTime) {
						theRelativePoint.x = stoi(data);
						thirdTime = false;
						fouthTime = true;
					}
					else if (fouthTime) {
						theRelativePoint.y = stoi(data);
						fouthTime = false;
						fifthTime = true;
					}
					else if (fifthTime) {
						theRelativePoint.z = stoi(data);
						fifthTime = false;
					}
					else {
						
					}
				}
				if (error) {
					cout << "Exiting ReadFrameRegisterToArray()";
					break;
				}

				firstLine = false;
				cout << "firstLine passed" << endl;
			}

			//NON-Alternate
			else{
				bool onetime = true;
				while (getline(linestream, data, ';')) {
					//linestream >> frames;
					if (onetime) {
						rowCount = stoi(data);
						onetime = false;
					}
					else {
						colCount = stoi(data);
					}
				}
				if (error) {
					cout << "Exiting ReadFrameRegisterToArray()";
					break;
				}

				firstLine = false;
				cout << "firstLine passed" << endl;
			}
		}
		else {
			row = 0;
			while (getline(linestream, data, ';')) {
				//linestream >> type;

				theMatrix[row][col] = stof(data);
				cout << theMatrix[row][col] << "----";
				row++;
			}

			cout << endl;

			if (rowCount - 1 == row) {
				cout << rowCount << "   reached end of " << endl;
				break;
			}
			//cout << col << endl;
			col++;

			//cout << col << endl;
		}
	}

	/*
	for (int i = 0; i < rowCount; i++)
	for (int j = 0; j < colCount ; j++)
	theMatrix[i][j] = theArray[i][j];
	*/
	if (!outfile.eof())
	{
		cerr << "Error in reading file!\n";
	}
	outfile.close();
	//cout << "finished   " << theMatrix[1][1]  <<endl;
	//return theArray;
}



/***ReadFrameRegisterToArray:************************************
Given the integer value of a joint, we adquire the string name of 
the referenced body element.
******************************************************************/
char* Int2JointIndexing(int integerValue) {
	char* jointName;
	switch (integerValue) {
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
	return jointName;
}



/***GetRelativePosition:************************************
Get the relative position vector from a joint to another
******************************************************************/

Point3f GetRelativePosition(Point3f Origin, Point3f Target = Point3f(0, 0, 0)) {
	Point3f coordinates;
	float x, y, z;
	x = Target.x - Origin.x;
	y = Target.y - Origin.y;
	z = Target.z - Origin.z;
	coordinates.set(x, y, z);
	return coordinates;
}
