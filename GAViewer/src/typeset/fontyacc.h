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
extern YYSTYPE yylval;
