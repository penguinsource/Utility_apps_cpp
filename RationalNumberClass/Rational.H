// Mihai Oprescu
// -------------
// Rational Number Class

#ifndef RATIONAL_H
#define RATIONAL_H

// templated rational number class stores fractions num/den
// where num,den are integer variables of type T
//
// invariant: den > 0 && gcd(abs(num),den) = 1

#include <iostream>
#include <cassert>
#include <cmath>

template <typename T>
class Rational
{
public:
  
  // 0/1
  Rational();
  
  // num/1
  Rational(const T& num);

  // set up num/den and normalize, pre: den != 0
  Rational(const T& num, const T& den);
  
  ~Rational() { }
  
  // return numerator, denominator
  T get_num() const;
  T get_den() const;

  void set_num(T arg){		// set numerator of a Rational object
	numerator = arg;
  }
  
  void set_den(T arg){		// set denominator of a Rational object
	denumerator = arg;
  }
   
  double value() const;		// return double approximation

  // after each artithmetic operation the result needs to be normalized
  Rational operator+(const Rational &rhs) const;
  Rational operator-(const Rational &rhs) const;
  Rational operator*(const Rational &rhs) const;

  Rational operator/(const Rational &rhs) const;	// pre: rhs != 0
  Rational &operator+=(const Rational &rhs);
  Rational &operator-=(const Rational &rhs);
  Rational &operator*=(const Rational &rhs);
  Rational &operator/=(const Rational &rhs);		// pre: rhs != 0

  Rational& operator--();
  Rational& operator++();
  Rational operator++(int);
  Rational operator--(int);


private:
	T numerator;
	T denumerator;
  // num and den have no commmon factor > 1
  void normalize(); // pre-cond: den != 0, change num/den such that den > 0, 
  T gcd(T a, T b);	// pre-cond: a, b > 0,  return greatest common divisor of a and b
};

//-----------------------------------------
// ------------- Definitions of functions :

// writes [num/den] to os
template <typename T>
std::ostream &operator<<(std::ostream &os, const Rational<T> &r) {
  //normalize();
  os << "[" << r.get_num() << "/" << r.get_den() << "]";
  return os;
}

template <class T>				// constructor
Rational <T>::Rational(){
	numerator = 0;
	denumerator = 1;
}

template <class T> 				// constructor takes 1 arg, den is set to 1
Rational <T>::Rational(const T& num){
	numerator = num;
	denumerator = 1;
}

template <class T>				// constructor takes 2 args
Rational <T>::Rational(const T& num, const T& den){
	assert(den != 0);
	numerator = num;
	denumerator = den;
	normalize();				// normalize (in case of 2 negatives or simplif.)
}

template <class T>
double Rational <T>::value() const{
	double ans = (double) numerator / (double) denumerator;
	return ans;
}

template <class T>
T Rational <T>::get_den() const{		// get denominator of a Rational object
	return denumerator;
}

template <class T>
T Rational <T>::get_num() const{		// get numerators of a Rational object
	return numerator;
}

template <class T>		// return another Rat object | operator+ definition
Rational <T> Rational <T>::operator+(const Rational &rhs) const{
	Rational ans(get_num() * rhs.get_den() + get_den() * rhs.get_num(),
		get_den() * rhs.get_den() );
	return ans;
}

template <class T>		// return another Rat object
Rational <T> Rational <T>::operator-(const Rational &rhs) const{
	Rational ans( get_num() * rhs.get_den() - get_den() * rhs.get_num(), 
		get_den() * rhs.get_den());
	return ans;
}

template <class T>		// return another Rat object
Rational <T> Rational <T>::operator*(const Rational &rhs) const{
	Rational ans( get_num() * rhs.get_num(), get_den() * rhs.get_den() );
	return ans;										// multiplication..
}

template <class T>		// return another Rat object
Rational <T> Rational <T>::operator/(const Rational &rhs) const{
	assert(rhs.get_num() != 0);						// division..
	Rational ans( get_num() * rhs.get_den(), get_den() * rhs.get_num() );
	return ans;
}

template <class T>
Rational<T>& Rational<T>::operator+=(const Rational<T> &rhs){
	numerator = get_num() * rhs.get_den() + get_den() * rhs.get_num();
	denumerator = get_den() * rhs.get_den();		// addition..
	normalize();									// return current Rat
	return *this;
}

template <class T>		// return current Rat object
Rational<T>& Rational<T>::operator-=(const Rational<T> &rhs){
	numerator = get_num() * rhs.get_den() - get_den() * rhs.get_num();
	denumerator = get_den() * rhs.get_den();		// substraction..
	normalize();									// return current Rat
	return *this;
}

template <class T>		// return current Rat object
Rational<T>& Rational<T>::operator*=(const Rational<T> &rhs){
	numerator = get_num() * rhs.get_num();		// do multiplications..
	denumerator = get_den() * rhs.get_den();
	normalize();
	return *this;
}

template <class T>		// return current Rat object
Rational<T>& Rational<T>::operator/=(const Rational<T> &rhs){
	assert(rhs.get_num() != 0);
	numerator = get_num() * rhs.get_den();		// flip it around
	denumerator = get_den() * rhs.get_num();	// do multiplications..
	normalize();
	return *this;
}

template <class T>		// return another Rat object
Rational<T> Rational<T>::operator++(int){
	Rational ans;							// make new Rat, set its numer and denumer
	ans.set_num(numerator);					// to current ones, then increase current numer
	ans.set_den(denumerator);
	numerator = numerator + denumerator;
	ans.normalize();
	return ans;
}

template <class T>		// return another Rat object
Rational<T> Rational<T>::operator--(int){
	Rational ans;							// make new Rat, set its numer and denumer
	ans.set_num(numerator);					// to current ones, then decrease current numer
	ans.set_den(denumerator);
	numerator = numerator - denumerator;
	ans.normalize();
	return ans;
}

template <class T>		// return current Rat object
Rational<T>& Rational<T>::operator--(){
	numerator = numerator - denumerator;		// substract denum from numer
	return *this;
}

template <class T>								// return current Rat object
Rational<T>& Rational<T>::operator++(){
	numerator = numerator + denumerator;		// add denum to numer
	return *this;
}

template <class T>					    // change num/den such that den > 0,
void Rational <T>::normalize(){			// and num and den have no commmon factor > 1
	assert(get_den() != 0);				// pre-cond: den != 0
		
	if (numerator == 0){				// set denum to 1 if the numerator is 0..
		denumerator = 1;
		return;							
	}
	
	T value_gcd = gcd(abs(numerator), abs(denumerator));		// get the gcd

	if (abs(value_gcd) > 1){			// if absolute value of gcd is > 1
		numerator = numerator / value_gcd;
		denumerator = denumerator / value_gcd;
	}

	if ( ( numerator < 0) && (denumerator < 0) ){		// if both numerator and denumerator
		numerator = -numerator;							// are negative, make them +
		denumerator = -denumerator;
	}
}

template <class T>			// return greatest common divisor of a and b (Euclid's algorithm)
T Rational <T>::gcd(T a, T b){
	assert(a > 0);			// pre-cond: a, b > 0
	assert(b > 0);
	if (a == 0){
		return b;
	}
	while (b != 0){
		if (a > b){
			a = a - b;
		}else{
			b = b - a;
		}
	}
	return a;
}

#endif
