%{
/*
flex options currently in use:
flex -PfontParse -L -B -ofontlex.c  fontparse.l
*/
#include <string.h>
#include <stdlib.h>
#include <string.h>
#define yylval fontparselval
#include "fontyacc.h"
%}

%s FPM_TXT
%s FPM_EQN

%option noyywrap
%option never-interactive

%{
/*
Input to parser (all input in kept in a buffer, 
this parser is intended for small input...)
*/
static char *s_inputBuf = NULL;
static int s_inputLength = 0;
int fontParseInputPos = 0;
/* 
Input is parsed differently depending on whether we are in 
equation mode or in text mode. These variables are used to 
keep track of these mode switches. 
*/
static int s_parseMode = FPM_TXT;
static int s_curlyDepth = 0;
static int *s_parseModeStack = NULL;
static int s_parseModeDepth = 0;

int fontParseSetInputBuf(const char*buf, int l) {
	// allocate memory for the buffer
	if ( (s_inputBuf = (char*)realloc(s_inputBuf, l + 4)) == NULL) {
		printf("fontParseSetInputBuf(): memory allocation error for %d bytes.\n", l + 4);
		return -1;
	}

	// copy buffer, append \eof
	memcpy(s_inputBuf, buf, l);
	memcpy(s_inputBuf + l, "\\eof", 4);
	l+=4;

	s_inputLength = l;
	fontParseInputPos = 0;

	// set state to the initial parse mode (can be changed by calling 'fontParseReset(int initialMode)')
	BEGIN s_parseMode;
	return 0;
}

static int getInput(char *buf, int max_size) {
	int l;
	if (fontParseInputPos >= s_inputLength) return 0; 
	l = (max_size < s_inputLength - fontParseInputPos) ? max_size : (s_inputLength - fontParseInputPos);
	memcpy(buf, s_inputBuf + fontParseInputPos, l);
	fontParseInputPos += l;
	return l;
}

// inputIdx() returns the location in the input wher 'yytext' is located 
// (must be called immediatelly after the token has been returned)
static int inputIdx() {
	int i, l = yyleng;

	for (i = fontParseInputPos - 1; i >= 0; i--) {
		if (!memcmp(s_inputBuf + i, yytext, l))
		return i;
	}
	
	return (fontParseInputPos) ? fontParseInputPos - 1 : 0;
}

// Prints the line and column of 'inputIdx', followed by
// the actual text (from 'chrBefore" chars before the 'inputIdx', 
// to 'chrAfter' chars after 'inputIdx'.
int fontParsePrintInput(int inputIdx, int chrBefore, int chrAfter) {
	int line = 0, column = 0, i = 0, s;
	int il = s_inputLength-4;

	for (i = 0; (i < il) && (i < inputIdx); i++) {
		if (s_inputBuf[i] == '\n') {
			line++;
			column = 0;
		}
		else column++;
	}

	printf("line %d, column %d\n", line + 1, column + 1);
	if (il < inputIdx) {
		il += 4;
		if (il < inputIdx) {
			printf("fontParsePrintInput(): error: input idx '%d' out of input range (max = %d)!\n", inputIdx, il);
			return -1;
		}
	}

	if (column < chrBefore) chrBefore = column;
	if (inputIdx > 0) printf("...");
	s = i - chrBefore;
	for (i = s; ((i < s + chrBefore + 1 + chrAfter) && (s_inputBuf[i] != '\n') && (i < il)); i++) {
		printf("%c", ((s_inputBuf[i] >= ' ') && (s_inputBuf[i] <= '~')) ? s_inputBuf[i] : ' ');
	}
	printf("...\n");
	chrBefore += (inputIdx > 0) ? 3 : 0;
	printf("%*s\n", chrBefore + 1, "^");

	return 0;
}


#define YY_INPUT(buf,result,max_size) { \
	result = getInput(buf, max_size); \
}
%}

