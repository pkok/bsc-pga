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
#include <ctype.h>

#include "gaincludes.h"

#include "gafile.h"
#include "osdep.h"
#include "state.h"
#include "uistate.h"
#include "glwindow.h"
#include "util.h"
#include "object.h"
#include "mainwindow.h"
#include "console/consolewindow.h"

// dummy constructor for ConsoleGAFile
GAfile::GAfile(state *s) {
	initToNothing();
}

// todo: handle the arguments...
GAfile::GAfile(state *s,const char *filename, int level, const char *deleteQuestion /*= NULL*/, int nbArg /*= 0*/, char *arg[] /*= NULL*/) {
	FILE *F;
	initToNothing();

	m_level = level;

	// check file
	if ((filename == NULL) || (filename[0] == 0)) {
		cprintf("GAfile::GAfile(): invalid filename\n");
		return;
	}
	else if ( (F = fopen(filename, "rb")) == NULL) {
		cprintf("GAfile::GAfile(): can not open '%s'\n", filename);
		return;
	}
	fclose(F);

	m_filename = strdup(filename);
//	printf("m_filename: %s %08X\n", m_filename, deleteQuestion); fflush(stdout);

	if (deleteQuestion)
		m_deleteFileQuestion = strdup(deleteQuestion);

	setArg(nbArg, arg);

	reset(s);
}

GAfile::~GAfile() {
	freeArg();
	if (m_filename) free(m_filename);
	if (m_buf) free(m_buf);
	if (m_deleteFileQuestion) free(m_deleteFileQuestion);
	initToNothing();
}

void GAfile::initToNothing() {
	m_filename = m_buf = NULL;
	m_pos = m_bufLen = m_bufMaxLen = 0;
	m_lastChar = -1;
	m_closeAtEOF = 0;
	m_deleteFile = -1; // -1 = no, 0: ask 1: yes
	m_deleteFileQuestion = NULL;
	m_nbArg = 0;
	m_lineNb = 0;
	m_arg = NULL;
	m_level = -1;
	m_directFileOpen = 0;
}

int GAfile::setArg(int nbArg, char *arg[]) {
	int i, j, s;
	freeArg();
	if ( (m_nbArg = nbArg) == 0) return 0;

	if ( (m_arg = (char**)malloc(sizeof(char*) * m_nbArg)) == NULL) {
		printf("GAfile::setArg(): memory allocation error for %d bytes\n", (int)(sizeof(char*) * m_nbArg));
		m_nbArg = 0;
		return -1;
	}

	for (i = 0; i < m_nbArg; i++) {
		if (arg[i])	{

			// check for spaces in the argument
			s = j = 0;
			while (arg[i][j]) {
				if (arg[i][j] <= ' ') s = 1;
				j++;
			}

			if (s) { // if space: then add quotes
				m_arg[i] = (char*)malloc(strlen(arg[i]) + 3);
				if (m_arg[i]) sprintf(m_arg[i], "\"%s\"", arg[i]);
			}
			else m_arg[i] = strdup(arg[i]); // othersize just copy
		}
		else m_arg[i] = strdup("");
	}

	return 0;
}

int GAfile::freeArg() {
	int i;

	if (m_arg) {
		for (i = 0; i < m_nbArg; i++)
			if (m_arg[i]) free(m_arg[i]);
		free(m_arg);
	}

	m_nbArg = 0;
	m_arg = NULL;

	return 0;
}

int GAfile::ensureBufLen(int l) {
	if (l >= m_bufMaxLen) {
		m_bufMaxLen = (l > (m_bufMaxLen * 2)) ? l : m_bufMaxLen * 2;
		m_buf = (char*)realloc(m_buf, m_bufMaxLen);
	}

	return 0;
}

int GAfile::handleDelete() {
	if (m_deleteFile < 0) return 0; // delete is not requested

	if (m_deleteFile == 0) {
//		if (!fl_ask(m_deleteFileQuestion, filename())) return 0; // user said 'no'

		char buf[1024];
		sprintf(buf, m_deleteFileQuestion, filename());
		if (fl_choice(buf, "No", "Yes", NULL)) return 0; // user said 'no'
	}
	
	deleteFile(filename());

	return 0;
}


int GAfile::reset(state *s) {
	m_pos = m_bufLen = 0;
	m_lineNb = 1;
	m_lastChar = -1;

	if ((m_level < 1) && s && (s->m_GAfileStackDepth <= 0)) {
		s->resetGAfileState();
		s->removeAllObjects();
	}

	return 0;
}

int GAfile::truncated(state *s) {
	cprintf("GAfile::read(): fseek() on '%s' returned error.\nAssuming the file has been truncated\n", m_filename);
	reset(s);
	return read(s);
}

