#ifndef INC_ConsoleLexerTokenTypes_hpp_
#define INC_ConsoleLexerTokenTypes_hpp_

/* $ANTLR 2.7.7 (20060906): "ConsoleLexer.g" -> "ConsoleLexerTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API ConsoleLexerTokenTypes {
#endif
	enum {
		EOF_ = 1,
		IDENTIFIER = 4,
		FUNCNAME = 5,
		TK_e3ga = 6,
		TK_p3ga = 7,
		TK_c3ga = 8,
		TK_i2ga = 9,
		TK_c5ga = 10,
		TK_return = 11,
		TK_switch = 12,
		TK_default = 13,
		TK_case = 14,
		TK_break = 15,
		TK_continue = 16,
		TK_suspend = 17,
		TK_if = 18,
		TK_else = 19,
		TK_while = 20,
		TK_for = 21,
		TK_function = 22,
		TK_batch = 23,
		TK_dynamic = 24,
		TK_inner_product = 25,
		TK_default_model = 26,
		TK_variable = 27,
		WS_ = 28,
		OPERATOR = 29,
		ML_COMMENT = 30,
		SL_COMMENT = 31,
		COLON = 32,
		SEMICOLON = 33,
		COMMA = 34,
		PAROPEN = 35,
		PARCLOSE = 36,
		SQUAREOPEN = 37,
		SQUARECLOSE = 38,
		CURLYOPEN = 39,
		CURLYCLOSE = 40,
		GLOBAL = 41,
		QUOTED_STR_ESC = 42,
		ID = 43,
		INT = 44,
		CONSTANT = 45,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_ConsoleLexerTokenTypes_hpp_*/
