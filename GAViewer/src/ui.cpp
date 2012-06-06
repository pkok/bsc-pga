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

#include "resource.h" /* for icon */
#endif /* WIN32 */

#include <FL/x.H> /* required to use windows file browser (contains definition of fl_xid()) */

#ifndef WIN32
#include "gaviewer.xbm"
#endif /* WIN32 */

#include <iostream>

#include <math.h>

#include "state.h"
#include "uistate.h"
#include "gafile.h"
#include "glwindow.h"
#include "object.h"
#include "mainwindow.h"
#include "console/consolewindow.h"
#include "selectwindow.h"
#include "dynamicstatementwindow.h"
#include "screenshotdialog.h"
#include "osdep.h"
#include "console/console.h"
#include "console/consolescope.h"
#include "console/consolevariable.h"

UIstate *gui_state = NULL;

void ui_timerCallback(void *);
void ui_controlCallback(Fl_Widget *W, void *Data);
void ui_statusCallback(Fl_Widget *W, void *Data);
void ui_consoleCallback(Fl_Widget *W, void *Data);

UIstate::UIstate(int argc, char *argv[]) {
	gui_state = this;

	m_interactiveMouse = true;

	m_tubeDraw.setLineWidth((float)2);
	m_tubeDraw.setUseOpenGL(false);
	m_tubeDraw.setNbSegments(8);

	initToNothing();

	int w = 1024, h = 700, mh = c_menuHeight, sh = c_statusHeight, consoleH = 200;

	m_controlGroupVisible = 1;
	m_consoleVisible = 1;
	m_scalarGroupVisible = 1;

	m_mainWindow = new mainWindow(w, h);
	m_mainWindow->setTitle("");
	m_mainWindow->setSizeRange();
	//m_mainWindow->size_range(c_controlWidth + 200, 200, 1600, 1200);

	m_menubar = new Fl_Menu_Bar (0,0, w, mh-1); 
	m_menubar->menu(gui_menuTable);
	m_menubar->global();

	m_glWindow = new glwindow(0, mh, w - c_controlWidth, h - mh - sh - consoleH, "OpenGL window");

	m_consoleGroup = new consoleWindow(0, m_glWindow->y() + m_glWindow->h(), m_glWindow->w(), consoleH);
	m_consoleGroup->size_range(100, 80);
	m_consoleGroup->box(FL_ENGRAVED_BOX);

/*	int cbw = (m_consoleGroup->w()-6 + 5) / 3;
	int cby = m_consoleGroup->h() - 3 - 20;
	m_consoleOutputButton = new Fl_Button(3, cby, cbw - 5, 20, "output");
	m_consoleOutputButton->callback(::ui_consoleCallback, NULL);
	m_consoleResetButton = new Fl_Button(3 + cbw * 1, cby, cbw - 5, 20, "reset");
	m_consoleResetButton->callback(::ui_consoleCallback, NULL);
	m_consoleInteractiveButton = new Fl_Button(3 + cbw * 2, cby, cbw - 5, 20, "interactive");
	m_consoleInteractiveButton->callback(::ui_consoleCallback, NULL);*/

	m_console = new Fl_Console(3, 3, m_consoleGroup->w()-6, m_consoleGroup->h() - 6);
	m_console->cprintf("GAViewer %s, created by Daniel Fontijne, \nLeo Dorst, Tim Bouma, University of Amsterdam; \nStephen Mann, University of Waterloo.\nType 'help()' for help on console functions.", g_version);
	m_console->add_command_callback(g_consoleCommandCallback, g_state);
	m_consoleGroup->end();
	m_consoleGroup->resizable(m_console);


	m_statusOutput = new Fl_Output(0, h - c_statusHeight, w - c_waitWidth, c_statusHeight);
	m_statusOutput->value("");
	m_statusOutput->color(FL_GRAY);
	m_statusOutput->box(FL_THIN_DOWN_BOX);

	m_waitButton = new Fl_Button(w - c_waitWidth, h - c_statusHeight, c_waitWidth, c_statusHeight, "pause");
	m_waitButton->callback(::ui_statusCallback, NULL);
	//m_waitButton->hide();
	
	m_controlGroup = new Fl_Window(w - c_controlWidth, mh, c_controlWidth, m_glWindow->h());
	m_controlGroup->box(FL_ENGRAVED_BOX);

	int x = 5, y = 5;

	// name 
	m_nameLabel = new Fl_Output(x, y, 55, 25);
	m_nameLabel->value("name: ");
	m_nameLabel->color(FL_GRAY);
	m_nameLabel->box(FL_FLAT_BOX);
	m_nameOutput = new Fl_Output(x + 60, y, 230, 25);
	m_nameOutput->color(FL_GRAY);
	y += 30;

	// remove
	m_removeButton = new Fl_Button(x, y, 290, 20, "remove this object");
	m_removeButton->callback(::ui_controlCallback, NULL);
	y += 25;

	// hide
	m_hideButton = new Fl_Button(x, y, 290, 20, "hide this object");
	m_hideButton->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	// foreground color & alpha
	m_fgColorButton = new Fl_Button(x, y, 290, 20, "set foreground color");
	m_fgColorButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_fgAlphaLabel = new Fl_Output(x, y, 70, 20);
	m_fgAlphaLabel->value("alpha: ");
	m_fgAlphaLabel->color(FL_GRAY);
	m_fgAlphaLabel->box(FL_FLAT_BOX);
	m_fgAlphaSlider = new Fl_Value_Slider(x + 75, y, 215, 20);
	m_fgAlphaSlider->type(FL_HOR_SLIDER);
	m_fgAlphaSlider->range(0.0, 1.0);
	m_fgAlphaSlider->step(0.01);
	m_fgAlphaSlider->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);
	m_fgAlphaSlider->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	// background color & alpha
	m_bgColorButton = new Fl_Button(x, y, 290, 20, "set background color");
	m_bgColorButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_bgAlphaLabel = new Fl_Output(x, y, 70, 20);
	m_bgAlphaLabel->value("alpha: ");
	m_bgAlphaLabel->color(FL_GRAY);
	m_bgAlphaLabel->box(FL_FLAT_BOX);
	m_bgAlphaSlider = new Fl_Value_Slider(x + 75, y, 215, 20);
	m_bgAlphaSlider->type(FL_HOR_SLIDER);
	m_bgAlphaSlider->range(0.0, 1.0);
	m_bgAlphaSlider->step(0.01);
	m_bgAlphaSlider->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);
	m_bgAlphaSlider->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	// outline color & alpha
	m_olColorButton = new Fl_Button(x, y, 290, 20, "set outline color");
	m_olColorButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_olAlphaLabel = new Fl_Output(x, y, 70, 20);
	m_olAlphaLabel->value("alpha: ");
	m_olAlphaLabel->color(FL_GRAY);
	m_olAlphaLabel->box(FL_FLAT_BOX);
	m_olAlphaSlider = new Fl_Value_Slider(x + 75, y, 215, 20);
	m_olAlphaSlider->type(FL_HOR_SLIDER);
	m_olAlphaSlider->range(0.0, 1.0);
	m_olAlphaSlider->step(0.01);
	m_olAlphaSlider->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);
	m_olAlphaSlider->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	// font size
	m_fontSizeLabel = new Fl_Output(x, y, 70, 20);
	m_fontSizeLabel->value("font size: ");
	m_fontSizeLabel->color(FL_GRAY);
	m_fontSizeLabel->box(FL_FLAT_BOX);
	m_fontSizeSlider = new Fl_Value_Slider(x + 75, y, 215, 20);
	m_fontSizeSlider->type(FL_HOR_SLIDER);
	m_fontSizeSlider->range(0.0, 100.0);
	m_fontSizeSlider->step(0.5);
	m_fontSizeSlider->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);
	m_fontSizeSlider->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	m_dmStippleButton = new Fl_Check_Button(x, y, 200, 20, "draw stipple");
	m_dmStippleButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_dmOriButton = new Fl_Check_Button(x, y, 200, 20, "draw orientation");
	m_dmOriButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_dmWireframeButton = new Fl_Check_Button(x, y, 200, 20, "draw wireframe");
	m_dmWireframeButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_dmShadeButton = new Fl_Check_Button(x, y, 200, 20, "draw shade");
	m_dmShadeButton->callback(::ui_controlCallback, NULL);
	y += 25;
	m_dmMagnitudeButton	= new Fl_Check_Button(x, y, 200, 20, "draw weight");
	m_dmMagnitudeButton->callback(::ui_controlCallback, NULL);
	y += 25;

	y += 10;

	m_drawMethodLabel = new Fl_Output(x, y, 290, 20);
	m_drawMethodLabel->value("draw method:");
	m_drawMethodLabel->color(FL_GRAY);
	m_drawMethodLabel->box(FL_FLAT_BOX);
	y += 25;
	m_drawMethodMenu = new Fl_Menu_Button(x, y, 290, 20);

	y += 10;

	// description
	m_descriptionLabel = new Fl_Output(x, y, 290, 20);
	m_descriptionLabel->value("object description:");
	m_descriptionLabel->color(FL_GRAY);
	m_descriptionLabel->box(FL_FLAT_BOX);
	y += 25;
	m_descriptionOutput = new Fl_Multiline_Output(x, y, 290, 95);
	m_descriptionOutput->color(FL_WHITE);
	m_descriptionOutput->box(FL_ENGRAVED_BOX);
	y += 100;

	m_controlGroup->end();

	
	m_scalarGroup = new Fl_Window(w - c_controlWidth, m_glWindow->h(), c_controlWidth, h - mh - sh - m_glWindow->h());
