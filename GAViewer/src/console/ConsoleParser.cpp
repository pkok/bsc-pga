/* $ANTLR 2.7.7 (20060906): "ConsoleParser.g" -> "ConsoleParser.cpp"$ */

#include <iostream>
#include <antlr/String.hpp>
#include "../state.h"
#include "console.h"
#include "consolescope.h"
#include "consolestatement.h"
#include "consolevariable.h"
using namespace std;

#include "ConsoleParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>

consoleScope *g_currentParsingScope = NULL;

ConsoleParser::ConsoleParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

ConsoleParser::ConsoleParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,3)
{
}

ConsoleParser::ConsoleParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

ConsoleParser::ConsoleParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,3)
{
}

ConsoleParser::ConsoleParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,3)
{
}

consoleStmtListStmt * ConsoleParser::input() {
	consoleStmtListStmt *cs;
	
		g_currentParsingScope = g_state->m_globalScope; // init scope
		consoleStmtListStmt *sl = NULL; cs = NULL;
		
	
	try {      // for error handling
		sl=stmtlist();
		cs = sl;
		match(ANTLR_USE_NAMESPACE(antlr)Token::EOF_TYPE);
		
				while (g_currentParsingScope && (g_currentParsingScope != g_state->m_globalScope))
					g_currentParsingScope = g_currentParsingScope->deleteScope();
		
			
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_0);
	}
	return cs;
}

consoleStmtListStmt * ConsoleParser::stmtlist() {
	consoleStmtListStmt *cs;
	cs = NULL;
		consoleStatement *s = NULL;
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((_tokenSet_1.member(LA(1)))) {
				s=stmt();
				
						if (s) {
							s->stmtListChild(1);
							if (cs) cs->addChild(s);
							else cs = new consoleStmtListStmt(s);
						}
			}
			else {
				goto _loop4;
			}
			
		}
		_loop4:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_2);
	}
	return cs;
}

