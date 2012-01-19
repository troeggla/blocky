#ifndef expression_hpp
#define expression_hpp

#include <string>

class Expression {
public:
    virtual std::string getType() = 0;
};

#endif
