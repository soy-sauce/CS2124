// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;


class List {
	//friend Iterator;

	struct Node {
		Node(int data = 0, Node* next = nullptr) :data(data), next(next) {}
		int data;
		Node* next;
		Node* prev;
	};

	friend ostream& operator<<(ostream& os, List rhs) {
		Node* curr = rhs.header->next;
		if (curr == rhs.trailer) {
			os << "Empty List";
			return os;
		}
		for (int i = 0; i < rhs.size(); ++i) {
			os << curr->data << ' ';
			curr = curr->next;
		}
		return os;
	}

public:
	class Iterator {
		friend List;

		friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
			return lhs.where == rhs.where;
		}


		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
			return lhs.where != rhs.where;
		}

	public:
		Iterator(Node* p) { where = p; }

		Iterator& operator++() {
			where = where->next;
			return *this;
		}

		Iterator& operator--() {
			where = where->prev;
			return *this;
		}


		int& operator*() {
			return where->data;
		}

		int operator*() const {
			return where->data;
		}


	private:
		Node* where;
	};


	List() {
		header->next = trailer;
		trailer->prev = header;
	}



	Iterator begin() { return Iterator(header->next); }
	Iterator end() { return Iterator(trailer); }


	int& front() {
		return header->next->data;
	}

	int front() const{
		return header->next->data;
	}

	int& back() {
		return trailer->prev->data;
	}

	int front() const {
		return header->next->data;
	}

	void push_back(int data) {
		Node* target = new Node(data);
		target->next = trailer;
		target->prev = trailer->prev;
		trailer->prev->next = target;
		trailer->prev = target;
		mySize += 1;

	}

	void pop_back() {
		//int last = trailer->prev->data;
		delete trailer->prev;
		trailer->prev->prev->next = trailer;
		trailer->prev = trailer->prev->prev;
		mySize -= 1;
		//return last;
	}


	int size() {
		return mySize;
	}

	void push_front(int data) {
		Node* target = new Node(data);
		target->next = header->next;
		target->prev = header;
		header->next->prev = target;
		header->next = target;
		mySize += 1;
	}

	void pop_front() {
		//int first = header->next->data;
		delete header->next;
		header->next->next->prev = header;
		header->next = header->next->next;
		mySize -= 1;
		//return first;
	}

	void clear() {
		if (header->next == trailer) {
			return;
		}

		Node* cur = header->next;
		Node* next = header->next->next;

		while (next != trailer) {
			delete cur;
			cur = next;
			next = next->next;
		}
		delete cur;
		header->next = trailer;
		trailer->prev = header;
		mySize = 0;
	}

	int operator[](size_t index)const {
		Node* cur = header->next;
		for (size_t i = 0; i < index; ++i) {
			cur = cur->next;
		}
		return cur->data;
	}

	int& operator[](size_t index) {

		Node* cur = header->next;
		for (size_t i = 0; i < index; ++i) {
			cur = cur->next;
		}
		return cur->data;
	}

	Iterator& insert(Iterator& index, int data) {
		Node* target = new Node(data);
		Node* replace = index.where;


		replace->prev->next = target;
		target->prev = replace->prev;
		replace->prev = target;
		target->next = replace;
		mySize += 1;
		return Iterator(target);

	}

	Iterator& erase(Iterator& index) {
		Node* toDelete = index.where;
		toDelete->prev->next = toDelete->next;
		toDelete->next->prev = toDelete->prev;

		mySize -= 1;
		return Iterator(toDelete->next);
	}

	/*
	List(List& rhs) {
		for (List::Iterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
			push_back(*iter);
		}
		mySize = rhs.mySize;
	}


	List& operator=(List& rhs) {
		if (this != &rhs) {
			clear();
			delete header;
			delete trailer;

			for (List::Iterator iter = rhs.begin(); iter != rhs.end(); ++iter) {
				push_back(*iter);
			}
			mySize = rhs.mySize;
		}
		return *this;
	}

	~List() {
		clear();
		delete header;
		delete trailer;
	}

	*/


private:
	Node* trailer = new Node(0);
	Node* header = new Node(0);
	size_t mySize = 0;


};

void printListInfo(List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}

// Task 8
void doNothing(List aList) {
	cout << "In doNothing\n";
	printListInfo(aList);
	cout << endl;
	cout << "Leaving doNothing\n";
}

int main() {

	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i*i << ");\n";
		myList.push_back(i*i);
		printListInfo(myList);
	}

	cout << "===================\n";
	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";

	// Task2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i*i << ");\n";
		myList.push_front(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";



	// Task3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i*i);
		printListInfo(myList);
	}



	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";



	// Task4
	cout << "\n------Task Four------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) { myList.push_back(i*i); }
	printListInfo(myList);


	cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;
	cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
	cout << "And print it out again with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
	cout << endl;


	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";


	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) {
		myList.insert(myList.end(), i*i);
	}
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) {
		myList.insert(myList.begin(), i*i);
	}
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";


	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase(myList.begin());
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";

	
	// Task 8
	cout << "\n------Task Eight------\n";
	cout << "Copy control\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	cout << "Calling doNothing(myList)\n";
	doNothing(myList);
	cout << "Back from doNothing(myList)\n";
	printListInfo(myList);

	cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
	List listTwo;
	for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
	printListInfo(listTwo);
	cout << "listTwo = myList\n";
	listTwo = myList;
	cout << "myList: ";
	printListInfo(myList);
	cout << "listTwo: ";
	printListInfo(listTwo);
	cout << "===================\n";

	
}