consoleStatement * ConsoleParser::stmt() {
	consoleStatement *cs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t7 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t13 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t9 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t10 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t11 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t12 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	int verbose = 0; consoleExprListStmt *el = NULL; consoleStmtListStmt *sl = NULL; cs = NULL; int m = -1; string name;
	
	try {      // for error handling
		switch ( LA(1)) {
		case CURLYOPEN:
		{
			match(CURLYOPEN);
			cs=stmtlist();
			match(CURLYCLOSE);
			break;
		}
		case TK_return:
		{
			t3 = LT(1);
			match(TK_return);
			el=exprlist();
			match(SEMICOLON);
			cs = new consoleReturnStmt(t3->getLine(), t3->getColumn(), el);
			break;
		}
		case TK_break:
		{
			t4 = LT(1);
			match(TK_break);
			match(SEMICOLON);
			cs = new consoleBreakStmt(t4->getLine(), t4->getColumn(), 0);
			break;
		}
		case TK_continue:
		{
			t5 = LT(1);
			match(TK_continue);
			match(SEMICOLON);
			cs = new consoleBreakStmt(t5->getLine(), t5->getColumn(), 1);
			break;
		}
		case TK_suspend:
		{
			t6 = LT(1);
			match(TK_suspend);
			match(SEMICOLON);
			cs = new consoleBreakStmt(t6->getLine(), t6->getColumn(), 2);
			break;
		}
		case TK_dynamic:
		{
			t7 = LT(1);
			match(TK_dynamic);
			match(CURLYOPEN);
			{
			if ((LA(1) == IDENTIFIER) && (LA(2) == COLON)) {
				t13 = LT(1);
				match(IDENTIFIER);
				match(COLON);
			}
			else if ((_tokenSet_3.member(LA(1))) && (_tokenSet_4.member(LA(2)))) {
			}
			else {
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			
			}
			sl=stmtlist();
			match(CURLYCLOSE);
			if (sl) cs = new consoleDynStmt(t7->getLine(), t7->getColumn(), sl, (t13) ? t13->getText() : "");
			break;
		}
		case TK_inner_product:
		{
			t8 = LT(1);
			match(TK_inner_product);
			match(PAROPEN);
			t9 = LT(1);
			match(FUNCNAME);
			match(PARCLOSE);
			cs = new consoleSetStmt(t8->getLine(), t8->getColumn(), t8->getText(), t9->getText());
			break;
		}
		case TK_variable:
		{
			t12 = LT(1);
			match(TK_variable);
			name=funcDefName();
			match(SEMICOLON);
			g_currentParsingScope->setVariable(name); cs = new consoleDummyStmt(t12->getLine(), t12->getColumn());
			break;
		}
		case TK_while:
		{
			cs=while_();
			break;
		}
		case TK_for:
		{
			cs=for_();
			break;
		}
		case TK_if:
		{
			cs=if_();
			break;
		}
		case TK_switch:
		{
			cs=switch_();
			break;
		}
		case TK_function:
		case TK_batch:
		{
			cs=function();
			break;
		}
		default:
			if (((_tokenSet_5.member(LA(1))) && (_tokenSet_4.member(LA(2))) && (_tokenSet_6.member(LA(3))))&&((LA(1) != SEMICOLON) && (LA(1) != CURLYOPEN) && (LA(1) != COMMA) && 
	(LA(1) != TK_return) && (LA(1) != TK_break) && (LA(1) != TK_continue) && 
	(LA(1) != TK_suspend) && (LA(1) != TK_dynamic)  && (LA(1) != TK_while) && 
	(LA(1) != TK_if)  && (LA(1) != TK_switch) && (LA(1) != TK_for) &&
	(LA(1) != TK_function)  && (LA(1) != TK_batch))) {
				cs=exprlist();
				{
				switch ( LA(1)) {
				case COMMA:
				{
					match(COMMA);
					verbose =1;
					break;
				}
				case SEMICOLON:
				{
					match(SEMICOLON);
					break;
				}
				default:
				{
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				}
				}
				if (cs) cs->verbose(verbose);
			}
			else if ((LA(1) == SEMICOLON) && (_tokenSet_7.member(LA(2))) && (_tokenSet_8.member(LA(3)))) {
				t1 = LT(1);
				match(SEMICOLON);
				cs = new consoleDummyStmt(t1->getLine(), t1->getColumn());
			}
			else if ((LA(1) == COMMA) && (_tokenSet_7.member(LA(2))) && (_tokenSet_8.member(LA(3)))) {
				t2 = LT(1);
				match(COMMA);
				cs = new consoleDummyStmt(t2->getLine(), t2->getColumn());
			}
			else if ((LA(1) == TK_default_model) && (LA(2) == PAROPEN) && ((LA(3) >= TK_e3ga && LA(3) <= TK_c5ga))) {
				t10 = LT(1);
				match(TK_default_model);
				match(PAROPEN);
				m=model();
				match(PARCLOSE);
				cs = new consoleSetStmt(t10->getLine(), t10->getColumn(), t10->getText(), m);
			}
			else if ((LA(1) == TK_default_model) && (LA(2) == PAROPEN) && (LA(3) == PARCLOSE)) {
				t11 = LT(1);
				match(TK_default_model);
				match(PAROPEN);
				match(PARCLOSE);
				cs = new consoleSetStmt(t11->getLine(), t11->getColumn(), t11->getText(), -1);
			}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return cs;
}

consoleExprListStmt * ConsoleParser::exprlist() {
	consoleExprListStmt *el;
	el = NULL; consoleStatement *e;
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((_tokenSet_9.member(LA(1)))) {
				e=expr();
				
						if (el && e) el->addChild(e);
						else if (e) el = new consoleExprListStmt(e);
			}
			else {
				goto _loop19;
			}
			
		}
		_loop19:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_10);
	}
	return el;
}

int  ConsoleParser::model() {
	int m;
	m = -1;
	
	try {      // for error handling
		switch ( LA(1)) {
		case TK_e3ga:
		{
			match(TK_e3ga);
			return MVI_E3GA;
			break;
		}
		case TK_p3ga:
		{
			match(TK_p3ga);
			return MVI_P3GA;
			break;
		}
		case TK_c3ga:
		{
			match(TK_c3ga);
			return MVI_C3GA;
			break;
		}
		case TK_c5ga:
		{
			match(TK_c5ga);
			return MVI_C5GA;
			break;
		}
		case TK_i2ga:
		{
			match(TK_i2ga);
			return MVI_I2GA;
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_11);
	}
	return m;
}

string  ConsoleParser::funcDefName() {
	string s;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	s = "";
	
	try {      // for error handling
		switch ( LA(1)) {
		case IDENTIFIER:
		{
			t1 = LT(1);
			match(IDENTIFIER);
			s = t1->getText();
			break;
		}
		case FUNCNAME:
		{
			t2 = LT(1);
			match(FUNCNAME);
			s = t2->getText();
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_12);
	}
	return s;
}

consoleWhileStmt * ConsoleParser::while_() {
	consoleWhileStmt *ws;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ws = NULL; consoleExprListStmt *el = NULL; consoleStatement *s = NULL;
	
	try {      // for error handling
		t1 = LT(1);
		match(TK_while);
		match(PAROPEN);
		el=exprlist();
		match(PARCLOSE);
		s=stmt();
		ws = new consoleWhileStmt(t1->getLine(), t1->getColumn(), el, s);
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return ws;
}

consoleForStmt * ConsoleParser::for_() {
	consoleForStmt *fs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	fs = NULL; consoleExprListStmt *e1 = NULL, *e2 = NULL, *e3 = NULL; consoleStatement *s = NULL;
	
	try {      // for error handling
		t1 = LT(1);
		match(TK_for);
		match(PAROPEN);
		e1=exprlist();
		match(SEMICOLON);
		e2=exprlist();
		match(SEMICOLON);
		e3=exprlist();
		match(PARCLOSE);
		s=stmt();
		
				fs = new consoleForStmt(t1->getLine(), t1->getColumn(), e1, e2, e3, s);
			
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return fs;
}

consoleIfElseStmt * ConsoleParser::if_() {
	consoleIfElseStmt *ifs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ifs = NULL; consoleExprListStmt *e = NULL; consoleStatement *is = NULL, *es = NULL;
	
	try {      // for error handling
		t1 = LT(1);
		match(TK_if);
		match(PAROPEN);
		e=exprlist();
		match(PARCLOSE);
		is=stmt();
		{
		if ((LA(1) == TK_else) && (_tokenSet_1.member(LA(2))) && (_tokenSet_4.member(LA(3)))) {
			match(TK_else);
			es=stmt();
		}
		else if ((_tokenSet_7.member(LA(1))) && (_tokenSet_8.member(LA(2))) && (_tokenSet_6.member(LA(3)))) {
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
		}
		
				ifs = new consoleIfElseStmt(t1->getLine(), t1->getColumn(), e, is, es);
			
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return ifs;
}

consoleSwitchStmt * ConsoleParser::switch_() {
	consoleSwitchStmt *ss;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ss = NULL; consoleExprListStmt *e = NULL; consoleCaseListStmt *cl = NULL;
	
	try {      // for error handling
		t1 = LT(1);
		match(TK_switch);
		match(PAROPEN);
		e=exprlist();
		match(PARCLOSE);
		match(CURLYOPEN);
		cl=caselist();
		match(CURLYCLOSE);
		
				ss = new consoleSwitchStmt(t1->getLine(), t1->getColumn(), e, cl);
			
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return ss;
}

consoleStatement * ConsoleParser::function() {
	consoleStatement *fs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	fs = NULL; consoleFuncArgSpecListStmt *fasl = NULL; consoleStmtListStmt *sl = NULL; int f = 1; string name; int i; consoleFuncArgSpecStmt *fas = NULL; bool def = false;
	
	try {      // for error handling
		{
		switch ( LA(1)) {
		case TK_function:
		{
			t1 = LT(1);
			match(TK_function);
			f = 1;
			break;
		}
		case TK_batch:
		{
			t2 = LT(1);
			match(TK_batch);
			f = 0;
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		name=funcDefName();
		match(PAROPEN);
		{
		if ((((LA(1) >= IDENTIFIER && LA(1) <= TK_c5ga)))&&(LA(1) != PARCLOSE)) {
			fasl=funcargspeclist();
		}
		else if ((LA(1) == PARCLOSE)) {
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
		}
		match(PARCLOSE);
		
					g_currentParsingScope->setFunction(name); 
					g_currentParsingScope = new consoleScope(name.c_str(), g_currentParsingScope);
					i = 0; // add all names as variables
					while (fasl && (fas = fasl->argSpec(i++)))
						g_currentParsingScope->setVariable(fas->name());
				
		{
		switch ( LA(1)) {
		case CURLYOPEN:
		{
			match(CURLYOPEN);
			sl=stmtlist();
			def = true;
			match(CURLYCLOSE);
			break;
		}
		case SEMICOLON:
		{
			match(SEMICOLON);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		// { stmt1, stmt2, ... } or ;
				if (def) { // function definition
					fs = new consoleFuncStmt(((f) ? t1 : t2)->getLine(), ((f) ? t1 : t2)->getColumn(), name.c_str(), fasl, sl, f); 
				}
				else { // function declaration
					fs = new consoleFuncDeclStmt(((f) ? t1 : t2)->getLine(), ((f) ? t1 : t2)->getColumn(), name.c_str(), fasl, f);
				}
				g_currentParsingScope = g_currentParsingScope->deleteScope();
			
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_7);
	}
	return fs;
}

consoleCaseListStmt * ConsoleParser::caselist() {
	consoleCaseListStmt *ccl;
	consoleCaseStmt *cs = NULL; ccl = NULL;
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == TK_default || LA(1) == TK_case)) {
				cs=case_();
				
						if (ccl && cs) ccl->addChild(cs);
						else if (cs) ccl = new consoleCaseListStmt(cs->line(), cs->column(), cs);
			}
			else {
				goto _loop15;
			}
			
		}
		_loop15:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_13);
	}
	return ccl;
}

consoleCaseStmt * ConsoleParser::case_() {
	consoleCaseStmt *cs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	cs = NULL; consoleExprListStmt *el = NULL; consoleStmtListStmt *sl = NULL;
	
	try {      // for error handling
		if (((LA(1) == TK_case) && (_tokenSet_14.member(LA(2))) && (_tokenSet_15.member(LA(3))))&&((LA(4) != CURLYCLOSE) && (LA(4) != TK_case) && (LA(4) != TK_default))) {
			t1 = LT(1);
			match(TK_case);
			el=exprlist();
			match(COLON);
			sl=stmtlist();
			
					cs = new consoleCaseStmt(t1->getLine(), t1->getColumn(), el, sl);
				
		}
		else if ((LA(1) == TK_case) && (_tokenSet_14.member(LA(2))) && (_tokenSet_16.member(LA(3)))) {
			t2 = LT(1);
			match(TK_case);
			el=exprlist();
			match(COLON);
			
					cs = new consoleCaseStmt(t2->getLine(), t2->getColumn(), el, NULL);
				
		}
		else if (((LA(1) == TK_default) && (LA(2) == COLON) && (_tokenSet_17.member(LA(3))))&&((LA(4) != CURLYCLOSE) && (LA(4) != TK_case) && (LA(4) != TK_default))) {
			t3 = LT(1);
			match(TK_default);
			match(COLON);
			sl=stmtlist();
			
					cs = new consoleCaseStmt(t3->getLine(), t3->getColumn(), NULL, sl);
				
		}
		else if ((LA(1) == TK_default) && (LA(2) == COLON) && (LA(3) == TK_default || LA(3) == TK_case || LA(3) == CURLYCLOSE)) {
			t4 = LT(1);
			match(TK_default);
			match(COLON);
			
					cs = new consoleCaseStmt(t4->getLine(), t4->getColumn(), NULL, NULL);
				
		}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_18);
	}
	return cs;
}

consoleStatement * ConsoleParser::expr() {
	consoleStatement *cs;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t5 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t7 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  o = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t9 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  fn3 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  fn2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t10 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	cs = NULL; consoleArrayIdxListStmt *ail = NULL; consoleFuncArgListStmt *fal = NULL; consoleExprListStmt *el = NULL; consoleStatement *e = NULL; int m = -1;
	
	try {      // for error handling
		switch ( LA(1)) {
		case CONSTANT:
		{
			t1 = LT(1);
			match(CONSTANT);
			cs = new consoleConstantScalarStmt(t1->getLine(), t1->getColumn(), atof(t1->getText().c_str()));
			break;
		}
		case IDENTIFIER:
		{
			ail = NULL;
			t5 = LT(1);
			match(IDENTIFIER);
			{
			if (((_tokenSet_19.member(LA(1))) && (_tokenSet_6.member(LA(2))) && (_tokenSet_6.member(LA(3))))&&(LA(1) == SQUAREOPEN)) {
				ail=arrayidxlist();
			}
			else if ((_tokenSet_20.member(LA(1))) && (_tokenSet_6.member(LA(2))) && (_tokenSet_6.member(LA(3)))) {
			}
			else {
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			
			}
			cs = new consoleVariableStmt(t5->getLine(), t5->getColumn(), t5->getText().c_str(), 0, ail);
			break;
		}
		case OPERATOR:
		{
			o = LT(1);
			match(OPERATOR);
			e=expr();
			if (e) {e->setOp(NULL, o->getLine(), o->getColumn(), o->getText().c_str()); cs = e;}
			break;
		}
		case FUNCNAME:
		{
			fal = NULL;
			fn3 = LT(1);
			match(FUNCNAME);
			match(PAROPEN);
			{
			if (((_tokenSet_21.member(LA(1))) && (_tokenSet_22.member(LA(2))) && (_tokenSet_6.member(LA(3))))&&(LA(1) != PARCLOSE)) {
				fal=funcarglist();
				match(PARCLOSE);
			}
			else if ((LA(1) == PARCLOSE) && (_tokenSet_20.member(LA(2))) && (_tokenSet_6.member(LA(3)))) {
				match(PARCLOSE);
			}
			else {
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			
			}
			cs = new consoleFuncCallStmt(fn3->getLine(), fn3->getColumn(), fn3->getText().c_str(), fal, 0);
			break;
		}
		default:
			if ((LA(1) == GLOBAL) && (LA(2) == IDENTIFIER)) {
				ail = NULL;
				t6 = LT(1);
				match(GLOBAL);
				t7 = LT(1);
				match(IDENTIFIER);
				{
				if (((_tokenSet_19.member(LA(1))) && (_tokenSet_6.member(LA(2))) && (_tokenSet_6.member(LA(3))))&&(LA(1) == SQUAREOPEN)) {
					ail=arrayidxlist();
				}
				else if ((_tokenSet_20.member(LA(1))) && (_tokenSet_6.member(LA(2))) && (_tokenSet_6.member(LA(3)))) {
				}
				else {
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				
				}
				cs = new consoleVariableStmt(t6->getLine(), t6->getColumn(), t7->getText().c_str(), 1, ail);
			}
			else if ((LA(1) == PAROPEN) && (_tokenSet_23.member(LA(2)))) {
				t9 = LT(1);
				match(PAROPEN);
				el=exprlist();
				match(PARCLOSE);
				if (el) {cs = new consoleParExprStmt(t9->getLine(), t9->getColumn(), el);}
			}
			else if ((LA(1) == GLOBAL) && (LA(2) == FUNCNAME)) {
				fal = NULL;
				t8 = LT(1);
				match(GLOBAL);
				fn2 = LT(1);
				match(FUNCNAME);
				match(PAROPEN);
				{
				if (((_tokenSet_21.member(LA(1))) && (_tokenSet_22.member(LA(2))) && (_tokenSet_6.member(LA(3))))&&(LA(1) != PARCLOSE)) {
					fal=funcarglist();
					match(PARCLOSE);
				}
				else if ((LA(1) == PARCLOSE) && (_tokenSet_20.member(LA(2))) && (_tokenSet_6.member(LA(3)))) {
					match(PARCLOSE);
				}
				else {
					throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
				}
				
				}
				cs = new consoleFuncCallStmt(t8->getLine(), t8->getColumn(), fn2->getText().c_str(), fal, 1);
			}
			else if ((LA(1) == PAROPEN) && ((LA(2) >= TK_e3ga && LA(2) <= TK_c5ga))) {
				e = NULL;
				t10 = LT(1);
				match(PAROPEN);
				m=model();
				match(PARCLOSE);
				e=expr();
				
						if (e) cs = new consoleFuncCallStmt(t10->getLine(), t10->getColumn(), 
						(m == MVI_E3GA) ? "cast_e3ga" : ((m == MVI_P3GA) ? "cast_p3ga" : ((m == MVI_C3GA) ? "cast_c3ga" : ((m == MVI_C5GA) ? "cast_c5ga" : "cast_i2ga"))),
						new consoleFuncArgListStmt(new consoleExprListStmt(e)), 1); 
					
			}
		else {
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_20);
	}
	return cs;
}

consoleArrayIdxListStmt * ConsoleParser::arrayidxlist() {
	consoleArrayIdxListStmt *ail;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t1 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	consoleExprListStmt *el = NULL; ail = NULL;
	
	try {      // for error handling
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == SQUAREOPEN)) {
				t1 = LT(1);
				match(SQUAREOPEN);
				el=exprlist();
				t2 = LT(1);
				match(SQUARECLOSE);
				
						if (ail && el) ail->addChild(el);
						else if(el) ail = new consoleArrayIdxListStmt(t1->getLine(), t1->getColumn(), el);
			}
			else {
				goto _loop30;
			}
			
		}
		_loop30:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_20);
	}
	return ail;
}

consoleFuncArgListStmt * ConsoleParser::funcarglist() {
	consoleFuncArgListStmt *fal;
	consoleExprListStmt *el = NULL; fal = NULL;
	
	try {      // for error handling
		el=exprlist();
		if (el) fal = new consoleFuncArgListStmt(el); el = NULL;
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == COMMA)) {
				match(COMMA);
				el=exprlist();
				if (el) {if (fal) fal->addChild(el); else fal = new consoleFuncArgListStmt(el);} el=NULL;
			}
			else {
				goto _loop27;
			}
			
		}
		_loop27:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_11);
	}
	return fal;
}

consoleFuncArgSpecListStmt * ConsoleParser::funcargspeclist() {
	consoleFuncArgSpecListStmt *fasl;
	fasl = NULL; consoleFuncArgSpecStmt *fas = NULL;
	
	try {      // for error handling
		fas=argspec();
		if (fas) fasl = new consoleFuncArgSpecListStmt(fas->line(), fas->column(), fas); fas = NULL;
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == COMMA)) {
				match(COMMA);
				fas=argspec();
				
						if (fasl && fas) fasl->addChild(fas);
						else if (fas) fasl = new consoleFuncArgSpecListStmt(fas->line(), fas->column(), fas);
						fas = NULL;
						
			}
			else {
				goto _loop38;
			}
			
		}
		_loop38:;
		} // ( ... )*
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_11);
	}
	return fasl;
}

