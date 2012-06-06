// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../state.h"
#include "console.h"
#include "consolefunction.h"
#include "consoleoperators.h"
#include "consolestatement.h"
#include "consolescope.h"
#include "consolevariable.h"

/* ******************************************************************* */

consoleStatement::consoleStatement() {
	initToNothing();
}

consoleStatement::consoleStatement(int line, int column) {
	initToNothing();
	lineAndColumn(line, column);
}

consoleStatement::consoleStatement(const consoleStatement &s) {
	initToNothing();
	lineAndColumn(s.line(), s.column());
	m_op = s.m_op;
	m_flags = s.m_flags;

	if (s.m_child) {
		for (int i = 0; i < s.m_nbChildren; i++)
			if (s.m_child[i]) addChild(s.m_child[i]->copy());
			else addChild(NULL);
	}
	
}

consoleStatement::~consoleStatement() {
	int i;

	if (m_child) {
		for (i = 0; i < m_nbChildren; i++)
			if (m_child[i]) delete m_child[i];
		free (m_child);
	}

	initToNothing();
}

void consoleStatement::initToNothing() {
	m_nbChildren = 0;
	m_child = NULL;
	m_op = 0;
	m_flags = 0;
	m_line = m_column = -1;
}

/*
int consoleStatement::usesVariable(const char *name, int global = 1  { // checks if global variable 'name' is used in this statement
	int i;
	for (i = 0; i < m_nbChildren; i++)
		if (m_child[i]) if (m_child[i]->usesVariable(name, global)) return 1;

	return 0;
}
*/

int consoleStatement::quote(const char *str) {
	int i = 0;
	while(str[i]) {
		if ((!isalnum(str[i])) && (str[i] != '_')) return 1;
		i++;
	}
	return 0;
}


int consoleStatement::getFlag(int flag) const {
	return (m_flags & flag);
}

int consoleStatement::setFlag(int flag, int val) {
	m_flags = (m_flags ^ (m_flags & flag)) | (val ? flag : 0);
	return 0;
}

int consoleStatement::addChild(consoleStatement *s) {
	if (s == (consoleStatement *)0xCCCCCCCC) {
		printf("alert  child %d is 0xCCCCCCCC!\n", m_nbChildren);
	}
	m_child = (consoleStatement**)realloc(m_child, sizeof(consoleStatement*) * (m_nbChildren + 1));
	m_child[m_nbChildren++] = s;
	return 0;
}

int consoleStatement::verbose(int v) {
	setFlag(CSF_VERBOSE, v);
	return 0;
}

int consoleStatement::verbose() {
	return getFlag(CSF_VERBOSE);
}

int consoleStatement::lhs(int l) {
	setFlag(CSF_LHS, l);
	return 0;
}

int consoleStatement::lhs() {
	return getFlag(CSF_LHS);
}

int consoleStatement::dummy() {
	return getFlag(CSF_DUMMY);
}

int consoleStatement::stmtListChild(int c) {
	setFlag(CSF_STMTLISTCHILD, c);
	return 0;
}

int consoleStatement::stmtListChild() {
	return getFlag(CSF_STMTLISTCHILD);
}

int consoleStatement::evalRequired() {
	return getFlag(CSF_EVALREQUIRED);
}

int consoleStatement::evalRequired(int e) {
	setFlag(CSF_EVALREQUIRED, e);
	return 0;
}

int consoleStatement::firstEval(int e) {
	setFlag(CSF_FIRSTEVAL, e);
	return 0;
}

int consoleStatement::firstEval() {
	return getFlag(CSF_FIRSTEVAL);
}


int consoleStatement::setOp(int op) {
	m_op = op;
	return 0;
}

int consoleStatement::setOp(const char *filename, int line, int column, const char *opStr) {
	char c, c2;
	int i;
	int op = 0;
	int opStrLen = strlen(opStr);


	// summarize operator list into integer 'op'
	// (CBO_X and CUO_X arguments are defined in consoleoperators.h)

	// skip over space
	i = 0;
	while ((opStr[i] > 0) && (opStr[i] <= ' ')) i++;
	
/*	if ((opStrLen >= (i + 2)) && (opStr[i + 0] == '/') && (opStr[i + 1] == '*')) {
//		printf("Begin long comment\n");
		BEGIN CMNTLONG;
	}
	else if ((opStrLen >= (i + 2)) && (opStr[i + 0] == '/') && (opStr[i + 1] == '/')) {
//		printf("Begin line comment\n");
		BEGIN CMNTLINE;
	}
	else {*/

		// the first non-space character determines the binary part, the rest is unary
		// the only exeption is when a '-' is used at the start of an expression (then it becomes unary)
		for (i = 0; (op == 0); i++) {
			c = opStr[i];
			if (c == 0) break;
			c2 = opStr[i+1];

			if ((c == ' ') || (c == '\t')) continue; // whitespace
			//if (c <= ' ') continue; // whitespace
			else if ((c == '=') && (c2 == '=')) {op = CBO_EQUAL; i++;}
			else if ((c == '!') && (c2 == '=')) {op = CBO_NE; i++;}
			else if ((c == '<') && (c2 == '=')) {op = CBO_LE; i++;}
			else if ((c == '>') && (c2 == '=')) {op = CBO_GE; i++;}
			else if ((c == '&') && (c2 == '&')) {op = CBO_AND; i++;}
			else if ((c == '|') && (c2 == '|')) {op = CBO_OR; i++;}
			else if (c == '=') op = CBO_ASSIGNMENT;
			else if (c == '<') op = CBO_LESS;
			else if (c == '>') op = CBO_GREATER;
			else if (c == '/') op = CBO_IGP;
			else if (c == '^') op = CBO_OP;
			else if (c == '.') op = CBO_IP;
			else if (c == '*') op = CBO_SCP;
			else if (c == '+') op = CBO_ADDITION;
			else if (c == '-') op = CBO_SUBTRACTION;
			else if (c == '&') op = CBO_MEET;
			else if (c == '|') op = CBO_JOIN;
			else break;
		}

		// summarize the unary operators
		for (;; i++) {
			c = opStr[i];
			if ((c == ' ') || (c == '\t') || (c == '\n')) continue;
			//if (c <= ' ') continue; // whitespace
			else if (c == '-') op ^= CUO_NEGATION;
			else if (c == '!') op ^= CUO_INVERSION;
			else if (c == '~') op ^= CUO_REVERSION;
			else if (c == 0) { // termination of loop
				setOp(op);
				return 0;
			}
			else {
				cprintf("Warning: %s%sline %d, column %d: ignoring non-unary operator '%d'\n", 
					(filename) ? filename : "", (filename) ? ": " : "", line, column, c);
				return -1;
			}
		}
//	}
}


/* ******************************************************************* */
consoleDummyStmt::consoleDummyStmt(int line, int column) : consoleStatement(line, column) {
	initToNothing();
	setFlag(CSF_DUMMY, 1);
}

consoleDummyStmt::consoleDummyStmt(const consoleDummyStmt &s) : consoleStatement(s) {
	initToNothing();
}


consoleStatement* consoleDummyStmt::copy() const  {
	return new consoleDummyStmt(*this);
}

consoleDummyStmt::~consoleDummyStmt() {
	initToNothing();
}

char *consoleDummyStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *str = (char*)malloc(5 + tl);
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';
	strcpy(str + i, (cr) ? ";\n" : ";");
	return str;
}

