#include "boolExpression.hpp"

BoolExpression::BoolExpression(bool value) {
    this->value = new bool;
    *(this->value) = value;
}

BoolExpression::BoolExpression(NumExpression *ex) : num(ex) {
}

BoolExpression::BoolExpression(BoolExpression *ex1, BoolExpression *ex2, char op) : ex1(ex1), ex2(ex2), op(op) {
}

BoolExpression::~BoolExpression() {
    //XXX IMPLEMENT ME
}

bool BoolExpression::evaluate() {
    if (this->value != 0) {
        return value;
    } else if (this->num != 0) {
        double result = num->evaluate();

        if (result == 0) {
            return false;
        } else {
            return true;
        }
    } else {
        //switch (op) {
        //case T_AND:
            return (ex1->evaluate() and ex2->evaluate());
        //case T_OR:
        //    return (ex1->evaluate() or ex2->evaluate());
        //}
    }
}
