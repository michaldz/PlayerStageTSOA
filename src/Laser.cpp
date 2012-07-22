/*
 * Laser.cpp
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */


#define PI 3.14159265
#include "Laser.h"
extern PlayerClient robot;
extern Position2dProxy p2dProxy;
extern LaserProxy laserProxy;
extern player_pose2d_t target_point;
Laser::Laser() {
   // samplesVector.push_back(0);
	samplesVector.resize(laserProxy.GetCount());
	laserRange = laserProxy.GetMaxRange();

}

Laser::~Laser() {
	// TODO Auto-generated destructor stub
}

void Laser::ReadScan(){

   //for(it = samplesVector.begin(); it!=samplesVector.end(); it++){
	for(int i = 0; i < (int)laserProxy.GetCount(); i++){

		samplesVector[i].AddSample(laserProxy[i]);
		samplesVector[i].ReturnValue(); //buduje tablice z wynikami i liczy listSum


   }




}
void Laser::ClearLastScan(){

	for(int i = 0; i < (int)laserProxy.GetCount(); i++){

			samplesVector[i].RemoveSapmle();

	   }


}
void Laser::PrintValuesToConsole(){

	PrintValuesToConsole((int)laserProxy.GetCount());

}
void Laser::PrintValuesToConsole(int number){

	for(int i = 0; i < number; i++){



	    	std::cout << "Stopień "<< i << ": ";
	    	for(int j = 0; j< samplesVector[i].ReturnSize();j++){

	    		std::cout << samplesVector[i].listValue[j] << " ";
	    	}

               std::cout << std::endl;

   }
	std::cout << "size: " << samplesVector[0].ReturnSize() << std::endl;
	std::cout << "listSum: " << samplesVector[0].listSum << std::endl;
	std::cout << "Laser Range " << laserRange << std::endl;
	std::cout << "DistanceX: " << distanceX << std::endl;
	std::cout << "DistanceY: " << distanceY << std::endl;
	std::cout << "TargetX: " << target_point.px << std::endl;
	std::cout << "TargetY: " << target_point.py << std::endl;
	std::cout << "Distance to Target: " << distanceToTarget << std::endl;


	std::cout << "Degrees to Target: " << degreesToTarget << std::endl;
	std::cout << "Angle to Target: " << angleToTarget << std::endl;
	std::cout << "Robot Orientation: " << robotOrientationInDegrees << std::endl;

}

