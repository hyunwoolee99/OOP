#ifndef _ICommand_H_
#define _ICommand_H_
#include <vector>
#include <stack>
using namespace std;

class ICommand {
private:
	string commandName;
public:
	void setCommandName(string s) { commandName = s; }
	string getCommandName() { return commandName; }
	virtual void addMenu(ICommand *command) { return; }
	virtual void execute() { return; };
	virtual void undo() { return; }
	virtual void redo() { return; }
};

class CommandManager {
private:
	int undoCount = 0;
	stack<ICommand *> undoStack;
	stack<ICommand *> redoStack;
public:
	CommandManager() {}
	void executeCmd(ICommand *command);
	void undo();
	void redo();
};

class Menu {
private:
	string menuName;
	int select;
	vector<ICommand *> menuCommandList;
	vector<ICommand *>::iterator it;
public:
	Menu(string name) { this->menuName = name; };
	void addMenu(ICommand *command) { menuCommandList.push_back(command); }
	void execute();
};

#endif