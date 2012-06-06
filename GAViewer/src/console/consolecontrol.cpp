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

#include <stdlib.h>

#include <vector>
#include <utility>
#include <algorithm>

#include "../state.h"
#include "../uistate.h"
#include "consolecontrol.h"
#include "consolescope.h"
#include "consolevariable.h"

#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Output.H>

int state::addConsoleControl(consoleControl *cc) {
	removeConsoleControl(cc->name());
	m_consoleControls.push_back(cc);
	resizeConsoleControls();
	return 0;
}

int state::addConsoleControlBool(const std::string &name, int value) {
	std::string callbackFunctionName = "";
	return addConsoleControlBool(name, value, callbackFunctionName);
}

int state::addConsoleControlRange(const std::string &name, GAIM_FLOAT value, GAIM_FLOAT minValue, GAIM_FLOAT maxValue, GAIM_FLOAT step) {
	std::string callbackFunctionName = "";
	return addConsoleControlRange(name, value, minValue, maxValue, step, callbackFunctionName);
}

int state::addConsoleControlSelection(const std::string &name, GAIM_FLOAT value, const std::vector<std::pair<std::string, GAIM_FLOAT > > &options) {
	std::string callbackFunctionName = "";
	return addConsoleControlSelection(name, value, options, callbackFunctionName);
}

int state::addConsoleControlBool(const std::string &name, int value, const std::string &callbackFunctionName) {
	return addConsoleControl(new consoleControlBool(name, value, callbackFunctionName));
}

int state::addConsoleControlRange(const std::string &name, GAIM_FLOAT value, GAIM_FLOAT minValue, GAIM_FLOAT maxValue, GAIM_FLOAT step, const std::string &callbackFunctionName) {
	return addConsoleControl(new consoleControlRange(name, value, minValue, maxValue, step, callbackFunctionName));
}

int state::addConsoleControlSelection(const std::string &name, GAIM_FLOAT value, const std::vector<std::pair<std::string, GAIM_FLOAT > > &options, const std::string &callbackFunctionName) {
	return addConsoleControl(new consoleControlSelection(name, value, options, callbackFunctionName));
}

int state::removeConsoleControl(const std::string &name) {
	std::vector<consoleControl*>::iterator I = 
		std::find(m_consoleControls.begin(), m_consoleControls.end(), name);

	if (I != m_consoleControls.end()) {
		delete (*I);
		m_consoleControls.erase(I);
	}

	resizeConsoleControls();

	return 0;
}

int state::removeAllConsoleControls() {
	std::vector<consoleControl*>::iterator I;
	for (I = m_consoleControls.begin(); I != m_consoleControls.end(); I++) {
		delete (*I); 
	}
	m_consoleControls.clear();

	if (gui_state) 
		gui_state->m_scalarGroup->redraw();
	
	return 0;
}

int state::resizeConsoleControls() {
	if (!gui_state) return 0;

	int y = 5;
	int w = gui_state->m_scalarGroup->w() - 25; // -25 to make room for scrollbar

	std::vector<consoleControl*>::iterator I;

	for (I = m_consoleControls.begin(); I != m_consoleControls.end(); I++) {
		(*I)->setWidgetWY(w, y);
		y += (*I)->widgetHeight() + 5;
	}

	gui_state->m_scalarGroup->redraw();


	return 0;
}


inline void consoleControlUpdateFunc(consoleControl *cc) {
	if (cc->updateRequired()) cc->consoleVariableModified();
}

int state::updateConsoleControls() {
	std::for_each(m_consoleControls.begin(), m_consoleControls.end(), consoleControlUpdateFunc);
	return 0;
}

/******************************* consoleControlCallback ******************************/

void consoleControlCallback(Fl_Widget *W, void *Data) {
	const char *name = (const char*)Data;
	std::vector<consoleControl*>::iterator I = 
		std::find(g_state->m_consoleControls.begin(), g_state->m_consoleControls.end(), std::string(name));

	if (I != g_state->m_consoleControls.end())
		(*I)->callback(W);
}

/******************************* consoleControl ******************************/

consoleControl::consoleControl(const std::string &nm, const std::string &callbackFunctionName) {
	initToNothing();

	name(nm);
	callbackFuncName(callbackFunctionName);
}

