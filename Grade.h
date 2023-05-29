#ifndef _Grade_H_
#define _Grade_H_
#include <vector>
using namespace std;

class Course;
class Grade {
private:
	Course *course;
	string grade;
public:
	Grade(Course *co, string gr)
	{
		course = co;
		grade = gr;
	};
	string getGrade() { return grade; }
	Course* getCourse() { return course; }
	void setGrade(string gr) { grade = gr; }
};

#endif