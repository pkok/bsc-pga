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

#pragma warning( disable : 4311 4312 4244 )

#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>

#include "state.h"
#include "uistate.h"
#include "object.h"
#include "glwindow.h"
#include "mainwindow.h"
#include "dynamicstatementwindow.h"
#include "console/console.h"
#include "console/consolestatement.h"

#include <FL/Fl_Scroll.H>

dynStmtWindow::dynStmtWindow(int w, int h, const char* label) : Fl_Window(w, h, label) {
	initToNothing();

	setupWidgets();
}

dynStmtWindow::dynStmtWindow(int x, int y, int w, int h, const char* label) : Fl_Window(x, y, w, h, label) {
	initToNothing();

	setupWidgets();
}

dynStmtWindow::~dynStmtWindow() {

	initToNothing();
}

void dynStmtWindow::initToNothing() {
}

static struct dynStmtWidgets {

	Fl_Button *remove;
	Fl_Button *update;
	Fl_Output *name;
	Fl_Text_Editor *editor;
	consoleStmtListStmt *stmt;
} *s_dynStmtWidgets = NULL;
static int s_nbDynStmtWidgets = 0;

static void ui_dynStmtCallback(Fl_Widget *W, void *Data) {
	int idx = (int)((unsigned char*)Data - (unsigned char*)NULL), i;
	if (idx >= 0) {
		if (W == s_dynStmtWidgets[idx].remove) {
			g_state->removeDynStmt(s_dynStmtWidgets[idx].stmt);
			s_dynStmtWidgets[idx].editor->deactivate();
			s_dynStmtWidgets[idx].editor->buffer()->insert(0, " -- Removed --\n\n");
			s_dynStmtWidgets[idx].stmt = NULL;
			s_dynStmtWidgets[idx].remove->deactivate();
			s_dynStmtWidgets[idx].update->deactivate();
		}
		else if (W == s_dynStmtWidgets[idx].update) {
			const char *wd = NULL;
			for (i = 0; i < (int)g_state->m_dynStmt.size(); i++)
				if (g_state->m_dynStmt[i].ds() == s_dynStmtWidgets[idx].stmt)
					wd = g_state->m_dynStmt[i].wd().c_str();
//			printf("WD: %08X\n", wd);
			
			consoleStmtListStmt *stmt = consoleParse(s_dynStmtWidgets[idx].editor->buffer()->text(), wd);
			if (stmt == NULL) {
				fl_message("Parse error\n(see error message on console)");
			}
			else {
				if (g_state->replaceDynStmt(s_dynStmtWidgets[idx].stmt, stmt)) {
					cprintf("ui_dynStmtCallback(): could not replace dynamic statement!\n");
				}
				else {
					s_dynStmtWidgets[idx].stmt = stmt;
					s_dynStmtWidgets[idx].update->deactivate();
					g_state->updateDynStmts();
					cprintf("Update successful\n");
				}
			}

		}
	}
	else { // close button pushed
		for (i = 0; i < s_nbDynStmtWidgets; i++)
			if (s_dynStmtWidgets[i].update->active())
				break;

		if (i != s_nbDynStmtWidgets) {
			// apply changes if user answer positively
			if (fl_choice("Update modified dynamic statements?", "No", "Yes", NULL)) {
				for (i = 0; i < s_nbDynStmtWidgets; i++)
					if (s_dynStmtWidgets[i].update->active())
						ui_dynStmtCallback(s_dynStmtWidgets[i].update, (void*)i);
			}
		}
			
		delete gui_state->m_dynStmtWindow;
		gui_state->m_dynStmtWindow = NULL;
	}
}


void modifyCallback(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg) {
	int idx = (int)((unsigned char*)cbArg - (unsigned char*)NULL);
	s_dynStmtWidgets[idx].update->activate();
}


