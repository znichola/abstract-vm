#include <map>

#include "Token.hpp"


const std::string &tokenTypeToString(eTokenType type) {
    static const std::map<eTokenType, std::string> tokenTypeMap = {
         {t_int8,   "int8"}
        ,{t_int16,  "int16"}
        ,{t_int32,  "int32"}
        ,{t_float,  "float"}
        ,{t_double, "double"}

        ,{t_push,   "push"}
        ,{t_pop,    "pop"}
        ,{t_dump,   "dump"}
        ,{t_assert, "assert"}
        ,{t_add,    "add"}
        ,{t_sub,    "sub"}
        ,{t_mul,    "mul"}
        ,{t_div,    "div"}
        ,{t_mod,    "mod"}
        ,{t_print,  "print"}
        ,{t_exit,   "exit"}

        ,{t_sep,    "sep"}
        ,{t_err,    "err"}
    };

    static const std::string unknown = "UNKNOWN";
    auto it = tokenTypeMap.find(type);
    return (it != tokenTypeMap.end()) ? it->second : unknown;
}

std::ostream &operator<<(std::ostream &os, const Token& token) {
    os << tokenTypeToString(token.type);
    if (token.s.has_value())
       os << "(" << token.s.value() << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Token>& tokens) {
    os << "[";
    bool first = true;
    for (const auto &token : tokens) {
        if (!first) os << " ,";
        os << token;
        first = false;
    }
    os << "]";
    return os;
}
