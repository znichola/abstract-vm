#include <string>
#include <iostream>
#include <iomanip>

#include "avm.hpp"

using std::cout;
using std::endl;

bool expect(bool res);

void test_lexer();


int main(void) {
    test_lexer();
}

void compare_tokenizer(const std::string &expected, const std::string &input) {
    auto tokens = Lexer::tokenize(input);

    std::ostringstream oss;
    oss << tokens;
    auto actual = oss.str();

    if (expect(actual == expected)) {
        cout << "Expected: " << expected << endl;
        cout << "  Actual: " << actual   << endl;
    }
}


void test_lexer() {
    cout << "Testing the Lexer" << endl;

    compare_tokenizer("[sep, push, int8(123), sep]", "\n\npush int8(123)\n\n");
    compare_tokenizer("[push, int16(123), sep, push, int32(32)]", "push int16(123)\npush int32(32)");
}

bool expect(bool res) {
    static int test_num = 0;

//    if (reset) {
//        test_num = 0;
//        return res;
//    }

    cout << std::setw(2) << test_num
         << ". " << (res ? "OK" : "KO") << endl;

    test_num++;
    return !res;
}

