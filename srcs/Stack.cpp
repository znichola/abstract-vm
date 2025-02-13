#include "Stack.hpp"

// Default constructor
Stack::Stack()
{
}

// Copy constructor
Stack::Stack(const Stack &other)
{
	*this = other;
}

// Destructor
Stack::~Stack()
{
}

// Copy assignment operator
Stack &Stack::operator=(const Stack &other)
{
    _stack = other._stack;
	return *this;
}


