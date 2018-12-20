#include "Command.h"
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
		if (arguments.size() < _argumentsAmount)
			throw "Amount of arguments is lower than 2";
		_dataReaderServer.doCommand(arguments, index);
	}
};