//	m_scalarGroup->box(FL_ENGRAVED_BOX);
	m_scalarGroup->box(FL_NO_BOX);
	m_scalarGroupScroll = new Fl_Scroll(0, 0, m_scalarGroup->w(), m_scalarGroup->h());
	m_scalarGroupScroll->box(FL_NO_BOX);
	m_scalarGroup->resizable(m_scalarGroupScroll);


	m_scalarGroup->end();

	setCurrentObject(NULL);

	char statusStr[256];
	sprintf(statusStr, "GAViewer %s", g_version);
	setStatus(statusStr);

#ifdef WIN32
	m_mainWindow->icon((char *)LoadIcon(fl_display, MAKEINTRESOURCE(IDI_ICON1)));
#else

#ifndef __MACH__
	Pixmap p = XCreateBitmapFromData(fl_display, DefaultRootWindow(fl_display),
                                 (const char *)gaviewer_bits, gaviewer_width, gaviewer_height);

	m_mainWindow->icon((char *)p);
#endif
	
#endif

	m_mainWindow->resizable(m_glWindow);
	m_mainWindow->end();
	m_mainWindow->show(argc, argv);


	Fl::add_timeout(1.0f / TIMER_FREQ, ui_timerCallback);
}

UIstate::~UIstate() {
	if (m_selectWindow) delete m_selectWindow;
	if (m_dynStmtWindow) delete m_dynStmtWindow;
	initToNothing();
}

void UIstate::initToNothing() {
	m_mainWindow = NULL;
	m_controlGroup = NULL;
	m_menubar = NULL;
	m_glWindow = NULL;

	m_nameLabel = m_nameOutput = m_fgAlphaLabel = 
		m_bgAlphaLabel = m_olAlphaLabel = m_fontSizeLabel = 
		m_descriptionLabel = m_drawMethodLabel = NULL;

	m_removeButton = m_hideButton = NULL;
	m_fgColorButton = m_bgColorButton = m_olColorButton = NULL;
	m_fgAlphaSlider = m_bgAlphaSlider = m_olAlphaSlider = m_fontSizeSlider = NULL;
	m_descriptionOutput = NULL;

	m_dmStippleButton = m_dmOriButton =	m_dmWireframeButton =m_dmShadeButton = m_dmMagnitudeButton = NULL;

	m_controlGroupVisible = 0;
	m_selectWindow = NULL;
	m_dynStmtWindow = NULL;

	m_statusOutput = NULL;
	m_waitButton = NULL;

	m_alwaysObjectDescriptionInStatusBar = true;

	m_drawMethodMenu = NULL;

	m_screenShotDialog = NULL;

//	m_centerTile = NULL;

	// console stuff
	m_consoleVisible = 0;
	m_consoleGroup = NULL;
//	m_consoleOutputButton = m_consoleResetButton = m_consoleInteractiveButton = NULL;
	m_console = NULL;

	// control scalars stuff:
	m_scalarGroupVisible = 0;
	m_scalarGroup = NULL;
	m_scalarGroupScroll = NULL;

	m_fsLastMouseActionTime = -1.0;
	m_fullscreen = 0;
	m_cursor = -1;


	m_screenShotOnNextRedraw = 0;
	m_ssWidth = m_ssHeight = 0;
	m_ssAlsoNoLabels = false; 

	m_pointSize = 0.1;
	m_textScale = 1.0;
	m_vectorHeadSize = -1.0;

}

void ui_timerCallback(void *) {
	Fl::repeat_timeout(1.0f / TIMER_FREQ, ui_timerCallback);
	gui_state->timerCallback();
}
int UIstate::timerCallback() {
	double t = u_timeGet();

	// read current file
	if (g_state->currentGAfile()) {
//		printf("Read file from timer\n");
		g_state->currentGAfile()->read(g_state);
	}

	// open a new file, if requested
	if (g_state->m_openFilename) {
//		printf("Open new file from timer\n");
		g_state->openGAfile(g_state->m_openFilename, g_state->m_openFileNbArg, g_state->m_openFileArg, g_state->m_openFileLevel);
		g_state->freeOpenFile();
	}


	if (m_mainWindow == NULL) return 0; // program terminated

	g_state->handleTrl();
	g_state->handleRot();
	g_state->objectUpdate();

	if (g_state->m_inputWait) { // make clear that we are waiting for input
		int cl = ((int)(t * 2) & 1)? FL_RED : FL_GRAY;
		if (cl != m_waitButton->color()) {
			m_waitButton->color(cl);
			m_waitButton->redraw();
		}
	}

	// if fullscreen, check for mouse action
	if (m_fullscreen) {
		if ((t - m_fsLastMouseActionTime) > 2.0) {
			if (m_cursor != FL_CURSOR_NONE) { // make cursor disappear
				m_cursor = FL_CURSOR_NONE;
				m_mainWindow->cursor(FL_CURSOR_NONE);
			}
		}
		else {
			if (m_cursor != FL_CURSOR_DEFAULT) {
				m_cursor = FL_CURSOR_DEFAULT;
				m_mainWindow->cursor(FL_CURSOR_DEFAULT);
			}
		}
	}

	// check for screenshots, if so: redraw
	if (m_screenShotOnNextRedraw) {
		m_glWindow->redraw();
	}


 	// animate dynamic statements depending on 'atime'
	g_state->updateAnimation();

	// handle network connections
	g_state->pollNetServers();

	return 0;
}

