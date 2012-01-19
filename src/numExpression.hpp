#ifndef numExpression_hpp
#define numExpression_hpp

#include <iostream>
#include "expression.hpp"

class NumExpression : public Expression {
    NumExpression *ex1, *ex2;
    double *value;
    char op;

public:
    NumExpression(double);
    NumExpression(NumExpression*, NumExpression*, char);
    ~NumExpression();

    virtual std::string getType();
    double evaluate();
};

#endif
