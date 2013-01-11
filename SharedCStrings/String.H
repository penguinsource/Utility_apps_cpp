// Mihai Oprescu
// -------------
// Shared C Strings class

#ifndef String_H
#define String_H

#include <iostream>

class String
{
public:

  // constructor
  String(const char *p);
  
  // destructor
  ~String();

  // copy constructor
  String(const String &x);

  // assignment operator
  String& operator=(const String &x); 
  
  // return number of non-0 characters in string
  int size() const;

  // return reference count
  int ref_count() const;
  
  // returns pointer to character array
  const char *cstr() const;
 
private:

  // data containing character strings
  // shared by Strings when copying/assigning
  struct SharedCString
  {
    char *data; // 0-terminated char array
    int n;      // number of non-0 characters in string
    int count;  // reference count
  };
  
  SharedCString *shared;
};

#endif

