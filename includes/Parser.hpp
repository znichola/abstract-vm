#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include <utility>
# include <optional>

# include "Token.hpp"
# include "Runtime.hpp"

class Parser
{
public:
    using TokIt   = std::vector<Token>::iterator;
    using OptInst = std::optional<Instruction>;
    using OptVal  = std::optional<IOperand *>;

    static Runtime parse(std::vector<Token> tokens);

    static std::optional<TokIt> parseError(TokIt tok_it);

    static std::pair<TokIt, OptInst> parseInstruction(TokIt tok_it, TokIt it_end);

    static std::pair<TokIt, OptVal> parseValue(TokIt tok_it, TokIt it_end);

//    std::pair<std::vector<Token>::iterator, IOperand *> parseValue(std::pair<std::vector<Token>::iterator tokens);
};

#endif /* PARSER_HPP */
