#if defined(__STDC__) || defined(__cplusplus)
#define YYCONST const
#define YYPARAMS(x) x
#define YYDEFUN(name, arglist, args) name(args)
#define YYAND ,
#define YYPTR void *
#else
#define YYCONST
#define YYPARAMS(x) ()
#define YYDEFUN(name, arglist, args) name arglist args;
#define YYAND ;
#define YYPTR char *
#endif
#ifndef lint
YYCONST static char yysccsid[] = "@(#)yaccpar	1.8 (Berkeley +Cygnus.28) 01/20/91";
#endif
#define YYBYACC 1
#ifndef YYDONT_INCLUDE_STDIO
#include <stdio.h>
#endif
#ifdef __cplusplus
#include <stdlib.h> /* for malloc/realloc/free */
#endif
/*
byacc options currently in use:
byacc -b fontparse -d -l -o fontyacc.c fontparse.y
*/
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
#include <stdlib.h>
#include <string.h>
#include "fontparse.h"
/*#define yylex fontParselex*/
int fontParseSetInputBuf(const char*buf, int l);
int fontParsePrintInput(int inputIdx, int chrBefore, int chrAfter);
int fontParseReset(const char *mode);
int fontparselex();
extern int fontParseInputPos;
extern char *fontparsetext;
static yyerror(const char *msg) {
	printf("Generic error: %s, approximately here:\n", msg);
	fontParsePrintInput(fontParseInputPos, 16, 16);
}
static yyerrorExpl(const char *msg, int inputIdx) {
	printf("%s\n", msg);
	fontParsePrintInput(inputIdx, 16, 16);
}
typedef union {
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
} YYSTYPE;
#define WHITESPACE 257
#define SPECIALCHAR 258
#define UNMATCHED 259
#define COMMAND 260
#define COMMANDARG 261
#define WORD 262
#define NUMBER 263
#define OPENCURLY 264
#define CLOSECURLY 265
#define SUPERSCRIPT 266
#define SUBSCRIPT 267
#define ENDOFFILE 268
#define YYERRCODE 256
static YYCONST short yylhs[] = {                                        -1,
    0,    3,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    4,    4,    2,    2,    2,
};
static YYCONST short yylen[] = {                                         2,
    2,    2,    1,    2,    2,    2,    2,    2,    1,    1,
    1,    1,    1,    1,    2,    1,    3,    3,    2,
};
static YYCONST short yydefred[] = {                                      0,
   13,   14,    0,   10,   11,   12,    0,    0,    0,    3,
    0,    0,   16,    0,    6,    7,    4,    5,    1,    2,
   19,    0,   15,   17,   18,
};
static YYCONST short yydgoto[] = {                                       9,
   10,   13,   11,   14,
};
static YYCONST short yysindex[] = {                                   -183,
    0,    0, -250,    0,    0,    0, -205, -205,    0,    0,
 -217, -194,    0, -250,    0,    0,    0,    0,    0,    0,
    0, -255,    0,    0,    0,
};
static YYCONST short yyrindex[] = {                                      0,
    0,    0, -241,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0, -229,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,
};
static YYCONST short yygindex[] = {                                      0,
   -7,   40,   -3,    0,
};
#define YYTABLESIZE 84
static YYCONST short yytable[] = {                                      15,
   17,    1,    2,   20,    3,    4,    5,    6,   22,   24,
    7,    8,   25,   12,   20,    9,    9,    0,    9,    9,
    9,    9,    0,    9,    9,    9,    9,    8,    8,    0,
    8,    8,    8,    8,    0,    8,    8,    8,    8,    1,
    2,    0,    3,    4,    5,    6,   16,   18,    7,    8,
   19,    1,    2,   23,    3,    4,    5,    6,   12,    0,
    7,    8,    1,    2,    0,    3,    4,    5,    6,    0,
   21,    7,    8,    1,    2,    0,    3,    4,    5,    6,
    0,    0,    7,    8,
};
static YYCONST short yycheck[] = {                                       7,
    8,  257,  258,   11,  260,  261,  262,  263,   12,  265,
  266,  267,  268,  264,   22,  257,  258,   -1,  260,  261,
  262,  263,   -1,  265,  266,  267,  268,  257,  258,   -1,
  260,  261,  262,  263,   -1,  265,  266,  267,  268,  257,
  258,   -1,  260,  261,  262,  263,    7,    8,  266,  267,
  268,  257,  258,   14,  260,  261,  262,  263,  264,   -1,
  266,  267,  257,  258,   -1,  260,  261,  262,  263,   -1,
  265,  266,  267,  257,  258,   -1,  260,  261,  262,  263,
   -1,   -1,  266,  267,
};
#define YYFINAL 9
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 268
#if YYDEBUG
static YYCONST char *YYCONST yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"WHITESPACE","SPECIALCHAR",
"UNMATCHED","COMMAND","COMMANDARG","WORD","NUMBER","OPENCURLY","CLOSECURLY",
"SUPERSCRIPT","SUBSCRIPT","ENDOFFILE",
};
static YYCONST char *YYCONST yyrule[] = {
"$accept : input",
"input : sentence ENDOFFILE",
"sentence : sentence word",
"sentence : word",
"word : SUBSCRIPT word",
"word : SUBSCRIPT option",
"word : SUPERSCRIPT word",
"word : SUPERSCRIPT option",
"word : COMMAND optionlist",
"word : COMMAND",
"word : COMMANDARG",
"word : WORD",
"word : NUMBER",
"word : WHITESPACE",
"word : SPECIALCHAR",
"optionlist : optionlist option",
"optionlist : option",
"option : OPENCURLY sentence CLOSECURLY",
"option : OPENCURLY sentence ENDOFFILE",
"option : OPENCURLY CLOSECURLY",
};
#endif
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif
#ifdef YYSTACKSIZE
#ifndef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#endif
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
#ifndef YYMAXSTACKSIZE
#define YYMAXSTACKSIZE 10000
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
YYSTYPE yyval;
YYSTYPE yylval;
static short *yyss;
static YYSTYPE *yyvs;
static int yystacksize;
#define yyfree(x) free(x)
extern int yylex();

