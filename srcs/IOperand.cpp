#include "IOperand.hpp"


std::ostream &operator<<(std::ostream &os, const IOperand *op) {
    os << op->toString();
    return os;
}

std::string toTypeString(const IOperand *op) {
    auto str = op->toString();
    switch (op->getType()) {
        case (e_int8):   return   "int8(" + str + ")";
        case (e_int16):  return  "int16(" + str + ")";
        case (e_int32):  return  "int32(" + str + ")";
        case (e_Float):  return  "float(" + str + ")";
        case (e_Double): return "double(" + str + ")";
    }
    return "UNKNOWN TYPE";
}
