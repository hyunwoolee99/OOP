#include "Student.h"
#include "Professor.h"
#include "Course.h"
#include "StuMenu.h"
#include "ProfMenu.h"
#include "ManageMenu.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<Student *> studentList;
vector<Professor *> professorList;
vector<Course *> courseList;

CommandManager commandManager;
int undoflag = 0;

int main(void) // 이 부분을 수정
{
	Menu *topMenu = new Menu("아주대학교학사시스템");
	ICommand *subMenu1 = new MenuCommand_Stu();
	ICommand *subMenu2 = new MenuCommand_Prof();
	ICommand *subMenu3 = new MenuCommand_Manage();
	ICommand *subMenu1_1 = new StuMenu_Course();
	ICommand *subMenu2_1 = new ProfMenu_Crs();
	ICommand *subMenu3_1 = new ManageMenu_Assignment();
	ICommand *subMenu3_2 = new ManageMenu_Delete();
	ICommand *subMenu3_3 = new ManageMenu_AllInfo();
	ICommand *command1 = new RegisterCourse();
	ICommand *command2 = new DropCourse();
	ICommand *command3 = new changeCourse();
	ICommand *command4 = new StudentPrint();
	ICommand *command5 = new CourseCreation();
	ICommand *command6 = new CourseDelete();
	ICommand *command7 = new CoursePrint();
	ICommand *command8 = new GradeSet();
	ICommand *command9 = new StudentCreation();
	ICommand *command10 = new ProfessorCreation();
	ICommand *command11 = new StudentDelete();
	ICommand *command12 = new ProfessorDelete();
	ICommand *command13 = new PrintAll();
	ICommand *command14 = new PrintAllCourse();
	topMenu->addMenu(subMenu1);
	topMenu->addMenu(subMenu2);
	topMenu->addMenu(subMenu3);
	subMenu1->addMenu(subMenu1_1);
	subMenu1_1->addMenu(command1);
	subMenu1_1->addMenu(command2);
	subMenu1_1->addMenu(command3);
	subMenu1->addMenu(command4);
	subMenu2->addMenu(subMenu2_1);
	subMenu2_1->addMenu(command5);
	subMenu2_1->addMenu(command6);
	subMenu2_1->addMenu(command7);
	subMenu2->addMenu(command8);
	subMenu3->addMenu(subMenu3_1);
	subMenu3_1->addMenu(command9);
	subMenu3_1->addMenu(command10);
	subMenu3->addMenu(subMenu3_2);
	subMenu3_2->addMenu(command11);
	subMenu3_2->addMenu(command12);
	subMenu3->addMenu(subMenu3_3);
	subMenu3_3->addMenu(command13);
	subMenu3_3->addMenu(command14);
	topMenu->execute();
	return 0;
}