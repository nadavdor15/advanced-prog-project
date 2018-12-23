#include "Minus.h"

double Minus::calculate() {
    return _left->calculate() - _right->calculate();
}

Minus::Minus(Expression * a, Expression * b) : BinaryExpression(a, b){}