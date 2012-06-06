%{
/*
byacc options currently in use:
byacc -b fontparse -d -l -o fontyacc.c fontparse.y
*/
%}

%{
#define yyact fontparseact
#define yychar fontparsechar
#define yychk fontparsechk
#define yydebug fontparsedebug
#define yydef fontparsedef
#define yyerrflag fontparseerrflag
#define yyerror fontparseerror
#define yyexca fontparseexca
#define yylex fontParselex
#define yylval fontparselval
#define yynerrs fontparsenerrs
#define yypact fontparsepact
#define yyparse fontParseParse
#define yypgo fontparsepgo
#define yyps fontparseps
#define yypv fontparsepv
#define yyr1 fontparser1
#define yyr2 fontparser2
#define yyreds fontparsereds
#define yys fontparses
#define yystate fontparsestate
#define yytmp fontparsetmp
#define yytoks fontparsetoks
#define yyv fontparsev
#define yyval fontparseval
%}

%{
#include <stdlib.h>
#include <string.h>
#include "fontparse.h"
/*#define yylex fontParselex*/
int fontParseSetInputBuf(const char*buf, int l);
int fontParsePrintInput(int inputIdx, int chrBefore, int chrAfter);
int fontParseReset(const char *mode);
int fontparselex();
extern int fontParseInputPos;
%}

%{
extern char *fontparsetext;
static yyerror(const char *msg) {
	printf("Generic error: %s, approximatelly here:\n", msg);
	fontParsePrintInput(fontParseInputPos, 16, 16);
}
static yyerrorExpl(const char *msg, int inputIdx) {
	printf("%s\n", msg);
	fontParsePrintInput(inputIdx, 16, 16);
}
%}

%union {
	struct {
		char *str;
		int inputIdx;
	} str;
	struct {
		int cnt;
		int inputIdx;
	} cnt;
	struct {
		int chr;
		int inputIdx;
	} chr;
	struct {
		struct fpNode_s *node;
		int inputIdx;
	} node;
}

%token <cnt> WHITESPACE 
%token <chr> SPECIALCHAR 
%token <cnt> UNMATCHED 
%token <str> COMMAND 
%token <cnt> COMMANDARG
%token <str> WORD
%token <str> NUMBER
%token <cnt> OPENCURLY 
%token <cnt> CLOSECURLY 
%token <chr> SUPERSCRIPT
%token <chr> SUBSCRIPT
%token <cnt> ENDOFFILE

%type <node> word, option, sentence, optionlist, input

%right SUPERSCRIPT
%right SUBSCRIPT


%%

input:
sentence ENDOFFILE {
	$$.node = $1.node;
	$$.node->inputIdx = $1.inputIdx;
};

sentence: 
sentence word {
	$$.node = fpNodeAlloc(fpnSentence, 2); 
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $1.node, 0);
	fpSetChild($$.node, $2.node, 1);
/*	if ($2->type == fpnWordSubscript) fpSetSubscript($1, $2);
	if ($2->type == fpnWordSuperscript) fpSetSubscript($1, $2);*/
//	printf("sentence \n", fontparseval);
//	printf("sentence word at %d\n", $$.inputIdx);
} | 
word {
	$$.node = fpNodeAlloc(fpnSentence, 2);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $1.node, 1);
//	printf("1 word sentence\n", fontparseval);
//	printf("word at %d\n", $$.inputIdx);
};

word: 
SUBSCRIPT word  {
	$$.node = fpNodeAlloc(fpnWordSubscript, 1);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $2.node, 0);	
//	printf("word (SUBSCRIPT option)\n", fontparseval);
//	printf("SUBSCRIPT word at %d\n", $$.inputIdx);
} | 
SUBSCRIPT option {
	$$.node = fpNodeAlloc(fpnWordSubscript, 1);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $2.node, 0);	
//	printf("SUBSCRIPT option at %d\n", $$.inputIdx);
} | 
SUPERSCRIPT word  {
	$$.node = fpNodeAlloc(fpnWordSuperscript, 1);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $2.node, 0);	
//	printf("word (SUPERSCRIPT option)\n", fontparseval);
//	printf("SUPERSCRIPT word at %d\n", $$.inputIdx);
} | 
SUPERSCRIPT option {
	$$.node = fpNodeAlloc(fpnWordSuperscript, 1);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $2.node, 0);	
