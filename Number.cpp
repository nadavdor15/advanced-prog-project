#include "Number.h"

double Number::calculate() {
    return _value;
}

Number::Number(double v) {
    this->_value = v;
}