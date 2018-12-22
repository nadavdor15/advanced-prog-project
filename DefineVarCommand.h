#include "Command.h"
#include <map>

using namespace std;

class DefineVarCommand : public Command {
	map<string, double>* _symbolTable;
	map<string, Command*>* _savedNames;

public:
	DefineVarCommand(map<string, double>* symbolTable, map<string, Command*>* savedNames) {
		_symbolTable = symbolTable;
		_savedNames = savedNames;
		_argumentsAmount = 1;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		if (_symbolTable->find(arguments[++index]) != _symbolTable->end())
			throw "The variable " + arguments[index] + " cannot be redefined";
		if (_savedNames->find(arguments[index]) != _savedNames->end())
			throw "The name " + arguments[index] + " is a saved word";
		checkValidity(arguments[index]);
		_symbolTable->operator[](arguments[index]) = 0;
	}

private:
	void checkValidity(string varName) {
		for (int i = 0; i < varName.length(); i++)
			if ((varName[i] < 'a' || varName[i] > 'z') && varName[i] != '_' &&
				(varName[i] < 'A' || varName[i] > 'Z') && ('0' > varName[i] || varName[i] > '9'))
				throw "The name " + varName + " contains a char that is not a-z OR A-Z OR 1-9 OR _";
		if ('0' <= varName[0] && varName[0] <= '9')
			throw "The name " + varName + " contains a digit for first char";
	}
};