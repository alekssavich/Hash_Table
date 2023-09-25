/*
Author: Aleks Savich
Date Created: 5-13-2019
Date Edited: 5-30-2019
Problem: In this program, you're to create member functions of a given container class.
You must write these functions based on what is told these functions do.
After completing all of the functions, you must test your code with a test program which has been
given and your output must match the test output given to you. 
*/

#ifndef SORTEDARRAY_CPP
#define SORTEDARRAY_CPP

#include "SortedArray.h"

// pre- theSize is a defined integer. theSize and SPARE_CAPACITY are valid integers. theCapacity is valid.
// post- variable theSize is able to update to be 0. theCapacity is able to add those 2 variables and store them. objects is able to update to the newly made dynamic array.
template<typename T>
SortedArray<T>::SortedArray() { // constructor
	theSize = 0; //  sets size of array to 0
	theCapacity = theSize + SPARE_CAPACITY; // sets the capacity of the array to the size + the spare capacity.
	objects = new T[theCapacity]; // intitalizes the dynamic array
}

// pre- from is valid for copying.
// post- operator variable is able to copy from "from".
template<typename T>
SortedArray<T>::SortedArray(const SortedArray<T>& from) { // copy constructor
	operator = (from);
}

// pre- objects is an array with elements.
// post- all the elements in the array objects are deallocated.
template<typename T>
SortedArray<T>::~SortedArray() { // destructor
	delete[] objects; // deallocate the dynamic array
}

// pre- this and from are comparable. from has a function called size() as well as theCapacity.
// post- if this does not equal to the address of from, do the following. elements in objects will be deallocated. theSize will update to the copy constructor size. theCapacity will update to the copy constructor capacity. All the elements in the objects array will update to the copy constructor array. return the pointer of this
template<typename T>
const SortedArray<T>& SortedArray<T>::operator=(const SortedArray& from) { // Assignment operator
	if (this != &from) {
		delete[] objects; // deallocate array
		theSize = from.size(); // copy size
		theCapacity = from.theCapacity; // copy the capacity

		objects = new T[capacity()]; // allocate new array
		for (int k = 0; k < size(); k++) {
			objects[k] = from.objects[k]; // copy all elements in array.
		}
	}
	return *this;
}

// pre- idx is of type int.
// post- return objects with an index of idx.
template<typename T>
const T& SortedArray<T>::operator[](int idx) const { // Assignment operator
	return objects[idx]; // return the element in the array at index
}

// pre- k and theSize are of the same type.
// post- if objects at index k does not equal the copy constructor array at index k then return false.
template<typename T>
bool SortedArray<T>::equals(const SortedArray<T>& rhs) { // boolean equals function.
	for (int k = 0; k < theSize; k++) { // goes through each element in the array and the rhs array.
		if (objects[k] != rhs.objects[k]) { // if the element in the array does not equal to the corresponding element in the rhs array, return false.
			return false;
		}
	}
}
// pre- theSize is defined
// post- return true if theSize equals 0, else return false
template<typename T>
bool SortedArray<T>::empty() { // boolean function to check for empty array
	if (theSize == 0) { // If the array is empty, return true else return false.
		return true;
	}
	else {
		return false;
	}
}
 
// pre- theSize is a defined integer
// post- return theSize
template<typename T>
int SortedArray<T>::size() const {
	return theSize; // return the actual size of the array
}

// pre- theCapacity is a defined integer.
// post- return theCapacity
template<typename T>
int SortedArray<T>::capacity() const {
	return theCapacity; // return the capacity of the array.
}

// pre- newCapacity and theSize are comparable.
// post- return if newCapacity is less than theSize. oldArray is updated to objects array.
template<typename T>
void SortedArray<T>::reserve(int newCapacity) { // reserve function
	if (newCapacity < theSize) {
		return; // return and do nothing if the new requested capacity is smaller than the actual size of the array.
	}
	T* oldArray = objects; // set oldArray = to objects array

	objects = new T[newCapacity]; // objects array is equal to a new allocated array with the new capacity
	for (int k = 0; k < theSize; k++) { // for loop to go through each element in the array
		objects[k] = oldArray[k];
	}
	theCapacity = newCapacity; // set the capacity to the new capacity

	delete[] oldArray; // deallocate old array
}

