/*
 * filename: MyADT.cpp
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
 * Author: Mehrshad Matin
 */
 
#include <iostream>
#include <string>
#include <cctype>
#include <locale>


#include "Profile.h"
#include "MyADT.h"


using namespace std;


//Default Constructor
MyADT::MyADT(){
	elementCount = 0;
	Array = new Profile[MIN_BLOCK_SIZE];
	arrayLength = MIN_BLOCK_SIZE;
    maxChar=26;
}

//Default Destructor
MyADT::~MyADT(){
    delete [] Array;
}


// Description: Returns the total of elements currently stored in MyADT.
int  MyADT::getElementCount() const {
	return elementCount;
}



// Description: Inserts an element.
// Precondition: newElement must not already be in data collection.  
// Postcondition: newElement inserted and the appropriate elementCount has been incremented.

bool MyADT::insert(const Profile& newElement) {
    int position=searchPosition(newElement);
    if(position!=-1)
        return false;
	if (elementCount >= arrayLength) {
    	arrayLength += MIN_BLOCK_SIZE;
        Profile *newArray=new Profile[arrayLength];
		for (int i = 0; i < elementCount; i++) {
			newArray[i] = Array[i];
		}
        delete [] Array;
        Array=newArray;
	}
	int key=tolower(newElement.getName()[0])-'a';
	maxChar=(key>maxChar)? key : maxChar;
	Array[elementCount++] = newElement;
	return true;
}

// Description: Removes an element. 
// Postcondition: toBeRemoved is removed and the appropriate elementCount has been decremented.	
bool MyADT::remove(const Profile& toBeRemoved) {
    int position;
    position=searchPosition(toBeRemoved);
    if(position!=-1) {
        for(int i=position+1; i<elementCount; i++)
            Array[i-1]=Array[i];
        elementCount--;
        return true;        
    }
    else
        return false;
}


// Description: Searches for target element.
int MyADT::searchPosition(const Profile& target) {
    int position=-1;
    for(int i=0; i<elementCount; i++) {
        if(Array[i]==target) {
            position=i;
            break;
        }
    }
    return position;
}


// Description: Searches for target element.
Profile* MyADT::search(const Profile& target) {
    Profile* element=NULL;
    int position=searchPosition(target);
    if(position!=-1) {
        element=&Array[position];
    }
    return element;
}



// Description: Removes all elements.
void MyADT::removeAll() {
    elementCount=0;
}

// Description: Prints all elements stored in MyADT.
//  It sorts the array of profiles using counting sort. 
ostream & operator<<(ostream & os, const MyADT& rhs) {
    int count[26];
   
    if(!rhs.elementCount)
        return os;
    Profile *output[rhs.elementCount];
    for(int i=0; i<26; i++) 
        count[i]=0;
    for(int i=0; i<rhs.elementCount; i++) {
        int key=tolower(rhs.Array[i].getName()[0])-'a';
        count[key]++;
    }
    
    int total=0;
    for(int i=0; i<rhs.maxChar; i++) {
        int oldCount=count[i];
        count[i]=total;
        total+=oldCount;        
    }
    for(int i=0; i<rhs.elementCount; i++) {
        int key=tolower(rhs.Array[i].getName()[0])-'a';
        output[count[key]] = &rhs.Array[i];
        count[key]++;
    }
    for(int i=0; i<rhs.elementCount; i++) {
        os << *output[i];
    }
    return os;   
}

