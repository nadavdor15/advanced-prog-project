#include "Command.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>

using namespace std;

class Connect : public Command {
	string _ip_address;
	int _port;
	int _client_fd;

public:
	Connect(int ip_address, int port) {
		_argumentsAmount = 0;
		_ip_address = ip_adress;
		_port = port;
	}

	virtual void doCommand(vector<string>& arguments) {
		thread t1(startClient);
	}

	~Connect() {
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