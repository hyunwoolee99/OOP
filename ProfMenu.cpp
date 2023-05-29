#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "ProfMenu.h"
#include <iostream>
#include <string>
#define INPUT(a) getline(cin, a); if(a=="") return;
#define UndoMessage cout<<"undo �Ϸ�"<<endl<<endl;
#define RedoMessage cout<<"redo �Ϸ�"<<endl<<endl;

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;

extern CommandManager commandManager;
extern int undoflag;

void MenuCommand_Prof::execute() { //���� �޴�
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

void ProfMenu_Crs::execute()  //���� �޴�-���� ����
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

void CourseCreation::execute() //���� ����
{
	string name, id, profid, courseID;
	int count = 0;
	vector<Course *>::iterator it = courseList.begin(), itf;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "���� �̸� :";
		INPUT(name);
		cout << endl;
		cout << "���� �ڵ� :";
		INPUT(id);
		cout << endl;
		if (id.length() == 5) break;
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	while (1)
	{
		cout << "���� ��ȣ :";
		INPUT(profid);
		if (FindProfessor(profid) != NULL) break;
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl;
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
	cout << "���� �̸� : " << name << " ���� �ڵ� : " << id << " ��ϵǾ���" << endl << endl;
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

void CourseDelete::execute() //���� ��
{
	string name, id, profid;
	Professor *prof;
	Course *co;
	int i = 0;
	vector<Student *>::iterator it = studentList.begin();
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "���� �̸� : ";
		INPUT(name);
		cout << endl;
		cout << "���� �ڵ� : ";
		INPUT(id);
		cout << endl;
		cout << "���� ��ȣ : ";
		INPUT(profid);
		cout << endl;
		prof = FindProfessor(profid);
		co = FindCourse(name, id);
		if (prof != NULL) break;
		if (co != NULL) break;
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���." << endl << endl;
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
	cout << id + " " + name + " ���� �� �Ϸ�" << endl;
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

void CoursePrint::execute() //���� ������ ���
{
	string name, id, coid;
	Professor *prof;
	Course *co;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "���� �̸� : ";
		INPUT(name);
		cout << "���� ��ȣ : ";
		INPUT(id);
		prof = FindProfessor(name, id);
		if (prof != NULL) break;
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	prof->printCo();
	while (1)
	{
		cout << "���� �ڵ� : ";
		INPUT(coid);
		co = FindCourse(coid);
		if (co != NULL)
		{
			if (co->getProf() == prof) break;
		}
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	co->PrintStud();
}

void GradeSet::execute() //���� �Է�
{
	string name, id, coid, grade[20];
	Professor *prof;
	Course *co;
	int i;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "���� �̸� : ";
		INPUT(name);
		cout << "���� ��ȣ : ";
		INPUT(id);
		prof = FindProfessor(name, id);
		if (prof != NULL) break;
		cout << "�Է��� ������ �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	prof->printCo();
	while (1)
	{
		cout << "���� �ڵ� : ";
		INPUT(coid);
		co = FindCourse(coid);
		if (co != NULL)
		{
			if (co->getProf() == prof) break;
		}
		cout << "�Է°��� �ٽ� Ȯ�����ּ���." << endl << endl;
	}
	co->PrintStud();
	cout << "������ �Է��ϼ���." << endl;
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