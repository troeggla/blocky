#include "penStatement.hpp"

PenStatement::PenStatement(int op, NumExpression *num1, NumExpression *num2) : op(op), num1(num1), num2(num2) {
}

PenStatement::PenStatement(int op, NumExpression *num1, NumExpression *num2, NumExpression *num3) : 
op(op), num1(num1), num2(num2), num3(num3) {
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
    } else if (op == 5) {
        int red = num1->evaluate();
        int green = num2->evaluate();
        int blue = num3->evaluate();

        red = (red > 255) ? 255 : red;
        green = (green > 255) ? 255 : green;
        blue = (blue > 255) ? 255 : blue;

        red = (red < 0) ? 0 : red;
        green = (green < 0) ? 0 : green;
        blue = (blue < 0) ? 0 : blue;

        Pen::instance()->setColor(red, green, blue);
    }
}
