#include "Command.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

using namespace std;

class ConnectCommand : public Command {
	string _ip_address;
	int _port;
	int _client_fd;

public:
	ConnectCommand() {
		_argumentsAmount = 2;
	}

	virtual void doCommand(vector<string>& arguments, int index) {
		if (arguments.size() < _argumentsAmount)
			throw "Arguments amount is lower than 2";
		_ip_address = arguments[++index];
		_port = arguments[++index];
		thread t1(startClient);
	}

	~ConnectCommand() {
		close(_client_fd);
	}

private:
	void startClient() {
		struct sockaddr_in address;
    	socklen_t addrlen = sizeof(address);

		if ((_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			throw "Could not open client socket";
	    cout << "Client socket is now open on port: " << _port << endl;

		address.sin_family = AF_INET;
	    address.sin_addr.s_addr = inet_aton(_ip_address);
	    address.sin_port = htons(_port);

	    connect(_client_fd, (struct sockaddr*) &address, sizeof(address));
	    cout << "Client socket is now connected to: " << address.sin_addr.s_addr << ", " << address.sin_port << endl;
	}
}