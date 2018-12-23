#include "Div.h"
#include <iostream>

double Div::calculate() {
    if (_right == 0)
        throw "Div By Zero";
    return _left->calculate() / _right->calculate();
}

Div::Div(Expression * a, Expression * b) : BinaryExpression(a, b){}