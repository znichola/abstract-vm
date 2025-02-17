
#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <ostream>
# include <vector>

# include "eInstructionType.hpp"
# include "IOperand.hpp"

struct Instruction {
    eInstructionType type;
    const IOperand * arg = nullptr;
};

const std::string &instructionTypeToString(eInstructionType type);

std::ostream &operator<<(std::ostream &os, const Instruction& instruction);
std::ostream &operator<<(std::ostream &os, const std::vector<Instruction>& instructions);

#endif /* INSTRUCTION_HPP */
