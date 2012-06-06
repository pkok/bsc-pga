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

#ifndef _CONSOLE_STATEMENT_H_
#define _CONSOLE_STATEMENT_H_

#include <set>
#include <string>

#include <stdlib.h>
//#include "consolefunction.h"
// remove this once consolefunction is included again:
#define maxConsoleFuncArg 8



class consoleVariable;
class consoleExprListStmt;
class consoleStmtListStmt;
class consoleFuncArgSpecStmt;
class consoleFuncArgSpecListStmt;
class consoleScope;
class consoleCaseListStmt;
class consoleArrayIdxListStmt;

// TODO: make const what is const...

/*

Functions are global
Variables are local (globals can not be reached, or only explicitly through ::xxx) ???
Constants are global (or can be looked up by any scope?)

*/
#define CSF_VERBOSE (1 << 0) // if verbose is true, any variables assigned a value will be displayed and printed
#define CSF_LHS (1 << 1) // flag indicating that this statement is on the left hand side of an assignment
#define CSF_DUMMY (1 << 2) // flag indicating this is a dummy statement 
#define CSF_STMTLISTCHILD (1 << 3) // flag indicating that this is a child of a statement list
#define CSF_EVALREQUIRED (1 << 4) // flag indicating dynamic re-evaluation is required
#define CSF_FIRSTEVAL (1 << 5) // flag indicating the first evaluation of a dynamic statement is yet to come

class consoleStatement {
public:
	consoleStatement();
	consoleStatement(const consoleStatement &s); // copy constructor
	consoleStatement(int line, int column);
	virtual ~consoleStatement();

	virtual consoleStatement*copy() const = 0; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s) = 0;
	virtual char *string(int cr = 0, int tl = 0) = 0; // cr = carriage return requested selected positions; tl = tab level

//	virtual int usesVariable(const char *name, int global = 1); // checks if global variable 'name' is used in this statement ('global' indicates whether check is still in the global scope)

	int addChild(consoleStatement *s); 

/*	inline int inputIdx() const {return m_inputIdx;}
	inline int inputIdx(int inputIdx) {m_inputIdx = inputIdx; return 0;}*/
	inline int line() const {return m_line;}
	inline int column() const {return m_column;}
	inline int line(int l) {m_line = l; return 0;}
	inline int column(int c) {m_column = c; return 0;}
	inline int lineAndColumn(int l, int c) {line(l); return column(c);}


	inline int op() {return m_op;}
	int setOp(int op);
	int setOp(const char *filename, int line, int column, const char *op);

	int verbose(int v);
	int verbose();
	int lhs(int l);
	int lhs();
	int dummy();	

	int stmtListChild(int c); // if true, this statement is a direct child of a stmtlist
	int stmtListChild();

	int evalRequired(int e);  // if true, this statement requires re-evaluation (dynamic stmt, variable modified)
	int evalRequired();

	int firstEval(int e);  
	int firstEval();


protected:
	int quote(const char *str); // return true if this name should be in quotes (contains tab, space, etc)

	int m_line, m_column; // position in file where the first token of this statement appeared

	int m_op;

	int m_nbChildren;
	consoleStatement **m_child;

	int setFlag(int flag, int val); // CSF_XXX
	int getFlag(int flag) const; // CSF_XXX
private:
	void initToNothing();
	int m_flags;
};

class consoleDummyStmt : public consoleStatement {
public:
	consoleDummyStmt(int line, int column);
	consoleDummyStmt(const consoleDummyStmt &s); // copy constructor
	virtual ~consoleDummyStmt();

	virtual consoleStatement* copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	void initToNothing();
};


class consoleVariableStmt : public consoleStatement {
public:
	consoleVariableStmt(int line, int column, const char *name, int global = 0, consoleArrayIdxListStmt *arrayIdx = NULL);
	consoleVariableStmt(const consoleVariableStmt &s); // copy constructor
	virtual ~consoleVariableStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

//	virtual int usesVariable(const char *name, int global = 1); // checks if global variable 'name' is used in this statement ('global' indicates whether check is still in the global scope)

protected:
	int m_global;
	char *m_name;

private:
	int getFullname(consoleScope *s, char *buf);
	void initToNothing();
};

