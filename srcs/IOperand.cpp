#include "IOperand.hpp"


std::ostream &operator<<(std::ostream &os, const IOperand *op) {
    os << op->toString();
    return os;
}
