grammar Console; 

options {
  language=Java;
  output=AST; 
  superClass=CustomParser;
}

tokens {
 DISPLAY;
 NODISPLAY;
 CONST;
 VAR;
 FUNC;
 APPLY;
 NIL;
}

@header {
package plviewer;

import java.util.Queue;
import java.util.LinkedList;

import pl3ga_pkg.mv;
import pl3ga_pkg.pl3ga;
}

@members {
  protected mv applyOperator(int op, mv x) {
    switch (op) {
      case NEGATE: 
        return pl3ga.negate(x);
      case REVERSE: 
        return pl3ga.reverse(x);
      case MINUS:
        return pl3ga.subtract(new mv(), x);
      case PLUS:
      default:
        break;
    }
    return x;
  }

  protected mv applyOperator(int op, mv x, mv y) {
    switch (op) {
      case PLUS:
        return pl3ga.add(x, y);
      case MINUS:
        return pl3ga.subtract(x, y);
      case MULT:
        return pl3ga.gp(x, y);
      case DIV:
        return pl3ga.igp(x, y);
      case DOT:
        return pl3ga.lc(x, y);
      case WEDGE:
        return pl3ga.op(x, y);
      default:
        break;
    }
    return new mv();
  }
}


/*----------------
* PARSER RULES
*----------------*/

prog : endstat* EOF;

endstat : s=stat t=terminator^ {completeExpr(s.r, t.display);}/* -> ^(t s)*/;

terminator returns [boolean display]
       : (COMMA | NEWLINE | EOF) 
            {$display = true;}
            -> DISPLAY
       | SEMICOLON 
            {$display = false;}
            -> NODISPLAY
       ;

stat returns [mv r]: (variable ASSIGN)+ expr {setVariable($variable.name, $expr.r); $r = $expr.r;}-> ^(ASSIGN variable* expr)
     | expr {$r = $expr.r;};

expr returns [mv r]: x=multExpr (o=plusgrp^ y=multExpr)* {$r = applyOperator(o.token, x.r, y.r);};

multExpr returns [mv r]: x=dotExpr (o=multgrp^ y=dotExpr )* {$r = applyOperator(o.token, x.r, y.r);};

dotExpr returns [mv r]: x=wedgeExpr (o=dotgrp^ y=wedgeExpr)* {$r = applyOperator(o.token, x.r, y.r);};

wedgeExpr returns [mv r]: x=prefixed (o=wedgegrp^ y=prefixed)* {$r = applyOperator(o.token, x.r, y.r);};

prefixed returns [mv r]: o=unarygrp? x=atom {$r = applyOperator(o.token, x.r);};

atom returns [mv r]: a=number {$r = a.r;}
 | b=constant {$r = b.r;}
 | c=variable {$r = c.r;}
 | d=funccall {$r = d.r;}
 | LPAREN! x=expr RPAREN! {$r = x.r;};

plusgrp  returns [int token]: x=(PLUS | MINUS) {$token = x.getType();};
multgrp  returns [int token]: x=(MULT | DIV) {$token = x.getType();};
dotgrp 	 returns [int token]: x=DOT {$token = x.getType();};
wedgegrp returns [int token]: x=WEDGE {$token = x.getType();};
unarygrp returns [int token]: x=(NEGATE | REVERSE | PLUS | MINUS) {$token = x.getType();};

number returns [mv r]
       : NUMBER {$r = toMV($NUMBER.text);};

constant returns [mv r, String name]
       : CONSTANT {$name = $CONSTANT.text; $r = getConstant($name); };

variable returns [mv r, String name]
       :  NAME {$name = $NAME.text; $r = getVariable($name); };
 
funccall returns [mv r]
       : fn=NAME LPAREN RPAREN 
            {$r = applyFunction($fn.text, new LinkedList<mv>());} 
            -> ^(APPLY $fn NIL)
       | fn=NAME LPAREN args=arguments RPAREN 
            {$r = applyFunction($fn.text, args.args);} 
            -> ^(APPLY $fn $args)
       ;

arguments returns [Queue<mv> args]
@init{$args = new LinkedList<mv>();}
       : x1=expr (COMMA! xn=expr)* {$args.offer(x1.r);};

/*----------------
* LEXER RULES
*----------------*/

// Operators
COMMA     : ',' ;
SEMICOLON : ';' ;
ASSIGN    : '=' ;
PLUS      : '+' ;
MINUS     : '-' ;
MULT      : '*' ;
DIV       : '/' ;
DOT       : '.' ;
WEDGE     : '^' ;
NEGATE    : '!' ;
REVERSE   : '~' ;
RPAREN    : ')' ;
LPAREN    : '(' ;

NEWLINE : ('\r'? '\n');

WHITESPACE : ( '\t' | ' ' | '\n' | '\r' | '\u000C' )+ { $channel = HIDDEN; } ;

CONSTANT : 'e01' | 'e02' | 'e03' | 'e12' | 'e23' | 'e31' ;

NAME : CHARACTER (CHARACTER | DIGIT)* ;

NUMBER : (PLUS | MINUS)? DIGIT+ ('.' DIGIT*)? EXPONENT? ;

fragment EXPONENT : ('e'|'E') (PLUS | MINUS)? DIGIT+ ;

fragment CHARACTER : ('a'..'z'|'A'..'Z'|'_') ;

fragment DIGIT : '0'..'9' ;
