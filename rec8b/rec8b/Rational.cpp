#include "Rational.h"
#include <iostream>

using namespace std;

namespace cs2124{
	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}


	ostream& operator<<(ostream& os, const Rational& rhs) {
		if (rhs.denom == 1) {
			os << rhs.num << endl;
		}
		else {
			os << rhs.num << "/" << rhs.denom << endl;
		}
		return os;
	}

	istream& operator >> (istream &in, Rational& rhs) {
		int num;
		int denom;
		char frac;
		cout << "Enter A Fraction: " << endl;
		in >> num >> frac >> denom;
		rhs.num = num;
		rhs.denom = denom;
		rhs.normalize();
		return in;
	}

	bool operator<(const Rational& lhs, const Rational& rhs) {
		Rational lcopy = lhs;
		Rational rcopy = rhs;
		lcopy.num *= rhs.denom;
		rcopy.num *= lhs.denom;
		return lcopy.num < rcopy.num;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		return(lhs.num == rhs.num && lhs.denom == rhs.denom);
	}



	void Rational::normalize() {
		int x = greatestCommonDivisor(num, denom);
		num = num / x;
		denom = denom / x;
		if (denom < 0) {
			num *= -1;
			denom *= -1;
		}
	}

	Rational::Rational(int num, int denom) :num(num), denom(denom) { normalize(); }

	Rational::operator bool() const {
		return num != 0;
	}



	Rational& Rational::operator+=(const Rational& rhs) {
		Rational rcopy = rhs;
		Rational lcopy = *this;
		num *= rhs.denom;
		denom *= rhs.denom;
		rcopy.num *= lcopy.denom;
		rcopy.denom *= lcopy.denom;
		num += rcopy.num;
		normalize();
		return *this;
	}


	//post
	Rational Rational::operator++(int dummy) {
		Rational temp = *this;
		num += denom;
		normalize();
		return temp;
	}

	//pre
	Rational& Rational::operator++() {
		num += denom;
		normalize();
		return *this;
	}



	



}