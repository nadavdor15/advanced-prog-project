#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
	Interpreter interpreter;

	string inputStr;
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
