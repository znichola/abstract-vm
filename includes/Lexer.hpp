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

    static std::pair<std::vector<Token>, std::vector<SyntaxError>>
        syntaxValidate(const std::vector<Token> & tokens);

    static std::pair<std::vector<Token>, std::vector<SyntaxError>>
        fixSpellings(const std::vector<Token> & tokens);

    static std::pair<std::vector<Token>, std::vector<SyntaxError>>
        dropErrorTokens(const std::vector<Token> & tokens);

    static std::optional<SyntaxError> checkNullaryInstruction();
    static std::optional<SyntaxError> checkUnaryInstruction();
    static std::optional<SyntaxError> checkValue();
};

#endif /* LEXER_HPP */
