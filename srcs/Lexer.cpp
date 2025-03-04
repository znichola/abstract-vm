#include <map>
#include <regex>
#include <utility>
#include <iostream>
#include <set>
#include <tuple>

#include "Lexer.hpp"

std::optional<SyntaxError>
    isValidValue(unsigned int line_number, Token t1, Token t2);

std::tuple<std::vector<Token>, std::vector<Token>, std::vector<SyntaxError>>
    checkSpelling(Token token);

// Tokenize this input, cannont fail.
std::vector<Token> Lexer::tokenize(const std::string &input) {

    static std::vector<std::pair<std::regex, eTokenType>> tokenRegex = {
         {std::regex("\\bpush "),   eTokenType::t_push}
        ,{std::regex("\\bpop\\b"),     eTokenType::t_pop}
        ,{std::regex("\\bdump\\b"),    eTokenType::t_dump}
        ,{std::regex("\\bassert "), eTokenType::t_assert}
        ,{std::regex("\\badd\\b"),     eTokenType::t_add}
        ,{std::regex("\\bsub\\b"),     eTokenType::t_sub}
        ,{std::regex("\\bmul\\b"),     eTokenType::t_mul}
        ,{std::regex("\\bdiv\\b"),     eTokenType::t_div}
        ,{std::regex("\\bmod\\b"),     eTokenType::t_mod}
        ,{std::regex("\\bprint\\b"),   eTokenType::t_print}
        ,{std::regex("\\bexit\\b"),    eTokenType::t_exit}

        ,{std::regex("\\bint8\\b"),   eTokenType::t_int8}
        ,{std::regex("\\bint16\\b"),  eTokenType::t_int16}
        ,{std::regex("\\bint32\\b"),  eTokenType::t_int32}
        ,{std::regex("\\bfloat\\b"),  eTokenType::t_float}
        ,{std::regex("\\bdouble\\b"), eTokenType::t_double}

        ,{std::regex(R"(\((-?[0-9]+\.[0-9]+)\))"), eTokenType::t_z}
        ,{std::regex(R"(\((-?[0-9]+)\))"),         eTokenType::t_n}

        ,{std::regex(";.+"),  eTokenType::t_com}
        ,{std::regex("\\n"), eTokenType::t_sep}
        ,{std::regex("(.)"),  eTokenType::t_err} // must be last!
    };

    std::vector<Token> tokens;

    unsigned int line_number = 0;

    std::string match_on = input;
    while (match_on.length() != 0) {
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
            auto [tok, com, err] = checkSpelling(token);
            retTok  .insert(retTok  .end(), tok.begin(), tok.end());
            retErr  .insert(retErr  .end(), err.begin(), err.end());
            comments.insert(comments.end(), com.begin(), com.end());

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

std::tuple<std::vector<Token>, std::vector<Token>, std::vector<SyntaxError>>

    checkSpelling(Token token) {

    static const std::vector<std::pair<eTokenType, std::string>> tok = {
         {t_int8,   "int8"}
        ,{t_int16,  "int16"}
        ,{t_int32,  "int32"}
        ,{t_float,  "float"}
        ,{t_double, "double"}
        ,{t_push,   "push "}
        ,{t_pop,    "pop"}
        ,{t_dump,   "dump"}
        ,{t_assert, "assert "}
        ,{t_add,    "add"}
        ,{t_sub,    "sub"}
        ,{t_mul,    "mul"}
        ,{t_div,    "div"}
        ,{t_mod,    "mod"}
        ,{t_print,  "print"}
        ,{t_exit,   "exit"}
    };

    auto word        = token.data.value();
    auto line_number = token.line_number;

    std::vector<SyntaxError> retErr;
    std::vector<Token>       retTok;
    std::vector<Token>       retCom;

    bool found = false;

    for (auto &elem : tok) {
        // Implement levenshtien distance for much better matching!
        bool isMatch = word.find(elem.second) != std::string::npos;
        isMatch |=  word.find(elem.second.substr(1, elem.second.size()))
                                                        != std::string::npos;
        isMatch |=  word.find(elem.second.substr(0, elem.second.size() - 1))
                                                        != std::string::npos;
        if (isMatch) {
            retTok.push_back({elem.first, line_number});
            retErr.push_back({
                    line_number,
                    "Did you mean \"" + elem.second + "\"? <- <" + word + ">"
                    });
            found = true;
            break;
        }
    }

    if (!found) {
        retErr.push_back({
                line_number,
                "Unexpected token \"" + word  + "\""
                });

        retCom.push_back({
                t_com,
                line_number,
                "; \"" + word + "\""
                });
    }

    return {retTok, retCom, retErr};
}