int GAfile::read(state *s) {
	int c;
	class fileObject {
	public:
		fileObject() {};
		~fileObject() {if (m_F) {fclose(m_F); m_F = NULL;}};
		FILE *m_F;
	} autoCloseF;
	FILE *F;

	s->setWorkingDirectory(m_filename, true);

	/*
	Open file and seek to last position, if possible.
	This method is error prone. If the file is truncated
	and rewritten to a size at least as large as before 
	the truncation, the truncation will not be detected.
	This is partially solved by checking the last character
	that has been read
	*/
	if ( (autoCloseF.m_F = F = fopen(m_filename, "rb")) == NULL) {
		cprintf("Could not fopen() '%s'\n", m_filename);
		return -1;
	}
	if (fseek(F, m_pos, SEEK_SET) != 0) { 
		return truncated(s);
	}
	if (m_pos) { // check last character
		fseek(F, -1, SEEK_CUR);
		if (fgetc(F) != m_lastChar) {
			return truncated(s);
		}
	}
	
	// read all you can...
	for (;;) {
		// unless a new file must be opened by the timer
		if (s->m_openFilename) return 0;

		// unless we are sleeping or waiting (except when parsing a playlist...)
		if ((!s->m_playListParse) && 
			(s->m_inputWait || ((s->m_inputSleepTime >= 0.0) && (u_timeGet() < s->m_inputSleepTime)))) {
			return 0;
		}
		//s->m_inputSleepTime = -1.0;


		// check if we have enough buffer left
		ensureBufLen(m_bufLen + 1);
		/*if (m_bufLen + 1 >= m_bufMaxLen) {
			m_bufMaxLen = (m_bufMaxLen) ? m_bufMaxLen * 2 : 4;
			m_buf = (char*)realloc(m_buf, m_bufMaxLen);
		}*/

		// check if we can read another character from the file
		m_lastChar = c = fgetc(F);
		m_pos++; // character read->increment position in file

		if (c > 127) {
			cprintf("Invalid characted '%d' in file '%s'", c, m_filename);
			continue;
		}

		if (c < 0) {
			// the search for a bookmark ends at the end of the file...
			s->bookmarkFound();

			if (m_closeAtEOF) {
				s->deleteTopOfGAfileStack();
				return 0; // we must return now, for 'this' has been deleted..
			}

			return 0;
		}

		if ((c == 10) || (c == 13)) { // end of line / carriage return:-> parse line
			if (c == 10) m_lineNb++; // or is it 13? :)
			m_buf[m_bufLen] = 0;

			substituteArguments(s);
			parseLine(s);
			//printf("Parse line %d\n", m_lineNb);

			if (gui_state->m_mainWindow == NULL) return 0; // program terminated
			m_bufLen = 0;
		}
		else m_buf[m_bufLen++] = (char)c; // store character
	}

	return 0;
}

int GAfile::substituteArguments(state *s) {
	int i, j, k, l, idx, err;
	const int maxNumberLength = 15;
	char number[maxNumberLength+1];

	for (i = 0; i < m_bufLen-1; i++) {
		if ((m_buf[i] == '$') &&  // find a '$' ...
			isdigit(m_buf[i+1])) {/* &&  // ... followed by digit ...
			(!(i && (m_buf[i-1] == '\\')))) { // and not preceded by a backslash*/

			if (i && (m_buf[i-1] == '\\')) { // this was not meant as an argument
				memmove(m_buf + i - 1, m_buf + i, m_bufLen - i + 1);
				continue;
			}

			// retrieve the number
			j = i + 1; k = 0;
			while ((k < maxNumberLength) && isdigit(number[k] = m_buf[j])) {k++; j++;}
			number[k] = 0;

			// convert to integer and check
			idx = atoi(number)-1;
			if ((idx >= 0) && (idx < m_nbArg) && (m_arg[idx])) {
				// substitute argument
				l = strlen(m_arg[idx]);
				if (err = ensureBufLen(m_bufLen + l)) return err;
				memmove(m_buf + i + l, m_buf + j, m_bufLen - j + 1);
				memcpy(m_buf + i, m_arg[idx], l);
				m_bufLen = i + l + (m_bufLen - j);
				i = i + l;
			}
			//else cprintf("GAfile::substituteCommands(): file '%s': warning: argument '%s' not defined\n", m_filename, number);
		}
	}

	return 0;
}


int GAfile::memberOf(char c, const char *set) { 
	int i = 0;
	while (set[i]) { 
		if (c == set[i]) return 1;
		i++;
	}
	return 0;
}

int GAfile::parseFlags(const char *line, int &drawMode, int &creationFlags) {		// parse flags
	char str[8][256];
	int n, i;

	creationFlags = drawMode = 0;
	if (n = sscanf(line, "%s %s %s %s %s %s %s %s", 
		str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]))
	for (i = 0; i < n ; i++) {
		if (!strcmpnc(str[i], "hide")) drawMode |= OD_HIDE;
		else if (!strcmpnc(str[i], "show")) drawMode |= 0;
		else if (!strcmpnc(str[i], "stipple")) drawMode |= OD_STIPPLE;
		else if (!strcmpnc(str[i], "orientation")) drawMode |= OD_ORI;
		else if (!strcmpnc(str[i], "wireframe")) drawMode |= OD_WIREFRAME;
		else if (!strcmpnc(str[i], "magnitude")) drawMode |= OD_MAGNITUDE;
		else if (!strcmpnc(str[i], "shade")) drawMode |= OD_SHADE;
		else if (!strcmpnc(str[i], "outline")) drawMode |= OD_OUTLINE;
		else if (!strcmpnc(str[i], "versor")) creationFlags |= OC_VERSOR;
		else if (!strcmpnc(str[i], "blade")) creationFlags |= OC_BLADE;
		// todo: dual
		else if (!strcmpnc(str[i], "dynamic")) creationFlags |= OC_DYNAMIC;
		else if (!strcmpnc(str[i], "compute_normals_flat")) creationFlags |= OC_COMPUTE_NORMALS_FLAT;
		else if (!strcmpnc(str[i], "compute_normals_gouraud")) creationFlags |= OC_COMPUTE_NORMALS_GOURAUD;
		else if (!strcmpnc(str[i], "specify_normals")) creationFlags |= OC_SPECIFY_NORMALS;
		else if (!strcmpnc(str[i], "grade0")) creationFlags |= OC_GRADE0;
		else if (!strcmpnc(str[i], "grade1")) creationFlags |= OC_GRADE1;
		else if (!strcmpnc(str[i], "grade2")) creationFlags |= OC_GRADE2;
		else if (!strcmpnc(str[i], "grade3")) creationFlags |= OC_GRADE3;
		else if (!strcmpnc(str[i], "grade4")) creationFlags |= OC_GRADE4;
		else if (!strcmpnc(str[i], "grade5")) creationFlags |= OC_GRADE5;
		else if (!strcmpnc(str[i], "grade6")) creationFlags |= OC_GRADE6;
		else if (!strcmpnc(str[i], "grade7")) creationFlags |= OC_GRADE7;
		else if (!strcmpnc(str[i], "grade8")) creationFlags |= OC_GRADE8;
		else if (!strcmpnc(str[i], "dm1")) creationFlags |= OC_DM1;
		else if (!strcmpnc(str[i], "dm2")) creationFlags |= OC_DM2;
		else if (!strcmpnc(str[i], "dm3")) creationFlags |= OC_DM3;
		else if (!strcmpnc(str[i], "dm4")) creationFlags |= OC_DM4;
		else if (!strcmpnc(str[i], "dm5")) creationFlags |= OC_DM5;
		else if (!strcmpnc(str[i], "dm6")) creationFlags |= OC_DM6;
		else if (!strcmpnc(str[i], "dm7")) creationFlags |= OC_DM7;
		else cprintf("File '%s': line %d: unknown flag '%s'\n", m_filename, m_lineNb, str[i]);
	}
	return n;
}

