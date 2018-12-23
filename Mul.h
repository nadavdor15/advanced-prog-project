#include "BinaryExpression.h"

class Mul : public BinaryExpression {
public:
    Mul(Expression& right_expression,
        Expression& left_expression):
        BinaryExpression(right_expression, 
                         left_expression) {}
    double calculate();
};
