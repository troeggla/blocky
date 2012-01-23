#include "blockScope.hpp"

BlockScope::BlockScope() {
}

BlockScope::BlockScope(BlockScope *parent) : parent(parent) {
}

BlockScope* BlockScope::get_parent() {
    if (parent == 0) {
        return this;
    }

    return parent;
}

void BlockScope::dump() {
    std::map<std::string, double>::iterator it;

    for (it=variables.begin(); it!=variables.end(); ++it) {
        std::cout << it->first << " => " << it->second << std::endl;
    }
}

void BlockScope::set_var(std::string name, double value) {
    if (variables.find(name) == variables.end()) {
        if (parent != 0) {
            parent->set_var(name, value);
        } else {
            throw std::exception();
        }
    } else {
        variables[name] = value;
    }
}

void BlockScope::add_var(std::string name, double value) {
    try {
        set_var(name, value);
    } catch (std::exception) {
        variables[name] = value; 
    }
}

void BlockScope::delete_var(std::string name) {
    if (variables.find(name) == variables.end()) {
        if (parent != 0) {
            parent->delete_var(name);
        }
    } else {
        variables.erase(name);
    }
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
    try {
        return find_var(name);
    } catch (std::exception) {
        this->add_var(name, 0);
        return 0;
    }
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
