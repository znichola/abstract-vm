#include <memory>
#include <iostream>
#include <functional>

#include "Factory.hpp"
#include "Base.hpp"

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {
    static IOperand const *(Factory::*mfs[])(std::string const &) const = {
         &Factory::createInt8
        ,&Factory::createInt16
        ,&Factory::createInt32
        ,&Factory::createFloat
        ,&Factory::createDouble
    };

    return (this->*mfs[type])(value);
}

IOperand const * Factory::dup(IOperand const *o) const {
    return createOperand(o->getType(), o->toString());
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

