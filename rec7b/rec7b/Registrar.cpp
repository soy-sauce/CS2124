#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>
#include <string>


using namespace std;


namespace BrooklynPoly {
	//Registrar
	ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrar's Report" << endl;
		os << "Classes Available: ";
		for (size_t i = 0; i < rhs.courses.size(); ++i) {
			os <<" "<< *rhs.courses[i];
		}
		
		os << "\nStudents: ";
		for (size_t i = 0; i < rhs.students.size(); ++i) {
			os << *rhs.students[i];
		}
		return os;
	}


	Registrar::Registrar() {};
	bool Registrar::addCourse(const string& name) {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == name) {
				return false;
			}
		}

		Course* newCourse = new Course(name);
		courses.push_back(newCourse);
		return true;
	}

	bool Registrar::addStudent(const string& name) {
		for(size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == name) {
				return false;
			}
		}

		Student* newStudent = new Student(name);
		students.push_back(newStudent);
		return true;
	}

	bool Registrar::enrollStudentInCourse(const string& studentName,
		const string& courseName) {
		size_t studentInd = findStudent(studentName);
		size_t courseInd = findCourse(courseName);
		if (studentInd != students.size() && courseInd != courses.size()) {
			students[studentInd]->addCourse(courses[courseInd]);
			courses[courseInd]->addStudent(students[studentInd]);
			return true;
		}
		return false;
	}


	bool Registrar::cancelCourse(const string& courseName) {
		size_t courseInd = findCourse(courseName);
		if (courseInd != courses.size()) {
			courses[courseInd]->removeStudentsFromCourse();
			swap(courses[courseInd], courses[courses.size() - 1]);
			delete courses[courses.size() - 1];
			courses.pop_back();
			return true;
		}
		return false;
	}


	void Registrar::purge() {
		for (size_t i = 0; i < courses.size(); ++i) {
			delete courses[i];
		}

		for (size_t i = 0; i < students.size(); ++i) {
			delete students[i];
		}

		students.clear();
		courses.clear();
	};







	//private methods

	size_t Registrar::findStudent(const string& name) const {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i]->getName() == name) {
				return i;
			}
		}
		return students.size();
	}


	size_t Registrar::findCourse(const string& name) const {
		for (size_t i = 0; i < courses.size(); ++i) {
			if (courses[i]->getName() == name) {
				return i;
			}
		}
		return courses.size();
	}

}