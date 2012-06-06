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

#include "../state.h"
#include "../uistate.h"
#include "../object.h"
#include "consolescope.h"
#include "consolefunction.h"
#include "console.h"
#include "consolestatement.h"
#include "consolevariable.h"

#include <iostream>
#include <vector>
#include <string>

int consoleScope::m_idCount = 0;

// important: adjust when new models are introduced...
// todo: merge with the same function in 'consolefunctions.cpp
static inline int model(int v) {
	return v & (MVI_E3GA | MVI_P3GA | MVI_C3GA | MVI_I2GA | CVF_ANY_MODEL);
}

static inline int compareModel(int m1, int m2) {
	if ((m1 & CVF_ANY_MODEL) || (m2 & CVF_ANY_MODEL)) return 1;
	else return (m1 == m2);
}

static inline int side(int v) {
	return v & (CVF_RHS | CVF_LHS);
}


consoleScope::consoleScope(const std::string &fname, consoleScope *parentScope, int id /* = -1 */) {
	initToNothing();

	{
		int on = 1;
		supressWarnings(on); // mute_warnings() by default
	}

	m_id = (id < 0) ? m_idCount++ : id;
	if (m_idCount < 0) m_idCount = 1;

	m_parentScope = parentScope;

	// keep?
	if (parentScope && parentScope->dynStmtVariableCollect())
		dynStmtVariableCollect(1);

	functionName(fname);

	if (m_parentScope) {
		m_defaultModel = m_parentScope->m_defaultModel;
		m_ip = m_parentScope->m_ip;
	}

}

consoleScope::~consoleScope() {
	if (m_suspendIdx) free(m_suspendIdx);
	if (m_resumeIdx) free(m_resumeIdx);

	// free variables
	removeAllVariables();

	// free functions 
	removeAllFunctions();

	initToNothing();
}

void consoleScope::initToNothing() {
//	m_variable = NULL ;
//	m_nbVariables = 0;
	m_parentScope = NULL;
	m_flags = 0;
	m_functionName = "";

	m_suspendIdx = NULL;
	m_resumeIdx = NULL;

	m_defaultModel = -1;
	m_ip = "";
}

int consoleScope::setInnerProduct(const std::string &ip) {
	m_ip = ip;
	return 0;
}

int consoleScope::setDefaultModel(int model) {
	m_defaultModel = model;
	return 0;
}


int consoleScope::addSuspendIdx(int idx) {
	int l;
	if (m_suspendIdx == NULL) l = 1;
	else l = m_suspendIdx[0] + 1;

	m_suspendIdx = (int*)realloc(m_suspendIdx, (l+1) * sizeof(int));
	m_suspendIdx[0] = l;
	m_suspendIdx[l] = idx + (l == 1); // add (l == 1) to prevent to skip the suspend on the next resume

//	printf("Suspend at idx %d\n", m_suspendIdx[l]);
	return 0;
}

int *consoleScope::getSuspendIdcs() {
	int *suspendIdx = m_suspendIdx;
	m_suspendIdx = NULL;
	return suspendIdx;
}

int consoleScope::getResumeIdx() {
	if ((m_resumeIdx == NULL) || (m_resumeIdx[0] == 0)) return 0;
	int idx = m_resumeIdx[m_resumeIdx[0]];
	m_resumeIdx[0]--;
	return idx;
}

int consoleScope::setResumeIdcs(int *idcs) {
	if (m_resumeIdx) free(m_resumeIdx);
	m_resumeIdx = idcs;
	return 0;
}


consoleScope* consoleScope::subScope() {
	consoleScope *ss = new consoleScope(functionName(), this, id());
	ss->flags(flags()); // subscope always copies flags 
	return ss;
}


int consoleScope::functionName(const std::string &fname) {
	m_functionName = fname;
	return 0;
}


int consoleScope::addUserFunction(consoleFuncStmt *funcStmt) {
	consoleFunc func;
	func.name = (char*)funcStmt->name();
	func.funcStmt = funcStmt;
	func.funcPtr = NULL;

	consoleFuncArgSpecListStmt *argSpecList = funcStmt->argSpecList();
	consoleFuncArgSpecStmt *argSpec = NULL;
	int i = 0;

	func.nbArg = 0;

	while (argSpec = argSpecList->argSpec(i)) {
		func.nbArg++;
		func.arg[i] = CVF_RHS | argSpec->model();
		i++;
	}

	return addFunction(&func);
}

int consoleScope::setFunctionOrVariable(const std::string &ident, bool value) {
	ITI I;
	if ( (I = m_identifierTable.find(ident)) != m_identifierTable.end())
		I->second = value;
	else m_identifierTable.insert(std::make_pair(ident, value));
	return 0;
}

