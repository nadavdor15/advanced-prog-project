#include "Command.h"
#include <iostream>
#include "DataReaderServer.h"

using namespace std;

class OpenServerCommand : public Command {
	DataReaderServer _dataReaderServer;

public:
	OpenServerCommand() {
		_dataReaderServer = DataReaderServer();
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		_dataReaderServer.doCommand(arguments, index);
	}
};
