
header "pre_include_cpp" {
#include <iostream>
#include <antlr/SemanticException.hpp>
#include <antlr/String.hpp>
#include "../state.h"
#include "consolescope.h"
using namespace std;

int g_consoleLexerGlobalScope = 0;
extern consoleScope *g_currentParsingScope;
}

options {
	mangleLiteralPrefix = "TK_";
	language="Cpp";
}

class ConsoleLexer extends Lexer;
options {
	k=2;
	importVocab=Extra;
	exportVocab=ConsoleLexer;
	charVocabulary = '\3'..'\377';
	interactive = false;
	genHashLines=false;
	testLiterals = true;
//	caseSensitiveLiterals = true;
}


tokens {
	"return"; "switch"; "default"; "case"; "break"; "continue"; "suspend"; 
	"if"; "else"; "while"; "for"; "function"; "batch"; "dynamic"; "inner_product"; "default_model"; "variable";
}


WS_	:	(' '
	|	'\t'
	|	'\n'	{newline();}
	|	'\r')
		{ _ttype = antlr::Token::SKIP; }
	;

OPERATOR
options {
	paraphrase = "operator";
} : ('<' | '>' | '!' | '=' | '.' | '+' | '-' | '&' | '|' | '^' | '~' | {((LA(2) != '*') && (LA(2) != '/'))}? '/' | '*' | WS_)+ 
	{};

ML_COMMENT
	:	"/*"
		(	{ LA(2)!='/' }? '*'
		|	'\n' { newline(); }
		|	~('*'|'\n')
		)*
		"*/"
			{ $setType(antlr::Token::SKIP); };

SL_COMMENT : 
	"//" 
	(~'\n')* 
	{ $setType(antlr::Token::SKIP); };

COLON 
options {
	paraphrase = ":";
} : {(LA(2) != ':')}?':' ;

SEMICOLON 
options {
	paraphrase = ";";
} : ';' ;

COMMA
options {
	paraphrase = ",";
} : ',' ;

PAROPEN 
options {
	paraphrase = "(";
} : '(' ;

PARCLOSE
options {
	paraphrase = ")";
} : ')' ;

SQUAREOPEN 
options {
	paraphrase = "[";
} : '[' ;

SQUARECLOSE
options {
	paraphrase = "]";
} : ']' ;

CURLYOPEN 
options {
	paraphrase = "{";
} : '{' ;

CURLYCLOSE
options {
	paraphrase = "}";
} : '}' ;


GLOBAL 
options {
	paraphrase = "global";
} : "::" 	{
	g_consoleLexerGlobalScope = 1;
};

protected
QUOTED_STR_ESC 
	:
	'\\' '\"' {
			$setText('"');
		};

ID
options {
	paraphrase = "an identifier";
}
	:	(('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'_'|'0'..'9')* |
		'"' (QUOTED_STR_ESC | ~('"' | '\n'))* ('"' | '\n')?)
{
	/* check termination of quoted string was by EOF or \n */ 
	string s = $getText;
	
	bool inQuotes = (s.at(0) == '"');
	if (inQuotes) {
		if (s.at(s.length()-1) != '"') {
			cprintf("Warning line(%d, %d): newline or end of file in quoted string\n", getLine(), getColumn());
			newline(); // it doesn't matter whether this EOF or newline, just up the line #
		}
		s = s.substr(1, s.length()-2);
		$setText(s);
	}

	// if Antlr keeps commenting out tokens with a digit in them, then let's just do it the hard way:
	if (s == "e3ga") $setType(TK_e3ga);
	else if (s == "p3ga") $setType(TK_p3ga);
	else if (s == "c3ga") $setType(TK_c3ga);
	else if (s == "c5ga") $setType(TK_c5ga);
	else if (s == "i2ga") $setType(TK_i2ga);
	else {/* determine if this is an identifier or function */
		if ((!inQuotes) && g_currentParsingScope->isFunction($getText)) $setType(FUNCNAME); 
		else $setType(IDENTIFIER);
	}
	
};

 


protected
INT : ('0'..'9')+ ;

CONSTANT options {
	paraphrase = "a constant scalar";
}
	: (INT ('.' INT)? | '.' INT) (('e' | 'E') ('+' | '-')? INT)? {};

