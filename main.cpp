/*******************************************************************************
*                                                                              *
*   PrimeSense NiTE 2.0 - User Viewer Sample                                   *
*   Copyright (C) 2012 PrimeSense Ltd.                                         *
*                                                                              *
*******************************************************************************/

//#include "Viewer.h"
#include "SequentialUserCapture.h"

int main(int argc, char** argv)
{
	openni::Status rc = openni::STATUS_OK;

	SampleViewer sampleViewer("Rehabilitation with Kinect");


	rc = sampleViewer.Init(argc, argv);
	if (rc != openni::STATUS_OK)
	{
		return 1;
	}
	sampleViewer.Run();
}
