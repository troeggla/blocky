#include "blockStatement.hpp"

BlockStatement::BlockStatement(int op, BoolExpression *boolean, BlockScope *scope) :
op(op), boolean(boolean), scope(scope) {
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
    }
}
