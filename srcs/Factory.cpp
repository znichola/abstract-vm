#include <memory>
#include <iostream>

#include "Factory.hpp"


// Default constructor
Factory::Factory() {
}

// Copy constructor
Factory::Factory(const Factory &other) {
	*this = other;
}

// Destructor
Factory::~Factory() {
}

// Copy assignment operator
Factory &Factory::operator=(const Factory &other) {
	(void)other;
	// TODO: insert return statement here
	return *this;
}

std::unique_ptr<IOperand> Factory::create(eOperandType t) {
    switch (t) {
        case eOperandType::int8:
            std::cout << "int8" << std::endl; 
          //  return std::make_unique<
        break ; 
        case eOperandType::int16:
            std::cout << "int16" << std::endl; 
        break ; 
        case eOperandType::int32:
            std::cout << "int32" << std::endl; 
        break ; 
        case eOperandType::Float:
            std::cout << "Float" << std::endl; 
        break ; 
        case eOperandType::Double:
            std::cout << "Double" << std::endl; 
        break ; 
    }
    return nullptr;
}
