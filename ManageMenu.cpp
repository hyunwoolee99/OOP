#include "ManageMenu.h"
#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include <iostream>
#include <string>
#define INPUT(a) getline(cin, a); if(a=="") return;
#define UndoMessage cout<<"undo 완료"<<endl<<endl;
#define RedoMessage cout<<"redo 완료"<<endl<<endl;

extern vector<Student *> studentList;
extern vector<Professor *> professorList;
extern vector<Course *> courseList;
extern CommandManager commandManager;
extern int undoflag;

void MenuCommand_Manage::execute() //매니저 메뉴
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

void ManageMenu_Assignment::execute() //매니저 메뉴-등록 관련
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

void StudentCreation::execute() //학생 등록
{
	string name[10], id[10], input;			//한번에 10명까지 입력 가능
	int i, j, flag, num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "등록 학생 인원 수 : ";
		INPUT(input);
		num = stoi(input);
		if (num == 0) break;
		else if (num > 0 && num <= 10) break;
		else cout << "등록 인원 수를 다시 확인해주세요.(최대 10명, 정수만 입력)" << endl;
	}
	for (i = 0; i < num; i++)
	{
		while (1)
		{
			flag = 0;
			cout << "학생 이름 : ";
			INPUT(name[i]);
			cout << endl;
			cout << "학 번 : ";
			INPUT(id[i]);
			cout << endl;
			if (id[i].length() == 9)//학번 9자리 확인
			{
				if (studentIDTest(id[i]))//중복검사
				{
					for (j = 0; j < i; j++)
					{
						if (id[j] == id[i]) flag = 1; //입력값끼리 중복
					}
					if (flag == 0) break;
				}
			}
			else cout << "이름과 학번을 다시 확인해주세요." << endl;
		}
	}
	for (i = 0; i < num; i++)
	{
		Student *st = new Student(name[i], id[i]);
		lastStu[i] = st;
		studentList.push_back(st);
	}
	cout << "학생 " << num << " 명 등록 완료" << endl << endl;
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

void ProfessorCreation::execute() //교수 등록
{
	string name[10], id[10], input;			//한번에 10명까지 입력 가능
	int i, j, flag, num;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "등록 교수 인원 수 : ";
		INPUT(input);
		num = stoi(input);
		if (num == 0) break;
		else if (num > 0 && num <= 10) break;
		else cout << "등록 인원 수를 다시 확인해주세요.(최대 10명, 정수만 입력)" << endl;
	}
	cout << endl;
	for (i = 0; i < num; i++)
	{
		while (1)
		{
			flag = 0;
			cout << "교수 이름 : ";
			INPUT(name[i]);
			cout << endl;
			cout << "교수 번호 : ";
			INPUT(id[i]);
			cout << endl;
			if (id[i].length() == 4)//교수번호 4자리 확인
			{
				if (studentIDTest(id[i]))//중복검사
				{
					for (j = 0; j < i; j++)
					{
						if (id[j] == id[i]) flag = 1; //입력값끼리 중복
					}
					if (flag == 0) break;
				}
			}
			else cout << "이름과 교수번호를 다시 확인해주세요." << endl;
		}
	}
	for (i = 0; i < num; i++)
	{
		Professor *prof = new Professor(name[i], id[i]);
		professorList.push_back(prof);
	}
	cout << "교수 " << num << " 명 등록 완료" << endl << endl;
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

void ManageMenu_Delete::execute() //매니저 메뉴-삭제 관련
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

void StudentDelete::execute() //학생 삭제
{
	string name, id;
	vector<Course *>::iterator it = courseList.begin();
	Student *st;
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "학생 이름 : ";
		INPUT(name);
		cout << "학 번 : ";
		INPUT(id);
		cout << endl;
		if (id.length() == 9)//학번 9자리 확인
		{
			st = FindStudent(name, id);
			if (st != NULL) break;
		}
		else cout << "이름과 학번을 다시 확인해주세요." << endl;
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
	cout << "삭제 완료!" << endl;
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

void ProfessorDelete::execute() //교수 삭제
{
	string name, id;
	Professor *prof;
	vector<Student *>::iterator it = studentList.begin();
	vector<Course *>::iterator itc = courseList.begin();
	cin.ignore(100, '\n');
	while (1)
	{
		cout << "교수 이름 : ";
		INPUT(name);
		cout << "교수 번호 : ";
		INPUT(id);
		cout << endl;
		if (id.length() == 4) //학번 4자리 확인
		{
			prof = FindProfessor(name, id);
			if (prof != NULL) break;
		}
		else cout << "이름과 학번을 다시 확인해주세요." << endl;
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
	} //교수 담당 모든 과목 폐강
	DeleteProfessor(prof);//교수리스트에서 삭제
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

void ManageMenu_AllInfo::execute() //매니저 메뉴-학사 정보
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
		cout << "  // 담당교수 : " << courseList.at(i)->getProfName() << endl;
		cout << "수강 학생 수 : " << courseList.at(i)->getNumofStud() << endl;
		courseList.at(i)->PrintStud();
	}
}