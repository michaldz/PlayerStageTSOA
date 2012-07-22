/*
 * TS.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#ifndef TS_H_
#define TS_H_
#include <iostream>
#include <math.h>
#include <cmath>
#include <algorithm>
#include <deque>

#include "Laser.h"

class Target{

public:
		int position;   //pozycja przed segregacji
		double offsetLeftValue;
		double offsetRightValue;
		double targetFunction;
		int tabuList; //wartości 0, 1 określające występowanie na liście
		int obstacleDegrees;
		double degreesToTarget;

        static bool LeftComparator(const Target &a, const Target &b){

       	if (a.offsetLeftValue < b.offsetLeftValue)
       		return true;
       	else
      		return false;


        }
        static bool RightComparator(const Target &a, const Target &b){

        	if (a.offsetRightValue < b.offsetRightValue)
        	        		return true;
        	        	else
        	        		return false;

        }


};

class TabuList{
public:
	int tlValue;





};



class TS: public Laser {
private:
	   double tabTargetFunction[180];
	   double tabOffsetLeft[180];
	   double tabOffsetRight[180];
	   std::vector <Target> targets;
	   int chosenDirection;  // 0 to lewy, 1 to prawy
	   std::deque <TabuList> tabuL;
	   static const int tabuLSize = 5;
	   static const double acceptObstacleDistance = 0.1; //akceptowalne zbliżenie do przeszkody


public:

	   void CalculateTargetFunction();
	   void CalculateOffset();
	   void PrintTargetFunction();
	   void PrintTargetFunction(int);
	   void PrintTabuL();
	   void TabuSearchMainAlgoritchm();

	   void TabuLAdd(int);
	   bool TabuLCheck(int);
	  // void TabuLPop();



	TS();
	virtual ~TS();
};

#endif /* TS_H_ */
