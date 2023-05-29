#include "Student.h"
#include "Course.h"
#include "Grade.h"
#include <iostream>
#include <string>

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

bool studentIDTest(string id) //학번 중복검사
{
	vector<Student *>::iterator it = studentList.begin();
	while (it < studentList.end())
	{
		if (id == (*it)->getID()) return false;
		it++;
	}
	return true;
}

void Student::printCoGr() //수강과목, 성적 출력
{
	unsigned int i;
	if (courseList.size() == 0)
	{
		cout << "수강중인 과목 없음." << endl;
	}
	for (i = 0; i < courseList.size(); i++)
	{
		cout << "수강과목 : " << courseList.at(i)->getName() << " / 성적 : ";
		if (gradeList.at(i)->getGrade() == "") cout << "-";
		else cout << gradeList.at(i)->getGrade() << endl;
	}
	cout << endl;
}

void Student::printCoList() //수강중인 과목 출력
{
	vector<Course*>::iterator it = courseList.begin();
	int i = 0;
	if (courseList.size() > 0)
	{
		cout << "***수강중인 과목***" << endl;
		while (it < courseList.end())
		{
			cout << i + 1 << ". " << (*it)->getID() << " " << (*it)->getName() << endl;
			it++; i++;
		}
	}
	else cout << "수강중인 과목이 없습니다." << endl;
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

void Student::RegisterCourse(Course *co) //수강신청
{
	this->courseList.push_back(co);
	Grade* grade = new Grade(co, "");
	this->gradeList.push_back(grade);
}

bool Student::DeleteCourse(Course *co) //학생 수강목록에서 삭제
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
Course* Student::DeleteCourse(int num) //드랍(정수로 입력받음)
{
	vector<Course *>::iterator it = courseList.begin();
	vector<Grade *>::iterator itg = gradeList.begin();
	Course *co = courseList.at(num - 1);
	courseList.erase(it + num - 1);
	delete(gradeList.at(num - 1));
	return co; //삭제한 강의 반환(StuMenu.cpp 수강취소, 정정 참고)
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

Student* FindStudent(string id) //학생정보조회용
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

