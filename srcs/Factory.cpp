#include <memory>
#include <iostream>

#include "Factory.hpp"
#include "Base.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    (void) value;
    switch (type) {
        case eOperandType::int8:
            std::cout << "int8" << std::endl; 
            return createInt8(value);
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

IOperand const * Factory::createInt8( std::string const & value ) const {
    return new Base<int8_t>(value);
}

/*
IOperand const * createInt16( std::string const & value ) const {
    (void) value;
    return NULL;
}
*/
//IOperand const * createInt32( std::string const & value ) const {}
//IOperand const * createFloat( std::string const & value ) const {}
//IOperand const * createDouble( std::string const & value ) const {}
