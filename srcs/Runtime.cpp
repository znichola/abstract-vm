#include "Runtime.hpp"

// Default constructor
Runtime::Runtime() {}

// Copy constructor
Runtime::Runtime(const Runtime &other) : Stack(other) {
	*this = other;
}

// Destructor
Runtime::~Runtime() {}

// Copy assignment operator
Runtime &Runtime::operator=(const Runtime &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}

void Runtime::addNullaryInst(NullaryInst::func_ptr fn) {
    _byteCode.push_back(new NullaryInst(fn));
}

void Runtime::addUnaryInst(UnaryInst::func_ptr fn, const IOperand * arg) {
    _byteCode.push_back(new UnaryInst(fn, arg));
}

void execute();
