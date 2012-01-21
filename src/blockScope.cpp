#include "blockScope.hpp"

BlockScope::BlockScope() {
}

BlockScope::BlockScope(BlockScope *parent) : parent(parent) {
}

void BlockScope::dump() {
    std::map<std::string, double>::iterator it;

    for (it=variables.begin(); it!=variables.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }
}


void BlockScope::add_var(std::string name, double value) {
   variables[name] = value; 
}

void BlockScope::delete_var(std::string name) {
    variables.erase(name);
}

double BlockScope::find_var(std::string name) {
    if (variables.find(name) == variables.end()) {
        if (parent != 0) {
            return parent->find_var(name);
        } else {
            throw std::exception();
        }
    } else {
        return variables[name];
    }
}

double BlockScope::get_var(std::string name) {
    if (variables.find(name) == variables.end()) {
        try {
            return find_var(name);
        } catch (std::exception) {
            this->add_var(name, 0);
            return 0;
        }
    }

    return variables[name];
}

void BlockScope::add_statement(Statement *stmt) {
    statements.push_back(stmt); 
}

void BlockScope::evaluate() {
    std::vector<Statement*>::iterator it;

    for (it=statements.begin(); it<statements.end(); it++) {
        (*it)->evaluate();
    }
}
