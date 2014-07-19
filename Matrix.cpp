/*
 * Matrix.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Matrix.h"

Matrix::Matrix(Vector * vectors, int initial_size) {
	bool sizeCheck = true;
	int n = 0;
	if (initial_size > 0) n = vectors[0].getSize();
	for (index = 0; index < initial_size; index++) {
		if (vectors[index].getSize() != n) sizeCheck = false;
	}
	if (sizeCheck) {
		components = vectors;
		size = initial_size;
		index = 0;
	} else {
		size = 0;
	}
}

Matrix::~Matrix() {
	// TODO Auto-generated destructor stub
}

