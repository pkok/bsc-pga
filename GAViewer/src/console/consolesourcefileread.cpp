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

#include <fstream>
#include <iostream>
#include <string>
//#include <ios>

#include "../state.h"
#include "../osdep.h"
#include "consolescope.h"
#include "consolestatement.h"
#include "console.h"
#include "consolevariable.h"

using namespace std;

#include <antlr/RecognitionException.hpp>
#include <antlr/TokenStreamRecognitionException.hpp>

#include "ConsoleLexer.hpp"
#include "consoleparserwrapper.h"


/*
Read a source file, parses it, and adds possible functions to the global scope.
*/

int state::consoleSourceFileRead(const char *filename) {
	consoleStmtListStmt *sl = NULL;

	cprintf("Parsing '%s'", filename);

	setWorkingDirectory(filename, true);

	try {
		std::fstream input(filename, std::ios::in);
		ConsoleLexer lexer(input);
		ConsoleParserWrapper parser(lexer);
		sl = parser.input();
	} 
	catch (...) {
		cprintf("state::consoleSourceFileRead(): exception while reading or parsing '%s'\n", filename);
	}

	if (sl) {
		//consoleVariable *cv = sl->execute(g_state->m_globalScope);
		// if (cv) delete cv;
		g_state->m_globalScope->execStmtList(sl);
		sl = NULL;
		return 0;
	}

	return -1;
}

int state::consoleSourceDirRead(const char *dirname) {
	u_dirEnt *dir = u_dirOpen(dirname, NULL);
	if (dir == NULL) {
		cprintf("state::consoleSourceDirRead(): Could not open directory '%s'\n", dirname);
		return -1;
	}

	cprintf("Reading all .g files in '%s'\n", dirname);

	char filename[1024], fullname[1024];
	int t, l;

	while ( (t = u_dirNext(dir, filename, 1023)) != U_DIR_END) {
		if (filename[0] == '.') continue;
		u_dirFullName(dir, filename, fullname, 1023);
		if (t == U_DIR_DIR) {
			consoleSourceDirRead(fullname);
		}
		else if (t == U_DIR_FILE) {
			l = strlen(fullname);
			if ((l > 1) && (!strcmpnc(fullname + l - 2, ".g")))
				consoleSourceFileRead(fullname);
		}
	}

	u_dirClose(dir);

	return 0;
}
