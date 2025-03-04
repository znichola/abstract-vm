#ifndef STACK_HPP
# define STACK_HPP

# include <vector>
# include <functional>

# include "IOperand.hpp"

class Stack
{
private:
    using Opr = const IOperand *;
    std::vector<Opr> _stack;

    bool wantToPop() const;
    void wantToPopThrow() const;
    void apply(std::function<Opr(Opr, Opr)> fn);

public:
// Default constructor
    Stack();

// Copy constructor
    Stack(const Stack &other);

// Destructor
    ~Stack();

// Copy assignment operator
    Stack & operator=(const Stack &other);

// Methods

    void push(Opr o);
    Opr  pop(void);

    std::string dump(void) const;
    std::string print(void) const;

    void assert(Opr o) const;

    void add(void);
    void sub(void);
    void mul(void);
    void div(void);
    void mod(void);


    void exit(void) const;

};

#endif /* STACK_HPP */
