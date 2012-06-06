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

#ifdef WIN32
#include <windows.h>
#include <commdlg.h> /* for win32 file browser */
#include <direct.h> /* for _getcwd() */
#include <FL/x.H> /* for fl_xid() */
#endif /* WIN32 */

#include <string.h>

#include "state.h"
#include "uistate.h"
#include "glwindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>

#include "screenshotdialog.h"
#include "uistate.h"

screenShotDialog::screenShotDialog(int w, int h, const char* label) : Fl_Window(w, h, label) {
	initToNothing();
	setupWidgets();
}

screenShotDialog::screenShotDialog(int x, int y, int w, int h, const char* label) : Fl_Window(x, y, w, h, label) {
	initToNothing();
	setupWidgets();

}

screenShotDialog::~screenShotDialog() {

	initToNothing();
}

void screenShotDialog::initToNothing() {
	m_storeLabel = NULL;
	m_browseButton = NULL;
	m_filenameInput = NULL;

	m_widthLabel = NULL;
	m_widthInput = NULL;

	m_heightLabel = NULL;
	m_heightInput = NULL;
	m_noLabelsCheckButton = NULL;

	m_OKButton = m_cancelButton = NULL;
}


void screenShotDialog::callback(Fl_Widget *W, void *Data) {
	if (W == m_OKButton) {
		std::string f(m_filenameInput->value());
		int w = atoi(m_widthInput->value());
		int h = atoi(m_heightInput->value());
		bool wol = m_noLabelsCheckButton->value() != 0;
		delete this;
		if (gui_state && gui_state->m_screenShotDialog) {
			gui_state->m_screenShotDialog = NULL;
			gui_state->setupScreenshot(f, w, h, wol);
			return;
		}
	}
	else if (W == m_cancelButton) {
		delete this;
		if (gui_state && gui_state->m_screenShotDialog) {
			gui_state->m_screenShotDialog = NULL;
			return;
		}
	}
	else if (W == m_browseButton) {
		browse();
	}
	else if (W == m_widthInput) {
		if (atoi(m_widthInput->value()) < 0) {
			// dialog?
			m_widthInput->value("0");
		}
	}
	else if (W == m_heightInput) {
		if (atoi(m_heightInput->value()) < 0) {
			// dialog?
			m_heightInput->value("0");
		}
	}
}

static void ssd_callback(Fl_Widget *W, void *Data) {
	if (gui_state && gui_state->m_screenShotDialog)
		gui_state->m_screenShotDialog->callback(W, Data);
}

int screenShotDialog::setupWidgets() {
	int x = 5, y = 5;
	const int labelWidth = 55;

	if (!(gui_state && g_state)) return -1;


/*	Fl_Output *warningLabel = new Fl_Output(x, y, labelWidth, 25);
	warningLabel->value("filename: ");
	warningLabel->color(FL_GRAY);
	warningLabel->box(FL_FLAT_BOX);*/


	static char wi[16], hi[16];
	sprintf(wi, "%d", gui_state->m_glWindow->w());
	sprintf(hi, "%d", gui_state->m_glWindow->h());

	m_storeLabel = new Fl_Output(x, y, labelWidth, 25);
	m_storeLabel->value("filename: ");
	m_storeLabel->color(FL_GRAY);
	m_storeLabel->box(FL_FLAT_BOX);
	m_storeLabel->clear_visible_focus();

	m_filenameInput = new Fl_Input(m_storeLabel->x() + m_storeLabel->w() + 5, y, 495, 25); // todo: not default.png but something from state
	m_filenameInput->value("default.png");

	m_browseButton = new Fl_Button(m_filenameInput->x() + m_filenameInput->w() + 5, y, 30, 25, "...");
	m_browseButton->callback(ssd_callback, NULL);


	y += 35;

	m_widthLabel = new Fl_Output(x, y, labelWidth, 25);
	m_widthLabel->value("width: ");
	m_widthLabel->color(FL_GRAY);
	m_widthLabel->box(FL_FLAT_BOX);
	m_widthLabel->clear_visible_focus();

	m_widthInput = new Fl_Int_Input(m_widthLabel->x() + m_widthLabel->w() + 5, y, 100, 25);
	m_widthInput->value(wi);
	m_widthInput->callback(ssd_callback, NULL);

	m_noLabelsCheckButton = new Fl_Check_Button(m_widthInput->x() + m_widthInput->w() + 20, y, 300, 25, "Render second screenshot without labels");
	m_noLabelsCheckButton->callback(ssd_callback, NULL);
	m_noLabelsCheckButton->value((gui_state->m_ssAlsoNoLabels) ? 1 : 0);

	y += 30;

	m_heightLabel = new Fl_Output(x, y, labelWidth, 25);
	m_heightLabel->value("height: ");
	m_heightLabel->color(FL_GRAY);
	m_heightLabel->box(FL_FLAT_BOX);
	m_heightLabel->clear_visible_focus();

	m_heightInput = new Fl_Int_Input(m_heightLabel->x() + m_heightLabel->w() + 5, y, 100, 25);
	m_heightInput->value(hi);
	m_heightInput->callback(ssd_callback, NULL);

	y += 35;

	m_OKButton = new Fl_Button(x, y, 100, 25, "OK");
	m_OKButton->callback(ssd_callback, NULL);
	
	m_cancelButton = new Fl_Button(m_OKButton->x() + m_OKButton->w() + 10, y, 100, 25, "Cancel");
	m_cancelButton->callback(ssd_callback, NULL);

	// set default values from previous screenshot:
	if (gui_state->m_ssFilename.length()) {
		sprintf(wi, "%d", gui_state->m_ssWidth);
		sprintf(hi, "%d", gui_state->m_ssHeight);
		m_filenameInput->value(gui_state->m_ssFilename.c_str());
		m_widthInput->value(wi);
		m_heightInput->value(hi);
	}


	return 0;
}

int screenShotDialog::browse() {
	char filename[1024];

	filename[0] = 0;

#ifdef WIN32
    char tmpFilename[1024], tmpFilename2[256];
	OPENFILENAME ofn;
	strcpy(tmpFilename, m_filenameInput->value());

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = fl_xid(this);
	ofn.lpstrTitle = "Save screenshot (.png):";
	ofn.lpstrFile = tmpFilename;
	ofn.lpstrFileTitle = tmpFilename2;
	ofn.nMaxFile = 1023;
	ofn.nMaxFileTitle = 255;
	ofn.lpstrFilter = "png files (*.png)\0*.png\0All files (*.*)\0*.*\0\0\0";
	ofn.lpstrDefExt = "png";
	if (GetSaveFileName(&ofn))
		strcpy(filename, tmpFilename);
	else return 0;
#else /* assume UNIX */
	char *sourcePath;
	if ( (sourcePath = fl_file_chooser("Save screenshot (.png):", "*.png", m_filenameInput->value())) != NULL)
		strcpy(filename, sourcePath);
	else return 0;
#endif /* WIN32 */
	//printf("Store in '%s'\n", filename);

	m_filenameInput->value(filename);

	return 0;
}

