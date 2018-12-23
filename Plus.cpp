#include "Plus.h"

double Plus::calculate() {
    return _left->calculate() + _right->calculate();
}

Plus::Plus(Expression * a, Expression * b) : BinaryExpression(a, b){}