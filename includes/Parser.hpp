#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <utility>

# include "Token.hpp"
# include "Runtime.hpp"

class Parser
{
public:
    using tok_iter = std::vector<Token>::iterator;
    //using token_iter = std::pair<std::vector<Token>::iterator, Instruction> 
    static Runtime parse(std::vector<Token> tokens);

    std::pair<std::vector<Token>::iterator, Instruction> parseInstruction(tok_iter tokens);

//    std::pair<std::vector<Token>::iterator, IOperand *> parseValue(std::pair<std::vector<Token>::iterator tokens);
};

#endif /* PARSER_HPP */
