#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include <iostream>
#include <string>

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

bool profIDTest(string id) //교수번호 중복검사
{
	vector<Professor *>::iterator it = professorList.begin();
	while (it < professorList.end())
	{
		if (id == (*it)->getID()) return false;
		it++;
	}
	return true;
}


void Professor::RegisterCourse(Course *co)
{
	courseList.push_back(co);
}

void Professor::printCo() //교수의 강의 과목 전체출력
{
	unsigned int i;
	cout << "강의 과목" << endl;
	for (i = 0; i < courseList.size(); i++)
	{
		cout << courseList.at(i)->getName() << " " << courseList.at(i)->getID() << endl;
	}
	cout << endl;
}

void Professor::DeleteCourse(Course *co)
{
	vector<Course *>::iterator it;
	it = courseList.begin();
	while (it < courseList.end())
	{
		if ((*it) == co)
		{
			courseList.erase(it);
			break;
		}
		it++;
	}
}

Professor* FindProfessor(string id)
{
	vector<Professor *>::iterator it = professorList.begin();
	while (it < professorList.end())
	{
		if ((*it)->getID() == id)
		{
			return (*it);
		}
		it++;
	}
	return NULL;
}

Professor* FindProfessor(string name, string id)
{
	vector<Professor *>::iterator it = professorList.begin();
	while (it < professorList.end())
	{
		if ((*it)->getID() == id)
		{
			if ((*it)->getName() == name)
			{
				return (*it);
			}
		}
		it++;
	}
	return NULL;
}

void DeleteProfessor(Professor *prof)
{
	vector<Professor *>::iterator it = professorList.begin();
	while (it < professorList.end())
	{
		if ((*it) == prof)
		{
			professorList.erase(it);
			break;
		}
		it++;
	}
}