void Laser::ReadDistanceToTarget(){


	//if jedna z liczb ujemna to suma wartości bezwzględnych
	if(p2dProxy.GetXPos() < 0 && target_point.px > 0 ||
	   p2dProxy.GetXPos() > 0 && target_point.px < 0   )
	{

		distanceX = std::abs(p2dProxy.GetXPos()) + std::abs(target_point.px);

	}
	//if dwie ujemne to mniejsza abs + większa
	else if(p2dProxy.GetXPos() < 0 && target_point.px < 0)
	{

		distanceX = std::abs(((p2dProxy.GetXPos() < target_point.px ) ? p2dProxy.GetXPos() : target_point.px)  )
                    + 	((p2dProxy.GetXPos() > target_point.px ) ? p2dProxy.GetXPos() : target_point.px)  ;
	}

	//dwie dodatenie
	else if(p2dProxy.GetXPos() > 0 && target_point.px > 0)
	{

		distanceX = ((p2dProxy.GetXPos() > target_point.px ) ? p2dProxy.GetXPos() : target_point.px)
		           -((p2dProxy.GetXPos() < target_point.px ) ? p2dProxy.GetXPos() : target_point.px)  ;

	}

	//if jedna z liczb ujemna to suma wartości bezwzględnych
		if(p2dProxy.GetYPos() < 0 && target_point.py > 0 ||
		   p2dProxy.GetYPos() > 0 && target_point.py < 0   )
		{

			distanceY = std::abs(p2dProxy.GetYPos()) + std::abs(target_point.py);

		}
		//if dwie ujemne to mniejsza abs + większa
		else if(p2dProxy.GetYPos() < 0 && target_point.py < 0)
		{

			distanceY = std::abs(((p2dProxy.GetYPos() < target_point.py ) ? p2dProxy.GetYPos() : target_point.py ) )
	                    + 	((p2dProxy.GetYPos() > target_point.py ) ? p2dProxy.GetYPos() : target_point.py)  ;
		}
		else if(p2dProxy.GetYPos() > 0 && target_point.py > 0)
		{

			distanceY = ((p2dProxy.GetYPos() > target_point.py ) ? p2dProxy.GetYPos() : target_point.py)
			           -((p2dProxy.GetYPos() < target_point.py ) ? p2dProxy.GetYPos() : target_point.py ) ;

		}
	distanceToTarget = std::abs(sqrt((distanceX*distanceX)+(distanceY*distanceY)));
}
void Laser::ReadDegreesToTarget(){

	Robotorientation();


	//pierwsza ćwiartka układu
	if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px >0 && target_point.py > 0))
	{
		degreesToTarget = 180 + atan (distanceY/distanceX) * 180 / PI;
	}
	else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px >0 && target_point.py > 0))
	{
		degreesToTarget = 270 + (90 - atan (distanceY/distanceX) * 180 / PI);
	}
	else if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px >0 && target_point.py > 0))
	{
		degreesToTarget = 90 + (90 - atan (distanceY/distanceX) * 180 / PI);
	}
	else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px >0 && target_point.py > 0))
			{
			 degreesToTarget = atan (distanceY/distanceX) * 180 / PI;

			}
	//druga ćwiartka
	else if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px <0 && target_point.py > 0))
		{
			degreesToTarget = 180 + atan (distanceY/distanceX) * 180 / PI;
		}
		else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px <0 && target_point.py > 0))
		{
			degreesToTarget = 270 + (90 - atan (distanceY/distanceX) * 180 / PI);
		}
		else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px <0 && target_point.py > 0))
		{
			degreesToTarget = (atan (distanceY/distanceX) * 180 / PI);
		}
		else if(p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()<target_point.py  && target_point.px <0 && target_point.py > 0)
								{
									degreesToTarget = 90 + (90 - atan (distanceY/distanceX) * 180 / PI);
								}
	  //trzecia ćwiartka
		else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px <0 && target_point.py < 0))
				{
					degreesToTarget = 270 + (90-atan (distanceY/distanceX) * 180 / PI);
				}
				else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px <0 && target_point.py < 0))
				{
					degreesToTarget = atan (distanceY/distanceX) * 180 / PI;
				}
				else if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px <0 && target_point.py < 0))
				{
					degreesToTarget = 90 + (90-atan (distanceY/distanceX) * 180 / PI);
				}
				else if  (p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()>target_point.py  && target_point.px <0 && target_point.py < 0 )
						{
					degreesToTarget = 180 + atan (distanceY/distanceX) * 180 / PI;

						}

	//czwarta ćwiartka
				else if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()>target_point.py && target_point.px >0 && target_point.py < 0))
								{
									degreesToTarget = 180 + (atan (distanceY/distanceX) * 180 / PI);
								}
								else if((p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px >0 && target_point.py < 0))
								{
									degreesToTarget = atan (distanceY/distanceX) * 180 / PI;
								}
								else if((p2dProxy.GetXPos()>target_point.px && p2dProxy.GetYPos()<target_point.py && target_point.px >0 && target_point.py < 0))
								{
									degreesToTarget = 90 + (90-atan (distanceY/distanceX) * 180 / PI);
								}
								else if (p2dProxy.GetXPos()<target_point.px && p2dProxy.GetYPos()>target_point.py  && target_point.px >0 && target_point.py < 0)
								{
									degreesToTarget = 270 + (90 -atan (distanceY/distanceX) * 180 / PI);

								}

		angleToTarget = robotOrientationInDegrees - degreesToTarget;



}
void Laser::Robotorientation(){

	if(p2dProxy.GetYaw() > 0)
	{
	robotOrientationInDegrees = ((180 * p2dProxy.GetYaw())/PI);
	}
	else{

		robotOrientationInDegrees =  180 + (180 + ((180 * p2dProxy.GetYaw())/PI));


	}
}
int Laser::SickResolution(){
	return laserProxy.GetCount();
}

int Laser::SickListMaxSize(){

	return samplesVector[0].ReturnMaxSize();

}

