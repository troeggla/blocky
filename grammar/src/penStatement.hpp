#ifndef penstatement_hpp
#define penstatement_hpp

#include "statement.hpp"
#include "numExpression.hpp"
#include "pen.hpp"

class PenStatement : public Statement {
    NumExpression *num1, *num2, *num3;
    int op;

public:
    PenStatement(int, NumExpression*, NumExpression*, NumExpression*);
    PenStatement(int, NumExpression*, NumExpression*);
    PenStatement(int, NumExpression*);
    PenStatement(int);

    virtual void evaluate();
};

#endif
