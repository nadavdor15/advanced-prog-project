#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Interpreter.h"
#define DELIM "\t "

using namespace std;

int main(int argc, char* argv[]) {
	Interpreter interpreter;

	string inputStr;
	if (argc == 2) {
		ifstream script(argv[2]);
		while (getline(script, inputStr)) {
			vector<string> line = Interpreter::lexer(inputStr);
			interpreter.parser(line, 0);
		}
	}
	while (getline(cin, inputStr)) {
		if (Interpreter::isScriptFile(inputStr)) {
			ifstream script(inputStr);
			while (getline(script, inputStr)) {
				vector<string> line = Interpreter::lexer(inputStr);
				interpreter.parser(line, 0);
			}
		}
		else {
			vector<string> line = Interpreter::lexer(inputStr);
			interpreter.parser(line, 0);
		}
	}
}
