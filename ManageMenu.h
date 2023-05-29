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
	MenuCommand_Manage() { setCommandName("매니저 메뉴"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class ManageMenu_Assignment : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ManageMenu_Assignment() { setCommandName("등록 관련"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StudentCreation : public ICommand {
private:
	Student *lastStu[10];
public:
	StudentCreation() { setCommandName("학생 등록"); }
	void execute();
	void undo();
	void redo();
};
class ProfessorCreation : public ICommand {
private:
	Professor *lastProf[10];
public:
	ProfessorCreation() { setCommandName("교수 등록"); }
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
	ManageMenu_Delete() { setCommandName("삭제 관련"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StudentDelete : public ICommand {
private:
	Student *lastStu;
	vector<Course *> lastcourseList;
public:
	StudentDelete() { setCommandName("학생 삭제"); }
	void execute();
	void undo();
	void redo();
};
class ProfessorDelete : public ICommand {
private:
	Professor *lastProf;
	vector<Course *> lastcourseList;
public:
	ProfessorDelete() { setCommandName("교수 삭제"); }
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
	ManageMenu_AllInfo() { setCommandName("학사 정보"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class PrintAll : public ICommand {
private:
public:
	PrintAll() { setCommandName("전체 인원 정보 출력"); }
	void execute();
};
class PrintAllCourse : public ICommand {
private:
public:
	PrintAllCourse() { setCommandName("전체 과목 정보 출력"); }
	void execute();
};

#endif