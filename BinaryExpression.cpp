#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(Expression *a, Expression *b) {
    this->_left = a;
    this->_right = b;
}