static YYPTR
YYDEFUN (yymalloc, (bytes), unsigned bytes)
{
    YYPTR ptr = (YYPTR) malloc (bytes);
    if (ptr != 0) return (ptr);
    yyerror ("yyparse: memory exhausted");
    return (0);
}

static YYPTR
YYDEFUN (yyrealloc, (old, bytes), YYPTR old YYAND unsigned bytes)
{
    YYPTR ptr = (YYPTR) realloc (old, bytes);
    if (ptr != 0) return (ptr);
    yyerror ("yyparse: memory exhausted");
    return (0);
}

static int
#ifdef __GNUC__
__inline__
#endif
yygrow ()
{
    int old_stacksize = yystacksize;
    short *new_yyss;
    YYSTYPE *new_yyvs;

    if (yystacksize == YYMAXSTACKSIZE)
        return (1);
    yystacksize += (yystacksize + 1 ) / 2;
    if (yystacksize > YYMAXSTACKSIZE)
        yystacksize = YYMAXSTACKSIZE;
#if YYDEBUG
    if (yydebug)
        printf("yydebug: growing stack size from %d to %d\n",
               old_stacksize, yystacksize);
#endif
    new_yyss = (short *) yyrealloc ((char *)yyss, yystacksize * sizeof (short));
    if (new_yyss == 0)
        return (1);
    new_yyvs = (YYSTYPE *) yyrealloc ((char *)yyvs, yystacksize * sizeof (YYSTYPE));
    if (new_yyvs == 0)
    {
        yyfree (new_yyss);
        return (1);
    }
    yyss = new_yyss;
    yyvs = new_yyvs;
    return (0);
}

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
#define YYABORT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#if YYDEBUG
#ifdef __cplusplus
extern "C" char *getenv();
#else
extern char *getenv();
#endif
#endif

int
yyparse()
{
    register int yym, yyn, yystate;
    register YYSTYPE *yyvsp;
    register short *yyssp;
    short *yysse;
#if YYDEBUG
    register YYCONST char *yys;

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == 0)
    {
        yyss = (short *) yymalloc (YYSTACKSIZE * sizeof (short));
        if (yyss == 0)
          goto yyabort;
        yyvs = (YYSTYPE *) yymalloc (YYSTACKSIZE * sizeof (YYSTYPE));
        if (yyvs == 0)
        {
            yyfree (yyss);
            goto yyabort;
        }
        yystacksize = YYSTACKSIZE;
    }
    yysse = yyss + yystacksize - 1;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;
    goto yyloop;