consoleVariable *consoleDummyStmt::execute(consoleScope *s) {
	return new consoleVariable("", e3ga(0.0));
}

void consoleDummyStmt::initToNothing() {
	
}


/* ******************************************************************* */

consoleVariableStmt::consoleVariableStmt(int line, int column, const char *name, int global /*= 0*/, consoleArrayIdxListStmt *arrayIdx /*= NULL*/) : consoleStatement(line, column) {
	initToNothing();

	m_name = strdup(name);
	m_global = global;

	addChild(arrayIdx);
}

consoleVariableStmt::consoleVariableStmt(const consoleVariableStmt &s) : consoleStatement(s) {
	m_name = strdup(s.m_name);
	m_global = s.m_global;
}


consoleStatement *consoleVariableStmt::copy() const {
	return new consoleVariableStmt(*this);
}

consoleVariableStmt::~consoleVariableStmt() {
	free(m_name);
	initToNothing();
}

char *consoleVariableStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *arrayStr = ((m_nbChildren > 0) && m_child[0]) ? m_child[0]->string(cr, tl) : strdup("");
	char *str = (char*)malloc(strlen(m_name) + strlen(arrayStr) + 10);
	const char *quotes = (quote(m_name)) ? "\"" : "";

	sprintf(str, "%s%s%s%s%s", (m_global) ? "::" : "", quotes, m_name, quotes, arrayStr);
	free(arrayStr);
	return str;
}

int consoleVariableStmt::getFullname(consoleScope *s, char *buf) {
	char idx[1024];

	if ((m_nbChildren > 0) && m_child[0]) {
		((consoleArrayIdxListStmt*)m_child[0])->execute(s, idx);
		sprintf(buf, "%s%s", m_name, idx);
	}
	else strcpy(buf, m_name);
	return 0;
}

consoleVariable *consoleVariableStmt::execute(consoleScope *s) {

	if (s->dynStmtVariableCollect() && (m_global || s->globalScope())) {
		s->dynStmtVariable(m_name);
	}

	char name[1024];
	getFullname(s, name);

	consoleVariable *result;
	s->lookupVariable(name, m_global, &result);
	if (result == NULL) {
		if (!lhs()) {
//			cprintf("Warning: variable '%s' does not exist. Assuming '%s = 0.0'\n", m_name, m_name);
		}
		result = new consoleVariable(name, e3ga(0.0));
		result->rhs(1);
		result->lhs(1);
	}
	result->global(m_global);
	return result;
}
/*
int consoleVariableStmt::usesVariable(const char *name, int global = 1) {
	if (global || m_global) { // compare name with this
		if (!strcmp(name, m_name)) return 1;

		// strip array indices from name & compare again
		char nameStriped[1024], *ptr;
		if (ptr = strchr(name, '[')) {
			memcpy(nameStriped, name, ptr - name);
			nameStriped[ptr - name] = 0;
			if (!strcmp(nameStriped, m_name)) return 1;

		}
	}
	return consoleStatement::usesVariable(name, global);
}
*/

void consoleVariableStmt::initToNothing() {
	m_global = 0;
	m_op = 0;
	m_name = NULL;
}

/* ******************************************************************* */

consoleConstantScalarStmt::consoleConstantScalarStmt(int line, int column, double d) : consoleStatement(line, column) {
	initToNothing();
	m_value = d;
}

consoleConstantScalarStmt::consoleConstantScalarStmt(const consoleConstantScalarStmt &s) : consoleStatement(s) {
	initToNothing();
	m_value = s.m_value;
}

consoleStatement *consoleConstantScalarStmt::copy() const {
	return new consoleConstantScalarStmt(*this);
}

consoleConstantScalarStmt::~consoleConstantScalarStmt() {
	initToNothing();
}

char *consoleConstantScalarStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *str = (char*)malloc(256);
	sprintf(str, "%f", m_value);
	return str;
}

consoleVariable *consoleConstantScalarStmt::execute(consoleScope *s) {
	char str[256];
	sprintf(str, "%f", m_value);
	
	consoleVariable *result;
	switch (s->getDefaultModel()) {
	case MVI_P3GA:
		result = new consoleVariable(str, p3ga(m_value));
		break;
	case MVI_C3GA:
		result = new consoleVariable(str, c3ga(m_value));
		break;
	case MVI_C5GA:
		result = new consoleVariable(str, c5ga(m_value));
		break;
	case MVI_I2GA:
		result = new consoleVariable(str, i2ga(m_value));
		break;
	default:
		result = new consoleVariable(str, e3ga(m_value));
		break;
	}

	result->rhs(1);
	result->lhs(0);
	return result;
}

void consoleConstantScalarStmt::initToNothing() {
	m_value = 0.0;
}

/* ******************************************************************* */

consoleFuncArgListStmt::consoleFuncArgListStmt(consoleExprListStmt *el) : consoleStatement(el->line(), el->column()) {
	initToNothing();
	addChild(el);
}

consoleFuncArgListStmt::consoleFuncArgListStmt(const consoleFuncArgListStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleFuncArgListStmt::copy() const {
	return new consoleFuncArgListStmt(*this);
}

consoleFuncArgListStmt::~consoleFuncArgListStmt() {

	initToNothing();
}
char *consoleFuncArgListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));
	int i, l = 0;
	for (i = 0; i < m_nbChildren; i++) {
		childStr[i] = m_child[i]->string(cr, tl);
		l += strlen(childStr[i]) + 10;
	}
	char *str = (char*)malloc(l + 1), *strPtr;
	strPtr = str;
	for (i = 0; i < m_nbChildren; i++) {
		strPtr += sprintf(strPtr, "%s%s", childStr[i], (i == (m_nbChildren-1)) ? "" : ", ");
		free(childStr[i]);
	}
	free(childStr);
	return str;
}

consoleVariable *consoleFuncArgListStmt::execute(consoleScope *s) {
	consoleVariable *result = NULL;
	consoleVariable *cv, *cvPrev = NULL;

	int i;
	for (i = 0; i < m_nbChildren; i++) {
		cv = m_child[i]->execute(s);
		if (result == NULL) result = cv;
		if (cvPrev) cvPrev->next(cv);
		cvPrev = cv;
	}
	return result;
}

/*consoleStatement *consoleFuncArgListStmt::removeDynStmt() {
	consoleStatement *stmt = NULL;
	if (m_nbChildren > 0) {
		stmt = m_child[0];
		m_child[0] = NULL;
	}
	return stmt;
}*/


void consoleFuncArgListStmt::initToNothing() {

}



/* ******************************************************************* */

consoleFuncCallStmt::consoleFuncCallStmt(int line, int column, const char *name, consoleFuncArgListStmt *arg, int global) : consoleStatement(line, column) {
	initToNothing();
	if (arg) addChild(arg);
	m_name = strdup(name);
	m_global = global;
}

consoleFuncCallStmt::consoleFuncCallStmt(const consoleFuncCallStmt &s) : consoleStatement(s) {
	initToNothing();
	m_name = strdup(s.m_name);
	m_global = s.m_global;

}

consoleStatement *consoleFuncCallStmt::copy() const {
	return new consoleFuncCallStmt(*this);
}

consoleFuncCallStmt::~consoleFuncCallStmt() {
	free(m_name);
	initToNothing();
}

