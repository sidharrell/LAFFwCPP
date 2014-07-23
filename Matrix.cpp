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

Matrix Matrix::identityMatrix(int size) {
	long double * components = new long double [size*size];
	// Partition new matrix A into A sub Left and A sub Right where A sub Left has 0 columns
	int horizontal_index = 0;
	// while size of A sub Left is less than size of whole A
	while (horizontal_index < size) {
		// repartition into A sub 0 (a matrix that is the sub-matrix of the matrix A from 0 to less than horizontal index)
		//                  a sub 1 (a vector that is the index'th column vector of the Matrix A)
		//                  A sub 2 (a matrix that is the sub-matrix of the matrix A from greater than the horizontal index to the horizontal size of A)

		// processing step:
		// 		set the a sub 1 to the correct unit basis vector
		for (int vertical_index=0;vertical_index<size;vertical_index++) {
			if (vertical_index == horizontal_index) {
				components[horizontal_index*size+vertical_index] = 1;
			} else {
				components[horizontal_index*size+vertical_index] = 0;
			}
		}
		// Continue with a sub 1 moved from A sub Right to a sub Left
		horizontal_index++;
	}

	Matrix return_matrix(components, size, size);
	return_matrix.set_dynamic(true);
	return return_matrix;
}
