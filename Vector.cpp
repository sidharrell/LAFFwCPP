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
	int x_size = x.getSize();
	if (size != x_size) return false;
	for (int i=0; i<size; i++) {
		components[i] = x.components[i];
	}
	return true;
}

void Vector::set_dynamic(bool new_dynamic) {
	dynamic = new_dynamic;
}

bool Vector::testEquality(Vector& v) {
	if (size != v.getSize()) return false;
	for (int i = 0; i < size; i++) {
		if (components[i] != v.components[i]) return false;
	}
	return true;
}

Vector Vector::add(Vector& v) {
	long double * elements = new long double [size];
	Vector w(elements, size);
	w.set_dynamic(true);
	if (size == v.getSize()) {
		for (int i=0; i<size; i++) {
			w.components[i] = v.components[i] + components[i];
		}
	}
	return w;
}

void Vector::scale(long double alpha) {
	for (int index = 0; index < size; index++) {
		components[index] *= alpha;
	}
}

bool Vector::axpy(long double alpha, Vector& x) {
	if (size != x.getSize()) return false;
	for (int index = 0; index < size; index++) {
		components[index] += alpha*x.components[index];
	}
	return true;
}

Vector Vector::linear_combination(Vector* vectors) {
	Vector w = Vector::zero_vector(size);
	for (int index = 0; index < size; index++) {
		if (!w.axpy(components[index], vectors[index])) break;
	}
	return w;
}

long double Vector::dot_product(Vector& y) {
	long double alpha = 0;
	if (size == y.getSize()) {
		for (int index = 0; index < size; index++) {
			alpha += components[index]*y.components[index];
		}
	}
	return alpha;
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

Vector Vector::zero_vector(int size) {
	long double * elements = new long double [size];
	Vector return_vec(elements, size);
	return_vec.scale(0);
	return_vec.set_dynamic(true);
	return return_vec;
}
