
#ifndef POLYNOMIAL_H 
#define POLYNOMIAL_H

#include <iostream>
#include <vector>
#include <cmath>    //used for exponential function ^
#include <string>   
#include <algorithm>
using namespace std;

/*
Provided Node Class on Resources online
*/
class Node {
public:
	Node(int data = 0, Node* next = nullptr);

	// accessors    
	int getData();
	Node* getNext();

	// mutators
	void setData(int data);
	void setNext(Node* next);

private:
	int data;
	Node* next;

};

/*
Polynomial
*/
class Polynomial {
public:
	//Constructor
	Polynomial();
	Polynomial(const vector<int>& init); //Constructor

																								 //Copy Constructor
	Polynomial(const Polynomial& init);

	Polynomial& operator=(const Polynomial& rhs); //ASsignment Operator

	~Polynomial(); //Destructor


	friend Polynomial operator+(const Polynomial& rhs);

	Polynomial& operator+=(const Polynomial& rhs);

	bool operator==(const Polynomial& rhs);

	bool operator!=(const Polynomial& rhs);

	void push_back(int data);//Create new node at the end of the Polynomial taking in data

	int pop_back();//Pops off, returns data last node that it pops, deletes the node that it pops off

	int evaluate(int n); //Evaluates, subsitute x with the provided input

public:
	friend ostream &operator<<(ostream& os, const Polynomial& rhs); //Printing out ostream
	size_t length;
	Node* header;
};

void doNothing(Polynomial temp); //To test the destructor call

#endif