
#ifndef INSTRUCTION_HPP
# define INSTRUCTION_HPP

class Instruction
{
public:
    virtual void execute(Stack &stack) = 0;
};

#endif /* INSTRUCTION_HPP */
