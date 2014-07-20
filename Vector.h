/*
 * Vector.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 *
 *      I explicitly removed the copy constructor, destructor, and assignment operator. There is now way
 *       (as far as I can tell) to prevent a memory leak if I introduce a deep copy. There is only one destructor, and it
 *       cannot distinguish between an object constructed with the constructor, and so whose components have been created
 *       on the heap by the client code, and an object constructed by the copy constructor, and so whose components have
 *       have been created on the heap by the copy constructor. If the destructor does not delete the components, then the
 *       components will go out of scope and be destroyed when the client code ends in the former case, and not be destroyed
 *       when the client code ends in the latter case, causing a memory leak. If the destructor deletes the components, then
 *       the components will be destroyed in the latter case when the client code ends and the copy goes out of scope, but in
 *       in the former case, the components will be destroyed twice, once when the components go out of scope, and again when
 *       the object goes out of scope. The best strategy, AFAIK, is to have the class be a shallow-copy type, or a deep-copy
 *       type. Since I don't want to incur the expense of deep-copying everything, I'm electing to have this be the shallow-copy
 *       type. Every array that it operates on must be created in the client code.
 *
 */

#ifndef VECTOR_H_
#define VECTOR_H_


using namespace std;

class Vector {
	long double * components;
	int size;
public:
	Vector(long double * initial_components, int initial_size);
	long double * getComponentsAddress();
	int getSize();
	bool copy(Vector& x);
	bool testEquality(Vector& otherVector);
	bool add(Vector& vector1, Vector& vector2);
	bool scale(long double alpha);
	bool axpy(long double alpha, Vector& x);
	bool linear_combination(Vector * vectors, Vector& coefficients);
	long double dot_product(Vector& y);
	long double dot_product(Vector * y);
	long double length();
};

#endif /* VECTOR_H_ */
