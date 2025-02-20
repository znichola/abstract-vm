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

    auto tokens = Lexer().tokenize("push int8(12)\npush int8(12)\nadd"); 
    std::cout << "TOKENS: " << tokens << std::endl;

    auto *k = Factory().createOperand(eOperandType::e_Float, "8.1");
    (void)k;

    auto runtime = Parser::parse(tokens);

    std::cout << runtime << std::endl;

    runtime.execute();

    // Lexer().tokenize("push int8(123)\n pull\n pop exit print me baby");
    auto ret = Lexer::tokenize("GG\npush float(2.1)\npush int32(9)\ndump\npop\npush int8(123)\n");

    std::cout << "Match tokens: " << ret <<std::endl;

    std::cout << "END TEST LEXER" << std::endl;

    auto *foo = Factory().createOperand(eOperandType::e_int8, "8");
    auto *bar = Factory().createOperand(eOperandType::e_int8, "12");
    auto *res = *foo + *bar;

    std::cout << foo->toString() << " + " << bar->toString() 
        << " = " << res->toString() << std::endl;

    auto *i = Factory().createOperand(eOperandType::e_int16, "16");

    auto *m = *bar + *i; // + *bar;

    std::cout << "and m : " << m->toString() << std::endl;
    std::cout << "and 16 : " << i->toString() << std::endl;

    auto *f = Factory().createOperand(eOperandType::e_Float, "8.1");
    auto *d = Factory().createOperand(eOperandType::e_Double, "9.3");
    auto *r = *d + *f;

    std::cout << "f:" << f->toString() << " d:" << d->toString() << " r:" << r->toString() << std::endl;

    Stack stack = Stack();

    stack.push(foo);
    stack.push(bar);

    stack.dump();
    
    stack.add();

    stack.dump();

    stack.exit();

    auto bleh = stack.pop();
    std::cout << "bleh " << bleh->toString() << std::endl;
    delete bleh;

    delete r;
    delete f;
    delete d;

    delete m;
    delete i;
//    delete foo;
//    delete bar;
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
