#include "Student.h"
#include "Course.h"
#include "Grade.h"
#include <iostream>
#include <string>

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

bool studentIDTest(string id) //�й� �ߺ��˻�
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		if (id == (*it)->getID()) return false;
		it++;
	}
	return true;
}

void Student::printCoGr() //��������, ���� ���
{
	unsigned int i;
	if (courseList.size() == 0)
	{
		cout << "�������� ���� ����." << endl;
	}
	for (i = 0; i < courseList.size(); i++)
	{
		cout << "�������� : " << courseList.at(i)->getName() << " / ���� : ";
		if (gradeList.at(i)->getGrade() == "") cout << "-";
		else cout << gradeList.at(i)->getGrade() << endl;
	}
	cout << endl;
}

void Student::printCoList() //�������� ���� ���
{
	vector<Course*>::iterator it = courseList.begin();
	int i = 0;
	if (courseList.size() > 0)
	{
		cout << "***�������� ����***" << endl;
		while (it < courseList.end())
		{
			cout << i + 1 << ". " << (*it)->getID() << " " << (*it)->getName() << endl;
			it++; i++;
		}
	}
	else cout << "�������� ������ �����ϴ�." << endl;
}

void Student::SetGrade(Course *co, string grade)
{
	vector<Grade *>::iterator it = gradeList.begin();
	while (it < gradeList.end())
	{
		if ((*it)->getCourse() == co) break;
		it++;
	}
	(*it)->setGrade(grade);
}

void Student::RegisterCourse(Course *co) //������û
{
	this->courseList.push_back(co);
	Grade* grade = new Grade(co, "");
	this->gradeList.push_back(grade);
}

bool Student::DeleteCourse(Course *co) //�л� ������Ͽ��� ����
{
	vector<Course *>::iterator it = courseList.begin();
	vector<Grade *>::iterator itg = gradeList.begin();
	while (it < courseList.end())
	{
		if ((*it) == co)
		{
			courseList.erase(it);
			break;
		}
		it++;
	}
	while (itg < gradeList.end())
	{
		if ((*itg)->getCourse() == co)
		{
			delete((*itg));
			return true;
		}
		itg++;
	}
	return false;
}
Course* Student::DeleteCourse(int num) //���(������ �Է¹���)
{
	vector<Course *>::iterator it = courseList.begin();
	vector<Grade *>::iterator itg = gradeList.begin();
	Course *co = courseList.at(num - 1);
	courseList.erase(it + num - 1);
	delete(gradeList.at(num - 1));
	return co; //������ ���� ��ȯ(StuMenu.cpp �������, ���� ����)
}

Student* FindStudent(string name, string id)
{
	vector<Student *>::iterator it=studentList.begin();
	while (it < studentList.end())
	{
		if ((*it)->getID() == id)
		{
			if ((*it)->getName() == name) return (*it);
		}
		it++;
	}
	return NULL;
}

Student* FindStudent(string id) //�л�������ȸ��
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		if ((*it)->getID() == id) return (*it);
		it++;
	}
	return NULL;
}

void DeleteStudent(Student *st)
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		if ((*it) == st)
		{
			studentList.erase(it);
			break;
		}
		it++;
	}
}

