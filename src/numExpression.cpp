#include "numExpression.hpp"

NumExpression::NumExpression(double *value) {
    this->value = value;
}

NumExpression::NumExpression(NumExpression *ex1, NumExpression *ex2, char op) : ex1(ex1), ex2(ex2), op(op) {
}

NumExpression::~NumExpression() {
    if (ex1 != 0) {
        delete ex1;
    }

    if (ex2 != 0) {
        delete ex2;
    }
}

double NumExpression::evaluate() {
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
