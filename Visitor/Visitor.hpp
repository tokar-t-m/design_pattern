#pragma once

#include <iostream>

struct Number;
struct BinaryOperation;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * operation) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual void visit(Visitor * vistitor) const = 0;
    virtual ~Expression() { }
};

struct Number : Expression
{
    Number(double value) : value(value) { }
    double evaluate() const { return value; }
    double get_value() const { return value; }
    void visit(Visitor * visitor) const { visitor->visitNumber(this); }
    ~Number() { }
private:
    double value;
};

struct BinaryOperation : Expression
{
    double evaluate() const {
        if(op == '+') return left->evaluate() + right->evaluate();
        if(op == '-') return left->evaluate() - right->evaluate();
        if(op == '*') return left->evaluate() * right->evaluate();
        if(op == '/') return left->evaluate() / right->evaluate();
        return 0;
    }
    BinaryOperation(Expression const * left, char op, Expression const * right) : left(left), op(op), right(right) { }
    Expression const * get_left() const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }
    void visit(Visitor * visitor) const { visitor->visitBinaryOperation(this); }
    ~BinaryOperation(){
        delete left;
        delete right;
    }

private:
    Expression const * left;
    char op;
    Expression const * right;
};

struct PrintBinaryOperationsVisitor : Visitor {
    void visitNumber(Number const * number) {
        std::cout << number->evaluate() << std::flush;
    }
    void visitBinaryOperation(BinaryOperation const * bop)
    {
        std::cout << "((" << std::flush;
        bop->get_left()->visit(this);
        std::cout << ")" << std::flush;
        std::cout << bop->get_op() << " ";
        std::cout << "(" << std::flush;
        bop->get_right()->visit(this);
        std::cout << "))" << std::flush;
    }
};

