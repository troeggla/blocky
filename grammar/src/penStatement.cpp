#include "penStatement.hpp"

PenStatement::PenStatement(int op, NumExpression *num1, NumExpression *num2) : op(op), num1(num1), num2(num2) {
}

PenStatement::PenStatement(int op, NumExpression *num1) : op(op), num1(num1) {
}

PenStatement::PenStatement(int op) : op(op) {
}

void PenStatement::evaluate() {
    if (op == 1) {
        Pen::instance()->gotoXY(num1->evaluate(), num2->evaluate());
    } else if (op == 2) {
        Pen::instance()->turn(num1->evaluate());
    } else if (op == 3) {
        Pen::instance()->drawLine(num1->evaluate());
    } else if (op == 4) {
        Pen::instance()->update();
    }
}