class consoleConstantScalarStmt : public consoleStatement {
public:
	consoleConstantScalarStmt(int line, int column, double d);
	consoleConstantScalarStmt(const consoleConstantScalarStmt &s); // copy constructor
	virtual ~consoleConstantScalarStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

protected:
	double m_value;
private:
	void initToNothing();
};

class consoleFuncArgListStmt : public consoleStatement {
public:
	consoleFuncArgListStmt(consoleExprListStmt *el);
	consoleFuncArgListStmt(const consoleFuncArgListStmt &s); // copy constructor
	virtual ~consoleFuncArgListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s);  // can return a list of cvs?
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

//	consoleStatement *removeDynStmt();

private:
	void initToNothing();
};

class consoleFuncCallStmt : public consoleStatement {
public:
	consoleFuncCallStmt(int line, int column, const char *name, consoleFuncArgListStmt *arg, int global);
	consoleFuncCallStmt(const consoleFuncCallStmt &s); // copy constructor
	virtual ~consoleFuncCallStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

protected:
	inline consoleFuncArgListStmt* argList() {return ((m_nbChildren == 1) && m_child[0]) ? (consoleFuncArgListStmt*)m_child[0] : NULL;}
	char *m_name;
	int m_global;
private:
	void initToNothing();
};

class consoleExprListStmt : public consoleStatement {
public:
	consoleExprListStmt(consoleStatement *expr);
	consoleExprListStmt(const consoleExprListStmt &s); // copy constructor
	virtual ~consoleExprListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	void initToNothing();
};

class consoleParExprStmt : public consoleStatement {
public:
	consoleParExprStmt(int line, int column, consoleExprListStmt *el);
	consoleParExprStmt(const consoleParExprStmt &s); // copy constructor
	virtual ~consoleParExprStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	void initToNothing();
};

class consoleWhileStmt : public consoleStatement {
public:
	consoleWhileStmt(int line, int column, consoleExprListStmt *el, consoleStatement *s);
	consoleWhileStmt(const consoleWhileStmt &s); // copy constructor
	virtual ~consoleWhileStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	inline consoleExprListStmt *condEl() {return (m_nbChildren > 0) ? (consoleExprListStmt*)m_child[0] : NULL;}
	inline consoleStatement *stmt() {return (m_nbChildren > 1) ? m_child[1] : NULL;}

	void initToNothing();
};

class consoleForStmt : public consoleStatement {
public:
	consoleForStmt(int line, int column, consoleExprListStmt *p_initEl, consoleExprListStmt *p_condEl, consoleExprListStmt *p_execEl, consoleStatement *s);
	consoleForStmt(const consoleForStmt &s); // copy constructor
	virtual ~consoleForStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	inline consoleExprListStmt *initEl() const {return m_initEl;}
	inline consoleExprListStmt *condEl() const {return m_condEl;}
	inline consoleExprListStmt *execEl() const {return m_execEl;}

	inline consoleStatement *stmt() {return (m_nbChildren > 0) ? m_child[0] : NULL;}

	consoleExprListStmt *m_initEl;
	consoleExprListStmt *m_condEl;
	consoleExprListStmt *m_execEl;

	void initToNothing();
};

class consoleIfElseStmt : public consoleStatement {
public:
	consoleIfElseStmt(int line, int column, consoleExprListStmt *el, consoleStatement *ifS, consoleStatement *elseS = NULL);
	consoleIfElseStmt(const consoleIfElseStmt &s); // copy constructor
	virtual ~consoleIfElseStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	inline consoleStatement *condStmt() {return (m_nbChildren > 0) ? m_child[0] : NULL;}
	inline consoleStatement *ifStmt() {return (m_nbChildren > 1) ? m_child[1] : NULL;}
	inline consoleStatement *elseStmt() {return (m_nbChildren > 2) ? m_child[2] : NULL;}

