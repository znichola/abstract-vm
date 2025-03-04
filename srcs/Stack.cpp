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
   return _stack.size() > 0;
}

void Stack::wantToPopThrow(void) const {
    if (wantToPop()) return;
    throw std::runtime_error("Can't pop empty stack");
}

void Stack::push(const IOperand * o) {
    _stack.push_back(o);
}

const IOperand * Stack::pop(void) {
    wantToPopThrow();
    auto ret = _stack.back();
    _stack.pop_back();
    return ret;
}

std::string Stack::dump(void) const {
    std::stringstream ss;

    auto print = [&](const IOperand *o) {
        ss << "" << o->toString() << std::endl;
    };
    std::for_each(_stack.rbegin(), _stack.rend(), print);
    return ss.str();
}

void Stack::assert(Opr o) const {
    wantToPopThrow();
    if (_stack.back()->toString() != o->toString())
        throw std::runtime_error("Assert failed");
}

std::string Stack::print(void) const {
    wantToPopThrow();
    Opr o = _stack.back();
    if (o->getType() != eOperandType::e_int8)
        throw std::runtime_error("Not a Char");
    char c = '#';
    std::stringstream ss(o->toString());
    ss >> c;
    return std::string(1, c) + "\n";
}

void Stack::apply(std::function<Opr(Opr, Opr)> fn) {
    wantToPopThrow();
    auto lhs = pop();
    if (!wantToPop()) {
        delete lhs;
        wantToPopThrow();
    }
    auto rhs = pop();
    try {
        Opr res = fn(lhs, rhs);
        delete rhs;
        delete lhs;
        push(res);
    } catch (std::exception &e) {
        delete rhs;
        delete lhs;
        throw;
    }
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
    // TODO : implement the post instruction checking
}

