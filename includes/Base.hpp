#ifndef BASE_HPP
# define BASE_HPP

# include <sstream>
# include <string>
# include <iostream>
# include <cstdint>
# include <functional>
# include <cmath>
# include <iomanip>

# include "IOperand.hpp"
# include "Factory.hpp"

template <typename T>
class Base: public IOperand {
private:
    std::string _value;
public:
// Default constructor
    Base() : _value("") {}

    Base(std::string v) : _value(v) {}

// Copy constructor
    Base(const Base &other) {
    *this = other;
    //_value = other._value;
}

// Destructor
    ~Base() {}

// Copy assignment operator
    Base &operator=(const Base &other) {
    _value = other._value;
	return *this;
}

// Methods
    eOperandType getType(void) const {
        if (typeid(T).name() == typeid(int8_t).name())
            return eOperandType::e_int8;
        if (typeid(T).name() == typeid(int16_t).name())
            return eOperandType::e_int16;
        if (typeid(T).name() == typeid(int32_t).name())
            return eOperandType::e_int32;
        if (typeid(T).name() == typeid(float).name())
            return eOperandType::e_Float;
        if (typeid(T).name() == typeid(double).name())
            return eOperandType::e_Double;
        return eOperandType::e_int8;
    }

    int getPrecision(void) const {
        return static_cast<int>(getType());
    }

    std::string const & toString(void) const {
        return _value;
    }

    T toValue(const std::string &s) const {
        if constexpr (std::is_same<T, int8_t>()) {
            std::int16_t v = 0;
            std::stringstream ss(s);
            ss >> v;

            if (ss.fail()) {} // TODO : add error handelling for parsing error
                              // std::cout << "string:" << s <<  " rest of string:" << s << " toValue: " << std::to_string(static_cast<std::int8_t>(v)) <<std::endl;
            return v;
        } else {
            T v = 0;
            std::stringstream ss(s);
            ss >> v;

            if (ss.fail()) {} // TODO : add error handelling for parsing error
            return v;
        }
    }

    // Operators

    IOperand const * apply(std::function<T(T, T)> fn, IOperand const &rhs) const {
        if (getPrecision() >= rhs.getPrecision()) {
            T res = fn(toValue(_value), toValue(rhs.toString()));

            if constexpr (std::is_same<T, int8_t>()) {
                return Factory().createOperand(getType(), std::to_string(static_cast<T>(res)));
            } else {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(1) << res;
                return Factory().createOperand(getType(), oss.str());
            }
        } else {
            IOperand const *tmp = Factory().createOperand(rhs.getType(), toString());
            // TODO: fix this error the toValue is wrong, it should use the 
            // more persise functions conversion, explain below.
            T res = fn(toValue(tmp->toString()), toValue(rhs.toString()));
            // TODO: above throws so it should be a leak of tmp
            delete tmp;

            if constexpr (std::is_same<T, int8_t>()) {
                return Factory().createOperand(rhs.getType(), std::to_string(static_cast<T>(res)));
            } else {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision(1) << res;
                return Factory().createOperand(rhs.getType(), oss.str());
            }

            //return Factory().createOperand(rhs.getType(), std::to_string(static_cast<T>(res)));
            // TODO : it's no longer recursive so the toValue call is with the wrong
            // type here, it should be with the tmp toValue, but ther stupid interface
            // does not allow for it. Might need to rethink this a bit.
        }
    }

    IOperand const * operator+( IOperand const &rhs ) const {
        return apply([](T a, T b) { return a + b; }, rhs);
    }

    IOperand const * operator-( IOperand const &rhs ) const {
        return apply([](T a, T b) { return a - b; }, rhs);
    }

    IOperand const * operator*( IOperand const &rhs ) const {
        return apply([](T a, T b) { return a * b; }, rhs);
    }

    IOperand const * operator/( IOperand const &rhs ) const {
        return apply([](T a, T b) { 
                if (b == 0) throw std::runtime_error("Div by zero");
                return a / b;
                }, rhs);
    }

    IOperand const * operator%( IOperand const &rhs ) const {
        if (getType() == eOperandType::e_Float
                || getType() == eOperandType::e_Double
                || rhs.getType() == eOperandType::e_Float
                || rhs.getType() == eOperandType::e_Double) {
            return apply([](T a, T b) {
                    if (b == 0) throw std::runtime_error("Mod by zero");
                    return a / b;
                    }, rhs);
        }
        return apply([](T a, T b) {
                if (b == 0) throw std::runtime_error("Mod by zero");
                return a / b;
                }, rhs);
    }
};


#endif /* BASE_HPP */
