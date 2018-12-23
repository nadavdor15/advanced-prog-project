#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <string>

using namespace std;

class Expression {
public:
	virtual double calculate(vector<string>& arguments, int index) = 0;
};

#endif 