void consoleFuncCallStmt::initToNothing() {
	m_name = NULL;
	m_global = 0;
}

char *consoleFuncCallStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *argStr = ((m_nbChildren == 1) && m_child[0]) ? m_child[0]->string(cr, tl) : strdup("");
	char *str = (char*)malloc(strlen(argStr) + strlen(m_name) + 12);
	const char *quotes = (quote(m_name)) ? "\"" : "";

	sprintf(str, "%s%s%s(%s)", quotes, m_name, quotes, argStr);
	free(argStr);
	return str;
}

consoleVariable *consoleFuncCallStmt::execute(consoleScope *s_in) {
	consoleVariable *cv = NULL;
	if (argList()) cv = argList()->execute(s_in);

	consoleVariable *result = consoleExecFunc(s_in, m_name, cv);

	return result;
}

/* ******************************************************************* */


consoleExprListStmt::consoleExprListStmt(consoleStatement *expr) : consoleStatement(expr->line(), expr->column()) {
	initToNothing();
	addChild(expr);
}

consoleExprListStmt::consoleExprListStmt(const consoleExprListStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleExprListStmt::copy() const {
	return new consoleExprListStmt(*this);
}

consoleExprListStmt::~consoleExprListStmt() {
	initToNothing();
}

void consoleExprListStmt::initToNothing() {
}

static char *s_opStrings[] = {
	(char*)" ", //CBO_GP 0 // 'space' (implicit, doesn't exist)
	(char*)"= ", //#define CBO_ASSIGNMENT 1 // '='
	(char*)"/ ", // CBO_IGP 2 // '/'
	(char*)"^ ", // CBO_OP 3 // '^'
	(char*)". ", // CBO_IP 4 // '.'
	(char*)"* ", // CBO_SCP 5 // '*'
	(char*)"+ ", // CBO_ADDITION 6 // '+'
	(char*)"- ", // CBO_SUBTRACTION 7 // '-'
	(char*)"& ", // CBO_MEET 8 // '&'
	(char*)"| ", // CBO_JOIN 9 // '|'
	(char*)"== ", // CBO_EQUAL 10 // '=='
	(char*)"< ", // CBO_LESS 11 // '<'
	(char*)"> ", // CBO_GREATER 12 // '>'
	(char*)"<= ", // CBO_LE 13 // '<='
	(char*)">= ", // CBO_GE 14 // '>='
	(char*)"&& ", // CBO_AND 15 // '&&'
	(char*)"|| ",  // CBO_OR 16 // '||'
	(char*)"!= " // CBO_NE 17 
};

char *consoleExprListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));
	int i, l = 0;

	// get all child strings
	for (i = 0; i < m_nbChildren; i++) {
		if (m_child[i]) {
			childStr[i] = m_child[i]->string(cr, tl);
//			printf("Child ops: %d\n", m_child[i]->op());
		}
		else childStr[i] = strdup("");
		l += strlen(childStr[i]) + 5;
	}
	char *str = (char*)malloc(l + tl + 10), *strPtr = str;

	// print tabs
	if (stmtListChild()) {
		for (i = 0; i < tl; i++) str[i] = '\t';
		strPtr += tl;
	}

	// print children
	for (i = 0; i < m_nbChildren; i++) {
		int o = (m_child[i]) ? m_child[i]->op() : 0;

		if ((o & CBO_MASK) - CBO_GP) strPtr += sprintf(strPtr, s_opStrings[(o & CBO_MASK) - CBO_GP]);

		if (o & CUO_NEGATION) strPtr += sprintf(strPtr, "-");
		if (o & CUO_INVERSION) strPtr += sprintf(strPtr, "!");
		if (o & CUO_REVERSION) strPtr += sprintf(strPtr, "~");


		strPtr += sprintf(strPtr, "%s%s", childStr[i], (i == (m_nbChildren-1)) ? "" : " ");
		free(childStr[i]);
	}
	free(childStr);

	if (stmtListChild()) {// print curly brace 
		strPtr += sprintf(strPtr, "%s%s", (verbose()) ? "," : ";",  (cr) ? "\n" : "");
	}

	return str;
}

consoleVariable *consoleExprListStmt::execute(consoleScope *s) {
	consoleVariable *cvStart = NULL, *cv, *cvPrev = NULL;
	int i;

	// execute a list of expressions, connected by operators, chain them
	for (i = 0; i < m_nbChildren; i++) {
		if (m_child[i] == NULL) continue;

		if (i < m_nbChildren - 1) { // if next op is assignment, then tell this to the current child, so it will not complain about non-existence
			if (m_child[i+1] && ((m_child[i+1]->op() & CBO_MASK) == CBO_ASSIGNMENT))
				m_child[i]->lhs(1);
		}
		cv = m_child[i]->execute(s);
		cv->op((m_child[i])->op());
		if (cvStart == NULL) cvStart = cv;
		if (cvPrev) cvPrev->next(cv);
		cvPrev = cv;
	}

	return consoleEvalExprList(s, cvStart);
}

/* ******************************************************************* */

consoleParExprStmt::consoleParExprStmt(int line, int column, consoleExprListStmt *el) : consoleStatement(line, column) {
	initToNothing();
	addChild(el);
}

consoleParExprStmt::consoleParExprStmt(const consoleParExprStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleParExprStmt::copy() const {
	return new consoleParExprStmt(*this);
}

consoleParExprStmt::~consoleParExprStmt() {
	initToNothing();
}

void consoleParExprStmt::initToNothing() {
}


char *consoleParExprStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *childStr;
	int i, l = 0;

	if (m_child[0]) childStr = m_child[0]->string(cr, tl);
	else childStr = strdup("");
	l = strlen(childStr);

	char *str = (char*)malloc(l + tl + 10), *strPtr = str;

	// print tabs
	if (stmtListChild()) {
		for (i = 0; i < tl; i++) str[i] = '\t';
		strPtr += tl;
	}

	strPtr += sprintf(strPtr, "(%s)", childStr);

	free(childStr);

	if (stmtListChild()) {// print curly brace 
		strPtr += sprintf(strPtr, "%s%s", (verbose()) ? "," : ";",  (cr) ? "\n" : "");
	}

	return str;
}

consoleVariable *consoleParExprStmt::execute(consoleScope *s) {
	if (m_child[0]) return m_child[0]->execute(s);
	else return new consoleVariable("", e3ga(0.0));
}


/* ******************************************************************* */

consoleWhileStmt::consoleWhileStmt(int line, int column, consoleExprListStmt *el, 
								   consoleStatement *sl) : consoleStatement(line, column) {
	initToNothing();
	addChild(el);
	addChild(sl);
}

consoleWhileStmt::consoleWhileStmt(const consoleWhileStmt &s) : consoleStatement(s) {
	initToNothing();	
}


consoleStatement *consoleWhileStmt::copy() const {
	return new consoleWhileStmt(*this);
}

consoleWhileStmt::~consoleWhileStmt() {

	initToNothing();
}

char *consoleWhileStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	int i;
	consoleExprListStmt *c = condEl();
	consoleStatement *st = stmt();
	
	// get condition and statement list strings
	char *condStr = (c) ? c->string(cr, tl) : strdup("1");
	char *stmtStr = (st) ? st->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");

	char *str = (char*)malloc(strlen(condStr) + strlen(stmtStr) + 32 + tl);

	// print tabs
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "while(%s) {%s}%s", condStr, stmtStr, (cr) ? "\n" : "");

	free(condStr);
	free(stmtStr);

	return str;
}

