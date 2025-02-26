#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "Stack.hpp"

//using Opr = const IOperand *;

// Default constructor
Stack::Stack() {}

// Copy constructor
Stack::Stack(const Stack &other) {
	*this = other;
}

// Destructor
Stack::~Stack() {
    auto remove = [](const IOperand *o) { delete o; };
    std::for_each(_stack.begin(), _stack.end(), remove);
}

// Copy assignment operator
Stack &Stack::operator=(const Stack &other) {
    _stack = other._stack;
	return *this;
}

bool Stack::wantToPop(void) const {
    if (_stack.size() > 0) return true;
    throw std::runtime_error("Can't pop empty stack");
}

void Stack::push(const IOperand * o) {
    _stack.push_back(o);
}

const IOperand * Stack::pop(void) {
    wantToPop();
    auto ret = _stack.back();
    _stack.pop_back();
    return ret;
}

void Stack::dump(void) const {
    auto print = [](const IOperand *o) {
        std::cout << "" << o->toString() << std::endl;
    };
    std::for_each(_stack.rbegin(), _stack.rend(), print);
}

void Stack::assert(Opr o) const {
    wantToPop();
    if (_stack.back()->toString() != o->toString())
        throw std::runtime_error("Assert failed");
}

void Stack::print(void) const {
    wantToPop();
    Opr o = _stack.back();
    if (o->getType() != eOperandType::e_int8)
        throw std::runtime_error("Not a Char");
    char c = '#';
    std::stringstream ss(o->toString());
    ss >> c;
    std::cout << c << std::endl;
}

void Stack::apply(std::function<Opr(Opr, Opr)> fn) {
    wantToPop();
    auto lhs = pop();
    wantToPop(); // if fails should handle a return of the first poped valeu
    auto rhs = pop();
    Opr res = fn(lhs, rhs);
    delete rhs;
    delete lhs;
    push(res);
}

void Stack::add(void) {
    apply([](Opr a, Opr b) { return *a + *b; });
}

void Stack::sub(void) {
    apply([](Opr a, Opr b) { return *a - *b; });
}

void Stack::mul(void) {
    apply([](Opr a, Opr b) { return *a * *b; });
}

void Stack::div(void) {
    apply([](Opr a, Opr b) { return *a / *b; });
}

void Stack::mod(void) {
    apply([](Opr a, Opr b) { return *a % *b; });
}

void Stack::exit(void) const {
    //std::cout << "EXIT" << std::endl;
    // TODO : implement the post instruction checking
}