yypush_lex:
    yyval = yylval;
    yystate = yytable[yyn];
yypush:
    if (yyssp >= yysse)
    {
        int depth = yyssp - yyss;
        if (yygrow() != 0)
             goto yyoverflow;
        yysse = yyss + yystacksize -1;
        yyssp = depth + yyss;
        yyvsp = depth + yyvs;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    yyn = yysindex[yystate];
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, reading %d (%s)\n", yystate,
                    yychar, yys);
        }
#endif
    }
    if (yyn != 0
        && ((yyn += yychar), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: state %d, shifting to state %d\n",
                    yystate, yytable[yyn]);
#endif
        if (yyerrflag > 0)  --yyerrflag;
        yychar = (-1);
        goto yypush_lex;
    }
    yyn = yyrindex[yystate];
    if (yyn != 0
        && ((yyn += yychar), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            yyn = yysindex[*yyssp];
            if (yyn != 0
                && ((yyn += YYERRCODE), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
                && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: state %d, error recovery shifting\
 to state %d\n", *yyssp, yytable[yyn]);
#endif
                goto yypush_lex;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("yydebug: error recovery discarding state %d\n",
                            *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("yydebug: state %d, error recovery discards token %d (%s)\n",
                    yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("yydebug: state %d, reducing by rule %d (%s)\n",
                yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
{
	yyval.node.node = yyvsp[-1].node.node;
	yyval.node.node->inputIdx = yyvsp[-1].node.inputIdx;
}
break;
case 2:
{
	yyval.node.node = fpNodeAlloc(fpnSentence, 2); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[-1].node.node, 0);
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 1);
/*	if ($2->type == fpnWordSubscript) fpSetSubscript($1, $2);
	if ($2->type == fpnWordSuperscript) fpSetSubscript($1, $2);*/
/*	printf("sentence \n", fontparseval);*/
/*	printf("sentence word at %d\n", $$.inputIdx);*/
}
break;
case 3:
{
	yyval.node.node = fpNodeAlloc(fpnSentence, 2);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 1);
/*	printf("1 word sentence\n", fontparseval);*/
/*	printf("word at %d\n", $$.inputIdx);*/
}
break;
case 4:
{
	yyval.node.node = fpNodeAlloc(fpnWordSubscript, 1);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].chr.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 0);	
/*	printf("word (SUBSCRIPT option)\n", fontparseval);*/
/*	printf("SUBSCRIPT word at %d\n", $$.inputIdx);*/
}
break;
case 5:
{
	yyval.node.node = fpNodeAlloc(fpnWordSubscript, 1);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].chr.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 0);	
/*	printf("SUBSCRIPT option at %d\n", $$.inputIdx);*/
}
break;
case 6:
{
	yyval.node.node = fpNodeAlloc(fpnWordSuperscript, 1);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].chr.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 0);	
/*	printf("word (SUPERSCRIPT option)\n", fontparseval);*/
/*	printf("SUPERSCRIPT word at %d\n", $$.inputIdx);*/
}
break;
case 7:
{
	yyval.node.node = fpNodeAlloc(fpnWordSuperscript, 1);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].chr.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 0);	
/*	printf("word (SUPERSCRIPT option)\n", fontparseval);*/
/*	printf("SUPERSCRIPT option at %d\n", $$.inputIdx);*/
}
break;
case 8:
{
	yyval.node.node = fpNodeAlloc(fpnWordCommand, 1);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].str.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 0);	
	yyval.node.node->str = yyvsp[-1].str.str;
