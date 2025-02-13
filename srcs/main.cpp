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

    auto *foo = Factory().createOperand(eOperandType::int8, "8");
    auto *bar = Factory().createOperand(eOperandType::int8, "12");
    auto *res = *foo + *bar;

    std::cout << foo->toString() << " + " << bar->toString() 
        << " = " << res->toString() << std::endl;

    auto *i = Factory().createOperand(eOperandType::int16, "16");

    auto *m = *bar + *i; // + *bar;

    std::cout << "and m : " << m->toString() << std::endl;
    std::cout << "and 16 : " << i->toString() << std::endl;

    auto *f = Factory().createOperand(eOperandType::Float, "8.1");
    auto *d = Factory().createOperand(eOperandType::Double, "9.3");
    auto *r = *d + *f;

    std::cout << "f:" << f->toString() << " d:" << d->toString() << " r:" << r->toString() << std::endl;
    

    delete r;
    delete f;
    delete d;

    delete m;
    delete i;
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
