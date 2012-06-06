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

#ifndef _GA_FILE_H_
#define _GA_FILE_H_

#include <stdlib.h>

class state;

class GAfile {
public:
	GAfile(state *s);
	GAfile(state *s, const char *filename, int level, const char *deleteQuestion = NULL, int nbArg = 0, char *arg[] = NULL);
	virtual ~GAfile();
	void initToNothing();

	virtual int reset(state *s);
	virtual int read(state *s);

	inline const char *filename() {return m_filename;}

	virtual int handleDelete();
	int m_deleteFile; // -1 = no, 0: ask 1: yes
	char *m_deleteFileQuestion; // question that will be asked if m_deleteFile == 0

	int m_closeAtEOF;

	int m_nbArg;
	char **m_arg;

protected:
	/*
	level -1: top level; delete the entire stack (cause: UI open, or next/prev in play list)
	level 0: replace current file in stack (cause: 'open' command
	level 1: add new file to the stack (cause: import command)
	*/
	int m_level; 

	int m_directFileOpen; // open .geo files directly? or wait until timer does it

	char *m_filename;
	int m_pos; // position in the file; the file is fopen-ed and fseek-ed on every call to read()
	int m_lineNb;
	int m_lastChar;

	int ensureBufLen(int l);
	int m_bufLen, m_bufMaxLen;
	char *m_buf;

	int truncated(state *s);
	int parseLine(state *s);

	// returns -1 if no string found (first char found is a member of 'noStrStart', or no char found at all)
	// returns the 'endIdx' plus string in 'str' 
	int readString(const char *buf, int startIdx, char *str, const char *noStrStart = "[]+-1234567890");
	int memberOf(char c, const char *set);
	int parseFlags(const char *line, int &drawMode, int &creationFlags);
	int parseLabelFlags(const char *line, int &labelMode, int &width);

	int substituteArguments(state *s);
	int setArg(int nbArg, char *arg[]);
	int freeArg();

};


#endif /* _GA_FILE_H_ */