consoleVariable *consoleWhileStmt::execute(consoleScope *s_in) {
	consoleVariable *cv, *result;
	int cond;

	consoleScope *s = s_in->subScope();

	consoleExprListStmt *c = condEl();
	consoleStatement *st = stmt();

	while (1) {
		// switch break & continue off for the conditional
		s->breakStmtAllowed(0);
		s->continueStmtAllowed(0);

		// check condition
		cond = 1;
		if (c) {
			cv = c->execute(s);
			cond = cv->isTrue();
			delete cv;
			cv = NULL;
		}
		if (cond == 0) break;

		// switch break & continue on for the main statement
		s->breakStmtAllowed(1);
		s->continueStmtAllowed(1);

		// execute the main statement
		if (st) {
			result = st->execute(s);
			if (s->returnStmt()) break;

			delete result; result = NULL;

			if (s->breakStmt()) {
				s->breakStmt(0); //clear the break
				break; // :)
			}
			else if (s->continueStmt()) {
				s->continueStmt(0); //clear the continue
				continue; // :)
			}

		}
	}

	// switch break & continue off
	s->breakStmtAllowed(0);
	s->continueStmtAllowed(0);

	delete s;

	return (result) ? result : new consoleVariable("", e3ga(0.0));
}

void consoleWhileStmt::initToNothing() {
}

/* ******************************************************************* */

consoleForStmt::consoleForStmt(int line, int column, consoleExprListStmt *p_initEl, consoleExprListStmt *p_condEl, 
							   consoleExprListStmt *p_execEl, consoleStatement *sl) : consoleStatement(line, column) {
	initToNothing();

	m_initEl = p_initEl;
	m_condEl = p_condEl;
	m_execEl = p_execEl;
	addChild(sl);
}

consoleForStmt::consoleForStmt(const consoleForStmt &s) : consoleStatement(s) {
	initToNothing();
	m_initEl = (consoleExprListStmt*) ((s.initEl()) ? s.initEl()->copy() : NULL);
	m_condEl = (consoleExprListStmt*) ((s.condEl()) ? s.condEl()->copy() : NULL);
	m_execEl = (consoleExprListStmt*) ((s.execEl()) ? s.execEl()->copy() : NULL);	
}

consoleStatement *consoleForStmt::copy() const {
	return new consoleForStmt(*this);
}

consoleForStmt::~consoleForStmt() {
	delete m_initEl;
	delete m_condEl;
	delete m_execEl;

	initToNothing();
}

char *consoleForStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	int i;
	consoleExprListStmt *in = initEl(), *c = condEl(), *e = execEl();
	consoleStatement *st = stmt();

	// get all the strings strings
	char *initStr = (in) ? in->string(cr, tl) : strdup("");
	char *condStr = (c) ? c->string(cr, tl) : strdup("");
	char *execStr = (e) ? e->string(cr, tl) : strdup("");
	char *stmtStr = (st) ? st->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");

	char *str = (char*)malloc(strlen(initStr) + strlen(condStr) + strlen(execStr) + strlen(stmtStr) + 48 + 2 * tl), *strPtr = str;

	char *tabStr = (char*)malloc(tl + 1);

	// print tabs
	for (i = 0; i < tl; i++) tabStr[i] = '\t';
	tabStr[i] = 0;

	strPtr += sprintf(strPtr, "%sfor (%s; %s; %s) {%s%s%s}%s", tabStr, initStr, condStr, execStr, (cr) ? "\n" : "", stmtStr, tabStr, (cr) ? "\n" : "");

	free(tabStr);
	free(initStr);
	free(condStr);
	free(execStr);
	free(stmtStr);

	return str;
}

consoleVariable *consoleForStmt::execute(consoleScope *s_in) {
	consoleVariable *cv;
	int cond, b;

	consoleScope *s = s_in->subScope();

	// execute initialization
	if (initEl()) {
		cv = initEl()->execute(s);
		delete cv;
		cv = NULL;
	}

	// do the loop
	consoleExprListStmt *c = condEl(), *e = execEl();
	consoleStatement *st = stmt();
	for (;;) {
		// check condition
		cond = 1;
		if (c) {
			cv = c->execute(s);
			cond = cv->isTrue();
			delete cv;
			cv = NULL;
		}
		if (cond == 0) break;

		// switch break & continue on for the main statement
		s->breakStmtAllowed(1);
		s->continueStmtAllowed(1);

		// execute the main statement
		if (st) {
			cv = st->execute(s);

			if (s->returnStmt()) {break;} // this will return cv;

			delete cv;
			cv = NULL;

			if ( (b = s->breakStmt()) || s->continueStmt()) { //  continue or break loop
				s->breakStmt(0); s->continueStmt(0); // clear the break / continue

				if (b) break; // :)
				else {
					// leaving main statement: switch break & continue off
					s->breakStmtAllowed(0);
					s->continueStmtAllowed(0);
					// don't break or continue here, or else the loop expression below won't get executed
				}
			}
		}

		// leaving main statement: switch break & continue off
		s->breakStmtAllowed(0);
		s->continueStmtAllowed(0);

		// execute the loop expression
		if  (e) {
			cv = e->execute(s);
			delete cv;
			cv = NULL;
		}
	}

	// leaving main statement: switch break & continue off
	s->breakStmtAllowed(0);
	s->continueStmtAllowed(0);

	delete s;

	return (cv) ? cv : new consoleVariable("", e3ga(0.0));
}

void consoleForStmt::initToNothing() {
}

/* ******************************************************************* */

consoleIfElseStmt::consoleIfElseStmt(int line, int column, consoleExprListStmt *el, consoleStatement *ifS, 
									 consoleStatement *elseS /*= NULL*/) : consoleStatement(line, column) {
	initToNothing();
	addChild(el);
	addChild(ifS);
	if (elseS) addChild(elseS);
}

consoleIfElseStmt::consoleIfElseStmt(const consoleIfElseStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleIfElseStmt::copy() const {
	return new consoleIfElseStmt(*this);
}

consoleIfElseStmt::~consoleIfElseStmt() {

	initToNothing();
}

char *consoleIfElseStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	int i;
	consoleStatement *c = condStmt(), *ifs = ifStmt(), *els = elseStmt();

	// get all the strings strings
	char *condStr = (c) ? c->string(cr, tl) : strdup("");
	char *ifStr = (ifs) ? ifs->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");
	char *elseStr = (els) ? els->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");
	char *tabStr = (char*)malloc(tl + 1);

	// print tabs
	for (i = 0; i < tl; i++) tabStr[i] = '\t';
	tabStr[i] = 0;

	char *str = (char*)malloc(strlen(condStr) + strlen(ifStr) + strlen(elseStr) + 32 + tl * 2), *strPtr = str;;

	if (els) {
		strPtr += sprintf(strPtr, "%sif (%s) {%s%s%s}%s", tabStr, condStr, (cr) ? "\n" : "", ifStr, tabStr, (cr) ? "\n" : "");
		strPtr += sprintf(strPtr, "%selse {%s%s%s}%s", tabStr, (cr) ? "\n" : "", elseStr, tabStr, (cr) ? "\n" : "");
	}
	else {
		strPtr += sprintf(strPtr, "%sif (%s) {%s%s%s}%s", tabStr, condStr, (cr) ? "\n" : "", ifStr, tabStr, (cr) ? "\n" : "");
	}

	free(condStr);
	free(ifStr);
	free(elseStr);
	free(tabStr);

	return str;
}

