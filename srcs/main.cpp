#include <iostream>
#include <fstream>
#include <iostream>

#include "avm.hpp"

void readData(std::istream& in) {
    while (!in.eof()) {
        std::string line;
        std::getline(in, line);
        std::cout << "read line: \"" << line << "\"" << std::endl;
    }
}

int main(int ac, char **av) {
    (void)av;

    auto *foo = Factory().createOperand(eOperandType::int8, "12");
    auto *bar = Factory().createOperand(eOperandType::int8, "12");
    auto *res = *foo + *bar;

    std::cout << foo->toString() << " + " << bar->toString() 
        << " = " << res->toString() << std::endl;

    delete foo;
    delete bar;
    delete res;


    return 0;

    if (ac < 2) {
        readData(std::cin); 
    } else {
        std::ifstream file(av[1]);
        if (file.is_open()) {
            readData(file);
            file.close();
        } else {
            std::cout << "faile to open file" << std::endl;
        } 
    }
    std::cout << "bye!" << std::endl;
    return 0;
}
