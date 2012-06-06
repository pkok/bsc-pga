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

#ifndef _CONSOLE_CONTROL_H_
#define _CONSOLE_CONTROL_H_

#include <string>
class Fl_Button;
class Fl_Widget;
class Fl_Check_Button;
class Fl_Value_Slider;
class Fl_Menu_Button;
class Fl_Output;

class consoleControl {
public:
	consoleControl(const std::string &nm, const std::string &callbackFunctionName);
	virtual ~consoleControl();

	void name(const std::string &nm);
	inline const char *name() const {return m_name;} // returned name can be used directly for FLTK widget

	void callbackFuncName(const std::string &callbackFunctionName);
	inline const std::string &callbackFuncName() const {return m_callbackFuncName;} 

	void callback(Fl_Widget *W);
	inline int updateRequired() const {return m_updateRequired;}
	inline void updateRequired(int u) {m_updateRequired = u;}
	int writeToGeoFileMemFun(FILE *F) ; // non-virtual function for use with mem_fun (calls writeToGeoFile())

//	int testFunc(int a);

	virtual int setWidgetWY(int w, int y); // sets the width and the 'y' location of the widget in it's parent group (must be called by subclasses)
	virtual int widgetHeight() const; // returns the height of the FLTK widget(s) (may be called by subclasses)
	virtual int writeToGeoFile(FILE *F)  = 0; // writes GAFile command(s) for storing this control
	virtual void widgetModified(Fl_Widget *W) = 0; // called when user has changed the value of the widget
	virtual void consoleVariableModified() = 0; // called when user has changed the value of the global console variable 'm_name'

protected:
	int createRemoveButton();
	inline void selfModify(int m) {m_selfModify = m;}
	GAIM_FLOAT lookupValue() const;
	int lookupValueBool() const;

	/// calls m_callbackFuncName in global scope, no arguments.
	void execCallbackFunc();

private:
	char *m_name; // as a char * so we can feed it to  FLTK
	std::string m_callbackFuncName; // called when value of callback changes
	int m_selfModify; // set to true by when 'this' is modifying itself, so widget callbacks (though callback()) don't have any effect
	int m_updateRequired; // set to true when widget(s) should be updated by calling consoleVariableModified()
	Fl_Button *m_removeButton;
	void initToNothing();
};

inline bool operator==(const consoleControl *cc, const std::string &name) {
	return name == std::string(cc->name());
}

class consoleControlBool : public consoleControl {
public:
	consoleControlBool(const std::string &name, int value, const std::string &callbackFunctionName);
	virtual ~consoleControlBool();

	virtual int setWidgetWY(int w, int y);
	virtual int widgetHeight() const ; 
	virtual int writeToGeoFile(FILE *F)  ;
	virtual void widgetModified(Fl_Widget *W);
	virtual void consoleVariableModified(); 

protected:
	Fl_Check_Button *m_checkButton;

private:
	void initToNothing();
};

class consoleControlRange : public consoleControl {
public:
	consoleControlRange(const std::string &name, GAIM_FLOAT minValue, GAIM_FLOAT maxValue, GAIM_FLOAT value, GAIM_FLOAT step, const std::string &callbackFunctionName);
	virtual ~consoleControlRange();

	virtual int setWidgetWY(int w, int y);
	virtual int widgetHeight() const ; 
	virtual int writeToGeoFile(FILE *F) ;
	virtual void widgetModified(Fl_Widget *W);
	virtual void consoleVariableModified(); 

protected:
	Fl_Value_Slider *m_valueSlider;

private:
	void initToNothing();
};

class consoleControlSelection : public consoleControl {
public:
	consoleControlSelection(const std::string &name,  GAIM_FLOAT value, const std::vector<std::pair<std::string, GAIM_FLOAT > > &options, const std::string &callbackFunctionName);
	virtual ~consoleControlSelection();

	virtual int setWidgetWY(int w, int y);
	virtual int widgetHeight() const ; 
	virtual int writeToGeoFile(FILE *F) ;
	virtual void widgetModified(Fl_Widget *W);
	virtual void consoleVariableModified(); 

protected:
	Fl_Menu_Button *m_menuButton;
	Fl_Menu_Item *m_menuItems;
	GAIM_FLOAT *m_menuValues;
	Fl_Widget *m_label;
	char *m_labelText;

private:
	void initToNothing();
};




#endif /* _CONSOLE_CONTROL_H_ */
