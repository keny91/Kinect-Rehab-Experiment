#include "FileHandler.h"

bool FileHandler::CreateFolder(const char* folderName) {
	if (_mkdir(folderName) == 0)
	{
		cout << "Created Directory:  " << folderName << endl;
		return true;
	}
	else if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		cout << "Cannot create " << folderName << ", folder already exists." << endl;
		return true;
	}
	else
	{
		cout << "Error creating folder: " << GetLastError() << endl;
		return false;
	}
	return false;
}

/***checkFileExistence:***************************************
Support Function that will tell us if a file with a certain name already exists.
Might cause unnecessary slow
******************************************************************/
bool FileHandler::CheckFileExistence(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}