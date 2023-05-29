#ifndef _ManageMenu_H_
#define _ManageMenu_H_
#include "ICommand.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"

class MenuCommand_Manage : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	MenuCommand_Manage() { setCommandName("�Ŵ��� �޴�"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class ManageMenu_Assignment : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ManageMenu_Assignment() { setCommandName("��� ����"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StudentCreation : public ICommand {
private:
	Student *lastStu[10];
public:
	StudentCreation() { setCommandName("�л� ���"); }
	void execute();
	void undo();
	void redo();
};
class ProfessorCreation : public ICommand {
private:
	Professor *lastProf[10];
public:
	ProfessorCreation() { setCommandName("���� ���"); }
	void execute();
	void undo();
	void redo();
};
class ManageMenu_Delete : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ManageMenu_Delete() { setCommandName("���� ����"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StudentDelete : public ICommand {
private:
	Student *lastStu;
	vector<Course *> lastcourseList;
public:
	StudentDelete() { setCommandName("�л� ����"); }
	void execute();
	void undo();
	void redo();
};
class ProfessorDelete : public ICommand {
private:
	Professor *lastProf;
	vector<Course *> lastcourseList;
public:
	ProfessorDelete() { setCommandName("���� ����"); }
	void execute();
	void undo();
	void redo();
};
class ManageMenu_AllInfo : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ManageMenu_AllInfo() { setCommandName("�л� ����"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class PrintAll : public ICommand {
private:
public:
	PrintAll() { setCommandName("��ü �ο� ���� ���"); }
	void execute();
};
class PrintAllCourse : public ICommand {
private:
public:
	PrintAllCourse() { setCommandName("��ü ���� ���� ���"); }
	void execute();
};

#endif