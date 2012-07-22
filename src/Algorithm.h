/*
 * Algorithm.h
 *
 *  Created on: 2012-05-20
 *      Author: michal
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "TS.h"

class Algorithm: public TS {
public:
			bool onTarget;

	void Test();


	Algorithm();
	virtual ~Algorithm();
};

#endif /* ALGORITHM_H_ */