consoleVariable *consoleIfElseStmt::execute(consoleScope *s) {
	// evaluate condition
	consoleStatement *c = condStmt();
	consoleVariable *condCv = c->execute(s);
	int cond = condCv->isTrue();
	delete condCv;

	// execute the if or the else part
	consoleStatement *e;
	if (cond) e = ifStmt();
	else e = elseStmt();

	if (e) return e->execute(s);
	else return new consoleVariable("", e3ga(0.0));
}

void consoleIfElseStmt::initToNothing() {
}

/* ******************************************************************* */
consoleSwitchStmt::consoleSwitchStmt(int line, int column, consoleExprListStmt *cond, consoleCaseListStmt *caseList) : consoleStatement(line, column) {
	initToNothing();
	addChild(cond);
	addChild(caseList);
}

consoleSwitchStmt::consoleSwitchStmt(const consoleSwitchStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleSwitchStmt::copy() const {
	return new consoleSwitchStmt(*this);
}

consoleSwitchStmt::~consoleSwitchStmt() {

	initToNothing();
}

char *consoleSwitchStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	consoleExprListStmt *cond = condStmt();
	consoleCaseListStmt *caseList = caseListStmt();

	char *condStr = cond->string(cr, tl);
	char *caseListStr = caseList->string(cr, tl);

	char *str = (char*)malloc(strlen(condStr) + strlen(caseListStr) + 32 + tl * 2), *strPtr = str;

	// print tabs
	char *tabStr = (char*)malloc(tl + 1);
	int i;
	for (i = 0; i < tl; i++) tabStr[i] = '\t';
	tabStr[i] = 0;

	// print string
	strPtr += sprintf(strPtr, "%sswitch (%s) {%s%s%s}%s", tabStr, condStr, (cr) ? "\n" : "", caseListStr, tabStr, (cr) ? "\n" : "");

	free(tabStr);
	free(condStr);
	free(caseListStr);

	return str;
}

consoleVariable *consoleSwitchStmt::execute(consoleScope *s) {
	consoleExprListStmt *cond = condStmt();
	consoleCaseListStmt *caseList = caseListStmt();
	consoleCaseStmt *c;
	consoleVariable *result = NULL;

	consoleVariable *condCv = cond->execute(s);
	
	int i = 0, xInner, xOuter = 0;
	while (c = caseList->caseStmt(i)) {
		consoleExprListStmt *caseCond = c->exprListStmt();

		s->breakStmtAllowed(0);

		xInner = 1;
		if ((!xOuter) && caseCond) {
			consoleVariable *caseCondCv = caseCond->execute(s);
			caseCondCv->next(new consoleVariable("", condCv));
			consoleVariable *xCv = consoleExecFunc(s, "equal", caseCondCv); // this deletes both caseCondCv and 'new consoleVariable(condCv)'
			xInner = xCv->isTrue();
			delete xCv;
		}

		// allow break for the main statements
		s->breakStmtAllowed(1);

		if (xInner || xOuter) {
			consoleStmtListStmt *sl;
//			consoleVariable *result;

			if (sl = c->stmtListStmt()) {
				result = c->stmtListStmt()->execute(s);
				if (s->returnStmt()) break; // this will return result

				delete result; 
				result = NULL;
			}

			if (s->breakStmt()) {
				s->breakStmt(0); //clear the break
				break;
			}
			else {
				xOuter = 1; // exec all until break;
			}
		}
		i++;
	}

	s->breakStmtAllowed(0);

	delete condCv;

	return (result) ? result : new consoleVariable("", e3ga(0.0));
}

void consoleSwitchStmt::initToNothing() {
}

/* ******************************************************************* */

consoleCaseStmt::consoleCaseStmt(int line, int column, consoleExprListStmt *caseStmt, consoleStmtListStmt* stmtList) : consoleStatement(line, column) {
	initToNothing();

	addChild(caseStmt);
	addChild(stmtList);
}

consoleCaseStmt::consoleCaseStmt(const consoleCaseStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleCaseStmt::copy() const {
	return new consoleCaseStmt(*this);
}

consoleCaseStmt::~consoleCaseStmt() {

	initToNothing();
}

char *consoleCaseStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	consoleStatement *el = exprListStmt();
	consoleStatement *st = stmtListStmt();

	char *elStr = (el) ? el->string(cr, tl) : strdup("");
	char *stStr = (st) ? st->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");
	char *str = (char*)malloc(strlen(elStr) + strlen(stStr) + 32);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "%s%s: %s%s", (el) ? "case " :  "default", elStr, (cr) ? "\n" : "", stStr);

	free(elStr);
	free(stStr);

	return str;
}

consoleVariable *consoleCaseStmt::execute(consoleScope *s) {
	return NULL; // does nothing
}

void consoleCaseStmt::initToNothing() {
}


/* ******************************************************************* */

consoleCaseListStmt::consoleCaseListStmt(int line, int column, consoleCaseStmt *caseStmt) : consoleStatement(line, column) {
	initToNothing();
	addChild(caseStmt);
}

consoleCaseListStmt::consoleCaseListStmt(const consoleCaseListStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleCaseListStmt::copy() const {
	return new consoleCaseListStmt(*this);
}

consoleCaseListStmt::~consoleCaseListStmt() {

	initToNothing();
}

char *consoleCaseListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));

	int i, l = 0;

	// get all child strings
	for (i = 0; i < m_nbChildren; i++) {
		childStr[i] = (m_child[i]) ? m_child[i]->string(cr, tl) : strdup("");
		l += strlen(childStr[i]) + 2;
	}
	char *str = (char*)malloc(l + 1), *strPtr = str;

	// print children
	for (i = 0; i < m_nbChildren; i++) {
		strPtr += sprintf(strPtr, "%s", childStr[i]);
		free(childStr[i]);
	}
	free(childStr);
	return str;
}

consoleVariable *consoleCaseListStmt::execute(consoleScope *s) {
	return NULL; // does nothing
}

void consoleCaseListStmt::initToNothing() {
}


/* ******************************************************************* */

consoleReturnStmt::consoleReturnStmt(int line, int column, consoleExprListStmt *expr) : consoleStatement(line, column) {
	initToNothing();

	addChild(expr);
}

consoleReturnStmt::consoleReturnStmt(const consoleReturnStmt &s) : consoleStatement(s) {
	initToNothing();
}


consoleStatement *consoleReturnStmt::copy() const {
	return new consoleReturnStmt(*this);
}

consoleReturnStmt::~consoleReturnStmt() {

	initToNothing();
}

void consoleReturnStmt::initToNothing() {
}

char *consoleReturnStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *childStr = (m_child[0]) ? m_child[0]->string(cr, tl) : strdup("");

	char *str = (char*)malloc(strlen(childStr) + 32 + tl);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "return %s%c%s", childStr, verbose() ? ',' : ';', (cr) ? "\n" : "");

	free(childStr);

	return str;
}

consoleVariable *consoleReturnStmt::execute(consoleScope *s) {
	s->returnStmt(1);
	return (m_child[0]) ? m_child[0]->execute(s) : new consoleVariable("", e3ga(0.0));
}

