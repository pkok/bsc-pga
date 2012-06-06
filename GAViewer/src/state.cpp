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
#ifndef WIN32
#include <stdarg.h>
#endif

#include <iostream>
#include <vector>
#include <algorithm>


#include "state.h"
#include "uistate.h"
#include "gafile.h"
#include "console/console.h"
#include "console/consolegafile.h"
#include "console/consolescope.h"
#include "console/consolevariable.h"

#include "object.h"
#include "osdep.h"
#include "glwindow.h"
#include "geosphere.h"
#include "mainwindow.h"
#include "util.h"


#include "typeset/typeset.h"

state *g_state = NULL;

state::state() {
	g_state = this;

	initToNothing();

	char buf[1024];
	u_dirGetCwd(buf, 1023);
	m_initialWorkingDirectory = buf;

	m_playListParse = 0;

	m_playbackSpeed = 1.0;

	setColor("fgcolor", "r");
	setColor("bgcolor", (float)0.7, (float)0.7, (float)0.7);
	setColor("olcolor", 0.0, 0.0, 0.0);
	setColor("cvcolor", 0.5f, 0.5f, 0.5f);
	m_fontSize = 20.0;
	m_clipDistance = 5.0;

	m_ambient = (float)0.2;
	m_diffuse = (float)0.8;

	m_labelsAlwaysOnTop = 1;

	gsCompute(&g_pointSphere, 2);
	gsCompute(&g_sphereSphere, 3);

	tsReset();

	m_deleteFileQuestion = strdup("Delete %s?");

	m_tsMode = "verbatim";
	m_tsFont = "regular";
	//m_tsMode = "text";

	m_consoleGAfile = new consoleGAfile(this);

	newGlobalScope();

	m_nbNetServers = -1; // value -1 signals pollNetServers() to create init server!
	m_defaultNetPort = "6860";
	m_displayNetworkCommands = true;
/*	// temp test...
	addConsoleControlBool("blah", 1.0);
	removeConsoleControl("blah");*/
}

state::~state() {
	if (m_consoleGAfile) delete m_consoleGAfile;

	deleteGAfileStack();

	if (m_deleteFileQuestion) free(m_deleteFileQuestion);
	if (m_openFilename) free(m_openFilename);

	removeAllObjects();

	delete m_globalScope;

	gsFree(&g_pointSphere);
	gsFree(&g_sphereSphere);

	if (m_typesetState) delete m_typesetState;

	clearPlayList();
	freeOpenFile();

	removeAllDynStmt();
	removeAllConsoleControls();

	closeNetServers();

	initToNothing();
}

void state::initToNothing() {
	m_consoleGAfile = NULL;

	m_GAfileStackDepth = -1;
	m_GAfileStack = NULL;

	m_inputSleepTime = -1;
	m_playbackSpeed = -1.0;
	m_inputWaitTime = -1.0;

/*	m_nbObjects = 0;
	m_object = NULL;*/

	setColor("fgcolor", 0.0, 0.0, 0.0, 0.0);
	setColor("bgcolor", 0.0, 0.0, 0.0, 0.0);
	setColor("olcolor", 0.0, 0.0, 0.0, 0.0);
	setColor("cvcolor", 0.0, 0.0, 0.0, 0.0);
	m_fontSize = 0.0;
	m_clipDistance = -1.0;
	m_ambient = m_diffuse = -1.0;
//	m_clippingPlanesEnabled = 0;
	m_poFactor = m_poUnits = 0.0;

	m_trlTime = m_trlEndTime = m_rotTime = m_rotEndTime = -1.0;
	m_trl = m_rot = 0;
	m_inputWait = 0;
	m_bookmarkSearch = 0;
	m_preBookmarkSearchPlaybackSpeed = 0.0;

	m_e3gaFactor[0] = m_e3gaFactor[1] = m_e3gaFactor[2] = 0.0;
	m_p3gaFactor[0] = m_p3gaFactor[1] = m_p3gaFactor[2] = m_p3gaFactor[3] = 0.0;
	m_c3gaFactor[0] = m_c3gaFactor[1] = m_c3gaFactor[2] = m_c3gaFactor[3] = m_c3gaFactor[4] = 0.0;

	m_deleteFileQuestion = NULL;
	m_openFilename = NULL;
	m_openFileLevel = 0;
	m_openFileNbArg = 0;
	m_openFileArg = NULL;

	m_typesetState = NULL;
	m_tsMode = NULL;
	m_tsFont = NULL;

	m_playListLength = m_playListPos = -1;
	m_playList = NULL;
	m_playListParse = 0;

	m_globalScope = NULL;

	m_animationMode = AM_STOPPED;
	m_lastAnimationUpdate = -1.0;

	m_netServers = NULL;
	m_nbNetServers = 0;
}

