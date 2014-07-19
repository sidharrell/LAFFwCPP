/*
 * Vector.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Vector.h"
#include <cmath>

Vector::Vector(long double * initial_components, int initial_size) {
	components = initial_components;
	size = initial_size;
}

Vector::~Vector() {
	// TODO Auto-generated destructor stub
}

long double * Vector::getComponentsAddress() {
	return components;
}

int Vector::getSize() {
	return size;
}

bool Vector::testEquality(Vector otherVector) {
	long double * otherComponents = otherVector.getComponentsAddress();
	int otherSize = otherVector.getSize();
	if (size != otherSize) return false;
	for (int i = 0; i < otherSize; i++) {
		if (components[i] != otherComponents[i]) return false;
	}
	return true;
}

bool Vector::add(Vector vector1, Vector vector2) {
	if (size != vector1.getSize() && size != vector2.getSize()) return false;
	for (int index = 0; index < size; index++) {
		components[index] = vector1.getComponentsAddress()[index] + vector2.getComponentsAddress()[index];
	}
	return true;
}

bool Vector::scale(long double alpha) {
	for (int index = 0; index < size; index++) {
		components[index] *= alpha;
	}
	return true;
}

bool Vector::axpy(long double alpha, Vector x) {
	if (size != x.getSize()) return false;
	long double * x_components = x.getComponentsAddress();
	for (int index = 0; index < size; index++) {
		components[index] += alpha*x_components[index];
	}
	return true;
}

bool Vector::linear_combination(Vector* vectors, Vector coefficients) {
	for (int index = 0; index < size; index++) {
		components[index] = 0;
	}
	long double * coefficients_array = coefficients.getComponentsAddress();
	for (int index = 0; index < coefficients.getSize(); index++) {
		this->axpy(coefficients_array[index], vectors[index]);
	}
	return true;
}

long double Vector::dot_product(Vector y) {
	long double alpha = 0;
	if (size != y.getSize()) return 0;
	long double * y_components = y.getComponentsAddress();
	for (int index = 0; index < size; index++) {
		alpha += components[index]*y_components[index];
	}
	return alpha;
}

long double Vector::dot_product(Vector* y) {
	return this->dot_product(*y);
}

long double Vector::length() {
	return sqrt(this->dot_product(this));
}
