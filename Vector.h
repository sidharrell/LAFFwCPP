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
public:
	Vector(long double * initial_components, int initial_size);
	Vector(const Vector& v);
	virtual ~Vector();
	long double * getComponentsAddress();
	int getSize();
	bool testEquality(Vector otherVector);
	bool add(Vector vector1, Vector vector2);
	bool scale(long double alpha);
	bool axpy(long double alpha, Vector x);
	bool linear_combination(Vector * vectors, Vector coefficients);
	long double dot_product(Vector y);
	long double dot_product(Vector * y);
	long double length();
};

#endif /* VECTOR_H_ */
