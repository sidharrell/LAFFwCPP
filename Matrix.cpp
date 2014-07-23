/*
 * Matrix.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Matrix.h"

void Matrix::set_dynamic(bool new_dynamic) {
	dynamic = new_dynamic;
}

Matrix::Matrix() {
	components = 0;
	size_horizontal = 0;
	size_vertical = 0;
	dynamic = false;
}

Matrix::Matrix(long double* new_components, int new_size_horizontal, int new_size_vertical) {
	components = new_components;
	size_horizontal = new_size_horizontal;
	size_vertical = new_size_vertical;
	dynamic = false;
}

Matrix::Matrix(const Matrix& m) {
	size_horizontal = m.size_horizontal;
	size_vertical = m.size_vertical;
	components = new long double [size_horizontal*size_vertical];
	for (int h=0;h<size_horizontal;h++) {
		for(int v=0;v<size_vertical;v++) {
			components[h*size_vertical + v] = m.components[h*size_vertical + v];
		}
	}
	dynamic = true;
}

Matrix& Matrix::operator =(const Matrix& m) {
	if (dynamic) delete[] components;
	size_horizontal = m.size_horizontal;
	size_vertical = m.size_vertical;
	components = new long double [size_horizontal*size_vertical];
	for (int h=0;h<size_horizontal;h++) {
		for(int v=0;v<size_vertical;v++) {
			components[h*size_vertical + v] = m.components[h*size_vertical + v];
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
	if (size_horizontal != m.size_horizontal && size_vertical != m.size_vertical) return false;
	for (int h=0;h<size_horizontal;h++) {
		for(int v=0;v<size_vertical;v++) {
			components[h*size_vertical + v] = m.components[h*size_vertical + v];
		}
	}
}

bool Matrix::testEquality(Matrix& m) {
	if (size_horizontal != m.size_horizontal && size_vertical != m.size_vertical) return false;
	for (int h=0;h<size_horizontal;h++) {
		for(int v=0;v<size_vertical;v++) {
			if (components[h*size_vertical + v] != m.components[h*size_vertical + v]) return false;
		}
	}
	return true;
}

Matrix Matrix::zeroMatrix(int size_horizontal, int size_vertical) {
	long double * components = new long double [size_horizontal*size_vertical];
	// Partition new matrix A into A sub Left and A sub Right where A sub Left has 0 columns
	int horizontal_index = 0;
	// while size of A sub left is less than size of whole A
	while (horizontal_index < size_horizontal) {
		// repartition into A sub 0 (a matrix that is the sub-matrix of the matrix A from 0 to less than horizontal index)
		//                  a sub 1 (a vector that is the index'th column vector of the Matrix A)
		//                  A sub 2 (a matrix that is the sub-matrix of the matrix A from greater than the horizontal index to the horizontal size of A)

		// processing step:
		// 		set a sub 1 to zero
		for (int vertical_index=0;vertical_index<size_vertical;vertical_index++) {
			components[horizontal_index*size_horizontal+vertical_index] = 0;
		}
		// Continue with a sub 1 moved from A sub Right to a sub Left
		horizontal_index++;
	}
	Matrix return_matrix(components, size_horizontal, size_vertical);
	return_matrix.set_dynamic(true);
	return return_matrix;
}

Matrix Matrix::identityMatrix(int sizeA) {
	long double * components = new long double [sizeA*sizeA];
	// Partition A into A sub Top Left, A sub Top Right, A sub Bottom Left, A sub Bottom Right where size of A sub Top Left is 0
	int sizeAtl = 0;
	// we can call the size of A sub Top Left the index in the rest of the comments
	// while size of A sub Top Left is less than size of whole A
	while (sizeAtl < sizeA) {
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

		// processing step:
		// 		1. set all (a sub 0 1)'s components to 0
		//		2. set alpha to 1
		//		3. set all (a sub 2 1)'s components to 0

		for (int index=0;index<sizeAtl;index++) {
			components[sizeAtl*sizeA+index] = 0;
		}

		components[sizeAtl*sizeA+sizeAtl] = 1;

		for (int index=sizeAtl+1;index<sizeA;index++) {
			components[sizeAtl*sizeA+index] = 0;
		}

		// Continue with alpha moving from bottom right to top left,
		// a sub 1 0 Transposed moving from bottom to top,
		// a sub 1 2 Transposed moving from bottom to top,
		// a sub 0 1 moving from right to left,
		// a sub 2 1 moving from right to left
		sizeAtl++;
	}

	Matrix return_matrix(components, size, size);
	return_matrix.set_dynamic(true);
	return return_matrix;
}
