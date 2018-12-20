#include "Command.h"
#include <map>

using namespace std;

class DefineVarCommand : public Command {
	map<string, double>* _symbolTable;

public:
	DefineVarCommand(map<string, double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 1;
	}

	virtual void doCommand(vector<string>& arguments) {
		if (arguments.size() < _argumentsAmount)
			throw "Amount of arguments is lower than 1";
	}
};
