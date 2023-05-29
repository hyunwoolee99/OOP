#ifndef _Student_H_
#define _Student_H_
#include <vector>

class Course;
class Grade;
using namespace std;

class Student {
private:
	string name, id;
	vector<Course *> courseList;
	vector<Grade *> gradeList;
public:
	Student(string name, string id)
	{
		this->name = name;
		this->id = id;
	};
	string getID() { return id; }
	string getName() { return name; }
	int getCourseList_size() { return courseList.size(); }
	void printCoGr();
	void printCoList();
	void SetGrade(Course *co, string gr);
	void RegisterCourse(Course *co);
	bool DeleteCourse(Course *co);
	Course* DeleteCourse(int num);
};
bool studentIDTest(string id);
Student* FindStudent(string id);
Student* FindStudent(string name, string id);
void DeleteStudent(Student *st);

#endif