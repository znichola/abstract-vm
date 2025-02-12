#ifndef FACTORY_HPP
# define FACTORY_HPP

#include <memory>

#include "IOperand.hpp"
#include "eOperandType.hpp"

class Factory {
private:

public:
// Default constructor
	Factory();

// Copy constructor
	Factory(const Factory &other);

// Destructor
	~Factory();

// Copy assignment operator
	Factory & operator=(const Factory &other);

    virtual std::unique_ptr<IOperand> create(eOperandType t);
};

#endif /* FACTORY_HPP */
