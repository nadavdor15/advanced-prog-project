#include "Expression.h"

using namespace std;

class Number : public Expression {
private:
    double _value;
public:
    Number(double value) {
        _value = value;
    }

    virtual double calculate(vector<string>& arguments, int index) {
        return _value;
    }
};
