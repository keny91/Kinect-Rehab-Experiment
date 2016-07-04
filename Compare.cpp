#include "Compare.h"



Compare::Compare(char* nameSample, char* nameGT)
{
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

	Cost = 0;
	JointSelection = new bool[NITE_JOINT_COUNT]();
	for (int i = 0; i < NITE_JOINT_COUNT; i++)
		JointSelection[i] = false;


}

/***initInfo:********************************************
Copy a NTSkeleton from another already existing.
Just mimic all parameter´s values
*******************************************************************/

void Compare::initInfo() {

}


/***SetFromNTSkeleton:********************************************
Copy a NTSkeleton from another already existing.
Just mimic all parameter´s values
*******************************************************************/


Compare::~Compare()
{
}
