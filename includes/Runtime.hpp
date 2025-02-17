#ifndef RUNTIME_HPP
# define RUNTIME_HPP

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

private:
    std::vector<Instruction> _byteCode;

};

#endif /* RUNTIME_HPP */
