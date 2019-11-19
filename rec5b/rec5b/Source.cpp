//connie zhou
//cz1529

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Section;
class LabWorker;



class Section {
	friend ostream& operator<<(ostream& os, const Section& rhs) {
		os << "Section: " << rhs.name << ", Time slot: " << *rhs.time << ", Students:";
		if (rhs.students.size() == 0) {
			os << " None";
		}
		else {
			os << endl;
			for (size_t i = 0; i < rhs.students.size(); ++i) {
				os << *rhs.students[i];
			}
		}
		return os;
	}

	class TimeSlot {
		friend ostream& operator<<(ostream& os, const TimeSlot& rhs) {
			os << "[Day: " << rhs.day << ", Start Time: ";
			if (rhs.hour > 12) {
				os << rhs.hour % 12 << "pm";
			}
			else {
				os << rhs.hour << "am";
			}
			os << "]";
			return os;
		}


	private:
		string day;
		int hour;
	public:
		TimeSlot(string day, int hour): day(day), hour(hour) {}


	
	};

	class Student {
		friend ostream& operator<<(ostream& os, const Student& rhs) {
			os << "Name: " << rhs.name << " Grades:";
			for (size_t i = 0; i < rhs.grades.size(); ++i) {
				os << " " << rhs.grades[i];
			}
			os << endl;
			return os;
		}

	private:
		string name;
		vector<int> grades; //each index is that week-1

	public:
		Student(const string& name) :name(name), grades(14,-1){}

		string getName() const { return name; }
		void setGrade(int grade, int week) {
			grades[week - 1] = grade;
		}
	};


private:
	vector<Student*> students;
	string name;
	TimeSlot time;

public:
	//big 3
	//constructor
	Section(const string& name,const string& day, int hour) :name(name) {
		time = TimeSlot(day, hour);
	}

	//destructor 
	~Section() {
		cout << "Section " << name << " is being cleared"<<endl;
		for (size_t i = 0; i < students.size(); ++i) {
			cout << "Deleting " << students[i]->getName() << endl;
			delete students[i];
		}
	}

	//copy construct
	Section(const Section& othersection){
		for (size_t i = 0; i < othersection.students.size(); ++i) {
			students.push_back(new Student(*othersection.students[i]));
		}

		name = othersection.name;
		time = new TimeSlot(*othersection.time);
	} 


	void addStudent(const string& name) {
		Student* student = new Student(name);
		students.push_back(student);
	}
	
	void addGrade(const string& name, int grade, int week) {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName()==name) {
				students[i]->setGrade(grade, week);
			}
		}
	
	}

};

class LabWorker {
	friend ostream& operator<<(ostream& os, const LabWorker& rhs) {
		if (rhs.labsection != nullptr) {
			os << rhs.name << " has "<<*rhs.labsection;
		}
		else {
			os << rhs.name << " has no section";
		}
		return os;
	}

private:
	string name;
	Section* labsection;

public:
	//constructor
	LabWorker(const string& name) :name(name) {}

	void addSection(Section& section) {
		labsection = &section;
	}

	void addGrade(const string& student, int grade, int week) {
		labsection->addGrade(student, grade, week);
	}

};

// Test code
void doNothing(Section sec) {
	cout << sec << endl;;
}

int main() {

	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;

	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;

	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	cout << moe << endl;

	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	cout << moe << endl;

	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection(secB3);
	cout << jane << endl;

	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << moe << endl;

	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	cout << moe << endl;

	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
		<< "those students (or rather their records?)\n";

	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works properly, i.e. no memory leaks\n";
	doNothing(secA2);
	cout << "Back from doNothing\n\n";

} // main
