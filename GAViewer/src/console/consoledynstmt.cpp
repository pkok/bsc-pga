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
#include <string.h>


#include "../osdep.h"
#include "../state.h"
#include "../uistate.h"
#include "../glwindow.h"
#include "consolescope.h"
#include "consolestatement.h"
#include "console.h"
#include "consolevariable.h"
#include "consolecontrol.h"

#include <iostream>
#include <vector>
#include <algorithm>

state::dynStmtInfo::dynStmtInfo(consoleStmtListStmt *dynStmt, const std::string &workingDirectory, const std::string &name) : m_dynStmt(dynStmt) {
	m_name = name;
	m_workingDirectory = workingDirectory;
}
state::dynStmtInfo::dynStmtInfo(const dynStmtInfo &dsi) {
	set(dsi);
}


state::dynStmtInfo::~dynStmtInfo() {
//	delete m_dynStmt;
}

void state::dynStmtInfo::ds(consoleStmtListStmt *stmt) {
//	if (m_dynStmt) delete m_dynStmt;
	m_dynStmt.reset(stmt);
}

void state::dynStmtInfo::set(const dynStmtInfo &dsi) {
	m_dynStmt.reset((consoleStmtListStmt *)dsi.ds()->copy());
	m_name = dsi.name();
	m_workingDirectory = dsi.wd();
//	printf("Copy %08X to %08X\n", &dsi, this);
}


int state::modified(const std::string &pname) {
	// prepare message to send to network client
	{
		m_netVarChanges.insert(pname);
		/**/

	}


	// strip name of array indices
	std::string name(pname);
	std::string::size_type idx = name.find('[');
	if (idx != std::string::npos)
		name.erase(idx);

	// check all dynamic statements: do they use variable 'pname'?
	for (DSI I = m_dynStmt.begin(); I != m_dynStmt.end(); I++) {
		if (I->ds()->dependsOn(name)) {
			//printf("%08X depends on %s, eval required\n", I->ds(), name.c_str());
			I->ds()->evalRequired(1);
		}
	}

	// check all control variables: do they control 'pname'?
	std::vector<consoleControl*>::iterator J = 
		std::find(m_consoleControls.begin(), m_consoleControls.end(), name);
	if (J != m_consoleControls.end()) {
		(*J)->updateRequired(1);
	}

	return 0;
}
// dynamic{my_animation(atime),}
int state::newDynStmt(consoleStmtListStmt *stmt) {
	stmt->evalRequired(1);
	stmt->firstEval(1);

	return 0;
}

int state::addDynStmt(consoleStmtListStmt *stmt,  
					  const std::string &workingDirectory, const std::string &name) {
	if (stmt == NULL) return 0;

	newDynStmt(stmt);

	// delete old dynamic statement that go by 'name'
	if (name.size()) removeDynStmt(name);

	m_dynStmt.push_back(dynStmtInfo(stmt, workingDirectory, name));


	return 0;
}

int state::removeDynStmt(int idx) {

	if ((idx < 0) || (idx >= (int)m_dynStmt.size())) {
		cprintf("state::removeDynStmt(): invalid index %d\n", idx);
		return -1;
	}

	m_dynStmt.erase(m_dynStmt.begin() + idx);

	return 0;
}

int state::removeDynStmt(const std::string &name) {

	for (DSI I = m_dynStmt.begin(); I != m_dynStmt.end(); I++) {
		if (I->name() == name) {
			removeDynStmt(I - m_dynStmt.begin());
			removeDynStmt(name); // just start over 
			return 0;
		}
	}
	return 0;
}

int state::removeDynStmt(consoleStmtListStmt *stmt) {

	for (DSI I = m_dynStmt.begin(); I != m_dynStmt.end(); I++) {
		if (I->ds() == stmt) {
			m_dynStmt.erase(I);
			return 0;
		}
	}

	return 0;
}


int state::removeAllDynStmt() {
	m_dynStmt.clear();
	return 0;
}

int state::replaceDynStmt(consoleStmtListStmt *oldStmt, consoleStmtListStmt *newStmt) {
	for (DSI I = m_dynStmt.begin(); I != m_dynStmt.end(); I++) {
		if (I->ds() == oldStmt) {
			// success:
			I->ds(newStmt);
			newDynStmt(newStmt);
			return 0;
		}
	}
	// failure:
	delete newStmt;
	return -1;
}


int state::updateDynStmts() {
	static int running = 0;
	if (running) return 0; // prevent reentrance (single theaded)
	running = 1;

	// little hack: call updateConsoleControls() too
	updateConsoleControls();


	int i, e;
	std::vector<int> evalDone(m_dynStmt.size(), 0);

	int sw = m_globalScope->supressWarnings();
	int se = m_globalScope->supressErrors();

//	printf("Update dynamics!\n");
	// evaluate each dynamic state once, only once, but do check if other dynamics, earlier in list, have to be reevaled
	do {
		e = 0;
		for (i = 0; i < (int)m_dynStmt.size(); i++) {
			
			if ((!evalDone[i]) && m_dynStmt[i].ds()->evalRequired()) {
//				printf("update %08X %d (%s)\n", m_dynStmt[i].ds(), m_dynStmt[i].ds()->evalRequired(), m_dynStmt[i].name().c_str());

				e = 1;
				evalDone[i] = 1;

				m_globalScope->supressWarnings(1);
				m_globalScope->supressErrors(1);
/*				
				// if this is not the first evalutation, suppress warning messages
				m_globalScope->supressWarnings((m_dynStmt[i].ds()->firstEval()) ? sw : 1);
				m_globalScope->supressErrors((m_dynStmt[i].ds()->firstEval()) ? se : 1);*/
		
				m_globalScope->dynStmtVariableCollect(1);

				//m_globalScope->noAssignmentDisplay(1);
				m_globalScope->noAssignmentDisplay(!m_dynStmt[i].ds()->firstEval()); // on first eval _do_ do a [display|hide]ConsoleAssignmentList in consoleGlobalScope::endStatement()

				consoleVariable *cv = m_dynStmt[i].ds()->execute(m_globalScope);
				if (cv) delete cv;

				if (m_globalScope->resetRequested()) {
					g_state->reset();
					running = 0; // allow reentrance
					return 0;
				}

				// transfer the variable names on which m_dynStmt[i] depends
				std::set<std::string> *dynStmtVariables = m_globalScope->getDynStmtVariables();
				/*if (dynStmtVariables)
					for (std::set<std::string>::iterator X = dynStmtVariables->begin(); X != dynStmtVariables->end(); X++)
						std::cout << (*X) << std::endl;*/

				m_dynStmt[i].ds()->setDynStmtVariables(dynStmtVariables/*m_globalScope->getDynStmtVariables()*/);
				
				m_dynStmt[i].ds()->firstEval(0); // first eval done
				m_dynStmt[i].ds()->evalRequired(0); // no re-eval required anymore
				evalDone[i] = 1; // keep track of which dyn stmts have been evalled this round
			}
		}
	} while (e);

	// force all dynamic statements to 'no eval required'
	for (i = 0; i < (int)m_dynStmt.size(); i++) {
		m_dynStmt[i].ds()->evalRequired(0);
	}


	m_globalScope->supressWarnings(sw);
	m_globalScope->supressErrors(se);
	m_globalScope->noAssignmentDisplay(0);
	m_globalScope->dynStmtVariableCollect(0);

	if(gui_state && gui_state->m_glWindow) gui_state->m_glWindow->redraw();

	running = 0; // allow reentrance

	//printf("DONE!\n");

	return 0;
}


