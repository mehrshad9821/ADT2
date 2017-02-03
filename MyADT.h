/*
 * filename: MyADT.h
 * 
 * Class Description: A data collection ADT class to satisfy Assn 1's requiremetns.
 * Class Invariant: Data collection with the following characteristics:
 *                   - Each element is unique (no duplicate).
 *                   - Once it has been ascertained that the element has not already been 
 *                     inserted, its data structure allows insertion in O(1)
 *                   - Once the element to be removed as been found, 
 *                     its data structure allows removal in O(1).
 *                   - Its data structure is resizable: when full, it expands to accommodate 
 *                     new element insertions. This is done unbeknown to the client code.
 *
 * Creation date: 05/30/2016
 * Author:	Mehrshad Matin
 */

 #pragma once
#include "Profile.h"
#include <string>
using namespace std;


class MyADT
{

private:
    static const int MIN_BLOCK_SIZE=5;
    int elementCount;
    int arrayLength;
    int maxChar;
    
	Profile* Array;

	// Description: Searches for target element. Returns target position in array.
    int searchPosition(const Profile& target);
public:

	MyADT();
	~MyADT();

	// Description: Returns the total of elements currently stored in MyADT.
	int  getElementCount() const;

	// Description: Inserts an element.
	// Precondition: newElement must not already be in data collection.  
	// Postcondition: newElement inserted and the appropriate elementCount has been incremented.
		
	bool insert(const Profile& newElement);

	// Description: Removes an element. 
	// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.	
	bool remove(const Profile& toBeRemoved);

	// Description: Searches for target element.
	Profile* search(const Profile& target);

	// Description: Removes all elements.
	void removeAll();

	// Description: Prints all elements stored in MyADT.
	friend ostream & operator<<(ostream & os, const MyADT& rhs);
};

