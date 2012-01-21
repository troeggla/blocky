#ifndef blockscope_hpp
#define blockscope_hpp

#include <string>
#include <map>
#include <vector>

#include "statement.hpp"

class BlockScope {
    std::vector<Statement*> statements;
    std::map<std::string, double> variables;

public:
    void add_var(std::string, double);
    void delete_var(std::string);
    double get_var(std::string);

    void add_statement(Statement*);
    void evaluate();
};

#endif
