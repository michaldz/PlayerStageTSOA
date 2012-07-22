//============================================================================
// Name        : TSOA.cpp
// Author      : MD
// Version     :
// Copyright   : Your copyright notice
// Description : 'Tabu Search Obstacle Algorithm' used to reach the target point
//============================================================================
#include <math.h>
#include <iostream>
#include <libplayerc++/playerc++.h>
using namespace PlayerCc;

#include "Laser.h"
#include "TS.h"
#include "Sick.h"
#include "Algorithm.h"


//connect to Player & interface set
PlayerClient robot("localhost",6665);
Position2dProxy p2dProxy(&robot,0);
LaserProxy laserProxy(&robot,0);

// target_point
player_pose2d_t target_point;




int main() {

		//enable motors
		p2dProxy.SetMotorEnable(1);
		//request geometries
		p2dProxy.RequestGeom();
		laserProxy.RequestGeom();

		target_point.px = 5;
		target_point.py = 5;
		target_point.pa = 0;

		robot.Read();

            Algorithm a;



        // p2dProxy.SetCarlike(0.2,0.25);
        //p2dProxy.SetSpeed(0.0,dtor(45));
        //sleep(1);
         //p2dProxy.SetSpeed(0.2,0);

            //main loop
        while(true){
		robot.Read();


		 std::cout << "francuz" << std::endl;

          a.Test();

          std::cout << "be cool" << std::endl;

		sleep(0.1);
//

	}



	return 0;
}

