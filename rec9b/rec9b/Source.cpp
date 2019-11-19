#include <iostream>
#include <vector>

using namespace std;

class PrintedMaterial {
public:
	PrintedMaterial(unsigned numPages) :numOfPages(numPages) {}

	virtual void displayNumPages() const = 0;

protected:
private:
	unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
	cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned numPages):PrintedMaterial(numPages) {}
	void displayNumPages() const {
		cout << "Magazine: ";
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned numPages) :PrintedMaterial(numPages) {}
protected:
private:
};

class TextBook : public Book {
public:
	TextBook(unsigned numPages, unsigned index):Book(numPages), indexNum(index) {}

	void displayNumPages() const {
		cout << "Textbook pages: ";
		PrintedMaterial::displayNumPages();
		cout<<"Index num: " << indexNum;
	}
protected:
private:
	unsigned indexNum;
};

class Novel : public Book {
public:
	Novel(unsigned numPages) :Book(numPages) {}
	void displayNumPages() const {
		cout << "Novel: ";
		PrintedMaterial::displayNumPages();
	}
protected:
private:
};




// tester/modeler code
int main()
{
	TextBook t(5430, 23);
	Novel n(213);
	Magazine m(6);

	// as direct method calls
	cout << "\nEach will now be asked directly,\n"
		<< "using the dot member operator to\n"
		<< "display its number of pages:\n";
	t.displayNumPages();
	n.displayNumPages();
	m.displayNumPages();

	

	// Storing generic objects in a vector 
	cout << "\n\nNow we'll use a container. Yea!!!\n\n";
	vector< PrintedMaterial* > allThemPrinties;
	allThemPrinties.push_back(&t);
	allThemPrinties.push_back(&n);
	allThemPrinties.push_back(&m);
	for (size_t ndx = 0; ndx < allThemPrinties.size(); ++ndx)
	{
		allThemPrinties[ndx]->displayNumPages();
		cout << endl;
	}
}