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
void test_runtime();

int main(void) {
    test_lexer_tokenizer();
    test_lexer_syntax();
    test_parser();
    test_runtime();

    cout << endl << (total_failed == 0 ? "PASSED" : "FAILED")
         << " : " << total_num - total_failed << "/" << total_num
         << endl;
}

///////////////////////////////////////////////////////////////////////////////
void compare_runtime(const std::string &expected, const std::string &input) {
    auto tokens = Lexer::tokenize(input);

    std::stringstream output;

    Runtime runtime;

    try {
        runtime = Parser::parse(tokens);
        runtime.execute(output);
    }
    catch (std::exception &e) {
        if (expect(e.what() == expected)) {
            cout << "Error catch" << endl;
            cout << "Expected: " << expected << endl;
            cout << "  Actual: " << e.what() << endl;
            cout << "  Tokens: " << tokens   << endl;
        }
        return ;
    }

    auto actual = output.str();

    if (expect(actual == expected)) {
        cout << "Expected: <" << expected << ">" << endl;
        cout << "  Actual: <" << actual   << ">" << endl;
        cout << "  Tokens: " << tokens   << endl;
    }

}

void test_runtime() {
    cout << "Testing the Runtime" << endl;

    compare_runtime("42\n42.42\n3341.250000\n"
            ,"\n;------------\n; exemple.avm\n;------------\n\npush int32(42)\npush int32(33)\n\nadd\n\npush float(44.55)\n\nmul\n\npush double(42.42)\npush int32(42)\n\ndump\n\npop\n\nassert double(42.42)\n\nexit\n\n");
    compare_runtime("42\n"
            ,"push int8(12)\npush int8(30)\nadd\ndump\nexit");
    compare_runtime("Exit must be called before program end"
            ,"push int8(42)");
    compare_runtime("Line 2 | Cannot have instructions after exit"
            ,"push int8(42)\nexit\ndump\ndump");
    compare_runtime("Line 2 | Div by zero"
            ,"push int8(1)\npush int8(0)\ndiv\nexit");
    compare_runtime("Line 2 | Mod by zero"
            ,"push int8(1)\npush int8(0)\nmod\nexit");
    compare_runtime("Line 1 | Assert failed int8(0) != int8(1)"
            ,"push int8(0)\nassert int8(1)\nexit");
    compare_runtime("Line 1 | Assert failed float(0.0) != int8(0)"
            ,"push float(0.0)\nassert int8(0)\nexit");
    compare_runtime("8\n"
            ,"push int8(4)\npush int16(4)\nadd\nassert int16(8)\ndump\nexit\n");
    compare_runtime("-5\n"
            ,"push int8(4)\npush int16(9)\nsub\nassert int16(-5)\ndump\nexit\n");
    compare_runtime("2\n"
            ,"push int8(12)\npush int16(10)\nsub\nassert int16(2)\ndump\nexit\n");
    compare_runtime("2\n"
            ,"push int16(12)\npush int32(10)\nsub\nassert int32(2)\ndump\nexit\n");
    compare_runtime("5.0\n"
            ,"push float(0.5)\npush int16(10)\nmul\nassert float(5.0)\ndump\nexit");


    cout << "Runtime tests complete. "
         << test_num - test_failed << "/" << test_num << endl;
    record_score();
}


void compare_parser(const std::string &expected, const std::string &input) {
    auto tokens = Lexer::tokenize(input);
    Runtime runtime;
    try {
        runtime = Parser::parse(tokens);
    }
    catch (std::exception &e) {
        if (expect(e.what() == expected)) {
            cout << "Error catch" << endl;
            cout << "Expected: " << expected << endl;
            cout << "  Actual: " << e.what() << endl;
            cout << "  Tokens: " << tokens   << endl;
        }
        return ;
    }

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

    compare_parser("[push(42)]", "push int8(42)");
    compare_parser("[push(12), push(12), add]", "push int8(12)\npush int8(12)\nadd");
    compare_parser("[]", "");
    compare_parser("Line 0 | Is not a value \"int7\"", "push int7(123)");
    compare_parser("Line 1 | Value types don't match \"float\" with \"N(2)\"", "push int8(123)\npush float(2)");
    compare_parser("Line 0 | Not enough to construct value for \"push\"", "push ");
    compare_parser("Line 0 | Value types don't match \"int8\" with \"Z(123.3)\"", "push int8(123.3)");
    compare_parser("Line 0 | Value types don't match \"float\" with \"N(123)\"", "assert float(123)");
    compare_parser("Line 4 | Not enough to construct value for \"push\"", "\n\n\n\npush 3");
    compare_parser("todo", "push");

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
            ,"[com(; push), sep, pop]"
            ,"push pop");
//    compare_syntaxchecker("[Line 0 | Some sort of error]"
//            ,"[com(; \"int8(16)\")]"
//            ,"int8(16)"); // Maybe moved to parsing errors?

    compare_syntaxchecker("[Line 0 | Unexpected token \"  \"]"
            ,"[com(; \"  \")]"
            ,"  ");
    compare_syntaxchecker("[Line 0 | Did you mean \"push \"? <- <push>]"
            ,"[push]"
            ,"push");
    compare_syntaxchecker("[Line 0 | Did you mean \"int8\"? <- <int>]"
            ,"[int8]"
            ,"int");
    compare_syntaxchecker("[Line 0 | Did you mean \"mul\"? <- <mu>]"
            ,"[mul]"
            ,"mu");

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
    compare_tokenizer("[i]", "i");
    compare_tokenizer("[#, push, @]", "#push @");

    // Complex
    compare_tokenizer("[sep, sep, sep, sep, exit, sep]", "\n\n\n\nexit\n");
    compare_tokenizer("[push, int8, N(50), sep, push, int16, N(-22), sep, add, sep, pop, sep, print, sep, exit]", 
                      "push int8(50)\npush int16(-22)\nadd\npop\nprint\nexit");
    compare_tokenizer("[sep, sep, push, int8, N(123), sep, sep]", "\n\npush int8(123)\n\n");
    compare_tokenizer("[push, int16, N(123), sep, push, int32, N(32)]", "push int16(123)\npush int32(32)");

    compare_tokenizer("[sep, com, sep, com, sep, com, sep, sep, push, int32, N(42), sep, push, int32, N(33), sep, sep, add, sep, sep, push, float, Z(44.55), sep, sep, mul, sep, sep, push, double, Z(42.42), sep, push, int32, N(42), sep, sep, dump, sep, sep, pop, sep, sep, assert, double, Z(42.42), sep, sep, exit, sep, sep]",
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

