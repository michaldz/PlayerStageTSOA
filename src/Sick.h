/*
 * Sick.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */
#include <list>

#ifndef SICK_H_
#define SICK_H_

class Sick {

private:
	//przechowuje liste probek z czujnika na danym kacie
	std::list <double> samplesList;
    static const int size = 20;



public:
	std::list <double>::iterator it;
	double listValue[size];
	double listSum;
	void AddSample(double);
    void RemoveSapmle();
    int ReturnSize();
    void ReturnValue();
    int ReturnMaxSize();
    double ReturnLastRange();

	Sick();
	virtual ~Sick();
};

#endif /* SICK_H_ */
