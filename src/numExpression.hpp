#ifndef numExpression_hpp
#define numExpression_hpp

#include <string>

#include "blockScope.hpp"
#include "expression.hpp"

class NumExpression : public Expression {
    BlockScope *scope;
    std::string var;
    NumExpression *ex1, *ex2;
    double *value;
    char op;

public:
    NumExpression(double);
    NumExpression(BlockScope*, std::string);
    NumExpression(NumExpression*, NumExpression*, char);
    ~NumExpression();

    virtual std::string getType();
    double evaluate();
};

#endif
