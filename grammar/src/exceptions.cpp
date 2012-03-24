#include "exceptions.hpp"

UndefinedVarException::UndefinedVarException(std::string msg) : msg(msg) {
}

const char* UndefinedVarException::what() const throw() {
    std::stringstream s;

    s << "Variable " << msg << " is null";
    return s.str().c_str();
}

IllegalValueException::IllegalValueException(double value) : value(value) {
}

const char* IllegalValueException::what() const throw() {
    std::stringstream s;

    s << "Value " << value << " is not allowed here";
    return s.str().c_str();
}
