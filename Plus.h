#include "BinaryExpression.h"

using namespace std;

class Plus : public BinaryExpression {
public:
    Plus(Expression& right_expression,
          Expression& left_expression):
          BinaryExpression(right_expression, left_expression) {}

    double calculate(vector<string>& arguments, int index) {
        return _right_expression.calculate(arguments, index) +
               _left_expression.calculate(arguments, index);
    }
};
