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

#ifndef _SCREEN_SHOT_DIALOG_H_
#define _SCREEN_SHOT_DIALOG_H_

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class Fl_Button;
class Fl_Output;
class Fl_Input;
class Fl_Int_Input;

class screenShotDialog : public Fl_Window {
public:
	screenShotDialog(int w, int h, const char* label=0);
	screenShotDialog(int x, int y, int w, int h, const char* label=0);
	virtual ~screenShotDialog();

	void callback(Fl_Widget *W, void *Data);

private:
	void initToNothing();
	int setupWidgets();
	int browse();

	Fl_Output *m_storeLabel;
	Fl_Button *m_browseButton;
	Fl_Input *m_filenameInput;

	Fl_Output *m_widthLabel;
	Fl_Int_Input *m_widthInput;

	Fl_Check_Button *m_noLabelsCheckButton;

	Fl_Output *m_heightLabel;
	Fl_Int_Input *m_heightInput;

	Fl_Button *m_OKButton, *m_cancelButton;
};

#endif /* _SCREEN_SHOT_DIALOG_H_ */
