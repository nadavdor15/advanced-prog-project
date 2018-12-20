#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Interpreter.h"

#define DELIM "\t "

using namespace std;

Interpreter::Interpreter() {
}

static bool Interpreter::isScriptFile(string& line) {
	bool flag;
	vector<string> words = lexer(line);
	if (words.size() != 2)
		return false;
	if (words[0].compare("run") != 0)
		return false;
	line = words[1].substr(1, words[1].length() - 2);
	ifstream file(line);
	flag = (bool) file;
	file.close();
	return flag;
}

static vector<string> Interpreter::lexer(string line) {
	vector<string> commands;
	int firstIndex;
	while ((firstIndex = line.find_first_of(DELIM)) < line.length()) {
			string word = line.substr(0, firstIndex);
			if (word.length())
				commands.push_back(word);
			line = line.substr(++firstIndex);
	}
	if (line.length())
				commands.push_back(line);
	return commands;
}

void Interpreter::parser(vector<string> line, int index) {
	for (int i = index; i < line.size(); i++) {
		
	}
}