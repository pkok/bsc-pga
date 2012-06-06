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

#ifndef _CONSOLE_SCOPE_H_
#define _CONSOLE_SCOPE_H_

#include <map>
#include <string>
#include <vector>
#include <set>

#include "consolefunction.h"

class consoleVariable;
class consoleFuncStmt;
class consoleStmtListStmt;

#define CSF_RETURN (1 << 0)
#define CSF_FUNCTION (1 << 1)
#define CSF_BREAK (1 << 2)
#define CSF_CONTINUE (1 << 3)
#define CSF_SUSPEND (1 << 4)
#define CSF_BREAK_ALLOWED (1 << 5)
#define CSF_CONTINUE_ALLOWED (1 << 6)
#define CSF_SUSPEND_ALLOWED (1 << 7)
#define CSF_NO_ASSIGNMENT_DISPLAY (1 << 8)
#define CSF_DYN_STMT_VARIABLE_COLLECT (1 << 9)
#define CSF_RESET_REQUESTED (1 << 10)
#define CSF_SUPRESS_WARNINGS (1 << 11)
#define CSF_SUPRESS_ERRORS (1 << 12)
// when adding a new flag that should survive statement starts, add it to 'consoleScope::startStatement()' list!

class consoleScope {
public:
	consoleScope(const std::string &fname, consoleScope *parentScope, int id = -1);
	virtual ~consoleScope();

	inline int existFunction(const std::string &name, int global) {return existFunction(m_id, name, global);}
	inline int lookupFunction(const std::string &name, int global, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func) {return lookupFunction(m_id, name, global, nbArg, arg, argType, func);}
	inline int lookupVariable(const std::string &name, int global, consoleVariable **variable) {return lookupVariable(m_id, name, global, variable);}

	int existFunction(int sid, const std::string &name, int global);
	int lookupConstant(int sid, const std::string &name, int global, consoleVariable **variable);
	int lookupFunction(int sid, const std::string &name, int global, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func);
	virtual int lookupVariable(int sid, const std::string &name, int global, consoleVariable **variable);
	int removeVariable(const std::string &name);

	virtual consoleScope*subScope(); // returns a new scope with the same ID, properties, class, a child of this scope

	virtual int startStatement(); // allows a scope to prepare for a statement (default does nothing)
	virtual int endStatement(consoleVariable *result, int verbose);

	virtual consoleVariable *assignVariable(consoleVariable *target, consoleVariable *value);

	virtual int dynStmtVariable(const std::string &name); // called by consoleVariableStatement->execute for every global variable, to collect all variables used in a dynamic statement

	int addUserFunction(consoleFuncStmt *funcStmt); // adds funcStmt to this scope; do not delete funcStmt after this!
	//int addDummyFunction(const char *name); // adds a dummy function (=name only) to this scope (used during parsing)
	//int removeDummyFunctions(); // removes all dummy functions from this scope

	// temp test
	inline int setFunction(const std::string &ident) {return setFunctionOrVariable(ident, true);} // sets 'ident is function in this scope'
	int setVariable(const std::string &ident) {return setFunctionOrVariable(ident, false);} // sets 'ident is variable in this scope'
	int setFunctionOrVariable(const std::string &ident, bool value);
	int isFunction(const std::string &ident) const; // returns true if ident is a function
	std::map<std::string, bool> m_identifierTable;
	typedef std::map<std::string, bool>::iterator ITI;
	typedef std::map<std::string, bool>::const_iterator CITI;

	// a bunch of functions to set/get CSF_XXX flags:
	int funcStmt();
	int funcStmt(int val);
	int returnStmt();
	int returnStmt(int val);
	int breakStmt();
	int breakStmt(int val);
	int continueStmt();
	int continueStmt(int val);
	int suspendStmt();
	int suspendStmt(int val);
	int breakStmtAllowed();
	int breakStmtAllowed(int val);
	int continueStmtAllowed();
	int continueStmtAllowed(int val);
	int suspendStmtAllowed();
	int suspendStmtAllowed(int val);
	int noAssignmentDisplay();
	int noAssignmentDisplay(int val);
	int dynStmtVariableCollect();
	int dynStmtVariableCollect(int val);
	int resetRequested();
	int resetRequested(int val);
	int supressWarnings();
	int supressWarnings(int val);
	int supressErrors();
	int supressErrors(int val);

	int addSuspendIdx(int idx);
	int *getSuspendIdcs();
	int getResumeIdx();
	int setResumeIdcs(int *idcs);

	inline const std::string &innerProduct() const {return m_ip;}
	int setInnerProduct(const std::string &ip);
	int setDefaultModel(int model);
	inline int getDefaultModel() {return m_defaultModel;}

	inline int globalScope() {return m_id == 0;} // return true if this is the global scope

	consoleScope *deleteScope() {consoleScope *parent = m_parentScope; delete this; return parent;}

	inline const std::string &functionName() const {return m_functionName;}
	int functionName(const std::string &fname);

	inline int id() const {return m_id;}

	int externalAssignVariable(const std::string &name, const e3ga &val, int drawMode = 0); // used by none-console functions to assign a variable
	int externalLookupVariable(const std::string &name, int global, e3ga &val); // used by none-console functions to lookup a variable


protected:

	int lookupLocalVariable(int sid, const std::string &name, int global, consoleVariable **variable); // looks up a variable in _this_ scope
	int lookupFunctionRec(int sid, const std::string &name, int global, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func, int *bestDistance); // looks up the best matching function in all scopes

