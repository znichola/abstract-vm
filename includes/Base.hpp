#ifndef BASE_HPP
# define BASE_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <cstdint>

#include "IOperand.hpp"
#include "Factory.hpp"

template <typename T>
class Base: public IOperand {
private:
    std::string value;
public:
// Default constructor
    Base() : value("") {}

    Base(std::string v) : value(v) {}

// Copy constructor
    Base(const Base &other) {
    value = other.value;
}

// Destructor
    ~Base() {}

// Copy assignment operator
    Base &operator=(const Base &other) {
    value = other.value;
	return *this;
}

// Methods
    eOperandType getType(void) const {
        if (typeid(T).name() == typeid(int8_t).name())
            return eOperandType::int8;
        if (typeid(T).name() == typeid(int16_t).name())
            return eOperandType::int16;
        if (typeid(T).name() == typeid(int32_t).name())
            return eOperandType::int32;
        if (typeid(T).name() == typeid(float).name())
            return eOperandType::Float;
        if (typeid(T).name() == typeid(double).name())
            return eOperandType::Double;
        return eOperandType::int8;
    }

    int getPrecision(void) const {
        return static_cast<int>(getType());
    }

    std::string const & toString(void) const {
        return value;
    }

    T toValue(const std::string &s) const {
        std::int16_t v = 0;
        std::stringstream ss(s);
        ss >> v;

        if (ss.fail()) {} // TODO : add error handelling for parsing error
       // std::cout << "string:" << s <<  " rest of string:" << s << " toValue: " << std::to_string(static_cast<std::int8_t>(v)) <<std::endl;
        return v;
    }

    // Operators

    IOperand const * operator+( IOperand const &rhs ) const {
        // this type is the highest proprity
        if (getPrecision() >= rhs.getPrecision()) {
            T res = toValue(value) + toValue(rhs.toString());
            return Factory().createOperand(getType(), std::to_string(static_cast<T>(res))); // use the facotry for this
        } else {
            IOperand const *tmp = Factory().createOperand(getType(), toString());
            IOperand const *res = *tmp + rhs; 
            delete tmp;
            return res;
        }
    }
};


#endif /* BASE_HPP */
