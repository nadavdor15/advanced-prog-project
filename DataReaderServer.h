#define _BAD_SOURCE
#include "Command.h"
#include "Interpreter.h"
#include "StringHelper.h"
#include <algorithm>
#include <iostream>
#include <ctype.h>
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
	map<string, vector<string>>* _bindTable;
	map<string,double>* _symbolTable;
public:
	DataReaderServer() {

	}

	DataReaderServer(map<string,double>* symbolTable,
					 map<string, vector<string>>* bindTable) {
		_symbolTable = symbolTable;
		_bindTable = bindTable;
		_argumentsAmount = 2;
	}

	virtual int doCommand(vector<string>& arguments, int index) {
		if ((arguments.size() - 1) < _argumentsAmount)
			throw "Amount of arguments is lower than " + to_string(_argumentsAmount);
		int port = stoi(arguments[++index]);
		int speed = stoi(arguments[++index]);
		if (port < MIN_PORT_SIZE || port > MAX_PORT_SIZE)
			throw "First argument must be in range of 1-65536";
		if (speed < MIN_SPEED)
			throw "Second argument must be positive";
		thread t1(startServer, port, speed, _symbolTable, _bindTable);
		t1.detach();
		return index;
	}

private:
	static void startServer(int port, 
							int speed,
							map<string,double>* symbolTable, map<string,
							vector<string>>* bindTable) {
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
			vector<string> names = getNames();
			for (int i = 0; i < speed; i++) {
				read(new_socket, buffer, 1024);
				vector<string> valuesInString = StringHelper::split(string(buffer), ",");
				vector<double> values;
				for (string value : valuesInString) {
					value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());
					cout  << "in string: '" << value << "'" << endl;
					cout  << "in double: '" << stod(value) << "'" << endl;
					values.push_back(stod(value));
				}
				updateVars(values, symbolTable, bindTable, names);
			}
			auto end = chrono::steady_clock::now();
			int time_left = SECOND_IN_MILLI - chrono::duration_cast<chrono::milliseconds>(end - start).count();
			if (time_left > 0)
				this_thread::sleep_for(chrono::milliseconds(time_left));
		}
	}

	static void updateVars(vector<double> values,
						   map<string,double>* symbolTable,
						   map<string, vector<string>>* bindTable,
						   vector<string>& names) {
		for (int i = 0; i < names.size(); i++) {
			vector<string> binds = bindTable->operator[](names[i]);
			for (string bind : binds)
				symbolTable->at(bind) = values[i];
		}
	}

	static vector<string> getNames() {
		vector<string> names = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
								"/instrumentation/altimeter/indicated-altitude-ft",
								"/instrumentation/altimeter/pressure-alt-ft",
								"/instrumentation/attitude-indicator/indicated-pitch-deg",
								"/instrumentation/attitude-indicator/indicated-roll-deg",
								"/instrumentation/attitude-indicator/internal-pitch-deg",
								"/instrumentation/attitude-indicator/internal-roll-deg",
								"/instrumentation/encoder/indicated-altitude-ft",
								"/instrumentation/encoder/pressure-alt-ft",
								"/instrumentation/gps/indicated-altitude-ft",
								"/instrumentation/gps/indicated-ground-speed-kt",
								"/instrumentation/gps/indicated-vertical-speed",
								"/instrumentation/heading-indicator/indicated-heading-deg",
								"/instrumentation/magnetic-compass/indicated-heading-deg",
								"/instrumentation/slip-skid-ball/indicated-slip-skid",
								"/instrumentation/turn-indicator/indicated-turn-rate",
								"/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
								"/controls/flight/aileron",
								"/controls/flight/elevator",
								"/controls/flight/rudder",
								"/controls/flight/flaps",
								"/controls/engines/engine/throttle",
								"/engines/engine/rpm"};
		return names;
	}
};