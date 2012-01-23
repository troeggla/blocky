#ifndef assignstatement_hpp
#define assignstatement_hpp

#include <string>

#include "blockScope.hpp"
#include "statement.hpp"
#include "numExpression.hpp"
#include "boolExpression.hpp"

class AssignStatement : public Statement {
    bool del;
    BlockScope *scope;
    std::string name;
    NumExpression *num;

public:
    AssignStatement(BlockScope*, std::string, NumExpression*);
    AssignStatement(BlockScope*, std::string);

    virtual void evaluate();
};

#endif
