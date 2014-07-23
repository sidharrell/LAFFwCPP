/*
 * Vector.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 *
 *       I explicitly removed the copy constructor, destructor, and assignment operator. There is now way
 *       (as far as I can tell) to prevent a memory leak if I introduce a deep copy. There is only one destructor, and it
 *       cannot distinguish between an object constructed with the constructor, and so whose components have been created
 *       on the heap by the client code, and an object constructed by the copy constructor, and so whose components have
 *       have been created on the heap by the copy constructor. If the destructor does not delete the components, then the
 *       components will go out of scope and be destroyed when the client code ends in the former case, and not be destroyed
 *       when the client code ends in the latter case, causing a memory leak. If the destructor deletes the components, then
 *       the components will be destroyed in the latter case when the client code ends and the copy goes out of scope, but in
 *       in the former case, the components will be destroyed twice, once when the components go out of scope, and again when
 *       the object goes out of scope. The best strategy, AFAIK, is to have the class be a shallow-copy type, or a deep-copy
 *       type. Since I don't want to incur the expense of deep-copying everything, I'm electing to have this be the shallow-copy
 *       type. Every array that it operates on must be created in the client code.
 *       It makes the client code a bit awkward, since you have to create an answer vector.
 *       Light Bulb!! have a switch that tells the destructor whether it was dynamically, or statically created.
 *       Actually, memory freed may not immediately be reported as freed by the OS. Rechecked, and this looks good.
 */

#ifndef VECTOR_H_
#define VECTOR_H_


using namespace std;

class Vector {
	int size; // size of the array pointed to by the Vector
	bool dynamic; // was the object created in the client code, or in an internal method? If it was created internally,
	// then responsibility for destroying it lies internally, and it need to be deep cleaned in the destructor, and at
	// the start of the assignment operator overloading. if it was created in the client code, then responsibility for
	// freeing the original pointed to memory lies with the client code.

	void set_dynamic(bool); // needed an internal method of switching a vector created by passing in an existing array over
	// to a vector that holds the only reference to the memory holding the components internally. See the static function
	// zero_vector and the vector addition method, add.

public:
	long double * components; // publically accessible because it makes the client code much cleaner. be aware, and don't
	// trust contents. you don't know where it's been.

	Vector(); // creates the 'zero' vector of length 0. components of the resulting vector is a null pointer (=0)
	// nothing internal to delete. deletion of the vector object is the responsibility of the client code

	Vector& operator= (const Vector&); // copies the vector passed in onto the previously declared Vector that is initialized with
	// the Vector object returned by this method. if the previously declared Vector was created dynamically (by a method
	// other than creating the array in the client code and passing it into the constructor, so that the memory allocated to the
	// components was 'new'd inside a vector object or static method) then the components memory is freed.
	// a new array of long doubles is then allocated, then the elements of the vector passed in are copied onto the components,
	// a new Vector is created, marked as dynamic, and passed to the client code. While the Vector will deallocate it's own internal
	// components, it is still the responsibility of the client code to delete the Vector itself.

	Vector (const Vector&); // creates a copy of the vector passed into the constructor. the array of long doubles
	// is 'new'd in the copy constructor, so it will be deleted in the destructor.

	Vector(long double * initial_components, int initial_size); // non-dynamic Vector is created. it is the responsibility of the
	// client code to delete the Vector that is created and the components array that was passed in.

	~Vector(); // destructor will free the memory of the components if the components memory was allocated internally, aka.
	// dynamically.

	int getSize(); // gotta make the client code work a little bit

	bool copy(Vector&); // does a element-wise copy of the vector passed in onto the vector of the calling object.

	bool testEquality(Vector&); // element-wise comparison

	Vector add(Vector&); // adds the calling vector to the passed in vector, creates a new vector and passes it out.

	void scale(long double); // scales the calling vector by the passed in scalar

	bool axpy(long double, Vector&); // adds the passed in vector scaled by the passed in scalar to the calling vector.

	Vector linear_combination(Vector *); // scales the i'th passed in vector by the i'th component of the calling vector
	// then adds all the resultant vectors together. returned vector's components were allocated internally, so the resultant
	// vector needs to clean up after itself

	long double dot_product(Vector&); // returns the scalar resultant from the transpose of the calling vector multiplied by the
	// passed in vector

	long double length(); // returns the scalar length of the vector. somewhat protected from overflow.

	Vector	static  zero_vector(int); // returns a vector of the passed in length will all elements set to zero
};

#endif /* VECTOR_H_ */