void UIstate::ui_controlCallback(Fl_Widget *W, void *Data) {
	int i;
	object *o = m_currentObject;
	if (o == NULL) return;

	if (W == m_removeButton) {
		g_state->removeObject(o);
	}
	else if (W == m_hideButton) {
		o->toggleHide();
		setCurrentObject(o);
	}
	else if (W == m_fgColorButton) {
		double rgb[4] = {o->fgColor(0), o->fgColor(1), o->fgColor(2), o->fgColor(3)};
		if (fl_color_chooser("Set foreground color", rgb[0], rgb[1], rgb[2])) {
			for (i = 0; i < 3; i++)
				o->setFgColor(rgb);
		}
	}
	else if (W == m_fgAlphaSlider) {
		o->setFgAlpha((float)m_fgAlphaSlider->value());
	}
	else if (W == m_bgColorButton) {
		double rgb[4] = {o->bgColor(0), o->bgColor(1), o->bgColor(2), o->bgColor(3)};
		if (fl_color_chooser("Set background color", rgb[0], rgb[1], rgb[2])) {
			for (i = 0; i < 3; i++)
				o->setBgColor(rgb);
		}
	}
	else if (W == m_bgAlphaSlider) {
		o->setBgAlpha((float)m_bgAlphaSlider->value());
	}
	else if (W == m_olColorButton) {
		double rgb[4] = {o->olColor(0), o->olColor(1), o->olColor(2), o->olColor(3)};
		if (fl_color_chooser("Set outline color", rgb[0], rgb[1], rgb[2])) {
			for (i = 0; i < 3; i++)
				o->setOlColor(rgb);
		}
	}
	else if (W == m_olAlphaSlider) {
		o->setOlAlpha((float)m_olAlphaSlider->value());
	}
	else if (W == m_fontSizeSlider) {
		//o->m_fontSize = (float)m_fontSizeSlider->value();
		o->setFontSize((float)m_fontSizeSlider->value());
	}
	else if (W == m_dmStippleButton) {
		o->m_drawMode = o->m_drawMode ^ OD_STIPPLE;
		m_dmStippleButton->value((o->m_drawMode & OD_STIPPLE) != 0);
	}
	else if (W == m_dmOriButton) {
		o->m_drawMode = o->m_drawMode ^ OD_ORI;
		m_dmOriButton->value((o->m_drawMode & OD_ORI) != 0);
	}
	else if (W == m_dmWireframeButton) {
		o->m_drawMode = o->m_drawMode ^ OD_WIREFRAME;
		m_dmWireframeButton->value((o->m_drawMode & OD_WIREFRAME) != 0);
	}
	else if (W == m_dmShadeButton) {
		o->m_drawMode = o->m_drawMode ^ OD_SHADE;
		m_dmShadeButton->value((o->m_drawMode & OD_SHADE) != 0);
	}
	else if (W == m_dmMagnitudeButton) {
		o->m_drawMode = o->m_drawMode ^ OD_MAGNITUDE;
		m_dmMagnitudeButton->value((o->m_drawMode & OD_MAGNITUDE) != 0);
	}


	gui_state->m_glWindow->redraw();
}

void ui_controlCallback(Fl_Widget *W, void *Data) {
	gui_state->ui_controlCallback(W, Data);
}

void ui_statusCallback(Fl_Widget *W, void *Data) {
	if (W == gui_state->m_waitButton) {
		g_state->setInputWaitState(!g_state->m_inputWait);
		//gui_state->m_statusOutput->value("");
	}
}

void UIstate::ui_consoleCallback(Fl_Widget *W, void *Data) {
/*	if (W == m_consoleOutputButton) {
		m_console->deactivate();
	}
	else if (W == m_consoleResetButton) {
		m_console->activate();		
		// todo: close all GA files
	}
	else if (W == m_consoleInteractiveButton) {
		m_console->activate();
	}*/
}


void ui_consoleCallback(Fl_Widget *W, void *Data) {
	gui_state->ui_consoleCallback(W, Data);
}


