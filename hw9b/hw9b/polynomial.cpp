#include "polynomial.h"

using namespace std;

Node::Node(int data, Node* next) : data(data), next(next) {}

// accessors    
int Node::getData() { return data; }
Node* Node::getNext() { return next; }

// mutators
void Node::setData(int data) { this->data = data; }
void Node::setNext(Node* next) { this->next = next; }


Polynomial::Polynomial() {
	header->setData(NULL);
}

Polynomial::Polynomial(const vector<int>& init) {
	if (init.size() > 0) {
		length = init.size() - 1;
		header = new Node(init[length]);
		Node* curr = header;
		for (size_t i = init.size() - 1; i > 0; --i) {
			Node* nextPtr = new Node(init[i - 1]);
			curr->setNext(nextPtr);
			curr = curr->getNext();
		}
	}
	else {
		length = 0;
		header = new Node();
	}
}


//Copy Constructor
Polynomial::Polynomial(const Polynomial& init){
	Node* initCursor = init.header->getNext();
	header = new Node(init.header->getData());
	Node* cursor = header;
	while (initCursor != nullptr) {
		cursor->setNext(new Node(initCursor->getData()));
		cursor = cursor->getNext();
		initCursor = initCursor->getNext();
	}

}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this != &rhs) {
		//1. free up resources
		for (size_t i = 0; i < length; i++) { pop_back(); }
		//2. allocate new resources
		//3. copy over
		Node* cursor = rhs.header;
		for (size_t j = 0; j < rhs.length; j++) {
			push_back(cursor->getData());
			cursor = cursor->getNext();
		}
	}
	return *this;
}

Polynomial::~Polynomial() {
	Node* cursor = header;
	size_t loop = length;
	for (size_t i = 0; i < loop; ++i) {
		pop_back();
	}
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial result(rhs);
	return result += lhs;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* cursor = header;
	Node* zero(0);
	Polynomial rhscopy = Polynomial(rhs);
	//add leading zeros to the shorter polynomial
	if (rhs.length > length) {
		for (int i = -1; i < rhs.length - length; ++i) {
			zero->setNext(header);
			header = zero;
		}
	}

	else if(rhs.length < length){
		for (int i = -1; i < length-rhs.length; ++i) {
			zero->setNext(rhs.header);
			rhscopy.header=zero;
		}
	}

	Node* rhsCursor = rhscopy.header;
	//add all elements together
	while (cursor != nullptr) {
		cursor->setData(cursor->getData() + rhsCursor->getData());
		rhsCursor = rhsCursor->getNext();
		cursor = cursor->getNext();
	}

	return *this;
}

bool Polynomial::operator==(const Polynomial& rhs) {
	if (rhs.length != length) { return false; }
	for (size_t i = 0; i < length; ++i) {
		Node* cursor = header;
		Node* rhsCursor = rhs.header;

		if (cursor->getData() != rhsCursor->getData()) {
			return false;
		}
	}
	return true;
}

bool Polynomial::operator!=(const Polynomial& rhs) {
	return !(*this == rhs);
}

void Polynomial::push_back(int data) {
	if (length == 0) {
		header->setData(data);
		++length;
	}
	else {
		Node* curr = header;
		while (curr->getNext() != nullptr) {
			curr = curr->getNext();
		}
		curr->setNext(&Node(data));
		++length;
	}
}

int Polynomial::pop_back() {
	int data = header->getData();
	if (length == 1) {
		delete header;
		header = nullptr;
		return data;
	}

	Node* curr = header;
	while (curr->getNext() != nullptr) {
		curr = curr->getNext();
	}

	data = curr->getData();
	delete curr->getNext();
	curr->setNext(nullptr);
	--length;
	return data;
}


int Polynomial::evaluate(int n) {
	double answer = 0;
	Node* cursor = header;
	int counter = 0;
	while (cursor != nullptr) {
		answer += (cursor->getData() * (pow(n, counter)));
		++counter;
		cursor = cursor->getNext();
	}
	return answer;
}

ostream &operator<<(ostream& os, const Polynomial& rhs) {
	string output = "";
	int count = 1;
	Node* curr = rhs.header;
	if (curr->getData()) {
		output = to_string(curr->getData());
	}
	curr = curr->getNext();
	while (curr) {
		if (curr->getData() != 1) {
			if (count != 1) {
				output = to_string(curr->getData()) + "x^" + to_string(count) + " + " + output;
			}
			else {
				output = to_string(curr->getData()) + "x" + " + " + output;
			}
		}
		++count;
		curr = curr->getNext();
	}
	os << output;
	return os;
}

void doNothing(Polynomial temp) {}


int main() {

	//test constructor
	Polynomial p1({ 17 });                 // 17
	Polynomial p2({ 1, 2 });               // x + 2
	Polynomial p3({ -1, 5 });              // -1x + 5
	Polynomial p4({ 5, 4, 3, 2, 1 });      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
	Polynomial has_a_zero({ 4, 0, 1, 7 }); // 4x^3 + x + 7

	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;
	cout << "p3: " << p3 << endl;
	cout << "p4: " << p4 << endl;
	cout << "has_a_zero: " << has_a_zero << endl;
	cout << "p2 + p3: " << (p2 + p3) << endl;
	cout << "p2 + p4: " << (p2 + p4) << endl;
	cout << "p4 + p2: " << (p4 + p2) << endl;

	/*
	//test copy constructor - the statement below uses the copy constructor
	//to initialize poly3 with the same values as poly4
	Polynomial p5(p4);
	p5 += p3;
	cout << "Polynomial p5(p4);\n"
		<< "p5 += p3;\n";

	cout << "p4: " << p4 << endl;
	cout << "p5: " << p5 << endl;

	cout << "Calling doNothing(p5)\n";
	doNothing(p5);
	cout << "p5: " << p5 << endl;

	//tests the assignment operator
	Polynomial p6;
	cout << "p6: " << p6 << endl;
	cout << boolalpha;  // Causes bools true and false to be printed that way.
	cout << "(p4 == p6) is " << (p4 == p6) << endl;
	p6 = p4;
	cout << "p6: " << p6 << endl;
	cout << boolalpha;
	cout << "(p4 == p6) is " << (p4 == p6) << endl;

	//test the evaluaton
	int x = 5;
	cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
	cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;

	Polynomial p7({ 3, 2, 1 });           // 3x^2 + 2x + 1
	cout << "p7: " << p7 << endl;
	cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

	cout << boolalpha;
	cout << "(p1 == p2) is " << (p1 == p2) << endl;
	cout << "(p1 != p2) is " << (p1 != p2) << endl;
	*/
}


