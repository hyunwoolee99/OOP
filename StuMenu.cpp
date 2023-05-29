#include "StuMenu.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#define INPUT(a) getline(cin, a); if(a=="") return;
#define UndoMessage cout<<"undo �Ϸ�"<<endl<<endl;
#define RedoMessage cout<<"redo �Ϸ�"<<endl<<endl;

extern vector<Course *> courseList;

extern CommandManager commandManager;
extern int undoflag;

void MenuCommand_Stu::execute() { //�л� �޴�
	while (1) {
		if (menuCommandList.empty() == true) break;
		it = menuCommandList.begin();
		int i = 1;
		while (it < menuCommandList.end()) {
			cout << i << ". " << (*it)->getCommandName() << endl;
			it++; i++;
		} //cout << i << ". " << "undo" << endl; i++;
		//cout << i << ". " << "redo" << endl; i++;
		cout << i << ". " << "�� ��" << endl;
		cout << ">> ";
		cin >> select;
		cout << endl;
		if (select >= i) break;
		//else if (select == i - 2) commandManager.undo();
		//else if (select == i - 1)commandManager.redo();
		else commandManager.executeCmd(menuCommandList.at(select - 1));
	}
}

void StuMenu_Course::execute() //�л��޴�-��������
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
		cout << i << ". " << "�� ��" << endl;
		cout << ">> ";
		cin >> select;
		cout << endl;
		if (select >= i) break;
		//else if (select == i - 2) commandManager.undo();
		//else if (select == i - 1)commandManager.redo();
		else commandManager.executeCmd(menuCommandList.at(select - 1));
	}
}
void RegisterCourse::execute() //���� ��û
{
	string name, id, input;
	Student *st;
	unsigned int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "�л� �̸� : ";
		INPUT(name);
		cout << endl;
		cout << "�й� : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���." << endl;
	}
	PrintCourse();
	if (courseList.size() != 0)
	{
		while (1)
		{
			cout << "���� ��û�� ������ ��ȣ�� �Է��ϼ���." << endl;
			cout << ">> ";
			INPUT(input);
			num = stoi(input);
			if (num <= courseList.size() && num > 0) break;
			cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl;
		}
		lastCo = courseList.at(num - 1);
		lastStu = st;
		courseList.at(num - 1)->RegisterStud(st);
		st->RegisterCourse(courseList.at(num - 1));
	}
	cout << "���� ��û �Ϸ�" << endl << endl;
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

void DropCourse::execute() //���� ���
{
	string name, id, input;
	Student *st;
	Course *co;
	int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "�л� �̸� : ";
		INPUT(name);
		cout << endl;
		cout << "�й� : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���.";
	}
	st->printCoList();
	if (st->getCourseList_size() == 0) return;
	while (1)
	{
		cout << "���� ����� ���� ��ȣ�� �Է��ϼ���." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= st->getCourseList_size()) break;
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl;
	}
	co = st->DeleteCourse(num);
	co->DeleteStud(st);
	lastCo = co;
	lastStu = st;
	cout << "���� ��� �Ϸ�" << endl << endl;
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

void changeCourse::execute() //���� ����
{
	string name, id, input;
	Student *st;
	Course *co;
	int num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "�л� �̸� : ";
		INPUT(name);
		cout << endl;
		cout << "�й� : ";
		INPUT(id);
		if (id.length() == 9)
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���.";
	}
	st->printCoList();
	if (st->getCourseList_size() == 0) return;
	while (1)
	{
		cout << "���� ����� ���� ��ȣ�� �Է��ϼ���." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= st->getCourseList_size()) break;
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl;
	}
	lastStu = st;
	co = st->DeleteCourse(num);
	beforeCo = co;
	co->DeleteStud(st);
	cout << "���� ��� �Ϸ�" << endl << endl;
	PrintCourse();
	while (1)
	{
		cout << "���� ������û�� ���� ��ȣ�� �Է��ϼ���." << endl;
		cout << "���� �ܰ迡�� ��������� ������ ������ �� �����ϴ�." << endl;
		cout << ">> ";
		INPUT(input);
		num = stoi(input);
		if (num > 0 && num <= courseList.size())
		{
			if (courseList.at(num - 1) != beforeCo) break;
		}
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	afterCo = courseList.at(num - 1);
	st->RegisterCourse(afterCo);
	cout << "���� ���� �Ϸ�." << endl << endl;
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

void StudentPrint::execute() //�л� ���� ��ȸ
{
	string id;
	Student* st;
	cin.ignore(100, '\n');
	cout << "�й� : ";
	INPUT(id);
	cout << endl;
	st = FindStudent(id);
	st->printCoGr();
}