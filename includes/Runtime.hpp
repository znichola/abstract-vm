#ifndef RUNTIME_HPP
# define RUNTIME_HPP

# include <iostream>

# include "Stack.hpp"
# include "Instruction.hpp"

class Runtime : public Stack {
public:
// Default constructor
	Runtime();

// Copy constructor
	Runtime(const Runtime &other);

// Move constructor
    Runtime(Runtime &&other) noexcept;

// Destructor
	~Runtime();

// Copy assignment operator
	Runtime & operator=(const Runtime &other);

// Move assignment operator
    Runtime &operator=(Runtime &&other) noexcept;

// Methods

    void push_back(Instruction instruction);

    void execute(std::ostream &os);

    const std::vector<Instruction> & getByteCode(void) const;

private:
    std::vector<Instruction> _byteCode;
    bool _logger = false;
};

std::ostream &operator<<(std::ostream &os, const Runtime& runtime);

#endif /* RUNTIME_HPP */
