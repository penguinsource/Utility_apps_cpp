// Mihai Oprescu
// -------------
// Shared C Strings test file

#include "String.H"
#include <iostream>
using namespace std;

int main()
{
  String a("aaa"), b("bbbb");  // construct
  String u = b;                // copy construct
  String v("cccc");
  v = a;                       // assign

  cout << "a: " << a.cstr() << " " << a.size() << " " << a.ref_count() << endl
       << "b: " << b.cstr() << " " << b.size() << " " << b.ref_count() << endl
       << "u: " << u.cstr() << " " << u.size() << " " << u.ref_count() << endl
       << "v: " << v.cstr() << " " << v.size() << " " << v.ref_count() << endl;
}

/*

  output:

s: aaa 3 2
t: bbbb 4 2
u: bbbb 4 2
v: aaa 3 2

*/
