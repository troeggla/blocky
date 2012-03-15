#include "blockScope.hpp"

BlockScope::BlockScope() {
}

BlockScope::BlockScope(BlockScope *parent) : parent(parent) {
}

BlockScope::~BlockScope() {
    std::vector<Statement*>::iterator it;

    for (it=statements.begin(); it<statements.end(); it++) {
        delete (*it);
    }
}

BlockScope* BlockScope::get_parent() {
    if (parent == 0) {
        return this;
    }

    return parent;
}

std::map<std::string, double> BlockScope::getVars() {
    return variables;
}

void BlockScope::dump_vars(BlockScope *scope) {
    std::map<std::string, double>::iterator it;
    std::map<std::string, double> varmap = scope->getVars();

    for (it=varmap.begin(); it!=varmap.end(); ++it) {
        std::cout << "\t" << it->first << " => " << it->second << std::endl;
    }
}

void BlockScope::dump() {

    std::cout << "----------------------------" << std::endl;
    std::cout << "Variables in current scope: " << std::endl;
   
    this->dump_vars(this);

    std::cout << "----------------------------" << std::endl;
}

void BlockScope::dumpall() {
    BlockScope *scope = this;

    std::cout << "----------------------------" << std::endl;
    std::cout << "Variables in all scopes: " << std::endl;

    while (true) {
        this->dump_vars(scope);

        if (scope == scope->get_parent()) {
            break;
        } else {
            scope = scope->get_parent();
        }
    }

    std::cout << "----------------------------" << std::endl;
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

double BlockScope::get_var(std::string name) {
    if (variables.find(name) == variables.end()) {
        if (parent != 0) {
            return parent->get_var(name);
        } else {
            throw UndefinedVarException(name);
        }
    } else {
        return variables[name];
    }
}

/*double BlockScope::get_var(std::string name) {
    try {
        return find_var(name);
    } catch (std::exception) {
        this->add_var(name, 0);
        return 0;
    }
}*/

void BlockScope::add_statement(Statement *stmt) {
    statements.push_back(stmt); 
}

void BlockScope::evaluate() {
    std::vector<Statement*>::iterator it;

    for (it=statements.begin(); it<statements.end(); it++) {
        (*it)->evaluate();
    }
}
