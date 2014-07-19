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
	array<long double, 3> lc_vector_data_1 {1, 0, 0};
	array<long double, 3> lc_vector_data_2 {0, 1, 0};
	array<long double, 3> lc_vector_data_3 {0, 0, 1};
	array<long double, 3> lc_vector_data_4 {-3, 2, 4};
	array<long double, 3> answer_data {0, 0, 0};
	Vector lc_vector1(lc_vector_data_1.data(), lc_vector_data_1.size());
	Vector lc_vector2(lc_vector_data_2.data(), lc_vector_data_2.size());
	Vector lc_vector3(lc_vector_data_3.data(), lc_vector_data_3.size());
	Vector matrix[] = {lc_vector1, lc_vector2, lc_vector3};
	Vector lc_vector4(lc_vector_data_4.data(), lc_vector_data_4.size());
	Vector answer(answer_data.data(), answer_data.size());
	answer.linear_combination(matrix, lc_vector4);
	cout << "linear combination: (";
	for (int index = 0; index < answer.getSize(); index++) {
		cout << answer.getComponentsAddress()[index];
		if (index != answer.getSize()-1) cout << ", ";
	}
	cout << ")" << endl;
	array<long double, 4> dot_vector_data_1 {2, 5, -6, 1};
	array<long double, 4> dot_vector_data_2 {1, 2, 3, 4};
	array<long double, 4> dot_vector_data_3 {1, 0, 0, 2};
	array<long double, 4> dot_answer_data {0, 0, 0, 0};
	Vector dot_vector1(dot_vector_data_1.data(), dot_vector_data_1.size());
	Vector dot_vector2(dot_vector_data_2.data(), dot_vector_data_2.size());
	Vector dot_vector3(dot_vector_data_3.data(), dot_vector_data_3.size());
	Vector dot_answer(dot_answer_data.data(), dot_answer_data.size());
	dot_answer.add(dot_vector1, dot_vector2);
	long double dot = dot_answer.dot_product(dot_vector3);
	cout << "dot product: " << dot << endl;
	return 0;
}
