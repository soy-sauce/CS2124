/*
rec07
Starter Code for required functionality
Yes, you may add other methods.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;
class Course;
class Registrar;

class Course {
	friend ostream& operator<<(ostream& os, const Course& rhs) {
		os << "Course " << rhs.name << " has students: " << endl;
		for (size_t i; i < rhs.students.size(); ++i) {
			os << rhs.students[i]->getName() << endl;
		}
		return os;
	}

public:
	// Course methods needed by Registrar
	Course(const string& courseName) : name(courseName) {}

	const string& getName() const {
		return name;
	}

	bool addStudent(Student* student) {
		students.push_back(student);
		return true;
	}

	void removeStudentsFromCourse() {
		for (size_t i = 0; i < students.size(); ++i) {
			students[i]->removedFromCourse(this);
		}
		students.clear();
	}

private:
	string name;
	vector<Student*> students;
};

class Student {
	friend ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.name << ": ";
		for (size_t i = 0; i < rhs.courses.size(); ++i) {
			os << rhs.courses[i]->getName()<<" "; 
		}
		return os;
	}
public:
	// Student methods needed by Registrar
	Student(const string& name): name(name) {}
	const string& getName() const {
		return name;
	}

	bool addCourse(Course* course) {
		courses.push_back(course);
		return true;
	}

	// Student method needed by Course
	void removedFromCourse(Course* course) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i] == course) {
				swap(courses[i], courses[courses.size() - 1]);
				courses.pop_back();
			
			}
		
		}
	}

private:
	string name;
	vector<Course*> courses;
};

class Registrar {
	friend ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrars Report: \n" << "Courses: ";
		for (size_t i = 0; i < rhs.courses.size(); ++i) {
			os << *rhs.courses[i];
		}
		os << "\n Students: " << endl;;
		for (size_t i = 0; i < rhs.students.size(); ++i) {
			os << *rhs.students[i];
		}
		return os;
	
	}
public:
	Registrar();
	bool addCourse(const string& courseName) {
		courses.push_back(new Course(courseName));
		return true;
	}

	bool addStudent(const string& studentName) {
		students.push_back(new Student(studentName));
		return true;
	}


	bool enrollStudentInCourse(const string& studentName,
		const string& courseName) {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == studentName) {
				for (size_t j = 0; j < courses.size(); ++j) {
					if (courses[j]->getName() == courseName) {
						courses[j]->addStudent(students[i]);
						return true;
					}
				}
			}
		}
		return false;
	}


	bool cancelCourse(const string& coursename) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if(courses[i]->getName()==coursename){
				courses[i]->removeStudentsFromCourse();
				swap(courses[i], courses[courses.size() - 1]);
				courses.pop_back();
			}
		}
	
	}


	void purge() {
		for (size_t i = 0; i < courses.size(); ++i) {
			delete courses[i];
		}
		for (size_t i = 0; i > students.size(); ++i) {
			delete students[i];
		}
		courses.clear();
		students.clear();
	}

private:
	size_t findStudent(const string&) const;
	size_t findCourse(const string&) const;

	vector<Course*> courses;
	vector<Student*> students;
};





int main() {

	Registrar registrar;

	cout << "No courses or students added yet\n";
	cout << registrar << endl;

	cout << "AddCourse CS101.001\n";
	registrar.addCourse("CS101.001");
	cout << registrar << endl;

	cout << "AddStudent FritzTheCat\n";
	registrar.addStudent("FritzTheCat");
	cout << registrar << endl;

	cout << "AddCourse CS102.001\n";
	registrar.addCourse("CS102.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
	cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
	registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
	cout << registrar << endl;

	cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
	cout << "Should fail, i.e. do nothing, "
		<< "since Bullwinkle is not a student.\n";
	registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
	cout << registrar << endl;

	cout << "CancelCourse CS102.001\n";
	registrar.cancelCourse("CS102.001");
	cout << registrar << endl;

	/*
	// [OPTIONAL - do later if time]
	cout << "ChangeStudentName FritzTheCat MightyMouse\n";
	registrar.changeStudentName("FritzTheCat", "MightyMouse");
	cout << registrar << endl;

	cout << "DropStudentFromCourse MightyMouse CS101.001\n";
	registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
	cout << registrar << endl;

	cout << "RemoveStudent FritzTheCat\n";
	registrar.removeStudent("FritzTheCat");
	cout << registrar << endl;
	*/

	cout << "Purge for start of next semester\n";
	registrar.purge();
	cout << registrar << endl;
}

