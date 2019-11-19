#include <iostream>
#include <string>
#include <vector>
#include <exception>

using namespace std;

//task 2 node functions + code to build/test lists
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listInsertHead(result, vals[index - 1]);
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




//task 3 TNode
struct TNode {
	TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode *left, *right;
};


//task 3
int max(TNode* root) { //throw an exception when the root is null
	if (!root) {
		throw exception();
	}

	int maxval = root->data;

	if (root->left != nullptr) {
		int newMax = max(root->left);
		if (maxval < newMax) {
			maxval = newMax;
		}
	}
	else if (root->right != nullptr) {
		int newMax = max(root->right);
		if (maxval < newMax) {
			maxval = newMax;
		}
	}

	return maxval;


}




//task1
bool evenNum(int num) {
	int remainder = num % 2;
	if (num == 0) {
		return true;
	}
	bool isEven = evenNum(num / 2);
	if (remainder) {
		return !isEven;
	}
	else {
		return isEven;
	}

}


//task 2
Node* sumList(Node* list1, Node* list2) {
	if (!list1 && !list2) { return nullptr; }

	Node* newNode;

	if (!list1) {
		newNode = new Node(list2->data);
		newNode->next = sumList(list1, list2->next);
	}
	else if (!list2) {
		newNode = new Node(list1->data);
		newNode->next = sumList(list1->next, list2);
	}
	else {
		newNode = new Node(list1->data + list2->data);
		newNode->next = sumList(list1->next, list2->next);
	}
	return newNode;
}


//task 4
bool palindrome(char* s, int length) {
	if (length < 2) {
		return true;
	}

	if (s[0] == s[length - 1]) {
		return palindrome(s + 1, length - 2);
	}
	else {
		return false;
	}
}

//task 5 towers
int towers(int n, char start, char target, char spare) {
	int sum = 1;
	if (n == 1) {
		return 1;
	}

	sum += towers(n - 1, start, spare, target) + towers(n - 1, spare, target, start);
}

//task 6 mystery
void mystery(int n) {
	if (n > 1) {
		cout << 'a';
		mystery(n / 2);
		cout << 'b';
		mystery(n / 2);
	}
	cout << 'c';
}

int main() {
	//task 1
	cout << "Task 1:\n";
	int n = 9; //even 1;s
	int n2 = 10; //even 1's
	int	n3 = 11; //not even
	cout << evenNum(n) << ' ' << evenNum(n2) << ' ' << evenNum(n3) << endl;
	cout << "-------------------\n";


	//task 2
	cout << "Task 2:\n";
	Node* myList = listBuild({ 1, 4, 9, 16, 23, 44 });
	Node* myList2 = listBuild({ 1, 2, 3 });
	display(sumList(myList, myList2));
	cout << "-------------------\n";


	//task 3
	cout << "Task 3:\n";
	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	cout << max(&f) << endl;
	try
	{
		TNode aNode;
		max(aNode.right);
	}
	catch (exception& e)
	{
		cerr << "exception caught: " << e.what() << '\n';
	}

	cout << "-------------------\n";




	//task4
	cout << "Task 4:\n";
	char s[] = "racecar";
	char s2[] = "racekar";
	char s3[] = "bacecar";
	cout << palindrome(s, 7) << ' ' << palindrome(s2, 7)<<' ' << palindrome(s3, 7) << endl;
	cout << "-------------------\n";

	//task5
	cout << "Task 5:\n";
	cout << towers(1, 'a', 'b', 'c') << endl;
	cout << towers(2, 'a', 'b', 'c') << endl;
	cout << towers(3, 'a', 'b', 'c') << endl;
	cout << towers(4, 'a', 'b', 'c') << endl;
	cout << towers(5, 'a', 'b', 'c') << endl;
	cout << towers(6, 'a', 'b', 'c') << endl;
	cout << towers(7, 'a', 'b', 'c') << endl;
	cout << towers(8, 'a', 'b', 'c') << endl;
	cout << towers(9, 'a', 'b', 'c') << endl;
	cout << towers(10, 'a', 'b', 'c') << endl;
	cout << "-------------------\n";

	//task6
	cout << "Task 6:\n";
	mystery(0);
	cout << endl;
	mystery(10);
	cout << endl;
	cout << "-------------------\n"; 
}


