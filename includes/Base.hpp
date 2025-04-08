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
        std::stringstream sserr;
        std::stringstream ss(v);
        if constexpr (std::is_same<T, float>() || std::is_same<T, double>()) {
            double tmp;
            ss >> tmp;
            if (ss.fail())
                throw std::runtime_error(
                        "Failed string to value converstion <" + v + ">");
            if (tmp < std::numeric_limits<T>::lowest()) {
                sserr << "Underflow value " << std::numeric_limits<T>::lowest();
                throw std::runtime_error(sserr.str());
            }
            if (tmp > std::numeric_limits<T>::max()) {
                sserr << "Overflow value " << std::numeric_limits<T>::max();
                throw std::runtime_error(sserr.str());
            }
            std::stringstream ss2;
            ss2 << std::fixed << std::setprecision(10) << tmp;
            auto t = ss2.str();
            // std::cout << "HERE DOUBLE FLOAT :" << v << ": and : " << t << ":\n";
            auto tpos = t.find_last_not_of("0");
            if (t[tpos] == '.') t.erase(tpos + 2, std::string::npos);
            else t.erase(tpos + 1, std::string::npos);
            // std::cout << "    POST DELETE T :" << v << ": and : " << t << ":\n";
            _value = t;
        } else {
            long long tmp;
            ss >> tmp;
            if (ss.fail())
                throw std::runtime_error(
                        "Failed string to value converstion <" + v + ">");
            if constexpr (std::is_same<T, int8_t>()) {
                if (tmp < INT8_MIN) {
                    sserr << "Underflow value " << INT8_MIN;
                    throw std::runtime_error(sserr.str());
                }
                if (tmp > INT8_MAX) {
                    sserr << "Overflow value " << INT8_MAX;
                    throw std::runtime_error(sserr.str());
                }
            } else {
                if (tmp < std::numeric_limits<T>::lowest()) {
                    sserr << "Underflow value " << std::numeric_limits<T>::lowest();
                    throw std::runtime_error(sserr.str());
                }
                if (tmp > std::numeric_limits<T>::max()) {
                    sserr << "Overflow value " << std::numeric_limits<T>::max();
                    throw std::runtime_error(sserr.str());
                }
            }
            std::stringstream ss2;
            ss2 << tmp;
            _value = ss2.str();
        }
    }

// Copy constructor
    Base(const Base &other) {
        *this = other;
    }


// Move constructor
    Base(const Base &&other) {
        _value = std::move(other._value);
    }


// Destructor
    ~Base() {}

// Copy assignment operator
    Base &operator=(const Base &other) {
        _value = other._value;
        return *this;
    }

// Move assignment operator
    Base &operator=(Base &&other) noexcept {
        if (this != &other) {
            _value = std::move(other._value);
        }
        return *this;
    }


// Methods
    eOperandType getType(void) const {
        if constexpr (std::is_same<T, int8_t>())
            return eOperandType::e_int8;
        else if constexpr (std::is_same<T, int16_t>())
            return eOperandType::e_int16;
        else if constexpr (std::is_same<T, int32_t>())
            return eOperandType::e_int32;
        else if constexpr (std::is_same<T, float>())
            return eOperandType::e_Float;
        else if constexpr (std::is_same<T, double>())
            return eOperandType::e_Double;
        else {
            // The expression is type dependant, so the compoiler will
            // evaluate it once it has the type!
            static_assert(sizeof(T) != sizeof(T), "T not supported");
        }
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
                oss << std::setprecision(10);
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
