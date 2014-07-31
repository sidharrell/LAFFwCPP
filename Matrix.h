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

	void _processMakeDiagonal(int);

	void _processMakeLowerTriangular(int);

	void _processMakeStrictlyLowerTriangular(int);

	void _processMakeUnitLowerTriangular(int);

	void _processMakeUpperTriangular(int);

	void _processMakeStrictlyUpperTriangular(int);

	void _processMakeUnitUpperTriangular(int);

	void _processTranspose(Matrix&, int);

	// Credit for the algorithm goes to [1], page 87
	void _processZeroMatrix(int);

	/**
	 * The processing step of the matrix A being turned into the identity matrix
	 * Credit for the algorithm goes to [1], page 87
	 * Updated the algorithm with [1], page 90.
	 * @param sizeAtl the current size of A Top Left
	 */
	void _processIdentityMatrix(int);

	/**
	 * Define a pointer to a method of Matrix that takes an integer and returns nothing
	 * @param an integer
	 */
	typedef void (Matrix::*intInVoidOut)(int);

	/**
	 * Take the current matrix and parse it from the Top Left to the Bottom Right
	 * @param callback The function that will do the processing step on the Matrix
	 */
	void _parseTLtoBR(intInVoidOut);

	/**
	 * Take the current matrix and parse it from Left to Right
	 * @param callback The function that will do the processing step on the current vector
	 */
	void _parseLtoR(intInVoidOut);

	/**
	 * Define a pointer to a function that takes in a reference to a Matrix object and an integer and returns nothing
	 * @param a reference to a Matrix object
	 * @param an integer
	 */
	typedef void (Matrix::*Matrix_intInVoidOut)(Matrix&, int);

	/**
	 * Take the current matrix of size m x n and parse it from Left to Right,
	 * at the same time take a matrix B of size p x m and parse it from Top to Bottom.
	 * @param callback The function that will do the processing step on the current vectors. Since the current vector of B will be a row vector,
	 *  the callback must accept an array of pointers to long doubles and an int that is the size of A sub 0.
	 *
	 * @param b The matrix B.
	 */
	void _parseLtoRandTtoB(Matrix_intInVoidOut, Matrix&);

	/**
	 * Find the index for an array element at the horizontal_position and the vertical_position inside a matrix with a vertical_size
	 * @param horizontal_position The horizontal postion of the element
	 * @param vertical_position The vertical position of the element
	 * @param vertical_size The vertical size of the matrix containing the element
	 * @return
	 */
	int static index(int, int, int);

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
	 * Construct a new Matrix of size m x n that operates on the data provided.
	 * Remember that components are added column-wise
	 * so the first column consists of components from 0 to n-1,
	 * second column from n to (2*n)-1, etc,
	 * up to m columns
	 * @param new_components pointer to the array of long doubles. The size of the array should be m * n
	 * @param new_size_horizontal m
	 * @param new_size_vertical n
	 */
	Matrix(long double *, int, int);

	/**
	 * Copy Constructor
	 * @param m Matrix to be copied
	 */
	Matrix(const Matrix&);

	/**
	 * Copy the Matrix to the right of the assignment operator to the Matrix on the left
	 * @param m Matrix to be used in assignment
	 * @return a reference to the new matrix, same as the old matrix
	 */
	Matrix& operator=(const Matrix&);

	/**
	 * The Destructor. 'nuff said.
	 */
	virtual ~Matrix();

	/**
	 * Get the horizontal size of the current Matrix
	 * @return the horizontal size
	 */
	int getHorizontalSize() {
		return size_horizontal;
	}
	;

	/**
	 * Get the vertical size of the current Matrix
	 * @return the vertical size
	 */
	int getVerticalSize() {
		return size_vertical;
	}
	;

	/**
	 * Perform an element by element copy of the Matrix B onto the current Matrix
	 * @param m the Matrix B
	 * @return true if the operation was successful
	 */
	bool elemental_copy(Matrix&);

	/**
	 *
	 * @param m
	 * @return
	 */
	bool testEquality(Matrix&);

	/**
	 * Perform an operation on the current matrix that makes everything off the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeDiagonal();

	/**
	 * Perform an operation on the current matrix that makes everything above the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeLowerTriangular();

	/**
	 * Perform an operation on the current matrix that makes the diagonal all zeros and everything above the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeStrictlyLowerTriangular();

	/**
	 * Perform an operation on the current matrix that makes the diagonal all ones and everything above the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeUnitLowerTriangular();

	/**
	 * Perform an operation on the current matrix that makes everything below the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeUpperTriangular();

	/**
	 * Perform an operation on the current matrix that makes the diagonal all zeros and everything below the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeStrictlyUpperTriangular();

	/**
	 * Perform an operation on the current matrix that makes the diagonal all ones and everything below the diagonal a zero
	 * @return a false if the operation was unsuccessful
	 */
	bool makeUnitUpperTriangular();

	/**
	 * Produce a matrix of size n x m that is the transpose of the current matrix of size m x n
	 * @return a matrix that is the transpose of the current matrix
	 */
	Matrix transpose();

	/**
	 * Produce a matrix of size m x n filled with zeros
	 * Credit for the algorithm goes to [1], page 87
	 * @param size_horizontal m
	 * @param size_vertical n
	 * @return a matrix of size m x n
	 */
	Matrix static zeroMatrix(int, int);

	/**
	 * Produce a matrix of size n x n
	 * Credit for the algorithm goes to [1], page 89
	 * @param sizeA n
	 * @return a matrix of size n x n
	 */
	Matrix static identityMatrix(int);
};

#endif /* MATRIX_H_ */
