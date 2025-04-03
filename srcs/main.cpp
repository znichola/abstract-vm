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
    if (!file) throw std::runtime_error("Cannot open file \"" 
            + std::string(fileName) + "\"");
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::tuple<bool, bool, bool, char *> parseInput(int ac, char **av) {
    bool isFix    = false;
    bool isHelp   = false;
    bool isStrict = false;
    char * file   = nullptr;

    for (int i = 1; i < ac; i++) {
        std::string s(av[i]);
        if (s == "--help" || s == "-h")
            isHelp = true;
        else if (s == "--fix" || s == "-f")
            isFix = true;
        else if (s == "--strict" || s == "-s")
            isStrict = true;
        else
            file = av[i];
    }
    return {isFix, isHelp, isStrict, file};
}

int main(int ac, char **av) {

    auto [isFix, isHelp, isStrict, file] = parseInput(ac, av);

    if (isHelp) {
        std::cout << "abstract virtual machine\nrun with " << av[0]
        << "\n   -h / --help   to see this message"
        << "\n   -f / --fix    to output the spelling and syntax fixer result"
        << "\n   -s / --strict does not tolerate any syntax or spelling errors"
        << std::endl;
        return 0;
    }

    std::string input;

    try {
        input = file == nullptr ? getStdInput() : getFileInput(file);
    } catch (std::exception &e) {
        std::cerr << "Startup error | " << e.what() << std::endl;
        return 1;
    }

    auto tokens = Lexer::tokenize(input);
    auto [correctedToken, spellingErrors] = Lexer::fixSpellings(tokens);
    auto [filteredTokens, errorTokens] = Lexer::dropErrorTokens(correctedToken);
    auto [cleanedTokens, syntaxErrors] = Lexer::syntaxValidate(filteredTokens);

    if (isFix) {
        auto print = [](const Token &t) {
            if (t.type == t_sep)
                std::cout << std::endl;
            else if (t.type == t_push || t.type == t_assert)
                std::cout << t << " ";
            else if (t.type == t_n || t.type == t_z)
                std::cout << "(" << t.data.value() << ")";
            else
                std::cout << t;
        };
        std::for_each(cleanedTokens.begin(), cleanedTokens.end(), print);
        return 0;
    }

    if (spellingErrors.size() != 0) {
        std::cerr << "Spelling Error/s :" << std::endl;
        auto print = [](const SyntaxError s) {
            std::cerr << s << std::endl;
        };
        std::for_each(spellingErrors.begin(), spellingErrors.end(), print);

        if (isStrict) return 1;
        std::cerr << "..attempting to fix before continuing" << std::endl;
    }

    if (syntaxErrors.size() != 0 || errorTokens.size() != 0) {
        std::cerr << "Syntax Error/s :" << std::endl;
        auto print = [](const SyntaxError s) {
            std::cerr << s << std::endl;
        };
        std::for_each(errorTokens.begin(), errorTokens.end(), print);
        std::for_each(syntaxErrors.begin(), syntaxErrors.end(), print);

        if (isStrict) return 1;
        std::cerr << "..attempting to fix before continuing" << std::endl;
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
