#ifndef APP_NUMBER_H
#define APP_NUMBER_H

#include "Expression.h"

class Number : public Expression {
private:
    double _value;
public:
    double calculate();
    Number(double v);
};

#endif //APP_NUMBER_H
