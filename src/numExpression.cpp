#include "numExpression.hpp"

NumExpression::NumExpression(double value) {
    this->value = new double;
    *(this->value) = value;
}

NumExpression::NumExpression(BlockScope* scope, std::string var) : scope(scope), var(var) {
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

std::string NumExpression::getType() {
    return "numerical";
}

double NumExpression::evaluate() {
    if (this->value != 0) {
        return *value;
    } else if (scope != 0) {
        return scope->get_var(var);
    } else {
        double val1 = ex1->evaluate();
        double val2 = ex2->evaluate();

        switch (op) {
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