int dynStmtWindow::setupWidgets() {
	int i, j;

	// various constants:
	int nb = (int)g_state->m_dynStmt.size();
	int closeButtonHeight = 30;
	int nameOutputWidth = 90;
	int removeButtonWidth = 90;
	int updateButtonWidth = 90;
	int nameOutputHeight = 20;
	int removeButtonHeight = 20;
	int updateButtonHeight = 20;
	int fontsize = 14;
	int textEditorHeight = fontsize * 4 + 20;
	int rh = closeButtonHeight +5 + (textEditorHeight + 10 + 5) * nb + 25;

	// set window size
	w(600);
	if (rh < gui_state->m_mainWindow->h()) h(rh);
	else h(gui_state->m_mainWindow->h());

	s_dynStmtWidgets = (struct dynStmtWidgets*) realloc(s_dynStmtWidgets, sizeof(struct dynStmtWidgets) * nb) ;
	s_nbDynStmtWidgets = nb;

	int cx = 0, cy = 0;
	if (nb) {
		// create the scroll the contains all the text editors, buttons, etc
		Fl_Scroll *scroll = new Fl_Scroll(cx, cy, w(), h() - 30);
		scroll->box(FL_ENGRAVED_BOX);
		scroll->type(Fl_Scroll::BOTH); // _ALWAYS

		cx += 5; cy += 5;


		for (i = 0; i < nb; i++) {
			char *str = g_state->m_dynStmt[i].ds()->string(1, 0);

			// remove all space / cr/ tabs etc form end of line
			j = strlen(str) - 1;
			while (j >= 0) {
				if (str[j] > ' ') break;
				else j--;
			}
			str[j+1] = 0;

			Fl_Group *g = new Fl_Group(cx, cy, w() - (25 + cx), textEditorHeight + 10);
			g->box(FL_THIN_DOWN_BOX);
			cx += 5; cy += 5;

			s_dynStmtWidgets[i].stmt = g_state->m_dynStmt[i].ds();

			Fl_Output *op = s_dynStmtWidgets[i].name = new Fl_Output(cx, cy, nameOutputWidth, nameOutputHeight);
			op->box(FL_FLAT_BOX);
			op->deactivate();
			op->value(g_state->m_dynStmt[i].name().size() ? g_state->m_dynStmt[i].name().c_str() : "anonymous");

			// create remove button
			Fl_Button *b = s_dynStmtWidgets[i].remove = new Fl_Button(cx, cy + nameOutputHeight + 5, removeButtonWidth, removeButtonHeight, "remove");
			b->callback(ui_dynStmtCallback, (void*)i);

			// create update button
			b = s_dynStmtWidgets[i].update = new Fl_Button(cx, cy + nameOutputHeight + 5 + removeButtonHeight + 5, updateButtonWidth, updateButtonHeight, "update");
			b->callback(ui_dynStmtCallback, (void*)i);
			b->deactivate();

			// create text editor
			Fl_Text_Display *te = s_dynStmtWidgets[i].editor = new Fl_Text_Editor(cx + removeButtonWidth + 5, cy, w() - (cx + removeButtonWidth + 10 + 25), textEditorHeight);
			te->textsize(fontsize);
			te->box(FL_THIN_DOWN_BOX);
			Fl_Text_Buffer *tb = new Fl_Text_Buffer();
			tb->text(str);
			te->buffer(tb);
			tb->add_modify_callback(modifyCallback, (void*)i);

			// string returned form stmt->string must be released
			free(str);

			g->end();

			cx -= 5;
			cy += textEditorHeight + 10;
		}

		// reposition scroll to 0, 0
		scroll->position(0, 0);
		// add no more children
		scroll->end();

	}

	Fl_Button *b = new Fl_Button(0, h() - 25, w(), 25, (g_state->m_dynStmt.size()) ? "close" : "close (no dynamic statements)");
	b->callback(ui_dynStmtCallback, (void*)-1);
	return 0;
}

//a = e1, dynamic{b = a ^ e2,}