/* ******************************************************************* */

consoleBreakStmt::consoleBreakStmt(int line, int column, int type) : consoleStatement(line, column) {
	initToNothing();

	m_type = type;
}

consoleBreakStmt::consoleBreakStmt(const consoleBreakStmt &s) : consoleStatement(s) {
	initToNothing();
	m_type = s.m_type;
}

consoleStatement *consoleBreakStmt::copy() const {
	return new consoleBreakStmt(*this);
}

consoleBreakStmt::~consoleBreakStmt() {

	initToNothing();
}

void consoleBreakStmt::initToNothing() {
	m_type = 0;
}

char *consoleBreakStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char *str = (char*)malloc(16 + tl);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	char *brStr;
	switch(m_type) {
	case CBS_CONTINUE:
		brStr = (char*)"continue";
		break;
	case CBS_BREAK:
		brStr = (char*)"continue";
		break;
	case CBS_SUSPEND:
		brStr = (char*)"suspend";
		break;
	default:
		brStr = (char*)"unkn br";
		break;
	}

	sprintf(str + i, "%s;%s", brStr, (cr) ? "\n" : "");

	return str;
}

consoleVariable *consoleBreakStmt::execute(consoleScope *s) {
	switch(m_type) {
	case CBS_CONTINUE:
		if (s->continueStmtAllowed()) {
			s->continueStmt(1);
		}
		else {
			cprintf("Illegal continue statement\n");
		}
		break;
	case CBS_BREAK:
		if (s->breakStmtAllowed()) {
			s->breakStmt(1);
		}
		else {
			cprintf("Illegal break statement\n");
		}
		break;
	case CBS_SUSPEND:
		if (s->suspendStmtAllowed()) {
//			cprintf("Legal suspend statement\n");
			s->suspendStmt(1);
		}
		else {
			cprintf("Illegal suspend statement (only allowed in global scope)\n");
		}
		break;
	default:
			cprintf("Unknown break statement\n");
		break;
	}
	return new consoleVariable("", e3ga(0.0));
}

/* ******************************************************************* */

consoleStmtListStmt::consoleStmtListStmt(consoleStatement *stmt) : consoleStatement(stmt->line(), stmt->column()) {
	initToNothing();
	addChild(stmt);
}

consoleStmtListStmt::consoleStmtListStmt(int line, int column) : consoleStatement(line, column) {
	initToNothing();
}

consoleStmtListStmt::consoleStmtListStmt() : consoleStatement() {
	initToNothing();
}

consoleStmtListStmt::consoleStmtListStmt(const consoleStmtListStmt &s) : consoleStatement(s) {
	initToNothing();
	// copy the m_dynStmtVariables???
	if (s.m_dynStmtVariables) {
		// how to copy a container???
		// m_dynStmtVariables = new std::set<std::string>(s.m_dynStmtVariables);
		m_dynStmtVariables = new std::set<std::string>();
		for (std::set<std::string>::const_iterator I = s.m_dynStmtVariables->begin();
				I != s.m_dynStmtVariables->end(); I++)
			m_dynStmtVariables->insert(*I);
	}
}


consoleStatement *consoleStmtListStmt::copy() const {
	return new consoleStmtListStmt(*this);
}

consoleStmtListStmt::~consoleStmtListStmt() {
	freeDynStmtVariables();
	initToNothing();
}

void consoleStmtListStmt::initToNothing() {
	m_dynStmtVariables = NULL;
}

int consoleStmtListStmt::freeDynStmtVariables() {
	if (m_dynStmtVariables) delete m_dynStmtVariables;
	m_dynStmtVariables = NULL;


	return 0;
}

int consoleStmtListStmt::setDynStmtVariables(std::set<std::string> *variables) {
	freeDynStmtVariables();
	m_dynStmtVariables = variables;
	return 0;
}

int consoleStmtListStmt::dependsOn(const std::string &name) {
	if (m_dynStmtVariables == NULL) {
	//	printf("%08X: I have no m_dynStmtVariables\n", this); 
		return 0;
	}
	else return (m_dynStmtVariables->find(name) != m_dynStmtVariables->end());
}


int consoleStmtListStmt::dummy() {
	return ((m_nbChildren == 1) && m_child[0]->dummy());
}

char *consoleStmtListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));

	int i, l = 0;

	// get all child strings
	for (i = 0; i < m_nbChildren; i++) {
		childStr[i] = (m_child[i]) ? m_child[i]->string(cr, tl + ((stmtListChild()) ? 1 : 0)) : strdup("");
		l += strlen(childStr[i]) + 2;
	}
	char *str = (char*)malloc(l + tl * 2 + 10), *strPtr = str;
	strPtr[0] = 0; // in case this has no children

	if (stmtListChild()) {// print curly brace 
		// print tabs
		for (i = 0; i < tl; i++) str[i] = '\t';
		strPtr += i;
		strPtr += sprintf(strPtr, "{%s", (cr) ? "\n" : "");
	}

	// print children
	for (i = 0; i < m_nbChildren; i++) {
		strPtr += sprintf(strPtr, "%s", childStr[i]);
		free(childStr[i]);
	}

	if (stmtListChild()) {// print curly brace 
		// print tabs
		for (i = 0; i < tl; i++) str[i] = '\t';
		strPtr += i;
		strPtr += sprintf(strPtr, "}%s", (cr) ? "\n" : "");
	}


	free(childStr);
	return str;
}

consoleVariable *consoleStmtListStmt::execute(consoleScope *s) {
	return execute(s, 0);
}	


consoleVariable *consoleStmtListStmt::execute(consoleScope *s, int stmtIdx) {
	int i;
	consoleVariable *result;
	int startIdx = s->getResumeIdx(); // this always returns 0, except when resuming; then it return the index of the next statement to execute

	// execute all statements in list
	for (i = startIdx; i < m_nbChildren; i++) {
		if (m_child[i] == NULL) continue;
		s->startStatement(); 

		result = m_child[i]->execute(s);
		if (s->funcStmt()) {
			// add function to local scope
			s->addUserFunction((consoleFuncStmt*)m_child[i]);

			if (s->globalScope()) m_child[i] = NULL; // the global scope keeps a copy of the pointer to the function forever

			result = NULL;
		}
		else {
			result->rhs(1);
			s->endStatement(result, (m_child[i])->verbose());

			if (s->returnStmt()) {
				if (s->globalScope()) {
					cprintf("Function %s, line %d, column %d: error: return statement in global scope!\n", s->functionName().c_str(), line(), column());
					delete result;
				}
				else return result;
			}
			else if (s->suspendStmt()) {
				s->addSuspendIdx(i);
				delete result;
				return new consoleVariable("", e3ga(0.0));
			}
			else if (s->breakStmt() || s->continueStmt()) {
				delete result;
				return new consoleVariable("", e3ga(0.0));
			}
			else delete result;
		}
	}

	return new consoleVariable("", e3ga(0));
}

/* ******************************************************************* */

consoleFuncDeclStmt::consoleFuncDeclStmt(int line, int column, const char *name, consoleFuncArgSpecListStmt *arg, int function) : consoleStatement(line, column) {
	initToNothing();

	m_name = strdup(name);
	m_function = function;	

	addChild(arg ? arg : new consoleFuncArgSpecListStmt(line, column));
}

