#ifndef boolexpression_hpp
#define boolexpression_hpp

#include "numExpression.hpp"

class BoolExpression {
    bool *value;
    char op;
    NumExpression *num;
    BoolExpression *ex1, *ex2;

public:
    BoolExpression(bool value);
    BoolExpression(NumExpression*);
    BoolExpression(BoolExpression*, BoolExpression*, char);
    ~BoolExpression();

    bool evaluate();
};

#endif
