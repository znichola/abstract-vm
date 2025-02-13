#ifndef STACK_HPP
# define STACK_HPP

#include <vector>

#include "IOperand.hpp"

class Stack
{
private:
    std::vector<const IOperand *> _stack;

public:
// Default constructor
	Stack();

// Copy constructor
	Stack(const Stack &other);

// Destructor
	~Stack();

// Copy assignment operator
	Stack & operator=(const Stack &other);
};

#endif /* STACK_HPP */
