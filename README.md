# AbstractVM

A machine that uses a stack to compute simple arithmetic expressions.

The simplified steps are as follows: 

- 1. read in a file
- 2. tokenize it's content
- 3. pass tokens through lexer to assign meaning, syntax error surfaced here.
- 3. 

## Errors

There is parsing & runtime. The errors should therefore be split between two classes of error.

### Lexographic errors (syntax)

These come from the lexer, and analysing the token stream. They do not throw, but rather are returned from the `Lexer::lex` function. Eg `int8(bzz)` -> TODO define error type or `push fufu` -> 'fufu' unknown value, `pushh` -> unknown instruction 'pushh'. or `push push` -> Push must be followed by a value.

### Parsing errors (syntax + sematic)

These come from the parser, when analysing the token stream and producing the exeicution structure. Eg: `int8(123.123)` -> Cannont instantiate 'int8' with floatvalue or `int8(9000)` -> Int8 value overflow. or Program end with no exit. 

### Runtime errors

These come from the runtime engine. Eg : `add` instruction pop on empty value. or `mul` Result overflows or `div` Division with zero.


# Links

- [lexers vs parsers](https://stackoverflow.com/questions/2842809/lexers-vs-parsers)
- [Chomsky hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy)

