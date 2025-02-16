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
    static std::vector<SyntaxError> syntaxValidate(const std::vector<Token> & tokens);

    static std::optional<SyntaxError> checkNullaryInstruction();
    static std::optional<SyntaxError> checkUnaryInstruction();
    static std::optional<SyntaxError> checkValue();
};

#endif /* LEXER_HPP */
