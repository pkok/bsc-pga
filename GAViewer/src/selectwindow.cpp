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

#include "state.h"
#include "uistate.h"
#include "object.h"
#include "glwindow.h"
#include "selectwindow.h"

#include <FL/Fl_Scroll.H>

// maybe make non-modal, such that we can still interact with main window
// but this would require reworking all of this stuff for interactivity
selectWindow::selectWindow(int mode, int w, int h, const char* label) : Fl_Window(w, h, label) {
	initToNothing();
	m_mode = mode;

	setupWidgets();
}

selectWindow::selectWindow(int mode, int x, int y, int w, int h, const char* label) : Fl_Window(x, y, w, h, label) {
	initToNothing();
	m_mode = mode;

	setupWidgets();
}

selectWindow::~selectWindow() {

	initToNothing();
}

void selectWindow::initToNothing() {
	m_mode = SWM_NONE;
}

static void selectWindowCallback(Fl_Widget *W, void *Data) {
	if (!gui_state->m_selectWindow) return;

	if (Data != NULL) {
		switch (gui_state->m_selectWindow->m_mode) {
		case SWM_SHOW:
			((object*)Data)->toggleHide();
			gui_state->setCurrentObject((object*)Data);
			gui_state->m_glWindow->redraw();

			break;
		case SWM_SELECT:
		case SWM_SELECT_HIDDEN:
			gui_state->setCurrentObject((object*)Data);
			break;
		default:
			break;
		}
	}

	if ((Data == NULL) || (gui_state->m_selectWindow->m_mode == SWM_SELECT_HIDDEN) ||
		 (gui_state->m_selectWindow->m_mode == SWM_SELECT))  {
		delete gui_state->m_selectWindow;
		gui_state->m_selectWindow = NULL;
	}
}

int selectWindow::setupWidgets() {
	int i, x, y, nb = 0;
	state::OI oi;

	for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++)
		if ((m_mode == SWM_SELECT) || oi->second->hidden()) nb++;

	x = 5; y = 5;


	if (nb) {
		static char **objectName = NULL;
		static int onnb = 0;
		if (nb > onnb) {
			objectName = (char**)realloc(objectName, sizeof(char*) * nb);
			for (i = onnb; i < nb; i++)
				objectName[i] = NULL;
			onnb = nb;
		}

		Fl_Scroll *scroll = new Fl_Scroll(0, 0, w(), h() - 30);
		scroll->box(FL_ENGRAVED_BOX);


		i = 0;
		for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++) {
			object *o = oi->second;
			if ((m_mode != SWM_SELECT) && (!o->hidden())) continue;

			if (i > onnb) {
				cprintf("Error inside selectWindow::setupWidgets()");
				break;
			}

			objectName[i] = (char*)realloc(objectName[i], sizeof(char) * (o->m_name.length() + 1));
			strcpy(objectName[i], o->m_name.c_str());

			if (m_mode == SWM_SELECT) {
				Fl_Check_Button *b = new Fl_Check_Button(x, y, w() - 10, 20, objectName[i]);
				b->callback(selectWindowCallback, o);
				b->value(0);
				y += 25;
			}
			else if (o->m_drawMode & OD_HIDE) {
				if (m_mode == SWM_SELECT_HIDDEN) {
					Fl_Button *b = new Fl_Button(x, y, w() - 10, 20, objectName[i]);
					b->callback(selectWindowCallback, o);
				}
				else if (m_mode == SWM_SHOW) {
					Fl_Check_Button *b = new Fl_Check_Button(x, y, w() - 10, 20, objectName[i]);
					b->callback(selectWindowCallback, o);
					b->value(0);
				}

				y += 25;
			}
			i++;
		}

		scroll->end();
	}

	Fl_Button *closeButton = new Fl_Button(x, h() - 25, w() - 10, 20, "close window");
	closeButton->callback(selectWindowCallback, NULL);

	return 0;
}

