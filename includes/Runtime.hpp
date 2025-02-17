#ifndef RUNTIME_HPP
# define RUNTIME_HPP

# include "Stack.hpp"

class Runtime : public Stack {

public:
// Constructs
    class IInstruction {
    public:
        virtual void execute(Stack &stack) = 0;
    };

    class NullaryInst : public IInstruction {
    public:
        using func_ptr = void(*)(Stack&);

        NullaryInst(func_ptr fn) : _action(fn) {}

        void execute(Stack &stack) override {
            _action(stack);
        }

    private:
        func_ptr _action;
    };

    class UnaryInst : public IInstruction {
    public:
        using func_ptr = void(*)(Stack&, const IOperand *);

        UnaryInst(func_ptr fn, const IOperand * arg) : _action(fn), _arg(arg) {}

        void execute(Stack &stack) override {
            _action(stack, _arg);
        }

    private:
        func_ptr _action;
        const IOperand * _arg;
    };


// Default constructor
	Runtime();

// Copy constructor
	Runtime(const Runtime &other);

// Destructor
	~Runtime();

// Copy assignment operator
	Runtime & operator=(const Runtime &other);

// Methods

    void addNullaryInst(NullaryInst::func_ptr fn);

    void addUnaryInst(UnaryInst::func_ptr fn, const IOperand * arg);

    void execute();

private:
    std::vector<IInstruction*> _byteCode;

};

#endif /* RUNTIME_HPP */
