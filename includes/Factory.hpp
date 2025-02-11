#pragma once

#include <memory>

#include "IOperands.hpp"
#include "eOperandType.hpp"

class Factory {
public:
    virtual std::unique_ptr<IOperand> create(eOperandType t);

};

