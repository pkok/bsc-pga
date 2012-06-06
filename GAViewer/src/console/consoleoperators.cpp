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

#include <string.h>

#include "../state.h"
#include "../mvint.h"
#include "../object.h"
#include "console.h"
#include "consolescope.h"
#include "consolefunction.h"
#include "consoleoperators.h"
#include "consolevariable.h"

/*
Todo: check somewhere that these precedence and associativity tables are correct
*/
static const int c_opPrecedence[CBO_NB_OPS] = {
	6, // CBO_GP 0 // 'space' (implicit, doesn't exist)
	0, // CBO_ASSIGNMENT 1 // '='
	6, // CBO_IGP 2 // '/'
	9, // CBO_OP 3 // '^'
	7, // CBO_IP 4 // '.'
	6, // CBO_GP 0 // '*'  
	5, // CBO_ADDITION 6 // '+'
	5, // CBO_SUBTRACTION 7 // '-'
	8, // CBO_MEET 8 // '&'
	8, // CBO_JOIN 9 // '|'*/
	3, //CBO_EQUAL 10 // '=='
	4, //CBO_LESS 11 // '<'
	4, //CBO_GREATER 12 // '>'
	4, //CBO_LE 13 // '<='
	4, //CBO_GE 14 // '>='
	2, //CBO_AND 15 // '&&'
	1, //CBO_OR 16 // '||'
	3 //CBO_NE 17 // '=='
};

const int c_opAssocitivity[CBO_NB_OPS] = { // -1 = left associative, 1 = right associative
	-1, // CBO_GP 0 // 'space' (implicit, doesn't exist)
	1, // CBO_ASSIGNMENT 1 // '='
	-1, // CBO_IGP 2 // '/'
	-1, // CBO_OP 3 // '^'
	-1, // CBO_IP 4 // '.'
	-1, // CBO_SCP 5 // '*'
	-1, // CBO_ADDITION 6 // '+'
	-1, // CBO_SUBTRACTION 7 // '-'
	-1, // CBO_MEET 8 // '&'
	-1, // CBO_JOIN 9 // '|'
	-1, //CBO_EQUAL 10 // '=='
	-1, //CBO_LESS 11 // '<'
	-1, //CBO_GREATER 12 // '>'
	-1, //CBO_LE 13 // '<='
	-1, //CBO_GE 14 // '>='
	-1, //CBO_AND 15 // '&&'
	-1, //CBO_OR 16 // '||'
	-1 //CBO_NE 17 // '=='
};

const char *c_opNames[CBO_NB_OPS] = {
	"gp",
	"assign",
	"igp",
	"op",
	"hip",
	"gp", // replacement for scp (Discuss with Leo)
//	"scp",
	"add",
	"sub",
	"meet",
	"join",
	"equal",
	"less",
	"greater",
	"le",
	"ge",
	"and",
	"or",
	"ne"
};

// !!!!!!!!!!!!!!!!!!!!	
// for a list of symbols, see consoleExprListStmt::string()

static consoleVariable *consoleEvalElRec(consoleScope *s, consoleVariable *cv) {
	consoleVariable *cvPrev, *cvStart, *cvNext, **cvPrevPtr;

	if (cv->next() == NULL) //end recursion
		return cv;

	// new code, non recursive
	// 'collapse' operators one by one, from the highest precedence to the lowest
	cvStart = cv;
	while (1) {
		cv = cvPrev = cvStart;
		cvPrevPtr = &cvStart;

		if (cv->next() == NULL) return cv; // list collapsed to a single variable

		while (cv = cv->next()) {
			// get operator function name (allow for arbitrary inner product)
			std::string opName = (cv->op() == CBO_IP) ? s->innerProduct() : c_opNames[cv->op()];
//			if (cv->op() == CBO_IP) printf("Ip: %s\n", opName.c_str());

			
			if (cv->next() == NULL) { // last in line: always execute (cvPrev's operator in front must have lower or equal precedence)
				*cvPrevPtr = consoleExecFunc(s, opName, cvPrev);
				break; // restart loop
			}

			else if (c_opPrecedence[cv->op()] > c_opPrecedence[cv->next()->op()]) { // higher precedence: execute operator
				cvNext = cv->next();
				cv->next(NULL); // break list
				*cvPrevPtr = consoleExecFunc(s, opName, cvPrev); // execute function
				(*cvPrevPtr)->next(cvNext);
				break; // restart loop
			}

			else if (c_opPrecedence[cv->op()] == c_opPrecedence[cv->next()->op()]) { // equal precedence: execution depends on associativity
				if (c_opAssocitivity[cv->op()] > 0) { // right associative (_don't_ execute, but continue loop)
					// continue loop
					cvPrevPtr = &(cvPrev->m_next);
					cvPrev = cv; 
				}
				else { // left associative (execute & continue loop)
					cvNext = cv->next();
					cv->next(NULL); // break list
					*cvPrevPtr = consoleExecFunc(s, opName, cvPrev); // execute function
					(*cvPrevPtr)->next(cvNext);

					// continue loop
					cvPrev = *cvPrevPtr;
					cv = *cvPrevPtr;
				}
			}
			else { // lower precedence: continue loop
				cvPrevPtr = &(cvPrev->m_next);
				cvPrev = cv; 
			}

		}
	}


	printf("Error in consoleEvalElRec()\n");
	return NULL; // function should never arrive over here...
}

consoleVariable *consoleEvalExprList(consoleScope *s, consoleVariable *cv) {
	int op;
	consoleVariable **cvPtr;

	if (cv == NULL) return cv;

	/* 
	It is possible to write something like '/x + a', because the 
	grammar allows an arbitrary operator before each expression.
	This is only semantically valid when the first operator is a '+' or a '-' (i.e., '-x + a').
	This next piece of code checks for this, and remove the invalid operator,
	or turns the '+' or '-' into a unary operator.
	*/
	op = cv->op();
	if (op & CBO_MASK) {
		if (op == CBO_SUBTRACTION) {
			// remove the binary part of the operator, toggle negation part
			cv->op(op ^ ((op & CBO_MASK) | CUO_NEGATION));
		}
		else if (op == CBO_ADDITION) {
			// remove the binary part of the operator
			cv->op(op ^ (op & CBO_MASK));
		}
		else {
			// issue warning 
			cprintf("Warning: invalid unary operator '%d' used (todo: make this warning clearer...)\n", op);
			// remove the binary part of the operator
			cv->op(op ^ (op & CBO_MASK));
		}
	}

	// apply all unary operators; count how many expressions there are
	// temp test: convert binary minus to binary plus and unary minus
	cvPtr = &cv;
	while (*cvPtr) {
		op = (*cvPtr)->op();

		if (op & CUO_MASK) {
			if (op & CUO_NEGATION)
				*cvPtr = consoleExecUnaryFunc(s, "negate", *cvPtr);

			if (op & CUO_INVERSION)
				*cvPtr = consoleExecUnaryFunc(s, "inverse", *cvPtr);

			if (op & CUO_REVERSION)
				*cvPtr = consoleExecUnaryFunc(s, "reverse", *cvPtr);

			(*cvPtr)->op(op ^ (op & CUO_MASK));
		}

		cvPtr = &((*cvPtr)->m_next);
	}

	return consoleEvalElRec(s, cv);
}











