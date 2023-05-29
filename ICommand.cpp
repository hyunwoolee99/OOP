#include "ICommand.h"
#include <iostream>
#include <string>

extern CommandManager commandManager;
extern int undoflag;

void CommandManager::executeCmd(ICommand *command)
{
	redoStack = stack<ICommand *>();
	command->execute();
	if (undoflag == 1)
	{
		undoStack.push(command);
		undoflag == 0;
		if (undoCount > 0) undoCount--;
	}
}
void CommandManager::undo()
{
	if (undoStack.size() <= 0 || undoCount == 5)
	{
		cout << "undo할 수 없습니다." << endl;
		return;
	}
	undoStack.top()->undo(); if (undoCount < 5) undoCount++;
	redoStack.push(undoStack.top());
	undoStack.pop();
}
void CommandManager::redo()
{
	if (redoStack.size() <= 0)
	{
		cout << "redo할 수 없습니다." << endl;
		return;
	}
	redoStack.top()->redo();
	undoStack.push(redoStack.top());
	redoStack.pop();
}

void Menu::execute()
{
	while (1)
	{
		cout << menuName << endl;
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
		//else if (select == i - 1) commandManager.redo();
		else commandManager.executeCmd(menuCommandList.at(select - 1));
	}
}