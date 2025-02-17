
#ifndef RUNTIME_HPP
# define RUNTIME_HPP

class Runtime
{
private:

public:
// Default constructor
	Runtime();

// Copy constructor
	Runtime(const Runtime &other);

// Destructor
	~Runtime();

// Copy assignment operator
	Runtime & operator=(const Runtime &other);
};

#endif /* RUNTIME_HPP */
