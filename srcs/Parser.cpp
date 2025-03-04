#include "Factory.hpp"
#include "Parser.hpp"

Runtime Parser::parse(std::vector<Token> tokens) {
    Runtime rt;

    TokIt tok_it = tokens.begin();

    while (tok_it != tokens.end()) {
        auto err = parseSkipTokens(tok_it);
        if (err.has_value()) {
            tok_it = err.value();
            continue;
        }

        auto inst = parseInstruction(tok_it, tokens.end());
        if (inst.second.has_value()) {
            rt.push_back(inst.second.value());
            tok_it = inst.first;
            continue;
        }

        std::cout << "UNKNOWN TOKEN : TODO remove!" << *tok_it << std::endl;
    }

    (void)rt;
    return rt;
}

std::optional<Parser::TokIt> Parser::

    parseSkipTokens(Parser::TokIt tok_it) {

    if (tok_it->type == t_err
        || tok_it->type == t_sep
        || tok_it->type == t_com)
        return tok_it + 1;
    return std::nullopt;
}

std::pair<Parser::TokIt, Parser::OptInst> Parser::

    parseInstruction(Parser::TokIt tok_it, Parser::TokIt it_end) {

    if (tok_it->isNullaryOp()) {
        return std::make_pair(
                tok_it + 1,
                (Instruction){
                    InstructionFromToken(tok_it->type),
                    tok_it->line_number
                    }
                );
    }

    if (tok_it->isUnaryOp()) {
        auto res = Parser::parseValue(tok_it, it_end);
        return std::make_pair(
                res.first,
                (Instruction){
                    InstructionFromToken(tok_it->type),
                    tok_it->line_number,
                    res.second.value()
                    }
                );
    }
    std::cout << *tok_it << std::endl;
    throw std::runtime_error(tok_it->genErr("Unknown instruction"));
}

eOperandType operandTypeFromToken(eTokenType tt);

// Returns manually allocated Operand
std::pair<Parser::TokIt, Parser::OptVal> Parser::

    parseValue(Parser::TokIt tok_it, Parser::TokIt it_end) {

    auto it_p1 = tok_it + 1;
    auto it_p2 = tok_it + 2;

    if (it_p1 == it_end || it_p2 == it_end) {
        throw std::runtime_error(tok_it->
                genErr("Not enough to construct value for"));
    }
    if (!it_p1->isValue()) {
        throw std::runtime_error(it_p1->genErr("Is not a value"));
    }
    if (it_p1->type == t_float || it_p1->type == t_double) {
        if (it_p2->type != t_z)
            throw std::runtime_error(it_p2->genErr("Value types don't match \"" 
                        + it_p1->tokenTypeToString() + "\" with"));
        else {
            auto o = it_p1->type == t_float ? e_Float : e_Double;
            if (!it_p2->data.has_value())
                throw std::runtime_error(it_p2->
                        genErr("Critical: No value with operand"));
            return std::make_pair<Parser::TokIt, Parser::OptVal>(
                        it_p2 + 1,
                        Factory().createOperand(o, it_p2->data.value())
                    );
        }
    } else {
        if (it_p2->type != t_n)
            throw std::runtime_error(it_p2->genErr("Value types don't match \"" 
                        + it_p1->tokenTypeToString() + "\" with"));
        else {
            auto o = operandTypeFromToken(it_p1->type);
            if (!it_p2->data.has_value())
                throw std::runtime_error(it_p2->
                        genErr("Critical: No value with operand"));
            return std::make_pair<Parser::TokIt, Parser::OptVal>(
                        it_p2 + 1,
                        Factory().createOperand(o, it_p2->data.value())
                    );
        }
    }

    throw std::runtime_error("Missing value!");
}

eOperandType operandTypeFromToken(eTokenType tt) {
    if (tt == t_float) return e_Float;
    if (tt == t_double) return e_Double;
    if (tt == t_int8) return e_int8;
    if (tt == t_int16) return e_int16;
    if (tt == t_int32) return e_int32;
    throw std::runtime_error("Critical: Unknow operation type token");
}

