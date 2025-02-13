#include <sstream>
#include <string>
#include <iostream>

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

int8_t Int8::toValue(const std::string &s) const {
    int8_t v = 0;
    std::stringstream ss(s);
    ss >> v;

    if (ss.fail()) {}// TODO : add error handelling for parsing error
    std::cout << "value: " << v <<std::endl;
    return v;
}

// Operators

IOperand const * Int8::operator+( IOperand const &rhs ) const {
    // this type is the highest proprity
    std::cout << "FOO " << getPrecision() << " " <<  rhs.getPrecision() << "  " << (getPrecision() >= rhs.getPrecision()) << std::endl;
    if (getPrecision() >= rhs.getPrecision()) {

        std::cout << "YES" << std::endl;
        std::cout << toValue(value) << "  " << toValue(rhs.toString()) << std::endl;
        int8_t res = toValue(value) + toValue(rhs.toString());
        std::cout << toValue(value) + toValue(rhs.toString()) << "  " << res << std::endl;

        return new Int8(std::to_string(res)); // use the facotry for this
    } else {
        std::cout << "YES" << std::endl;
        // make a new type with factory and conver this to it,
        // then do the math and return the new such value

        return NULL;
    }
}