	void initToNothing();
};

class consoleSwitchStmt : public consoleStatement {
public:
	consoleSwitchStmt(int line, int column, consoleExprListStmt *cond, consoleCaseListStmt *caseList);
	consoleSwitchStmt(const consoleSwitchStmt &s); // copy constructor
	virtual ~consoleSwitchStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	inline consoleExprListStmt *condStmt() {return (m_nbChildren > 0) ? (consoleExprListStmt*)m_child[0] : NULL;}
	inline consoleCaseListStmt *caseListStmt() {return (m_nbChildren > 1) ? (consoleCaseListStmt*)m_child[1] : NULL;}

	void initToNothing();
};

class consoleCaseStmt : public consoleStatement {
public:
	consoleCaseStmt(int line, int column, consoleExprListStmt *caseStmt, consoleStmtListStmt* stmtList);
	consoleCaseStmt(const consoleCaseStmt &s); // copy constructor
	virtual ~consoleCaseStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

	inline consoleExprListStmt *exprListStmt() {return (m_nbChildren > 0) ? (consoleExprListStmt*)m_child[0] : NULL;}
	inline consoleStmtListStmt *stmtListStmt() {return (m_nbChildren > 1) ? (consoleStmtListStmt*)m_child[1] : NULL;}

	void initToNothing();
};

class consoleCaseListStmt : public consoleStatement {
public:
	consoleCaseListStmt(int line, int column, consoleCaseStmt *caseStmt);
	consoleCaseListStmt(const consoleCaseListStmt &s); // copy constructor
	virtual ~consoleCaseListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

	consoleCaseStmt *caseStmt(int idx) {return ((idx < m_nbChildren) ? (consoleCaseStmt *)m_child[idx] : NULL);};

	void initToNothing();
};

class consoleReturnStmt : public consoleStatement {
public:
	consoleReturnStmt(int line, int column, consoleExprListStmt *expr);
	consoleReturnStmt(const consoleReturnStmt &s); // copy constructor
	virtual ~consoleReturnStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	void initToNothing();
};

#define CBS_BREAK 0
#define CBS_CONTINUE 1
#define CBS_SUSPEND 2

class consoleBreakStmt : public consoleStatement {
public:
	consoleBreakStmt(int line, int column, int type);
	consoleBreakStmt(const consoleBreakStmt &s); // copy constructor
	virtual ~consoleBreakStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	int m_type; // CBS_XXX
	void initToNothing();
};

class consoleStmtListStmt : public consoleStatement {
public:
	consoleStmtListStmt();
	consoleStmtListStmt(int line, int column);
	consoleStmtListStmt(consoleStatement *stmt);
	consoleStmtListStmt(const consoleStmtListStmt &s); // copy constructor
	virtual ~consoleStmtListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s);  // returns execute(s, stmtIdx)
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level
	consoleVariable *execute(consoleScope *s, int stmtIdx); 

	int dummy();	// returns true if only one child, which is a dummy

	int setDynStmtVariables(std::set<std::string> * variables);
	int dependsOn(const std::string &name); // checks if the outcome of this statement depends on global variable 'name' (by checking m_dynStmtVariable list)

private:
	int freeDynStmtVariables();
	std::set<std::string> *m_dynStmtVariables;


	void initToNothing();
//	int m_suspendStmtChildIdx; // the idx of the suspend child
};

class consoleFuncDeclStmt: public consoleStatement {
public:
	consoleFuncDeclStmt(int line, int column, const char *name, consoleFuncArgSpecListStmt *arg, int function);
	consoleFuncDeclStmt(const consoleFuncDeclStmt &s); // copy constructor
	virtual ~consoleFuncDeclStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s);  // always returns 0.0
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

	consoleFuncArgSpecListStmt *argSpecList() {return (consoleFuncArgSpecListStmt *)m_child[0];}
	inline const char *name() const {return m_name;}

