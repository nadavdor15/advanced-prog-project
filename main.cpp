#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Interpreter.h"
//edit check
using namespace std;

int main(int argc, char* argv[]) {
	Interpreter interpreter;

	string inputStr;
	while (getline(cin, inputStr)/* && inputStr.compare("exit()") != 0*/) {
		if (Interpreter::isScriptFile(inputStr)) {
			ifstream script(inputStr);
			while (getline(script, inputStr))
				vector<string> line = Interpreter::lexer(inputStr);		
		} else
			vector<string> line = Interpreter::lexer(inputStr);
	}
}