int consoleScope::isFunction(const std::string &ident) const {
	CITI I;
	if ( (I = m_identifierTable.find(ident)) != m_identifierTable.end())
		return I->second;
	if (m_parentScope) return m_parentScope->isFunction(ident);
	else return false;
}

int consoleScope::freeFunction(consoleFunc *f) {
	if (f == NULL) return -1;
	if (f->name) {
		free((void*)f->name);
	}
	if (globalScope() && f->funcStmt) delete f->funcStmt; // only global functions should be deleted (since local functions are pointed to by global functions)
	free(f);
	return 0;
}

void consoleScope::removeAllFunctions() {
	FI fi;
	consoleFunc *f;

	for (fi = m_functions.begin(); fi != m_functions.end(); fi++) {
		if (f = fi->second) {
			freeFunction(f);
		}
	}
	m_functions.clear();
}

void consoleScope::removeAllVariables() {
	for (CVI i = m_variables.begin(); i != m_variables.end(); i++) delete i->second;
	m_variables.clear();
}


int consoleScope::removeFunction(const std::string &nameWithArguments) {
//	std::cout << "request to remove " << nameWithArguments << "\n";
	FI fi = m_functions.find(nameWithArguments);
	if (fi != m_functions.end()) {
//		std::cout << "removing " << nameWithArguments << "\n";
		freeFunction(fi->second);
		m_functions.erase(fi);
	}

	return 0;
}

int consoleScope::addFunction(const consoleFunc *func) {
	// copy func
	consoleFunc *funcCopy = (consoleFunc *)malloc(sizeof(consoleFunc));
	memcpy(funcCopy, func, sizeof(consoleFunc));
	funcCopy->name = strdup(funcCopy->name);

	std::string nameWithArguments = getFuncStringNameWithArguments(func, 0);

/*	nameWithArguments += "(";

	if (func->funcStmt) {
		consoleFuncArgSpecListStmt *asl = func->funcStmt->argSpecList();
		consoleFuncArgSpecStmt *s;

		// add all arguments
		int i = 0;
		while (s = asl->argSpec(i)) {
			nameWithArguments += ((i == 0) ? "" : ", ");

			switch (s->model()) {
			case MVI_E3GA:
				nameWithArguments += "e3ga ";
				break;
			case MVI_P3GA:
				nameWithArguments += "p3ga ";
				break;
			case MVI_C3GA:
				nameWithArguments += "c3ga ";
				break;
			default:
				nameWithArguments += " ";
				break;

			}

			i++;
		}
		nameWithArguments += ")";
	}
	else {
		// add all arguments
		int i = 0;
		for (i = 0; i < func->nbArg; i++) {
			nameWithArguments += ((i == 0) ? "" : ", ");

			switch (model(func->arg[i])) {
			case MVI_E3GA:
				nameWithArguments += "e3ga ";
				break;
			case MVI_P3GA:
				nameWithArguments += "p3ga ";
				break;
			case MVI_C3GA:
				nameWithArguments += "c3ga ";
				break;
			default:
				nameWithArguments += " ";
				break;
			}
		}
		nameWithArguments += ")";
	}
*/
	// remove old function from list if it already exists
	removeFunction(nameWithArguments);

	// add function to list
	m_functions.insert(std::make_pair(nameWithArguments, funcCopy));

	if (func->funcStmt && globalScope() && (!supressWarnings())) {
		// print out message stating function was added
		cprintf("Added %s %s\n", func->funcStmt->function() ? "function" : "batch", getFuncStringNameWithArguments(func, 1).c_str());
	}

	setFunction(func->name);

	return 0;
}

int consoleScope::existFunction(int sid, const std::string &name, int global) {
	if (!global || (global && globalScope())) {
		FI fi = m_functions.lower_bound(name);
		if ((fi != m_functions.end()) && (name == fi->second->name))
			return 1;
	}
	else if (m_parentScope) {return m_parentScope->existFunction(sid, name, global);}

	return 0;
}

