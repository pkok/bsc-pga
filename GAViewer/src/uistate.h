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

#ifndef _UI_STATE_H_
#define _UI_STATE_H_

#ifdef WIN32
// disable some annoying warnings in VC++ due to FLTK (1.1.6)
#pragma warning( disable : 4311 4312 4244 )
#endif

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_message.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Color_Chooser.H>

#include <vector>
#include <utility>
#include <string>


#include "console/fl_console.h"
#include "tubedraw.h"

class glwindow;
class object;
class selectWindow;
class dynStmtWindow;
class screenShotDialog;
class mainWindow;
class consoleWindow;

#define MI_OPEN 1
#define MI_QUIT 2
#define MI_ABOUT 3
#define MI_HIDE_CONTROLS 4
#define MI_LABELSALWAYSONTOP 5
//#define MI_CLIPPINGPLANES 6
#define MI_UNHIDEALL 7
#define MI_LISTHIDDENOBJECTS 8
#define MI_SHOWHIDDENOBJECTS 9
#define MI_FULLSCREEN 11
#define MI_PRINT_ROTATION_BIVECTOR 12
#define MI_PRINT_ROTATION_ROTOR 13
#define MI_PRINT_TRANSLATION_VECTOR 14
#define MI_SLEEP_x4 15
#define MI_SLEEP_x2 16
#define MI_SLEEP_x1 17
#define MI_SLEEP_d2 18
#define MI_SLEEP_d4	19
#define MI_SPEED_d10 20
#define MI_SPEED_x0 21
#define MI_REPLAY 22
#define MI_BOOKMARK 23
#define MI_WHITE_CANVAS 24
#define MI_GREY_CANVAS 25
#define MI_BLACK_CANVAS 26
#define MI_HIDE_CONSOLE 27
#define MI_OPENPLAYLIST 28
#define MI_NEXTPLAYLIST 29
#define MI_PREVPLAYLIST 30
#define MI_SELECTOBJECTS 31
#define MI_SAVE_STATE 32
#define MI_LOAD_G_FILE 33
#define MI_LOAD_G_DIR 34
#define MI_DYNAMIC_STATEMENTS 35

#define MI_FONT_SIZE_MIN 36
#define MI_FONT_SIZE_12 MI_FONT_SIZE_MIN
#define MI_FONT_SIZE_16 37
#define MI_FONT_SIZE_20 38
#define MI_FONT_SIZE_24 39
#define MI_FONT_SIZE_MAX MI_FONT_SIZE_24

#define MI_START_ANIMATION 45
#define MI_STOP_ANIMATION 46
#define MI_PAUSE_ANIMATION 47

#define MI_HIDE_SCALAR_CONTROLS 48
#define MI_OPEN_ANY 49
#define MI_SCREENSHOT 50
#define MI_OBJECTDESCRIPTIONINSTATUSBAR 51

#define MI_LIGHT_GREY_CANVAS 52

#define MI_POINT_SIZE_MIN 53
#define MI_POINT_SIZE_01 MI_POINT_SIZE_MIN
#define MI_POINT_SIZE_05 54
#define MI_POINT_SIZE_1 55
#define MI_POINT_SIZE_5 56
#define MI_POINT_SIZE_MAX MI_POINT_SIZE_5

#define MI_GLLINES 60

#define MI_LINE_WIDTH_MIN 61
#define MI_LINE_WIDTH_1 MI_LINE_WIDTH_MIN
#define MI_LINE_WIDTH_2 62
#define MI_LINE_WIDTH_4 63
#define MI_LINE_WIDTH_8 64
#define MI_LINE_WIDTH_MAX MI_LINE_WIDTH_8

#define TIMER_FREQ 30

#define c_controlWidth 300
#define c_menuHeight 30
#define c_statusHeight 25
#define c_waitWidth 75

void ui_menuCallback(Fl_Widget *W, void *Data);

class UIstate {
public:
	UIstate(int argc, char *argv[]);
	~UIstate();
	void initToNothing();

	int timerCallback();
	void ui_controlCallback(Fl_Widget *W, void *Data);
	void ui_consoleCallback(Fl_Widget *W, void *Data);
	int toggleHideControls(int mi);
	int toggleHideScalarControls(int mi);
	int toggleHideConsole(int mi);
	int toggleFullscreen(int mi);

	std::string m_prevGeoFile;
	std::string m_prevGPLFile;
	std::string m_prevGFile;
	std::string m_prevAnyFile;

	inline void setPrevGeoFile(const std::string &f) {m_prevGeoFile = m_prevAnyFile = f;}
	inline void setPrevGPLFile(const std::string &f) {m_prevGPLFile = m_prevAnyFile = f;}
	inline void setPrevGFile(const std::string &f) {m_prevGFile = m_prevAnyFile = f;}

