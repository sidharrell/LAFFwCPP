//============================================================================
// Name        : LAFF.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <array>
#include "Vector.h"
using namespace std;

void test_vector_addition_and_scaling() {
	long double data1[] = {2, 3, 4, 5};
	long double data2[] = {6, 7, 8, 9};
	const int VECTOR_SIZE = 4;

	Vector sample_vector(data1, VECTOR_SIZE);
	Vector sample_vector2(data2, VECTOR_SIZE);

	const string test = sample_vector.testEquality(sample_vector2) ? "true" : "false";
	cout << "vector 1 == vector 2: " << test << endl;

	Vector output_vector = sample_vector.add(sample_vector2);

	cout << "vector 3 = vector 1 + vector 2: (";
	for (int index = 0; index < VECTOR_SIZE; index++) {
		cout << output_vector.components[index];
		if (index != VECTOR_SIZE-1) cout << ", ";
	}
	cout << ")" << endl;

	long double product = 1;
	for (int i=0; i<VECTOR_SIZE; i++) {
		product *= output_vector.components[i];
	}
	cout << "product of all the components of vector 3: " << product << endl;

	output_vector.scale(-2);
	cout << "vector 3 scaled by -2: (";
	for (int index = 0; index < VECTOR_SIZE; index++) {
		cout << output_vector.components[index];
		if (index != VECTOR_SIZE-1) cout << ", ";
	}
	cout << ")" << endl;
}
void test_linear_combinations() {
	const int VECTOR_SIZE1 = 2;
	const int VECTOR_SIZE2 = 4;

	long double v[VECTOR_SIZE1][VECTOR_SIZE2] = { {2, 4, -1, 0}, {1, 0, 1, 0} };
	long double x[] = {3, 2};
	Vector vec_array[] = {Vector(v[0], VECTOR_SIZE2),
			Vector(v[1], VECTOR_SIZE2)};
	Vector x_vec(x, VECTOR_SIZE1);
	Vector w_vec = x_vec.linear_combination(vec_array);
	cout << "linear combination: (";
	for (int index = 0; index < VECTOR_SIZE2; index++) {
		cout << w_vec.components[index];
		if (index != VECTOR_SIZE2-1) cout << ", ";
	}
	cout << ")" << endl;
}
void test_dot_product() {
	const int VECTOR_SIZE = 4;

	long double data[3][VECTOR_SIZE] = { {2, 5, -6, 1}, {1, 2, 3, 4}, {1, 0, 0, 2} };
	Vector v[] = { Vector(data[0], VECTOR_SIZE),
			Vector(data[1], VECTOR_SIZE),
			Vector(data[2], VECTOR_SIZE) };
	Vector w = v[0].add(v[1]);
	long double dot = w.dot_product(v[2]);
	cout << "(vector 1 + vector 2) dot vector 3: " << dot << endl;
}

void test_length() {
	const int VECTOR_SIZE = 4;

	long double data[] = {2, 5, -6, 1};
	Vector v(data, VECTOR_SIZE);
	cout << "length: " << v.length() << endl;
}

void test_copy() {
	const int VECTOR_SIZE = 3;

	long double data[] = {1, 2, 3};
	Vector v(data, VECTOR_SIZE);
	long double data2[] = {4, 5, 6};
	Vector x(data2, VECTOR_SIZE);
	v.copy(x);
	cout << "copy: (";
	for (int index = 0; index < VECTOR_SIZE; index++) {
		cout << v.components[index];
		if (index != VECTOR_SIZE-1) cout << ", ";
	}
	cout << ")" << endl;
}

int main() {
	test_vector_addition_and_scaling();

	test_linear_combinations();

	test_dot_product();

	test_length();

	test_copy();

	string temp;

	cin >> temp;

	return 0;
}


