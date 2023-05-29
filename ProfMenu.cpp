#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "ProfMenu.h"
#include <iostream>
#include <string>
#define INPUT(a) getline(cin, a); if(a=="") return;
#define UndoMessage cout<<"undo 완료"<<endl<<endl;
#define RedoMessage cout<<"redo 완료"<<endl<<endl;

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

extern CommandManager commandManager;
extern int undoflag;

void MenuCommand_Prof::execute() { //교수 메뉴
	while (1) {
		if (menuCommandList.empty() == true) break;
		it = menuCommandList.begin();
		int i = 1;
		while (it < menuCommandList.end()) {
			cout << i << ". " << (*it)->getCommandName() << endl;
			it++; i++;
		} //cout << i << ". " << "undo" << endl; i++;
		//cout << i << ". " << "redo" << endl; i++;
		cout << i << ". " << "종 료" << endl;
		cout << ">> ";
		cin >> select;
		cout << endl;
		if (select >= i) break;
		//else if (select == i - 2) commandManager.undo();
		//else if (select == i - 1)commandManager.redo();
		else commandManager.executeCmd(menuCommandList.at(select - 1));
	}
}

void ProfMenu_Crs::execute()  //교수 메뉴-과목 관련
{
	while (1) {
		if (menuCommandList.empty() == true) break;
		it = menuCommandList.begin();
		int i = 1;
		while (it < menuCommandList.end()) {
			cout << i << ". " << (*it)->getCommandName() << endl;
			it++; i++;
		} //cout << i << ". " << "undo" << endl; i++;
		//cout << i << ". " << "redo" << endl; i++;
		cout << i << ". " << "종 료" << endl;
		cout << ">> ";
		cin >> select;
		cout << endl;
		if (select >= i) break;
		//else if (select == i - 2) commandManager.undo();
		//else if (select == i - 1)commandManager.redo();
		else commandManager.executeCmd(menuCommandList.at(select - 1));
	}
}

void CourseCreation::execute() //과목 개설
{
	string name, id, profid, courseID;
	int count = 0;
	vector<Course *>::iterator it = courseList.begin(), itf;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "과목 이름 :";
		INPUT(name);
		cout << endl;
		cout << "과목 코드 :";
		INPUT(id);
		cout << endl;
		if (id.length() == 5) break;
		cout << "입력값을 다시 확인해주세요." << endl << endl;
	}
	while (1)
	{
		cout << "교수 번호 :";
		INPUT(profid);
		if (FindProfessor(profid) != NULL) break;
		cout << "입력값을 다시 확인해주세요." << endl;
	}
	cout << endl;
	while (it < courseList.end())
	{
		courseID = (*it)->getID();
		if (courseID.compare(0, 5, id) == 0)
		{
			count++;
			itf = it;
		}
		it++;
	}
	if (count >= 1)
	{
		if (count == 1) (*itf)->appendID();
		id.append("-" + to_string(count + 1));
	}
	Course *co = new Course(name, id);
	courseList.push_back(co);
	for (unsigned int i = 0; i < professorList.size(); i++)
	{
		if (profid == professorList.at(i)->getID())
		{
			co->RegisterPr(professorList.at(i));
			professorList.at(i)->RegisterCourse(co);
		}
	}
	lastCo = co;
	lastProf = FindProfessor(profid);
	cout << "과목 이름 : " << name << " 과목 코드 : " << id << " 등록되었음" << endl << endl;
	undoflag = 1;
}
void CourseCreation::undo()
{
	DeleteCourse(lastCo);
	lastProf->DeleteCourse(lastCo);
	UndoMessage
}
void CourseCreation::redo()
{
	courseList.push_back(lastCo);
	lastProf->RegisterCourse(lastCo);
	RedoMessage
}

void CourseDelete::execute() //과목 폐강
{
	string name, id, profid;
	Professor *prof;
	Course *co;
	int i = 0;
	vector<Student *>::iterator it = studentList.begin();
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "과목 이름 : ";
		INPUT(name);
		cout << endl;
		cout << "과목 코드 : ";
		INPUT(id);
		cout << endl;
		cout << "교수 번호 : ";
		INPUT(profid);
		cout << endl;
		prof = FindProfessor(profid);
		co = FindCourse(name, id);
		if (prof != NULL) break;
		if (co != NULL) break;
		cout << "입력한 정보를 다시 확인해주세요." << endl << endl;
	}
	lastCo = co;
	lastProf = prof;
	prof->DeleteCourse(co);
	while (it < studentList.end())
	{
		if ((*it)->DeleteCourse(co))
		{
			laststuList.push_back(*it);
		}
		it++;
	}
	DeleteCourse(co);
	cout << id + " " + name + " 과목 폐강 완료" << endl;
	undoflag = 1;
}
void CourseDelete::undo()
{
	vector<Student *>::iterator it = laststuList.begin();
	courseList.push_back(lastCo);
	lastCo->RegisterPr(lastProf);
	lastProf->RegisterCourse(lastCo);
	while (it < laststuList.end())
	{
		(*it)->RegisterCourse(lastCo);
		it++;
	}
	UndoMessage
}
void CourseDelete::redo()
{
	vector<Student *>::iterator it = laststuList.begin();
	lastProf->DeleteCourse(lastCo);
	while (it < laststuList.end())
	{
		(*it)->DeleteCourse(lastCo);
		it++;
	}
	DeleteCourse(lastCo);
	RedoMessage
}

void CoursePrint::execute() //과목 수강생 출력
{
	string name, id, coid;
	Professor *prof;
	Course *co;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "교수 이름 : ";
		INPUT(name);
		cout << "교수 번호 : ";
		INPUT(id);
		prof = FindProfessor(name, id);
		if (prof != NULL) break;
		cout << "입력한 정보를 다시 확인해주세요." << endl << endl;
	}
	prof->printCo();
	while (1)
	{
		cout << "과목 코드 : ";
		INPUT(coid);
		co = FindCourse(coid);
		if (co != NULL)
		{
			if (co->getProf() == prof) break;
		}
		cout << "입력값을 다시 확인해주세요." << endl << endl;
	}
	co->PrintStud();
}

void GradeSet::execute() //성적 입력
{
	string name, id, coid, grade[20];
	Professor *prof;
	Course *co;
	int i;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "교수 이름 : ";
		INPUT(name);
		cout << "교수 번호 : ";
		INPUT(id);
		prof = FindProfessor(name, id);
		if (prof != NULL) break;
		cout << "입력한 정보를 다시 확인해주세요." << endl << endl;
	}
	prof->printCo();
	while (1)
	{
		cout << "과목 코드 : ";
		INPUT(coid);
		co = FindCourse(coid);
		if (co != NULL)
		{
			if (co->getProf() == prof) break;
		}
		cout << "입력값을 다시 확인해주세요." << endl << endl;
	}
	co->PrintStud();
	cout << "성적을 입력하세요." << endl;
	for (i = 0; i < co->getNumofStud(); i++)
	{
		cout << i + 1 << ". ";
		INPUT(grade[i]);
		lastGrade[i] = grade[i];
	}
	for (i = 0; i < co->getNumofStud(); i++)
	{
		co->setGrade(i, grade[i]);
	}
	lastCo = co;
	undoflag = 1;
}
void GradeSet::undo()
{
	for (int i = 0; i < lastCo->getNumofStud(); i++)
	{
		lastCo->setGrade(i, "\0");
	}
}
void GradeSet::redo()
{
	for (int i = 0; i < lastCo->getNumofStud(); i++)
	{
		lastCo->setGrade(i, lastGrade[i]);
	}
}