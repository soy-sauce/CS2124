#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}

// listBuild: constructs a list from a vector of data items.
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listAddHead(result, vals[index - 1]);
	}
	return result;
}

void display(Node* head) {
	Node* curr = head;
	while (curr != nullptr) {
		cout << curr->data << " ";
		curr = curr->next;
	}
	cout << endl;
}



void splice(Node* toAdd, Node* location) {
	Node* curr = toAdd;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	curr->next = location->next;
	location->next = toAdd;
}

Node* isSubList(Node* sublist, Node* list) {
	Node* p1 = sublist;
	Node* p2 = list;

	Node* p2copy = p2;
	bool isSub = false;

	while (p1 != nullptr && p2!=nullptr) {
		if (p1->next == nullptr && p1->data==p2->data) {
			return p2copy;
		}

		else if (p1->data == p2->data && isSub == false) {
			p2copy = p2;
			isSub = true;
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->data == p2->data && isSub == true) {
			p1 = p1->next;
			p2 = p2->next;
		}

		else if (p1->data != p2->data && isSub == true) {
			p1 = sublist;
			p2 = p2copy->next;
			isSub = false;
		}
		else {
			p2 = p2->next;
		}
	}
	return nullptr;
}

Node* sharedListBruteForce(Node* list1, Node* list2) {
	Node* p1 = list1;
	Node* p2 = list2;

	while (p1 != nullptr) {
		while (p2 != nullptr) {
			if (p1 == p2) {
				return p2;
			}
			p2 = p2->next;
		}
		p2 = list2;
		p1 = p1->next;
	}
	return nullptr;
}

Node* sharedListUsingSet(Node* list1, Node* list2) {
	unordered_set<Node*> nodes;
	Node* p1 = list1;
	Node* p2 = list2;
	while (p1 != nullptr) {
		nodes.insert(p1);
		p1 = p1->next;
	}

	while (p2 != nullptr) {
		if (nodes.find(p2) != nodes.end()) {
			return p2;
		}
		p2 = p2->next;
	}
	return nullptr;
}


int main() {
	/*Node* myList = listBuild({ 1, 4, 9, 16, 23, 44 });
	Node* myList2 = listBuild({ 1, 2, 3 });
	Node* myList3 = listBuild({ 1, 2, 3,2,3,5,2,3,4,6 });
	Node* myList4 = listBuild({ 2, 3,5,2 });
	Node* myList5 = listBuild({ 1, 2, 3,2,3,5,2,3,4,6 });
	Node* myList6 = listBuild({ 4,6,7 });
	Node* myList7 = listBuild({ 1, 2, 3,2,3,5,2,3,4,6 });
	Node* myList8 = listBuild({ 2,3,5,2,1 });

	display(myList);
	cout << "Splicing" << endl;
	splice(myList2, myList->next->next); 
	display(myList);
	cout << "Sublist search" << endl;
	Node* task2 = isSubList(myList4, myList3);
	display(task2);
	cout << "-----" << endl;
	Node* task3 = isSubList(myList6, myList5);
	display(task3);
	cout << "-----" << endl;
	Node* task4 = isSubList(myList8, myList7);
	display(task4);
	*/

	

	Node* node1 = &Node(4);
	Node* node2 = &Node(2);

	Node* myList3 = listBuild({ 1, 2, 3,2,3,5,2,3,4,6 });
	Node* myList4 = listBuild({ 2, 3,5,2 });

	myList3->next->next->next = node1;
	myList4->next->next = node1;

	Node* result = sharedListUsingSet(myList3, myList4);
	Node* result2 = sharedListBruteForce(myList3, myList4);

	display(myList3);
	display(myList4);
	display(result);
	display(result2);
}