/*
Menu definition
*/
Fl_Menu_Item gui_menuTable[] = {
  {"&File",0,0,0,FL_SUBMENU},
    {"&Open", FL_ALT+'o', ui_menuCallback, (void*)MI_OPEN_ANY, 0},
	{"Open ->",0,0,0,FL_SUBMENU},
		{"Open geo file", 0, ui_menuCallback, (void*)MI_OPEN, 0},
	    {"Open geo playlist", 0, ui_menuCallback, (void*)MI_OPENPLAYLIST, 0},
	    {"Open g file", 0, ui_menuCallback, (void*)MI_LOAD_G_FILE, 0},
	    {0},
    {"Load .g directory", 0, ui_menuCallback, (void*)MI_LOAD_G_DIR, FL_MENU_DIVIDER | 0},
    {"&Save State", 0, ui_menuCallback, (void*)MI_SAVE_STATE, FL_MENU_DIVIDER | 0},
    {"&Replay",	FL_ALT+'r', ui_menuCallback, (void*)MI_REPLAY, 0},
    {"Next file in playlist", FL_ALT+'.', ui_menuCallback, (void*)MI_NEXTPLAYLIST, 0},
    {"Previous file in playlist", FL_ALT+',', ui_menuCallback, (void*)MI_PREVPLAYLIST, FL_MENU_DIVIDER | 0},
    {"&Exit",	FL_ALT+'x', ui_menuCallback, (void*)MI_QUIT, 0},
    {0},
  {"&View",0,0,0,FL_SUBMENU},
	{"Select object",	0, ui_menuCallback, (void*)MI_SELECTOBJECTS, 0},
	{"Hide",0,0,0,FL_SUBMENU},
		{"Unhide &all",	FL_ALT+'a', ui_menuCallback, (void*)MI_UNHIDEALL, 0},
		{"Select hidden object",	0, ui_menuCallback, (void*)MI_LISTHIDDENOBJECTS, 0},
		{"Show hidden object",	0, ui_menuCallback, (void*)MI_SHOWHIDDENOBJECTS, 0},
	    {0},
	{"Canvas",0,0,0,FL_SUBMENU},
		{"White canvas",	0, ui_menuCallback, (void*)MI_WHITE_CANVAS, 0},
		{"Light grey canvas",	0, ui_menuCallback, (void*)MI_LIGHT_GREY_CANVAS, 0},
		{"Grey canvas",	0, ui_menuCallback, (void*)MI_GREY_CANVAS, 0},
		{"Black canvas",	0, ui_menuCallback, (void*)MI_BLACK_CANVAS, 0},
	    {0},
	{"Console font size",0,0,0,FL_SUBMENU},
		{"12",	0, ui_menuCallback, (void*)MI_FONT_SIZE_12, 0},
		{"16",	0, ui_menuCallback, (void*)MI_FONT_SIZE_16, 0},
		{"20",	0, ui_menuCallback, (void*)MI_FONT_SIZE_20, 0},
		{"24",	0, ui_menuCallback, (void*)MI_FONT_SIZE_24, 0},
	    {0},
	{"Point size",0,0,0,FL_SUBMENU},
		{"0.01",	0, ui_menuCallback, (void*)MI_POINT_SIZE_01, 0},
		{"0.05",	0, ui_menuCallback, (void*)MI_POINT_SIZE_05, 0},
		{"0.1",	0, ui_menuCallback, (void*)MI_POINT_SIZE_1, 0},
		{"0.5",	0, ui_menuCallback, (void*)MI_POINT_SIZE_5, 0},
	    {0},
	{"Line Width",0,0,0,FL_SUBMENU},
		{"1.0",	0, ui_menuCallback, (void*)MI_LINE_WIDTH_1, 0},
		{"2.0",	0, ui_menuCallback, (void*)MI_LINE_WIDTH_2, 0},
		{"4.0",	0, ui_menuCallback, (void*)MI_LINE_WIDTH_4, 0},
		{"8.0",	0, ui_menuCallback, (void*)MI_LINE_WIDTH_8, 0},
	    {0},
    {"&Controls",	0, ui_menuCallback, (void*)MI_HIDE_CONTROLS, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"Scalar Controls",	0, ui_menuCallback, (void*)MI_HIDE_SCALAR_CONTROLS, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"Console",	0, ui_menuCallback, (void*)MI_HIDE_CONSOLE, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"&Labels always on top",	FL_ALT+'l', ui_menuCallback, (void*)MI_LABELSALWAYSONTOP, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"&Object description in statusbar",	0, ui_menuCallback, (void*)MI_OBJECTDESCRIPTIONINSTATUSBAR, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"&GL lines",	0, ui_menuCallback, (void*)MI_GLLINES, FL_MENU_TOGGLE},
//    {"Enable clipping planes",	0, ui_menuCallback, (void*)MI_CLIPPINGPLANES, FL_MENU_TOGGLE},
	{"F&ullscreen", FL_ALT+'u', ui_menuCallback, (void*)MI_FULLSCREEN, FL_MENU_TOGGLE},
    {0},
  {"&Dynamic",0,0,0,FL_SUBMENU},
	{"View Dynamic statements", 0, ui_menuCallback, (void*)MI_DYNAMIC_STATEMENTS, FL_MENU_DIVIDER | 0},
	{"Start / resume animation", 0, ui_menuCallback, (void*)MI_START_ANIMATION, 0},
	{"Pause animation", 0, ui_menuCallback, (void*)MI_PAUSE_ANIMATION, 0},
	{"Stop animation", 0, ui_menuCallback, (void*)MI_STOP_ANIMATION, 0},
	{"Playback speed",0,0,0,FL_SUBMENU},
		{"0.25x realtime", 0, ui_menuCallback, (void*)MI_SLEEP_x4, 0},
		{"0.5x realtime", 0, ui_menuCallback, (void*)MI_SLEEP_x2, 0},
		{"realtime", 0, ui_menuCallback, (void*)MI_SLEEP_x1, 0},
		{"2x realtime", 0, ui_menuCallback, (void*)MI_SLEEP_d2, 0},
		{"4x realtime", 0, ui_menuCallback, (void*)MI_SLEEP_d4, 0},
		{"10x realtime", 0, ui_menuCallback, (void*)MI_SPEED_d10, 0},
		{"AFAP", 0, ui_menuCallback, (void*)MI_SPEED_x0, 0},
	    {0},
    {0},
  {"&Utils",0,0,0,FL_SUBMENU},
	{"Search for next &bookmark", FL_ALT+'b', ui_menuCallback, (void*)MI_BOOKMARK, FL_MENU_DIVIDER | 0},  
	{"Output current camera orientation (bivector)",0, ui_menuCallback, (void*)MI_PRINT_ROTATION_BIVECTOR, 0},
	{"Output current camera orientation (rotor)",0, ui_menuCallback, (void*)MI_PRINT_ROTATION_ROTOR, 0},
	{"Output current camera translation",0, ui_menuCallback, (void*)MI_PRINT_TRANSLATION_VECTOR, FL_MENU_DIVIDER | 0},
	{"Screenshot",0, ui_menuCallback, (void*)MI_SCREENSHOT, 0},
    {0},
  {"&Help",0,0,0,FL_SUBMENU},
    {"About", 0, ui_menuCallback, (void*)MI_ABOUT, 0},
    {0},
  {0}
};

