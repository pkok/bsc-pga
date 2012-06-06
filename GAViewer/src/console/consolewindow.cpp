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
#include "../uistate.h"
#include "../mainwindow.h"
#include "consolewindow.h"


void consoleWindow::initToNothing() {
	m_currentCursor = -1;
	m_dragging = 0;
//	m_prevY = 0;
}

int consoleWindow::handle(int event) {
	int cursorOnEntry = m_currentCursor;
	const int border = 3;
	int ret = 0;
	int eY = Fl::event_y();

	// set cursor
	if (m_dragging) m_currentCursor = FL_CURSOR_NS;
	else if ((event == FL_MOVE) || (event == FL_PUSH) ||
		(event == FL_DRAG) || (event == FL_RELEASE)) {
		// check y, set cursor
		m_currentCursor = (eY < border) ? FL_CURSOR_NS : FL_CURSOR_DEFAULT;
//		printf("y: %d cursor: %d\n", eY, m_currentCursor);

		if (m_currentCursor == FL_CURSOR_NS)
			ret = 1;
	}

//	printf("Event %d (%d)\n", event, FL_DRAG);
	if (event == FL_LEAVE) {
		// reset cursor
		m_currentCursor = FL_CURSOR_DEFAULT;
	}
	else if (event == FL_PUSH) {	
		// if we are in the sensitive region, start dragging
		if (m_currentCursor == FL_CURSOR_NS)
			m_dragging = 1;
	}
	else if (event == FL_RELEASE) {
		// on release, we always stop dragging
		m_dragging = 0;
	}
	else if (event == FL_DRAG) {
		// resize if we are dragging
		if (m_dragging) {
//			printf("Resize from %d %d to %d %d\n", w(), h(), w(), h() + eY - m_prevY);
			//printf("Prev: %d New: %d\n", m_prevY, eY);
//			int gy = y() + eY;
			size(w(), h() - eY);

			gui_state->m_mainWindow->resize(gui_state->m_mainWindow->x(), gui_state->m_mainWindow->y(), 
				gui_state->m_mainWindow->w(), gui_state->m_mainWindow->h());
		}
	}
	else if (event == FL_ENTER) {
		// reset all statics
		m_currentCursor = FL_CURSOR_DEFAULT;
		m_dragging = 0;
	}

/*	if ((event == FL_MOVE) || (event == FL_PUSH) ||
		(event == FL_DRAG) || (event == FL_RELEASE)) {
		m_prevY = eY;
	}*/

	// pass currrent cursor setting to window
	if ((cursorOnEntry != m_currentCursor) || (m_currentCursor == FL_CURSOR_NS))
		cursor((Fl_Cursor)m_currentCursor);

	return (ret) ? ret : Fl_Double_Window::handle(event);
}
