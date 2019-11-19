#ifndef COURSE_H //if not defined then define, if it is, go to #endif
#define COURSE_H 
#include<string>
#include<vector>
#include<iostream>


namespace BrooklynPoly {
	class Student;

	class Course {
		friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
	public:
		Course(const std::string& courseName);
		const std::string& getName() const;
		bool addStudent(Student* student);
		void removeStudentsFromCourse();
		void removeAStudent(const std::string& name);

	private:
		std::string name;
		std::vector<Student*> students;
	};

}
#endif