int GAfile::parseLabelFlags(const char *line, int &labelMode, int &width) {		// parse flags
	char str[8][256];
	int n, i;

	width = -1;
	labelMode = 0;
	if (n = sscanf(line, "%s %s %s %s %s %s %s %s", 
		str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]))
	for (i = 0; i < n ; i++) {
		if ((!strcmpnc(str[i], "2d")) || (!strcmpnc(str[i], "flag_2d"))) labelMode |= LABEL_2D;
		else if ((!strcmpnc(str[i], "3d")) || (!strcmpnc(str[i], "flag_3d"))) labelMode |= LABEL_3D;
		else if ((!strcmpnc(str[i], "cx")) || (!strcmpnc(str[i], "flag_cx"))) labelMode |= LABEL_CX;
		else if ((!strcmpnc(str[i], "cy")) || (!strcmpnc(str[i], "flag_cy"))) labelMode |= LABEL_CY;
		else if ((!strcmpnc(str[i], "px")) || (!strcmpnc(str[i], "flag_px"))) labelMode |= LABEL_PX;
		else if ((!strcmpnc(str[i], "py")) || (!strcmpnc(str[i], "flag_py"))) labelMode |= LABEL_PY;
		else if ((!strcmpnc(str[i], "nx")) || (!strcmpnc(str[i], "flag_nx"))) labelMode |= LABEL_NX;
		else if ((!strcmpnc(str[i], "ny")) || (!strcmpnc(str[i], "flag_ny"))) labelMode |= LABEL_NY;
		else if ((!strcmpnc(str[i], "acx")) || (!strcmpnc(str[i], "flag_acx"))) labelMode |= LABEL_ACX;
		else if ((!strcmpnc(str[i], "dynamic")) || (!strcmpnc(str[i], "flag_dynamic"))) labelMode |= LABEL_DYNAMIC;
		else if ((!strcmpnc(str[i], "image")) || (!strcmpnc(str[i], "flag_image"))) labelMode |= LABEL_IMAGE;
		else if ((!strcmpnc(str[i], "fullscreen")) || (!strcmpnc(str[i], "flag_fullscreen"))) labelMode |= LABEL_FULLSCREEN;
		else if (strstr(str[i], "width=") == str[i]) {
			width = atoi(str[i] + strlen("width="));
			if (width > 0) labelMode |= LABEL_WIDTH;
		}
		else cprintf("File '%s': line %d: unknown flag '%s'\n", m_filename, m_lineNb, str[i]);
	}
	return n;
}

// returns -1 if no string found (first char found is a member of 'noStrStart', or no char found at all)
// returns the 'endIdx' plus string in 'str' 
int GAfile::readString(const char *buf, int startIdx, char *str, const char *noStrStart /* = "[]+-1234567890" */) {
	int endIdx;

	str[0] = 0;
	// find the start of the string
	while (buf[startIdx] && (buf[startIdx] <= 32)) startIdx++;
	if (buf[startIdx] == 0) return -1; // no string found

	if (buf[startIdx] == '\"') { // string is between quotes
		startIdx++;
		endIdx = startIdx;
		while (buf[endIdx] && (buf[endIdx] != '\"'))
			endIdx++;
		if (buf[endIdx] == '\"') { // end of quotes found;
			memcpy(str, buf + startIdx, endIdx - startIdx);
			str[endIdx - startIdx] = 0;
			endIdx++;
			return endIdx;
		}
		else return -1;
	}
	else { // ordinary string, no quotes
		if (memberOf(buf[startIdx], noStrStart)) return -1;

		endIdx = startIdx;
		while (buf[endIdx] > 32) endIdx++;

		memcpy(str, buf + startIdx, endIdx - startIdx);
		str[endIdx - startIdx] = 0;
		return endIdx;
	}

	return 0;
}

