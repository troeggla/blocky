#include "expression.hpp"

Expression::Expression(double value) {
    this->value = &value;
}

Expression::Expression(Expression *ex1, Expression *ex2, char op) : ex1(ex1), ex2(ex2), op(op) {
}

double Expression::evaluate() {
    if (this->value != 0) {
        return *this->value;
    } else {
        switch (this->op) {
        case '+':
            return ex1->evaluate() + ex2->evaluate();
        case '-':
            return ex1->evaluate() - ex2->evaluate();
        case '*':
            return ex1->evaluate() * ex2->evaluate();
        case '/':
            return ex1->evaluate() / ex2->evaluate();
        }
    }
}
