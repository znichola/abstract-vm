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
    auto s      = Lexer::syntaxValidate(tokens);
    auto syntaxErrors  = s.second;
    auto cleanedTokens = s.first;

    auto runtime = Parser::parse(cleanedTokens);

    runtime.execute();

    if (syntaxErrors.size() != 0) {
        std::cout << "Syntax errors found:" << std::endl
                  << syntaxErrors           << std::endl
                  << "attempting to fix before continuing" << std::endl;
    }


    return 0;
}
