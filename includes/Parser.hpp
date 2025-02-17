#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>

# include "Token.hpp"
# include "Runtime.hpp"

class Parser
{
public:
    static Runtime parse(std::vector<Token> tokens);

};
#endif /* PARSER_HPP */
