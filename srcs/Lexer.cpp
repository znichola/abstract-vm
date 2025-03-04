#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include <set>

#include "Lexer.hpp"

std::optional<SyntaxError>
    isValidValue(unsigned int line_number, Token t1, Token t2);

// Tokenize this input, cannont fail.
std::vector<Token> Lexer::tokenize(const std::string &input) {

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

    unsigned int line_number = 0;

    std::string match_on = input;
    while (match_on.length() != 0) {
        //std::cout << "MATCHING: \"" << match_on << "\"" << std::endl;
        for (const auto &[regex, type] : tokenRegex) {
            std::smatch match;
            if (std::regex_search(match_on, match, regex, std::regex_constants::match_continuous)) {
                if (type == t_err && tokens.size() > 0 && tokens.back().type == t_err) {
                    tokens.back().data.value() += match[1];
                } else {
                    Token token(
                        type,
                        line_number,
                        match.size() > 1 ?
                            std::optional<std::string>(match[1]) : std::nullopt
                            );
                    tokens.push_back(token);
                    if (type == t_sep) line_number += 1;
                }
                match_on = match.suffix(); // must be last! all match indexs ref to this
                break;
            }
        }
    }
    return tokens;
}

// Lex the input, checks for err tokens and some syntax errors by inspecting the tokens
std::pair<std::vector<Token>, std::vector<SyntaxError>>

    Lexer::syntaxValidate(const std::vector<Token> & tokens) {

    unsigned int line_number = 0;

    std::vector<SyntaxError> retErr;
    std::vector<Token>       retTok;
    std::vector<Token>       comments;

    bool can_have_op = true;

    for (auto it = tokens.begin(); it != tokens.end(); it++) {

        auto token = *it;
        if (token.type == t_sep) {
            line_number++;
            can_have_op = true;

            // add comments and sep
            retTok.insert(retTok.end(), comments.begin(), comments.end());
            comments.erase(comments.begin(), comments.end());
            retTok.push_back({t_sep, line_number});

        } else if (token.type == t_com) {
            comments.push_back(token);

        } else if (token.type == t_err) {
            retErr.push_back({token.line_number,
                "Unexpected token \""
                + token.data.value() + "\""});

            comments.push_back({t_com, token.line_number,
                    "; \"" + token.data.value() + "\"" });

        } else if (token.isNullaryOp()) {
            if (can_have_op) can_have_op = false;
            else {
                retErr.push_back(token.
                        genSyxErr("Only one operation per line, move"));

                // add comments and sep
                retTok.insert(retTok.end(), comments.begin(), comments.end());
                comments.erase(comments.begin(), comments.end());
                retTok.push_back({t_sep, line_number});
            }
            retTok.push_back(token);

        } else if (token.isUnaryOp()) {
            if (can_have_op) can_have_op = false;
            else {
                retErr.push_back(token.
                        genSyxErr("Only one operation per line, move"));

                // add comments and sep
                retTok.insert(retTok.end(), comments.begin(), comments.end());
                comments.erase(comments.begin(), comments.end());
                retTok.push_back({t_sep, line_number});
            }
            auto plus1 = std::next(it, 1);
            auto plus2 = std::next(it, 2);

            if (plus1 == tokens.end()) {
                retErr.push_back({token.line_number,
                    "Incomplete value with \""
                    + token.tokenTypeToString() + "\""});

            } else if (plus2 == tokens.end()) {
                retErr.push_back(token.genSyxErr("Incomplete value with"));
                comments.push_back({t_com, line_number, "; " + token.tokToStr()});
            } else {
                auto res = isValidValue(line_number, *plus1, *plus2);
                if (res.has_value()) {
                    retErr.push_back(res.value());
                    comments.push_back({t_com, line_number, "; \""
                            + token.tokToStr() + "\""});
                } else {
                    retTok.push_back(token);
                    retTok.push_back(*plus1);
                    retTok.push_back(*plus2);
                    it += 2;
                }

            }
        } else if (true) {
            retErr.push_back(token.genSyxErr("Lone value error"));
            comments.push_back({t_com, token.line_number, "; \""
                    + token.tokToStr() + "\""});
        }
    }
    retTok.insert(retTok.end(), comments.begin(), comments.end());

    // TODO maybe I need to sort of recursive structure,
    // so I re analyse tokens after I have made the list
    return {retTok, retErr};
}

std::optional<SyntaxError>

    isValidValue(unsigned int line_number, Token t1, Token t2) {

    if (!t1.isValue()) {
        return std::optional<SyntaxError>(t1.
                genSyxErr("Is not a valid value"));
    }
    if (!(t2.type == t_n || t2.type == t_z)) {
        return std::optional<SyntaxError>(t2.
                genSyxErr("Numeric value must be specified"));
    }
    if (t1.type == t_float || t1.type == t_double) {
        if (t2.type != t_z)
            return std::optional<SyntaxError>({line_number,
                    "Value missmatch \"" + t1.tokenTypeToString()
                    + "\" with \"" + t2.data.value() + "\""});
    } else {
        if (t2.type != t_n)
            return std::optional<SyntaxError>({line_number,
                    "Value missmatch \"" + t1.tokenTypeToString()
                    + "\" with \"" + t2.data.value() + "\""});
    }
    return std::nullopt;
}