void ui_menuCallback(Fl_Widget *W, void *Data) {
	int item = (int)((unsigned char*)Data - (unsigned char*)NULL);
	int mi = 0, d = 1;
	e3ga B, R;
	GAIM_FLOAT angle;
	state::OI oi;

	while (d) {
		if (gui_menuTable[mi].text == 0) d--;
		else if (gui_menuTable[mi].flags & FL_SUBMENU) d++;
		if (gui_menuTable[mi].user_data_ == Data) break;
		mi++;
	}

	switch(item) {
	case MI_OPEN_ANY:
		gui_state->openAnyFile();
		break;
	case MI_OPEN:
		gui_state->openGeoFile();
		break;
	case MI_REPLAY:
		if (g_state) g_state->replayFirstGAfile();
		break;
	case MI_SAVE_STATE:
		gui_state->saveState();
		/*cprintf("Todo: selection window\n");
		if (g_state) g_state->writeStateToGeoFile("test.geo");*/
		break;
	case MI_LOAD_G_FILE:
		gui_state->loadGFile();
		break;
	case MI_LOAD_G_DIR:
		gui_state->loadGDir();
		//cprintf("Todo\n");
		break;
	case MI_QUIT:
		delete gui_state->m_mainWindow;
		break;
	case MI_HIDE_CONTROLS:
		gui_state->toggleHideControls(mi);
		break;
	case MI_HIDE_SCALAR_CONTROLS:
		gui_state->toggleHideScalarControls(mi);
		break;
	case MI_HIDE_CONSOLE:
		gui_state->toggleHideConsole(mi);
		break;
	case MI_LABELSALWAYSONTOP:
		g_state->m_labelsAlwaysOnTop = !g_state->m_labelsAlwaysOnTop;
		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((g_state->m_labelsAlwaysOnTop) ? FL_MENU_VALUE : 0);
		break;
	case MI_OBJECTDESCRIPTIONINSTATUSBAR:
		gui_state->m_alwaysObjectDescriptionInStatusBar = !gui_state->m_alwaysObjectDescriptionInStatusBar;
		if (!gui_state->m_alwaysObjectDescriptionInStatusBar) gui_state->setStatus("");
		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((gui_state->m_alwaysObjectDescriptionInStatusBar) ? FL_MENU_VALUE : 0);
		break;
	case MI_GLLINES:
		gui_state->m_tubeDraw.setUseOpenGL(!gui_state->m_tubeDraw.getUseOpenGL());
		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((gui_state->m_tubeDraw.getUseOpenGL()) ? FL_MENU_VALUE : 0);
		break;
/*	case MI_CLIPPINGPLANES:
		g_state->m_clippingPlanesEnabled = !g_state->m_clippingPlanesEnabled;
		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((g_state->m_clippingPlanesEnabled) ? FL_MENU_VALUE : 0);
		break;*/
	case MI_UNHIDEALL:
		for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++) {
			if (oi->second->hidden())
					oi->second->show();
		}
		gui_state->m_glWindow->redraw();
		break;
	case MI_LISTHIDDENOBJECTS:
		gui_state->createSelectWindow(SWM_SELECT_HIDDEN);
		break;
	case MI_SELECTOBJECTS:
		gui_state->createSelectWindow(SWM_SELECT);
		break;
	case MI_SHOWHIDDENOBJECTS:
		gui_state->createSelectWindow(SWM_SHOW);
		break;
	case MI_DYNAMIC_STATEMENTS:
		gui_state->createDynStmtWindow();
		break;
	case MI_ABOUT:
		fl_message("GAViewer %s, created by Daniel Fontijne, \n"
			"Leo Dorst, Tim Bouma, University of Amsterdam; \n"
			"Stephen Mann, University of Waterloo.\n"
			"\nGAViewer makes use of the following great libraries/programs:\n\n"
			"-flex and byacc (label typesetting parser)\n"
			"-zlib and libpng (reading and writing images)\n"
			"-FLTK (user interface)\n"
			"-ANTLR (console parser and internal programming language)\n"
			, g_version);
		break;
	case MI_START_ANIMATION:
		g_state->startAnimation();
		break;
	case MI_STOP_ANIMATION:
		g_state->stopAnimation();
		break;
	case MI_PAUSE_ANIMATION:
		g_state->pauseAnimation();
//		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((gui_state->m_glWindow->m_animate) ? FL_MENU_VALUE : 0);
		break;
/*	case MI_ANIMATE:
		gui_state->m_glWindow->m_animate = !gui_state->m_glWindow->m_animate;
//		gui_menuTable[mi].flags  = FL_MENU_TOGGLE | ((gui_state->m_glWindow->m_animate) ? FL_MENU_VALUE : 0);
		break;*/
	case MI_FULLSCREEN:
		gui_state->toggleFullscreen(mi);
		break;
	case MI_PRINT_ROTATION_BIVECTOR:
		// todo: use function rotor2Bivector for this purpose
		R = gui_state->m_glWindow->getCamOri();
		R = R / sqrt((R << R.reverse()).scalar()); // normalization (rotor seems to drift of unit manifold, todo: fix this in glwindow.cpp)
		B = R(GRADE2);
		angle = atan2(sqrt(B.norm_a()), R.scalar());
		if (B.norm_a() != 0.0) B = angle * B.normal();
		else B = 0.0;
/*		R.print("Rotor : "); // check...
		B.exp().print("exp(B): ");*/
		cprintf("Camera bivector: %s", B.string("%e"));
		break;
	case MI_PRINT_ROTATION_ROTOR:
		R = gui_state->m_glWindow->getCamOri();
		R = R / sqrt((R << R.reverse()).scalar()); // normalization (rotor seems to drift of unit manifold, todo: fix this in glwindow.cpp)
		//R.print("Camera rotor: ", "%e");
		cprintf("Camera rotor: %s", R.string("%e"));
		break;
	case MI_PRINT_TRANSLATION_VECTOR:
		cprintf("Camera translation: %s\n", gui_state->m_glWindow->getCamPos().string("%e"));
		break;
	case MI_SLEEP_x4:
		g_state->setPlaybackSpeed(4.0);
		break;
	case MI_SLEEP_x2:
		g_state->setPlaybackSpeed(2.0);
		break;
	case MI_SLEEP_x1:
		g_state->setPlaybackSpeed(1.0);
		break;
	case MI_SLEEP_d2:
		g_state->setPlaybackSpeed(0.5);
		break;
	case MI_SLEEP_d4:
		g_state->setPlaybackSpeed(0.25);
		break;
	case MI_SPEED_d10:
		g_state->setPlaybackSpeed(0.1);
		break;
	case MI_SPEED_x0:
		g_state->setPlaybackSpeed(0.0);
		break;
	case MI_BOOKMARK:
		g_state->bookmarkSearch();
		break;
	case MI_WHITE_CANVAS:
	case MI_GREY_CANVAS:
	case MI_BLACK_CANVAS:
		g_state->setColor("cvcolor", -0.5f * (item - MI_BLACK_CANVAS) , 
			-0.5f * (item - MI_BLACK_CANVAS), 
			-0.5f * (item - MI_BLACK_CANVAS), 0.0f);
		gui_state->m_glWindow->redraw();
		break;
	case MI_LIGHT_GREY_CANVAS:
		g_state->setColor("cvcolor", 0.65f, 0.65f, 0.65f, 0.0f);
		gui_state->m_glWindow->redraw();
		break;
	case MI_OPENPLAYLIST:
		gui_state->openPlayList();
		break;
	case MI_NEXTPLAYLIST:
		g_state->nextPlayListEntry();
		break;
	case MI_PREVPLAYLIST:
		g_state->previousPlayListEntry();
		break;
	case MI_FONT_SIZE_12:
	case MI_FONT_SIZE_16:
	case MI_FONT_SIZE_20:
	case MI_FONT_SIZE_24:
		gui_state->setConsoleFontSizeFromMenu(item);
		break;
	case MI_POINT_SIZE_01:
	case MI_POINT_SIZE_05:
	case MI_POINT_SIZE_1:
	case MI_POINT_SIZE_5:
		gui_state->setPointSizeFromMenu(item);
		break;
	case MI_LINE_WIDTH_1:
	case MI_LINE_WIDTH_2:
	case MI_LINE_WIDTH_4:
	case MI_LINE_WIDTH_8:
		gui_state->setLineWidthFromMenu(item);
		break;
	case MI_SCREENSHOT:
		gui_state->createScreenshotDialog();
		break;
	}
}

int UIstate::setConsoleFontSizeFromMenu(int menuItem) {
	int sizeTable[] = {12, 16, 20, 24, -1, -1, -1};
	if ((menuItem <MI_FONT_SIZE_MIN) || (menuItem > MI_FONT_SIZE_MAX)) return -1;
	menuItem -= MI_FONT_SIZE_MIN;
	return setConsoleFontSize(sizeTable[menuItem]);
}

int UIstate::setConsoleFontSize(int size) {
	const int minS = 6, maxS = 32;
	if ((size < minS) || (size > maxS)) {
		cprintf("UIstate::setConsoleFontSize(): invalid font size '%d' (min: %d, max: %d)\n", size, minS, maxS);
		return -1;
	}

	if (m_console) {
		m_console->textsize(size);
		m_console->resize(m_console->x(), m_console->y(), m_console->w(), m_console->h()); // to force recalc of lines pos?
		m_console->redraw();
	}

	return 0;
}

void UIstate::setPointSize(double size) {
	m_pointSize = size;
}

void UIstate::setPointSizeFromMenu(int menuItem) {
	double s = 0.1;
	switch(menuItem) {
		case MI_POINT_SIZE_01:
			s = 0.01;
			break;
		case MI_POINT_SIZE_05:
			s = 0.05;
			break;
		case MI_POINT_SIZE_1:
			s = 0.1;
			break;
		case MI_POINT_SIZE_5:
			s = 0.5;
			break;
	}
	setPointSize(s);
}

