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

// Lex the input, checks for err tokens
std::vector<SyntaxError> Lexer::syntaxValidate(const std::vector<Token> & tokens) {
    unsigned int line_number = 0;
    std::vector<SyntaxError> ret;
    //for (const auto & token : tokens) {
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
        std::set<eTokenType> nullaryOps = {t_pop, t_dump, t_add, t_sub, t_mul, t_div, t_mod, t_print, t_exit};
        if (nullaryOps.find(token.type) != nullaryOps.end()) {
            //  std::cout << "nullary op" << std::endl;
            if (can_have_op) can_have_op = false;
            else ret.push_back({line_number, "Only one operation per line, move \"" + tokenTypeToString(token.type) + "\""});
        }
        if (token.type == t_push || token.type == t_assert) {
            // Unary token, looks ahead by one
            if (can_have_op) can_have_op = false;
            else ret.push_back({line_number, "Only one operation per line, move \"" + tokenTypeToString(token.type) + "\""});
        }
    }
    return ret;
}
