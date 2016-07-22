#pragma once


#include <direct.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <winerror.h>

using namespace std;
class FileHandler
{
public:
	static bool CreateFolder(const char* folderName);
	static bool CheckFileExistence(const char* name);
};