// pre- k and theSize are both integers.
// post- output objects array at index k, followed by a character delimiter
template<typename T>
void SortedArray<T>::print(ostream &out, char delimiter) const { // print function to print each element of array
	for (int k = 0; k < theSize - 1; k++) { // for loop to print out each element in array followed by a character except last element.
		cout << objects[k] << delimiter;
	}
	cout << objects[theSize - 1]; // print last element in array.
}

// pre- k and theSize are integers
// post- update objects array at index k equal to " ". 
template<typename T>
void SortedArray<T>::clear() {
	for (int k = 0; k < theSize; k++) { // clear every element in the array.
		objects[k] = " ";
	}
}

// pre- theSize and theCapacity are comparable. k and theSize are both integers. l and k are both integers.
// post- objects at index 0 will update to obj. make theSize one bigger. objects at index l is equal to objects at index l - 1. objects at index k is updated to the value of obj. Return.
template<typename T>
void SortedArray<T>::insert(const T& obj) { // insert function to insert an element in the correct position in the array.
	if (theSize == 0) { // if array has a size of 0, insert new element at postion 0 and make the size one bigger.
		objects[0] = obj; // set first element in objects array equal to obj.
		theSize++; // increase theSize by one.
		reserve(theCapacity + 1); // call function reserve to make theCapacity one size bigger.
	}

	else {
		for (int k = 0; k < theSize; k++) {
			if (obj <= objects[k]) { //else, if new element is less than or equal to objects array at k, then move all elements at postion k to the right by one 
				for (int l = theSize; l > k; l--) {
					objects[l] = objects[l - 1]; // for loop to move all elements to the right one postion until location for new element is reached.
				}
				objects[k] = obj; //insert new element at postion k
				theSize++;//increase size by one.
				reserve(theCapacity + 1); // call function reserve to make theCapacity bigger by one.
				return;
			}
		}
		objects[theSize] = obj;
		theSize++;//increase size by one.
		reserve(theCapacity + 1); // call function reserve to make theCapacity bigger by one.
	}
}


// pre- theSize is an integer. 
// post- objects at index k is updated to objects at index k + 1. decrease theSize by 1
template<typename T>
void SortedArray<T>::deleteMin() {
	if (theSize >= 1) { // cant delete element in array if the size of the array is 0.
		for (int k = 0; k < theSize; k++) { // moving every element to the left one postion.
			objects[k] = objects[k + 1]; // move all elements in array to left by one to fill the deleted element. 
		}
		theSize--; // make the size -= 1
		reserve(theCapacity - 1); // call function reserve to make theCapacity bigger by one.
	}
}

// pre- theSize must be a defined integer.
// post- decrease theSize by one
template<typename T>
void SortedArray<T>::deleteMax() {
	if (theSize >= 1) {
		theSize--; // if there is at least one element in the array, make the size - 1.
		reserve(theCapacity - 1); // call function reserve to make theCapacity smaller by one.
	}
}

// pre-
// post- return objects array at index 0.
template<typename T>
const T& SortedArray<T>::findMin() const {
	return objects[0]; // since array is in non decreasing order, return first element in array.
}

// pre- 
// post- return objects at index theSize - 1.
template<typename T>
const T& SortedArray<T>::findMax() const {
	if (theSize != 0) {
		return objects[theSize - 1]; // since array is in non decreasing order, return last element in array.
	}
}

// pre- mid is a valid integer.
// post- add one to mid and set it to low. minus 1 from mid and set it equal to low. Return mid. Return -1
template<typename T>
int SortedArray<T>::binarySearch(const T& obj) { // binary search function
	int low = 0, high = theSize;
	while (low <= high) {
		int mid = (low + high) / 2; // add low + high and divide by 2 to get halfway point in array.
		if (objects[mid] < obj) { // if the midway point is less than the element you're searching for, low = mid + 1 and the function will now look in upper half of the array.
			low = mid + 1;
		}
		else if (objects[mid] > obj) { // if the midway point is greater than the element you're searching for, low = mid - 1 and the function will now look in lower half of the array.
			high = mid - 1;
		}
		else {
			return mid; // if the midway point is equal to what element youre looking for return mid.
		}
	}
	return -1; // if binary search function can not find requested element return -1 indicating no element found.
}

#endif