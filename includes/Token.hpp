#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>

# include "eTokenType.hpp"

struct Token {
    eTokenType type;
    std::string value = "";
};

#endif /* TOKEN_HPP */