consoleFuncDeclStmt::consoleFuncDeclStmt(const consoleFuncDeclStmt &s) : consoleStatement(s) {
	initToNothing();
	m_name = strdup(s.m_name);
	m_function = s.m_function;	
}

consoleStatement *consoleFuncDeclStmt::copy() const {
	return new consoleFuncDeclStmt(*this);
}

consoleFuncDeclStmt::~consoleFuncDeclStmt() {
	if (m_name) free(m_name);

	initToNothing();
}

void consoleFuncDeclStmt::initToNothing() {
	m_name = NULL;
}

char *consoleFuncDeclStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	consoleStatement *arg = argSpecList();

	char *argStr = (arg) ? arg->string(cr, tl) : strdup("");
	
	const char *quotes = (quote(m_name)) ? "\"" : "";

	int l = strlen(argStr) + strlen(m_name) + tl + 64;
	char *str = (char*)malloc(strlen(argStr) + strlen(m_name) + tl + 64);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "%s %s%s%s(%s);%s", (m_function) ? "function" : "batch",
		quotes, m_name, quotes, argStr, (cr) ? "\n" : "");

	free(argStr);

	return str;
}

consoleVariable *consoleFuncDeclStmt::execute(consoleScope *s) {
	return new consoleVariable("", e3ga(0.0));
}

/* ******************************************************************* */

consoleFuncStmt::consoleFuncStmt(int line, int column, const char *name, consoleFuncArgSpecListStmt *arg, 
								 consoleStmtListStmt *sl, int function) : consoleStatement(line, column) {
	initToNothing();

	m_name = strdup(name);
	m_function = function;
	m_workingDirectory = g_state->m_workingDirectory;


	addChild(arg ? arg : new consoleFuncArgSpecListStmt(line, column));
	addChild(sl);
}

consoleFuncStmt::consoleFuncStmt(const consoleFuncStmt &s) : consoleStatement(s) {
	initToNothing();
	m_function = s.m_function;
	m_name = strdup(s.m_name);
//	if (s.m_filename) m_filename = strdup(s.m_filename);
	m_workingDirectory = s.m_workingDirectory;
}


consoleStatement *consoleFuncStmt::copy() const {
	return new consoleFuncStmt(*this);
}

consoleFuncStmt::~consoleFuncStmt() {
	if (m_name) free(m_name);
//	if (m_filename) free(m_filename); 

	initToNothing();
}

void consoleFuncStmt::initToNothing() {
	m_name = NULL;
//	m_filename = NULL;
	m_function = -1;
}
/*
int consoleFuncStmt::filename(const char *filename) {
	if (m_filename) free(m_filename); 
	m_filename = strdup(filename);
	return 0;
}
*/
char *consoleFuncStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	consoleStatement *arg = argSpecList();
	consoleStatement *stmt = stmtList();

	char *argStr = (arg) ? arg->string(cr, tl) : strdup("");
	char *stmtStr = (stmt) ? stmt->string(cr, tl + ((cr) ? 1 : 0)) : strdup("");
	
	const char *quotes = (quote(m_name)) ? "\"" : "";

	int l = strlen(argStr) + strlen(stmtStr) + strlen(m_name) + tl + 64;
	char *str = (char*)malloc(strlen(argStr) + strlen(stmtStr) + strlen(m_name) + tl + 64);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "%s %s%s%s(%s) {%s%s}%s", (m_function) ? "function" : "batch",
		quotes, m_name, quotes, 
		argStr, (cr) ? "\n" : "", stmtStr, (cr) ? "\n" : "");

//	printf("%s %d %d\n", str, l, strlen(str));
//	free(str);
//	str = strdup("test");

	free(argStr);
	free(stmtStr);

	return str;
}

consoleVariable *consoleFuncStmt::execute(consoleScope *s) {
	s->funcStmt(1);
	return NULL;
}

consoleVariable *consoleFuncStmt::execute(consoleScope *s, consoleVariable *arg[maxConsoleFuncArg]) {
//	printf("Exec function in %s\n", m_filename);
	g_state->setWorkingDirectory(m_workingDirectory);

	/*  bind arguments */
	consoleFuncArgSpecListStmt *asl = argSpecList();
	int i = 0;
	consoleFuncArgSpecStmt *spec;
	consoleVariable *result;
	while (spec = asl->argSpec(i)) {
		consoleVariable temp(spec->name(), e3ga(0.0));
		temp.functionArgument(1);
		result = s->assignVariable(&temp, arg[i]);
		delete result;
		i++;
	}

	// execute function
	consoleStatement *stmt = stmtList();
	return (stmt) ? stmt->execute(s) : new consoleVariable("", e3ga(0.0)); 
}
/*
int consoleFuncStmt::usesVariable(const char *name, int global = 1) {
	if (m_function == 1)  global = 0; // leaving the global scope
	return consoleStatement::usesVariable(name, global);
}
*/

/* ******************************************************************* */

consoleFuncArgSpecStmt::consoleFuncArgSpecStmt(int line, int column, const char *name, int model) : consoleStatement(line, column) {
	initToNothing();

	m_name = strdup(name);
	m_model = model;	
}

consoleFuncArgSpecStmt::consoleFuncArgSpecStmt(const consoleFuncArgSpecStmt &s) : consoleStatement(s) {
	initToNothing();
	m_name = strdup(s.m_name);
	m_model = s.m_model;		
}

consoleStatement *consoleFuncArgSpecStmt::copy() const {
	return new consoleFuncArgSpecStmt(*this);
}

consoleFuncArgSpecStmt::~consoleFuncArgSpecStmt() {
	free(m_name);

	initToNothing();
}

void consoleFuncArgSpecStmt::initToNothing() {
	m_model = 0;
	m_name = NULL;
}

char *consoleFuncArgSpecStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	const char *quotes = (quote(m_name)) ? "\"" : "";

	char *str = (char*)malloc(strlen(m_name) + 32);
	char *model;
	switch(m_model) {
	case MVI_E3GA:
		model = (char*)"e3ga ";
		break;
	case MVI_P3GA:
		model = (char*)"p3ga ";
		break;
	case MVI_C3GA:
		model = (char*)"c3ga ";
		break;
	case MVI_C5GA:
		model = (char*)"c5ga ";
		break;
	case MVI_I2GA:
		model = (char*)"i2ga ";
		break;
	default:
		model = (char*)"";
		break;
	}

	sprintf(str, "%s%s%s%s", model, quotes, m_name, quotes);

	return str;
}

consoleVariable *consoleFuncArgSpecStmt::execute(consoleScope *s) {
	// doesn't do anything...
	return NULL;
}

/* ******************************************************************* */

consoleFuncArgSpecListStmt::consoleFuncArgSpecListStmt(int line, int column, consoleFuncArgSpecStmt *arg) : consoleStatement(line, column) {
	initToNothing();
	addChild(arg);
}

consoleFuncArgSpecListStmt::consoleFuncArgSpecListStmt(int line, int column) : consoleStatement(line, column) {
	initToNothing();
}

