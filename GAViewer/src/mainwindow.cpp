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

#include <FL/x.H>

#include "state.h"
#include "uistate.h"
#include "mainwindow.h"
#include "console/consolewindow.h"
#include "glwindow.h"

mainWindow::~mainWindow() {
}

void mainWindow::resize(int xPos, int yPos, int width, int height) {
	// Fl_Window::resize() behaves weird sometimes (calls back to this function)
	static int running = 0;
//	if (running) {printf("Yop!\n"); return;}
	running = 1;
	Fl_Window::resize(xPos, yPos, width, height);
	running = 0;

//	size_range(c_controlWidth + 200, 200); // this prevents some weird bug in FLTK (due to my own abuse?): window can not be resized any more
//	printf("Resized to %d\n", h());

	if (gui_state->m_fullscreen) {
		//gui_state->m_statusOutput->hide();
		gui_state->m_menubar->hide();
		gui_state->m_controlGroup->hide();
		gui_state->m_consoleGroup->hide();
		gui_state->m_scalarGroup->hide();

		gui_state->m_statusOutput->hide();
		gui_state->m_waitButton->hide();


		// remember to draw a little 'w' when waiting (mouse click sensitive)
		gui_state->m_glWindow->resize(0, 0, w(), h());// - c_statusHeight);
	}
	else {
		gui_state->m_menubar->show();
		gui_state->m_menubar->resize(0, 0, w(), c_menuHeight-1);

		// set the height of the console (always maintain 20 pixels for glwindow)
		int consoleHeight = gui_state->m_consoleGroup->h();
		if (consoleHeight > h() - c_menuHeight - c_statusHeight - 20)
			consoleHeight =h() - c_menuHeight - c_statusHeight - 20;
		if (consoleHeight < 80) consoleHeight = 80;
		
		int glwidth, glheight;

		if (gui_state->m_controlGroupVisible) {
			gui_state->m_controlGroup->show();
			gui_state->m_controlGroup->resize(w() - c_controlWidth, c_menuHeight, 
				c_controlWidth, h() - c_menuHeight - c_statusHeight - (gui_state->m_scalarGroupVisible ? consoleHeight : 0));

			glwidth = w() - c_controlWidth;

		}
		else  {
			glwidth = w();
		}

		if (gui_state->m_consoleVisible) {
			int consoleWidth = glwidth;
			if (!gui_state->m_controlGroupVisible && gui_state->m_scalarGroupVisible)
				consoleWidth -= c_controlWidth;

			gui_state->m_consoleGroup->show();
			glheight = h() - c_menuHeight - c_statusHeight - consoleHeight;

			gui_state->m_consoleGroup->resize(0, gui_state->m_glWindow->y() + glheight,
				consoleWidth, consoleHeight);
		}
		else {
//			printf("glheight ~ %d %d %d\n", h(), c_menuHeight, c_statusHeight);
			glheight = h() - c_menuHeight - c_statusHeight;
		}

		if (gui_state->m_scalarGroupVisible) {
				gui_state->m_scalarGroup->show();
				gui_state->m_scalarGroup->resize(w() - c_controlWidth, 
					gui_state->m_glWindow->y() + h() - c_menuHeight - c_statusHeight - consoleHeight, 
					c_controlWidth, 
					consoleHeight);
		}

		gui_state->m_glWindow->resize(0, c_menuHeight, glwidth, glheight);



		gui_state->m_statusOutput->show();

		gui_state->m_statusOutput->resize(
			gui_state->m_statusOutput->x(),
			gui_state->m_mainWindow->h() - c_statusHeight,
			gui_state->m_mainWindow->w() - c_waitWidth,
			gui_state->m_statusOutput->h());

		gui_state->m_waitButton->resize(
			gui_state->m_mainWindow->w() - c_waitWidth,
			gui_state->m_mainWindow->h() - c_statusHeight,
			c_waitWidth,
			c_statusHeight);

/*		printf("%d %d\n", 
			gui_state->m_glWindow->h() + gui_state->m_glWindow->y(),
			gui_state->m_waitButton->y());
		if (gui_state->m_glWindow->h() + gui_state->m_glWindow->y() > gui_state->m_waitButton->y())
			printf("Whaaa!\n");*/
	}

}

void mainWindow::initToNothing() {
	m_fsoX = m_fsoY = m_fsoW = m_fsoH = -1;
#ifdef WIN32
	m_fsoStyle = m_fsoExStyle = 0;
#endif
}

void mainWindow::fullscreen() {
	m_fsoX = x();
	m_fsoY = y();
	m_fsoW = w();
	m_fsoH = h();
	Fl_Window::fullscreen();
	// fix for FLTKs half implemented of fullscreen
#ifdef WIN32
	// modify the ex style
	LONG exStyle = GetWindowLong(fl_xid(this),  GWL_EXSTYLE);
	exStyle = exStyle ^ (exStyle & (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION));
	m_fsoExStyle = SetWindowLong(fl_xid(this),  GWL_EXSTYLE, exStyle | WS_EX_TOPMOST);

	// modify ordinary style
	LONG style = GetWindowLong(fl_xid(this),  GWL_STYLE);
	style = style ^ (style & (WS_THICKFRAME | WS_MAXIMIZEBOX | WS_CAPTION));
	m_fsoStyle = SetWindowLong(fl_xid(this),  GWL_STYLE, style | WS_POPUP | WS_MAXIMIZE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	SetWindowPos(fl_xid(this), HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 0);
#endif
}

void mainWindow::fullscreen_off() {
#ifdef WIN32
	// restore ex and ordinary style
	SetWindowLong(fl_xid(this), GWL_EXSTYLE, m_fsoExStyle);
	SetWindowLong(fl_xid(this), GWL_STYLE, m_fsoStyle);
	m_fsoStyle = m_fsoExStyle = 0;
#endif
	Fl_Window::fullscreen_off(m_fsoX, m_fsoY, m_fsoW, m_fsoH);
	m_fsoX = m_fsoY = m_fsoW = m_fsoH = -1;
	setSizeRange();
}

int mainWindow::setSizeRange() {
	size_range(c_controlWidth + 200, 200); // this prevents some weird bug in FLTK (due to my own abuse?): window can not be resized any more
	return 0;
}

int mainWindow::handle(int event) {
	if (event == FL_KEYBOARD) {
		switch (Fl::event_key()) {
		case ' ':
			if (gui_state->m_fullscreen) g_state->nextPlayListEntry();
			return 1;
		case FL_Escape:
			if (gui_state->m_fullscreen)
				ui_menuCallback(NULL, (void*)MI_FULLSCREEN);
			return 1;
		case FL_Enter:
			if (g_state->m_inputWait) g_state->setInputWaitState(0);
			if (gui_state->m_waitButton)
				gui_state->m_waitButton->redraw();
			return 1;
		default:
			return Fl_Window::handle(event);
		}
	}
	else if (event == FL_FOCUS) {
		return 1;
	}
	else return Fl_Window::handle(event);
}

int mainWindow::setTitle(const char *str) {
	static char title[1024];
	sprintf(title, "GAViewer%s%s", strlen(str) ? ": " : "", str);
	label(title);
	return 0;
}

