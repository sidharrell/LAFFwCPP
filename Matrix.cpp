/*
 * Matrix.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Matrix.h"
#include <algorithm>

void Matrix::set_dynamic(bool new_dynamic) {
	dynamic = new_dynamic;
}

void Matrix::_processMakeDiagonal(int sizeAtl) {
	Vector a;
	// processing step:

	// set a to a sub 0 1
	a.components = components + sizeAtl * size_vertical;
	// make sure doesn't run past bottom of matrix
	a.size = max(sizeAtl, size_vertical);
	// 		1. set all (a sub 0 1)'s components to 0
	a.set_to_zero();

	// set a to a sub 2 1
	a.components = components + sizeAtl * size_vertical + sizeAtl + 1;
	// make sure goes negative if past bottom of matrix
	a.size = size_vertical - sizeAtl - 1;
	//		2. set all (a sub 2 1)'s components to 0
	a.set_to_zero();
}

void Matrix::_processMakeLowerTriangular(int sizeAtl) {
	Vector a;
	// processing step:

	// set a to a sub 0 1
	a.components = components + sizeAtl * size_vertical;
	// make sure doesn't run past bottom of matrix
	a.size = max(sizeAtl, size_vertical);
	// 		1. set all (a sub 0 1)'s components to 0
	a.set_to_zero();
}

void Matrix::_processMakeStrictlyLowerTriangular(int sizeAtl) {
	Vector a;
	// processing step:

	// set a to a sub 0 1
	a.components = components + sizeAtl * size_vertical;
	// make sure doesn't run past bottom of matrix
	a.size = max(sizeAtl, size_vertical);
	// 		1. set all (a sub 0 1)'s components to 0
	a.set_to_zero();
	//		2. set alpha to 1
	components[sizeAtl * size_vertical + sizeAtl] = 0;
}

void Matrix::_processMakeUnitLowerTriangular(int sizeAtl) {
	Vector a;
	// processing step:

	// set a to a sub 0 1
	a.components = components + sizeAtl * size_vertical;
	// make sure doesn't run past bottom of matrix
	a.size = max(sizeAtl, size_vertical);
	// 		1. set all (a sub 0 1)'s components to 0
	a.set_to_zero();
	//		2. set alpha to 1
	components[sizeAtl * size_vertical + sizeAtl] = 1;
}

void Matrix::_processMakeUpperTriangular(int sizeAtl) {
	Vector a;

	// set a to a sub 2 1
	a.components = components + sizeAtl * size_vertical + sizeAtl + 1;
	// make sure goes negative if past bottom of matrix
	a.size = size_vertical - sizeAtl - 1;
	//		2. set all (a sub 2 1)'s components to 0
	a.set_to_zero();
}

void Matrix::_processMakeStrictlyUpperTriangular(int sizeAtl) {
	Vector a;

	//		2. set alpha to 0
	components[sizeAtl * size_vertical + sizeAtl] = 0;

	// set a to a sub 2 1
	a.components = components + sizeAtl * size_vertical + sizeAtl + 1;
	// make sure goes negative if past bottom of matrix
	a.size = size_vertical - sizeAtl - 1;
	//		2. set all (a sub 2 1)'s components to 0
	a.set_to_zero();
}

void Matrix::_processMakeUnitUpperTriangular(int sizeAtl) {
	Vector a;

	//		2. set alpha to 1
	components[sizeAtl * size_vertical + sizeAtl] = 1;

	// set a to a sub 2 1
	a.components = components + sizeAtl * size_vertical + sizeAtl + 1;
	// make sure goes negative if past bottom of matrix
	a.size = size_vertical - sizeAtl - 1;
	//		2. set all (a sub 2 1)'s components to 0
	a.set_to_zero();
}

void Matrix::_processTranspose(Matrix& b, int sizeAl) {
	for (int index = 0; index < size_vertical; index++) {
		b.components[this->index(index, sizeAl, b.size_vertical)] =
				components[this->index(sizeAl, index, size_vertical)];
	}
}

void Matrix::_processZeroMatrix(int sizeA_left) {
	Vector a;

	// set a to the column vector
	a.components = components + sizeA_left * size_vertical;
	a.size = size_vertical;

	// set all a's components to 0
	a.set_to_zero();
}

void Matrix::_processIdentityMatrix(int sizeAtl) {
	Vector a;
	// there is an implicit guarantee that the size_horizontal == size_vertical
	// since the Identity matrix is nxn. However, I add a bit of bounds checking
	// on a sub 0 1 (will not run past the bottom of an nxm matrix)
	// and on a sub 2 1 (size is from sizeAtl to bottom of matrix,
	// so will be negative if out of bounds, and so set_to_zero will
	// do nothing)

	// set a to a sub 0 1
	a.components = components + sizeAtl * size_vertical;
	a.size = max(sizeAtl, size_vertical);
	// 		1. set all (a sub 0 1)'s components to 0
	a.set_to_zero();

	//		2. set alpha to 1
	components[sizeAtl * size_vertical + sizeAtl] = 1;

	// set a to a sub 2 1
	a.components = components + sizeAtl * size_vertical + sizeAtl + 1;
	a.size = size_vertical - sizeAtl - 1;
	//		3. set all (a sub 2 1)'s components to 0
	a.set_to_zero();
}

typedef void (Matrix::*intInVoidOut)(int);

void Matrix::_parseTLtoBR(intInVoidOut callback) {
	// Partition A into A sub Top Left, A sub Top Right, A sub Bottom Left, A sub Bottom Right where size of A sub Top Left is 0
	int sizeAtl = 0;
	// we can call the size of A sub Top Left the index in the rest of the comments
	// while size of A sub Top Left is less than size of whole A
	while (sizeAtl < size_horizontal) {
		//
		// repartition into A sub 0 0 (a matrix that is the sub-matrix of the matrix A from 0 to less than the index horizontally and vertically)
		//					A sub 0 2 (a matrix that is the sub-matrix of the matrix A from the index + 1 to the size of A horizontally
		//								and from 0 to the index vertically)
		//					A sub 2 0 (a matrix that is the sub-matrix of the matrix A from 0 to the index horizontally
		//								and from the index plus one to the size of A vertically)
		//					A sub 2 2 (a matrix that is the sub-matrix of the matrix A from the index + 1 to the size of A horizontally
		//								and from the index plus one to the size of A vertically)
		//                  a sub 1 0 Transposed (a vector that is a sub vector of the index'th row vector of the Matrix A from 0 to the index)
		//                  a sub 1 2 Transposed (a vector that is a sub vector of the index'th row vector of the Matrix A from the index + 1 to the size of A)
		//                  a sub 0 1 (a vector that is a sub vector of the index'th column vector of the Matrix A from 0 to the index)
		//                  a sub 2 1 (a vector that is a sub vector of the index'th column vector of the Matrix A from the index + 1 to the size of A)
		//                  alpha (the scalar that is the index'th element of the index'th row (or column) vector)

		(this->*callback)(sizeAtl);

		// Continue with alpha moving from bottom right to top left,
		// a sub 1 0 Transposed moving from bottom to top,
		// a sub 1 2 Transposed moving from bottom to top,
		// a sub 0 1 moving from right to left,
		// a sub 2 1 moving from right to left
		sizeAtl++;
	}

}

void Matrix::_parseLtoR(intInVoidOut callback) {
	// Partition A into A sub Left, A sub Right where size of A sub Left is 0
	int sizeAl = 0;
	// we can call the size of A sub Left the index in the rest of the comments
	// while size of A sub Left is less than the horizontal size of A
	while (sizeAl < size_horizontal) {
		//
		// repartition into A sub 0 (a matrix that is the sub-matrix of the matrix A from 0 to less than the index horizontally)
		//					A sub 2 (a matrix that is the sub-matrix of the matrix A from the index horizontally to the size of A horizontally)
		//                  a sub 1 (the vector that is the index'th column vector of the matrix A)

		(this->*callback)(sizeAl);

		// Continue with a moving from A sub Right to A sub Left
		sizeAl++;
	}

}

typedef void (Matrix::*Matrix_intInVoidOut)(Matrix&, int);

void Matrix::_parseLtoRandTtoB(Matrix_intInVoidOut callback, Matrix& b) {
	if (size_horizontal != b.size_vertical)
		return;
	// Partition A into A sub Left, A sub Right where size of A sub Left is 0
	int sizeAl = 0;
	// we can call the size of A sub Left the index in the rest of the comments
	// while size of A sub Left is less than the horizontal size of A
	while (sizeAl < size_horizontal) {
		//
		// repartition into A sub 0 (a matrix that is the sub-matrix of the matrix A from 0 to less than the index horizontally)
		//					A sub 2 (a matrix that is the sub-matrix of the matrix A from the index horizontally to the size of A horizontally)
		//                  a sub 1 (the vector that is the index'th column vector of the matrix A)

		(this->*callback)(b, sizeAl);

		// Continue with a moving from A sub Right to A sub Left
		sizeAl++;
	}
}

int Matrix::index(int horizontal_position, int vertical_position,
		int vertical_size) {
	return horizontal_position * vertical_size + vertical_position;
}

Matrix::Matrix() {
	components = 0;
	size_horizontal = 0;
	size_vertical = 0;
	dynamic = false;
}

Matrix::Matrix(long double* new_components, int new_size_horizontal,
		int new_size_vertical) {
	components = new_components;
	size_horizontal = new_size_horizontal;
	size_vertical = new_size_vertical;
	dynamic = false;
}

Matrix::Matrix(const Matrix& m) {
	size_horizontal = m.size_horizontal;
	size_vertical = m.size_vertical;
	components = new long double[size_horizontal * size_vertical];
	for (int h = 0; h < size_horizontal; h++) {
		for (int v = 0; v < size_vertical; v++) {
			components[h * size_vertical + v] = m.components[h * size_vertical
					+ v];
		}
	}
	dynamic = true;
}

Matrix& Matrix::operator =(const Matrix& m) {
	if (dynamic)
		delete[] components;
	size_horizontal = m.size_horizontal;
	size_vertical = m.size_vertical;
	components = new long double[size_horizontal * size_vertical];
	for (int h = 0; h < size_horizontal; h++) {
		for (int v = 0; v < size_vertical; v++) {
			components[h * size_vertical + v] = m.components[h * size_vertical
					+ v];
		}
	}
	dynamic = true;
	return *this;
}

Matrix::~Matrix() {
	if (dynamic) {
		delete[] components;
	}
}

bool Matrix::elemental_copy(Matrix& m) {
	if (size_horizontal != m.size_horizontal
			&& size_vertical != m.size_vertical)
		return false;
	for (int h = 0; h < size_horizontal; h++) {
		for (int v = 0; v < size_vertical; v++) {
			components[h * size_vertical + v] = m.components[h * size_vertical
					+ v];
		}
	}
	return true;
}

bool Matrix::testEquality(Matrix& m) {
	if (size_horizontal != m.size_horizontal
			&& size_vertical != m.size_vertical)
		return false;
	for (int h = 0; h < size_horizontal; h++) {
		for (int v = 0; v < size_vertical; v++) {
			if (components[h * size_vertical + v]
					!= m.components[h * size_vertical + v])
				return false;
		}
	}
	return true;
}

bool Matrix::makeDiagonal() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeDiagonal);
	return true;
}

bool Matrix::makeLowerTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeLowerTriangular);
	return true;
}

bool Matrix::makeStrictlyLowerTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeStrictlyLowerTriangular);
	return true;
}

bool Matrix::makeUnitLowerTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeUnitLowerTriangular);
	return true;
}

bool Matrix::makeUpperTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeUpperTriangular);
	return true;
}

bool Matrix::makeStrictlyUpperTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeStrictlyUpperTriangular);
	return true;
}

bool Matrix::makeUnitUpperTriangular() {
	if (size_horizontal != size_vertical)
		return false;
	this->_parseTLtoBR(&Matrix::_processMakeUnitUpperTriangular);
	return true;
}

Matrix Matrix::transpose() {
	long double * components = new long double[size_horizontal * size_vertical];
	Matrix b(components, size_vertical, size_horizontal);
	b.set_dynamic(true);
	this->_parseLtoRandTtoB(&Matrix::_processTranspose, b);
	return b;
}

Matrix Matrix::zeroMatrix(int size_horizontal, int size_vertical) {
	long double * components = new long double[size_horizontal * size_vertical];
	Matrix return_matrix(components, size_horizontal, size_vertical);
	return_matrix.set_dynamic(true);
	return_matrix._parseLtoR(&Matrix::_processZeroMatrix);

	return return_matrix;
}

Matrix Matrix::identityMatrix(int sizeA) {
	long double * components = new long double[sizeA * sizeA];
	Matrix return_matrix(components, sizeA, sizeA);
	return_matrix.set_dynamic(true);
	return_matrix._parseTLtoBR(&Matrix::_processIdentityMatrix);

	return return_matrix;
}
