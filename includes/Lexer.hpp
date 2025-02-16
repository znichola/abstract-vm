#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>

# include "Token.hpp"
# include "SyntaxError.hpp"

class Lexer
{
public:
    static std::vector<Token> tokenize(const std::string &line);
    static std::vector<SyntaxError> lex(const std::vector<Token> & tokens);
};

#endif /* LEXER_HPP */
