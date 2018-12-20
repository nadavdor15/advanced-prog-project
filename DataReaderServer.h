#include "Command.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

using namespace std;

class DataReaderServer : public Command {
	int _port;
	int _speed;
	int _server_fd;
	int _new_socket;

public:
	DataReaderServer() {}

	DataReaderServer(int port, int speed) {
		_argumentsAmount = 0;
		_port = port;
		_speed = speed;
	}

	virtual void doCommand(vector<string>& arguments) {
		thread t1(startServer);
	}

	~DataReaderServer() {
		close(_server_fd);
	}

private:
	void startServer() {
		if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open server socket";
		cout << "Server socket is now open on port: " << _port << endl;
    	struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		address.sin_family = AF_INET;
		address.sin_addr.s_addr = INADDR_ANY;
		address.sin_port = htons(_port);

		bind(_server_fd, (struct sockaddr *)&address, sizeof(address));
		cout << "Server is now binded to 0.0.0.0" << endl;
		listen(_server_fd, 5);
		cout << "Server is now listening to 5" << endl;
		_new_socket = accept(_server_fd, (struct sockaddr*) &address, &addrlen);
		cout << "Server has now accepted this client: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
	}
};