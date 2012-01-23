#include "putStatement.hpp"

PutStatement::PutStatement(int op, std::string *str) : op(op), str(str) {
}

PutStatement::PutStatement(int op, NumExpression *num) : op(op), num(num) {
}

PutStatement::PutStatement(int op, BoolExpression *boolean) : op(op), boolean(boolean) {
}

void PutStatement::evaluate() {
    if (str != 0) {
        if (str->length() > 2) {
            std::string out = str->substr(1, str->length() - 2);
            std::cout << out;
        }
        
        if (op == 1) {
            std::cout << std::endl;
        }
    } else if (num != 0) {
        std::cout << num->evaluate(); 
        
        if (op == 1) {
            std::cout << std::endl;
        }
    } else if (boolean != 0) {
        std::string val = (boolean->evaluate() == true) ? "true" : "false";
        std::cout << "bool:" << val; 
        
        if (op == 1) {
            std::cout << std::endl;
        }
    }
}
