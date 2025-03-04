
#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

# include <ostream>
# include <vector>

# include "eTokenType.hpp"
# include "eInstructionType.hpp"
# include "IOperand.hpp"

struct Instruction {
    eInstructionType type;
    unsigned int     line_number;
    const IOperand * arg = nullptr;
};

eInstructionType InstructionFromToken(eTokenType tt);

const std::string &instructionTypeToString(eInstructionType type);

std::ostream &operator<<(std::ostream &os, const Instruction& instruction);
std::ostream &operator<<(std::ostream &os, const std::vector<Instruction>& instructions);

#endif /* INSTRUCTION_HPP */
