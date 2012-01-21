#ifndef putstatement_hpp
#define putstatement_hpp

#include <iostream>
#include <string>

#include "statement.hpp"
#include "numExpression.hpp"
#include "boolExpression.hpp"

class PutStatement : public Statement {
    NumExpression *num;
    BoolExpression *boolean;
    std::string *str;

public:
    PutStatement(std::string*);
    PutStatement(NumExpression*);
    PutStatement(BoolExpression*);

    virtual void evaluate();
};

#endif