int GAfile::parseLine(state *s) {
	int e3gaO, p3gaO, c3gaO, c5gaO;
	int n, nbTabs, i, idx, commentFound, err, drawMode, creationFlags, labelMode, h, w, x, y, action, vtxIdx[16];
	char *line = m_buf;
	char entryname[256], name[1024], text[2048], filename[1024], pointName[256];
	float c[4], f1, f2, f3;
	object *o;
	std::string cppstr;

	const int nbStr = 8;
	char str[nbStr][256];
	char *strPtr[nbStr] = {str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]};


	e3ga e3gaMv;
	p3ga p3gaMv;
	c3ga c3gaMv;
	c5ga c5gaMv;
	e3ga_ben eBen('[', ']');
	eBen.addName("I3", e3ga::I);
	p3ga_ben pBen('[', ']');
	c3ga_ben cBen('[', ']');
	cBen.addName("einf", c3ga::ni);
	cBen.addName("e0", c3ga::no);

	c5ga_ben c5Ben('[', ']');
	c5Ben.addName("einf", c5ga::ni);
	c5Ben.addName("e0", c5ga::no);



	// first get rid of crap at the end of the line, plus spaces and tabs at the beginning
	n = strlen(line);
	commentFound = -1; i = 0; // remove comments from end of line
	for (; n >= 0; n--) {
		if (line[n] == '\"') i ^= 1;
		else if ((!i) && (line[n] == '#')) commentFound = n;
	}
	if (commentFound >= 0) n = commentFound;
	else n = strlen(line);
	if (n > 0) while ((n>0) && (line[n-1] <= 32)) n--;
	else n = 0;
	line[n] = 0;
	nbTabs = i = 0;
	while ((line[i] <= 32) && (i < n)) {
		if (line[i] == '\t') (nbTabs)++;
		i++;
	}
	memmove(line, line + i, n - i + 1);
	if ((n == 0) || (line[0] == '#') || (line[0] == '\0')) return 0;

	// parse the buffer;
	if (sscanf(line, "%s ", entryname) != 1) return 0;
	
	if ((s->m_playListParse) && (!strcmpnc(entryname, "play"))) {
		idx = strlen(entryname); // end of entryname

		if ( (idx = readString(line, idx, name)) <= 0) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// get full filename relative to this GAfile
		//fullFilename(filename, m_filename, name);
		cppstr = s->fullFilename(name);

		// read all arguments
		i = 0;
		while ((i < nbStr) && ( (idx = readString(line, idx, str[i])) > 0)) i++;
		
		// add to playlist
//		s->addPlayListEntry(filename, i, strPtr);
		s->addPlayListEntry(cppstr.c_str(), i, strPtr);
	}
	else if (s->m_playListParse) { // fallthrough while parsing playlist
		cprintf("GAfile::parseLine(): file '%s': invalid entry '%s' while parsing playlist\n", m_filename, entryname);
		return 0;
	}
	else if ((e3gaO = (!strcmpnc(entryname, "e3ga")) || (!strcmpnc(entryname, "ca3d"))) ||
		(p3gaO = (!strcmpnc(entryname, "p3ga")) || (!strcmpnc(entryname, "ca4d"))) ||
		(c3gaO = (!strcmpnc(entryname, "c3ga")) || (!strcmpnc(entryname, "ca5d"))) ||
		(c5gaO = (!strcmpnc(entryname, "c5ga")))) {		// e3ga, ca3d, p3ga, ca4d, c3ga, ca5d ********************* 
		// first retrieve the name string
		if ( (idx = readString(line, strlen(entryname) + 1, name)) < 0) {
			idx = strlen(entryname) + 1;
			name[0] = 0;
		}

		// parse the multivector string
		err = 0;
		if (e3gaO) {
			if ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0) err = -1;
		}
		else if (p3gaO) {
			if ( (n = p3gaMv.parseString(line + idx, &pBen)) < 0) err = -1;
		}
		else if (c3gaO) {
			if ( (n = c3gaMv.parseString(line + idx, &cBen)) < 0) err = -1;
		}
		else if (c5gaO) {
			if ( (n = c5gaMv.parseString(line + idx, &c5Ben)) < 0) err = -1;
		}
		if (err < 0) {
			cprintf("GAfile::parseLine(): file '%s': Could not parse multivector coordinates '%s'\n", m_filename, line + idx);
			return 0;
		}
		idx += n;

		// parse flags
		parseFlags(line + idx, drawMode, creationFlags); // todo: return force flags TOO

		// add the multivector to the list of objects
		if (e3gaO) { // todo: the force flags should include every property that was set not just 'OFF_COLOR | OFF_ALPHA'
			s->addE3gaObject(e3gaMv, name, drawMode, creationFlags, OFF_COLOR | OFF_ALPHA);
		}
		else if (p3gaO) {
			s->addP3gaObject(p3gaMv, name, drawMode, creationFlags, OFF_COLOR | OFF_ALPHA);
		}
		else if (c3gaO) {
			s->addC3gaObject(c3gaMv, name, drawMode, creationFlags, OFF_COLOR | OFF_ALPHA);
		}
	}
	else if (!strcmpnc(entryname, "label")) {		// label ********************* 

		idx = strlen(entryname) + 1;

		// first retrieve the name string
		if ( (idx = readString(line, idx, name)) < 0) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// parse either multivector coordinates, or a string
		pointName[0] = 0; e3gaMv = 0.0;
		if ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0) {
			// no coordinates, thus first name must be refering to a point
			if (( (idx = readString(line, idx, pointName)) < 0) || 
				((o = s->getObjectPtrByName(pointName)) == NULL))  {
				cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
				return 0;
			}
		}
		else idx += n;

		// then retrieve the text
		if ( (idx = readString(line, idx, text)) < 0) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// parse the labels
		parseLabelFlags(line + idx, labelMode, w);

		// if 'text' is a filename, make it full
		if (labelMode & LABEL_IMAGE) {
			//fullFilename(filename, m_filename, text);
			strcpy(text, s->fullFilename(text).c_str());
		}


		if (pointName[0]) s->addTextObject(text, pointName, name, labelMode, w);
		else s->addTextObject(text, e3gaMv, name, labelMode, w);
	}
	else if (!strcmpnc(entryname, "title")) {		// title ********************* 
		// first retrieve the name string
		if ( (idx = readString(line, strlen(entryname) + 1, name)) < 0) {
			cprintf("GAfile::parseLine(): file '%s': no name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (gui_state && gui_state->m_mainWindow)
			gui_state->m_mainWindow->setTitle(name);
	}
	else if (!strcmpnc(entryname, "bookmark")) {		// bookmark ********************* 
		s->bookmarkFound();
	}
	else if ((!strcmpnc(entryname, "fgcolor")) || (!strcmpnc(entryname, "bgcolor")) || 
		(!strcmpnc(entryname, "olcolor")) || (!strcmpnc(entryname, "cvcolor")) ) {		// color
		if (sscanf(line, "%s %f %f %f %f", entryname, c + 0, c + 1, c + 2, c + 3) == 5)
			s->setColor(entryname, c[0], c[1], c[2], c[3]);
		else if (sscanf(line, "%s %f %f %f", entryname, c + 0, c + 1, c + 2) == 4)
			s->setColor(entryname, c[0], c[1], c[2]);
		else if (sscanf(line, "%s %s", entryname, name) == 2)
			s->setColor(entryname, name);
		else {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid color entry at line '%d'\n", m_filename, m_lineNb);
			return 0;
		}
	}
	else if (!strcmpnc(entryname, "fontsize")) { // fontsize ********************* 
		if ((sscanf(line, "%s %f", entryname, &f1) != 2) || (f1 <= 0.0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid fontsize entry at line '%d'\n", m_filename, m_lineNb);
			return 0;
		}
		s->m_fontSize = f1;
	}
	else if (!strcmpnc(entryname, "consolefontsize")) { // consolefontsize ********************* 
		if ((sscanf(line, "%s %d", entryname, &h) != 2) || (h <= 0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid fontsize entry at line '%d'\n", m_filename, m_lineNb);
			return 0;
		}
		gui_state->setConsoleFontSize(h);
	}
	else if (!strcmpnc(entryname, "clear")) { // clear ********************* 
		s->removeAllObjects();
		s->removeAllDynStmt();
		if (gui_state && (gui_state->m_console))
			gui_state->m_console->clear();
		
		gui_state->setStatus("");
		s->newGlobalScope();
	}
	else if (!strcmpnc(entryname, "clearconsole")) { // clearconsole ********************* 
		if (gui_state && (gui_state->m_console))
			gui_state->m_console->clear();
		if (g_state)
			g_state->removeAllConsoleControls();
	}
	else if (!strcmpnc(entryname, "remove")) { // remove ********************* 
		if (readString(line, strlen("remove"), name) >= 0) {
			s->removeObject(name);
		}
	}
	else if (!strcmpnc(entryname, "clip")) { // clip ********************* 
		if ((sscanf(line, "%s %f", entryname, &f1) != 2) || (f1 < 0.01)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid clip entry at line '%d'\n", m_filename, m_lineNb);
			return 0;
		}
		s->m_clipDistance = f1;
	}
	else if ((!strcmpnc(entryname, "eyepos")) || (!strcmpnc(entryname, "campos"))) { // eyepos ********************* 
		// retrieve coordinates, built up multivector
		if  ( (n = e3gaMv.parseString(line + strlen("eyepos"), &eBen)) < 0) return n;
		gui_state->m_glWindow->setCamPos(e3gaMv(GRADE1));
		gui_state->m_glWindow->redraw();
	}
	else if ((!strcmpnc(entryname, "eyetrl")) || (!strcmpnc(entryname, "camtrl"))) { // eyetrl ********************* 
		// get the duration of the translation
		if ((sscanf(line, "%s %f", entryname, &f1) != 2) || (f1 < 0.0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid %s entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// find out where the multivector coordinates begin
		idx = strlen("eyetrl");
		while (line[idx] && (line[idx] <= 32)) idx++;
		while (line[idx] && (line[idx] > 32)) idx++;
		if (line[idx] == 0) return 0;

		// retrieve coordinates, built up multivector
		if  ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0) return n;
		e3gaMv = e3gaMv(GRADE1);
		s->setTrl(e3gaMv, f1);
	}
	else if ((!strcmpnc(entryname, "eyeori")) || (!strcmpnc(entryname, "camori"))) { // eyeori ********************* 
		// retrieve coordinates, built up multivector
		if  ( (n = e3gaMv.parseString(line + strlen("eyepos"), &eBen)) < 0) return n;
		gui_state->m_glWindow->setCamOri((-e3gaMv(GRADE2)).exp());
		gui_state->m_glWindow->redraw();
	}
	else if ((!strcmpnc(entryname, "eyerot")) || (!strcmpnc(entryname, "camrot"))) { // eyerot ********************* 
		// get the duration of the rotation
		if ((sscanf(line, "%s %f", entryname, &f1) != 2) || (f1 < 0.0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid %s entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// find out where the multivector coordinates begin
		idx = strlen("eyerot");
		while (line[idx] && (line[idx] <= 32)) idx++; // skip space
		while (line[idx] && (line[idx] > 32)) idx++; // space duration
		if (line[idx] == 0) return 0;

		// retrieve coordinates, built up multivector
		if  ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0) {
			cprintf("warning: GAfile::parseLine(): file '%s': could not parse rotation\n", m_filename);
			return n;
		}
		e3gaMv = e3gaMv(GRADE2);

		s->setRot(e3gaMv, f1);
	}
	else if ((h = (!strcmpnc(entryname, "hide"))) || (!strcmpnc(entryname, "show"))) {		// hide/show ********************* 
		// first retrieve the name string
		if ( (idx = readString(line, strlen(entryname) + 1, name)) < 0) {
			cprintf("GAfile::parseLine(): file '%s': no name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		if (!strcmpnc(name, "controls")) {
			if (h) {
				if (gui_state->m_controlGroupVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_CONTROLS);
			}
			else {
				if (!gui_state->m_controlGroupVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_CONTROLS);
			}
		}
		else if (!strcmpnc(name, "scalar_controls")) {
			if (h) {
				if (gui_state->m_scalarGroupVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_SCALAR_CONTROLS);
			}
			else {
				if (!gui_state->m_scalarGroupVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_SCALAR_CONTROLS);
			}
		}
		else if (!strcmpnc(name, "console")) {
			if (h) {
				if (gui_state->m_consoleVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_CONSOLE);
			}
			else {
				if (!gui_state->m_consoleVisible) 
					ui_menuCallback(NULL, (void*)MI_HIDE_CONSOLE);
			}
		}
		else if (o = s->getObjectPtrByName(name)) {
			if (h) o->hide();
			else o->show();
			gui_state->m_glWindow->redraw();
		}
		else {
			cprintf("GAfile::parseLine(): file '%s': invalid name '%s' specified in entry '%s' at line '%d'\n", m_filename, name, entryname, m_lineNb);
			return 0;
		}
	}
	else if (!strcmpnc(entryname, "sleep")) {
		if ((sscanf(line, "%s %f", entryname, &f1) != 2) || (f1 <= 0.0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		f1 *= (float)s->m_playbackSpeed;
		if (s->m_inputSleepTime > 0.0)
			s->m_inputSleepTime += f1;
		else s->m_inputSleepTime = u_timeGet() + f1;
	}
	else if (!strcmpnc(entryname, "wait")) { // wait ********************* 
		s->setInputWaitState(1);
//		gui_state->setStatus("Waiting->");
	}
	else if (!strcmpnc(entryname, "status")) { // status ********************* 
		if ( (idx = readString(line, strlen(entryname) + 1, text)) < 0) {
			cprintf("GAfile::parseLine(): file '%s': no name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		gui_state->setStatus(text);
	}
	else if ((!strcmpnc(entryname, "polygon")) || (!strcmpnc(entryname, "simplex"))) { // polygon/simplex ***********************

		idx = strlen(entryname); // end of entryname

		// read (optional) name of object
		if ( (idx = readString(line, idx, name)) <= 0) {
			name[0] = 0;
			idx = strlen(entryname); // end of entryname
		}

		while (line[idx] <= 32) idx++;  // skip through space
		if ((sscanf(line + idx, "%d", &n) != 1) || (n > 8)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		while (line[idx] > 32) idx++; // skip over 'n'

		// parse the vertices
		for (i = 0; i < n; i++) {
			if ( (idx = readString(line, idx, str[i])) <= 0) {
				cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
				return 0;
			}
		}

		// parse flags
		parseFlags(line + idx, drawMode, creationFlags);

		// create the object
		polygonObject *p = new polygonObject((name[0]) ? name : NULL, drawMode, creationFlags); // add draw mode and creation flags
		for (i = 0; i < n; i++) p->addVertex(str[i]);

		if (!strcmpnc(entryname, "simplex")) 
			p->setSimplex(1);

		s->addObject(p);
	}
	else if (!strcmpnc(entryname, "factor")) {// factor ********************* 
		if (((sscanf(line, "%s %s %d", entryname, name, &i) != 3) || (i < 1) || (i > 5))) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// determine algebra
		e3gaO = (!strcmpnc(name, "e3ga")) || (!strcmpnc(name, "ca3d"));
		p3gaO = (!strcmpnc(name, "p3ga")) || (!strcmpnc(name, "ca4d"));
		c3gaO = (!strcmpnc(name, "c3ga")) || (!strcmpnc(name, "ca5d"));
		if (!(e3gaO || p3gaO || c3gaO))  {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// skip through line, towards multivector string
		idx = strlen(entryname);
		while (line[idx] <= 32) idx++;  // skip through space
		while (line[idx] > 32) idx++;  // skip through name of algebra
		while (line[idx] <= 32) idx++;  // skip through space
		while (line[idx] > 32) idx++;  // skip through index

		// parse the multivector string
		err = 0;
		if (e3gaO) {
			if ((i > 3) || ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0)) e3gaMv.null();
			return s->setE3gaFactor(e3gaMv, i-1);
		}
		else if (p3gaO) {
			if ((i > 4) || ( (n = p3gaMv.parseString(line + idx, &pBen)) < 0)) p3gaMv.null();
			return s->setP3gaFactor(p3gaMv, i-1);
		}
		else if (c3gaO) {
			if ((i > 5) || ( (n = c3gaMv.parseString(line + idx, &cBen)) < 0)) c3gaMv.null();
			return s->setC3gaFactor(c3gaMv, i-1);
		}
	}
	else if (!strcmpnc(entryname, "exit")) {// exit********************* 
		delete gui_state->m_mainWindow;
		gui_state->m_mainWindow = NULL;
		return 0;
	}
	else if (!strcmpnc(entryname, "delete")) {// delete ********************* 
		if ((sscanf(line, "%s %s", entryname, name) != 2)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (!strcmpnc(name, "yes")) m_deleteFile = 1;
		else if (!strcmpnc(name, "ask")) {
			m_deleteFile = 0;

			idx = strlen(entryname); // end of entryname
			while (line[idx] <= 32) idx++; // skip over space
			while (line[idx] > 32) idx++; // skip over [yes|no|ask]

			// read the (optional) question
			if ( (idx = readString(line, idx, text)) > 0) {
				if (m_deleteFileQuestion) free(m_deleteFileQuestion);
				m_deleteFileQuestion = strdup(text);
			}
		}
		else m_deleteFile = -1;
	}
	else if (!strcmpnc(entryname, "resize")) {// resize ********************* 
//		printf("Resize command\n");
		n = sscanf(line, "%s %d %d %d %d", entryname, &x, &y, &w, &h);
		if (n == 3) {
			w = x;
			h = y;
		}
		if (((n != 3) && (n != 5)) || (w < 1) || (h < 1)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (w < c_controlWidth + 100) w = c_controlWidth + 100;
		if (h < 100) h = 100;

		if (n == 3) gui_state->m_mainWindow->size(w, h);
		else if (n == 5) gui_state->m_mainWindow->resize(x, y, w, h);
		//gui_state->m_mainWindow->free_position();
	}
	else if (!strcmpnc(entryname, "consoleheight")) {// consoleheight ********************* 
		n = sscanf(line, "%s %d %s", entryname, &h, str[0]);
		if (!(gui_state && gui_state->m_consoleGroup)) return 0;

		if ((n != 3) || (h < 0) || (h > 2048)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		if (!strcmpnc(str[0], "pixels")) y = 1;
		else if (!strcmpnc(str[0], "lines")) y = gui_state->m_console->textsize();
		else {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		gui_state->m_consoleGroup->resize(
			gui_state->m_consoleGroup->x(),
			gui_state->m_consoleGroup->y() + (gui_state->m_consoleGroup->h() - h * y),
			gui_state->m_consoleGroup->w(), 
			h * y + (gui_state->m_consoleGroup->h() - gui_state->m_console->h()));
		gui_state->m_mainWindow->size(gui_state->m_mainWindow->w(), gui_state->m_mainWindow->h());

	}
	else if (!strcmpnc(entryname, "viewwindowsize")) {// viewwindowsize ********************* 
		n = sscanf(line, "%s %d %d", entryname, &w, &h);
		if (!(gui_state && gui_state->m_glWindow)) return 0;

		if ((n != 3) || (w < 0) || (h < 0)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (w < 200) w = 200;
		if (h < 16) h = 16;

		gui_state->m_mainWindow->size(
			gui_state->m_mainWindow->w() + (w - gui_state->m_glWindow->w()), 
			gui_state->m_mainWindow->h() + (h - gui_state->m_glWindow->h()));
		if ((gui_state->m_glWindow->w() != w) || (gui_state->m_glWindow->h() != h)) // the very first resize is 2 pixels too small for some reason
			gui_state->m_mainWindow->size(
				gui_state->m_mainWindow->w() + (w - gui_state->m_glWindow->w()), 
				gui_state->m_mainWindow->h() + (h - gui_state->m_glWindow->h()));
		cprintf("New view window size: %d x %d", gui_state->m_glWindow->w(), gui_state->m_glWindow->h());
	}
	else if (!strcmpnc(entryname, "fullscreen")) {// fullscreen ********************* 
		n = sscanf(line, "%s %s", entryname, name);
		if ((n == 1) || (!strcmpnc(name, "on"))) {
			if (gui_state->m_fullscreen) return 0;
			else ui_menuCallback(NULL, (void*)MI_FULLSCREEN);
		}
		else if (!strcmpnc(name, "off")) {
			if (!gui_state->m_fullscreen) return 0;
			else ui_menuCallback(NULL, (void*)MI_FULLSCREEN);
		}
		else {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
	}
	else if ((!strcmpnc(entryname, "open")) || (!strcmpnc(entryname, "switchto")) || (!strcmpnc(entryname, "import"))) { // open/switchto/import ***********************
		idx = strlen(entryname); // end of entryname

		// read the filename
		if ( (idx = readString(line, idx, name)) <= 0) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		//fullFilename(filename, m_filename, name);
		strcpy(filename, s->fullFilename(name).c_str());

		//printf("fullfilename %s | %s | %s\n", filename, m_filename, name);

		// read all arguments
		i = 0;
		while ((i < nbStr) && ( (idx = readString(line, idx, str[i])) > 0)) i++;

		if (m_directFileOpen) {
			g_state->openGAfile(filename, i, strPtr, (!strcmpnc(entryname, "open")) ? -1 : ((!strcmpnc(entryname, "switchto")) ? 0 : 1));
			if (g_state->currentGAfile())
				g_state->currentGAfile()->read(g_state);
		}
		else {
			// set the to-open-file
			s->setOpenFile(filename, i, strPtr, (!strcmpnc(entryname, "open")) ? -1 : ((!strcmpnc(entryname, "switchto")) ? 0 : 1));
		}
	}
	else if (!strcmpnc(entryname, "polygonoffset")) {	// polygonoffset ********************* 
		if ((sscanf(line, "%s %f %f", entryname, &f1, &f2) != 3)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		s->m_poFactor = f1;
		s->m_poUnits = f2;
	}
	else if (!strcmpnc(entryname, "tsmode")) {	// tsmode ********************* 
		if ((sscanf(line, "%s %s", entryname, str[0]) != 2)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		s->tsSetMode(str[0]);
	}
	else if (!strcmpnc(entryname, "tsfont")) {	// tsfont ********************* 
		if ((sscanf(line, "%s %s", entryname, str[0]) != 2)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		s->tsSetFont(str[0]);
	}
	else if (!strcmpnc(entryname, "tsmode")) {	// tsparse ********************* 
		if ((sscanf(line, "%s %s", entryname, str[0]) != 2)) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		s->tsSetMode(str[0]);
	}
	else if (!strcmpnc(entryname, "tsinterpret")) {		// tsinterpret ********************* 
		if ( (idx = readString(line, strlen(entryname) + 1, text)) < 0) {
			cprintf("GAfile::parseLine(): file '%s': no text specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (err = s->tsParse(text)) {
			cprintf("warning: GAfile::parseLine(): file '%s': error in text in '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
	}
	else if (!strcmpnc(entryname, "console")) { // console *****************************
		// execute rest of line as if read from console
//		printf("Exec '%s'\n", line + strlen("console "));
		g_state->consoleCommandCallback(line + strlen("console "));
	}
	else if ((!strcmpnc(entryname, "fade")) ||
		(!strcmpnc(entryname, "fade_and_remove")) ||
		(!strcmpnc(entryname, "fade_and_hide")) ||
		(!strcmpnc(entryname, "show_and_fade"))) {		// fade ********************* 

		// first retrieve the name string, object ptr
		if ( (idx = readString(line, strlen(entryname) + 1, name)) < 0) {
			cprintf("GAfile::parseLine(): file '%s': no name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if ( (o = s->getObjectPtrByName(name)) == NULL) {
			cprintf("warning: GAfile::parseLine(): file '%s': unknown object '%s' entry at line '%d'\n", m_filename, name, m_lineNb);
			return 0;
		}
		
		if (!strcmpnc(entryname, "fade")) action = FADE_NOTHING;
		else if (!strcmpnc(entryname, "fade_and_remove")) action = FADE_REMOVE;
		else if (!strcmpnc(entryname, "fade_and_hide")) action = FADE_HIDE;
		else if (!strcmpnc(entryname, "show_and_fade")) {
			o->show(); // show object
			action = FADE_NOTHING;
		}

		if ( (n = sscanf(line + idx, "%f %f %f", &f1, &f2, &f3)) < 2) {
			cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		if (n < 3) f3 = -1.0f;

		f1 *= (float)s->m_playbackSpeed;
		try {
			o->setFade(f1, f2, action, f3); 
		} catch(removeObjectException e) {
			g_state->removeObject(name);
		}

		gui_state->m_glWindow->redraw();
	}
	else if (!strcmpnc(entryname, "mesh")) { // mesh ***********************
		idx = strlen(entryname); // end of entryname

		// read name of object
		if ( (idx = readString(line, idx, name)) <= 0) {
			cprintf("GAfile::parseLine(): file '%s': no name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		// parse flags
		parseFlags(line + idx, drawMode, creationFlags);

		// create the object
		meshObject *m = new meshObject((name[0]) ? name : NULL, drawMode, creationFlags); // add draw mode and creation flags

		s->addObject(m);
	}
	else if ((!strcmpnc(entryname, "meshvertex")) || (!strcmpnc(entryname, "meshnormal"))) { // meshnormal ***********************
		meshObject *m = NULL;
		idx = strlen(entryname); // end of entryname

		// read name of mesh object
		if (( (idx = readString(line, idx, name)) <= 0) ||
			( (m = (meshObject *)s->getObjectPtrByName(name)) == NULL))   {
			cprintf("GAfile::parseLine(): file '%s': no (or invalid) mesh name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		// read idx
		if (( (idx = readString(line, idx, str[0], "")) <= 0) || ( (i = atoi(str[0])) < 0)) {
			cprintf("GAfile::parseLine(): file '%s': no (or invalid) vertex index specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}
		// read point multivector coordinates of point name 
		pointName[0] = 0; e3gaMv = 0.0;
		if ( (n = e3gaMv.parseString(line + idx, &eBen)) < 0) {
			// no coordinates, thus first name must be refering to a point
			if (( (idx = readString(line, idx, pointName)) < 0) || 
				((o = s->getObjectPtrByName(pointName)) == NULL))  {
				cprintf("warning: GAfile::parseLine(): file '%s': invalid '%s' entry at line '%d' (no point name or 3D GA coordinates specified)\n", m_filename, entryname, m_lineNb);
				return 0;
			}
		}
		else idx += n;
		
		// set vertex/normal
		if (!strcmpnc(entryname, "meshvertex")) {
			if (pointName[0]) err = m->setVertexPos(i, pointName);
			else err = m->setVertexPos(i, e3gaMv[GRADE1]);
		}
		else {
			if (pointName[0]) err = m->setVertexNormal(i, pointName);
			else err = m->setVertexNormal(i, e3gaMv[GRADE1]);
		}
	}
	else if (!strcmpnc(entryname, "meshface")) { // meshface ***********************
		meshObject *m = NULL;
		idx = strlen(entryname); // end of entryname

		// read name of object
		if (( (idx = readString(line, idx, name)) <= 0) ||
			( (m = (meshObject *)s->getObjectPtrByName(name)) == NULL))   {
			cprintf("GAfile::parseLine(): file '%s': no (or invalid) mesh name specified in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
			return 0;
		}

		if ( (n = sscanf(line + idx, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", 
			vtxIdx + 0, vtxIdx + 1, vtxIdx + 2, vtxIdx + 3, vtxIdx + 4, vtxIdx + 5, vtxIdx + 6, vtxIdx + 7, 
			vtxIdx + 8, vtxIdx + 9, vtxIdx + 10, vtxIdx + 11, vtxIdx + 12, vtxIdx + 13, vtxIdx + 14, vtxIdx + 15)) < 3) {
			cprintf("GAfile::parseLine(): file '%s': too little vertices for face in entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
		}
		m->addFace(n, vtxIdx);
	}
	else {
		cprintf("warning: GAfile::parseLine(): file '%s': Unknown entry '%s' at line '%d'\n", m_filename, entryname, m_lineNb);
	}

	return 0;
}
