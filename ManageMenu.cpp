#include "ManageMenu.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
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

void MenuCommand_Manage::execute() //�Ŵ��� �޴�
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

void ManageMenu_Assignment::execute() //�Ŵ��� �޴�-��� ����
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

void StudentCreation::execute() //�л� ���
{
	string name[10], id[10], input;			//�ѹ��� 10����� �Է� ����
	int i, j, flag, num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "��� �л� �ο� �� : ";
		INPUT(input);
		num = stoi(input);
		if (num == 0) break;
		else if (num > 0 && num <= 10) break;
		else cout << "��� �ο� ���� �ٽ� Ȯ�����ּ���.(�ִ� 10��, ������ �Է�)" << endl;
	}
	for (i = 0; i < num; i++)
	{
		while (1)
		{
			flag = 0;
			cout << "�л� �̸� : ";
			INPUT(name[i]);
			cout << endl;
			cout << "�� �� : ";
			INPUT(id[i]);
			cout << endl;
			if (id[i].length() == 9)//�й� 9�ڸ� Ȯ��
			{
				if (studentIDTest(id[i]))//�ߺ��˻�
				{
					for (j = 0; j < i; j++)
					{
						if (id[j] == id[i]) flag = 1; //�Է°����� �ߺ�
					}
					if (flag == 0) break;
				}
			}
			else cout << "�̸��� �й��� �ٽ� Ȯ�����ּ���." << endl;
		}
	}
	for (i = 0; i < num; i++)
	{
		Student *st = new Student(name[i], id[i]);
		lastStu[i] = st;
		studentList.push_back(st);
	}
	cout << "�л� " << num << " �� ��� �Ϸ�" << endl << endl;
	undoflag = 1;
}
void StudentCreation::undo()
{
	int i = 0;
	while (lastStu[i] != NULL)
	{
		DeleteStudent(lastStu[i]);
		i++;
	}
}
void StudentCreation::redo()
{
	int i = 0;
	while (lastStu[i] != NULL)
	{
		studentList.push_back(lastStu[i]);
		i++;
	}
}

void ProfessorCreation::execute() //���� ���
{
	string name[10], id[10], input;			//�ѹ��� 10����� �Է� ����
	int i, j, flag, num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "��� ���� �ο� �� : ";
		INPUT(input);
		num = stoi(input);
		if (num == 0) break;
		else if (num > 0 && num <= 10) break;
		else cout << "��� �ο� ���� �ٽ� Ȯ�����ּ���.(�ִ� 10��, ������ �Է�)" << endl;
	}
	cout << endl;
	for (i = 0; i < num; i++)
	{
		while (1)
		{
			flag = 0;
			cout << "���� �̸� : ";
			INPUT(name[i]);
			cout << endl;
			cout << "���� ��ȣ : ";
			INPUT(id[i]);
			cout << endl;
			if (id[i].length() == 4)//������ȣ 4�ڸ� Ȯ��
			{
				if (studentIDTest(id[i]))//�ߺ��˻�
				{
					for (j = 0; j < i; j++)
					{
						if (id[j] == id[i]) flag = 1; //�Է°����� �ߺ�
					}
					if (flag == 0) break;
				}
			}
			else cout << "�̸��� ������ȣ�� �ٽ� Ȯ�����ּ���." << endl;
		}
	}
	for (i = 0; i < num; i++)
	{
		Professor *prof = new Professor(name[i], id[i]);
		professorList.push_back(prof);
	}
	cout << "���� " << num << " �� ��� �Ϸ�" << endl << endl;
	undoflag = 1;
}
void ProfessorCreation::undo()
{
	int i = 0;
	while (lastProf[i] != NULL)
	{
		DeleteProfessor(lastProf[i]);
		i++;
	}
}
void ProfessorCreation::redo()
{
	int i = 0;
	while (lastProf[i] != NULL)
	{
		professorList.push_back(lastProf[i]);
		i++;
	}
}

void ManageMenu_Delete::execute() //�Ŵ��� �޴�-���� ����
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

