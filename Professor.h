#ifndef _Professor_H_
#define _Professor_H_
#include <vector>
using namespace std;

class Course;
class Professor
{
private:
	string name, id;
	vector<Course *> courseList;
public:
	Professor(string name, string id)
	{
		this->name = name;
		this->id = id;
	}
	string getID() { return id; }
	string getName() { return name; }
	void printCo();
	void RegisterCourse(Course *co);
	void DeleteCourse(Course *co);
};

Professor* FindProfessor(string id);
Professor* FindProfessor(string name, string id);
void DeleteProfessor(Professor *prof);

#endif