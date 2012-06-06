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

#ifndef _CONSOLE_FUNCTION_H_
#define _CONSOLE_FUNCTION_H_

#include <string>

class consoleFuncStmt;
class consoleVariable;
class consoleScope;

#define maxConsoleFuncArg 8

/*
class consoleFunc {
public:
	consoleFunc();
	consoleFunc(const char *name, consoleFuncStmt *m_funcStmt, consoleVariable *(*m_funcPtr)(consoleScope *s, consoleVariable *arg[]), int m_nbArg, int m_arg[maxConsoleFuncArg]);
//	consoleFunc(const consoleFunc *f);
	~consoleFunc();

	int set(const consoleFunc *f);

	const char *m_name;
	consoleFuncStmt *m_funcStmt; // either funcStmt or funcPtr must be NULL (depending on whether this function is user declared)
	consoleVariable *(*m_funcPtr)(consoleScope *s, consoleVariable *arg[]);
	int m_nbArg;
	int m_arg[maxConsoleFuncArg];
};*/

// todo: turn consoleFunc into class
typedef struct consoleFunc_s {
	const char *name;
	consoleFuncStmt *funcStmt; // either funcStmt or funcPtr must be NULL (depending on whether this function is user declared)
	consoleVariable *(*funcPtr)(consoleScope *s, consoleVariable *arg[]);
	int nbArg;
	int arg[maxConsoleFuncArg];
} consoleFunc;


extern const consoleFunc c_consoleFunc[];

// executes function with name 'name'
// frees all resources in 'cv'
// returns new consoleVariable
consoleVariable *consoleExecFunc(consoleScope *s, const std::string &name, consoleVariable*cv);

// as consoleExecFunc(), but cut the list at 'cv', to enforce unary argument
consoleVariable *consoleExecUnaryFunc(consoleScope *s, const std::string &name, consoleVariable*cv);

std::string getFuncStringNameWithArguments(const consoleFunc *f, int argNames);


#endif /* _CONSOLE_FUNCTION_H_ */