double Laser::ReturnSickListSum(int i){

	return samplesVector[i].listSum;
}
double Laser::ReturnSickSize(int i){

	return samplesVector[i].ReturnSize();
}
double Laser::ReturnLastScan(int i){


	return samplesVector[i].ReturnLastRange();
}
void Laser::MoveTo(double x,double a){

	p2dProxy.SetSpeed(x,dtor(a));

}
void Laser::NativeObstacleAvoid(){

	double sumLeft, sumRight;
	nativeObstacleAvoid = false;

	this->CheckInTarget();
		if (this->CheckInTarget() == true)
		{
			MoveTo(0,0);

		}
		else{
	for(int i = 60 ; i < 120 ; i++)
	{
		if(ReturnLastScan(i) < 1.5) //jeśli robot napotka przeszkode w zakresie kątowym sick 50-130 bliżej niż ...
		{
			nativeObstacleAvoid = true;
			for(int j = 0; j< 50; j++)
			{
				sumLeft += ReturnLastScan(179 -j);
				sumRight += ReturnLastScan(j);
			}
			if(sumLeft > sumRight )
			{
				MoveTo(0.0,45);
			}
			else
			{
				MoveTo(0.0,-45);
			}
            break;
			//sleep(0.5);
			//MoveTo(0.1,0);
		}
		else if(ReturnLastScan(i-60)< 1.0 || ReturnLastScan(i+59) < 1.0) //przeszkoda z boku
		{
			nativeObstacleAvoid = true;
						for(int j = 0; j< 50; j++)
						{
							sumLeft += ReturnLastScan(179 -j);
							sumRight += ReturnLastScan(j);
						}
						if(sumLeft > sumRight)
						{

							if(ReturnLastScan(0) < 0.5)
							{
								MoveTo(0.0,45);
								sleep(0.5);
							}
							else
							{
								MoveTo(0.0,15);
								sleep(0.5);
							}
						}
						else
						{
							if(ReturnLastScan(180) < 0.5)
							{
							MoveTo(0.0,-45);
							sleep(0.5);
							}
							else
							{
							MoveTo(0.0,-15);
							sleep(0.5);
							}
						}

						break;

		}
	}
					if(ReturnLastScan(0) < 0.7)
					{
						nativeObstacleAvoid = true;
						MoveTo(0.0,-15);
						sleep(0.5);

					}
					else if (ReturnLastScan(179) < 0.7)
					{
						nativeObstacleAvoid = true;
						MoveTo(0.0,15);
						sleep(0.5);

					}

					sleep(0.5);
					MoveTo(0.1,0);
					//sleep(1);
		}
}

void Laser::NativeObstacleAvoid1(){

	double sumLeft, sumRight;
	nativeObstacleAvoid = false;
	this->CheckInTarget();
			if (this->CheckInTarget() == true)
			{
				MoveTo(0,0);

			}
			else{
//front
				for(int i = 60 ; i < 120 ; i++)
					{
						if(ReturnLastScan(i) < 0.5) //jeśli robot napotka przeszkode w zakresie kątowym sick 50-130 bliżej niż ...
						{
							nativeObstacleAvoid = true;
							for(int j = 0; j< 50; j++)
							{
								sumLeft += ReturnLastScan(179 -j);
								sumRight += ReturnLastScan(j);
							}
							if(sumLeft > sumRight )
							{
								MoveTo(0.0,45);
							}
							else
							{
								MoveTo(0.0,-45);
							}
				            break;
							sleep(0.5);
							//MoveTo(0.1,0);
						}
					}

////Strona prawa
				if(ReturnLastScan(0) < 0.7)
									{
										nativeObstacleAvoid = true;
										MoveTo(0.0,20);
										sleep(0.5);

									}

				else if (ReturnLastScan(0) > 0.7 && ReturnLastScan(0) < 0.9)
				{
					nativeObstacleAvoid = true;
					MoveTo(0.2,2);
					sleep(0.5);
				}
///Strona lewa
				if(ReturnLastScan(179) < 0.7)
				{
					nativeObstacleAvoid = true;
					MoveTo(0.0,-20);
					sleep(0.5);
				}

				else if (ReturnLastScan(179) > 0.7 && ReturnLastScan(179) < 0.9)
				{
				nativeObstacleAvoid = true;
				MoveTo(0.2,-2);
				sleep(0.5);
				}






}
}
bool Laser::CheckInTarget(){


	if((target_point.px + tolerancy > p2dProxy.GetXPos() && target_point.px -tolerancy < p2dProxy.GetXPos()) &&
		(target_point.py+tolerancy > p2dProxy.GetYPos() && target_point.py-tolerancy < p2dProxy.GetYPos() ))
	{
		return true;
	}
	else
	{
		return false;
	}


}
