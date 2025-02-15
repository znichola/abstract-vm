#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>

# include "Token.hpp"

class Lexer
{
public:
    static std::vector<Token> tokenize(const std::string &line);
};

#endif /* LEXER_HPP */
