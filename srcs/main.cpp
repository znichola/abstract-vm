#include <iostream>
#include <fstream>

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
