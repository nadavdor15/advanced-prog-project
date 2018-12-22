#define _BAD_SOURCE
#include "Command.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <map>
#define MAX_PORT_SIZE 65536
#define MIN_PORT_SIZE 1
#define MIN_SPEED 1
#define SECOND_IN_MILLI

using namespace std;

class DataReaderServer : public Command {
	map<string, vector<string>>* bindMap;
public:
	DataReaderServer() {
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		int port = stoi(arguments[++index]);
		int speed = stoi(arguments[++index]);
		if (port < MIN_PORT_SIZE || port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		if (speed < MIN_SPEED)
			throw "Second argument must be positive";
		thread t1(startServer, port, speed);
		t1.detach();
	}

private:
	static void startServer(int port, int speed) {
		int server_fd;
		if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open server socket";
    	struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(port);

		if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
			throw "Could not bind";
		if (listen(server_fd, 5) < 0)
			throw "Could not listen, please be more quiet";
		int new_socket = accept(server_fd, (struct sockaddr*) &address, &addrlen);
		if (new_socket < 0)
			throw "Could not accept a client";
		cout << "Server has now accepted this client: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
		while (true) {
			auto start = chrono::steady_clock::now();
			char buffer[1024];
			for (int i = 0; i < speed; i++) {
				read(new_socket, buffer, 1024);
			}
			auto end = chrono::steady_clock::now();
			int time_left = SECOND_IN_MILLI - chrono::duration_cast<chrono::milliseconds>(end - start).count();
			if (time_left > 0)
				this_thread::sleep_for(chrono::milliseconds(time_left));
		}
	}
};