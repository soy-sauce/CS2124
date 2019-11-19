#include "Student.h"
#include "Course.h"
#include "Registrar.h"
#include <iostream>
#include <string>
using namespace std;


namespace BrooklynPoly {
	//course
	// Course methods needed by Registrar
	ostream& operator<<(ostream& os, const Course& rhs) {
		os << rhs.name << ": ";
		if (rhs.students.size() > 0) {
			for (size_t i = 0; i < rhs.students.size(); ++i) {
				os << rhs.students[i]->getName();
			}
		}
		else {
			os << "No Students";
		}
		return os;
	}


	Course::Course(const string& courseName) :name(courseName) {};
	const string& Course::getName() const { return name; };

	bool Course::addStudent(Student* student) {
		for (size_t i = 0; i < students.size(); ++i) {
			if (students[i] == student) {
				return false;
			}
		}
		students.push_back(student);
		return true;
	};

	void Course::removeStudentsFromCourse() {
		for (size_t i = 0; i < students.size(); ++i) {
			students[i]->removedFromCourse(this);
		}
		students.clear();
	}



	/*	void Course::removeAStudent(const string& name) {
	for (size_t i = 0; i < students.size(); ++i) {
	if (students[i]->getName() == name) {
	swap(students[i], students[students.size() - 1]);
	students.pop_back();
	}
	}
	} */
}