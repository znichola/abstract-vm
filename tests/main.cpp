#include <string>
#include <iostream>
#include <iomanip>

#include "avm.hpp"

using std::cout;
using std::endl;

static int test_num = 0;
static int total_num = 0;
static int test_failed = 0;
static int total_failed = 0;

bool expect(bool res);
void record_score();
void test_lexer_tokenizer();
void test_lexer_syntax();
void test_parser();

int main(void) {
    test_lexer_tokenizer();
    test_lexer_syntax();
//    test_parser();

    cout << endl << (total_failed == 0 ? "PASSED" : "FAILED")
         << " : " << total_num - total_failed << "/" << total_num
         << endl;
}

///////////////////////////////////////////////////////////////////////////////

void compare_parser(const std::string &expected, const std::string &input) {
    auto tokens = Lexer::tokenize(input);
    auto runtime = Parser::parse(tokens);

    std::ostringstream oss;
    oss << runtime;
    auto actual = oss.str();

    if (expect(actual == expected)) {
        cout << "Expected: " << expected << endl;
        cout << "  Actual: " << actual   << endl;
        cout << "  Tokens: " << tokens   << endl;
    }

}

void test_parser() {
    cout << "Testing the Parser" << endl;

    compare_parser("[]", "push int8(42)");

    cout << "Parser tests complete. "
         << test_num - test_failed << "/" << test_num << endl;
    record_score();
}



void compare_syntaxchecker(const std::string &expectedErrors,
        const std::string &expectedTokens, const std::string &input) {

    auto tokens = Lexer::tokenize(input);
    auto ret    = Lexer::syntaxValidate(tokens);
    auto syntaxErrors  = ret.second;
    auto cleanedTokens = ret.first;

    std::ostringstream oss;
    oss << syntaxErrors;
    auto actualErrors = oss.str();

    std::ostringstream osss;
    osss << cleanedTokens;
    auto actualTokens = osss.str();

    if (expect(actualErrors == expectedErrors)) {
        cout << "   InputTokens: " << tokens         << endl;
        cout << "ExpectedErrors: " << expectedErrors << endl;
        cout << "  ActualErrors: " << actualErrors   << endl;
    }

    if (expect(actualTokens == expectedTokens)) {
        cout << "   InputTokens: " << tokens         << endl;
        cout << "ExpectedTokens: " << expectedTokens << endl;
        cout << "  ActualTokens: " << actualTokens   << endl;
    }
}

void test_lexer_syntax() {
    cout << "Testing the Syntax checker" << endl;

    compare_syntaxchecker("[]","[push, int8, N(12)]", "push int8(12)");
    compare_syntaxchecker("[Line 1 | Unexpected token \"bzz\", Line 2 | Unexpected token \" \", Line 3 | Unexpected token \"foo\"]"
            ,"[pop, sep, com(; \"bzz\"), sep, div, com(; \" \"), sep, com(; \"foo\")]"
            ,"pop\nbzz\ndiv \nfoo");
    compare_syntaxchecker("[Line 0 | Unexpected token \" \", Line 0 | Only one operation per line, move \"div\"]"
            ,"[add, com(; \" \"), sep, div]"
            ,"add div");
    compare_syntaxchecker("[Line 0 | Unexpected token \" \", Line 0 | Only one operation per line, move \"assert\"]"
            ,"[push, int8, N(2), com(; \" \"), sep, assert, int8, N(0)]"
            ,"push int8(2) assert int8(0)");
    compare_syntaxchecker("[Line 0 | Incomplete value with \"push\", Line 0 | Only one operation per line, move \"pop\"]"
            ,"[push, com(; \" \"), sep, pop]"
            ,"push pop");
    compare_syntaxchecker("[Line 0 | Some sort of error]"
            ,"[com(; \"int8(16)\")]"
            ,"int8(16)"); // Maybe moved to parsing errors?

    cout << "Lexer syntax tests complete. "
         << test_num - test_failed << "/" << test_num << endl;
    record_score();
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


void test_lexer_tokenizer() {
    cout << "Testing the Lexer" << endl;

    // Math ops
    compare_tokenizer("[add]", "add");
    compare_tokenizer("[sub]", "sub");
    compare_tokenizer("[mul]", "mul");
    compare_tokenizer("[div]", "div");
    compare_tokenizer("[mod]", "mod");

    // Stack ops
    compare_tokenizer("[push, int8, N(42)]", "push int8(42)");
    compare_tokenizer("[push, int16, N(-123)]", "push int16(-123)");
    compare_tokenizer("[push, int32, N(99999)]", "push int32(99999)");
    compare_tokenizer("[push, float, Z(3.14)]", "push float(3.14)");
    compare_tokenizer("[push, double, Z(-2.718)]", "push double(-2.718)");
    compare_tokenizer("[pop]", "pop");
    compare_tokenizer("[dump]", "dump");

    // Assertions
    compare_tokenizer("[assert, int8, N(0)]", "assert int8(0)");
    compare_tokenizer("[assert, int16, N(-32768)]", "assert int16(-32768)");

    // Print and Exit
    compare_tokenizer("[print]", "print");
    compare_tokenizer("[exit]", "exit");

    // Separators
    compare_tokenizer("[push, int8, N(123), sep, push, int16, N(456)]", "push int8(123)\npush int16(456)");
    compare_tokenizer("[sep, push, int8, N(77), sep, dump, sep]", "\npush int8(77)\ndump\n");

    // Comments
    compare_tokenizer("[com]", "; This is a comment");
    compare_tokenizer("[push, int8, N(5), sep, com, sep]", "push int8(5)\n; comment\n");

    // Invalid tokens
    compare_tokenizer("[err(i)]", "i");
    compare_tokenizer("[err(#), push, err(@)]", "#push @");

    // Complex
    compare_tokenizer("[push, int8, N(50), sep, push, int16, N(-22), sep, add, sep, pop, sep, print, sep, exit]", 
                      "push int8(50)\npush int16(-22)\nadd\npop\nprint\nexit");
    compare_tokenizer("[sep, push, int8, N(123), sep]", "\n\npush int8(123)\n\n");
    compare_tokenizer("[push, int16, N(123), sep, push, int32, N(32)]", "push int16(123)\npush int32(32)");

    compare_tokenizer("[sep, com, sep, com, sep, com, sep, push, int32, N(42), sep, push, int32, N(33), sep, add, sep, push, float, Z(44.55), sep, mul, sep, push, double, Z(42.42), sep, push, int32, N(42), sep, dump, sep, pop, sep, assert, double, Z(42.42), sep, exit, sep]",
            "\n;------------\n; exemple.avm\n;------------\n\npush int32(42)\npush int32(33)\n\nadd\n\npush float(44.55)\n\nmul\n\npush double(42.42)\npush int32(42)\n\ndump\n\npop\n\nassert double(42.42)\n\nexit\n\n");

    cout << "Tokenizer tests complete. "
         << test_num - test_failed << "/" << test_num << endl;
    record_score();
}

void record_score() {
    total_failed += test_failed;
    total_num += test_num;
    test_num = 0;
    test_failed = 0;
}

bool expect(bool res) {
//    if (reset) {
//        test_num = 0;
//        return res;
//    }

    cout << std::setw(2) << test_num
         << ". " << (res ? "OK" : "KO") << endl;
    
    test_failed += res ? 0 : 1;
    test_num++;
    return !res;
}

