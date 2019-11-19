#include <iostream>

using namespace std;

int greatestCommonDivisor(int x, int y) {
	while (y != 0) {
		int temp = x % y;
		x = y;
		y = temp;
	}
	return x;
}



class Rational {
	friend ostream& operator<<(ostream& os, const Rational& rhs) {
		if (rhs.denom == 1) {
			os << rhs.num << endl;
		}
		else {
			os << rhs.num << "/" << rhs.denom << endl;
		}
		return os;
	}

	friend istream& operator >> (istream &in, Rational& rhs) {
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

	friend bool operator<(const Rational& lhs, const Rational& rhs) {
		Rational lcopy = lhs;
		Rational rcopy = rhs;
		lcopy.num *= rhs.denom;
		rcopy.num *= lhs.denom;
		return lcopy.num < rcopy.num;
	}

	friend bool operator==(const Rational& lhs, const Rational& rhs) {
		return(lhs.num == rhs.num && lhs.denom == rhs.denom);
	}


private:
	int num;
	int denom;


	void normalize() {
		int x = greatestCommonDivisor(num, denom);
		num = num / x;
		denom = denom / x;
		if (denom < 0) {
			num *= -1;
			denom *= -1;
		}
	}

public:
	Rational(int num=0, int denom=1):num(num), denom(denom) { normalize(); }

	explicit operator bool() const {
		return denom != 0;
	}



	Rational& operator+=(const Rational& rhs) {
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
	Rational operator++(int dummy) {
		Rational temp = *this;
		num += denom;
		normalize();
		return temp;
	}

	//pre
	Rational& operator++() {
		num += denom;
		normalize();
		return *this;
	}



};


Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational rcopy = rhs;
	Rational lcopy = lhs;
	lcopy += rcopy;
	return lcopy;

}

bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

//post
Rational operator--(Rational& lhs, int dummy) {
	Rational temp = lhs;
	lhs += (-1);
	return temp;
}

//pre
Rational& operator--(Rational& lhs) {
	lhs += (-1);
	return lhs;
}


bool operator<=(const Rational& lhs, const Rational& rhs) {
	return (lhs < rhs || lhs == rhs);

}

bool operator>(const Rational& lhs, const Rational& rhs) {
	return !(lhs < rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	return (lhs>rhs || lhs == rhs);
}


int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	Rational a, b;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "a: ";
	cin >> a;
	cout << "Input a rational number, e.g. 6/9.\n";
	cout << "b: ";
	cin >> b;
	const Rational one = 1;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;

	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;

	// How does this manage to work?
	// It does NOT require writing another == operator. 
	cout << "1 == one: " << boolalpha << (1 == one) << endl;

	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;

	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;

	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;

	// Even though the above example, (a++ ++), compiled, the
	// following shouldn't.
	// But some compiler vendors might let it...  Is your compiler
	// doing the right thing?
	cout << "a-- -- = " << (a-- --) << endl;
	cout << "a = " << a << endl;


	// Should report that 1 is true
	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}

	// Should report that 0 is false
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
}
