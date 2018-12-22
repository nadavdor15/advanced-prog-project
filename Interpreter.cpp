#include <fstream>
#include <iostream>
#include "Interpreter.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "PrintCommand.h"
#define SHOULD_GET_SPACES ",+,-,*,/,<,<=,>,>=,!=,==,=,(,),{,},[,],(),[],{},"
#define DELIM "\t "

using namespace std;

Interpreter::Interpreter() {
	setCommandsMap();
}

vector<string> Interpreter::lexer(string line, const char* delim) {
	addSpaces(line);
	vector<string> commands;
	int firstIndex;
	while ((firstIndex = line.find_first_of(delim)) < line.length()) {
			string word = line.substr(0, firstIndex);
			if (word.length())
				commands.push_back(word);
			line = line.substr(++firstIndex);
	}
	if (line.length())
				commands.push_back(line);
	return commands;
}

void Interpreter::parser(vector<string> line, int index) {
	for (int i = index; i < line.size(); i++) {
		Command* c;
		try {
			c = _commandsMap.at(line[i]);
		} catch (...) {
			cout "Could not resolve '" + line[i] + "'";
			continue;
		}
		try {
			c->doCommand(line, i);
		} catch (string e) {
			cout << e << endl;
			break;
		} catch (char const* e) {
			cout << e << endl;
			break;
		}
	}
}

void Interpreter::setCommandsMap() {
	_commandsMap["openDataServer"] = new OpenServerCommand(&_symbolTable, &_bindTable);
	_commandsMap["connect"] = new ConnectCommand(&_symbolTable);
	_commandsMap["var"] = new DefineVarCommand(&_symbolTable, &_commandsMap);
	_commandsMap["="] = new AssignCommand(&_symbolTable, &_bindTable);
	_commandsMap["print"] = new PrintCommand(&_symbolTable);
}

bool Interpreter::isScriptFile(string& line) {
	bool flag;
	vector<string> words = lexer(line, DELIM);
	if (words.size() != 2)
		return false;
	if (words[0].compare("run") != 0)
		return false;
	line = words[1].substr(1, words[1].length() - 2);
	ifstream file(line);
	flag = (bool) file;
	file.close();
	return flag;
}

void Interpreter::addSpaces(string& line) {
  string needSpaces = string(SHOULD_GET_SPACES);
	for (int i = 0; (i + 1) < line.length(); i++) {
		if (line[i] == '\"')
			while (line[++i] != '\"') {}
		if (needSpaces.find(string(",") + line[i] + string(",")) != string::npos) {
        line.insert(i + 1, " ");
        line.insert(i, " ");
        i+=2;
	  }
  }
}

Interpreter::~Interpreter() {
	for (auto it = _commandsMap.begin(); it != _commandsMap.end(); it++)
		delete it->second;
}