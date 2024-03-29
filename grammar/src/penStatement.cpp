#include "penStatement.hpp"

PenStatement::PenStatement(int op, NumExpression *num1, NumExpression *num2) : op(op), num1(num1), num2(num2) {
}

PenStatement::PenStatement(int op, NumExpression *num1, NumExpression *num2, NumExpression *num3) : 
op(op), num1(num1), num2(num2), num3(num3) {
}

PenStatement::PenStatement(int op, NumExpression *num1) : op(op), num1(num1) {
}

PenStatement::~PenStatement() {
    delete num1;
    delete num2;
    delete num3;
}

void PenStatement::evaluate() {
    if (op == 1) {
        Pen::instance()->gotoXY(num1->evaluate(), num2->evaluate());
    } else if (op == 2) {
        Pen::instance()->turn(num1->evaluate());
    } else if (op == 3) {
        Pen::instance()->drawLine(num1->evaluate());
    } else if (op == 4) {
        Pen::instance()->setDelay(num1->evaluate());
    } else if (op == 5) {
        int red = num1->evaluate();
        int green = num2->evaluate();
        int blue = num3->evaluate();

        Pen::instance()->setColor(red, green, blue);
    } else if (op == 6) {
        Pen::instance()->setDirection(num1->evaluate());
    } else if (op == 7) {
        Pen::instance()->move(num1->evaluate());
    } else if (op == 8) {
        Pen::instance()->lineTo(num1->evaluate(), num2->evaluate());
    }

}