void StudentDelete::execute() //�л� ����
{
	string name, id;
	vector<Course *>::iterator it = courseList.begin();
	Student *st;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "�л� �̸� : ";
		INPUT(name);
		cout << "�� �� : ";
		INPUT(id);
		cout << endl;
		if (id.length() == 9)//�й� 9�ڸ� Ȯ��
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		else cout << "�̸��� �й��� �ٽ� Ȯ�����ּ���." << endl;
	}
	while (it < courseList.end())
	{
		if ((*it)->DeleteStud(st))
		{
			lastcourseList.push_back(*it);
		}
		it++;
	}
	DeleteStudent(st);
	lastStu = st;
	cout << "���� �Ϸ�!" << endl;
	undoflag = 1;
}
void StudentDelete::undo()
{
	vector<Course *>::iterator it = lastcourseList.begin();
	studentList.push_back(lastStu);
	while (it < lastcourseList.end())
	{
		(*it)->RegisterStud(lastStu);
		it++;
	}
	UndoMessage
}
void StudentDelete::redo()
{
	vector<Course *>::iterator it = lastcourseList.begin();
	while (it < lastcourseList.end())
	{
		(*it)->DeleteStud(lastStu);
		it++;
	}
	DeleteStudent(lastStu);
	RedoMessage
}

void ProfessorDelete::execute() //���� ����
{
	string name, id;
	Professor *prof;
	vector<Student *>::iterator it = studentList.begin();
	vector<Course *>::iterator itc = courseList.begin();
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "���� �̸� : ";
		INPUT(name);
		cout << "���� ��ȣ : ";
		INPUT(id);
		cout << endl;
		if (id.length() == 4) //�й� 4�ڸ� Ȯ��
		{
			prof = FindProfessor(name, id);
			if (prof != NULL) break;
		}
		else cout << "�̸��� �й��� �ٽ� Ȯ�����ּ���." << endl;
	}
	while (itc < courseList.end())
	{
		if ((*itc)->getProf() == prof)
		{
			while (it < studentList.end())
			{
				(*it)->DeleteCourse((*itc));
				it++;
			}
			DeleteCourse((*itc));
			lastcourseList.push_back(*itc);
		}
		itc++;
	} //���� ��� ��� ���� ��
	DeleteProfessor(prof);//��������Ʈ���� ����
	lastProf = prof;
	undoflag = 1;
}
void ProfessorDelete::undo()
{
	vector<Course *>::iterator it = lastcourseList.begin();
	professorList.push_back(lastProf);
	while (it < lastcourseList.end())
	{
		(*it)->undoCourse();
	}
}
void ProfessorDelete::redo()
{
	vector<Course *>::iterator it = lastcourseList.begin();
	vector<Student *>::iterator its = studentList.begin();
	while (it < lastcourseList.end())
	{
		while (its < studentList.end())
		{
			(*its)->DeleteCourse((*it));
			its++;
		}
		it++;
	}
	DeleteProfessor(lastProf);
}

void ManageMenu_AllInfo::execute() //�Ŵ��� �޴�-�л� ����
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

void PrintAll::execute()
{
	vector<Student*>::iterator it;
	vector<Professor*>::iterator itp;
	int i = 0;
	it = studentList.begin();
	while (it < studentList.end())
	{
		cout << studentList.at(i)->getID() << " " << studentList.at(i)->getName() << endl;
		studentList.at(i)->printCoGr();
		cout << endl << endl;
		it++; i++;
	}
	itp = professorList.begin();
	i = 0;
	while (itp < professorList.end())
	{
		cout << professorList.at(i)->getID() << " " << professorList.at(i)->getName() << endl;
		professorList.at(i)->printCo();
		cout << endl << endl;
		itp++; i++;
	}
}

void PrintAllCourse::execute()
{
	unsigned int i;
	for (i = 0; i < courseList.size(); i++)
	{
		cout << courseList.at(i)->getID() << " " << courseList.at(i)->getName();
		cout << "  // ��米�� : " << courseList.at(i)->getProfName() << endl;
		cout << "���� �л� �� : " << courseList.at(i)->getNumofStud() << endl;
		courseList.at(i)->PrintStud();
	}
}