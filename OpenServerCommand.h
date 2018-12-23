#include "Command.h"
#include <iostream>
#include <map>
#include "DataReaderServer.h"

using namespace std;

class OpenServerCommand : public Command {
	DataReaderServer _dataReaderServer;

public:
	OpenServerCommand(map<string,double>* symbolTable, map<string, vector<string>>* bindTable) {
		_dataReaderServer = DataReaderServer(symbolTable, bindTable);
		_argumentsAmount = 2;
	}

	virtual int doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		return _dataReaderServer.doCommand(arguments, index);
	}
};
