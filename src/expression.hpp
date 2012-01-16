#ifndef expression_hpp
#define expression_hpp

class Expression {
    Expression *ex1, *ex2;
    double* value;
    char op;

public:
    Expression(double);
    Expression(Expression*, Expression*, char);
    ~Expression();

    double evaluate();
};

#endif
