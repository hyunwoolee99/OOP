#ifndef _Course_H_
#define _Course_H_
#include <vector>
using namespace std;

class Professor;
class Student;
class Course {
private:
	string name, id;
	Professor *professor;
	vector<Student *> studentList;
public:
	Course(string name, string id)
	{
		this->name = name;
		this->id = id;
	}
	string getID() { return id; }
	string getName() { return name; }
	string getProfName();
	Professor *getProf() { return professor; }
	int getNumofStud();
	void PrintStud();
	void setGrade(int num, string grade);
	void RegisterPr(Professor *pr);
	void RegisterStud(Student *st);
	bool DeleteStud(Student *st);
	void appendID();
	void undoCourse();
};
void PrintCourse();
Course* FindCourse(string id);
Course* FindCourse(string name, string id);
void DeleteCourse(Course *co);
#endif