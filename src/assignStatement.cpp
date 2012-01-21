#include "assignStatement.hpp"

AssignStatement::AssignStatement(BlockScope *scope, std::string name, NumExpression *num) : 
scope(scope), name(name), num(num) {
}

void AssignStatement::evaluate() {
    scope->add_var(name, num->evaluate());
}
