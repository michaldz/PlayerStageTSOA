/*
 * Sick.cpp
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#include "Sick.h"

Sick::Sick() {
	// ustawienie wielkości

}

Sick::~Sick() {
	// TODO Auto-generated destructor stub
}
void Sick::AddSample(double sam){

	samplesList.push_front(sam);

}
void Sick::RemoveSapmle(){

	if((int)samplesList.size() < size){}
	else {samplesList.pop_back();}


}
int Sick::ReturnSize(){

	return samplesList.size();

}
void Sick::ReturnValue(){


	int a = 0;
    listSum = 0;
	for(it = samplesList.begin(); it != samplesList.end(); ++it)
	{
		listValue[a] = *it;
		listSum += *it;
		a++;
	}

}
int Sick::ReturnMaxSize(){

	return size;

}
double Sick::ReturnLastRange(){

return listValue[0];
}
