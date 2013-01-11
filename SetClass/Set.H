// Mihai Oprescu
// -------------
// Memory efficient method of holding a set of (integer) values
// Set class

#ifndef Set_H
#define Set_H

#include <iostream>
#include <cassert>

static const int INT_BITS = sizeof(int) * 8;
// represents a set of integers 0..n-1

class Set
{
public:

  Set(int narg);                   	// create empty subset of {0..n-1}
  ~Set();                       	// destructor
  Set(const Set &s);            	// copy constructor
  Set& operator=(const Set &s); 	// assignment operator
  void clear();              		// empty set
  void complement();         		// negate set (x was in set before <=> x is not in set after)
  bool has(int x) const;     		// return true iff x is element of set (0 <= x < n)
  void add(int x);           		// add element x to set (0 <= x < n)
  void remove(int x);        		// remove element x from set (0 <= x < n)
    
  // add all elements of s to set; pre-cond: s.n == n
  void add(const Set &s);

  // remove all elements of s from set; pre-cond: s.n == n
  void remove(const Set &s);

  // return maximum number of elements
  int get_n() const;
  
  // return number of ints allocated
  int get_a() const;
    
  // print elements to output stream os like so: 
  // [ 1 2 4 5 ]
  // for set {1,2,4,5}
  void print(std::ostream &os = std::cout) const;
  
private:

  int *bits; // array of integers storing bits (x in set <=> bit x = 1)
  int n;     // max. number of elements (elements are 0,1,...n-1)
  int a;     // number of allocated ints
};
  
#endif

