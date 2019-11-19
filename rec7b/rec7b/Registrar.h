#ifndef REGISTRAR_H //if not defined then define, if it is, go to #endif
#define REGISTRAR_H

#include <string>
#include <vector>
#include<iostream>

//using namespace std; //namespace pollution
namespace BrooklynPoly {
	class Course;
	class Student;

	class Registrar {
		friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);

	public:

		Registrar();
		bool Registrar::addCourse(const std::string& name);
		bool addStudent(const std::string& name);
		bool enrollStudentInCourse(const std::string& studentName,
			const std::string& courseName);
		bool cancelCourse(const std::string& courseName);
		void purge();

	private:

		size_t findStudent(const std::string& name) const;
		size_t findCourse(const std::string& name) const;



		/*		size_t findStudent(const string& name) const {
		for (size_t i = 0; i < students.size(); ++i) {
		if (students[i]->getName() == name) {
		return i;
		}
		}
		return students.size();
		}


		size_t findCourse(const string& name) const {
		for (size_t i = 0; i < courses.size(); ++i) {
		if (courses[i]->getName() == name) {
		return i;
		}
		}
		return courses.size();
		}
		*/

		std::vector<Course*> courses;
		std::vector<Student*> students;
	};
}
#endif
