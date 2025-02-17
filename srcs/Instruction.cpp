#include <map>

#include "Instruction.hpp"

const std::string &instructionTypeToString(eInstructionType type) {
    static const std::map<eInstructionType, std::string> instructionTypeMap = {
         {u_push,   "push"}
        ,{u_assert, "assert"}

        ,{n_pop,    "pop"}
        ,{n_dump,   "dump"}
        ,{n_add,    "add"}
        ,{n_sub,    "sub"}
        ,{n_mul,    "mul"}
        ,{n_div,    "div"}
        ,{n_mod,    "mod"}
        ,{n_print,  "print"}
        ,{n_exit,   "exit"}
    };

    static const std::string unknown = "UNKNOWN";
    auto it = instructionTypeMap.find(type);
    return (it != instructionTypeMap.end()) ? it->second : unknown;
}

std::ostream &operator<<(std::ostream &os, const Instruction& instruction) {
    os << instructionTypeToString(instruction.type);
    if (instruction.arg != nullptr)
       os << "(" << instruction.arg << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Instruction>& instructions) {
    os << "INST: [";
    bool first = true;
    for (const auto &instruction : instructions) {
        if (!first) os << ", ";
        os << instruction;
        first = false;
    }
    os << "]";
    return os;
}
