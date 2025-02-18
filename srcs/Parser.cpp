
#include "Parser.hpp"

Runtime Parser::parse(std::vector<Token> tokens) {
    Runtime rt;

    TokIt tok_it = tokens.begin();

    bool sep_passed = true;
    (void) sep_passed;
    while (tok_it != tokens.end()) {

        auto err = parseError(tok_it); // ignore error tokens
        if (err.has_value()) {
            tok_it = err.value();
            continue;
        }

        auto inst = parseInstruction(tok_it, tokens.end());
        if (inst.second.has_value()) {
            rt.addInstruction(inst.second.value());
            tok_it = inst.first;
            continue;
        }

        std::cout << "UNKNOWN TOKEN" << *tok_it << std::endl;
    }

    (void)rt;
    return rt;
}

std::optional<Parser::TokIt>
    Parser::parseError(Parser::TokIt tok_it) {
    if ((*tok_it).type == t_err) return tok_it + 1;
    return std::nullopt;
}

std::pair<Parser::TokIt, Parser::OptInst>
    Parser::parseInstruction(Parser::TokIt tok_it, Parser::TokIt it_end) {
    if (isNullaryOp(*tok_it)) {
        return std::make_pair(tok_it + 1, (Instruction){InstructionFromToken(tok_it->type)});
    }
    if (isUnaryOp(*tok_it)) {
        Parser::parseValue(tok_it + 1, it_end);
        // must parse int, and pass it as value
        return std::make_pair(tok_it + 1, (Instruction){InstructionFromToken(tok_it->type)});
    }
    return std::make_pair(tok_it + 1, (Instruction){n_pop});
}

std::pair<Parser::TokIt, Parser::OptVal>
    Parser::parseValue(Parser::TokIt tok_it, Parser::TokIt it_end) {
    if (!isValue(*tok_it)) {
        throw "Missing value!";
    }

    auto it_p1 = tok_it + 1;
    auto it_p2 = tok_it + 2;

    if (it_p1 == it_end || it_p2 == it_end) {
        throw "Not enough to construct value";
    }

    //return std::make_pair(tok_it + 1, (Instruction){InstructionFromToken(tok_it->type)});

    throw "Missing value!";
}