consoleControl::~consoleControl() {
	if (m_name) free(m_name);
	if (m_removeButton) {
//		if (gui_state) gui_state->m_scalarGroup->remove(m_removeButton);
		if (gui_state) gui_state->m_scalarGroupScroll->remove(m_removeButton);
		delete m_removeButton;
	}

	initToNothing();
}

void consoleControl::initToNothing() {
	m_name = NULL;
	m_removeButton = NULL;
	
	m_selfModify = m_updateRequired = 0;
}


void consoleControl::name(const std::string &nm) {
	if (m_name) free(m_name);
	m_name = strdup(nm.c_str());
}

void consoleControl::callbackFuncName(const std::string &callbackFunctionName) {
	m_callbackFuncName = callbackFunctionName;
}

int consoleControl::createRemoveButton() {
	const int width = 70;
	m_removeButton = new Fl_Button(5, 2, width-10, 20, "remove");
	m_removeButton->callback(consoleControlCallback, (void*)name());
	return width;
}

int consoleControl::setWidgetWY(int w, int y) {
	if (m_removeButton) {
		m_removeButton->position(m_removeButton->x(), y+2);
	}
	return 0;
}

int consoleControl::widgetHeight() const {
	return (m_removeButton) ? m_removeButton->h() : 0;
}

void consoleControl::callback(Fl_Widget *W) {
	if (m_selfModify) return;
	if (W == m_removeButton) {
		g_state->removeConsoleControl(std::string(name()));
		return; // must return _now_ for 'this' has been destroyed by the previous call!
	}
	else {
		widgetModified(W);

//		printf("consoleControl::callback() %s\n", m_name);


		// execute the callback
		execCallbackFunc();
	}
}

void consoleControl::execCallbackFunc() {
	if (callbackFuncName().length() > 0) {
//		printf("Doing the callback to %s\n", callbackFuncName().c_str());
		consoleVariable *cv = consoleExecFunc(g_state->m_globalScope, callbackFuncName(), NULL);
		if (cv) delete cv;
	}
}

GAIM_FLOAT consoleControl::lookupValue() const{
	GAIM_FLOAT value = 0.0;
	consoleVariable *cv;
	if (g_state && (g_state->m_globalScope->lookupVariable(name(), 1, &cv) == 0)) {
		value = cv->scalar();
		delete cv;
	}
	return value;
}

int consoleControl::lookupValueBool() const{
	int bl = 0;
	consoleVariable *cv;
	if (g_state && (g_state->m_globalScope->lookupVariable(name(), 1, &cv) == 0)) {
		bl = cv->isTrue();
		delete cv;
	}
	return bl;
}




/******************************* consoleControlBool ******************************/

consoleControlBool::consoleControlBool(const std::string &nm, int val, const std::string &callbackFunctionName) : consoleControl(nm, callbackFunctionName) {
	initToNothing();

//	if (gui_state) gui_state->m_scalarGroup->begin();
	if (gui_state) gui_state->m_scalarGroupScroll->begin();

	int x = createRemoveButton();

	m_checkButton = new Fl_Check_Button(x, 0, 1, 25, name());
	m_checkButton->value(val);
	m_checkButton->callback(consoleControlCallback, (void*)name());
	m_checkButton->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);

	if (gui_state) gui_state->m_scalarGroup->end();

	widgetModified(m_checkButton); // make sure the value is assigned
}

consoleControlBool::~consoleControlBool() {
	if (m_checkButton) {
//		if (gui_state) gui_state->m_scalarGroup->remove(m_checkButton);
		if (gui_state) gui_state->m_scalarGroupScroll->remove(m_checkButton);

		delete m_checkButton;
	}

	initToNothing();
}

int consoleControlBool::setWidgetWY(int pw, int py) {
	consoleControl::setWidgetWY(pw, py);
	if (m_checkButton) {
		m_checkButton->size(pw - m_checkButton->x() - 5, m_checkButton->h());
		m_checkButton->position(m_checkButton->x(), py);
	}
	return 0;
}

int consoleControlBool::widgetHeight() const {
	int ph = consoleControl::widgetHeight();
	return (ph < m_checkButton->h()) ? m_checkButton->h() : ph;
}


