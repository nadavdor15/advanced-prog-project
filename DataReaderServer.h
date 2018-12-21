#define _BAD_SOURCE
#include "Command.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1
#define MIN_SPEED 1

using namespace std;

class DataReaderServer : public Command {
	int _speed;
	int _server_fd;

public:
	DataReaderServer() {
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if (arguments.size() < 2)
			throw "Amount of arguments is lower than 2";
		int port = stoi(arguments[++index]);
		_speed = stoi(arguments[++index]);
		if (port < MIN_PORT_SIZE || port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		if (_speed < MIN_SPEED)
			throw "Second argument must be positive";
		thread t1(startServer, port);
		t1.detach();
	}

	~DataReaderServer() {
		// close(_server_fd);
	}

private:
	static void startServer(int port) {
		int server_fd;
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open server socket";
    	struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);

		bind(server_fd, (struct sockaddr *)&address, sizeof(address));
		listen(server_fd, 5);
		int _new_socket = accept(server_fd, (struct sockaddr*) &address, &addrlen);
		cout << "Server has now accepted this client: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
	}
};