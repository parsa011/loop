# Lexer Grammar `[work in progress]`
This is the grammar for the programming language Loop:
```c++
NEWLINE         : '\n'
WHITESPACE      : [t ]+ -> skip

// Datatypes
CHAR            : 'char'
STRING          : 'string'
INT             : 'int'
FLOAT           : 'float'
DOUBLE          : 'double'
BOOLEAN         : 'bool'
```