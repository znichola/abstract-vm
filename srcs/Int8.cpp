#include "Int8.hpp"

// Default constructor
Int8::Int8() : value("") {}

Int8::Int8(int8_t v) : value(std::to_string(v)) {}

// Copy constructor
Int8::Int8(const Int8 &other) {
	value = other.value;
}

// Destructor
Int8::~Int8() {}

// Copy assignment operator
Int8 &Int8::operator=(const Int8 &other) {
    value = other.value;
	return *this;
}

// Methods
eOperandType Int8::getType(void) const {
    return eOperandType::int8;
}

int Int8::getPrecision(void) const {
    return static_cast<int>(getType());
}

std::string const & Int8::toString(void) const {
    return value;
}

// Operators
/*
IOperand const * Int8::operator+( IOperand const &rhs ) const {
    return new Int8(value + rhs.value);
}
*/
