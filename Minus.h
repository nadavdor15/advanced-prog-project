#ifndef APP_MINUS_H
#define APP_MINUS_H

#include "BinaryExpression.h"


class Minus : public BinaryExpression {
public:
    Minus(Expression * a, Expression * b);
    double calculate();
};


#endif //APP_MINUS_H
