#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "Stack.hpp"
#include "Factory.hpp"

//using Opr = const IOperand *;

// Default constructor
Stack::Stack() {}

// Copy constructor
Stack::Stack(const Stack &other) {
    *this = other;
}

// Move constuctor
Stack::Stack(Stack &&other) noexcept : _stack(std::move(other._stack)) {}

// Destructor
Stack::~Stack() {
    auto remove = [](const IOperand *o) { delete o; };
    std::for_each(_stack.begin(), _stack.end(), remove);
}

// Copy assignment operator
Stack &Stack::operator=(const Stack &other) {
    if (this != &other) {
        for (const auto & o : other._stack) {
            _stack.push_back(Factory().dup(o));
        }
    }
    return *this;
}

// Move assignment operator
Stack &Stack::operator=(Stack &&other) noexcept {
    if (this != &other) {
        _stack = std::move(other._stack);
    }
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
    if (_stack.back()->toString() != o->toString()
          || _stack.back()->getType() != o->getType()) {
        std::stringstream ss;
        ss << toTypeString(_stack.back())
           << " != "
           << toTypeString(o);
        delete o;
        throw std::runtime_error("Assert failed " + ss.str());
    }
    delete o;
}

std::string Stack::print(void) const {
    wantToPopThrow();
    Opr o = _stack.back();
    if (o->getType() != eOperandType::e_int8)
        throw std::runtime_error("Not a Char");
    int c = 0;
    std::stringstream ss(o->toString());
    ss >> c;
    std::stringstream ss2;
    ss2 << static_cast<char>(c);
    return ss2.str() + "\n";
}

void Stack::apply(std::function<Opr(Opr, Opr)> fn) {
    wantToPopThrow();
    auto rhs = pop();
    if (!wantToPop()) {
        delete rhs;
        wantToPopThrow();
    }
    auto lhs = pop();
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