protected:
	char *m_name;
	int m_function;

private:
	void initToNothing();
};

class consoleFuncStmt : public consoleStatement {
public:
	consoleFuncStmt(int line, int column, const char *name, consoleFuncArgSpecListStmt *arg, consoleStmtListStmt *sl, int function);
	consoleFuncStmt(const consoleFuncStmt &s); // copy constructor
	virtual ~consoleFuncStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s);  // this one does only sets the 'funcStmt' flag
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level
	consoleVariable *execute(consoleScope *s, consoleVariable *arg[maxConsoleFuncArg]); // this one does all the work

	inline const char *name() const {return m_name;}
	inline const int function() const {return m_function;}

	consoleFuncArgSpecListStmt *argSpecList() {return (consoleFuncArgSpecListStmt *)m_child[0];}
	consoleStmtListStmt *stmtList() {return (consoleStmtListStmt *)m_child[1];}

//	inline const char *filename() const {return m_filename;}
//	int filename(const char *filename);
	
protected:
	int m_function; // 1 = function, 0 = batch
	char *m_name;
	std::string m_workingDirectory; // the direcory the file containing this function was read from

private:
	void initToNothing();
};

class consoleFuncArgSpecStmt : public consoleStatement {
public:
	consoleFuncArgSpecStmt(int line, int column, const char *name, int model);
	consoleFuncArgSpecStmt(const consoleFuncArgSpecStmt &s); // copy constructor
	virtual ~consoleFuncArgSpecStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level
	int model() const {return m_model;}
	const char *name() const {return m_name;}

protected:
	int m_model;
	char *m_name;

private:
	void initToNothing();
};

class consoleFuncArgSpecListStmt : public consoleStatement {
public:
	consoleFuncArgSpecListStmt(int line, int column);
	consoleFuncArgSpecListStmt(int line, int column, consoleFuncArgSpecStmt *arg);
	consoleFuncArgSpecListStmt(const consoleFuncArgSpecListStmt &s); // copy constructor
	virtual ~consoleFuncArgSpecListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

	consoleFuncArgSpecStmt *argSpec(int idx) {return ((idx < m_nbChildren) ? (consoleFuncArgSpecStmt *)m_child[idx] : NULL);};

private:
	void initToNothing();
};

class consoleArrayIdxListStmt : public consoleStatement {
public:
	consoleArrayIdxListStmt(int line, int column, consoleExprListStmt *el);
	consoleArrayIdxListStmt(const consoleArrayIdxListStmt &s); // copy constructor
	virtual ~consoleArrayIdxListStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

	int execute(consoleScope *s, char *idxStr);
//	consoleFuncArgSpecStmt *argSpec(int idx) {return ((idx < m_nbChildren) ? (consoleFuncArgSpecStmt *)m_child[idx] : NULL);};

private:
	void initToNothing();
};

class consoleDynStmt : public consoleStatement {
public:
	consoleDynStmt(int line, int column, consoleStatement *stmt, const std::string &name);
	consoleDynStmt(const consoleDynStmt &s); // copy constructor
	virtual ~consoleDynStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	void initToNothing();

	std::string m_workingDirectory;
	std::string m_name;
};

class consoleSetStmt : public consoleStatement {
public:
	consoleSetStmt(int line, int column, const std::string &what, const std::string &value);
	consoleSetStmt(int line, int column, const std::string &what, int value);
	consoleSetStmt(const consoleSetStmt &s); // copy constructor
	virtual ~consoleSetStmt();

	virtual consoleStatement *copy() const; // returns a copy of 'this'

	virtual consoleVariable *execute(consoleScope *s); 
	virtual char *string(int cr = 0, int tl = 0); // cr = carriage return requested selected positions; tl = tab level

private:
	std::string m_what;
	std::string m_strValue;
	int m_intValue;
	void initToNothing();
};

#endif /* _CONSOLE_STATEMENT_H_ */
