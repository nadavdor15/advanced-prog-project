#ifndef APP_MULTIPLICATION_H
#define APP_MULTIPLICATION_H


#include "BinaryExpression.h"


class Mul : public BinaryExpression {
public:
    Mul(Expression * a, Expression * b);
    double calculate();
};


#endif //APP_MULTIPLICATION_H
