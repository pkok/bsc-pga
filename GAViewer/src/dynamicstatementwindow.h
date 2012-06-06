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

#ifndef _DYNAMIC_STATEMENT_WINDOW_H_
#define _DYNAMIC_STATEMENT_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class dynStmtWindow : public Fl_Window {
public:
	dynStmtWindow(int w, int h, const char* label=0);// : Fl_Window(w, h, label) {};
	dynStmtWindow(int x, int y, int w, int h, const char* label=0);// : Fl_Window(x, y, w, h, label) {};
	virtual ~dynStmtWindow();

	void initToNothing();
	int setupWidgets();
};


#endif /* _SELECT_WINDOW_H_ */