/*
This function computes the distances of two sets of arguments (formal, actual).
It will return 0 for a perfect match.
It will return lower values the closer the cast is.
A 'upward' cast (e.g. from Euclidean to Conformal) is preferred (== return a lower value)
over a 'downward' cast (e.g. from Conformal to Euclidean).
The smaller the cast (Euclidean to Projective is smaller than Euclidean to Conformal),
the lower the distance.
*/
static int distance(int nbArg, const int *formalArg, const int *actualArg) {
	int i, d = 0, mf, ma;

	// update when new models are introduced
	int dmatrix[5][5] = {
		//{MVI_E3GA, MVI_P3GA, MVI_C3GA, MVI_I2GA, MVI_C5GA}
		{       0,        1,        2,     5,   3}, // from E3GA to ...
		{100+1,        0,        1,     6,   2}, // from P3GA to ...
		{100+2, 100+1,        0,     5,  1}, // from C3GA to ...
		{100+2, 100+3, 100+1,     0, 100+1}, // from I2GA to ...
		{100+3, 100+2,        100+1,     5,  0}, // from C5GA to ...

	};


	for (i = 0; i < nbArg; i++) {
		if (compareModel(formalArg[i], actualArg[i])) continue;
		mf = model(formalArg[i]);
		ma = model(actualArg[i]);

		// turn model into integer [0....n-1]
		ma = ma / MVI_E3GA - 1;
		mf = mf / MVI_E3GA - 1;

		d += dmatrix[ma][mf];

#ifdef RIEN
// old code (assumes mf, ma one of MVI_E3GA, MVI_P3GA, MVI_C3GA, MVI_I2GA

		if ((ma == MVI_E3GA) && (mf == MVI_P3GA)) { // e->p: one up
			d += 1;
		}
		else if ((ma == MVI_E3GA) && (mf == MVI_C3GA)) { // e->c: two up
			d += 2;
		}
		else if ((ma == MVI_P3GA) && (mf == MVI_C3GA)) { // p->c: one up
			d += 1;
		}

		else if ((ma == MVI_C3GA) && (mf == MVI_E3GA)) { // c->e: two down
			d += 100 + 2;
		}
		else if ((ma == MVI_C3GA) && (mf == MVI_P3GA)) { // c->p: one down
			d += 100 + 1;
		}
		else if ((ma == MVI_P3GA) && (mf == MVI_E3GA)) { // p->e: one down
			d += 100 + 1;
		}
#endif

	}
	return d;
}

int consoleScope::lookupFunctionRec(int sid, const std::string &name, int global, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func, int *bestDistance) {
	int d;

	// search (back to front, this is important!) for best matching function and return it if argument matches exactly
	if ((!global) || (global && globalScope())) {
		FI fi = m_functions.lower_bound(name);

		for (; (fi != m_functions.end()) && (name == fi->second->name); fi++) {
			if (fi->second->nbArg == nbArg) {
				// compute how good the arguments match
				if ((d = distance(nbArg, fi->second->arg, argType)) < *bestDistance) {
					*bestDistance = d;
					*func = fi->second;
				}
			}
		}
	}

	if (m_parentScope) return m_parentScope->lookupFunctionRec(sid, name, global, nbArg, arg, argType, func, bestDistance);
	else return 0;
}

/*
Searches in scope for function with name 'name'.
If found, checks semantics and returns function.
Returns 0 when function is found, -1 otherwise.
*/
int consoleScope::lookupFunction(int sid, const std::string &name, int global, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func) {	
	int bestDistance = 1 << 30;
	*func = NULL;
	lookupFunctionRec(sid, name, global, nbArg, arg, argType, func, &bestDistance);

	if (*func == NULL) return -1;

	// now check sideness (lhs, rhs)
	int i;
	for (i = 0; i < nbArg; i++) {
		//printf("Arg %d: %08X %08X\n", i, side(argType[j]), side(c_consoleFunc[i].arg[j]));
		if ((argType[i] & side((*func)->arg[i])) == 0) { // temp test, == 0 used to be: != side(c_consoleFunc[i].arg[j])) {
			cprintf("Error: Attempt to use '%s' as %s value in function %s\n", arg[i]->name().c_str(), 
				(side((*func)->arg[i]) == CVF_LHS) ? "lhs" : "rhs", (*func)->name);
			*func = NULL;
			return -1;
		}
	}

	return 0;
}



int consoleScope::lookupLocalVariable(int sid, const std::string &name, int global, consoleVariable **variable) {
	*variable = NULL;

	// if this is the global scope, or the same scope ID, go through variables
	//int i;
	if (globalScope() || (sid == m_id)) {
		CVI cvi= m_variables.find(name);
		if (cvi != m_variables.end()) {
			*variable = new consoleVariable("", cvi->second);
			return 0;
		}
/*		for (i = 0; i < m_nbVariables; i++) {
			if (m_variable[i]->nameEquals(name)) {
				*variable = new consoleVariable("", m_variable[i]);
				return 0;
			}
		}*/
	}
	return -1;
}

int consoleScope::lookupVariable(int sid, const std::string &name, int global, consoleVariable **variable) {

	// first check constants
	if (lookupConstant(sid, name, global, variable) == 0)
		return 0;

	// if global variable is requested, and this is not the global scope, forward call
	if (global) {
		if (globalScope())
			if (lookupLocalVariable(sid, name, global, variable) == 0)
				return 0;
		if (m_parentScope) return m_parentScope->lookupVariable(sid, name, global, variable);
		else return -1;
	}

	// lookup in local scope, on failure go to parent scope
	if (lookupLocalVariable(sid, name, global, variable) == 0) return 0;
	else return (m_parentScope && (m_parentScope->id() == id())) ? m_parentScope->lookupVariable(sid, name, global, variable) : -1;
}

