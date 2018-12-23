#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#define SHOULD_GET_SPACES ",+,-,*,/,<,<=,>,>=,!=,==,=,(,),{,},[,],(),[],{},"

#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

class StringHelper {
public:
	static void addSpaces(string& line) {
	  	string needSpaces = string(SHOULD_GET_SPACES);
		for (int i = 0; (i + 1) < line.length(); i++) {
			if (line[i] == '\"')
				while (line[++i] != '\"') {}
			if (needSpaces.find(string(",") + line[i] + string(",")) != string::npos) {
	        	line.insert(i + 1, " ");
	        	line.insert(i, " ");
	        	i+=2;
		  	}
		}
	}

	static string getArgument(vector<string>& arguments) {
		string argument = "";
		for (string arg : arguments)
			argument += (arg + " ");
		return argument;
	}

	static vector<string> split(string line, const char* delim) {
		vector<string> commands;
		int firstIndex;
		while ((firstIndex = line.find_first_of(delim)) < line.length()) {
			string word = line.substr(0, firstIndex);
			if (word.length())
				commands.push_back(word);
			line = line.substr(++firstIndex);
		}
		if (line.length())
			commands.push_back(line);
		return commands;
	}
	
	// static string getArgumentNoSpaces(vector<string>& arguments, int index) {
	// 	string argument = "";
	// 	for (int i = index; i < arguments.size(); i++)
	// 		argument += argument[i];
	// 	argument.erase(remove_if(argument.begin(), argument.end(), ::isspace), argument.end());
	// 	return argument;
	// }
};

#endif