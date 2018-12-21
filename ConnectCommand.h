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
	map<string, double>* _symbolTable;

	void startClient(int port, const char* dst_addr) {
		struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open client socket";

		address.sin_family = AF_INET;
	    inet_aton(dst_addr, &address.sin_addr);
	    address.sin_port = htons(port);

	    connect(_client_fd, (struct sockaddr*) &address, sizeof(address));
	    cout << "Client socket is now connected to: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
	}

public:
	ConnectCommand(map<string, double>* symbolTable) {
		_symbolTable = symbolTable;
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if (arguments.size() < _argumentsAmount)
			throw "Arguments amount is lower than 2";
		const char* ip_address = arguments[++index].c_str();
		int port = stoi(arguments[++index]);
		if (port < MIN_PORT_SIZE || port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		startClient(port, ip_address);
	}

	~ConnectCommand() {
		close(_client_fd);
	}
};