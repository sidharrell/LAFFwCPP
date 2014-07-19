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

