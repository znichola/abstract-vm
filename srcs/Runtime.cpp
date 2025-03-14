#include <sstream>

#include "Runtime.hpp"
#include "Factory.hpp"

// Default constructor
Runtime::Runtime() {}

// Copy constructor
Runtime::Runtime(const Runtime &other) : Stack(other) {
    *this = other;
}

// Destructor
Runtime::~Runtime() {
    auto remove = [](Instruction i) {
        if (i.arg != nullptr)
            delete i.arg;
    };
    std::for_each(_byteCode.begin(), _byteCode.end(), remove);
}

// Copy assignment operator
Runtime &Runtime::operator=(const Runtime &other) {
    for (const auto & i : other._byteCode) {
        auto copy = i;
        if (copy.arg) {
            copy.arg = Factory().dup(copy.arg);
        }
        _byteCode.push_back(copy);
    }
    return *this;
}

void Runtime::push_back(Instruction instruction) {
    _byteCode.push_back(instruction);
}

const std::vector<Instruction> & Runtime::getByteCode(void) const {
    return _byteCode;
}

std::string genErr(const Instruction & inst, const std::string & msg);

void Runtime::execute(std::ostream &os) {
    bool exitRun = false;
    while (!_byteCode.empty()) {
        auto inst = _byteCode.front();

        if (exitRun)
            throw std::runtime_error(
                    genErr(inst, "Cannot have instructions after exit"));

        if (_logger)
            os << "EXECUTING " << inst << std::endl;
        try {
            switch (inst.type) {
                case (u_push) :
                    push(Factory().dup(inst.arg));
                    //inst.arg = nullptr;
                    break;
                case (u_assert) :
                    assert(Factory().dup(inst.arg));
                    //inst.arg = nullptr;
                    break;
                case (n_pop) :
                    delete pop();
                    break;
                case (n_dump) :
                    os << dump();
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
                    os << print();
                    break;
                case (n_exit) :
                    exit();
                    exitRun = true;
            }
        } catch (std::exception & e) {
            throw std::runtime_error(genErr(inst, e.what()));
        }
        if (inst.arg != nullptr)
            delete inst.arg;
        _byteCode.erase(_byteCode.begin());
    }

    if (exitRun == false)
        throw std::runtime_error("Exit must be called before program end");

    if (_logger)
        os << "END EXECUTION" << std::endl;
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

std::string genErr(const Instruction & inst, const std::string & msg) {
    std::stringstream ss;
    ss << "Line " << inst.line_number << " | " << msg;
    return ss.str();
}

