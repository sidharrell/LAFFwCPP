/*
 * Vector.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#ifndef VECTOR_H_
#define VECTOR_H_

using namespace std;

class Vector {
	long double * components;
	int size;
	int index;
public:
	Vector(long double * initial_components, int initial_size);
	virtual ~Vector();
	long double * getComponentsAddress();
	int getSize();
	bool testEquality(Vector otherVector);
	bool add(Vector vector1, Vector vector2);
	bool scale(long double alpha);
};

#endif /* VECTOR_H_ */
