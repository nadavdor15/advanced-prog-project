#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include "CommandExpression.h"

using namespace std;

class Interpreter {
private:
	map<string, CommandExpression*> _commandsMap;
	map<string, double> _symbolTable;
	map<string, vector<string>> _bindTable;

public:
	Interpreter();
	static vector<string> lexer(string line);
	static bool isScriptFile(string& line);
	void parser(vector<string> line, int index);
	~Interpreter();

private:
	void setCommandsMap();
};

#endif