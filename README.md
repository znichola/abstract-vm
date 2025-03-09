# AbstractVM

A machine that uses a stack to compute simple arithmetic expressions.

## How it works

Using a pseudo haskell like syntax this is the highlevel overview of how the program functions.

```haskell
input_string -> Tokenizer -> Tokens

Token -> Tokenizer.syntaxChecker -> (Tokens', SyntaxError)

Tokens' -> Parser -> Runtime(Stack) {Throw error}

Runtime.execute(out_stream) -> result in out_stream {Throw error}
```

--- 

## TODO

## Stream of thoughts about Parsing vs Lexer/Tokenizer split

> _:warning: These are just misalenious thoughts during dev and where not updated after the fact._

The code so far is split down the Tokenizer to parser. The problem is that the parsing is basically already present in the lexer/tokenizer. I transform the token stream into something that can aproximativly run, and to do this it's a whole loa of parsing really. So how do i make this split more correct and keep the envisioned functionality where i can on the fly fix the syntax tree as much as possible. 
One idea I have is to basically keep the lexer so it just removes any error tokens as comments and add the seperators to provide a simple and correct token stream for parsing. And parsing will take care of creating a correct synax things.

ok new idea. I make a thing to export the "AST" in quotes because it's a straight line. Stored in a vector. But if I can print the ast then I can very simply export it to a file for correcting the syntax. And it also means i can do actual parsing because that's what will produce the AST. Downside is I'm both rewriting the AST and making the AST at once. But this could be ok? hmmm how do i handel comments in the AST? don't want to be dragging them around for the execution structure

> :warning: Don't try using `unique_ptr` it's very broken. Can't have it in containers becasuse you can't "copy" it, it's dificult to get working and I've spend enough time already.


# Parsing

I think this grammar they have given us is not a [context free grammar](https://en.wikipedia.org/wiki/Context-free_grammar) because `exit` must be the last argument, so you need to pass a variable down for it, at least I think that's how it works. It's maybe a [conjunctive grammar](https://en.wikipedia.org/wiki/Conjunctive_grammar)? but who knows. 

## Errors

There is parsing & runtime. The errors should therefore be split between two classes of error.

### Lexographic errors (syntax)

These come from the lexer, and analysing the token stream. They do not throw, but rather are returned from the `Lexer::syntaxValidate` function. Eg `int8(bzz)` -> TODO define error type or `push fufu` -> 'fufu' unknown value, `pushh` -> unknown instruction 'pushh'. or `push push` -> Push must be followed by a value.

### Parsing errors (syntax + sematic)

These come from the parser, when analysing the token stream and producing the exeicution structure. Eg: `int8(123.123)` -> Cannont instantiate 'int8' with floatvalue or `int8(9000)` -> Int8 value overflow. or Program end with no exit. 

### Runtime errors

These come from the runtime engine. Eg : `add` instruction pop on empty value. or `mul` Result overflows or `div` Division with zero.


# Links

- [lexers vs parsers](https://stackoverflow.com/questions/2842809/lexers-vs-parsers)
- [Chomsky hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy)


