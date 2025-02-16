#ifndef SYNTAXERROR_HPP
# define SYNTAXERROR_HPP

# include <string>
# include <ostream>
# include <vector>

struct SyntaxError {
    unsigned int line_number;
    std::string message;
};

std::ostream &operator<<(std::ostream &os, const SyntaxError& syntaxError);
std::ostream &operator<<(std::ostream &os, const std::vector<SyntaxError>& syntaxErrors);

#endif /* SYNTAXERROR_HPP */
