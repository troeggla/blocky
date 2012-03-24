#include <stdexcept>
#include <string>
#include <sstream>

#ifndef exceptions_hpp
#define exceptions_hpp

class UndefinedVarException : public std::exception {
    std::string msg;

public:
    UndefinedVarException(std::string);
    virtual ~UndefinedVarException() throw() {}

    virtual const char* what() const throw(); 
};

class IllegalValueException : public std::exception {
    double value;

public:
    IllegalValueException(double);
    virtual ~IllegalValueException() throw() {}

    virtual const char* what() const throw();
};

#endif