int consoleScope::removeVariable(const std::string &name) {
	CVI i = m_variables.find(stringPtr(name));

//	printf("Scope %08X remove var %s\n", this, name.c_str());
	if (i != m_variables.end()) {
		consoleVariable *ptr = i->second;
		m_variables.erase(stringPtr(ptr->m_name));
		delete ptr;
	}

	return 0;
}


consoleVariable *consoleScope::assignVariable(consoleVariable *target, consoleVariable *value) {
	// forward call toward global scope if the target is global
	if (target->global() && (!globalScope()) && m_parentScope) return m_parentScope->assignVariable(target, value);

	// forward call if this is not the outer scope of a function
	if (m_parentScope && (m_parentScope->id() == m_id))
		return m_parentScope->assignVariable(target, value);

	// locally assign variable
	setVariable(target->name());

	removeVariable(target->m_name); // remove old
	consoleVariable *result = new consoleVariable(target->name(), value); // make copy
	m_variables.insert(std::make_pair(stringPtr(result->m_name), result)); // insert

	result->rhs(1);
	result->lhs(1);

	return new consoleVariable("", result); // return a copy of result, because it will be deleted.
}

static e3ga s_pi(3.1415926535897932384626433832795);
static e3ga s_e(2.7182818284590452353602874713527);
static struct {
		char *name;
		e3ga *e;
		p3ga *p;
		c3ga *c;
		c5ga *c5;
		i2ga *i2;
		bool nameAlloced;
	} s_constant[] = {
		{(char*)"e1", (e3ga*)&(e3ga::e1), NULL, NULL, NULL, NULL, false},
		{(char*)"e2", (e3ga*)&(e3ga::e2), NULL, NULL, NULL, NULL, false},
		{(char*)"e3", (e3ga*)&(e3ga::e3), NULL, NULL, NULL, NULL, false},
		{(char*)"e4", NULL, NULL, NULL, (c5ga*)&(c5ga::e4), NULL, false},
		{(char*)"e5", NULL, NULL, NULL, (c5ga*)&(c5ga::e5), NULL, false},
		{(char*)"e0", NULL, (p3ga*)&(p3ga::e0), NULL, NULL, NULL, false},
		{(char*)"no", NULL, NULL, (c3ga*)&(c3ga::no), NULL, NULL, false},
		{(char*)"ni", NULL, NULL, (c3ga*)&(c3ga::ni), NULL, NULL, false},
		{(char*)"go", NULL, NULL, NULL, NULL, (i2ga*)&(i2ga::go), false},
		{(char*)"gi", NULL, NULL, NULL, NULL, (i2ga*)&(i2ga::gi), false},
		{(char*)"einf", NULL, NULL, (c3ga*)&(c3ga::ni), NULL, NULL, false},
		{(char*)"pi", &s_pi, NULL, NULL, NULL, NULL, false},
		{(char*)"e_", &s_e, NULL, NULL, NULL, NULL, false},
		  {NULL, NULL, NULL, NULL, NULL, NULL, false}
	};

int consoleScope::lookupConstant(int sid, const std::string &name, int global, consoleVariable **variable) {
	*variable = NULL;

	// first attempt lookup in constant list
	int i = 0;
	while (s_constant[i].name) {
	  if (name == s_constant[i].name) {
			if (s_constant[i].e) *variable = new consoleVariable(s_constant[i].name, s_constant[i].e);
			else if (s_constant[i].p) *variable = new consoleVariable(s_constant[i].name, s_constant[i].p);
			else if (s_constant[i].c) *variable = new consoleVariable(s_constant[i].name, s_constant[i].c);
			else if (s_constant[i].c5) *variable = new consoleVariable(s_constant[i].name, s_constant[i].c5);
			else if (s_constant[i].i2) *variable = new consoleVariable(s_constant[i].name, s_constant[i].i2);

			return processConstant(variable);
	  }
	  i++;
	}

	return g_state->m_globalScope->lookupUserConstant(name, variable);
}


int consoleGlobalScope::lookupUserConstant(const std::string &name, consoleVariable **variable) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->lookupUserConstant(name, variable);

	UCI I = m_userConstants.find(name);

	if (I != m_userConstants.end()) {
		*variable = new consoleVariable(name, &(I->second));
		return processConstant(variable);
	}

	return -1;
}

void consoleGlobalScope::addConstant(const std::string &name, consoleVariable *C) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->addConstant(name, C);
	g_state->removeObject(name);
	m_userConstants[name].set(consoleVariable(name, C));
}
	
void consoleGlobalScope::removeConstant(const std::string &name) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->removeConstant(name);
	UCI I = m_userConstants.find(name);
	if (I != m_userConstants.end())
		m_userConstants.erase(I);
	else cprintf("Constant '%s' not found", name.c_str());
}

