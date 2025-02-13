#ifndef FACTORY_HPP
# define FACTORY_HPP

# include <memory>

# include "IOperand.hpp"
# include "eOperandType.hpp"

class Factory {
private:
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;

public:
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;
};

#endif /* FACTORY_HPP */