/*	printf("word (COMMAND optionlist) '%s'\n", $1);*/
/*	printf("COMMAND optionlist at %d\n", $$.inputIdx);*/
/*	printf("COMMAND '%s' at %d\n", $$.node->str, $$.inputIdx);*/
}
break;
case 9:
{
	yyval.node.node = fpNodeAlloc(fpnWordCommandNoOption, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].str.inputIdx;
	yyval.node.node->str = yyvsp[0].str.str;
/*	printf("word (COMMAND) '%s'\n", $1);*/
/*	printf("COMMAND NO ARG '%s' at %d\n", $$.node->str, $$.inputIdx);*/
}
break;
case 10:
{
	yyval.node.node = fpNodeAlloc(fpnWordCommandArg, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].cnt.inputIdx;
	yyval.node.node->nb = yyvsp[0].cnt.cnt;
/*	printf("word (COMMAND ARG) '%s'\n", $1);*/
/*	printf("COMMANDARG at %d\n", $$.inputIdx);*/
}
break;
case 11:
{
	yyval.node.node = fpNodeAlloc(fpnWordWord, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].str.inputIdx;
	yyval.node.node->str = yyvsp[0].str.str;
/*	printf("word (WORD) '%s'\n", $1);*/
/*	printf("WORD at %d\n", $$.inputIdx);*/
/*	fontParsePrintInput($$.inputIdx, 10, 10);*/
}
break;
case 12:
{
	yyval.node.node = fpNodeAlloc(fpnWordNumber, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].str.inputIdx;
	yyval.node.node->str = yyvsp[0].str.str;
/*	printf("word (NUMBER) '%s'\n", $1);*/
/*	printf("NUMBER at %d\n", $$.inputIdx);*/
}
break;
case 13:
{
	yyval.node.node = fpNodeAlloc(fpnWordWhiteSpace, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].cnt.inputIdx;
	yyval.node.node->nb = yyvsp[0].cnt.cnt;
/*	printf("word (WHITESPACE) %d chars\n", $1);*/
/*	printf("WHITESPACE at %d\n", $$.inputIdx);*/
}
break;
case 14:
{
	yyval.node.node = fpNodeAlloc(fpnWordSpecialChar, 0);
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].chr.inputIdx;
	yyval.node.node->nb = yyvsp[0].chr.chr;
/*	printf("word (SPECIALCHAR) '%c'\n", fontparseval);*/
/*	printf("SPECIALCHAR at %d\n", $$.inputIdx);*/
}
break;
case 15:
{
	yyval.node.node = fpNodeAlloc(fpnOptionList, 2); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[-1].node.node, 0);
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 1);
/*	printf("optionlist option\n");*/
/*	printf("optionlist option at %d\n", $$.inputIdx);*/
}
break;
case 16:
{
	yyval.node.node = fpNodeAlloc(fpnOptionList, 2); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[0].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[0].node.node, 1);
/*	printf("optionlist option\n");*/
/*	printf("option at %d\n", $$.inputIdx);*/
}
break;
case 17:
{
	yyval.node.node = fpNodeAlloc(fpnOption, 1); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[-1].node.node, 0);
/*	printf("option\n");*/
/*	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);*/
}
break;
case 18:
{
	yyerrorExpl("Parser: warning: unterminated option, missing '}': ", yyvsp[0].cnt.inputIdx - 1);
	yyval.node.node = fpNodeAlloc(fpnOption, 1); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].node.inputIdx;
	fpSetChild(yyval.node.node, yyvsp[-1].node.node, 0);
/*	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);*/
}
break;
case 19:
{
	yyerrorExpl("Parser: warning: empty option: ", yyvsp[-1].cnt.inputIdx);
	yyval.node.node = fpNodeAlloc(fpnOption, 1); 
	yyval.node.node->inputIdx = yyval.node.inputIdx = yyvsp[-1].cnt.inputIdx;
/*	fpSetChild($$.node, $2.node, 0);*/
/*	printf("OPENCURLY sentence CLOSECURLY at %d\n", $$.inputIdx);*/
}
break;
    }
    yyssp -= yym;
    yyvsp -= yym;
    yym = yylhs[yyn];
    yystate = *yyssp;
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("yydebug: after reduction, shifting from state 0 to\
 state %d\n", YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("yydebug: state %d, reading %d (%s)\n",
                        YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    yyn = yygindex[yym];
	 if (yyn != 0
        && ((yyn += yystate), ((unsigned)yyn <= (unsigned)YYTABLESIZE))
        && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("yydebug: after reduction, shifting from state %d \
to state %d\n", *yyssp, yystate);
#endif
    goto yypush;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