consoleFuncArgSpecStmt * ConsoleParser::argspec() {
	consoleFuncArgSpecStmt *fas;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t2 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t4 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t6 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t8 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  t10 = ANTLR_USE_NAMESPACE(antlr)nullToken;
	fas = NULL; string name;
	
	try {      // for error handling
		switch ( LA(1)) {
		case IDENTIFIER:
		case FUNCNAME:
		{
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(0, 0, name.c_str(), CVF_ANY_MODEL);
			break;
		}
		case TK_e3ga:
		{
			t2 = LT(1);
			match(TK_e3ga);
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(t2->getLine(), t2->getColumn(), name.c_str(), MVI_E3GA);
			break;
		}
		case TK_p3ga:
		{
			t4 = LT(1);
			match(TK_p3ga);
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(t4->getLine(), t4->getColumn(), name.c_str(), MVI_P3GA);
			break;
		}
		case TK_c3ga:
		{
			t6 = LT(1);
			match(TK_c3ga);
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(t6->getLine(), t6->getColumn(), name.c_str(), MVI_C3GA);
			break;
		}
		case TK_c5ga:
		{
			t8 = LT(1);
			match(TK_c5ga);
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(t6->getLine(), t8->getColumn(), name.c_str(), MVI_C5GA);
			break;
		}
		case TK_i2ga:
		{
			t10 = LT(1);
			match(TK_i2ga);
			name=funcDefName();
			fas = new consoleFuncArgSpecStmt(t10->getLine(), t10->getColumn(), name.c_str(), MVI_I2GA);
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_24);
	}
	return fas;
}

void ConsoleParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* ConsoleParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"an identifier",
	"a function",
	"e3ga typename",
	"p3ga typename",
	"c3ga typename",
	"i2ga typename",
	"c5ga typename",
	"\"return\"",
	"\"switch\"",
	"\"default\"",
	"\"case\"",
	"\"break\"",
	"\"continue\"",
	"\"suspend\"",
	"\"if\"",
	"\"else\"",
	"\"while\"",
	"\"for\"",
	"\"function\"",
	"\"batch\"",
	"\"dynamic\"",
	"\"inner_product\"",
	"\"default_model\"",
	"\"variable\"",
	"WS_",
	"operator",
	"ML_COMMENT",
	"SL_COMMENT",
	":",
	";",
	",",
	"(",
	")",
	"[",
	"]",
	"{",
	"}",
	"global",
	"QUOTED_STR_ESC",
	"an identifier",
	"INT",
	"a constant scalar",
	0
};

