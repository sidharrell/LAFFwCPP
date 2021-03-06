/*
 * Vector.h
 *
 *  Created on: Jul 19, 2014
 *      Author: sidney
 *
 *      References:
 *      	[1] "Linear Algebra: Foundations to Frontiers, Notes to LAFF with" by Margaret E. Myers, Pierce M. van de Geijn, and Robert A. van de Geijn
 *			https://s3.amazonaws.com/ulaff/LAFFNotes.pdf
 *			[2] "The Science of Programming Matrix Computations" by Robert A. van de Geijn and Enrique S. Quintana-Orti
 *			http://www.lulu.com/us/en/shop/enrique-s-quintana-ort%C3%AD/the-science-of-programming-matrix-computations/ebook/product-17418498.html
 *
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

/**
 * The Vector class should be able to instantiate the zero vector and Vector objects should be able to perform basic
 * Vector-Scalar and Vector-Vector operations.
 */
class Vector {

	/**
	 * was the object created in the client code, or in an internal method? If it was created internally,
	// then responsibility for destroying it lies internally, and it need to be deep cleaned in the destructor, and at
	// the start of the assignment operator overloading. if it was created in the client code, then responsibility for
	// freeing the original pointed to memory lies with the client code.
	 */
	bool dynamic;

	/**
	 * needed an internal method of switching a vector created by passing in an existing array over
	// to a vector that holds the only reference to the memory holding the components internally. See the static function
	// zero_vector and the vector addition method, add.
	 * @param
	 */
	void set_dynamic(bool);

public:

	/**
	 * The length of the vector. It is public because occasionally you may want to have a vector that you can set as the column vector
	 *  of a matrix. You could do this by creating new vector for each column, but having the size publicly available saves some
	 *  processing.  But with great power comes great responsibility. Remember that if you set this larger than your data set, you will
	 *  stomp on someone else's data.
	 */
	int size;

	/**
	 * Publicly accessible because it makes the client code much cleaner. be aware, and leave it lying around. Is there a 3 second rule for data?
	 */
	long double * components;

	/**
	 * creates the 'zero' vector of length 0. components of the resulting vector is a null pointer (=0)
	 * nothing internal to delete. deletion of the vector object is the responsibility of the client code
	 */
	Vector();

	/**
	 * Copies the vector passed in onto the previously declared Vector that is initialized with
	 * the Vector object returned by this method. if the previously declared Vector was created dynamically (by a method
	 * other than creating the array in the client code and passing it into the constructor, so that the memory allocated to the
	 * components was 'new'd inside a vector object or static method) then the components memory is freed.
	 * a new array of long doubles is then allocated, then the elements of the vector passed in are copied onto the components,
	 * a new Vector is created, marked as dynamic, and passed to the client code. While the Vector will deallocate it's own internal
	 * components, it is still the responsibility of the client code to delete the Vector itself.
	 * @param v The vector to be copied
	 * @return a reference to the new vector, same as the old vector
	 */
	Vector& operator=(const Vector&);

	/**
	 * Creates a copy of the vector passed into the constructor. the array of long doubles
	 * is 'new'd in the copy constructor, so it will be deleted in the destructor.
	 * @param v The vector to be copied
	 */
	Vector(const Vector&);

	/**
	 * Non-dynamic Vector is created. it is the responsibility of the
	 * client code to delete the Vector that is created and the components array that was passed in.
	 * @param initial_components pointer to the first element of the data array
	 * @param initial_size the length of the vector
	 */
	Vector(long double *, int);

	/**
	 * Destructor will free the memory of the components if the components memory was allocated internally, aka.dynamically.
	 */
	~Vector();

	/**
	 * Copy the passed into vector onto the current vector, element by element
	 * Credit for the algorithm goes to [1], page 10
	 * @param x
	 * @return true if the operation was successful
	 */
	bool copy(Vector&);

	/**
	 * Compare the passed in vector to the current vector, element by element
	 * Credit for the algorithm goes to [1], page 9, Definition 1.4
	 * @param v the vector to be compared
	 * @return true if the operation was successful
	 */
	bool testEquality(Vector&);

	/**
	 * Adds the current vector to the passed in vector, creates a new vector and passes it out.
	 * Credit for the algorithm goes to [1], page 12
	 * @param v
	 * @return The vector that is the sum of the current vector and the passed in vector
	 */
	Vector add(Vector&);

	/**
	 * Scales the calling vector by the passed in scalar
	 * Credit for the algorithm goes to [1], page 14
	 * @param alpha
	 */
	void scale(long double);

	/**
	 * Adds the passed in vector scaled by the passed in scalar to the calling vector.
	 * Credit for the algorithm goes to [1], page 18
	 *
	 * @param alpha
	 * @param x
	 * @return true if the operation was successful
	 */
	bool axpy(long double, Vector&);

	/**
	 * Scales the i'th passed in vector by the i'th component of the calling vector
	 * then adds all the resultant vectors together. returned vector's components were allocated internally, so the resultant
	 * vector needs to clean up after itself
	 * Credit for the algorithm goes to [1], page 20
	 * @param vectors an array of vectors
	 * @return the vector that results from the linear combination of the current vector with the array of vectors passed in
	 */
	Vector linear_combination(Vector *);

	/**
	 * Returns the scalar resulting from the transpose of the current vector multiplied by the passed in vector
	 * Credit for the algorithm goes to [1], page 24
	 * @param y the vector to be dotted with the current vector
	 * @return the dot product of the current vector and the passed in vector
	 */
	long double dot_product(Vector&);

	/**
	 * Returns the scalar length of the vector. somewhat protected from overflow.
	 * Credit for the algorithm goes to [1], page 44, the discussion of overflow and underflow
	 * @return the length of the current vector from the origin to the point defined by the elements
	 */
	long double length();

	/**
	 * Set all the elements of the current vector to zero
	 */
	void set_to_zero();

	/**
	 * Produce a vector of size m with all zeros
	 * @param size m
	 * @return A vector of size m with all zeros
	 */
	Vector static zero_vector(int); // returns a vector of the passed in length will all elements set to zero
};

#endif /* VECTOR_H_ */
