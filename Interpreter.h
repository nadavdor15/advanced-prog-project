#include <vector>
#include <string>
#include <map>
#include "Command.h"

#define DELIM "\t "

using namespace std;

class Interpreter {
private:
	map<string, Command*> _commandsMap;
	map<string, double> _symbolTable;

public:
	Interpreter();
	static vector<string> lexer(string line);
	static bool isScriptFile(string& line);
	void parser(vector<string> line, int index);
	~Interpreter();

private:
	void setCommandsMap();
	static void addSpaces(strin& line);
};