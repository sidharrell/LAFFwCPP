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

/**
 * The class Matrix should be able to generate zero and identity matrices
 * and instantiate Matrix objects that can operate on themselves, and
 * perform GEMV and GEMM operations.
 */
class Matrix {
	/**
	 *
	 */

	int size_horizontal;
	int size_vertical;
	bool dynamic;

	void set_dynamic(bool);

public:

	/**
	 * a column-wise 2D array
	 * so the first column consists from 0 to the size_horizontal-1,
	 * second column from size_horizontal to 2*size_horizontal-1, etc,
	 * up to the size_vertical
	 * size_horizontal and size_vertical are passes into the object on instantiation
	 */
	long double * components;

	Matrix();

	/**
	 *
	 * @param new_components
	 * @param new_size_horizontal
	 * @param new_size_vertical
	 *
	 * Remember that components are added column-wise
	 * so the first column consists from 0 to the size_horizontal-1,
	 * second column from size_horizontal to 2*size_horizontal-1, etc,
	 * up to the size_vertical
	 */
	Matrix(long double *, int, int);

	/** Copy Constructor
	 *
	 * @param m Matrix to be copied
	 */
	Matrix(const Matrix&);

	/**
	 *
	 * @param m Matrix to be used in assignment
	 * @return
	 */
	Matrix& operator= (const Matrix&);
	virtual ~Matrix();

	/**
	 *
	 * @return horizontal size of the Matrix
	 */
	int getHorizontalSize() {return size_horizontal;};

	/**
	 *
	 * @return vertical size of the Matrix
	 */
	int getVerticalSize() {return size_vertical;};

	bool elemental_copy(Matrix&);
	bool testEquality(Matrix&);

	bool makeDiagonal();
	void processMakeDiagonal(int);

	bool makeLowerTriangular();
	void processMakeLowerTriangular(int);

	bool makeStrictlyLowerTriangular();
	void processMakeStrictlyLowerTriangular(int);

	bool makeUnitLowerTriangular();
	void processMakeUnitLowerTriangular(int);

	bool makeUpperTriangular();
	void processMakeUpperTriangular(int);

	bool makeStrictlyUpperTriangular();
	void processMakeStrictlyUpperTriangular(int);

	bool makeUnitUpperTriangular();
	void processMakeUnitUpperTriangular(int);

	Matrix transpose();
	void processTranspose(long double**, int);

	Matrix static zeroMatrix(int, int);
	// Credit for the algorithm goes to [1], page 87
	void processZeroMatrix(int);

	Matrix static identityMatrix(int);
	// Credit for the algorithm goes to [1], page 87
	// Updated the algorithm with [1], page 90.
	void processIdentityMatrix(int);

	typedef void(Matrix::*AfromLtoR)(int);
	typedef void(Matrix::*AfromTLtoBR)(int);
	typedef void(Matrix::*AfromLtoR_BfromTtoB)(long double**, int);

	void parseTLtoBR(AfromTLtoBR);
	void parseLtoR(AfromLtoR);
	void parseLtoRandTtoB(AfromLtoR_BfromTtoB, long double*);
};

#endif /* MATRIX_H_ */
