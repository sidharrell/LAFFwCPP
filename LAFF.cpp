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

int main() {
	array<long double, 4> data1 {2, 3, 4, 5};
	array<long double, 4> data2 {6, 7, 8, 9};
	array<long double, 4> output;
	Vector sample_vector(data1.data(),data1.size());
	Vector sample_vector2(data2.data(),data2.size());
	Vector output_vector(output.data(), output.size());
	output_vector.add(sample_vector, sample_vector2);
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	long double * output_array = sample_vector.getComponentsAddress();
	int output_size = sample_vector.getSize();
	long double product = 1;
	for (int index = 0; index < output_size; index++) {
		product *= output_array[index];
	}
	cout << "product of all the components of vector 1: " << product << endl;
	cout << "vector 1 == vector 2: " << sample_vector.testEquality(sample_vector2) << endl;
	cout << "vector 3 = vector 1 + vector 2: (";
	for (int index = 0; index < output_vector.getSize(); index++) {
		cout << output_vector.getComponentsAddress()[index];
		if (index != output_vector.getSize()-1) cout << ", ";
	}
	cout << ")" << endl;
	output_vector.scale(-2);
	cout << "vector 3 scaled by -2: (";
	for (int index = 0; index < output_vector.getSize(); index++) {
		cout << output_vector.getComponentsAddress()[index];
		if (index != output_vector.getSize()-1) cout << ", ";
	}
	cout << ")" << endl;
	return 0;
}
