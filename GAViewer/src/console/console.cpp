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
#include <string.h>

#include <iostream>
#include <string>
#include <sstream>


#include "console.h"
#include "../state.h"

//#include "consoleparse.h"

#include "consolescope.h"
#include "consolestatement.h"

using namespace std;
#include <antlr/RecognitionException.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>
#include <antlr/ANTLRException.hpp>
#include "ConsoleLexer.hpp"
#include "consoleparserwrapper.h"

void g_consoleCommandCallback(const char *cmd, void *cbArg) {
	if (cbArg == NULL) return;

	int l = (int)strlen(cmd), i;
	char *buf = (char*)malloc(l + 4);
	strcpy(buf, cmd);
	
	// check if last character is a ',' or ';', if not, then append ','
	for (i = l-1; (i>0) && (buf[i] < ' '); i--);
	if ((buf[i] != ',') && (buf[i] != ';')) {
		strcpy(buf + i + 1, "\n,");
	}

	((state*)cbArg)->consoleCommandCallback(buf);
	free(buf);
}

consoleStmtListStmt *consoleParse(const char *cmd, const char *wd /* = NULL */) {
	consoleStmtListStmt *sl = NULL;
	string cmdStr(cmd);
	istringstream input(cmdStr);

	if (wd) g_state->setWorkingDirectory(wd);
	else g_state->setWorkingDirectory(g_state->m_initialWorkingDirectory);

	try {
		ConsoleLexer lexer(input);
		ConsoleParserWrapper parser(lexer);
		sl = parser.input();
	}
	catch (ANTLRException &) {

	}
	catch (...) {
		cprintf("Non-ANTLRException during parsing\n");
	}

/*	if (sl) { // temp test
		char *readStr = sl->string();
		printf("read: '%s'\n", readStr);
		free(readStr);
	}*/

	return sl;
}

int state::consoleCommandCallback(const char *cmd) {
	consoleStmtListStmt *stmtList = consoleParse(cmd);

	if ((stmtList == NULL) || (stmtList->dummy())) {
			// if we have suspended stmtLists resume the top one on the stack
//			cprintf("Dummy!\n");
			if (stmtList) delete stmtList;
			g_state->m_globalScope->resumeStmtList();
	}
	else g_state->m_globalScope->execStmtList(stmtList);

	if (m_globalScope->resetRequested()) {
		g_state->reset();
		return 0;
	}

	g_state->updateDynStmts();

	return 0;
}