void consoleGlobalScope::renameBuiltinConstant(const std::string &oldName, 
    const std::string &newName) {

  	int i = 0;
	while (s_constant[i].name) {
	  if (oldName == s_constant[i].name) {
//	        printf("index %d = %s\n", i, s_constant[i].name);
			if (s_constant[i].e) e3ga::renameBasisVector(oldName.c_str(), newName.c_str());
			else if (s_constant[i].p) p3ga::renameBasisVector(oldName.c_str(), newName.c_str());
			else if (s_constant[i].c) c3ga::renameBasisVector(oldName.c_str(), newName.c_str());
			else if (s_constant[i].i2) i2ga::renameBasisVector(oldName.c_str(), newName.c_str());

            if (s_constant[i].nameAlloced)
                free(s_constant[i].name);
			s_constant[i].name = strdup(newName.c_str());
			s_constant[i].nameAlloced = true;
			return;
	  }
	  i++;
	}
  
}


/*
int consoleGlobalScope::lookupUserConstant(const std::string &name, consoleVariable **variable) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->lookupUserConstant(name, variable);

	UCI I = m_userConstants.find(name);

	if (I != m_userConstants.end()) {
		*variable = new consoleVariable(name, I->second.get());
		return processConstant(variable);
	}

	return -1;
}

void consoleGlobalScope::addConstant(const std::string &name, consoleVariable *C) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->addConstant(name, C);
	g_state->removeObject(name);
	m_userConstants[name] = std::auto_ptr<consoleVariable>(new consoleVariable(name, C));
}
	
void consoleGlobalScope::removeConstant(const std::string &name) {
	if (m_parentScope) return ((consoleGlobalScope*)m_parentScope)->removeConstant(name);
	UCI I = m_userConstants.find(name);
	if (I != m_userConstants.end())
		m_userConstants.erase(I);
	else cprintf("Constant '%s' not found", name.c_str());
}
*/

int consoleScope::processConstant(consoleVariable **variable) {
	// cast to default model
//	if ((m_defaultModel != -1) && 
//		((*variable)->model() == MVI_E3GA)) {
	if ((m_defaultModel != -1) && (m_defaultModel != (*variable)->model()))  {
		(*variable)->rhs(1);
		(*variable)->lhs(0);
		if (m_defaultModel == MVI_P3GA) {
			*variable = consoleExecFunc(this, "cast_p3ga", *variable);	
		}
		else if (m_defaultModel == MVI_C3GA) {
			*variable = consoleExecFunc(this, "cast_c3ga", *variable);	
		}
		else if (m_defaultModel == MVI_C5GA) {
			*variable = consoleExecFunc(this, "cast_c5ga", *variable);	
		}
		else if (m_defaultModel == MVI_I2GA) {
			*variable = consoleExecFunc(this, "cast_i2ga", *variable);	
		}
	}
	(*variable)->rhs(1);
	(*variable)->lhs(0);
	return 0;
}

int consoleScope::dynStmtVariable(const std::string &name) {
	if (m_parentScope) return m_parentScope->dynStmtVariable(name);
	else {
		cprintf("consoleScope::dynStmtVariable(): variable '%s' lost?\n", name.c_str());
		return 0;
	}
}

int consoleScope::startStatement() {
	m_flags = m_flags & (CSF_BREAK_ALLOWED | CSF_CONTINUE_ALLOWED | CSF_SUSPEND_ALLOWED | 
		CSF_NO_ASSIGNMENT_DISPLAY | CSF_DYN_STMT_VARIABLE_COLLECT |
		CSF_SUPRESS_WARNINGS | CSF_SUPRESS_ERRORS);
	return 0;
}

int consoleScope::endStatement(consoleVariable *result, int verbose) {
	return 0;
}

int consoleScope::getFlag(int flag) const {
	return (m_flags & flag);
}

int consoleScope::setFlag(int flag, int val) {
	m_flags = (m_flags ^ (m_flags & flag)) | (val ? flag : 0);
	return 0;
}

int consoleScope::funcStmt() {
	return getFlag(CSF_FUNCTION);
}

int consoleScope::funcStmt(int val) {
	return setFlag(CSF_FUNCTION, val);
}

int consoleScope::returnStmt() {
	return getFlag(CSF_RETURN);
}

int consoleScope::returnStmt(int val) {
	return setFlag(CSF_RETURN, val);
}

int consoleScope::breakStmt() {
	return getFlag(CSF_BREAK);
}

int consoleScope::breakStmt(int val) {
	return setFlag(CSF_BREAK, val);
}

int consoleScope::continueStmt() {
	return getFlag(CSF_CONTINUE);
}

int consoleScope::continueStmt(int val) {
	return setFlag(CSF_CONTINUE, val);
}

int consoleScope::breakStmtAllowed() {
	return getFlag(CSF_BREAK_ALLOWED);
}

int consoleScope::breakStmtAllowed(int val) {
	return setFlag(CSF_BREAK_ALLOWED, val);
}

