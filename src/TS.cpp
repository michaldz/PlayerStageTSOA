/*
 * TS.cpp
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#include "TS.h"

TS::TS() {

	//tabTargetFunction[this->SickResolution()];
	//tabOffsetLeft[this->SickResolution()];
	//tabOffsetRight[this->SickResolution()];


	targets.resize(this->SickResolution());

}

TS::~TS() {
	// TODO Auto-generated destructor stub
}

void TS::CalculateTargetFunction(){


	for(int i = 0 ; i < this->SickResolution(); i++)
	{

     if (this->angleToTarget >  this->SickResolution())
      {
		if(i < (this->SickResolution()/2))
		{
			tabTargetFunction[i] =((this->ReturnSickSize(i)+1)*this->laserRange-this->ReturnSickListSum(i)) - ( ((this->ReturnSickSize(i)+1)*this->laserRange) -    std::abs(((this->angleToTarget) + (-(this->SickResolution()/2) + i))));
		}
		else
			{
			tabTargetFunction[i] = ((this->ReturnSickSize(i)+1)*this->laserRange-this->ReturnSickListSum(i)) - ( ((this->ReturnSickSize(i)+1)*this->laserRange) -  std::abs(((this->angleToTarget) + (i-(this->SickResolution()/2) )))) - this->robotOrientationInDegrees ;
			}
      }
      else
      {
    	  if(i < (this->SickResolution()/2))
    	  		{
    	  			tabTargetFunction[i] =((this->ReturnSickSize(i)+1)*this->laserRange-this->ReturnSickListSum(i)) - ( ((this->ReturnSickSize(i)+1)*this->laserRange) -    std::abs(((this->angleToTarget) + (-(this->SickResolution()/2) + i))));
    	  		}
    	  		else
    	  			{
    	  			tabTargetFunction[i] = ((this->ReturnSickSize(i)+1)*this->laserRange-this->ReturnSickListSum(i)) - ( ((this->ReturnSickSize(i)+1)*this->laserRange) -  std::abs(((this->angleToTarget) + (i-(this->SickResolution()/2) ))));
    	  			}


      }





      //Degreeetotarget mierzone od środka przodu robota
					                 //po prawej stronie robota stomnie odejmowane
					                //po lewej dodawane
                                   //TODO zmienić magicnumber na
			                      // Laser::SickListMaxSize * max zakres czujnika
		//this->ReturnSickListSum(i) + ( (this->ReturnSickSize(i)*this->laserRange)

	}


/*	this->ReadScan();
	this->ReadDegreesToTarget();
	this->ReadDistanceToTarget();
	this->PrintValuesToConsole(10);
*/
}

void TS::CalculateOffset(){

	for(int i = 1 ; i < this->SickResolution()+ 1; i++)
		{


		if(i < (this->SickResolution()/2))
		  	{

			targets[(i-1)].offsetLeftValue = std::abs((this->angleToTarget) + (-(this->SickResolution()/2) + (i-1)));
			targets[(i-1)].obstacleDegrees = std::abs((this->robotOrientationInDegrees) + (-(this->SickResolution()/2) + (i-1)));
	   		}
		    else
		    {
		    	targets[(i-1)].offsetLeftValue = std::abs((this->angleToTarget) + ((i-1)-(this->SickResolution()/2))) ;
		    	targets[(i-1)].obstacleDegrees = std::abs((this->robotOrientationInDegrees) + ((i-1)-(this->SickResolution()/2))) ;



            }
					targets[(i-1)].offsetRightValue = 360 - targets[(i-1)].offsetLeftValue;
					targets[(i-1)].position = (i-1);

}

}



void TS::PrintTargetFunction(int number){


	for(int i = 0 ; i < number ;i++)

		{
			std::cout << "distanceSum" << i << ": " << this->ReturnSickListSum(i) << std::endl;
			std::cout << "tabLeft" << i << ": " << targets[i].offsetLeftValue << std::endl;
			std::cout << "tabRight" << i << ": " << targets[i].offsetRightValue << std::endl;


		}

	std::stable_sort(targets.begin(),targets.end(),Target::RightComparator);
	std::cout << "Direction " << chosenDirection << std::endl;

	for(int i = 0 ; i < number ;i++)
	{

		std::cout << "posegregowaneR" << i << ": " << targets[i].offsetRightValue << " "<< targets[i].position << " "  <<targets[i].position -90 <<std::endl;


	}

	std::stable_sort(targets.begin(),targets.end(),Target::LeftComparator);


		for(int i = 0 ; i < number ;i++)
		{

			std::cout << "posegregowaneL" << i << ": " << targets[i].offsetLeftValue << " "<< targets[i].position << " "  <<targets[i].position -90 << std::endl;


		}
		std::cout << "NOA" << this->nativeObstacleAvoid << std::endl;

}
void TS::PrintTargetFunction(){

	PrintTargetFunction((int)this->SickResolution());

}

void TS::TabuLAdd(int tar){

          TabuList a;
          a.tlValue = tar;
		  tabuL.push_front(a);

	if ((int)tabuL.size() > tabuLSize){

		tabuL.pop_back();
	}


}

void TS::TabuSearchMainAlgoritchm(){

	this->CheckInTarget();
	if (this->CheckInTarget() == true)
	{
		MoveTo(0,0);

	}
	else
	{


	int minLeft, minRight;
	//bool move = true;

	std::stable_sort(targets.begin(),targets.end(),Target::LeftComparator);
	 minLeft = targets[0].offsetLeftValue;


	std::stable_sort(targets.begin(),targets.end(),Target::RightComparator);
	 minRight = targets[0].offsetRightValue;

	//wybór kierunku skrętu na podstawie uchybu od celu
	if(minLeft < minRight)
	{
		chosenDirection = 0;
		std::stable_sort(targets.begin(),targets.end(),Target::LeftComparator);
	}
	else
	{
		chosenDirection = 1;
	}

	//iteracja po elementach Target( od najmniejszego uchybu)
	for(int i = 0 ; i < this->SickResolution(); i++){

		if (this->ReturnLastScan(targets[i].position) > acceptObstacleDistance)
		{
			//Sprawdzanie wystąpienia na liście tabu
			//TODO wygładzenie skętu
			if(TabuLCheck(i) == false && nativeObstacleAvoid == false)
			{


				this->MoveTo(0.1,0.0);
				if (chosenDirection == 0)
				{

				this->MoveTo(0.1,  (targets[i].position -90)/2);
				//sleep(0.5);
				//this->MoveTo(0.2,  (targets[i].position -90));
				}
				else
				{
				this->MoveTo(0.1,-(90 -targets[i].position)/2);
				//sleep(0.5);
				//this->MoveTo(0.2,-(90 -targets[i].position));

				}
				sleep(1);
				//this->ReadScan();
				//this->NativeObstacleAvoid();
				if(nativeObstacleAvoid == false)
				{
					this->MoveTo(0.2,0);
				}

				break;
			}


		}
		else
		{
			//dodaje kierunek główny kierunek robota do listy tabu
				TabuLAdd((int)targets[(i)].obstacleDegrees);
		}


	}
	}

}
bool TS::TabuLCheck(int i){

	for(int j = 0 ; j < tabuLSize; j++){

			if( targets[i].obstacleDegrees < (tabuL[j].tlValue +0.5) && targets[i].obstacleDegrees > (tabuL[j].tlValue -0.5))
			{
				return true;
			}
	}


return false;

}

void TS::PrintTabuL(){

	for(int k = 0; k < tabuLSize; k++){


		std::cout << "TL" << k << ": " << tabuL[k].tlValue << std::endl;

	}

}
