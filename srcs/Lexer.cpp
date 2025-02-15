#include <map>
#include <regex>
#include <utility>
#include <iostream>

#include "Lexer.hpp"

// Default constructor
Lexer::Lexer() {
}

// Copy constructor
Lexer::Lexer(const Lexer &other) {
	*this = other;
}

// Destructor
Lexer::~Lexer() {
}

// Copy assignment operator
Lexer &Lexer::operator=(const Lexer &other) {
	(void)other;
	// TODO: insert return statement here
	return *this;
}

std::vector<Token> Lexer::tokenize(const std::string &line) const {

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

        ,{std::regex(R"(int8\((-?[0-9]+)\))"),  eTokenType::t_int8}
        ,{std::regex(R"(int16\((-?[0-9]+)\))"), eTokenType::t_int16}
        ,{std::regex(R"(int32\((-?[0-9]+)\))"), eTokenType::t_int32}
        ,{std::regex(R"(float\((-?[0-9]+\.[0-9]+)\))"),  eTokenType::t_float}
        ,{std::regex(R"(double\((-?[0-9]+\.[0-9]+)\))"), eTokenType::t_double}

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
                if (match.size() == 1) {
                    tokens.push_back({type});
                } else {
                    tokens.push_back({type, std::string(match[1])});
                }
                match_on = match.suffix(); // must be last! all match indexs ref to this
                break;
            }
        }
    }
    return tokens;
}

