#include <iostream>

#include "Factory.hpp"

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

