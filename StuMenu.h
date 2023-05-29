#ifndef _StuMenu_H_
#define _StuMenu_H_
#include "Student.h"
#include "Course.h"
#include "Professor.h"
#include "ICommand.h"


class MenuCommand_Stu : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	MenuCommand_Stu() { setCommandName("�л� �޴�"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StuMenu_Course : public ICommand {
private:
	int select;
	vector<ICommand*> menuCommandList;
	vector<ICommand*>::iterator it;
public:
	StuMenu_Course() { setCommandName("���� ����"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class RegisterCourse : public ICommand {
private:
	Student *lastStu;
	Course *lastCo;
public:
	RegisterCourse() { setCommandName("���� ��û"); }
	void execute();
	void undo();
	void redo();
};
class DropCourse : public ICommand {
private:
	Student *lastStu;
	Course *lastCo;
public:
	DropCourse() { setCommandName("���� ���"); }
	void execute();
	void undo();
	void redo();
};
class changeCourse : public ICommand {
private:
	Course *beforeCo;
	Course *afterCo;
	Student *lastStu;
public:
	changeCourse() { setCommandName("���� ����"); }
	void execute();
	void undo();
	void redo();
};
class StudentPrint : public ICommand {
private:
public:
	StudentPrint() { setCommandName("�л� ���� ��ȸ"); }
	void execute();
};
#endif