void UIstate::setTextScale(double scale) {
	double oldScale = m_textScale;
	m_textScale = scale;

	if (oldScale != m_textScale) {
		g_state->textScaleChanged();
	}
}


void UIstate::setLineWidthFromMenu(int menuItem) {
	double s = 1.0;
	switch(menuItem) {
		case MI_LINE_WIDTH_1:
			s = 1.0;
			break;
		case MI_LINE_WIDTH_2:
			s = 2.0;
			break;
		case MI_LINE_WIDTH_4:
			s = 4.0;
			break;
		case MI_LINE_WIDTH_8:
			s = 8.0;
			break;
	}
	setLineWidth(s);
	
}

void UIstate::setLineWidth(double width) {
	//m_lineWidth = width;
	m_tubeDraw.setLineWidth(width);
}

void UIstate::setVectorHeadSize(double size) {
	m_vectorHeadSize = size;
}


int UIstate::createSelectWindow(int mode) {
	int nb = 0, h;
	state::OI oi;
	for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++)
		if ((mode == SWM_SELECT) || (oi->second->hidden())) nb++;

	if (nb == 0)
		m_selectWindow = new selectWindow(mode, 200, 30, (mode == SWM_SELECT) ? "No objects" : "No hidden objects");
	else {
		h = 25 + 10 + nb * 25;
		m_selectWindow = new selectWindow(mode, 200, (h > 400) ? 400 : h, 
			(mode == SWM_SELECT_HIDDEN) ? "Select hidden object:" : 
			((mode == SWM_SELECT) ? "Select object:" : "Show hidden objects:"));
	}
//	m_selectWindow->m_mode = mode;
	m_selectWindow->end();
	m_selectWindow->set_modal();
	m_selectWindow->hotspot(100, 100);
	m_selectWindow->show();
	return 0;
}


int UIstate::createDynStmtWindow() {
	m_dynStmtWindow = new dynStmtWindow(500, 30, "Dynamic statements:");
	m_dynStmtWindow->end();
	m_dynStmtWindow->set_modal();
	m_dynStmtWindow->hotspot(100, 100);
	m_dynStmtWindow->show();
	return 0;
}

int UIstate::createScreenshotDialog() {

	// try to create the dialog so that it does not overlap with the GL window:
	int x = m_mainWindow->x() + m_mainWindow->w() / 2 - 280 / 2;
	int y = m_mainWindow->y() + m_glWindow->y() + m_glWindow->h() + 50;

	m_screenShotDialog = new screenShotDialog(x, y, 600, 150, "Screen shot:");
	m_screenShotDialog->end();
	m_screenShotDialog->set_modal();
//	m_screenShotDialog->hotspot(100, 100);
	m_screenShotDialog->show();

	return 0;
}

#ifdef WIN32
// Win32 Version:
const char *UIstate::genericOpenFile(const std::string &dialogMsg, std::vector<std::pair<const char *, const char *> >filterDesc, const std::string &defFileName) {
	// setup filter
	std::string filter;
	std::vector<std::pair<const char *, const char *> >::iterator I;
	for (I = filterDesc.begin(); I != filterDesc.end(); I++) {
		filter += std::string((*I).second) + " (" + std::string((*I).first) + ")";
		filter.append(1, 0);
		filter += std::string((*I).first);
		filter.append(1, 0);
	}
	filter.append(2, 0);

	// display dialog, return file
    char tmpFilename[1024], tmpFilename2[256];
	strcpy(tmpFilename, defFileName.c_str());
	OPENFILENAME ofn;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = fl_xid(m_mainWindow);
	ofn.lpstrTitle = dialogMsg.c_str();
	ofn.lpstrFile = tmpFilename;
	ofn.lpstrFileTitle = tmpFilename2;
	ofn.nMaxFile = 1023;
	ofn.nMaxFileTitle = 255;
	ofn.lpstrFilter = filter.c_str();
//	printf("'%s' '%s'\n", ofn.lpstrTitle, ofn.lpstrFilter);
	ofn.lpstrDefExt = filterDesc.at(0).second + 2;
	if (GetOpenFileName(&ofn)) {
		static char filename[1024];
		strcpy(filename, tmpFilename);
		return filename;
	}
	else return NULL;
}
#else 
// UNIX version:
const char *UIstate::genericOpenFile(const std::string &dialogMsg, std::vector<std::pair<const char *, const char *> >filterDesc, const std::string &defFileName) {
	// setup filter
	std::string filter;
	std::vector<std::pair<const char *, const char *> >::iterator I;
	for (I = filterDesc.begin(); I != filterDesc.end(); I++) {
		filter += ((I == filterDesc.begin()) ? "" : "|") + std::string((*I).first);
	}

	// display dialog, return file
	return fl_file_chooser(dialogMsg.c_str(), filter.c_str(), defFileName.c_str());
}
#endif

int UIstate::openAnyFile() {
	std::vector<std::pair<const char *, const char *> >filterDesc;
	filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.*", (const char*)"all files"));
	filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.geo", (const char*)"geo files"));
	filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.gpl", (const char*)"geo play list files"));
	filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.g", (const char*)"g files"));

	const char *filename = genericOpenFile("open file: ", filterDesc, m_prevAnyFile);
	if (filename == NULL) return 0; // no open

	const char *ptr = strrchr(filename, '.');
	std::string ext((ptr) ? ptr : "");
	if (ext == ".geo") return openGeoFile(filename);
	else if (ext == ".gpl") return openPlayList(filename);
	else if (ext == ".g") return loadGFile(filename);
	else {
		cprintf("Can not handle file '%s'\n", filename);
		return 0;
	}
}

int UIstate::openGeoFile(const char *filename /*= NULL*/) {

	if (filename == NULL) {
		std::vector<std::pair<const char *, const char *> >filterDesc;
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.geo", (const char*)"geo files"));
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.*", (const char*)"all files"));

		filename = genericOpenFile("Open geo file: ", filterDesc, m_prevGeoFile);
		if (filename == NULL) return 0; // no open

	}

	setPrevGeoFile(filename);

	g_state->clearPlayList();

//	m_glWindow->redraw();

	return g_state->openGAfile(filename);
}

int UIstate::openPlayList(const char *filename /*= NULL*/) {
	if (filename == NULL) {
		std::vector<std::pair<const char *, const char *> >filterDesc;
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.gpl", (const char*)"geo playlist files"));
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.*", (const char*)"all files"));

		filename = genericOpenFile("Open gpl file: ", filterDesc, m_prevGPLFile);
		if (filename == NULL) return 0; // no open
	}

	setPrevGPLFile(filename);

//	m_glWindow->redraw();

	return g_state->openPlayList(filename);
}


int UIstate::loadGFile(const char *filename /*= NULL*/) {

	if (filename == NULL) {
		std::vector<std::pair<const char *, const char *> >filterDesc;
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.g", (const char*)"g"));
		filterDesc.push_back(std::make_pair<const char*, const char *>((const char*)"*.*", (const char*)"all files"));

		filename = genericOpenFile("Open g file: ", filterDesc, m_prevGFile);
		if (filename == NULL) return 0; // no open
	}

	setPrevGFile(filename);

	g_state->consoleSourceFileRead(filename);

	g_state->updateDynStmts();

	return 0;
}

