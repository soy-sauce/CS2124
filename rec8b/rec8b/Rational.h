#ifndef RATIONAL_H //if not defined then define, if it is, go to #endif
#define RATIONAL_H 
#include<iostream>

namespace cs2124 {
	class Rational {
		friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
		friend std::istream& operator >> (std::istream &in, Rational& rhs);
		friend bool operator<(const Rational& lhs, const Rational& rhs);
		friend bool operator==(const Rational& lhs, const Rational& rhs);


	private:
		int num;
		int denom;
		void normalize();

	public:
		Rational(int num = 0, int denom = 1);
		explicit operator bool() const;
		Rational& operator+=(const Rational& rhs);
		//post
		Rational operator++(int dummy);
		//pre
		Rational& operator++();

	};
}



#endif