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

// Destructor
	~Runtime();

// Copy assignment operator
	Runtime & operator=(const Runtime &other);

// Methods

    void addInstruction(Instruction instruction);

    void execute();

    const std::vector<Instruction> & getByteCode(void) const;

private:
    std::vector<Instruction> _byteCode;

};

std::ostream &operator<<(std::ostream &os, const Runtime& runtime);

#endif /* RUNTIME_HPP */
