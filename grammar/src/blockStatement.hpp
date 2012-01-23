#ifndef blockstatement_hpp
#define blockstatement_hpp

#include "statement.hpp"
#include "blockScope.hpp"
#include "boolExpression.hpp"

class BlockStatement : public Statement {
    BlockScope *scope;
    BlockScope *elseScope;
    BoolExpression *boolean;
    NumExpression *num;
    int op;

public:
    BlockStatement(int, BlockScope*);
    BlockStatement(int, BoolExpression*, BlockScope*);
    BlockStatement(int, BoolExpression*, BlockScope*, BlockScope*);
    BlockStatement(int, NumExpression*, BlockScope*);

    virtual void evaluate();
};

#endif
