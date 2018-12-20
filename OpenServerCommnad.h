#include "Command.h"
#include "DataReaderServer.h"
#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1
#define MIN_SPEED 1

using namespace std;

class OpenServerCommand : public Command {
	DataReaderServer _dataReaderServer;

public:
	OpenServerCommand() {
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments) {
		if (arguments.size() < _argumentsAmount)
			throw "Amount of arguments is lower than 2";
		int port = stoi(arguments[0]);
		int speed = stoi(arguments[1]);
		if (port < MIN_PORT_SIZE || port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		if (speed < MIN_SPEED)
			throw "Second argument must be positive";
		_dataReaderServer = DataReaderServer(port, speed);
		_dataReaderServer.doCommand();
	}
};
