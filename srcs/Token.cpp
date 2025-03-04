#include <map>
#include <set>
#include <sstream>

#include "Token.hpp"

Token::Token() :
    type(t_err), line_number(0), data(std::nullopt) {}

Token::Token(eTokenType type, unsigned int line_number,
        std::optional<std::string> data) :
    type(type), line_number(line_number), data(data) {}

Token::Token(eTokenType type, unsigned int line_number) :
    type(type), line_number(line_number), data(std::nullopt) {}

Token::Token(const Token &other) {
    *this = other;
}

Token::~Token() {};

Token & Token::operator=(const Token &other) {
    type = other.type;
    line_number = other.line_number;
    data = other.data;
    return *this;
}

const std::string & Token::tokenTypeToString(void) const {
    static const std::map<eTokenType, std::string> tokenTypeMap = {
         {t_int8,   "int8"}
        ,{t_int16,  "int16"}
        ,{t_int32,  "int32"}
        ,{t_float,  "float"}
        ,{t_double, "double"}

        ,{t_n,      "N"}
        ,{t_z,      "Z"}

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

        ,{t_com,    "com"}
        ,{t_sep,    "sep"}
        ,{t_err,    "err"}
    };

    static const std::string unknown = "UNKNOWN";
    auto it = tokenTypeMap.find(this->type);
    return (it != tokenTypeMap.end()) ? it->second : unknown;
}

std::ostream &operator<<(std::ostream &os, const Token& token) {
    if (token.type == t_err) {
        os << "" << token.data.value() << "";
    } else {
        os << token.tokenTypeToString();
        if (token.data.has_value())
           os << "(" << token.data.value() << ")";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Token>& tokens) {
    os << "[";
    bool first = true;
    for (const auto &token : tokens) {
        if (!first) os << ", ";
        os << token;
        first = false;
    }
    os << "]";
    return os;
}

bool Token::isNullaryOp(void) const {
    std::set<eTokenType> nullaryOps = {
         t_pop
        ,t_dump
        ,t_add
        ,t_sub
        ,t_mul
        ,t_div
        ,t_mod
        ,t_print
        ,t_exit
    };

    return nullaryOps.find(this->type) != nullaryOps.end();
}

bool Token::isUnaryOp(void) const {
    return this->type == t_push || this->type == t_assert;
}

bool Token::isValue(void) const {
    std::set<eTokenType> values = {
         t_int8
        ,t_int16
        ,t_int32
        ,t_float
        ,t_double
   };
    return values.find(this->type) != values.end();
}

const std::string Token::tokToStr(void) const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

const std::string Token::genErr(const std::string & msg) const {
    std::stringstream ss;
    ss << genSyxErr(msg);
    return ss.str();
}

const SyntaxError Token::genSyxErr(const std::string & msg) const {
    std::stringstream ss;
    ss << msg << " \"" << *this << "\"";
    return (SyntaxError){line_number, ss.str()};
}

