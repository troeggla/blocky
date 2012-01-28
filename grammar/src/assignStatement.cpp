#include "assignStatement.hpp"

AssignStatement::AssignStatement(BlockScope *scope, std::string name, NumExpression *num) : 
scope(scope), name(name), num(num), del(false) {
}

AssignStatement::AssignStatement(BlockScope *scope, std::string name) :
scope(scope), name(name), del(true) {
}

AssignStatement::~AssignStatement() {
    delete num;
}

void AssignStatement::evaluate() {
    if (del == false) {
        scope->add_var(name, num->evaluate());
    } else {
        scope->delete_var(name);
    }
}
