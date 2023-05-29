#ifndef _ProfMenu_H_
#define _ProfMenu_H_
#include "ICommand.h"

class MenuCommand_Prof : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	MenuCommand_Prof() { setCommandName("���� �޴�"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class ProfMenu_Crs : public ICommand {
private:
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	ProfMenu_Crs() { setCommandName("���� ����"); }
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};
class CourseCreation : public ICommand { //�⺻�ڵ�
private:
	Course *lastCo;
	Professor *lastProf;
public:
	CourseCreation() { setCommandName("���� ����"); }
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
	CourseDelete() { setCommandName("���� ��"); }
	void execute();
	void undo();
	void redo();
};
class CoursePrint : public ICommand {
private:
public:
	CoursePrint() { setCommandName("���� ������ ���"); }
	void execute();
};
class GradeSet : public ICommand {
private:
	string lastGrade[20];
	Course *lastCo;
public:
	GradeSet() { setCommandName("���� �Է�"); }
	void execute();
	void undo();
	void redo();
};

#endif