consoleFuncArgSpecListStmt::consoleFuncArgSpecListStmt(const consoleFuncArgSpecListStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleFuncArgSpecListStmt::copy() const {
	return new consoleFuncArgSpecListStmt(*this);
}

consoleFuncArgSpecListStmt::~consoleFuncArgSpecListStmt() {

	initToNothing();
}

void consoleFuncArgSpecListStmt::initToNothing() {

}

char *consoleFuncArgSpecListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));
	int i, l = 2;
	for (i = 0; i < m_nbChildren; i++) {
		childStr[i] = (m_child[i]) ? m_child[i]->string(cr, tl) : strdup("");
		l += strlen(childStr[i]) + 2;
	}
	char *str = (char*)malloc(l + 1), *strPtr;
	strPtr = str;
	for (i = 0; i < m_nbChildren; i++) {
		strPtr += sprintf(strPtr, "%s%s", childStr[i], (i == (m_nbChildren-1)) ? "" : ", ");
		free(childStr[i]);
	}
	strPtr += sprintf(strPtr, "");
	free(childStr);
	return str;
}

consoleVariable *consoleFuncArgSpecListStmt::execute(consoleScope *s) {
	// doesn't do anything
	return NULL;
}

/* ******************************************************************* */

consoleArrayIdxListStmt::consoleArrayIdxListStmt(int line, int column, consoleExprListStmt *el) : consoleStatement(line, column) {
	initToNothing();
	addChild(el);
}

consoleArrayIdxListStmt::consoleArrayIdxListStmt(const consoleArrayIdxListStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleArrayIdxListStmt::copy() const {
	return new consoleArrayIdxListStmt(*this);
}

consoleArrayIdxListStmt::~consoleArrayIdxListStmt() {
	initToNothing();
}

consoleVariable *consoleArrayIdxListStmt::execute(consoleScope *s) {
	return NULL; // does nothing
}

char *consoleArrayIdxListStmt::string(int cr /*= 0*/, int tl /* = 0 */) {
	char **childStr = (char**)calloc(m_nbChildren, sizeof(char*));
	int i, l = 0;
	for (i = 0; i < m_nbChildren; i++) {
		childStr[i] = (m_child[i]) ? m_child[i]->string(cr, tl) : strdup("0");
		l += strlen(childStr[i]) + 2;
	}
	char *str = (char*)malloc(l + 1), *strPtr;
	strPtr = str;
	for (i = 0; i < m_nbChildren; i++) {
		strPtr += sprintf(strPtr, "[%s]", childStr[i]);
		free(childStr[i]);
	}
	free(childStr);
	return str;
}

int consoleArrayIdxListStmt::execute(consoleScope *s, char *idxStr) {
	int i;
	for (i = 0; i < m_nbChildren; i++) {
		consoleVariable *result = NULL;
		if (m_child[i]) result = m_child[i]->execute(s);

		if (result) {
			double val = result->scalar();
			if (val < 0) val -= 0.5;
			else val += 0.5;
//			idxStr += sprintf(idxStr, "[%d]", (int)(result->scalar() + 0.5));
			idxStr += sprintf(idxStr, "[%d]", (int)val);
			delete result;
		}
		else idxStr += sprintf(idxStr, "[0]");
	}

	return 0;
}

void consoleArrayIdxListStmt::initToNothing() {
}

/* ******************************************************************* */

consoleDynStmt::consoleDynStmt(int line, int column, consoleStatement *stmt, const std::string &name) : consoleStatement(line, column) {
	initToNothing();

	addChild(stmt);
	m_name = name;
}

consoleDynStmt::consoleDynStmt(const consoleDynStmt &s) : consoleStatement(s) {
	initToNothing();
	m_workingDirectory = s.m_workingDirectory;
	m_name = s.m_name;
}

consoleStatement *consoleDynStmt::copy() const {
	return new consoleDynStmt(*this);
}

consoleDynStmt::~consoleDynStmt() {

	initToNothing();
}

consoleVariable *consoleDynStmt::execute(consoleScope *s) {
	consoleVariable *result = NULL;
	if (s->dynStmtVariableCollect()) {
		cprintf("Error in '%s': dynamic() call inside a dynamic() call (returning 0.0).\n", s->functionName().c_str());
	}
	else if (!s->globalScope()) {
		cprintf("Error in '%s': dynamic() can only be called in global scope!\n", s->functionName().c_str());
	}
	else if (m_child[0]) {
		consoleStmtListStmt *sl = (consoleStmtListStmt*)(m_child[0]->copy());

		// execute immediatelly 
		//(the dynamic will get evaluated again at the end of this 'run' 
		// (batch, console command list, etc) 
		// but not assignment displat, since this will be done on first eval...
		int nad = s->noAssignmentDisplay();
		s->noAssignmentDisplay(1);
		sl->execute(s); 
		s->noAssignmentDisplay(nad);

		// add dynamic
		g_state->addDynStmt(sl, m_workingDirectory, m_name);
	}

	return (result) ? result : new consoleVariable("", e3ga(0.0)); 
}

char *consoleDynStmt::string(int cr /*= 0*/, int tl /*= 0*/) {
	const char *stmtStr = (m_child[0]) ? m_child[0]->string(cr, tl + ((cr) ? 1 : 0)) : "statement already added to state";
	char *str = (char*)malloc(strlen(stmtStr) + 32 + tl);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	sprintf(str + i, "dynamic{%s}%s", stmtStr, (cr) ? "\n" : "");


	return str;
}

void consoleDynStmt::initToNothing() {

}

/* ******************************************************************* */

consoleSetStmt::consoleSetStmt(int line, int column, const std::string &what, const std::string &value) : consoleStatement(line, column) {
	initToNothing();

	m_what = what;
	m_strValue = value;
}

consoleSetStmt::consoleSetStmt(int line, int column, const std::string &what, int value) {
	initToNothing();

	m_what = what;
	m_intValue = value;

}

consoleSetStmt::consoleSetStmt(const consoleSetStmt &s) : consoleStatement(s) {
	initToNothing();
}

consoleStatement *consoleSetStmt::copy() const {
	return new consoleSetStmt(*this);
}

consoleSetStmt::~consoleSetStmt() {

	initToNothing();
}

consoleVariable *consoleSetStmt::execute(consoleScope *s) {
	if (m_what == "inner_product") {
		s->setInnerProduct(m_strValue);
	}
	else if (m_what == "default_model") {
		s->setDefaultModel(m_intValue);
	}
	else {
		cprintf("consoleSetStmt::execute(): can not set '%s'\n", m_what.c_str());
	}

	return new consoleVariable("", e3ga(0.0)); 
}

char *consoleSetStmt::string(int cr /*= 0*/, int tl /*= 0*/) {
	char *str = (char*)malloc(m_what.length() + 64 + tl);

	// print tabs
	int i;
	for (i = 0; i < tl; i++) str[i] = '\t';

	if (m_what == "inner_product") {
		sprintf(str + i, "%s(%s)%s", m_what.c_str(), m_strValue.c_str(), (cr) ? "\n" : "");
	}
	else if (m_what == "default_model") {
		sprintf(str + i, "%s(%s)%s", m_what.c_str(), 
			(m_intValue == -1) ? "none" : 
			((m_intValue == MVI_E3GA) ? "e3ga" : 
			((m_intValue == MVI_P3GA) ? "p3ga" : "c3ga")),
			(cr) ? "\n" : "");
	}
	else {
		sprintf(str + i, "unimplemented_set(%s or %d)%s", m_strValue.c_str(), m_intValue, (cr) ? "\n" : "");
	}

	return str;
}

void consoleSetStmt::initToNothing() {
	m_intValue = -1;
}
