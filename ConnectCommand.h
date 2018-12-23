#define _BAD_SOURCE
#include "Command.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <map>

#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1

using namespace std;

class ConnectCommand : public Command {
	int _client_fd;
	int _port;
	map<string, double>* _symbolTable;

	void startClient(const char* dst_addr) {
		close(_client_fd);
		struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open client socket";

		address.sin_family = AF_INET;
	    inet_aton(dst_addr, &address.sin_addr);
	    address.sin_port = htons(_port);

	    connect(_client_fd, (struct sockaddr*) &address, sizeof(address));
	    cout << "Client socket is now connected to: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
	}

public:
	ConnectCommand(map<string, double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 2;
		_client_fd = -1;
	}

	virtual int doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Arguments amount is lower than " + to_string(_argumentsAmount);
		const char* ip_address = arguments[++index].c_str();
		_port = stoi(arguments[++index]);
		if (_port < MIN_PORT_SIZE || _port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		startClient(ip_address);
		return index;
	}

	void sendMessage() {

	}

	~ConnectCommand() {
		close(_client_fd);
	}
};