#include "Command.h"
#include "StringHelper.h"
#include <iostream>
#include <map>
#define OPERATORS "-+/*()"

using namespace std;

class AssignCommand : public Command {
	map<string, double>* _symbolTable;
	map<string, vector<string>>* _bindTable;

public:
	AssignCommand(map<string, double>* symbolTable, map<string, vector<string>>* bindTable) {
		_symbolTable = symbolTable;
		_bindTable = bindTable;
		_argumentsAmount = 2;
	}

	virtual int doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Arguments amount is lower than " + to_string(_argumentsAmount);
		if (_symbolTable->find(arguments[index - 1]) == _symbolTable->end())
			throw "The variable " + arguments[index - 1] + " is not defined";
		string argument = StringHelper::getArgument(arguments);
		StringHelper::addSpaces(argument);
		arguments = StringHelper::split(argument, " ");
		if ((arguments.size() - index - 1) >= 2) {
			if (arguments[index + 1].compare(string("bind")) == 0) {
				string path = arguments[index + 2];
				int path_length = path.length();
				if (path[0] != '\"' || path[path_length - 1] != '\"')
					throw "Path should be in quatation marks";
				path = path.substr(1, path_length - 2);
				_bindTable->operator[](path).push_back(arguments[index - 1]);
				return index + 3;
			}
		}
		string operators = string(OPERATORS);
		for (int i = index + 1; i < arguments.size(); i++) {
			try {
				stoi(arguments[i]);
			} catch (...) {
				if (operators.find(arguments[i]) != string::npos)
					continue;
				if (_symbolTable->find(arguments[i]) == _symbolTable->end())
					throw "The variable " + arguments[i] + " is not defined";
				arguments[i] = to_string(_symbolTable->operator[](arguments[i]));
			}
		}
		for (string s : arguments)
			cout << "'" << s << "' ";
		cout << endl;
		return arguments.size();
	}
};