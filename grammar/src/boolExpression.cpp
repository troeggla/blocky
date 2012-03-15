#include "boolExpression.hpp"

BoolExpression::BoolExpression(bool value) {
    this->value = new bool;
    *(this->value) = value;
}

BoolExpression::BoolExpression(NumExpression *ex) : numEx1(ex) {
}

BoolExpression::BoolExpression(BlockScope *scope, std::string name, char op) : scope(scope), name(name), op(op) {
}

BoolExpression::BoolExpression(BoolExpression *ex1, BoolExpression *ex2, char op) : ex1(ex1), ex2(ex2), op(op) {
}

BoolExpression::BoolExpression(NumExpression *ex1, NumExpression *ex2, char op) : numEx1(ex1), numEx2(ex2), op(op) {
}

BoolExpression::~BoolExpression() {
    delete value;
    delete ex1;
    delete ex2;
    delete numEx1;
    delete numEx2;
}

std::string BoolExpression::getType() {
    return "bool";
}

bool BoolExpression::evaluate() {
    if (this->value != 0) {
        return *value;
    } else if (this->numEx1 != 0 and this->numEx2 == 0) {
        double result = numEx1->evaluate();

        if (result == 0) {
            return false;
        } else {
            return true;
        }
    } else if (this->numEx1 != 0 and this->numEx2 != 0) {
        switch (op) {
        case 3:
            return (numEx1->evaluate() == numEx2->evaluate());
        case 4:
            return (numEx1->evaluate() >= numEx2->evaluate());
        case 5:
            return (numEx1->evaluate() <= numEx2->evaluate());
        case 6:
            return (numEx1->evaluate() != numEx2->evaluate());
        case 7:
            return (numEx1->evaluate() > numEx2->evaluate());
        case 8:
            return (numEx1->evaluate() < numEx2->evaluate());
        }
    } else if (scope != 0) {
        if (op == 10) {
            double value = scope->get_var(name);

            if (value == 0) {
                return false;
            } else {
                return true;
            }
        }
    } else {
        switch (op) {
        case 1:
            return (ex1->evaluate() && ex2->evaluate());
        case 2:
            return (ex1->evaluate() || ex2->evaluate());
        case 3:
            return (ex1->evaluate() == ex2->evaluate());
        case 6:
            return (numEx1->evaluate() != numEx2->evaluate());
        case 9:
            return !(ex1->evaluate());
        }
    }
}
