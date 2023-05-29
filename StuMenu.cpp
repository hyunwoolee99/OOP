#include "StuMenu.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#define INPUT(a) getline(cin, a); if(a=="") return;
#define UndoMessage cout<<"undo 완료"<<endl<<endl;
#define RedoMessage cout<<"redo 완료"<<endl<<endl;

extern vector<Course *> courseList;

extern CommandManager commandManager;
extern int undoflag;

void MenuCommand_Stu::execute() { //학생 메뉴
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

void StuMenu_Course::execute() //학생메뉴-수강관련
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
void RegisterCourse::execute() //수강 신청
{
	string name, id, input;
	Student *st;
	unsigned int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "학생 이름 : ";
		INPUT(name);
		cout << endl;
		cout << "학번 : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "입력한 정보를 다시 확인해주세요." << endl;
	}
	PrintCourse();
	if (courseList.size() != 0)
	{
		while (1)
		{
			cout << "수강 신청할 과목의 번호를 입력하세요." << endl;
			cout << ">> ";
			INPUT(input);
			num = stoi(input);
			if (num <= courseList.size() && num > 0) break;
			cout << "입력값을 다시 확인해주세요." << endl;
		}
		lastCo = courseList.at(num - 1);
		lastStu = st;
		courseList.at(num - 1)->RegisterStud(st);
		st->RegisterCourse(courseList.at(num - 1));
	}
	cout << "수강 신청 완료" << endl << endl;
	undoflag = 1;
}
void RegisterCourse::undo()
{
	lastStu->DeleteCourse(lastCo);
	lastCo->DeleteStud(lastStu);
	UndoMessage
}
void RegisterCourse::redo()
{
	lastCo->RegisterStud(lastStu);
	lastStu->RegisterCourse(lastCo);
	RedoMessage
}

void DropCourse::execute() //수강 취소
{
	string name, id, input;
	Student *st;
	Course *co;
	int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "학생 이름 : ";
		INPUT(name);
		cout << endl;
		cout << "학번 : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "입력한 정보를 다시 확인해주세요.";
	}
	st->printCoList();
	if (st->getCourseList_size() == 0) return;
	while (1)
	{
		cout << "수강 취소할 과목 번호를 입력하세요." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= st->getCourseList_size()) break;
		cout << "입력값을 다시 확인해주세요." << endl;
	}
	co = st->DeleteCourse(num);
	co->DeleteStud(st);
	lastCo = co;
	lastStu = st;
	cout << "수강 취소 완료" << endl << endl;
	undoflag = 1;
}
void DropCourse::undo()
{
	lastCo->RegisterStud(lastStu);
	lastStu->RegisterCourse(lastCo);
	UndoMessage
}
void DropCourse::redo()
{
	lastStu->DeleteCourse(lastCo);
	lastCo->DeleteStud(lastStu);
	RedoMessage
}

void changeCourse::execute() //수강 정정
{
	string name, id, input;
	Student *st;
	Course *co;
	int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "학생 이름 : ";
		INPUT(name);
		cout << endl;
		cout << "학번 : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "입력한 정보를 다시 확인해주세요.";
	}
	st->printCoList();
	if (st->getCourseList_size() == 0) return;
	while (1)
	{
		cout << "수강 취소할 과목 번호를 입력하세요." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= st->getCourseList_size()) break;
		cout << "입력값을 다시 확인해주세요." << endl;
	}
	lastStu = st;
	co = st->DeleteCourse(num);
	beforeCo = co;
	co->DeleteStud(st);
	cout << "수강 취소 완료" << endl << endl;
	PrintCourse();
	while (1)
	{
		cout << "새로 수강신청할 과목 번호를 입력하세요." << endl;
		cout << "이전 단계에서 수강취소한 과목은 선택할 수 없습니다." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= courseList.size())
		{
			if (courseList.at(num - 1) != beforeCo) break;
		}
		cout << "입력값을 다시 확인해주세요." << endl << endl;
	}
	afterCo = courseList.at(num - 1);
	st->RegisterCourse(afterCo);
	cout << "수강 정정 완료." << endl << endl;
	undoflag = 1;
}
void changeCourse::undo()
{
	lastStu->DeleteCourse(afterCo);
	afterCo->DeleteStud(lastStu);
	lastStu->RegisterCourse(beforeCo);
	beforeCo->RegisterStud(lastStu);
	UndoMessage
}
void changeCourse::redo()
{
	lastStu->DeleteCourse(beforeCo);
	beforeCo->DeleteStud(lastStu);
	lastStu->RegisterCourse(afterCo);
	afterCo->RegisterStud(lastStu);
	RedoMessage
}

void StudentPrint::execute() //학생 정보 조회
{
	string id;
	Student* st;
	cin.ignore(100, '\n');
	cout << "학번 : ";
	INPUT(id);
	cout << endl;
	st = FindStudent(id);
	st->printCoGr();
}