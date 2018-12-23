#include <fstream>
#include <iostream>
#include "Interpreter.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "AssignCommand.h"
#include "PrintCommand.h"
#include "CommandExpression.h"
#include "StringHelper.h"
#define DELIM "\t "

using namespace std;

Interpreter::Interpreter() {
	setCommandsMap();
}

vector<string> Interpreter::lexer(string line) {
	return StringHelper::split(line, DELIM);
}

void Interpreter::parser(vector<string> line, int index) {
	for (int i = index; i < line.size(); i++) {
		CommandExpression* command_expression;
		try {
			command_expression = _commandsMap.at(line[i]);
		} catch (...) {
			cout << "Could not resolve '" << line[i] << "'" << endl;
			string argument = StringHelper::getArgument(line);
			StringHelper::addSpaces(argument);
			line = StringHelper::split(argument, " ");
			try {
				command_expression = _commandsMap.at(line[i]);
			} catch (...) {
				continue;
			}
			continue;
		}
		try {
			i = (int) command_expression->calculate(line, i);
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
	_commandsMap["openDataServer"] = new CommandExpression(new OpenServerCommand(&_symbolTable, &_bindTable));
	_commandsMap["connect"] = new CommandExpression(new ConnectCommand(&_symbolTable));
	_commandsMap["var"] = new CommandExpression(new DefineVarCommand(&_symbolTable, &_commandsMap));
	_commandsMap["="] = new CommandExpression(new AssignCommand(&_symbolTable, &_bindTable));
	_commandsMap["print"] = new CommandExpression(new PrintCommand(&_symbolTable));
}

bool Interpreter::isScriptFile(string& line) {
	bool flag;
	vector<string> words = StringHelper::split(line, DELIM);
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

Interpreter::~Interpreter() {
	for (auto it = _commandsMap.begin(); it != _commandsMap.end(); it++)
		delete it->second;
}