int UIstate::loadGDir() {
	char filename[1024];

	filename[0] = 0;

	char *sourcePath;
	if ( (sourcePath = fl_dir_chooser("Open dir", NULL)) != NULL)
		strcpy(filename, sourcePath);
	else return 0;

	g_state->consoleSourceDirRead(filename);

	g_state->updateDynStmts();

	return 0;
}

int UIstate::saveState() {
	char filename[1024];

	filename[0] = 0;

#ifdef WIN32
    char tmpFilename[1024], tmpFilename2[256];
	OPENFILENAME ofn;
	tmpFilename[0] = 0;
	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = fl_xid(m_mainWindow);
	ofn.lpstrTitle = "Save file";
	ofn.lpstrFile = tmpFilename;
	ofn.lpstrFileTitle = tmpFilename2;
	ofn.nMaxFile = 1023;
	ofn.nMaxFileTitle = 255;
	ofn.lpstrFilter = "geo files (*.geo)\0*.geo\0All files (*.*)\0*.*\0\0\0";
	ofn.lpstrDefExt = "geo";
	if (GetSaveFileName(&ofn))
		strcpy(filename, tmpFilename);
	else return 0;
#else /* assume UNIX */
	char *sourcePath;
	if ( (sourcePath = fl_file_chooser("Save file", "*.geo", filename)) != NULL)
		strcpy(filename, sourcePath);
	else return 0;
#endif /* WIN32 */
	//printf("Store in '%s'\n", filename);

	if (g_state) g_state->writeStateToGeoFile(filename);

	return 0;
}



int UIstate::toggleHideControls(int mi) {
	m_controlGroupVisible = !m_controlGroupVisible;

	if (m_controlGroupVisible) {
		m_controlGroup->show();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE | FL_MENU_VALUE;
	}
	else {
		m_controlGroup->hide();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE;
	}

	if (!m_controlGroupVisible && !m_consoleVisible && m_scalarGroupVisible)
		ui_menuCallback(NULL, (void*)MI_HIDE_SCALAR_CONTROLS);

	m_mainWindow->resize(m_mainWindow->x(), m_mainWindow->y(), m_mainWindow->w(), m_mainWindow->h());
	return 0;
}

int UIstate::toggleHideScalarControls(int mi) {	
	m_scalarGroupVisible = !m_scalarGroupVisible;

	if (m_scalarGroupVisible) {
		if (!m_controlGroupVisible && !m_consoleVisible) 
			ui_menuCallback(NULL, (void*)MI_HIDE_CONSOLE);
		m_scalarGroup->show();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE | FL_MENU_VALUE;
	}
	else {
		m_scalarGroup->hide();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE;
	}

	m_mainWindow->resize(m_mainWindow->x(), m_mainWindow->y(), m_mainWindow->w(), m_mainWindow->h());
	return 0;
}

int UIstate::toggleHideConsole(int mi) {
	m_consoleVisible = !m_consoleVisible;

	if (m_consoleVisible) {
		m_consoleGroup->show();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE | FL_MENU_VALUE;
	}
	else {
		m_consoleGroup->hide();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE;
	}

	if (!m_controlGroupVisible && !m_consoleVisible && m_scalarGroupVisible)
		ui_menuCallback(NULL, (void*)MI_HIDE_SCALAR_CONTROLS);

	m_mainWindow->resize(m_mainWindow->x(), m_mainWindow->y(), m_mainWindow->w(), m_mainWindow->h());
	return 0;

}

int UIstate::mouseMove() {
	m_fsLastMouseActionTime = u_timeGet();
	return 0;
}

int UIstate::toggleFullscreen(int mi) {
	m_fullscreen = !m_fullscreen;

	if (m_fullscreen) {
		gui_state->m_mainWindow->fullscreen();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE | FL_MENU_VALUE;
	}
	else {
		m_mainWindow->cursor(FL_CURSOR_DEFAULT);
		m_cursor = FL_CURSOR_DEFAULT;
		gui_state->m_mainWindow->fullscreen_off();
		gui_menuTable[mi].flags = FL_MENU_TOGGLE;
	}

	return 0;
}

static void repositionY(Fl_Widget *W, int y) {
	W->resize(W->x(), y, W->w(), W->h());
	W->show();
}

int UIstate::setCurrentObjectByName(const std::string &name) {
	return setCurrentObject(g_state->getObjectPtrByName(name));
}

int UIstate::setCurrentObject(object *o) {
	m_currentObject = o;

	if (o == NULL) {
		m_nameLabel->show();
		m_nameOutput->value("no object selected");
		m_removeButton->hide();
		m_hideButton->hide();
		m_fgColorButton->hide();
		m_fgAlphaLabel->hide();
		m_fgAlphaSlider->hide();
		m_bgColorButton->hide();
		m_bgAlphaLabel->hide();
		m_bgAlphaSlider->hide();
		m_olColorButton->hide();
		m_olAlphaLabel->hide();
		m_olAlphaSlider->hide();
		m_fontSizeLabel->hide();
		m_fontSizeSlider->hide();
		m_descriptionLabel->hide();
		m_descriptionOutput->hide();
		m_dmStippleButton->hide();
		m_dmOriButton->hide();
		m_dmWireframeButton->hide();
		m_dmShadeButton->hide();
		m_dmMagnitudeButton->hide();
		m_drawMethodLabel->hide();
		m_drawMethodMenu->hide();
	}
	else {
		int y = 5;

		if (o->m_properties & OP_NAME) {
			m_nameLabel->show();
			m_nameLabel->position(m_nameLabel->x(), y);
			m_nameOutput->show();
			m_nameOutput->position(m_nameOutput->x(), y);
			y += 30;
		}
		else {
			m_nameLabel->hide();
			m_nameOutput->hide();
		}

		m_removeButton->show();
		m_removeButton->position(m_removeButton->x(), y);
		y += 25;

		if (o->m_properties & OP_HIDE) {
			m_hideButton->show();
			m_hideButton->position(m_hideButton->x(), y);
			y += 25; 
	//		m_hideButton->label((o->m_drawMode & OD_HIDE) ? "show this object" : "hide this object");
			m_hideButton->redraw();
		}
		else m_hideButton->hide();

		y += 10;

		if (o->m_properties & OP_FGCOLOR) {
			repositionY(m_fgColorButton, y);
			y += 25;
			repositionY(m_fgAlphaLabel, y);
			repositionY(m_fgAlphaSlider, y);
			y += 25;
			y += 10;
		}
		else {
			m_fgColorButton->hide();
			m_fgAlphaLabel->hide();
			m_fgAlphaSlider->hide();
		}

		if (o->m_properties & OP_BGCOLOR) {
			repositionY(m_bgColorButton, y);
			y += 25;
			repositionY(m_bgAlphaLabel, y);
			repositionY(m_bgAlphaSlider, y);
			y += 25;
			y += 10;
		}
		else {
			m_bgColorButton->hide();
			m_bgAlphaLabel->hide();
			m_bgAlphaSlider->hide();
		}

		if (o->m_properties & OP_OLCOLOR) {
			repositionY(m_olColorButton, y);
			y += 25;
			repositionY(m_olAlphaLabel, y);
			repositionY(m_olAlphaSlider, y);
			y += 25;
			y += 10;
		}
		else {
			m_olColorButton->hide();
			m_olAlphaLabel->hide();
			m_olAlphaSlider->hide();
		}

		if (o->m_properties & OP_FONTSIZE) {
			// font size
			repositionY(m_fontSizeLabel, y);
			repositionY(m_fontSizeSlider, y);
			y += 25;
			y += 10;
		}
		else {
			m_fontSizeLabel->hide();
			m_fontSizeSlider->hide();
		}


		if (o->m_properties & OP_DRAWMODE) {
			repositionY(m_dmStippleButton, y);
			y += 25;
			repositionY(m_dmOriButton, y);
			y += 25;
			repositionY(m_dmWireframeButton, y);
			y += 25;
			repositionY(m_dmShadeButton, y);
			y += 25;
			repositionY(m_dmMagnitudeButton, y);
			y += 25;
			y += 10;
		}
		else {
			m_dmStippleButton->hide();
			m_dmOriButton->hide();
			m_dmWireframeButton->hide();
			m_dmShadeButton->hide();
			m_dmMagnitudeButton->hide();
		}

		if (o->m_properties & OP_DRAWMETHOD) {
			repositionY(m_drawMethodLabel, y);
			y += 25;
			repositionY(m_drawMethodMenu, y);
			y += 25;
			y += 10;
		}
		else {
			m_drawMethodLabel->hide();
			m_drawMethodMenu->hide();
		}

		if (o->m_properties & OP_DESCRIPTION) {
			repositionY(m_descriptionLabel, y);
			y += 25;
			repositionY(m_descriptionOutput, y);
			y += 100;
		}
		else {
			m_descriptionLabel->hide();
			m_descriptionOutput->hide();
		}
	}

	updateControls(0xFFFFFFFF);

	if (m_controlGroupVisible) {
		m_controlGroup->redraw(); // OK?
	}
	if ((!m_controlGroupVisible) || m_alwaysObjectDescriptionInStatusBar) { // set status bar to short description of object
		const int bufLen = 1024;
		char buf[bufLen];
		if (o) o->description(buf, bufLen-1, 1);
		else buf[0] = 0;
		setStatus(buf);
	}

	return 0;
}

