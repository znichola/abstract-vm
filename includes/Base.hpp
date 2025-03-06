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
//# include "toValue.hpp"

template <typename T>
class Base: public IOperand {
private:
    std::string _value;
public:
// Default constructor
    Base() : _value("") {}

    Base(std::string v) {
        if (v == "") return ; //TODO test removing this to see if tests break
        if constexpr (std::is_same<T, float>() || std::is_same<T, double>()) {
            double tmp;
            std::stringstream ss(v);
            ss >> tmp;
            if (ss.fail())
                throw std::runtime_error(
                        "Failed string to value converstion <" + v + ">");
            if (tmp < std::numeric_limits<T>::lowest()) {
                std::stringstream ss2;
                ss2 << "Underflow value "
                    << std::numeric_limits<T>::lowest();
                throw std::runtime_error(ss2.str());
            }
            if (tmp > std::numeric_limits<T>::max()) {
                std::stringstream ss2;
                ss2 << "Overflow value "
                    << std::numeric_limits<T>::lowest();
                throw std::runtime_error(ss2.str());
            }
            _value = ss.str();
            if (_value.find(".") == std::string::npos) _value += ".0";
        } else {
            long long tmp;
            std::stringstream ss(v);
            ss >> tmp;
            if (ss.fail())
                throw std::runtime_error(
                        "Failed string to value converstion <" + v + ">");
            if (tmp < std::numeric_limits<T>::lowest()) {
                std::stringstream ss2;
                ss2 << "Underflow value "
                    << std::numeric_limits<T>::lowest();
                throw std::runtime_error(ss2.str());
            }
            if (tmp > std::numeric_limits<T>::max()) {
                std::stringstream ss2;
                std::cout << std::numeric_limits<T>::lowest() << "FAAAA\n";
                std::cout << INT8_MIN << "FAAAA\n";
                std::cout << std::numeric_limits<T>::max() << "FAAAA\n";
                ss2 << "Overflow value "
                    << std::numeric_limits<T>::max();
                throw std::runtime_error(ss2.str());
            }
            _value = ss.str();
        }
        // TODO : this should throw after createing if it's an overflow value!
    }

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

            if (ss.fail())
                throw std::runtime_error("Error parsing value");
            return v;
        } else {
            T v = 0;
            std::stringstream ss(s);
            ss >> v;

            if (ss.fail())
                throw std::runtime_error("Error parsing value");
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
                oss << res;
                return Factory().createOperand(getType(), oss.str());
            }
        } else {
            throw std::runtime_error("Presision upscale error");
        }
    }

    IOperand const * operator+( IOperand const &rhs ) const {
        if (getPrecision() < rhs.getPrecision()) {
            std::unique_ptr<IOperand const> tmp(Factory().createOperand(rhs.getType(), toString()));
            return *tmp + rhs;
        }
        return apply([](T a, T b) { return a + b; }, rhs);
    }

    IOperand const * operator-( IOperand const &rhs ) const {
        if (getPrecision() < rhs.getPrecision()) {
            std::unique_ptr<IOperand const> tmp(Factory().createOperand(rhs.getType(), toString()));
            return *tmp - rhs;
        }
        return apply([](T a, T b) { return a - b; }, rhs);
    }

    IOperand const * operator*( IOperand const &rhs ) const {
        if (getPrecision() < rhs.getPrecision()) {
            std::unique_ptr<IOperand const> tmp(Factory().createOperand(rhs.getType(), toString()));
            return *tmp * rhs;
        }
        return apply([](T a, T b) { return a * b; }, rhs);
    }

    IOperand const * operator/( IOperand const &rhs ) const {
        if (getPrecision() < rhs.getPrecision()) {
            std::unique_ptr<IOperand const> tmp(Factory().createOperand(rhs.getType(), toString()));
            return *tmp / rhs;
        }
        return apply([](T a, T b) { 
                if (b == 0) throw std::runtime_error("Div by zero");
                return a / b;
                }, rhs);
    }

    IOperand const * operator%( IOperand const &rhs ) const {
        if (getPrecision() < rhs.getPrecision()) {
            std::unique_ptr<IOperand const> tmp(Factory().createOperand(rhs.getType(), toString()));
            return *tmp % rhs;
        }
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
