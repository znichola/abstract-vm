#ifndef TOVALUE_HPP
# define TOVALUE_HPP

# include "eOperandType.hpp"

template <eOperandType T>
constexpr auto getZeroVal() {
    if constexpr (T == e_int8) {
        return std::int16_t{0}; // TODO hadle this case specially
    } else if constexpr (T == e_int16) {
        return std::int16_t{0};
    } else if constexpr (T == e_int32) {
        return std::int32_t{0};
    } else if constexpr (T == e_Float) {
        return float{0};
    } else {
        return double{0};
    }
}

template <eOperandType T>
auto toValue(const std::string &s) {
    std::stringstream ss(s);
    auto v = getZeroVal<T>();
    ss >> v;
    if (ss.fail()) {} // TODO : add error handelling for parsing error
    return v;
}


#endif /* TOVALUE_HPP */