int consoleScope::continueStmtAllowed() {
	return getFlag(CSF_CONTINUE_ALLOWED);
}

int consoleScope::continueStmtAllowed(int val) {
	return setFlag(CSF_CONTINUE_ALLOWED, val);
}

int consoleScope::suspendStmt() {
	return getFlag(CSF_SUSPEND);
}

int consoleScope::suspendStmt(int val) {
	return setFlag(CSF_SUSPEND, val);
}

int consoleScope::suspendStmtAllowed() {
	return getFlag(CSF_SUSPEND_ALLOWED);
}

int consoleScope::suspendStmtAllowed(int val) {
	return setFlag(CSF_SUSPEND_ALLOWED, val);
}

int consoleScope::noAssignmentDisplay() {
	return getFlag(CSF_NO_ASSIGNMENT_DISPLAY);
}

int consoleScope::noAssignmentDisplay(int val) {
	return setFlag(CSF_NO_ASSIGNMENT_DISPLAY, val);
}

int consoleScope::dynStmtVariableCollect() {
	return getFlag(CSF_DYN_STMT_VARIABLE_COLLECT);
}
 
int consoleScope::dynStmtVariableCollect(int val) {
	return setFlag(CSF_DYN_STMT_VARIABLE_COLLECT, val);
}

int consoleScope::resetRequested() {
	return getFlag(CSF_RESET_REQUESTED);
}

int consoleScope::resetRequested(int val) {
	return setFlag(CSF_RESET_REQUESTED, val);
}

int consoleScope::supressWarnings() {
	return getFlag(CSF_SUPRESS_WARNINGS);
}

int consoleScope::supressWarnings(int val) {
	return setFlag(CSF_SUPRESS_WARNINGS, val);
}

int consoleScope::supressErrors() {
	return getFlag(CSF_SUPRESS_ERRORS);
}

int consoleScope::supressErrors(int val) {
	return setFlag(CSF_SUPRESS_ERRORS, val);
}

int consoleScope::externalAssignVariable(const std::string &name, const e3ga &val, int drawMode /*= 0*/) {
	consoleVariable *valueCv = new consoleVariable("", val);
	if (drawMode) valueCv->drawMode(drawMode);

	consoleVariable *targetCv = new consoleVariable(name, e3ga(0.0));

	consoleVariable *resultCv = assignVariable(targetCv, valueCv);
	delete resultCv;

	delete targetCv;
	delete valueCv;

	return 0;
}

int consoleScope::externalLookupVariable(const std::string &name, int global, e3ga &val) {
	consoleVariable *cv, *castCv;
	if (lookupVariable(name, global, &cv) == 0) {
		castCv = cv->castToE3ga();
		val = castCv->e();
		delete cv;
		delete castCv;
		return 0;
	}
	else {
		val = 0;
		return -1;
	}
}


consoleGlobalScope::consoleGlobalScope(consoleGlobalScope *m_parent /* = NULL*/) : consoleScope("global scope", m_parent, 0) {
	initToNothing();
	m_idCount = 1; // force static m_idCount to 0

	if (m_parent == NULL) setFlag(CSF_SUSPEND_ALLOWED, 1); // the only place where suspend is allowed

	// add all predefined functions
	int i = 0;
	while (c_consoleFunc[i].name) {
		addFunction(c_consoleFunc + i);
		i++;
	}
	
	m_defaultModel = -1;
	m_ip = "hip";
}

consoleGlobalScope::~consoleGlobalScope() {
	clearConsoleAssignmentList();

	int i;
	for (i = 0; i < m_suspendedStmtListLength; i++) {
		if (m_suspendedStmtList[i].stmtList) delete m_suspendedStmtList[i].stmtList;
		if (m_suspendedStmtList[i].suspendIdcs)  free(m_suspendedStmtList[i].suspendIdcs);
	}
	freeDynStmtVariables();

	initToNothing();
}

void consoleGlobalScope::initToNothing() {

	m_suspendedStmtList = 0;
	m_suspendedStmtListLength = 0;
	//m_nbDynStmtVariables = 0;
	m_dynStmtVariables = NULL;

}


consoleScope* consoleGlobalScope::subScope() {
	consoleGlobalScope *ss = new consoleGlobalScope(this);
	ss->flags(flags()); // copy flags 
	ss->setFlag(CSF_SUSPEND_ALLOWED, 0); // clear the suspend allowed flag (suspend is only allowed in outermost global scope)
	return ss;
}

