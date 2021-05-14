# Lexer Grammar `[work in progress]`
This is the grammar for the programming language Loop:
```js
UNRECOGNIZED    :
NEWLINE         : '\n'
WHITESPACE      : [t ]+ -> skip

// Datatypes
BOOLEAN                 : 'true'|'false'
STRING                  : 'string'
INT                     : 'i8', 'i16', 'i32', 'i64'
UNSIGNED                : 'u8', 'u16', 'u32', 'u64'
FLOAT                   : 'f8', 'f16', 'f32', 'f64'

// Literals
INT_LITERALS            : '0'|[1-9][0-9]*
DEC_LITERALS            : '0'|[1-9][0-9]* '.' [0-9]+
HEX_LITERALS            : 0[xX][0-9a-fA-F]+
BIN_LITERALS            : \b[01]+\b
UNICODE_LITERALS        : 0[xX][0-9a-fA-F]+

// Operators
EQUAL                   : '='
PLUS                    : '+'
MINUS                   : '-'
SLASH                   : '/'
PERCENT                 : '%'
PIPE                    : '|'
AND                     : '&'
T_DOT                   : '.'
T_COMMA                 : ','
T_COLON                 : ':'
SEMICOLON               : ';'
T_LEFT_ROUND_BRACKET    : '('
RIGHT_ROUNDED_BRACKET   : ')'
LEFT_CURLY_BRACKET      : '{'
RIGHT_CURLY_BRACKET     : '}'
LEFT_SQUARE_BRACKET     : '['
RIGHT_SQUARE_BRACKET    : ']'
LEFT_ANGLE_BRACKET      : '<'
RIGHT_ANGLE_BRACKET     : '>'
DOUBLE_COLON            : '::'
LOGIC_AND               : '&&'
DOUBLE_PIPE             : '||'
DOUBLE_EQUAL            : '=='
DOUBLE_PLUS             : '++'
DOUBLE_MINUS            : '--'
EQUAL_PLUS              : '+='
EQUAL_MINUS             : '-='
EQUAL_PIPE              : '|='
EQUAL_LESSER_BRACKET    : '<='
EQUAL_GREETER_BRACKET   : '>='

// Keywords
MODULE                  : 'module'
IMPORT                  : 'import'
FUNCTION                : 'fn'
PUBLIC                  : 'pub'
STATIC                  : 'public'
IF                      : ' if'
ELSE                    : 'else'
LOOP                    : 'loop'
RETURN                  : 'return'
STOP                    : 'stop'
JUMP                    : 'jump'
GO                      : 'go'
IN                      : 'in'
T_LABEL                 : '@label'

// Comments
MULTI_LINE_COMMENT      : '/*' [A-Za-z0-9_]* '*/'
SINGLE_LINE_COMMENT     : '//' [A-Za-z0-9_]*

// Identifiers
ID                      : [a-z][A-Za-z0-9_]*
```
