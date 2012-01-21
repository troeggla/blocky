#ifndef blockstatement_hpp
#define blockstatement_hpp

#include "statement.hpp"
#include "blockScope.hpp"
#include "boolExpression.hpp"

class BlockStatement : public Statement {
    BlockScope *scope;
    BoolExpression *boolean;
    int op;

public:
    BlockStatement(int, BoolExpression*, BlockScope*);

    virtual void evaluate();
};

#endif
