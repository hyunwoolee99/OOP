#ifndef _ProfMenu_H_
#define _ProfMenu_H_
#include "ICommand.h"

class MenuCommand_Prof : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	MenuCommand_Prof() { setCommandName("교수 메뉴"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class ProfMenu_Crs : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ProfMenu_Crs() { setCommandName("과목 관련"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class CourseCreation : public ICommand { //기본코드
private:
	Course *lastCo;
	Professor *lastProf;
public:
	CourseCreation() { setCommandName("과목 개설"); }
	void execute();
	void undo();
	void redo();
};
class CourseDelete : public ICommand {
private:
	Professor *lastProf;
	Course *lastCo;
	vector<Student *> laststuList;
public:
	CourseDelete() { setCommandName("과목 폐강"); }
	void execute();
	void undo();
	void redo();
};
class CoursePrint : public ICommand {
private:
public:
	CoursePrint() { setCommandName("과목 수강생 출력"); }
	void execute();
};
class GradeSet : public ICommand {
private:
	string lastGrade[20];
	Course *lastCo;
public:
	GradeSet() { setCommandName("성적 입력"); }
	void execute();
	void undo();
	void redo();
};

#endif