#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>

using namespace std;

class Command {
protected:
	int _argumentsAmount;

public:
	virtual int doCommand(vector<string>& arguments, int index) = 0;
};

#endif