#ifndef blockscope_hpp
#define blockscope_hpp

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "statement.hpp"

class BlockScope {
    BlockScope *parent;
    std::vector<Statement*> statements;
    std::map<std::string, double> variables;

public:
    BlockScope();
    BlockScope(BlockScope*);
    ~BlockScope();

    BlockScope* get_parent();

    std::map<std::string, double> getVars();
    void dump_vars(BlockScope*);
    void dump();
    void dumpall();

    void set_var(std::string, double);
    void add_var(std::string, double);
    void delete_var(std::string);

    double find_var(std::string);
    double get_var(std::string);

    void add_statement(Statement*);
    void evaluate();
};

#endif
