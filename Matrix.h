/*
 * Matrix.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 *
 *      References:
 *      	[1] "Linear Algebra: Foundations to Frontiers, Notes to LAFF with" by Margaret E. Myers, Pierce M. van de Geijn, and Robert A. van de Geijn
 *			https://s3.amazonaws.com/ulaff/LAFFNotes.pdf
 *			[2] "The Science of Programming Matrix Computations" by Robert A. van de Geijn and Enrique S. Quintana-Orti
 *			http://www.lulu.com/us/en/shop/enrique-s-quintana-ort%C3%AD/the-science-of-programming-matrix-computations/ebook/product-17418498.html
 *
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
	// Credit for the algorithm goes to [1], page 87
	Matrix static identityMatrix(int);
	// Credit for the algorithm goes to [1], page 87
	// Updated the algorithm with [1], page 90.
};

#endif /* MATRIX_H_ */
