#include <sstream>
#include <string>
#include <iostream>
#include <cstdint>

#include "Base.hpp"
#include "Factory.hpp"

// Default constructor
Base::Base() : value("") {}

Base::Base(std::string v) : value(v) {}

// Copy constructor
Base::Base(const Base &other) {
	value = other.value;
}

// Destructor
Base::~Base() {}

// Copy assignment operator
Base &Base::operator=(const Base &other) {
    value = other.value;
	return *this;
}

// Methods
eOperandType Base::getType(void) const {
    return eOperandType::int8;
}

int Base::getPrecision(void) const {
    return static_cast<int>(getType());
}

std::string const & Base::toString(void) const {
    return value;
}

std::int8_t Base::toValue(const std::string &s) const {
    std::int16_t v = 0;
    std::stringstream ss(s);
    ss >> v;

    if (ss.fail()) {} // TODO : add error handelling for parsing error
   // std::cout << "string:" << s <<  " rest of string:" << s << " toValue: " << std::to_string(static_cast<std::int8_t>(v)) <<std::endl;
    return v;
}

// Operators

IOperand const * Base::operator+( IOperand const &rhs ) const {
    // this type is the highest proprity
    if (getPrecision() >= rhs.getPrecision()) {
        int8_t res = toValue(value) + toValue(rhs.toString());
        return Factory().createOperand(getPrecision(), std::to_string(static_cast<int8_t>(res))); // use the facotry for this
    } else {
        IOperand const *tmp = Factory().createOperand(getPrecision(), toString());
        IOperand const *res = *tmp + rhs; 
        delete tmp;
        return res;
    }
}

