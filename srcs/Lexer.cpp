#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include <set>

#include "Lexer.hpp"

// Tokenize this input, cannont fail.
std::vector<Token> Lexer::tokenize(const std::string &line) {

    static std::vector<std::pair<std::regex, eTokenType>> tokenRegex = {
         {std::regex("push "),   eTokenType::t_push}
        ,{std::regex("pop"),     eTokenType::t_pop}
        ,{std::regex("dump"),    eTokenType::t_dump}
        ,{std::regex("assert "), eTokenType::t_assert}
        ,{std::regex("add"),     eTokenType::t_add}
        ,{std::regex("sub"),     eTokenType::t_sub}
        ,{std::regex("mul"),     eTokenType::t_mul}
        ,{std::regex("div"),     eTokenType::t_div}
        ,{std::regex("mod"),     eTokenType::t_mod}
        ,{std::regex("print"),   eTokenType::t_print}
        ,{std::regex("exit"),    eTokenType::t_exit}

        ,{std::regex("int8"),   eTokenType::t_int8}
        ,{std::regex("int16"),  eTokenType::t_int16}
        ,{std::regex("int32"),  eTokenType::t_int32}
        ,{std::regex("float"),  eTokenType::t_float}
        ,{std::regex("double"), eTokenType::t_double}

        ,{std::regex(R"(\((-?[0-9]+\.[0-9]+)\))"), eTokenType::t_z}
        ,{std::regex(R"(\((-?[0-9]+)\))"),         eTokenType::t_n}

        ,{std::regex(";.+"),  eTokenType::t_com}
        ,{std::regex("\\n+"), eTokenType::t_sep}
        ,{std::regex("(.)"),  eTokenType::t_err} // must be last!
    };

    std::vector<Token> tokens;

    std::string match_on = line;
    while (match_on.length() != 0) {
        //std::cout << "MATCHING: \"" << match_on << "\"" << std::endl;
        for (const auto &[regex, type] : tokenRegex) {
            std::smatch match;
            if (std::regex_search(match_on, match, regex, std::regex_constants::match_continuous)) {
                if (type == t_err && tokens.size() > 0 && tokens.back().type == t_err) {
                    tokens.back().data.value() += match[1];
                } else {
                    Token token = {
                        type,
                        match.size() > 1 ?
                            std::optional<std::string>(match[1]) : std::nullopt
                    };
                    tokens.push_back(token);
                }
                match_on = match.suffix(); // must be last! all match indexs ref to this
                break;
            }
        }
    }
    return tokens;
}

std::optional<SyntaxError> isValidValue(unsigned int line_number, Token t1, Token t2);

// Lex the input, checks for err tokens and some syntax errors by inspecting the tokens
std::vector<SyntaxError> Lexer::syntaxValidate(const std::vector<Token> & tokens) {
    unsigned int line_number = 0;
    std::vector<SyntaxError> ret;
    bool can_have_op = true;
    for (auto it = tokens.begin(); it != tokens.end(); it++) {
        auto token = *it;
        if (token.type == t_sep) {
            line_number++;
            can_have_op = true;
        }
        if (token.type == t_err) {
            ret.push_back({line_number, "Unexpected token \"" + token.data.value() + "\""});
        }
        if (isNullaryOp(token)) {
            if (can_have_op) can_have_op = false;
            else ret.push_back({line_number, "Only one operation per line, move \"" + tokenTypeToString(token.type) + "\""});
        }
        if (isUnaryOp(token)) {
            if (can_have_op) can_have_op = false;
            else ret.push_back({line_number, "Only one operation per line, move \"" + tokenTypeToString(token.type) + "\""});

            auto plus1 = std::next(it);
            auto plus2 = std::next(it, 2);
            if (plus1 == tokens.end() || plus2 == tokens.end())
                ret.push_back({line_number, "Incomplete value with \"" + tokenTypeToString(token.type) + "\""});
            else {
                auto res = isValidValue(line_number, *plus1, *plus2);
                if (res.has_value()) ret.push_back(res.value());
            }
        }
    }
    return ret;
}

std::optional<SyntaxError> isValidValue(unsigned int line_number, Token t1, Token t2) {
    if (!isValue(t1))
        return std::optional<SyntaxError>({line_number, "Value must follow an operation \""
            + tokenTypeToString(t1.type) + "\""});
    if (!(t2.type == t_n || t2.type == t_z))
        return std::optional<SyntaxError>({line_number, "Numeric value must be specified \""
            + tokenTypeToString(t2.type) + "\""});

    if (t1.type == t_float || t1.type == t_double) {
        if (t2.type != t_z) 
            return std::optional<SyntaxError>({line_number, "Value missmatch \"" + tokenTypeToString(t1.type)
                + "\" with \"" + t2.data.value() + "\""});
    } else {
        if (t2.type != t_n)
            return std::optional<SyntaxError>({line_number, "Value missmatch \"" + tokenTypeToString(t1.type)
                + "\" with \"" + t2.data.value() + "\""});
    }
    return std::nullopt;
}
