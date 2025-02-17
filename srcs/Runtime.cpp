#include "Runtime.hpp"

// Default constructor
Runtime::Runtime() {}

// Copy constructor
Runtime::Runtime(const Runtime &other) : Stack(other) {
	*this = other;
}

// Destructor
Runtime::~Runtime() {}

// Copy assignment operator
Runtime &Runtime::operator=(const Runtime &other)
{
	(void)other;
	// TODO: insert return statement here
	return *this;
}

void Runtime::addInstruction(Instruction instruction) {
    _byteCode.push_back(instruction);
}

const std::vector<Instruction> & Runtime::getByteCode(void) const {
    return _byteCode;
}

void Runtime::execute() {
    while (!_byteCode.empty()) {
        auto inst = _byteCode.front();

        // TODO : handel error!
        switch (inst.type) {
            case (u_push) :
                push(inst.arg);
                break;
            case (u_assert) :
                assert(inst.arg);
                break;
            case (n_pop) :
                pop();
                break;
            case (n_dump) :
                dump();
                break;
            case (n_add) :
                add();
                break;
            case (n_sub) :
                sub();
                break;
            case (n_mul) :
                mul();
                break;
            case (n_div) :
                div();
                break;
            case (n_mod) :
                mod();
                break;
            case (n_print) :
                print();
                break;
            case (n_exit) :
                exit();
                break;
        }
    }
}

void execute() {

}

std::ostream &operator<<(std::ostream &os, const Runtime& runtime) {
    os << "[";
    bool first = true;
    auto instructions = runtime.getByteCode();
    for (const auto &instruction : instructions) {
        if (!first) os << ", ";
        os << instruction;
        first = false;
    }
    os << "]";
    return os;
}
