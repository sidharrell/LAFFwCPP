/*
 * Vector.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Vector.h"
#include <cmath>
#include <stdlib.h>

Vector::Vector() {
	components = 0;
	size = 0;
	dynamic = false;
}

Vector::Vector(long double * initial_components, int initial_size) {
	components = initial_components;
	size = initial_size;
	dynamic = false;
}

Vector& Vector::operator =(const Vector& v) {
	if (dynamic) delete[] components;
	size = v.size;
	components = new long double [size];
	for (int i=0; i<size; i++) {
		components[i] = v.components[i];
	}
	dynamic = true;
	return *this;
}

Vector::Vector(const Vector& v) {
	size = v.size;
	components = new long double [size];
	for (int i=0; i<size; i++) {
		components[i] = v.components[i];
	}
	dynamic = true;
}

Vector::~Vector() {
	if (dynamic) {
		delete[] components;
	}
}

long double * Vector::getComponentsAddress() {
	return components;
}

int Vector::getSize() {
	return size;
}

bool Vector::copy(Vector& x) {
	long double * chi = x.getComponentsAddress();
	int x_size = x.getSize();
	if (size != x_size) return false;
	for (int i=0; i<size; i++) {
		components[i] = chi[i];
	}
	return true;
}

bool Vector::testEquality(Vector& otherVector) {
	long double * otherComponents = otherVector.getComponentsAddress();
	int otherSize = otherVector.getSize();
	if (size != otherSize) return false;
	for (int i = 0; i < otherSize; i++) {
		if (components[i] != otherComponents[i]) return false;
	}
	return true;
}

bool Vector::add(Vector& vector1, Vector& vector2) {
	if (size != vector1.getSize() && size != vector2.getSize()) return false;
	long double * v1 = vector1.getComponentsAddress();
	long double * v2 = vector2.getComponentsAddress();
	for (int index = 0; index < size; index++) {
		components[index] = v1[index] + v2[index];
	}
	return true;
}

bool Vector::scale(long double alpha) {
	for (int index = 0; index < size; index++) {
		components[index] *= alpha;
	}
	return true;
}

bool Vector::axpy(long double alpha, Vector& x) {
	if (size != x.getSize()) return false;
	long double * x_components = x.getComponentsAddress();
	for (int index = 0; index < size; index++) {
		components[index] += alpha*x_components[index];
	}
	return true;
}

bool Vector::linear_combination(Vector* vectors, Vector& coefficients) {
	for (int index = 0; index < size; index++) {
		components[index] = 0;
	}
	long double * coefficients_array = coefficients.getComponentsAddress();
	for (int index = 0; index < coefficients.getSize(); index++) {
		if (!this->axpy(coefficients_array[index], vectors[index])) return false;
	}
	return true;
}

long double Vector::dot_product(Vector& y) {
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
	long double max_component = 0;
	long double * new_data;
	new_data = new long double [size];
	for (int index = 0; index < size; index++) {
		if (components[index] > max_component) max_component = components[index];
		new_data[index] = components[index];
	}
	Vector scaled(new_data, size);
	scaled.scale(1/max_component);
	long double result = max_component*sqrt(scaled.dot_product(scaled));
	delete new_data;
	return result;
}