consoleVariable *consoleGlobalScope::assignVariable(consoleVariable *target, consoleVariable *value) {
	/*
	Goal of this function:
	If a variable is assigned in the global scope, make it a true object that can be displayed

    Also: apply auto color function
	*/

	// if autocolor is on, call the auto color function
	consoleVariable *acCv = NULL, *tVc;
	lookupVariable(target->name(), 1, &tVc);

	if ((!(value->drawMode() & OD_HIDE_ALWAYS)) &&
		((tVc == NULL) || (!(tVc->drawMode() & OD_HIDE_ALWAYS)))) { // never apply autocolor to internal global variables like cam[pos|ori]
		lookupVariable("autocolor", 1, &acCv);
		if (acCv && acCv->isTrue()) { // auto color must be true
			value = new consoleVariable("", value); // duplicate value, cause consoleExecFunc will delete it... (todo:why????)
			value->next(NULL);
			value->rhs(1);
			value = consoleExecFunc(this, "autocolorfunc", value);
			value->rhs(1);
		}
		if (acCv) delete acCv;
	}
	if (tVc) delete tVc;

	// save color state; set color in state
	float tempC[4];
	memcpy(tempC, g_state->m_fgColor, 4 * sizeof(float));
	g_state->setColor("fgcolor", value->color());

	// if batch argument, don't alter the hide property of the target
	int drawMode = value->drawMode();
	if (target->functionArgument()) {
		object *o = g_state->getObjectPtrByName(target->name());
		if (!o)	drawMode |= OD_HIDE;
	}

	// assign value to variable
	if (value->model() == MVI_E3GA)
		g_state->addE3gaObject(value->e(), target->name(), drawMode, value->creationFlags(), value->forceFlags());
	else if (value->model() == MVI_P3GA)
		g_state->addP3gaObject(value->p(), target->name(), drawMode, value->creationFlags(), value->forceFlags());
	else if (value->model() == MVI_C3GA)
		g_state->addC3gaObject(value->c(), target->name(), drawMode, value->creationFlags(), value->forceFlags());
	else if (value->model() == MVI_C5GA)
		g_state->addC5gaObject(value->c5(), target->name(), drawMode, value->creationFlags(), value->forceFlags());
	else if (value->model() == MVI_I2GA)
		g_state->addI2gaObject(value->i2(), target->name(), drawMode, value->creationFlags(), value->forceFlags());

	// restore color state
	g_state->setColor("fgcolor", tempC);

	// remeber which variables were assigned, so we can show / hide them later on (this depends on whether the statement ended in a comma or a semicolon
	// -And don't do this for batch arguments
	if ((!(value->drawMode() & OD_HIDE_ALWAYS)) && (!target->functionArgument()))
		addConsoleAssignmentList(target->name(), value->forceFlags());

	setVariable(target->name());

	return (acCv) ? value : new consoleVariable("", value); // (don't add to local scope->) consoleScope::assignVariable(target, value);
}

int consoleGlobalScope::dynStmtVariable(const std::string &pname) {
	if (m_parentScope) return m_parentScope->dynStmtVariable(pname);
	else {
		// strip name of array indices
		std::string name(pname);
		std::string::size_type idx = name.find('[');
		if (idx != std::string::npos)
			name.erase(idx);

		if (m_dynStmtVariables == NULL) m_dynStmtVariables = new std::set<std::string>();
		m_dynStmtVariables->insert(name);

		return 0;
	}
}

std::set<std::string> *consoleGlobalScope::getDynStmtVariables() {
	std::set<std::string> *vars = m_dynStmtVariables;
	m_dynStmtVariables = NULL;
	return vars;
}

int consoleGlobalScope::freeDynStmtVariables() {
	if (m_dynStmtVariables) {
		delete m_dynStmtVariables;
		m_dynStmtVariables = NULL;
	}
	return 0;
}



int consoleGlobalScope::lookupVariable(int sid, const std::string &name, int global, consoleVariable **variable) {
	*variable = NULL;

	// lookup in this local (==global) scope
	if (consoleScope::lookupVariable(sid, name, global, variable) == 0) return 0;

	// attempt lookup in state object list
	object *objectPtr = g_state->getObjectPtrByName(name);
	if (objectPtr == NULL) return -1; // no object of that name found

	switch (objectPtr->m_type) {
	case OT_E3GA:
		*variable = new consoleVariable(name, &((e3gaObject*)objectPtr)->m_mv);
		break;
	case OT_P3GA:
		*variable = new consoleVariable(name, &((p3gaObject*)objectPtr)->m_mv);
		break;
	case OT_C3GA:
		*variable = new consoleVariable(name, &((c3gaObject*)objectPtr)->m_mv);
		break;
	case OT_C5GA:
		*variable = new consoleVariable(name, &((c5gaObject*)objectPtr)->m_mv);
		break;
	case OT_I2GA:
		*variable = new consoleVariable(name, &((i2gaObject*)objectPtr)->m_mv);
		break;
	default: 
		return -1; // object is not of GA type 
	}

	// copy properties such as color and draw mode flags
	(*variable)->color4(objectPtr->fgColor());
	(*variable)->creationFlags(((objectPtr->m_dmMenuIdx >= 0) ? ((objectPtr->m_dmMenuIdx+1) << OC_DMBASE): 0) );
	(*variable)->drawMode(objectPtr->m_drawMode);
//	(*variable)->drawMode(objectPtr->m_drawMode ^ (objectPtr->m_drawMode & (OD_HIDE | OD_HIDE_ALWAYS)));


	(*variable)->rhs(1);
	(*variable)->lhs(1);

	return 0;
}

