#include <map>

#include "Instruction.hpp"
#include "eTokenType.hpp"

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

eInstructionType InstructionFromToken(eTokenType tt) {
    static const std::map<eTokenType, eInstructionType> tokInstMap = {
         {t_push,   u_push}
        ,{t_assert, u_assert}

        ,{t_pop,    n_pop}
        ,{t_dump,   n_dump}
        ,{t_add,    n_add}
        ,{t_sub,    n_sub}
        ,{t_mul,    n_mul}
        ,{t_div,    n_div}
        ,{t_mod,    n_mod}
        ,{t_print,  n_print}
        ,{t_exit,   n_exit}
    };

    auto it = tokInstMap.find(tt);
    if (it == tokInstMap.end()) throw std::runtime_error("Unknown operation!");
    return it->second;
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
