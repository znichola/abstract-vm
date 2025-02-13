#include <memory>
#include <iostream>

#include "Factory.hpp"
#include "Base.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    (void) value;
    switch (type) {
        case eOperandType::int8:
            return createInt8(value);
        break ; 
        case eOperandType::int16:
            return createInt16(value);
        break ; 
        case eOperandType::int32:
            return createInt32(value);
        break ; 
        case eOperandType::Float:
            return createFloat(value);
        break ; 
        case eOperandType::Double:
            return createDouble(value);
        break ; 
    }
    return nullptr;
}

IOperand const * Factory::createInt8( std::string const & value ) const {
    return new Base<int8_t>(value);
}

IOperand const * Factory::createInt16( std::string const & value ) const {
    return new Base<int16_t>(value);
}

IOperand const * Factory::createInt32( std::string const & value ) const {
    return new Base<int32_t>(value);
}

IOperand const * Factory::createFloat( std::string const & value ) const {
    return new Base<float>(value);
}

IOperand const * Factory::createDouble( std::string const & value ) const {
    return new Base<double>(value);
}

