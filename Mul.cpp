#include "Mul.h"

double Mul::calculate() {
    return _left->calculate() * _right->calculate();
}

Mul::Mul(Expression * a, Expression * b) : BinaryExpression(a, b){}