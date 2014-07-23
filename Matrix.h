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
	int size_horizontal;
	int size_vertical;
	bool dynamic;

	void set_dynamic(bool);

public:
	long double * components;

	Matrix();
	Matrix(long double *, int, int);
	Matrix(const Matrix&);
	Matrix& operator= (const Matrix&);
	virtual ~Matrix();

	int getHorizontalSize() {return size_horizontal;};
	int getVerticalSize() {return size_vertical;};

	bool elemental_copy(Matrix&);
	bool testEquality(Matrix&);

	Matrix static zeroMatrix(int, int);
	Matrix static identityMatrix(int);
};

#endif /* MATRIX_H_ */
