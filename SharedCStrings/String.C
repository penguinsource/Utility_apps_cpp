// Mihai Oprescu
// -------------
// Shared C Strings class

#include "String.H"
#include <iostream>
#include <cstring>

String::String(const char *p){		// constructor
	shared = new SharedCString;		// allocate memory for object
	shared->data = new char[strlen(p)];	// allocate memory for char pointer
	
	shared->n = strlen(p);			// get length of 'p'
	strcpy(shared->data, p);		// copy p into shared->data
	shared->data[shared->n] = '\0';	// add \0 at end of string
	shared->count = 1;				// set the reference count to 1
}

String::~String(){					// destructor
	shared->count--;
	if (shared->count < 1){			// if 0 references.. 
		delete [] shared->data;		// release char array
		delete shared;				// release memory by deleting 'shared' pointer
	}
}

String::String(const String &x){
	shared = x.shared;	// point to the object in argument
	shared->count++;	// increase the reference count
}

String& String::operator=(const String &x){		// AO
	shared->count--;	// decrease ref count of the object calling the function
	shared = x.shared;	// point the calling object to the new object's address
	shared->count++;	// increase ref count of the object
	
	return *this;		// return this object
}

int String::size() const{
	return shared->n;	// return 'n'
}

int String::ref_count() const{
	return shared->count;	// return 'count'
}

const char* String::cstr() const{
	return shared->data;	// return 'data'
}