//	printf("word (SUPERSCRIPT option)\n", fontparseval);
//	printf("SUPERSCRIPT option at %d\n", $$.inputIdx);
} | 
COMMAND optionlist {
	$$.node = fpNodeAlloc(fpnWordCommand, 1);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $2.node, 0);	
	$$.node->str = $1.str;
//	printf("word (COMMAND optionlist) '%s'\n", $1);
//	printf("COMMAND optionlist at %d\n", $$.inputIdx);
//	printf("COMMAND '%s' at %d\n", $$.node->str, $$.inputIdx);
} | 
COMMAND {
	$$.node = fpNodeAlloc(fpnWordCommandNoOption, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->str = $1.str;
//	printf("word (COMMAND) '%s'\n", $1);
//	printf("COMMAND NO ARG '%s' at %d\n", $$.node->str, $$.inputIdx);
} | 
COMMANDARG {
	$$.node = fpNodeAlloc(fpnWordCommandArg, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->nb = $1.cnt;
//	printf("word (COMMAND ARG) '%s'\n", $1);
//	printf("COMMANDARG at %d\n", $$.inputIdx);
} | 
WORD {
	$$.node = fpNodeAlloc(fpnWordWord, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->str = $1.str;
//	printf("word (WORD) '%s'\n", $1);
//	printf("WORD at %d\n", $$.inputIdx);
//	fontParsePrintInput($$.inputIdx, 10, 10);
} | 
NUMBER	{
	$$.node = fpNodeAlloc(fpnWordNumber, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->str = $1.str;
//	printf("word (NUMBER) '%s'\n", $1);
//	printf("NUMBER at %d\n", $$.inputIdx);
} | 
WHITESPACE	{
	$$.node = fpNodeAlloc(fpnWordWhiteSpace, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->nb = $1.cnt;
//	printf("word (WHITESPACE) %d chars\n", $1);
//	printf("WHITESPACE at %d\n", $$.inputIdx);
} |
SPECIALCHAR {
	$$.node = fpNodeAlloc(fpnWordSpecialChar, 0);
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	$$.node->nb = $1.chr;
//	printf("word (SPECIALCHAR) '%c'\n", fontparseval);
//	printf("SPECIALCHAR at %d\n", $$.inputIdx);
};

optionlist: 
optionlist option {
	$$.node = fpNodeAlloc(fpnOptionList, 2); 
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $1.node, 0);
	fpSetChild($$.node, $2.node, 1);
//	printf("optionlist option\n");
//	printf("optionlist option at %d\n", $$.inputIdx);
} |
option {
	$$.node = fpNodeAlloc(fpnOptionList, 2); 
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
	fpSetChild($$.node, $1.node, 1);
//	printf("optionlist option\n");
//	printf("option at %d\n", $$.inputIdx);
};

option:
OPENCURLY sentence CLOSECURLY {
	$$.node = fpNodeAlloc(fpnOption, 1); 
	$$.node->inputIdx = $$.inputIdx = $2.inputIdx;
	fpSetChild($$.node, $2.node, 0);
//	printf("option\n");
//	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);
} |
OPENCURLY sentence ENDOFFILE {
	yyerrorExpl("Parser: warning: unterminated option, missing '}': ", $3.inputIdx - 1);
	$$.node = fpNodeAlloc(fpnOption, 1); 
	$$.node->inputIdx = $$.inputIdx = $2.inputIdx;
	fpSetChild($$.node, $2.node, 0);
//	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);
} |
OPENCURLY CLOSECURLY {
	yyerrorExpl("Parser: warning: empty option: ", $1.inputIdx);
	$$.node = fpNodeAlloc(fpnOption, 1); 
	$$.node->inputIdx = $$.inputIdx = $1.inputIdx;
//	fpSetChild($$.node, $2.node, 0);
//	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);
};



%%

fpNode *fontParse(const char *str, const char *mode) {
	int err;

	fontParseReset(mode);

	fontParseSetInputBuf(str, strlen(str));


	err = fontParseParse();
	if (err) {
		printf("fontParse(): error '%d'\n", err);
		return NULL;
	}
	else return fontparseval.node.node;
}
