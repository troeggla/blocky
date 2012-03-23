#include <stdexcept>
#include <string>

#ifndef exceptions_hpp
#define exceptions_hpp

class UndefinedVarException : public std::runtime_error {
public:
    UndefinedVarException(std::string msg) : std::runtime_error("Variable " + msg + " is not defined") {}
};

class IllegalValueException : public std::runtime_error {
public:
    IllegalValueException(std::string msg) : std::runtime_error("Value " + msg + " is not allowed here") {}
};

#endif
