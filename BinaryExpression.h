#include "Expression.h"

using namespace std;

class BinaryExpression : public Expression {
protected:
    Expression& _left_expression;
    Expression& _right_expression;
public:
    BinaryExpression(Expression& left_expression,
                     Expression& right_expression):
                     _left_expression(left_expression),
                     _right_expression(right_expression) {}
    virtual double calculate(vector<string>& arguments, int index) = 0;
};
