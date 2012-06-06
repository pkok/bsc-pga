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

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

/*
This custom window handles the custom resizing and win32 fullscreen issues
  */

class mainWindow : public Fl_Window {
public:
	mainWindow(int w, int h, const char* label=0) : Fl_Window(w, h, label) {initToNothing();};
	mainWindow(int x, int y, int w, int h, const char* label=0) : Fl_Window(x, y, w, h, label) {initToNothing();};
	virtual ~mainWindow();

	void initToNothing();

	virtual void resize(int x, int y, int w, int h);
	virtual int handle(int event);

	int setTitle(const char *title);

	int setSizeRange(); // sets the default size range

	void fullscreen();
	void fullscreen_off();

protected:
	int m_fsoX, m_fsoY, m_fsoW, m_fsoH; // fullscreen off x, y, w, h
#ifdef WIN32
	// these are used to remember the style of the window in fullscreen off mode
	LONG m_fsoStyle, m_fsoExStyle;
#endif
};


#endif /* _MAIN_WINDOW_H_ */
