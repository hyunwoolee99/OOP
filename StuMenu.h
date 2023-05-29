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
	MenuCommand_Stu() { setCommandName("학생 메뉴"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class StuMenu_Course : public ICommand {
private:
	int select;
	vector<ICommand*> menuCommandList;
	vector<ICommand*>::iterator it;
public:
	StuMenu_Course() { setCommandName("수강 관련"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class RegisterCourse : public ICommand {
private:
	Student *lastStu;
	Course *lastCo;
public:
	RegisterCourse() { setCommandName("수강 신청"); }
	void execute();
	void undo();
	void redo();
};
class DropCourse : public ICommand {
private:
	Student *lastStu;
	Course *lastCo;
public:
	DropCourse() { setCommandName("수강 취소"); }
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
	changeCourse() { setCommandName("수강 정정"); }
	void execute();
	void undo();
	void redo();
};
class StudentPrint : public ICommand {
private:
public:
	StudentPrint() { setCommandName("학생 정보 조회"); }
	void execute();
};
#endif
