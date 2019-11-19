#ifndef STUDENT_H //if not defined then define, if it is, go to #endif
#define STUDENT_H


#include <string>
#include <vector>
#include<iostream>

//using namespace std; //namespace pollution
namespace BrooklynPoly {
	class Course;

	class Student {
		friend std::ostream& operator<<(std::ostream& os, const Student& rhs);

	public:
		Student(const std::string& name);
		const std::string& getName() const;
		bool addCourse(Course* course);
		void removedFromCourse(Course* course);

	private:
		std::string name;
		std::vector<Course*> courses;
	};
}
#endif