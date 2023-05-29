#include "Course.h"
#include "Student.h"
#include "Professor.h"
#include <iostream>
#include <string>

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

string Course::getProfName() { return professor->getName(); }

int Course::getNumofStud() { return studentList.size(); }

void Course::RegisterPr(Professor *pr)
{
	this->professor = pr;
}

void Course::RegisterStud(Student *st) //�л� ���
{
	studentList.push_back(st);
}

bool Course::DeleteStud(Student *st)
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		if ((*it) = st)
		{
			studentList.erase(it);
			return true;
		}
		it++;
	}
	return false;
}

void Course::PrintStud() //���� ������ ��ü���
{
	vector<Student *>::iterator it = studentList.begin();
	int i = 0;
	while (it < studentList.end())
	{
		cout << i + 1 << ". " << (*it)->getID() << " " << (*it)->getName() << endl;
		it++;
	}
	cout << endl;
}

void Course::setGrade(int num, string grade)
{
	studentList.at(num)->SetGrade(this, grade);
}

void Course::undoCourse()
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		(*it)->RegisterCourse(this);
		it++;
	}
}

void Course::appendID()
{
	this->id.append("-1");
}

void PrintCourse() //��ü ���� ���
{
	vector<Course *>::iterator it = courseList.begin();
	int i = 0;
	if (courseList.size() > 0)
	{
		cout << "***��ü ���� ���***" << endl;
		while (it < courseList.end())
		{
			cout << i + 1 << ". " << (*it)->getID() << " " << (*it)->getName() << endl;
			it++; i++;
		}
		cout << endl;
	}
	else cout << "���� ���ǰ� �����ϴ�." << endl << endl;
}

Course* FindCourse(string id)
{
	vector<Course *>::iterator it = courseList.begin();
	while (it < courseList.end())
	{
		if ((*it)->getID() == id) return (*it);
		it++;
	}
	return NULL;
}
Course* FindCourse(string name, string id)
{
	vector<Course *>::iterator it = courseList.begin();
	int i = 0;
	while (it < courseList.end())
	{
		if ((*it)->getID() == id)
		{
			if ((*it)->getName() == name) return (*it);
		}
		it++;
	}
	return NULL;
}

void DeleteCourse(Course *co)
{
	vector<Course *>::iterator it = courseList.begin();
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