// really really really resets the entire state (right? ;)
void state::reset(const char *filename /* = NULL */) {
	removeAllDynStmt();
	stopAnimation();
	removeAllObjects();
	deleteGAfileStack(filename);
	resetGAfileState();

	if (gui_state && (gui_state->m_console))
		gui_state->m_console->clear();

	m_displayNetworkCommands = true;

	newGlobalScope();
}

void state::setWorkingDirectory(const std::string &pdir, bool removeTrailingFilename /*= false*/) {
	std::string dir(pdir);
	if (removeTrailingFilename) {
		std::string::size_type slashPos = dir.find_last_of(std::string("/\\"));
		if (slashPos != std::string::npos)
			dir.erase(slashPos);
	}

	m_workingDirectory = dir;

//	std::cout << "Working directory: " << m_workingDirectory << std::endl;
}

std::string state::fullFilename(const std::string &filename) {
	std::string fullname;

	// check if filename is absolute
#ifdef WIN32
	if (((filename[0] == '\\') && (filename[1] == '\\')) ||
		(filename[1] == ':')) {
#else // assume UNIX
	if ((filename[0] == '/') || (filename[0] == '~')) {
#endif
		return filename;
	}
	else return m_workingDirectory + "/" + filename;
	
}

void state::setDefaultGlobalScopeVariables() {
	// camera orientation (camori)
	m_globalScope->externalAssignVariable("camori", e3ga(1.0), OD_HIDE | OD_HIDE_ALWAYS);

	// camera position (campos)
	m_globalScope->externalAssignVariable("campos", e3ga(GRADE1, 0.0, 0.0, 11.0), OD_HIDE | OD_HIDE_ALWAYS | OD_MAGNITUDE);

	// autocolor function on or off (autocolor)
	m_globalScope->externalAssignVariable("autocolor", e3ga(1.0), OD_HIDE | OD_HIDE_ALWAYS);

	return;
}

void state::newGlobalScope() {
	if (m_globalScope) delete m_globalScope;
	m_globalScope = new consoleGlobalScope();

	// create global state variables:

/*	// add autocolorfunc (removed, since autocolor is now hard coded)
	m_globalScope->supressWarnings(1); // don't say 'added function ...' on the console
	consoleCommandCallback(g_defaultAutoColorFunction);
	m_globalScope->supressWarnings(0);*/

	setDefaultGlobalScopeVariables();
}

/*
level -1: top level; delete the entire stack (cause: UI open, or next/prev in play list)
level 0: replace current file in stack (cause: 'open' command
level 1: add new file to the stack (cause: import command)
*/
int state::openGAfile(const char *filename, int nbArg /*= 0*/, char *arg[] /*= NULL*/, int level /*= -1*/) {
	if ((filename == NULL) || (filename[0] == 0)) return 0;

	// do this reset if top level replace (level = -1, or level = 0, currently at top level)
	if ((level == -1) || ((m_GAfileStackDepth == 0) && (level == 0))) {
		// reset entire state
		reset(filename);
	}

	// open the file (maybe put this after deleteing the stack??
	m_GAfileStackDepth++; // this is to make sure the file thinks it is being opened at the right level
	GAfile *file = new GAfile(this, filename, level, m_deleteFileQuestion, nbArg, arg);
	m_GAfileStackDepth--; // this is to make sure the file thinks it is being opened at the right level
	if (file->filename() == NULL) { // open failed
		m_GAfileStackDepth--;
		delete file;
		return -1;
	}

	// possibly delete part of the stack
	if (m_GAfileStackDepth >= 0) {
		switch (level) {
		case -1: // delete the entire stack
			//deleteGAfileStack(); // is done above 
			break;
		case 0: // delete the current (if any) file
			if (currentGAfile())
				file->m_closeAtEOF = currentGAfile()->m_closeAtEOF;
			deleteTopOfGAfileStack();
			break;
		case 1: // add on top of stack
			break;
		}
	}
	if (level == 1) file->m_closeAtEOF = 1; // always close an import at end of file

	// now add the file to the top of the stack...
	m_GAfileStackDepth++;
	if ( (m_GAfileStack = (GAfile **)realloc(m_GAfileStack, sizeof(GAfile *) * (m_GAfileStackDepth + 1))) == NULL) {
		printf("state::openGAfile(): memory allocation error\n");
		return -1;
	}
	m_GAfileStack[m_GAfileStackDepth] = file;


	// read first data? Maybe not... (just leave that to the timer)
	//file->read(this);

	return 0;
}

int state::resetGAfileState() {
//	printf("Reset state\n");
	m_rotTime = m_trlTime = m_inputSleepTime = -1.0;
	m_bookmarkSearch = 0;
	m_fontSize = 20.0;
	m_tsMode = "verbatim"; // todo: can this be replaced by a call to tsReset()
	m_tsFont = "regular";
	setInputWaitState(0);
	gui_state->m_mainWindow->setTitle("untitled");
	gui_state->setStatus("");
	return 0;
}

int state::filenameOnGAfileStack(const char *filename, int depth) {
	int i;
	if (depth < 0) depth = m_GAfileStackDepth;

	if (filename == NULL) return 0;

	for (i = 0; i <= depth; i++) {
		if ((m_GAfileStack[i]) && (!strcmpnc(filename, m_GAfileStack[i]->filename())))
			return 1;
	}

	return 0;
}

int state::deleteGAfileStack(const char *newFilename, int depth /* = 0 */) {
	int err;
	while  (m_GAfileStackDepth >= depth)
		if ( (err = deleteTopOfGAfileStack(newFilename)) != 0)
			return err;

	return 0;
}

int state::deleteTopOfGAfileStack(const char *newFilename) {

	if (m_GAfileStackDepth < 0) return 0;
	if (m_GAfileStack[m_GAfileStackDepth]) {
//		int handleDelete = filenameOnGAfileStack(newFilename);

		// check if we should delete this file; do so
		if (newFilename && 
			((!strcmpnc(m_GAfileStack[m_GAfileStackDepth]->filename(), newFilename)) ||
			(filenameOnGAfileStack(m_GAfileStack[m_GAfileStackDepth]->filename(), m_GAfileStackDepth -1))))
				m_GAfileStack[m_GAfileStackDepth]->handleDelete();

		// remove the file from the stack
		delete m_GAfileStack[m_GAfileStackDepth];
		m_GAfileStack[m_GAfileStackDepth] = NULL;
	}
	m_GAfileStackDepth--;
	if (m_GAfileStackDepth < 0) {
		free(m_GAfileStack);
		m_GAfileStack = NULL;
	}
	return 0;
}


int state::replayFirstGAfile() {
	char str[1024];
	int i, err = 0;

	if ((m_GAfileStackDepth >= 0) && 
		(m_GAfileStack[0])) {
		strcpy(str, m_GAfileStack[0]->filename());

		// copy arguments
		int nbArg = m_GAfileStack[0]->m_nbArg;
		char **arg = (char**)malloc(sizeof(char*) * nbArg);
		if (arg == NULL) nbArg = 0;
		for (i = 0; i < nbArg; i++)
			arg[i] = (m_GAfileStack[0]->m_arg[i]) ? strdup(m_GAfileStack[0]->m_arg[i]) : NULL;

		g_state->deleteGAfileStack(str); // remove all from the stack

		err = g_state->openGAfile(str, nbArg, arg);

		// free arguments
		if (arg) {
			for (i = 0; i < nbArg; i++)
				if (arg[i]) free(arg[i]);
			free(arg);
		}
	}
	return err;
}


int state::clearPlayList() {
	int i, j;
	if (m_playList) {
		for (i = 0; i < m_playListLength; i++) {
			if (m_playList[i].filename) free(m_playList[i].filename);
			if (m_playList[i].arg) {
				for (j = 0; j < m_playList[i].nbArg; j++)
					if (m_playList[i].arg[j]) free(m_playList[i].arg[j]);
				free(m_playList[i].arg);
			}
		}
		free(m_playList);
		m_playList = NULL;
	}

	m_playListLength = 0;
	m_playListPos = -1;
	return 0;
}

int state::openPlayList(const char *filename) {
	//cprintf("Open playlist '%s'\n", filename);
	clearPlayList();

	// parse file... 
	m_playListParse = 1;
	GAfile *f = new GAfile(this, filename, -1);
	f->read(this);
	delete f;
	m_playListParse = 0;

	setPlayListPos(0);

	return 0;
}


int state::addPlayListEntry(const char *filename, int nbArg /*= 0*/, char *arg[] /*= NULL*/) {
	int i;
	// sanity check
	if (filename == NULL) return -1;
	if (m_playListLength < 0) m_playListLength = 0;

	// allocate mem, duplicate string
	m_playList = (struct playList_s*)realloc(m_playList, sizeof(struct playList_s) * (m_playListLength + 1));
	if (m_playList)	{
		m_playList[m_playListLength].filename = strdup(filename);
		m_playList[m_playListLength].arg = (char**)malloc(sizeof(char*) * nbArg);
		if (m_playList[m_playListLength].arg) {
			for (i = 0; i < nbArg; i++) {
				m_playList[m_playListLength].arg[i] = strdup(arg[i]);
//				printf("Arg %d: '%s'\n", i, m_playList[m_playListLength].arg[i]);
			}
		}
		m_playList[m_playListLength].nbArg = nbArg;
	}

	// check mem allocs
	if ((m_playList == NULL) || (m_playList[m_playListLength].filename == NULL) || 
		(m_playList[m_playListLength].arg == NULL)) {
		printf("state::addPlayListEntry(): memory allocation error\n");
		return -1;
	}
	m_playListLength++;

	return 0;
}

int state::nextPlayListEntry() {
	if (m_playListPos >= 0)
		return setPlayListPos(m_playListPos + 1);
	else {
		cprintf("state::nextPlayListEntry(): no playlist open\n");
		return -1;
	}
}

int state::previousPlayListEntry() {
	if (m_playListPos >= 0)
		return setPlayListPos(m_playListPos - 1);
	else {
		cprintf("state::previousPlayListEntry(): no playlist open\n");
		return -1;
	}
}

int state::setPlayListPos(int pos) {
	if (m_playListLength <= 0) {
		cprintf("state::setPlayListPos(): no playlist loaded\n");
		return -1;
	}

	if ((pos < 0) || (pos >= m_playListLength)) {
		cprintf("state::setPlayListPos(): playlist position '%d' is out of range\n", pos + 1);
		return -1;
	}

	m_playListPos = pos;
//	printf("setPlayListPos %d -> %s\n", pos, m_playList[pos].filename);
	openGAfile(m_playList[pos].filename, m_playList[pos].nbArg, m_playList[pos].arg);

	return 0;
}

int state::setOpenFile(const char *filename, int nbArg /*= 0*/, char *arg[] /*= NULL*/, int level /*= 1*/) {
	int i;
	freeOpenFile();

	m_openFileLevel = level;
	m_openFilename = strdup(filename);

	m_openFileNbArg = nbArg;
	m_openFileArg = (char**)calloc(sizeof(char*), nbArg);
	// todo: chekc mem alloc
	if (m_openFileArg) {
		for (i = 0; i < nbArg; i++)
			m_openFileArg[i] = strdup(arg[i]);
	}

	return 0;
}

int state::freeOpenFile() {
	int i;

	if (m_openFilename) free(m_openFilename);

	if (m_openFileArg) {
		for (i = 0; i < m_openFileNbArg; i++)
			if (m_openFileArg[i]) free(m_openFileArg[i]);
		free(m_openFileArg);
	}

	m_openFileNbArg = 0;
	m_openFileArg = NULL;
	m_openFilename = NULL;

	return 0;
}

int state::addE3gaObject(const e3ga &mv, const std::string &name, int drawMode /* = 0 */, int creationFlags /*= 0*/, int forceFlags /* = 0 */) {
	e3gaObject *o = new e3gaObject(mv, name, drawMode, creationFlags, forceFlags);
	if (!o->m_int.m_valid) {
		if (mv.norm_a() > 1e-5) {
			if (!m_globalScope->supressWarnings()) {
				cprintf("Interpretation of object '%s' with coordinates %s failed.\n", name.c_str(), mv.string());
			}
		}
//		delete o; // yeah?
//		o->m_type = MVI_UNKNOWN;
//		return 0;
	}

	addObject(o, forceFlags);

	return 0;
}

int state::addP3gaObject(const p3ga &mv, const std::string &name, int drawMode /* = 0 */, int creationFlags /*= 0*/, int forceFlags /* = 0 */) {

	p3gaObject *o = new p3gaObject(mv, name, drawMode, creationFlags, forceFlags);
	if (!o->m_int.m_valid) {
		if (mv.norm_a() > 1e-5) {
			if (!m_globalScope->supressWarnings()) {
				cprintf("Interpretation of object '%s' with coordinates %s failed.\n", name.c_str(), mv.string());
			}
		}
//		delete o; // yeah?
//		o->m_type = MVI_UNKNOWN;
//		return 0;
	}

	addObject(o, forceFlags);

	return 0;
}

int state::addC3gaObject(const c3ga &mv, const std::string &name, int drawMode /* = 0 */, int creationFlags /*= 0*/, int forceFlags /* = 0 */) {

	c3gaObject *o = new c3gaObject(mv, name, drawMode, creationFlags, forceFlags);
	if (!o->m_int.m_valid) {
		if (mv.norm_a() > 1e-5) {
			if (!m_globalScope->supressWarnings()) {
				cprintf("Interpretation of object '%s' with coordinates %s failed.\n", name.c_str(), mv.string());
			}
		}
	}
	
	addObject(o, forceFlags);

	return 0;
}

int state::addC5gaObject(const c5ga &mv, const std::string &name, int drawMode /* = 0 */, int creationFlags /*= 0*/, int forceFlags /* = 0 */) {

	c5gaObject *o = new c5gaObject(mv, name, drawMode, creationFlags, forceFlags);
	if (!o->m_int.m_valid) {
		if (mv.norm_a() > 1e-5) {
			if (!m_globalScope->supressWarnings()) {
				cprintf("Interpretation of object '%s' with coordinates %s failed.\n", name.c_str(), mv.string());
			}
		}
	}
	
	addObject(o, forceFlags);

	return 0;
}

int state::addI2gaObject(const i2ga &mv, const std::string &name, int drawMode /* = 0 */, int creationFlags /* = 0 */, int forceFlags /* = 0 */) {

	i2gaObject *o = new i2gaObject(mv, name, drawMode, creationFlags, forceFlags);
	if (!o->m_int.m_valid) {
		if (mv.norm_a() > 1e-5) {
			if (!m_globalScope->supressWarnings()) {
				cprintf("Interpretation of object '%s' with coordinates %s failed.\n", name.c_str(), mv.string());
			}
		}
	}
	
	addObject(o, forceFlags);

	return 0;
}



int state::addTextObject(const char *text, const e3ga &pos, const std::string &name, int labelFlags, int width) {
	textObject *o = new textObject(text, pos, name, 0, labelFlags, width);
	addObject(o);
	return 0;
}


int state::addTextObject(const char *text, const std::string &pointName, const std::string &name, int labelFlags, int width) {
	textObject *o = new textObject(text, pointName, name, 0, labelFlags, width);
	addObject(o);
	return 0;
}

int state::addObject(object *o, int forceFlags /* = -1 */) {
	int err;

	modified(o->m_name);

	// set all kinds of properties from the state:
	o->setFgColor(m_fgColor);
	o->setBgColor(m_bgColor);
	o->setOlColor(m_olColor);
	o->m_fontSize = m_fontSize;
	o->m_poFactor = m_poFactor;
	o->m_poUnits = m_poUnits;

	/* 
	If we are simply updating an object, 
	restore it as the current object once we are done
	*/
	// make it an option to keep the old 'displaying' properties,
	// and only change new true content, like mv, coordinates or text
	object *sameNameObject = getObjectPtrByName(o->m_name);
	int hideAlways = 0;
	if (sameNameObject) {
		int propertiesChanged;
		hideAlways = sameNameObject->m_drawMode & OD_HIDE_ALWAYS;
		if ( (err = sameNameObject->copy(o, propertiesChanged, forceFlags)) == 0) { // add enforce flag here?
			if (gui_state) {
				if (sameNameObject == gui_state->m_currentObject)
					gui_state->updateControls(propertiesChanged);
				if (gui_state->m_glWindow) gui_state->m_glWindow->redraw();
			}
			sameNameObject->m_drawMode |= hideAlways | (hideAlways ? OD_HIDE : 0); // always keep hide always!

			delete o;
			return 0;
		}
		// else : copy failure, simply overwrite....
	}

	// first remove any object that already has that name
	removeObject(o->m_name);

	o->m_drawMode |= hideAlways | (hideAlways ? OD_HIDE : 0); // always keep hide always!

	m_objects.insert(std::make_pair(stringPtr(&(o->m_name)), o));
	
	if (gui_state && gui_state->m_glWindow) gui_state->m_glWindow->redraw();

	return 0;
}

int state::objectUpdate() {
//	object *o;
	double t = u_timeGet();
		
	std::vector<std::string *> removeObjectVector;


	for (OI oi = m_objects.begin(); oi != m_objects.end(); oi++) {
		try {
			oi->second->update(t);
		} catch(removeObjectException e) {
//			std::cout << "remove: " << oi->second->m_name << "\n";
			removeObjectVector.push_back(&(oi->second->m_name));
		}
	}

	for (int i = 0; i < (int)removeObjectVector.size(); i++)
		removeObject(*(removeObjectVector[i]));

	return 0;
}

void state::textScaleChanged() {
	for (OI oi = m_objects.begin(); oi != m_objects.end(); oi++) {
		oi->second->textScaleChanged();
	}
}


int state::removeObject(object *ptr) {
	return removeObject(ptr->m_name);
}

//inline bool operator==(const object *a, const state::stringPtr b) {return (a->m_name) == (*b.ptr);}

int state::removeObject(const std::string &name) {
	COI i = m_objects.find(stringPtr(name));
		//std::find(m_objects.begin(), m_objects.end(), stringPtr(name));

	if (i != m_objects.end()) {
		object *ptr = i->second;
		m_objects.erase(stringPtr(ptr->m_name));

		modified(ptr->m_name); // tell dynamic statement eval

		if (gui_state && (ptr == gui_state->m_currentObject))
			gui_state->setCurrentObject(NULL);

		delete ptr;

		if (gui_state && gui_state->m_glWindow) gui_state->m_glWindow->redraw();
	}

	return 0;
}

int state::removeAllObjects() {

	if (gui_state) gui_state->setCurrentObject(NULL);

	for (OI i = m_objects.begin(); i != m_objects.end(); i++) delete i->second;
	m_objects.clear();

	object::m_objectCount = 1;

	if (gui_state && gui_state->m_glWindow) gui_state->m_glWindow->redraw();

	return 0;
}

int state::hideObject(const std::string &name) {
	object *o = getObjectPtrByName(name);
	if (o == NULL) return -1;
	o->hide();
	return 0;
}

int state::showObject(const std::string &name) {
	object *o = getObjectPtrByName(name);
	if (o == NULL) return -1;
	o->show();
	return 0;
}


object *state::getObjectPtrByName(const std::string &name) {
	COI i = m_objects.find(stringPtr(name));//std::find(m_objects.begin(), m_objects.end(), stringPtr(name));
	return ((i != m_objects.end()) ? i->second : NULL);
}

float *state::getColorPtr(const char *colorName) {
	if (!strcmpnc(colorName, "fgcolor")) return m_fgColor;
	else if (!strcmpnc(colorName, "bgcolor")) return m_bgColor;
	else if (!strcmpnc(colorName, "olcolor")) return m_olColor;
	else if (!strcmpnc(colorName, "cvcolor")) return m_cvColor;
	else {
		printf("state::getColorPtr(): unknown color name '%s'\n", colorName);
		return NULL;
	}
}

int state::setColor(const char *colorName, const char *value) {
	float c[4];
	int err;
	if ( (err = ::getColor(value, c)) != 0)
		printf("state::setColor(): unknown color '%s'\n", value);
	else setColor(colorName, c[0], c[1], c[2], c[3]);

	/*
	if ((!strcmpnc(value, "r")) || (!strcmpnc(value, "red"))) return setColor(colorName, 1.0, 0.0, 0.0, 1.0);
	else if ((!strcmpnc(value, "g")) || (!strcmpnc(value, "green"))) return setColor(colorName, 0.0, 1.0, 0.0, 1.0);
	else if ((!strcmpnc(value, "b")) || (!strcmpnc(value, "blue"))) return setColor(colorName, 0.0, 0.0, 1.0, 1.0);
	else if ((!strcmpnc(value, "w")) || (!strcmpnc(value, "white"))) return setColor(colorName, 1.0, 1.0, 1.0, 1.0);
	else if ((!strcmpnc(value, "m")) || (!strcmpnc(value, "magenta"))) return setColor(colorName, 1.0, 0.0, 1.0, 1.0);
	else if ((!strcmpnc(value, "y")) || (!strcmpnc(value, "yellow"))) return setColor(colorName, 1.0, 1.0, 0.0, 1.0);
	else if ((!strcmpnc(value, "c")) || (!strcmpnc(value, "cyan"))) return setColor(colorName, 0.0, 1.0, 1.0, 1.0);
	else if ((!strcmpnc(value, "k")) || (!strcmpnc(value, "black"))) return setColor(colorName, 0.0, 0.0, 0.0, 1.0);
	else if ((!strcmpnc(value, "grey")) || (!strcmpnc(value, "gray"))) return setColor(colorName, 0.5f, 0.5f, 0.5f, 1.0f);
	else printf("state::setColor(): unknown color '%s'\n", value);*/

	return 0;
}

int state::setColor(const char *colorName, float r, float g, float b, float a /*= 1.0*/) {
	float *rgba = getColorPtr(colorName);
	if (rgba == NULL) return -1;
//	printf("Set color %s to %f %f %f\n", colorName, r, g, b);
	rgba[0] = r;
	rgba[1] = g;
	rgba[2] = b;
	rgba[3] = a;
	return 0;
}

int state::setTrl(e3ga &trl, double dIn) {
	double duration = dIn;
	m_trlTime = -1.0;
	if ((gui_state == NULL) || (duration < 0.0)) return -1;

	trl = trl(GRADE1);

	duration *= m_playbackSpeed;
	if (duration == 0.0) {
		// instantanious translation
		gui_state->m_glWindow->setCamPos(gui_state->m_glWindow->getCamPos() + (dIn * trl));
		gui_state->m_glWindow->redraw();
	}
	else {
		m_trlTime = u_timeGet();
		m_trlEndTime = m_trlTime + duration;
		m_trl = trl / m_playbackSpeed;
	}
	return 0;
}

int state::handleTrl() {
	if ((m_trlTime < 0.0) || (gui_state == NULL)) return 0;

	if (m_inputWait) { // don't translate
		double t = u_timeGet();
		m_trlEndTime += t - m_trlTime;
		m_trlTime = t;
	}
	else {
		double t = U_MIN(m_trlEndTime, u_timeGet());
		gui_state->m_glWindow->setCamPos(gui_state->m_glWindow->getCamPos() + m_trl * (t - m_trlTime));
		gui_state->m_glWindow->redraw();
		m_trlTime = (t >= m_trlEndTime) ? -1.0 : t;
	}

	return 0;
}

int state::setRot(e3ga &rot, double dIn) {
	double duration = dIn;
	m_rotTime = -1.0;
	if ((gui_state == NULL) || (duration < 0.0)) return -1;

	rot = -rot(GRADE2);

	duration *= m_playbackSpeed;
	if (duration == 0.0) {
		// instantanious translation
		gui_state->m_glWindow->setCamOri((dIn * rot).exp() * gui_state->m_glWindow->getCamOri());
		gui_state->m_glWindow->redraw();
	}
	else {
		m_rotTime = u_timeGet();
		m_rotEndTime = m_rotTime + duration;
		m_rot = rot / m_playbackSpeed;
	}
	return 0;
}

int state::handleRot() {
	if ((m_rotTime < 0.0) || (gui_state == NULL)) return 0;

	if (m_inputWait) { // don't translate
		double t = u_timeGet();
		m_rotEndTime += t - m_rotTime;
		m_rotTime = t;
	}
	else {
		double t = U_MIN(m_rotEndTime, u_timeGet());
		gui_state->m_glWindow->setCamOri(
			(m_rot * (t - m_rotTime)).exp() * gui_state->m_glWindow->getCamOri());
		gui_state->m_glWindow->redraw();

		m_rotTime = (t >= m_rotEndTime) ? -1.0 : t;
	}

	return 0;
}


int state::setInputWaitState(int wait) {
	double t = u_timeGet();

	if (wait) {
		if (m_bookmarkSearch) return 0; // never wait when searching for bookmark

		if (gui_state) {
			/*gui_state->m_waitButton->show();

			gui_state->m_statusOutput->resize(
				gui_state->m_statusOutput->x(),
				gui_state->m_statusOutput->y(),
				gui_state->m_mainWindow->w() - c_waitWidth,
				gui_state->m_statusOutput->h());*/
			gui_state->m_waitButton->label("waiting");
		}


		m_inputWait = 1;

		// remember when we started waiting (to compensate the sleep later on)
		if (m_inputSleepTime < t) m_inputSleepTime = -1.0;
		else m_inputWaitTime = t;
	}
	else {
		/*gui_state->m_waitButton->hide();

		gui_state->m_statusOutput->resize(
			gui_state->m_statusOutput->x(),
			gui_state->m_statusOutput->y(),
			gui_state->m_mainWindow->w(),
			gui_state->m_statusOutput->h());*/
		if (gui_state) {
			gui_state->m_waitButton->label("pause");
			gui_state->m_waitButton->color(FL_GRAY);
		}

		m_inputWait = 0;

		// compensate the sleep for waiting (we can't miss any sleep)
		if ((m_inputWaitTime >= 0.0) && (m_inputSleepTime >= 0.0)) {
			m_inputSleepTime += t - m_inputWaitTime;
			m_inputWaitTime = -1.0;
		}
	}

	// if in fullscreen mode: redraw glWindow
	if (gui_state->m_fullscreen) {
		gui_state->m_glWindow->redraw();
	}

	return 0;
}

int state::bookmarkFound() {
	if (m_bookmarkSearch == 0) return 0;
	m_bookmarkSearch = 0;
	m_playbackSpeed = m_preBookmarkSearchPlaybackSpeed;
	m_inputWait = 0;
	m_inputSleepTime = -1.0;
	return 0;
}

int state::bookmarkSearch() {
	if (m_bookmarkSearch) return 0;
	setInputWaitState(0);
	m_bookmarkSearch = 1;
	m_preBookmarkSearchPlaybackSpeed = m_playbackSpeed;
	m_playbackSpeed = 0.0; // infinite playback speed

	objectUpdate();

	return 0;
}

int state::setPlaybackSpeed(double speed ) {
	if (m_bookmarkSearch)
		m_preBookmarkSearchPlaybackSpeed = speed;
	else m_playbackSpeed = speed;
	return 0;
}

int state::setE3gaFactor(const e3ga &mv, int idx) {
	if ((idx < 0) || (idx > 2)) {
		printf("state::setE3gaFactor(): invalid index %d\n", idx);
		return -1;
	}
	m_e3gaFactor[idx] = mv(GRADE1);

	return 0;
}

int state::setP3gaFactor(const p3ga &mv, int idx) {
	if ((idx < 0) || (idx > 3)) {
		printf("state::setP3gaFactor(): invalid index %d\n", idx);
		return -1;
	}
	m_p3gaFactor[idx] = mv(GRADE1);

	return 0;
}

int state::setC3gaFactor(const c3ga &mv, int idx) {
	if ((idx < 0) || (idx > 4)) {
		printf("state::setE3gaFactor(): invalid index %d\n", idx);
		return -1;
	}
	m_c3gaFactor[idx] = mv(GRADE1);

	return 0;
}

int state::tsReset() {
	if (m_typesetState) delete m_typesetState;
	m_typesetState = new typesetState();
	m_tsMode = "verbatim";
	m_tsFont = "regular";
	return 0;
}

int state::tsParse(const char *str) {
	m_typesetState->setInitialMode("text");
	return m_typesetState->parse(str);
}

int state::tsSetMode(const char *m) {
	if ((m[0] == 't') || (m[0] == 'T')) m_tsMode = "text";
	else if ((m[0] == 'e') || (m[0] == 'E')) m_tsMode = "equation";
	else if ((m[0] == 'v') || (m[0] == 'V')) m_tsMode = "verbatim";

	return 0;
}

int state::tsSetFont(const char *m) {
	if ((m[0] == 'r') || (m[0] == 'R')) m_tsFont = "regular";
	else if ((m[0] == 'b') || (m[0] == 'B')) m_tsFont = "bold";
	else if ((m[0] == 'i') || (m[0] == 'I')) m_tsFont = "italic";
	else if ((m[0] == 'g') || (m[0] == 'G')) m_tsFont = "greek";

	return 0;
}

int state::forwardAnimationTime(double dt) {
	consoleVariable *atime;
	if (m_globalScope->lookupVariable("atime", 1, &atime) == 0)
		setAnimationTime(atime->e().scalar() + dt);
	else {
		cprintf("Can not lookup global variable 'atime', setting it to %f \n", dt);
		setAnimationTime(dt);
	}
	return 0;
}

int state::setAnimationTime(double t) {
	g_state->m_globalScope->externalAssignVariable("atime", e3ga(t), OD_HIDE | OD_HIDE_ALWAYS);
/*	consoleVariable *atime = new consoleVariable("", e3ga(t));
	atime->drawMode(OD_HIDE | OD_HIDE_ALWAYS);
	g_state->m_globalScope->assignVariable(new consoleVariable("atime", e3ga(0.0)), atime);
	delete atime;*/
	return 0;
}

// starts possible animation, sets mode to AM_PLAYING, sets 'atime' console variable to 0.0, calls updateDynamics
int state::startAnimation() {
	m_lastAnimationUpdate = u_timeGet();
	if (m_animationMode == AM_STOPPED) {
		m_animationMode = AM_PLAYING;
		setAnimationTime(0.0);
	}
	else if (m_animationMode == AM_PAUSED) { // exiting AM_PAUSED
		m_animationMode = AM_PLAYING;
	}
	else cprintf("Animation is already playing\n");

	updateDynStmts();

	return 0;
}

// sets mode to AM_STOPPED
int state::stopAnimation() {
	if (m_animationMode != AM_STOPPED) {
		m_animationMode = AM_STOPPED;
		updateDynStmts();
	}
	else cprintf("Animation is already stopped\n");

	return 0;
}

int state::pauseAnimation() {
	if (m_animationMode == AM_PLAYING) {
		m_animationMode = AM_PAUSED;
		updateDynStmts();
	}
	else cprintf("Animation is not playing\n");

	return 0;
}

// updates the 'atime' console variable if mode is AM_PLAYING, calls updateDynamics
int state::updateAnimation() {
	if (m_animationMode == AM_PLAYING) {
		double t = u_timeGet();
		double dt = (t - m_lastAnimationUpdate) / ((m_playbackSpeed>0.0) ? m_playbackSpeed : 10e-5);
		m_lastAnimationUpdate = t;
		forwardAnimationTime(dt);
		updateDynStmts();
	}

	return 0;
}

// prints to the console
int cprintf(const char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);

	if (g_state && gui_state && gui_state->m_console)
		return gui_state->m_console->cprintf(fmt, ap);
	else return vprintf(fmt, ap);
}

/*int cprintfC(const char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);

	if (g_state && gui_state && gui_state->m_console)
		return gui_state->m_console->cprintf(fmt, ap);
	else return vprintf(fmt, ap);
}
*/

