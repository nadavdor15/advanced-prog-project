#include <vector>
#include <string>
#include <map>
#include "Command.h"

#define DELIM "\t "

using namespace std;

class Interpreter {
private:
	map<string, Command> _commandsMap;
	map<string, double> _symbolTable;

public:
	static vector<string> lexer(string line);
	static bool isScriptFile(string& line);
	void parser(vector<string> line, int index);

private:
	void setCommandsMap();
};