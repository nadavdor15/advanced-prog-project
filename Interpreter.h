#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <map>
#include "Command.h"

using namespace std;

class Interpreter {
private:
	map<string, Command*> _commandsMap;
	map<string, double> _symbolTable;
	map<string, vector<string>> _bindTable;

public:
	Interpreter();
	static vector<string> lexer(string line, const char* delim);
	static bool isScriptFile(string& line);
	void parser(vector<string> line, int index);
	~Interpreter();

private:
	void setCommandsMap();
	static void addSpaces(string& line);
};

#endif