int UIstate::updateControls(int properties) {
	object *o = m_currentObject;
	if (o == NULL) return 0;

	properties = properties & o->m_properties;

	if (properties & OP_NAME) {
		//static char *name = NULL;
		//name = (char*)realloc(name, o->m_name.length() + 1);
		//strcpy(name, o->m_name.c_str());
		m_nameOutput->value(o->m_name.c_str());
		m_nameOutput->redraw();
	}
		
	if (properties & OP_DRAWMODE) {
		m_hideButton->label((o->m_drawMode & OD_HIDE) ? "show this object" : "hide this object");
		m_hideButton->redraw();
	}

	if (properties & OP_FGCOLOR) {
		m_fgAlphaSlider->value(o->fgColor(3));
		m_fgAlphaSlider->redraw();
	}

	if (properties & OP_BGCOLOR) {
		m_bgAlphaSlider->value(o->bgColor(3));
		m_bgAlphaSlider->redraw();
	}

	if (properties & OP_OLCOLOR) {
		m_olAlphaSlider->value(o->olColor(3));
		m_olAlphaSlider->redraw();
	}

	if (properties & OP_FONTSIZE) {
		m_fontSizeSlider->value(o->m_fontSize);
		m_fontSizeSlider->redraw();
	}

	if (properties & OP_DRAWMODE) {
		m_dmStippleButton->value((o->m_drawMode & OD_STIPPLE) != 0);
		m_dmOriButton->value((o->m_drawMode & OD_ORI) != 0);
		m_dmWireframeButton->value((o->m_drawMode & OD_WIREFRAME) != 0);
		m_dmShadeButton->value((o->m_drawMode & OD_SHADE) != 0);
		m_dmMagnitudeButton->value((o->m_drawMode & OD_MAGNITUDE) != 0);
		m_dmStippleButton->redraw();
		m_dmOriButton->redraw();
		m_dmWireframeButton->redraw();
		m_dmShadeButton->redraw();
		m_dmMagnitudeButton->redraw();
	}

	if (properties & OP_DRAWMETHOD) {
		if (o->m_dmMenu)
			setDrawMethodMenu(o->m_dmMenu, o->m_dmMenuIdx);
	}

	if (properties & OP_DESCRIPTION) {
		static char descStr[1024];
		o->description(descStr, 1023);
		m_descriptionOutput->value(descStr);
		m_descriptionOutput->redraw();
	}

	return 0;
}


int UIstate::setStatus(const char *str) {
	/*static char *statusStr = NULL;
	statusStr = (char*)realloc(statusStr, (str) ? strlen(str) + 1 : 1);
	strcpy(statusStr, (str) ? str : "");*/
	m_statusOutput->value(str);

	return 0;
}

void ui_drawMethodMenuCallback(Fl_Widget *W, void *Data);

int UIstate::setDrawMethodMenu(Fl_Menu_Item *menu, int idx) {
	int d = 0, i = 0;

	while (d >= 0) {
		menu[i].callback_ = ui_drawMethodMenuCallback;
		if (menu[i].text == NULL) d--;
		else if (menu[i].flags & FL_SUBMENU) d++;
		i++;
	}

	if ((idx < 0) || (idx >= i)) return -1;

	m_drawMethodMenu->menu(menu);
	m_drawMethodMenu->label(menu[idx].text);

	return 0;
}

void ui_drawMethodMenuCallback(Fl_Widget *W, void *Data) {
	if (gui_state->m_currentObject == NULL) return;

	const Fl_Menu_Item* menu = ((Fl_Menu_Button*)W)->menu();
//	int item = (int)((unsigned char*)Data - (unsigned char*)NULL);
	int mi = 0, d = 1;

	while (d) {
		if (menu[mi].text == 0) d--;
		else if (menu[mi].flags & FL_SUBMENU) d++;
		if (menu[mi].user_data_ == Data) break;
		mi++;
	}

	gui_state->m_currentObject->m_dmMenuIdx = mi;
	gui_state->m_drawMethodMenu->label(menu[mi].text);
	gui_state->m_drawMethodMenu->redraw();
	gui_state->m_glWindow->redraw();
}

void UIstate::saveDiary(const char *filename) {
	if (filename == NULL)
		filename = fl_file_chooser("Save diary:", "text file (*.txt)\tXML (*.txt)", NULL);
	if (filename != NULL) {
		std::string diaryStr = m_console->diary();
		FILE *F = fopen(filename, "wb+");
		if (F == NULL) {
			fl_alert("Error: can not open '%s' for writing\n", filename);
			return;
		}
		int l = (int)diaryStr.length();
		if (fwrite(diaryStr.c_str(), 1, l, F) != l) {
			fl_alert("Error: can not write '%s'\n", filename);
			return;
		}
		fclose(F);

		cprintf("Saved diary to '%s'\n", filename);
		m_console->diary(); // clear diary again
	}
}
