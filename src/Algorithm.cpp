/*
 * Algorithm.cpp
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#include "Algorithm.h"

Algorithm::Algorithm() {
	// TODO Auto-generated constructor stub

}

Algorithm::~Algorithm() {
	// TODO Auto-generated destructor stub
}
void Algorithm::Test(){


	//if (onTarget == false){
	    this->ReadScan();
		this->ReadDistanceToTarget();
		this->ReadDegreesToTarget();
		this->CalculateOffset();
		this->PrintValuesToConsole(10);
		this->PrintTargetFunction(10);
		this->PrintTabuL();
		this->ClearLastScan();

	    //this->CalculateTargetFunction();
	    this->CalculateOffset();
	    this->NativeObstacleAvoid1();
        this->TabuSearchMainAlgoritchm();
        onTarget = this->CheckInTarget();
	//}
	//else
	//{
	//	this->MoveTo(0,0);
	//	onTarget = this->CheckInTarget();

	//}


}
