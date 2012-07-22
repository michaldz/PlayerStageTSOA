/*
 * Laser.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#ifndef LASER_H_
#define LASER_H_
#include <stdio.h>
#include <limits>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>
#include "Sick.h"
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;
class Laser {

private:
	std::vector <Sick> samplesVector;
	//std::vector <Sick>::iterator it;
	double distanceX;
	double distanceY;
	static const double tolerancy = 0.1;

public:
	void ReadScan();
	void ClearLastScan();
	void PrintValuesToConsole();
	void PrintValuesToConsole(int);
    double distanceToTarget;
    double degreesToTarget;
    double angleToTarget;
    double robotOrientationInDegrees;
    double laserRange;
    bool nativeObstacleAvoid;
    bool CheckInTarget();
    void Robotorientation();
    void ReadDistanceToTarget();
    void ReadDegreesToTarget();
	int SickResolution();
	int SickListMaxSize();
	double ReturnSickListSum(int);
	double ReturnSickSize(int);
	double ReturnLastScan(int);
	void MoveTo(double,double); // set meters,angle per sec
	void NativeObstacleAvoid();
	void NativeObstacleAvoid1();


	Laser();
	virtual ~Laser();




};

#endif /* LASER_H_ */
