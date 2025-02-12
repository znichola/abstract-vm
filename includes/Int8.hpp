#ifndef INT8_HPP
# define INT8_HPP

#include "IOperand.hpp"

class Int8: public IOperand {
private:
    std::string value;
public:
// Default constructor
	Int8();

    Int8(std::string v);

// Copy constructor
	Int8(const Int8 &other);

// Destructor
	~Int8();

// Copy assignment operator
	Int8 & operator=(const Int8 &other);

// Methods
    eOperandType getType(void) const;
    int getPrecision(void) const;
    std::string const & toString(void) const;

    int8_t toValue(const std::string &s) const;

// Operators
    IOperand const * operator+(IOperand const & rhs) const;
};


#endif /* INT8_HPP */
