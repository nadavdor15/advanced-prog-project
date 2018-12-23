#ifndef APP_DEV_H
#define APP_DEV_H


#include "BinaryExpression.h"


class Div : public BinaryExpression {
public:
    Div(Expression * a, Expression * b);
    double calculate();
};


#endif //APP_DEV_H