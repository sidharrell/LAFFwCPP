/*
 * Vector.cpp
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 */

#include "Vector.h"

Vector::Vector(long double * initial_components, int initial_size) {
	components = initial_components;
	size = initial_size;
	index = 0;
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
	for (index = 0; index < size; index++) {
		components[index] = vector1.getComponentsAddress()[index] + vector2.getComponentsAddress()[index];
	}
	return true;
}

bool Vector::scale(long double alpha) {
	for (index = 0; index < size; index++) {
		components[index] *= alpha;
	}
	return true;
}
