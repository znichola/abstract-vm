#include "SyntaxError.hpp"

std::ostream &operator<<(std::ostream &os, const SyntaxError& syntaxError) {
    os << "Line " << syntaxError.line_number << " | "
       << syntaxError.message;
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<SyntaxError>& syntaxErrors) {
    os << "[";
    bool first = true;
    for (const auto &syntaxError : syntaxErrors) {
        if (!first) os << ", ";
        os << syntaxError;
        first = false;
    }
    os << "]";
    return os;
}