%{
static int toggleParseMode() {
//	printf("Parse mode toggle\n");
	s_parseModeStack = (int*)realloc(s_parseModeStack, sizeof(int) * (s_parseModeDepth + 1));
	s_parseModeStack[s_parseModeDepth++] = s_curlyDepth;
	s_parseMode = (s_parseMode == FPM_TXT) ? FPM_EQN : FPM_TXT;
	BEGIN s_parseMode;
	return 0;
}

static int openCurly() {
	s_curlyDepth++;
	return 0;
}

static int closeCurly() {
	s_curlyDepth--;
	if (s_parseModeDepth && 
		(s_curlyDepth == s_parseModeStack[s_parseModeDepth-1])) {
		s_parseModeDepth--;
		s_parseMode = (s_parseMode == FPM_TXT) ? FPM_EQN : FPM_TXT;
		BEGIN s_parseMode;
	}
	return 0;
}

int fontParseReset(const char *mode) {
	s_curlyDepth = s_parseModeDepth = 0;
	if ((mode[0] == 't') || (mode[0] == 'T')) s_parseMode = FPM_TXT;
	else if ((mode[0] == 'e') || (mode[0] == 'E')) s_parseMode = FPM_EQN;
	else {
		printf("fontParseReset(): warning: invalid parse mode '%s', assuming mode 'text'.\n", mode);
		s_parseMode = FPM_TXT;
	}

	if (s_parseModeStack) free(s_parseModeStack);
	s_parseModeStack = NULL;
	return 0;
}

%}


splchr [!@#$%^&*()\[\]\":;\-_=+\|'~`<,>./?]
backslash \\
curlyopen \{
curlyclose \}


%%

  int i, wsCnt;
[\t \n]+ 	 {
	wsCnt = 0;
	for (i = 0; i < yyleng; i++) {
		if (yytext[i] == '\t') wsCnt += 4; // a tab is 4 spaces
		else wsCnt++;
	}
	fontparselval.cnt.cnt = wsCnt;
	fontparselval.cnt.inputIdx = inputIdx();
	return WHITESPACE;
}

<FPM_TXT>\\eqn		{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	toggleParseMode(); return COMMAND;
}
<FPM_TXT>([a-zA-Z0-9]|[\-\_\+])+		{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	return WORD;
}
<FPM_TXT>\\ws	{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	toggleParseMode(); return COMMAND;
}
<FPM_TXT>\\scale	{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	toggleParseMode(); return COMMAND;
}
<FPM_TXT>\\newcolor	{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	toggleParseMode(); return COMMAND;
}

<FPM_EQN>\\txt		{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	toggleParseMode(); 
	return COMMAND;
}
<FPM_EQN>([a-zA-Z])+		{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	return WORD;
}
<FPM_EQN>(([0-9]+|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)?) {
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	return NUMBER;
}
<FPM_EQN>\^										{
	fontparselval.chr.chr = '^'; 
	fontparselval.chr.inputIdx = inputIdx();
	return SUPERSCRIPT;
}
<FPM_EQN>\_											{
	fontparselval.chr.chr = '_'; 
	fontparselval.chr.inputIdx = inputIdx();
	return SUBSCRIPT;
}
<FPM_EQN>{backslash}^						{
	fontparselval.chr.chr = '^'; 
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}
<FPM_EQN>{backslash}_						{
	fontparselval.chr.chr = '_';
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}

{backslash}{splchr}							{
	fontparselval.chr.chr = yytext[1]; 
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}
{backslash}{curlyopen}						{
	fontparselval.chr.chr = yytext[1]; 
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}
{backslash}{curlyclose}						{
	fontparselval.chr.chr = yytext[1]; 
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}
{backslash}eof {
	fontparselval.cnt.cnt = 0; 
	fontparselval.cnt.inputIdx = inputIdx();
	return ENDOFFILE;
}
{backslash}(([a-zA-Z]+)|{backslash})	{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	return COMMAND;
}
{backslash}([0-9]+)						{
	fontparselval.cnt.cnt = atoi(yytext + 1); 
	fontparselval.cnt.inputIdx = inputIdx();
	return COMMANDARG;
}

{splchr}									{
	fontparselval.chr.chr = yytext[0]; 
	fontparselval.chr.inputIdx = inputIdx();
	return SPECIALCHAR;
}
{curlyopen}									{
	openCurly(); 
	fontparselval.cnt.cnt = s_curlyDepth; 
	fontparselval.cnt.inputIdx = inputIdx();
	return OPENCURLY;
}
{curlyclose}								{
	fontparselval.cnt.cnt = s_curlyDepth; 
	fontparselval.cnt.inputIdx = inputIdx();
	closeCurly(); 
	return CLOSECURLY;
}
. 													{
	fontparselval.str.str = strdup(yytext); 
	fontparselval.str.inputIdx = inputIdx();
	return UNMATCHED;
}

%%

