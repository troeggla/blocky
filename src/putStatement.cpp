#include "putStatement.hpp"

PutStatement::PutStatement(std::string *str) : str(str) {
}

PutStatement::PutStatement(NumExpression *num) : num(num) {
}

PutStatement::PutStatement(BoolExpression *boolean) : boolean(boolean) {
}

void PutStatement::evaluate() {
    if (str != 0) {
        std::cout << (*str) << std::endl;
    } else if (num != 0) {
        std::cout << num->evaluate() << std::endl;
    } else if (boolean != 0) {
        std::string val = (boolean->evaluate() == true) ? "true" : "false";
        std::cout << "bool:" << val << std::endl;
    }
}
