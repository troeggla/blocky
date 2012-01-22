#ifndef putstatement_hpp
#define putstatement_hpp

#include <iostream>
#include <string>

#include "statement.hpp"
#include "numExpression.hpp"
#include "boolExpression.hpp"

class PutStatement : public Statement {
    int op;
    NumExpression *num;
    BoolExpression *boolean;
    std::string *str;

public:
    PutStatement(int, std::string*);
    PutStatement(int, NumExpression*);
    PutStatement(int, BoolExpression*);

    virtual void evaluate();
};

#endif
