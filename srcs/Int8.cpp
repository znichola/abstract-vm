#include "Int8.hpp"

// Default constructor
Int8::Int8() : value("") {}

Int8::Int8(std::string v) : value(v) {}

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

IOperand const * Int8::operator+( IOperand const &rhs ) const {
    if (getPrecision() == rhs.getPrecision()) {
        // TODO : convert the commong value, helper function needed!

    }

    eOperandType pres = getPrecision() >= rhs.getPrecision() ? getType() : rhs.getType();



    // in board strokes what needs to happen here is:
    // we get the two values a + b
    // aka this + rhs
    // then we need to figure out who has persision
    // convert everything to this
    // do the op
    // return the result

    // this means I need a function to convert any 
    // value to any other, no matter the string format

    return new Int8(value);
}

