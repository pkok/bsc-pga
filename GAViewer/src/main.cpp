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
#include <math.h>

#include <FL/Fl.H>

#include "gafile.h"
#include "state.h"
#include "uistate.h"

#include "util.h"
#include "osdep.h"

#include "geosphere.h"

#include "mt19937-2.h"


// test:
#include <map>
#include <iostream>
#include <string>
#include "object.h"

const char *g_version = "0.86";

/*
To compile without a console for win32: 
Define WIN32_NO_CONSOLE  (use settings 
and use a 'win32 application' project in MSVC6.0

In properties->linker->system, set to windows or console application
*/


#ifdef WIN32_NO_CONSOLE
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow) {
	// make up the argc and argv from lpCmdLine
	int argc = 1;
	char **argv = (char**)malloc(sizeof(char*));
	int idx = 0, startIdx;

	argv[0] = strdup("GAViewer"); // first argument is executable name

	while (lpCmdLine[idx]) {
		while (lpCmdLine[idx] && (lpCmdLine[idx] <= 32)) idx++; // skip space
		if (!lpCmdLine[idx]) break;
		startIdx = idx;
		while (lpCmdLine[idx] > 32) idx++; // search for end of argument

		// create new argument entry
		argv = (char**)realloc(argv, sizeof(char*) * (argc + 1));
		argv[argc] = (char*)malloc(idx - startIdx + 1);

		// copy string
		memcpy(argv[argc], lpCmdLine + startIdx, idx - startIdx);
		argv[argc][idx - startIdx] = 0;

		argc++;
	}
#else /* assume UNIX or WIN32 with console */
int main(int argc, char *argv[]) {    
#endif 

//	const char *initialFile = "txt_files/font_samples.txt"; // change this to 'NULL' to prevent it from automatically trying to load this file
	const char *initialFile = NULL; //"asciifile.geo"; // change this to 'NULL' to prevent it from automatically trying to load this file
	const char *initialPlayList = NULL;
	bool enableNet = false;
	std::string defaultNetPort;

	int i;
	for (i = 1; i < argc; i++) {
		if (((!strcmp(argv[i], "-f")) || (!strcmp(argv[i], "-file"))) && ((argc - i) >= 2)) {
			initialFile = argv[i+1];
			memmove(argv + i, argv + i + 2, (argc - i - 2) * sizeof(char*));
			argc -= 2;
			i -= 2;
		}
		else if (((!strcmp(argv[i], "-l")) || (!strcmp(argv[i], "-playlist"))) && ((argc - i) >= 2)) {
			initialPlayList = argv[i+1];
			memmove(argv + i, argv + i + 2, (argc - i - 2) * sizeof(char*));
			argc -= 2;
			i -= 2;
		}
		else if (!strcmp(argv[i], "-net")) {
			enableNet = true;
			int nbArgsEaten = 1;
			if (((argc - i) >= 2) && isdigit(argv[i+1][0])) {
				defaultNetPort = argv[i+1];
				nbArgsEaten = 2;
			}
			memmove(argv + i, argv + i + nbArgsEaten, (argc - i - nbArgsEaten) * sizeof(char*));
			argc -= nbArgsEaten;
			i -= nbArgsEaten;
		}
	}

	g_state = new state();

	if ((!enableNet) && (g_state->m_nbNetServers <= 0)) {
		// disable network connection (otherwise the value '-1' signals for the net port gets opened by default)
		g_state->m_nbNetServers = 0;
	}
	if (defaultNetPort.length() > 0)
		g_state->m_defaultNetPort = defaultNetPort;


	 //temp todo
/*	int consoleTest(); 
	int consoleTest2(); 
	int consoleTest3(); 
	double t = u_timeGet();
	int result = consoleTest3();
	printf("T: %f/n", u_timeGet() - t);
	return result;*/
	// end of temp todo


	gui_state = new UIstate(argc, argv);

	if (initialPlayList) 
		g_state->openPlayList(initialPlayList); // todo: arguments
	else if (initialFile)
		g_state->openGAfile(initialFile); // todo: arguments


	Fl::run();

	// todo: delete the entire stack...
	g_state->deleteGAfileStack();
	//g_state->handleDeleteGAfile();

	// we must run a second time, in case the UI has a question to ask in a popup box...
	Fl::run();

//	printf("Yo! %d %d/n", g_nbFPAllocated, g_nbBoxAllocated);


	return 0;
}