void consoleControlBool::widgetModified(Fl_Widget *W) {
	if (g_state) {
		GAIM_FLOAT val = (GAIM_FLOAT)m_checkButton->value();
		g_state->m_globalScope->externalAssignVariable(name(), e3ga(val));
		g_state->updateDynStmts();
	}
}

void consoleControlBool::consoleVariableModified() {
	int newValue = lookupValueBool();
	if (newValue != m_checkButton->value()) {
		selfModify(1);
		m_checkButton->value(newValue);
		selfModify(0);
		execCallbackFunc();
	}
}

void consoleControlBool::initToNothing() {
	m_checkButton = NULL;
}

/******************************* consoleControlRange ******************************/

consoleControlRange::consoleControlRange(const std::string &nm, 
										 GAIM_FLOAT value, 
										 GAIM_FLOAT minValue, 
										 GAIM_FLOAT maxValue, 
										 GAIM_FLOAT step, 
										 const std::string &callbackFunctionName)  : consoleControl(nm, callbackFunctionName) {
	initToNothing();

	if (minValue > maxValue) {
		GAIM_FLOAT tmp = minValue;
		minValue = maxValue;
		maxValue = tmp;
	}
	if (step < 0) {
		step = (maxValue - minValue) / 200;
	}

//	if (gui_state) gui_state->m_scalarGroup->begin();
	if (gui_state) gui_state->m_scalarGroupScroll->begin();

	int x = createRemoveButton();

	m_valueSlider = new Fl_Value_Slider(x, 0, 1, 25, name());
	m_valueSlider->value(value);
	m_valueSlider->range(minValue, maxValue);
	m_valueSlider->step(step);
	m_valueSlider->callback(consoleControlCallback, (void*)name());
	m_valueSlider->when(FL_WHEN_CHANGED | FL_WHEN_RELEASE);
	m_valueSlider->type(FL_HORIZONTAL);

	if (gui_state) gui_state->m_scalarGroup->end();

	widgetModified(m_valueSlider); // make sure the value is assigned
}

consoleControlRange::~consoleControlRange() {
	if (m_valueSlider) {
//		if (gui_state) gui_state->m_scalarGroup->remove(m_valueSlider);
		if (gui_state) gui_state->m_scalarGroupScroll->remove(m_valueSlider);
		delete m_valueSlider;
	}

	initToNothing();
}

int consoleControlRange::setWidgetWY(int pw, int py) {
	consoleControl::setWidgetWY(pw, py);
	if (m_valueSlider) {
		m_valueSlider->size(pw - m_valueSlider->x() - 5, m_valueSlider->h());
		m_valueSlider->position(m_valueSlider->x(), py);
	}
	return 0;
}

int consoleControlRange::widgetHeight() const {
	int ph = consoleControl::widgetHeight();
	int wh = m_valueSlider->h() + 20;
	return (ph < wh) ? wh : ph;
}



void consoleControlRange::widgetModified(Fl_Widget *W) {
	if (g_state) {
		GAIM_FLOAT val = (GAIM_FLOAT)m_valueSlider->value();
		g_state->m_globalScope->externalAssignVariable(name(), e3ga(val));
//		g_state->m_globalScope->assignVariable(new consoleVariable(name(), e3ga(0.0)), new consoleVariable("", e3ga(val)));
		g_state->updateDynStmts();
	}
}

void consoleControlRange::consoleVariableModified() {
//	printf("consoleControlRange::consoleVariableModified() %s\n", name());
	double newValue = lookupValue();
	if (newValue != m_valueSlider->value()) {
		selfModify(1);
		m_valueSlider->value(newValue);
		selfModify(0);
		execCallbackFunc();
	}
}

void consoleControlRange::initToNothing() {
	m_valueSlider = NULL;
}

/******************************* consoleControlRange ******************************/

// ctrl_select(s = 1, a = 2, b = 1);

