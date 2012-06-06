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

/*
A subclass of GAFile.
Should mimic the behaviour of a real file, while
input is actual coming from cmd("xyz"); console commands
*/

#ifndef _CONSOLE_GA_FILE_H_
#define _CONSOLE_GA_FILE_H_

#include "../gafile.h"

class consoleGAfile : public GAfile {
public:
	consoleGAfile(state *s);
	virtual ~consoleGAfile();
	void initToNothing();

	virtual int read(state *s);

	inline const char *filename() {return m_filename;}

	virtual int reset(state *s);
	int read(state *s, const char *cmd);
	virtual int handleDelete();

};



#endif /* _CONSOLE_GA_FILE_H_ */