int consoleGlobalScope::startStatement() {
	clearConsoleAssignmentList();
	return consoleScope::startStatement();
}

int consoleGlobalScope::endStatement(consoleVariable *result, int verbose) {
	if (!noAssignmentDisplay()) {
		g_state->removeObject("ans");
		if (verbose) displayConsoleAssignmentList(result);
		else hideConsoleAssignmentList(result);	
	}
	return consoleScope::endStatement(result, verbose);
}

int consoleGlobalScope::addConsoleAssignmentList(const std::string name, int forceFlags) {
	m_consoleAssignmentList.push_back(caItem(name, forceFlags));

	return 0;
}

int consoleGlobalScope::clearConsoleAssignmentList() {
	m_consoleAssignmentList.clear();
		
	return 0;
}

consoleVariable *consoleGlobalScope::displayConsoleAssignmentList(consoleVariable *ans) {
	int err;
	consoleVariable *cv = NULL;
	object *o;

	// assign 'ans' to variable named 'ans' :)
	if (m_consoleAssignmentList.size() == 0) {
		assignVariable(new consoleVariable("ans", ans), ans);
	}

	CAI cai;
	for (cai = m_consoleAssignmentList.begin(); cai != m_consoleAssignmentList.end(); cai++) {
		// todo test: process each variable only once
//		if (processedVariables.find(cai->name) != processedVariables.end()) continue;
//		processedVariables.insert(cai->name);
//		std::cout << cai->name << std::endl;

		if (err = lookupVariable(cai->name, 1, &cv)) continue;
		if (cv->drawMode() & OD_HIDE_ALWAYS) continue;
		if (cv->drawMode() & OD_MUTE) continue;

		consoleVariableFree(consoleExecFunc(this, "print", cv));

		o = NULL;
		if ((o = g_state->getObjectPtrByName(cai->name)) && 
			(!(cai->forceFlags & OFF_HIDE))) {
			o->show();
		}

		if ((cai == m_consoleAssignmentList.end()) && gui_state && o) gui_state->setCurrentObject(o);
	}

	clearConsoleAssignmentList();

	return ans;
}

consoleVariable * consoleGlobalScope::hideConsoleAssignmentList(consoleVariable *ans) {
	object *o;

	// if list is empty, just return 'ans;
	if (m_consoleAssignmentList.size() == 0)
		return ans;

	CARI cari;
	for (cari = m_consoleAssignmentList.rbegin(); cari != m_consoleAssignmentList.rend(); cari++) {
		if ((!(cari->forceFlags & OFF_HIDE)) && 
			(o = g_state->getObjectPtrByName(cari->name))) {
				o->hide();
		}
	}

	clearConsoleAssignmentList();
	return ans;
}

int consoleGlobalScope::resumeStmtList() {
	if (m_suspendedStmtListLength) {
//		printf("Resuming!\n");

		// get index into suspended statement list
		int idx = m_suspendedStmtListLength-1;

		// get the statement
		consoleStmtListStmt *stmtList = m_suspendedStmtList[idx].stmtList;

		// set the resume indices
		setResumeIdcs(m_suspendedStmtList[idx].suspendIdcs); // memory of indices will be freed by scope later on

		// the stmtList has been removed, so lower its length
		m_suspendedStmtListLength--;

		return execStmtList(stmtList); // this will either delete stmtList, or put it back on the list
	}
	else return 0;
}

int consoleGlobalScope::addSuspendStmtList(consoleStmtListStmt *stmtList, int *suspendIdcs) {
	m_suspendedStmtList = (struct suspendList*)realloc(m_suspendedStmtList, (m_suspendedStmtListLength + 1) * sizeof(struct suspendList));
	m_suspendedStmtList[m_suspendedStmtListLength].stmtList = stmtList;
	m_suspendedStmtList[m_suspendedStmtListLength].suspendIdcs = suspendIdcs;
	m_suspendedStmtListLength++;
	return 0;
}


int consoleGlobalScope::execStmtList(consoleStmtListStmt *stmtList) {
	if (stmtList) {

		consoleVariable *cv = stmtList->execute(this);
		if (cv) delete cv;

		// handle suspension
		if (suspendStmt()) {
//			cprintf("SuspendStmt!!!!!!!!!!!!!!\n");
			addSuspendStmtList(stmtList, getSuspendIdcs());
		}
		else delete stmtList;
	}
	return 0;
}


