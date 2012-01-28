#include "blockStatement.hpp"

BlockStatement::BlockStatement(int op, BlockScope* scope) :
op(op), scope(scope) {
}

BlockStatement::BlockStatement(int op, BoolExpression *boolean, BlockScope *scope) :
op(op), boolean(boolean), scope(scope) {
}

BlockStatement::BlockStatement(int op, BoolExpression *boolean, BlockScope *scope, BlockScope *elseScope) :
op(op), boolean(boolean), scope(scope), elseScope(elseScope) {
}

BlockStatement::BlockStatement(int op, NumExpression *num, BlockScope *scope) :
op(op), num(num), scope(scope) {
}

BlockStatement::~BlockStatement() {
    delete scope;
    delete elseScope;
    delete boolean;
    delete num;
}

void BlockStatement::evaluate() {
    if (op == 1) {
        if (boolean->evaluate()) {
            scope->evaluate();
        }
    } else if (op == 2) {
        if (!boolean->evaluate()) {
            scope->evaluate();
        }
    } else if (op == 3) {
        for (int i=0; i<num->evaluate(); i++) {
            scope->evaluate();
        }
    } else if (op == 4) {
        while (boolean->evaluate()) {
            scope->evaluate();
        }
    } else if (op == 5) {
        if (boolean->evaluate()) {
            scope->evaluate();
        } else {
            if (elseScope != 0) {
                elseScope->evaluate();
            }
        }
    } else if (op == 6) {
        if (!boolean->evaluate()) {
            scope->evaluate();
        } else {
            if (elseScope != 0) {
                elseScope->evaluate();
            }
        }
    } else if (op == 7) {
        scope->dump();
    } else if (op == 8) {
        scope->dumpall();
    }
}
