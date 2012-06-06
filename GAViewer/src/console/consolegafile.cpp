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

#include "consolegafile.h"

consoleGAfile::consoleGAfile(state *s) : GAfile(s) {
	initToNothing();

	m_filename = strdup("virtual console file.geo");
	m_directFileOpen = 1;
}

consoleGAfile::~consoleGAfile() {
	initToNothing();
}

void consoleGAfile::initToNothing() {
}

int consoleGAfile::read(state *s) {
	cprintf("consoleGAfile::read() was called, which should never happen!\n");
	return 0;
}

int consoleGAfile::reset(state *s) {
	cprintf("consoleGAfile::reset() was called, which should never happen!\n");
	m_lineNb = 1;
	return 0;
}

int consoleGAfile::read(state *s, const char *cmd) {
	int l = strlen(cmd) + 1;
	ensureBufLen(l);
	memcpy(m_buf, cmd, l);
	m_bufLen = l-1;
	substituteArguments(s);
	parseLine(s);
	return 0;
}

int consoleGAfile::handleDelete() {
	cprintf("consoleGAfile::handleDelete() was called, which should never happen!\n");
	return 0;
}
