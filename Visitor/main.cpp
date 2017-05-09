#include <iostream>
#include "Visitor.hpp"

bool check_equals(Expression const *left, Expression const *right);

int main(int argc, char **argv){
	Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
	Expression * expr = new BinaryOperation(new Number(3), '+', sube);
	std::cout << expr->evaluate() << std::endl;
	PrintBinaryOperationsVisitor visitor;
	expr->visit(&visitor);
	std::cout << "\n" << ((check_equals(sube, expr) == true) ? "true" : "false") << std::endl;
	return 0;
}

bool check_equals(Expression const *left, Expression const *right){
    return (*((size_t*)left) == *((size_t*)right)) ? true : false;
}