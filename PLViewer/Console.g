grammar Console;

tokens {
  COMMA = ',' ;
  SEMICOLON = ';' ;
  ASSIGN = '=' ;
  PLUS  = '+' ;
  MINUS = '-' ;
  MULT = '*' ;
  DIV = '/' ;
  DOT = '|' ;
  WEDGE = '^' ;
  NEGATE = '!' ;
  REVERSE = '~' ;
  RPAREN = ')' ;
  LPAREN = '(' ;
}

/*----------------
* PARSER RULES
*----------------*/

prog : stat ((COMMA | SEMICOLON) NEWLINE? stat)* (COMMA | SEMICOLON)? NEWLINE?;

stat : (ID ASSIGN)* expr 
     | 'quit(' ')' ;

expr : multExpr ((PLUS | MINUS) multExpr)* ;

multExpr : dotExpr ((MULT | DIV) dotExpr )* ;

dotExpr : wedgeExpr (DOT wedgeExpr)* ;

wedgeExpr : prefixed (WEDGE prefixed)* ;

prefixed : (NEGATE | REVERSE | PLUS | MINUS)? atom ;

atom : NUMBER
 | ID
 | LPAREN expr RPAREN;

/*----------------
* LEXER RULES
*----------------*/

NEWLINE : '\r'?'\n';

WHITESPACE : ( '\t' | ' ' | '\r' | '\n'| '\u000C' )+ { $channel = HIDDEN; } ;

ID : CHARACTER (CHARACTER | DIGIT)* ;

NUMBER : DIGIT+ '.' DIGIT* EXPONENT?
       | '.' DIGIT+ EXPONENT?
       | DIGIT+ EXPONENT
       | DIGIT+
      ;

fragment EXPONENT : ('e'|'E') (PLUS | MINUS)? DIGIT+ ;

fragment CHARACTER : ('a'..'z'|'A'..'Z'|'_') ;

fragment DIGIT : '0'..'9' ;
