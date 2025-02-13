#include <sstream>
#include <string>
#include <iostream>
#include <cstdint>

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

std::int8_t Int8::toValue(const std::string &s) const {
    std::int16_t v = 0;
    std::stringstream ss(s);
    ss >> v;

    if (ss.fail()) {} // TODO : add error handelling for parsing error
   // std::cout << "string:" << s <<  " rest of string:" << s << " toValue: " << std::to_string(static_cast<std::int8_t>(v)) <<std::endl;
    return v;
}

// Operators

IOperand const * Int8::operator+( IOperand const &rhs ) const {
    // this type is the highest proprity
    if (getPrecision() >= rhs.getPrecision()) {
        int8_t res = toValue(value) + toValue(rhs.toString());
        return new Int8(std::to_string(static_cast<int8_t>(res))); // use the facotry for this
    } else {
        std::cout << "YES" << std::endl;

        // make a new type with factory and convert this to it,
        // then do the math and return the new value

        Int8 *tmp = new Int8(toString());
        IOperand const *res = *tmp + rhs; 
        delete tmp;
        return res;
    }
}
