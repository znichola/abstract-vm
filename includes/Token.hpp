#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <ostream>
# include <vector>
# include <optional>

# include "eTokenType.hpp"
# include "SyntaxError.hpp"

class Token {
public:
    eTokenType type;
    unsigned int line_number;
    std::optional<std::string> data;

    // Default constructor
    Token();

    Token(eTokenType type, unsigned int line_number);

    Token(eTokenType type, unsigned int line_number,
            std::optional<std::string> data);

    // Copy constructor
    Token(const Token &other);

    // Move constructor
    Token(Token &&other) noexcept;

    // Destructor
    ~Token();

    // Copy assignment operator
    Token & operator=(const Token &other);

    // Move assignment operator
    Token & operator=(Token &&other) noexcept;

    bool isNullaryOp(void) const;
    bool isUnaryOp(void) const;
    bool isValue(void) const;

    const std::string &tokenTypeToString(void) const;
    const std::string tokToStr(void) const;

    const std::string genErr(const std::string & msg) const;
    const SyntaxError genSyxErr(const std::string & msg) const;
};



std::ostream &operator<<(std::ostream &os, const Token& token);
std::ostream &operator<<(std::ostream &os, const std::vector<Token>& tokens);

#endif /* TOKEN_HPP */
