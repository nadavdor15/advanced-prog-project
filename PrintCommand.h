#include "Command.h"
#include <iostream>
#include <stdio.h>
#include <map>

using namespace std;

class PrintCommand : public Command {
	map<string, double>* _symbolTable;

public:
	PrintCommand(map<string,double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 1;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		do {
			string arg = arguments[++index];
			int arg_l = arg.length();
			if (arg[0] == '\"' && arg[arg_l - 1] == '\"')
				printf(arg.substr(1, arg_l - 2).c_str());
			else {
				if (_symbolTable->find(arg) == _symbolTable->end())
					throw "The var " + arg + " is not defined";
				cout << _symbolTable->at(arg);
			}
		} while ((++index + 1) < arguments.size() && arguments[index] == "+");
	}
};
