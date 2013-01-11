// test file for the ListStack class

#include <iostream>
#include "assert.h"
#include "ListStack.h"

using namespace std;

class Thing{
public:
 Thing(int n, int m){
  data = n;
  data = m;
  cout << "thing init with data " << data << endl; 
}
int data;

};
 
int main(){
	//cout << "geezus .. " << endl;
	ListStack<int> hey;
	hey.push(5);
	hey.push(34);
	hey.push(17);
	//hey.pop();
	hey.size();
	//int x = hey.top();
	//int *y = &hey.top();
	//cout << "x is asdasdasda y " << *y << endl;
	cout << "WIN WIN is " << hey.top() << endl;
	//ListStack<int> blah = hey;
	ListStack<int> blah;
	blah = hey;
	cout << "hellooo " << blah.top() << endl;

	//blah = hey;

	//ListStack
	Thing one(5,7);
	//Thing two;
	
	ListStack<Thing> bam;
	
	bam.push(one);
	bam.size();
	//bam.pop();
	//bam.size();
	ListStack<Thing> hah = bam;
	//ListStack<Thing> hah;
	//hah = bam;
	//hah = bam;
	
	//if (bam.empty()){
		//cout << "its empty.. " << endl;
	//}
	//Thing *ha = &bam.top();
	//cout << "aaaa " << ha->data << endl;
	//cout << "what is this .. " << bam.top().data  << endl;
	
	return 0;
}
























/*
// function template
#include <iostream>
using namespace std;

template <typename T> T GetMax (T a, T b) {
  return a > b ? a : b;
}

int main () {
  int i=5, j=6, k;
  long l=10, m=5, n;
  k=GetMax<int>(i,j);
  n=GetMax<long>(l,m);
  cout << k << endl;
  cout << n << endl;
  return 0;
}



#include <iostream>
using namespace std;

template <typename T, typename V> T tomb (T a, V b)
{ 
  return a > b ? a : b;
}

template <class Y>
class mypair {
  Y values [2];
  public:
    mypair (Y first, Y second)
    {
      values[0]=first; values[1]=second;
    }
	
	Y getV(int n){
		return values[n];
	}
};

int main()
{
  int i = 5;
  float j = 4;
  int k = tomb(i,j);
  // cout << "k is " << k << endl; 
  
  mypair<int> obj(105, 555);
  cout << "obj first value is " << obj.getV(1) << endl;
  return 0;
}

/*

template <class myType>
myType GetMax (myType a, myType b) {
 T result; // if myType is int, this is equivalent to 'int result;'
 return (a>b?a:b);
}

*/