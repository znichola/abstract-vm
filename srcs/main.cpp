#include <iostream>
#include <fstream>
#include <iostream>

#include "avm.hpp"

std::string getStdInput() {
    std::string ret;
    std::string buff;
    while (std::getline(std::cin, buff)) {
        auto pos = buff.find(";;");
        if (pos == std::string::npos)
            ret += buff + "\n";
        else {
            ret += buff.substr(0, pos);
            break ;
        }
    }
    return ret;
}

std::string getFileInput(char *fileName) {
    std::ifstream file(fileName);
    if (!file) throw std::runtime_error("Error opening file");
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}


int main(int ac, char **av) {
    std::string input = ac < 2 ? getStdInput() : getFileInput(av[1]);

    auto tokens = Lexer::tokenize(input);
    auto [cleanedTokens, syntaxErrors] = Lexer::syntaxValidate(tokens);

    if (syntaxErrors.size() != 0) {
        std::cout << "Syntax Error/s :" << std::endl;
        auto print = [](const SyntaxError s) {
            std::cout << s << std::endl;
        };
        std::for_each(syntaxErrors.begin(), syntaxErrors.end(), print);

        std::cout << "..attempting to fix before continuing" << std::endl;
    }

    Runtime runtime;
    try {
        runtime = Parser::parse(cleanedTokens);
    } catch (std::exception &e) {
        std::cerr << "Parsing Error : " << e.what() << std::endl;
        return 1;
    }

    try {
        runtime.execute(std::cout);
    } catch (std::exception &e) {
        std::cerr << "Runtime Error : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