const unsigned long ConsoleParser::_tokenSet_0_data_[] = { 2UL, 0UL, 0UL, 0UL };
// EOF 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_0(_tokenSet_0_data_,4);
const unsigned long ConsoleParser::_tokenSet_1_data_[] = { 804755504UL, 8846UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME "return" "switch" "break" "continue" "suspend" "if" 
// "while" "for" "function" "batch" "dynamic" "inner_product" "default_model" 
// "variable" OPERATOR SEMICOLON COMMA PAROPEN CURLYOPEN GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_1(_tokenSet_1_data_,4);
const unsigned long ConsoleParser::_tokenSet_2_data_[] = { 24578UL, 256UL, 0UL, 0UL };
// EOF "default" "case" CURLYCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_2(_tokenSet_2_data_,4);
const unsigned long ConsoleParser::_tokenSet_3_data_[] = { 804755504UL, 9102UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME "return" "switch" "break" "continue" "suspend" "if" 
// "while" "for" "function" "batch" "dynamic" "inner_product" "default_model" 
// "variable" OPERATOR SEMICOLON COMMA PAROPEN CURLYOPEN CURLYCLOSE GLOBAL 
// CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_3(_tokenSet_3_data_,4);
const unsigned long ConsoleParser::_tokenSet_4_data_[] = { 805306354UL, 9150UL, 0UL, 0UL };
// EOF IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga "return" 
// "switch" "default" "case" "break" "continue" "suspend" "if" "else" "while" 
// "for" "function" "batch" "dynamic" "inner_product" "default_model" "variable" 
// OPERATOR SEMICOLON COMMA PAROPEN PARCLOSE SQUAREOPEN CURLYOPEN CURLYCLOSE 
// GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_4(_tokenSet_4_data_,4);
const unsigned long ConsoleParser::_tokenSet_5_data_[] = { 536870960UL, 8718UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR SEMICOLON COMMA PAROPEN GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_5(_tokenSet_5_data_,4);
const unsigned long ConsoleParser::_tokenSet_6_data_[] = { 805306354UL, 9215UL, 0UL, 0UL };
// EOF IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga "return" 
// "switch" "default" "case" "break" "continue" "suspend" "if" "else" "while" 
// "for" "function" "batch" "dynamic" "inner_product" "default_model" "variable" 
// OPERATOR COLON SEMICOLON COMMA PAROPEN PARCLOSE SQUAREOPEN SQUARECLOSE 
// CURLYOPEN CURLYCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_6(_tokenSet_6_data_,4);
const unsigned long ConsoleParser::_tokenSet_7_data_[] = { 805304370UL, 9102UL, 0UL, 0UL };
// EOF IDENTIFIER FUNCNAME "return" "switch" "default" "case" "break" "continue" 
// "suspend" "if" "else" "while" "for" "function" "batch" "dynamic" "inner_product" 
// "default_model" "variable" OPERATOR SEMICOLON COMMA PAROPEN CURLYOPEN 
// CURLYCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_7(_tokenSet_7_data_,4);
const unsigned long ConsoleParser::_tokenSet_8_data_[] = { 805306354UL, 9151UL, 0UL, 0UL };
// EOF IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga "return" 
// "switch" "default" "case" "break" "continue" "suspend" "if" "else" "while" 
// "for" "function" "batch" "dynamic" "inner_product" "default_model" "variable" 
// OPERATOR COLON SEMICOLON COMMA PAROPEN PARCLOSE SQUAREOPEN CURLYOPEN 
// CURLYCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_8(_tokenSet_8_data_,4);
const unsigned long ConsoleParser::_tokenSet_9_data_[] = { 536870960UL, 8712UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR PAROPEN GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_9(_tokenSet_9_data_,4);
const unsigned long ConsoleParser::_tokenSet_10_data_[] = { 0UL, 87UL, 0UL, 0UL };
// COLON SEMICOLON COMMA PARCLOSE SQUARECLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_10(_tokenSet_10_data_,4);
const unsigned long ConsoleParser::_tokenSet_11_data_[] = { 0UL, 16UL, 0UL, 0UL };
// PARCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_11(_tokenSet_11_data_,4);
const unsigned long ConsoleParser::_tokenSet_12_data_[] = { 0UL, 30UL, 0UL, 0UL };
// SEMICOLON COMMA PAROPEN PARCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_12(_tokenSet_12_data_,4);
const unsigned long ConsoleParser::_tokenSet_13_data_[] = { 0UL, 256UL, 0UL, 0UL };
// CURLYCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_13(_tokenSet_13_data_,4);
const unsigned long ConsoleParser::_tokenSet_14_data_[] = { 536870960UL, 8713UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR COLON PAROPEN GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_14(_tokenSet_14_data_,4);
const unsigned long ConsoleParser::_tokenSet_15_data_[] = { 804782064UL, 9151UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga "return" 
// "switch" "default" "case" "break" "continue" "suspend" "if" "while" 
// "for" "function" "batch" "dynamic" "inner_product" "default_model" "variable" 
// OPERATOR COLON SEMICOLON COMMA PAROPEN PARCLOSE SQUAREOPEN CURLYOPEN 
// CURLYCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_15(_tokenSet_15_data_,4);
const unsigned long ConsoleParser::_tokenSet_16_data_[] = { 536897520UL, 9017UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga "default" 
// "case" OPERATOR COLON PAROPEN PARCLOSE SQUAREOPEN CURLYCLOSE GLOBAL 
// CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_16(_tokenSet_16_data_,4);
const unsigned long ConsoleParser::_tokenSet_17_data_[] = { 804780080UL, 9102UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME "return" "switch" "default" "case" "break" "continue" 
// "suspend" "if" "while" "for" "function" "batch" "dynamic" "inner_product" 
// "default_model" "variable" OPERATOR SEMICOLON COMMA PAROPEN CURLYOPEN 
// CURLYCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_17(_tokenSet_17_data_,4);
const unsigned long ConsoleParser::_tokenSet_18_data_[] = { 24576UL, 256UL, 0UL, 0UL };
// "default" "case" CURLYCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_18(_tokenSet_18_data_,4);
const unsigned long ConsoleParser::_tokenSet_19_data_[] = { 536870960UL, 8831UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR COLON SEMICOLON COMMA PAROPEN PARCLOSE 
// SQUAREOPEN SQUARECLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_19(_tokenSet_19_data_,4);
const unsigned long ConsoleParser::_tokenSet_20_data_[] = { 536870960UL, 8799UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR COLON SEMICOLON COMMA PAROPEN PARCLOSE 
// SQUARECLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_20(_tokenSet_20_data_,4);
const unsigned long ConsoleParser::_tokenSet_21_data_[] = { 536870960UL, 8732UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR COMMA PAROPEN PARCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_21(_tokenSet_21_data_,4);
const unsigned long ConsoleParser::_tokenSet_22_data_[] = { 536872944UL, 8831UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME TK_e3ga TK_p3ga TK_c3ga TK_i2ga TK_c5ga OPERATOR 
// COLON SEMICOLON COMMA PAROPEN PARCLOSE SQUAREOPEN SQUARECLOSE GLOBAL 
// CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_22(_tokenSet_22_data_,4);
const unsigned long ConsoleParser::_tokenSet_23_data_[] = { 536870960UL, 8728UL, 0UL, 0UL };
// IDENTIFIER FUNCNAME OPERATOR PAROPEN PARCLOSE GLOBAL CONSTANT 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_23(_tokenSet_23_data_,4);
const unsigned long ConsoleParser::_tokenSet_24_data_[] = { 0UL, 20UL, 0UL, 0UL };
// COMMA PARCLOSE 
const ANTLR_USE_NAMESPACE(antlr)BitSet ConsoleParser::_tokenSet_24(_tokenSet_24_data_,4);


