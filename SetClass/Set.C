// Mihai Oprescu
// -------------
// Memory efficient method of holding a set of (integer) values
// Set class

#include "Set.H"
#include <iostream>
#include <cstring>
#include <math.h>

Set::Set(int narg){
		//std::cout << "Constructor called" << std::endl;
	n = narg;										// save var n
	a = ceil((double) n / (double)INT_BITS);		// number of allocated ints
	bits = new int[a]();	// create new array of ints and set them all to 0
}
  
Set::~Set(){
		//std::cout << "Destructor called" << std::endl;
	delete [] bits;
}

Set::Set(const Set &x){
		//std::cout << "CC called" << std::endl;
	n = x.n;			// copy values 'n' and 'a' to this set
	a = x.a;
	bits = new int[a]();	// create new array of ints and set them all to 0
	for (int j=0; j < a; j++){
		bits[j] = x.bits[j];		// copy each int of set x to this set
	}
}

Set& Set::operator=(const Set &x){
		//std::cout << "AO called" << std::endl;
	delete [] bits;		// delete array of ints
	n = x.n;			// copy values 'n' and 'a' to this set
	a = x.a;
	bits = new int[a]();	// create new array of ints and set them all to 0
	for (int j=0; j < a; j++){
		bits[j] = x.bits[j];	// copy each int of set x to this set
	}
	return *this;
}

void Set::clear(){
	for (int j=0; j < a; j++){
		bits[j] = 0;			// set each int of the set to 0
	}
	//n = 0;						// set the set's vars to 0
	//a = 0;
}

void Set::complement(){
	for (int j=0; j < a; j++){
		bits[j] = ~bits[j];		// complement each int of the set
	}
}

bool Set::has(int x) const{
	assert(x < n);		// check if int x can be added to this set (0 <= x < n)
	int int_index = ceil((double)(x+1) / (double)INT_BITS) - 1;	// get int index
	int shift_by = x - 32*int_index;							// get value to shift by
	
	if (bits[int_index] & (1 << shift_by)){			// OR operation that checks if a bit
		return 1;									// is set to 1 or not. if it is, 
	}else{											// the set contains 'x' and function
		return 0;									// returns 1
	}
}

void Set::add(int x){
	assert(x < n);			// check if int x can be added to this set (0 <= x < n)
	int int_index = ceil((double)(x+1) / (double)INT_BITS) - 1;	// get int index
	int shift_by = x - 32*int_index;							// get value to shift by
	
	bits[int_index] = bits[int_index] | (1 << shift_by);   // OR operation adds x to the set
}
  
void Set::remove(int x){
	assert(x < n);		// check if int x can be removed from this set (0 <= x < n)
	if (this->has(x)){
		int int_index = ceil((double)(x+1) / (double)INT_BITS) - 1;	// get int index
		int shift_by = x - 32*int_index;							// get value to shift by
		
		bits[int_index] = bits[int_index] & ~(1 << shift_by);  	// binary operation (& and ~)
																// removes x from the set
	}
	// otherwise nothing to remove from the set..
}

// add all elements of s to set; pre-cond: s.n == n
void Set::add(const Set &s){
	assert(s.get_n() == n);	// check if s.n == n
	
	for (int j = 0; j < s.get_a(); j++){	//go through each int j of set 's'
	  for (int i = 0; i < 32; i++){			//go through each bit i of int j
		int value = 32*j + i;	// value of bit position
		if (value < n){			// check set boundaries
			if (s.has(value)){		// if set 's' has the int 'value'
				this->add(value);	// add it to this set
			}
		}
	  }
	}
}

// remove all elements of s from set; pre-cond: s.n == n
void Set::remove(const Set &s){
	assert(s.get_n() == n);	// check if s.n == n
	for (int j = 0; j < s.get_a(); j++){	//go through each int j of set 's'
	  for (int i = 0; i < 32; i++){			//go through each bit i of int j
		int value = 32*j + i;	// value of bit position
		if (value < n){			// check set boundaries
			if (s.has(value)){			// if set 's' has the int 'value'
				this->remove(value);	// remove it from this set
			}
		}
	  }
	}
}

  // return maximum number of elements
int Set::get_n() const { return n; }

  // return number of ints allocated
int Set::get_a() const { return a; }

// print elements to output stream os like so: 
// [ 1 2 4 5 ]
// for set {1,2,4,5}
void Set::print(std::ostream &os) const{
		os << "[ "; 					// print '['
		for (int j = 0; j < a; j++){		//go through each int j of this set
		  for (int i = 0; i < 32; i++){		//go through each bit i of int j
				int shift = (1 << i);		// get shift position
				int toPrint = (bits[j] & shift);
				if (toPrint != 0){
					os << (32*j + i) << " ";		// print value found at bit i 
				}										// of int j in this set
		  }
		}
		os << "]";		// print ']'
}

