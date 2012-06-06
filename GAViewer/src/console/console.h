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

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

class consoleScope;
class consoleVariable;

extern void g_consoleCommandCallback(const char *cmd, void *cbArg);

class consoleStmtListStmt;
consoleStmtListStmt *consoleParse(const char *cmd, const char *wd = NULL); // wd = working directory

// evaluates and expressions list
// frees all resources in 'cv'
// returns new consoleVariable
consoleVariable *consoleEvalExprList(consoleScope *s, consoleVariable *cv);

int stateExistConsoleFunction(const char *name);
void *consoleVariableScalar(const char *name, double val);
//void *consoleVariableName(const char *name); // returns the variable with name 'name', if any
int consoleVariableSetOperator(void *cv, int op);
void consoleVariableFree(void *cv);

#endif /* _CONSOLE_H_ */
