#ifndef APP_MINUS_H
#define APP_MINUS_H


#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    Plus(Expression * a, Expression * b);
    double calculate();
};

#endif