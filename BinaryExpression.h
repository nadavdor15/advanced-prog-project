#ifndef APP_BINARYEXPRESSION_H
#define APP_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression *_right;
    Expression * _left;
    BinaryExpression(Expression * a, Expression * b);
};

#endif //APP_BINARYEXPRESSION_H
