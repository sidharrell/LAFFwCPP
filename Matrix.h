/*
 * Matrix.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */
#include "Vector.h"
#ifndef MATRIX_H_
#define MATRIX_H_


class Matrix {
	Vector * components;
	int size;
	int index;
public:
	Matrix(Vector * vectors, int initial_size);
	virtual ~Matrix();
	int getSize() {return size;};
};

#endif /* MATRIX_H_ */
