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
        ,{std::regex("\\n+"),    eTokenType::t_sep}

        ,{std::regex("."),       eTokenType::t_err}
    };

    std::vector<Token>tokens({});

    std::string match_on = line;
    while (match_on.length() != 0) {
        std::cout << "MATCHING: \"" << match_on << "\"" << std::endl;
        for (const auto &[regex, type] : tokenRegex) {
            std::smatch match;
            if (std::regex_search(match_on, match, regex, std::regex_constants::match_continuous)) {
                std::cout << "Match size: " << match.size() << " : ";
                for (std::size_t i = 0; i < match.size(); i++) {
                    std::cout << match[i] << " ";
                }
                std::cout << std::endl;
                match_on = match.suffix();
                tokens.push_back({type});
                break;
            }
        }
        //std::cout << "match_on: " << match_on << std::endl;
    }

    (void)line;
    return tokens;
}

