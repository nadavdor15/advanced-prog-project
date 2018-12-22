#include "Command.h"
#include <iostream>
#include <map>

using namespace std;

class AssignCommand : public Command {
	map<string, double>* _symbolTable;

public:
	AssignCommand(map<string, double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Arguments amount is lower than " + to_string(_argumentsAmount);
		
	}
};