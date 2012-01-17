#ifndef numExpression_hpp
#define numExpression_hpp

class NumExpression {
    NumExpression *ex1, *ex2;
    double *value;
    char op;

public:
    NumExpression(double);
    NumExpression(NumExpression*, NumExpression*, char);
    ~NumExpression();

    double evaluate();
};

#endif