	const char *genericOpenFile(const std::string &dialogMsg, 
		std::vector<std::pair<const char *, const char *> >filterDesc, const std::string &defFileName);
	int openAnyFile(); // displays dialog, redirects to Open
	int openGeoFile(const char *filename = NULL);
	int openPlayList(const char *filename = NULL);
	int loadGFile(const char *filename = NULL);
	int loadGDir();

	int saveState();

	void saveDiary(const char *filename);


	mainWindow *m_mainWindow;
	Fl_Menu_Bar *m_menubar;

	//Fl_Tile *m_centerTile; // the tile that contains the glwindow and the console group
	glwindow *m_glWindow;

	// point size stuff
	void setPointSize(double size);
	void setPointSizeFromMenu(int menuItem); // size = MI_POINT_SIZE_XX
	double m_pointSize;

	// text scaling stuff
	void setTextScale(double scale);
	double m_textScale;

	// line width stuff
	void setLineWidth(double width);
	void setLineWidthFromMenu(int menuItem); // size = MI_LINE_WIDTH_XX
//	double m_lineWidth;
	
	// vector head stuff
	void setVectorHeadSize(double size);
	double m_vectorHeadSize;


	// console stuff
	int m_consoleVisible;
	consoleWindow *m_consoleGroup;
	Fl_Console *m_console;
	int setConsoleFontSize(int size);  // size = size in pixels
	int setConsoleFontSizeFromMenu(int menuItem); // size = MI_FONT_SIZE_XXX

	// control scalars stuff:
	int m_scalarGroupVisible;
	Fl_Window *m_scalarGroup;
	Fl_Scroll *m_scalarGroupScroll;

	// controll stuff
	int m_controlGroupVisible;
	Fl_Window *m_controlGroup;

	// control widgets
	// name 
	Fl_Output *m_nameLabel;
	Fl_Output *m_nameOutput;
	Fl_Button *m_removeButton, *m_hideButton;
	Fl_Button *m_fgColorButton;
	Fl_Output *m_fgAlphaLabel;
	Fl_Value_Slider *m_fgAlphaSlider;
	Fl_Button *m_bgColorButton;
	Fl_Output *m_bgAlphaLabel;
	Fl_Value_Slider *m_bgAlphaSlider;
	Fl_Button *m_olColorButton;
	Fl_Output *m_olAlphaLabel;
	Fl_Value_Slider *m_olAlphaSlider;
	Fl_Output *m_fontSizeLabel;
	Fl_Value_Slider *m_fontSizeSlider;
	Fl_Output *m_descriptionLabel;
	Fl_Multiline_Output *m_descriptionOutput;
	Fl_Output *m_drawMethodLabel;
	Fl_Menu_Button *m_drawMethodMenu;

	Fl_Check_Button *m_dmStippleButton;
	Fl_Check_Button *m_dmOriButton;
	Fl_Check_Button *m_dmWireframeButton;
	Fl_Check_Button *m_dmShadeButton;
	Fl_Check_Button *m_dmMagnitudeButton;

	// fullscreen stuff
	int mouseMove();
	double m_fsLastMouseActionTime;
	int m_fullscreen;
	int m_cursor;


	// draw method menu
	int setDrawMethodMenu(Fl_Menu_Item *menu, int idx);

	inline void setInteractiveMouse(bool val) {
		m_interactiveMouse = val;
	}

	// status bar widgets
	bool m_alwaysObjectDescriptionInStatusBar;
	Fl_Output *m_statusOutput;
	Fl_Button *m_waitButton;
	int setStatus(const char *str);

	int updateControls(int properties);
	int setCurrentObject(object *o);
	int setCurrentObjectByName(const std::string &name);
	object *m_currentObject;

	int createSelectWindow(int mode); // mode = SWM_XXX
	selectWindow *m_selectWindow;

	int createDynStmtWindow();
	dynStmtWindow *m_dynStmtWindow;

	// screenshot:
	int createScreenshotDialog();
	screenShotDialog *m_screenShotDialog;
	int setupScreenshot(const std::string &filename, int width, int height, bool alsoWithoutLabels);
	int m_screenShotOnNextRedraw;
	std::string m_ssFilename;
	int m_ssWidth, m_ssHeight;
	bool m_ssAlsoNoLabels;

	// tube draw:
	TubeDraw m_tubeDraw;

	// enable mouse interaction
	bool m_interactiveMouse;


};

extern UIstate *gui_state;
extern Fl_Menu_Item gui_menuTable[];

#endif /* _UI_STATE_H_ */

