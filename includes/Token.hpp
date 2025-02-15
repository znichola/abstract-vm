#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <ostream>
# include <vector>
# include <optional>

# include "eTokenType.hpp"

struct Token {
    eTokenType type;
    std::optional<std::string> data = std::nullopt;
};

const std::string &tokenTypeToString(eTokenType type);

std::ostream &operator<<(std::ostream &os, const Token& token);
std::ostream &operator<<(std::ostream &os, const std::vector<Token>& tokens);

#endif /* TOKEN_HPP */
