# Lexer Grammar `[work in progress]`
This is the grammar for the programming language Loop:
```c++
NEWLINE         : '\n'
WHITESPACE      : [t ]+ -> skip

// Datatypes
CHAR                    : 'char'
STRING                  : 'string'
INT                     : 'int'
FLOAT                   : 'float'
DOUBLE                  : 'double'
BOOLEAN                 : 'bool'
VOID                    : 'void'

// Literals
INT_LITERALS            : '0'|[1-9][0-9]*
DEC_LITERALS            : '0'|[1-9][0-9]* '.' [0-9]+

// Operators
EQUAL                   : '='
PLUS                    : '+'
MINUS                   : '-'
SLASH                   : '/'
PERCENT                 : '%'
PIPE                    : '|'
AND                     : '&'
SEMICOLON               : ';'
LEFT_ROUNDED_BRACKET    : '('
RIGHT_ROUNDED_BRACKET   : ')'
LEFT_CURLY_BRACKET      : '{'
RIGHT_CURLY_BRACKET     : '}'
LEFT_SQUARE_BRACKET     : '['
RIGHT_SQUARE_BRACKET    : ']'
LEFT_ANGLE_BRACKET      : '<'
RIGHT_ANGLE_BRACKET     : '>'
LOGIC_AND               : '&&'
DOUBLE_EQUAL            : '=='
DOUBLE_PLUS             : '++'
DOUBLE_MINUS            : '--'
DOUBLE_PIPE             : '||'
EQUAL_PLUS              : '+='
EQUAL_MINUS             : '-='
EQUAL_PIPE              : '|='
EQUAL_LESSER_BRACKET    : '<='
EQUAL_GREETER_BRACKET   : '>='

// Keywords
NAMESPACE               : 'namespace'
CLASS                   : 'class'
ENUM                    : 'enum'
EXTERN                  : 'extern'
INTERFACE               : 'interface'
EXTENDS                 : 'extends'
IMPLEMENTS              : 'implements'
ABSTRACT                : 'abstract'
PUBLIC                  : 'public'
PRIVATE                 : 'private'
PROTECTED               : 'protected'
STATIC                  : 'static'
IF                      : 'if'
ELIF                    : 'elif'
ELSE                    : 'else'
FOR                     : 'for'
WHILE                   : 'while'
RETURN                  : 'return'
BREAK                   : 'break'
CONTINUE                : 'continue'
USING                   : 'using'
FINAL                   : 'final'
TRUE                    : 'true'
FALSE                   : 'false'
THIS                    : 'this'

// Comments
MULTI_LINE_COMMENT      : '/*' [A-Za-z0-9_]* '*/
SINGLE_LINE_COMMENT     : '//' [A-Za-z0-9_]*

// Identifiers
ID                      : [_]*[a-z][A-Za-z0-9_]*
```