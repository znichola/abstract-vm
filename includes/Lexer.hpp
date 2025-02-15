#ifndef LEXER_HPP
# define LEXER_HPP

# include <vector>
# include <string>

# include "Token.hpp"

class Lexer
{
private:

public:
// Default constructor
	Lexer();

// Copy constructor
	Lexer(const Lexer &other);

// Destructor
	~Lexer();

// Copy assignment operator
	Lexer & operator=(const Lexer &other);

    std::vector<Token> tokenize(const std::string &line) const;
};

#endif /* LEXER_HPP */