	int addFunction(const consoleFunc *func); // makes a copy of func, stores it in m_function list/tree
	int removeFunction(const std::string &nameWithArguments);
	int freeFunction(consoleFunc *f); // releases resources of f

//	std::map<const std::string, consoleFunc*/*, functionLess*/> m_functions;
	std::map<std::string, consoleFunc* /*, functionLess*/> m_functions;
	void removeAllFunctions();
	typedef std::map<std::string, consoleFunc* /*, functionLess*/>::iterator FI;
	typedef std::map<std::string, consoleFunc* /*, functionLess*/>::const_iterator CFI;
//	typedef std::map<const std::string, consoleFunc*/*, functionLess*/>::iterator FI;
//	typedef std::map<const std::string, consoleFunc*/*, functionLess*/>::const_iterator CFI;

public:
	class stringPtr {
	public:
		stringPtr(const std::string *s) : ptr(s) {}
		stringPtr(const std::string &s) : ptr(&s) {}
		~stringPtr() {}
		const std::string *ptr;
	};
	// objects are kept in a map, order by lexical order using stringPointerLess:
	struct stringPtrLess {
		inline bool operator()(const stringPtr a, const stringPtr b) const {return (*a.ptr) < (*b.ptr);}
	};
protected:
	typedef std::map<stringPtr, consoleVariable*, stringPtrLess> CVC;
//	typedef std::map<const stringPtr, consoleVariable*, stringPtrLess> CVC;
	typedef CVC::iterator CVI;
	CVC m_variables;
	void removeAllVariables();

/*	consoleVariable **m_variable;
	int m_nbVariables;*/

	consoleScope *m_parentScope;

	std::string m_functionName; // the name of the function this scope is tied to

	int m_defaultModel; // default model in which e1, e2, ni  etc are given (-1 for smallest enclosing)
	std::string m_ip; // inner product function

	int m_id; // each function scope has a unique ID (id 0 is global scope);
	static int m_idCount; // for each new function scope, a new ID is created

	int setFlag(int flag, int val); // CSF_XXX
	int getFlag(int flag) const; // CSF_XXX
	inline int flags(int f) {m_flags = f; return 0;}
	inline int flags() const {return m_flags;}

	// called by lookupConstant(); handles defaultModel, rhs, lhs, etc
	int processConstant(consoleVariable **variable);

private:
	int m_flags;


	int *m_suspendIdx; // length stored at first index
	int *m_resumeIdx;// length stored at first index

	void initToNothing();

};

class consoleGlobalScope : public consoleScope {
public:
	consoleGlobalScope(consoleGlobalScope *m_parent = NULL);
	virtual ~consoleGlobalScope();

	inline int lookupVariable(const std::string &name, int global, consoleVariable **variable) {return lookupVariable(m_id, name, global, variable);}

	virtual int lookupVariable(int sid, const std::string &name, int global, consoleVariable **variable);

	virtual consoleScope*subScope(); // returns a new scope with the same ID, properties, class


	virtual int startStatement(); // allows a scope to prepare for a statement (default does nothing)
	virtual int endStatement(consoleVariable *result, int verbose);

	//virtual consoleVariable *assignVariable(const char *name, consoleVariable *value);
	virtual consoleVariable *assignVariable(consoleVariable *target, consoleVariable *value);

	virtual int dynStmtVariable(const std::string &name); // called by consoleVariableStatement->execute, to collect all variables used in a dynamic statement
	std::set<std::string> *getDynStmtVariables(); // returns dynamic variables & nb collected so far, and clears the array
	int freeDynStmtVariables();

	int resumeStmtList();
	int addSuspendStmtList(consoleStmtListStmt *stmtList, int *suspendIdcs);
	int execStmtList(consoleStmtListStmt *stmtList);

	// adds constant 'name' (removes object 'name' if it exists)
	void addConstant(const std::string &name, consoleVariable *C);
	void removeConstant(const std::string &name);
	int lookupUserConstant(const std::string &name, consoleVariable **variable);
	int writeConstantsToGeoFile(FILE *F);
	
    void renameBuiltinConstant(const std::string &oldName, const std::string &newName);

	int clearConsoleAssignmentList();

protected:
	/*
	The assignment list is used to keep track of every variable/object that has 
	been assignment a value during the last statement. When a statement is
	completed, the assignment list is either hidden or displayed (depending on whether
	the assignment ended in a semicolon or a comma). After that, the list is cleared
	*/
	class caItem {
	public:
		caItem(std::string pname, int pforceFlags) : name(pname), forceFlags(pforceFlags) {}
		caItem(const caItem &i) : name(i.name), forceFlags(i.forceFlags) {}
		~caItem()  {}
		std::string name;
		int forceFlags; // force flags at time of assignment
	};
	std::vector<caItem> m_consoleAssignmentList;
	typedef std::vector<caItem>::iterator CAI;
	typedef std::vector<caItem>::reverse_iterator CARI;
	int addConsoleAssignmentList(std::string name, int forceFlags);
	consoleVariable *displayConsoleAssignmentList(consoleVariable *ans);
	consoleVariable *hideConsoleAssignmentList(consoleVariable *ans);



private:
	void initToNothing();


	struct suspendList {
		consoleStmtListStmt *stmtList;
		int *suspendIdcs;
	} *m_suspendedStmtList;
	int m_suspendedStmtListLength;

	std::set<std::string> *m_dynStmtVariables;

	//typedef std::map<std::string, std::auto_ptr<consoleVariable> >UCType;
	typedef std::map<std::string, consoleVariable >UCType;
	typedef UCType::iterator UCI;
	UCType m_userConstants;

/*	int m_nbDynStmtVariables;
	char **m_dynStmtVariable;*/
};

#endif /* _CONSOLE_SCOPE_H_ */
