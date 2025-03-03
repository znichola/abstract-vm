#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <ostream>
# include <vector>
# include <optional>

# include "eTokenType.hpp"

struct Token {
    eTokenType type;
    unsigned int line_number;
    std::optional<std::string> data = std::nullopt;
};

bool isNullaryOp(Token token);
bool isUnaryOp(Token token);
bool isValue(Token token);

const std::string &tokenTypeToString(eTokenType type);

const std::string tokToStr(Token tok);

std::ostream &operator<<(std::ostream &os, const Token& token);
std::ostream &operator<<(std::ostream &os, const std::vector<Token>& tokens);

#endif /* TOKEN_HPP */
