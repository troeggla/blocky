#include "blockStatement.hpp"

BlockStatement::BlockStatement(int op, BoolExpression *boolean, BlockScope *scope) :
op(op), boolean(boolean), scope(scope) {
}

BlockStatement::BlockStatement(int op, NumExpression *num, BlockScope *scope) :
op(op), num(num), scope(scope) {
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
    }
}