consoleControlSelection::consoleControlSelection(const std::string &nm, GAIM_FLOAT value, 
												 const std::vector<std::pair<std::string, GAIM_FLOAT > > &options, 
												 const std::string &callbackFunctionName)
												 : consoleControl(nm, callbackFunctionName) {
	int i,x, v;
	initToNothing();

//	if (gui_state) gui_state->m_scalarGroup->begin();
	if (gui_state) gui_state->m_scalarGroupScroll->begin();

	x = createRemoveButton();

	m_labelText = strdup((std::string(name()) + ": ").c_str());
	m_label = new Fl_Button(x, 0, 40, 20, m_labelText);
	m_label->deactivate();
	m_label->align(FL_ALIGN_CENTER);
	m_label->color(FL_GRAY);
	m_label->box(FL_FLAT_BOX);

	x += 55;

	m_menuButton = new Fl_Menu_Button(x, 0, 1, 20, name());

	m_menuItems = new Fl_Menu_Item[options.size() + 1];
	m_menuValues = new GAIM_FLOAT[options.size() + 1];
	memset(m_menuItems, 0, (options.size() + 1) * sizeof(Fl_Menu_Item));
	v = 0;
	for (i = 0; i < (int)options.size(); i++) {
		m_menuValues[i] = options[i].second;
		if (value == m_menuValues[i]) v = i;

		m_menuItems[i].text = strdup(options[i].first.c_str());
		m_menuItems[i].callback_ = consoleControlCallback;
		m_menuItems[i].user_data_ = (void*)name();
	}

	m_menuButton->menu(m_menuItems);
	m_menuButton->value(v);

	if (gui_state) gui_state->m_scalarGroup->end();

	widgetModified(m_menuButton); // make sure the value is assigned

}

consoleControlSelection::~consoleControlSelection() {
	if (m_menuButton) {
//		if (gui_state) gui_state->m_scalarGroup->remove(m_menuButton);
		if (gui_state) gui_state->m_scalarGroupScroll->remove(m_menuButton);
		delete m_menuButton;
	}

	if (m_menuItems) {
		int i = 0;
		while (m_menuItems[i].text) {
			free((char*)m_menuItems[i].text);
			i++;
		}
		delete[] m_menuItems;
	}
	if (m_menuValues)  {
		delete[] m_menuValues;
	}

	if (m_label)  {
//		if (gui_state) gui_state->m_scalarGroup->remove(m_label);
		if (gui_state) gui_state->m_scalarGroupScroll->remove(m_label);
		delete m_label;
	}
	if (m_labelText) free(m_labelText);


	initToNothing();

}

int consoleControlSelection::setWidgetWY(int pw, int py) {
	consoleControl::setWidgetWY(pw, py);
	if (m_menuButton) {
		((Fl_Widget*)m_menuButton)->size(pw - m_menuButton->x() - 5, m_menuButton->h());
		m_menuButton->position(m_menuButton->x(), py);
	}
	if (m_label) {
		m_label->position(m_label->x(), py);
	}

	return 0;
}

int consoleControlSelection::widgetHeight() const {
	int ph = consoleControl::widgetHeight();
	int wh = m_menuButton->h();
	return (ph < wh) ? wh : ph;
}

// ctrl_select(a = 1, option1 = 1, option2 = 3, option3 = 3);


void consoleControlSelection::widgetModified(Fl_Widget *W) {
	if (g_state) {
		int idx = (int)m_menuButton->value();
		m_menuButton->label(m_menuItems[idx].text); 
		g_state->m_globalScope->externalAssignVariable(name(), e3ga(m_menuValues[idx]));
		//g_state->m_globalScope->assignVariable(new consoleVariable(name(), e3ga(0.0)), new consoleVariable("", e3ga(m_menuValues[idx])));
		g_state->updateDynStmts();
	}
}

void consoleControlSelection::consoleVariableModified() {

	//printf("consoleControlSelection::consoleVariableModified() %s\n", name());

	GAIM_FLOAT val = lookupValue();
	int newValue = 0;
	int i = 0;
	while (m_menuItems[i].text) {
		if (m_menuValues[i] == val) newValue = i;
		i++;
	}
	//printf("Old value: %d, new value: %d\n", );

	if (m_menuButton->value() != newValue) {
		selfModify(1);
		m_menuButton->value(newValue);
		m_menuButton->label(m_menuItems[newValue].text); 
		selfModify(0);
		execCallbackFunc();
	}

}

void consoleControlSelection::initToNothing() {
	m_menuButton = NULL;
	m_menuItems = NULL;
	m_menuValues = NULL;
	m_label = NULL;
	m_labelText = NULL;

}


