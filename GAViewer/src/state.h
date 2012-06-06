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

#ifndef _STATE_H_
#define _STATE_H_

#include <vector>
#include <string>
#include <set>
#include <map>
#include <utility>
#include <memory>

#ifdef WIN32
#pragma warning( disable : 4311 4312 4244 4996 4267)
#endif

class GAfile;
class consoleGAfile;
class object;
class typesetState;
class consoleVariable;
class consoleGlobalScope;
class consoleStatement;
class consoleStmtListStmt;
class consoleControl;
class netServer;


#include "gaincludes.h"

#define GL_INVALID_DISPLAY_LIST 0xFFFFFFFF
#define GL_INVALID_TEXTURE_NAME 0xFFFFFFFF

#define AM_STOPPED 0
#define AM_PLAYING 1
#define AM_PAUSED 2

class state {
public:
	state();
	~state();
	void initToNothing();

	// resets all, filename argument is only used by state::openGAfile()
	void reset(const char *filename = NULL);
	void newGlobalScope();
	void setDefaultGlobalScopeVariables();

	// special GAFile just for console input
	consoleGAfile * m_consoleGAfile;

	// every file reference is done relative to m_workingDirectory (unless it is absolute)
	void setWorkingDirectory(const std::string &dir, bool removeTrailingFilename = false);
	std::string fullFilename(const std::string &filename); // returns the full path of 'filename'
	std::string m_workingDirectory;
	std::string m_initialWorkingDirectory; // working directory at the time 'state' was created


	/*
	'GAfiles' are managed on a stack.
	Items opened from the user interface, or from
	playlists, or 'opened' (command) files are put at 
	the bottom of the stack.
	'Imported' (command) files are put on top of the stack.
	Switchto (command) files replace the top of the stack.

	Input from the console is implemented as a GAfile that
	is put at the bottom of the stack, allowing one to import
	other files.
	*/

	/*
	level -1: top level; delete the entire stack (cause: UI open, or next/prev in play list)
	level 0: replace current file in stack (cause: 'open' command
	level 1: add new file to the stack (cause: import command)
	*/
	int openGAfile(const char *filename, int nbArg = 0, char *arg[] = NULL, int level = -1);
	int filenameOnGAfileStack(const char *filename, int depth = -1); // return true if 'filename' is in use on the current stack
	int resetGAfileState(); // resets all state vars that have to do with the GAfile reading/parsing
	int deleteTopOfGAfileStack(const char *newFilename = NULL); // closes the top file of the stack
	int deleteGAfileStack(const char *newFilename = NULL, int depth = 0); // closes all files on the stack
	int replayFirstGAfile(); // closes all files on the stack, rereads the file originally at depth 0
	// GAfile stack
	int m_GAfileStackDepth;
	GAfile **m_GAfileStack;
	inline GAfile *currentGAfile() {return (m_GAfileStackDepth >= 0) ? m_GAfileStack[m_GAfileStackDepth] : NULL;}

	// This is the default question question that will be asked if m_deleteFile == 0 for a GAfile
	char *m_deleteFileQuestion; 

	// these two variables are used to indicate that the main timer (ui_timerCallback()) should open a different file on the next 'tick'
	char *m_openFilename; // if this is not NULL, this file will be opened by UIstate::timercallback
	int m_openFileLevel; // the level at which the file is to be opened
	int m_openFileNbArg;
	char **m_openFileArg;
	int setOpenFile(const char *filename, int nbArg = 0, char *arg[] = NULL, int level = -1);
	int freeOpenFile();


	/*
	A playlist (geo play list, .gpl) can be read. 
	ctrl-n, file->next can then be used to go to open the next file
	ctrl-p, file->previous can then be used to go to open the previous file
	GA files are opened at level -1
	*/
	int clearPlayList(); // removes all
	int openPlayList(const char *filename); // loads a playlist file (.gpl)
	int addPlayListEntry(const char *filename, int nbArg = 0, char *arg[] = NULL);
	int nextPlayListEntry();
	int previousPlayListEntry();
	int setPlayListPos(int pos);
	int m_playListLength, m_playListPos;
	struct playList_s {
		char *filename;
		int nbArg;
		char **arg;
	} *m_playList;
	// remember playlist filename???
	//char **m_playList;
	int m_playListParse; // set to true while parsing a playlist (used by GAfile::parseLine() to determine its behaviour);

	double m_inputSleepTime; // don't poll input until current time > m_inputSleepTime (unless < 0)
	int m_inputWait; // if true, don't read input at all...
	double m_inputWaitTime; // when was the m_inputWait set to true? This value is used to compensate the m_inputSleepTime when the m_inputWait is set to false again
	int setInputWaitState(int wait);

	double m_playbackSpeed; // defaults to 1.0
	int setPlaybackSpeed(double speed);

	int m_bookmarkSearch; // if true, we never sleep or wait until a bookmark is found
	double m_preBookmarkSearchPlaybackSpeed; // remember the m_playbackSpeed from before the start of the search
	int bookmarkFound();
	int bookmarkSearch();

	// saving the current 'scene' to a .geo file
	int writeStateToGeoFile(const char *filename); // in writestate.cpp

	// console stuff
//	int lookupConsoleVariable(const char *name, consoleVariable **variable);
//	int lookupConsoleFunction(const char *name, int nbArg, consoleVariable *arg[], int *argType, const struct consoleFunc_s **func);
//	int existConsoleFunction(const char *name);
	int consoleCommandCallback(const char *cmd); // handles commands entered at the console

	consoleGlobalScope *m_globalScope;
	int consoleSourceFileRead(const char *filename); // reads a '.g' file, parses it, adds functions/batches to global scope
	int consoleSourceDirRead(const char *filename); // reads all '.g' files in directory

	// console control stuff
	std::vector<consoleControl*> m_consoleControls;
	int addConsoleControl(consoleControl *cc);
	int addConsoleControlBool(const std::string &name, int value);
	int addConsoleControlRange(const std::string &name, GAIM_FLOAT value, GAIM_FLOAT minValue, GAIM_FLOAT maxValue, GAIM_FLOAT step);
	int addConsoleControlSelection(const std::string &name, GAIM_FLOAT value, const std::vector<std::pair<std::string, GAIM_FLOAT> >&options);
	int addConsoleControlBool(const std::string &name, int value, const std::string &callbackFunctionName);
	int addConsoleControlRange(const std::string &name, GAIM_FLOAT value, GAIM_FLOAT minValue, GAIM_FLOAT maxValue, GAIM_FLOAT step, const std::string &callbackFunctionName);
	int addConsoleControlSelection(const std::string &name, GAIM_FLOAT value, const std::vector<std::pair<std::string, GAIM_FLOAT> >&options, const std::string &callbackFunctionName);
	int removeConsoleControl(const std::string &name);
	int removeAllConsoleControls();
	int writeConsoleControlsToGeoFile(FILE *F);
	int resizeConsoleControls();	
	int updateConsoleControls(); // called only by updateDynStmts(); 

	// calls textScaleChanged on all objects 
	void textScaleChanged();

	int objectUpdate(); // calls the 'update' function of all objects (takes care of fading, etc)
	int addE3gaObject(const e3ga &mv, const std::string &name, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	int addP3gaObject(const p3ga &mv, const std::string &name, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	int addC3gaObject(const c3ga &mv, const std::string &name, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	int addC5gaObject(const c5ga &mv, const std::string &name, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	int addI2gaObject(const i2ga &mv, const std::string &name, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	int addTextObject(const char *text, const std::string &pointName, const std::string &name, int labelFlags, int width);
	int addTextObject(const char *text, const e3ga &pos, const std::string &name, int labelFlags, int width);
	int addObject(object *o, int forceFlags = -1);
	int removeObject(const std::string &name);
	int removeObject(object *ptr);
	int hideObject(const std::string &name);
	int showObject(const std::string &name);
	int removeAllObjects();
	object *getObjectPtrByName(const std::string &name);
///	int getObjectIdxByName(const std::string &name);

	class stringPtr {
	public:
		stringPtr(const std::string *s) : ptr(s) {}
		stringPtr(const std::string &s) : ptr(&s) {}
		~stringPtr() {}
		const std::string *ptr;
	};
	// objects are kept in a map, order by lexical order using stringPointerLess:
	struct stringPtrLess {
		inline bool operator()(const stringPtr a, const stringPtr b) const {return (*a.ptr) < (*b.ptr);}
	};
//	typedef std::map<const stringPtr, object*, stringPtrLess> OCT;
	typedef std::map<stringPtr, object*, stringPtrLess> OCT;
	typedef OCT::iterator OI;
	typedef OCT::const_iterator COI;
	OCT m_objects;

	class dynStmtInfo {
	public:
//		dynStmtInfo(consoleStmtListStmt *dynStmt, const std::string &workingDirectory, const std::string &name) {}
		dynStmtInfo(consoleStmtListStmt *dynStmt, const std::string &workingDirectory, const std::string &name);
		dynStmtInfo(const dynStmtInfo &dsi);
		~dynStmtInfo();

		void set(const dynStmtInfo &dsi);

		inline dynStmtInfo&operator=(const dynStmtInfo &dsi) {
			if (this != &dsi) set(dsi);
			return *this;
		}

		inline bool hasName() const {return (m_name.size() != 0);}
		inline const std::string &name() const {return m_name;}
		inline const std::string &wd() const {return m_workingDirectory;}
		inline consoleStmtListStmt *ds() const {return m_dynStmt.get();}
		void ds(consoleStmtListStmt *stmt);

	private:
		std::auto_ptr<consoleStmtListStmt> m_dynStmt;
		std::string m_name; // "" if anonymous (size = 0)
		std::string m_workingDirectory; // "" if anonymous (size = 0)
	};

	// dynamic statements
	typedef std::vector<dynStmtInfo>::iterator DSI ;
	std::vector<dynStmtInfo> m_dynStmt;
	int modified(const std::string &name); // checks with all current dynamic equations if 'name' is a variable inside them
	int addDynStmt(consoleStmtListStmt *stmt,  const std::string &workingDirectory, const std::string &name); // deletes old dynamic statement that go by 'name'
	int removeDynStmt(int idx);
	int removeDynStmt(const std::string &name);
	int removeDynStmt(consoleStmtListStmt *stmt);
	int replaceDynStmt(consoleStmtListStmt *oldStmt, consoleStmtListStmt *newStmt); // replace old by new, deletes old (deletes new on failure)
	int removeAllDynStmt();
	int updateDynStmts(); // goes through all dynamic statements, updates them as requied

	// current properties, as set through file commands
	int setColor(const char *colorName, const char *value);
	inline int setColor(const char *colorName, const float rgba[4]) {return setColor(colorName, rgba[0], rgba[1], rgba[2], rgba[3]);}
	int setColor(const char *colorName, float r, float g, float b, float a = 1.0);
	float m_fgColor[4]; // foreground color rgba [0.0, 1.0]
	float m_bgColor[4]; // background color rgba [0.0, 1.0]
	float m_olColor[4];  // outline color rgba [0.0, 1.0]
	float m_cvColor[4];  // canvas color rgba [0.0, 1.0]
	float m_fontSize; // height of font in pixels
	float m_clipDistance; // half size of the clipping 'cube'
	float m_poFactor, m_poUnits; // polygon offset

	float m_ambient, m_diffuse; // how much ambient and diffuse in material (constants)
	int m_labelsAlwaysOnTop; // should the labels always be drawn on top of other objects?
//	int m_clippingPlanesEnabled; // is the world clipped according to 'm_clipDistance'?

	int setTrl(e3ga &trl, double duration);
	int handleTrl();
	double m_trlTime; // if > 0.0, then we are currently translating until...
	double m_trlEndTime; // the time >= m_trlEndTime
	e3ga m_trl; // translation per second

	int setRot(e3ga &rot, double duration);
	int handleRot();
	double m_rotTime; // if > 0.0, then we are currently rotating until...
	double m_rotEndTime; // the time >= m_rotEndTime
	e3ga m_rot; // rotation per second

	// These factors are used during the interpretation of some objects to factor them.
	// They are provided such that the user can override the default factorization
	int setE3gaFactor(const e3ga &mv, int idx);
	int setP3gaFactor(const p3ga &mv, int idx);
	int setC3gaFactor(const c3ga &mv, int idx);
	inline int setI2gaFactor(const i2ga &mv, int idx) {return -1;} // todo
	inline int setC5gaFactor(const c5ga &mv, int idx) {return -1;} // todo
	e3ga m_e3gaFactor[3];
	p3ga m_p3gaFactor[4];
	c3ga m_c3gaFactor[5];

	// typesetting labels...
	typesetState *m_typesetState;
	const char *m_tsMode, *m_tsFont;
	int tsReset();
	int tsParse(const char *str);
	int tsSetMode(const char *mode); // text, equation, or verbatim
	int tsSetFont(const char *mode); // regular, bold, italic or greek

	// animation of dynamics
	int startAnimation(); // starts possible animation, sets mode to AM_PLAYING, sets 'atime' console variable to 0.0, calls updateDynamics
	int stopAnimation(); // sets mode to AM_STOPPED, calls updateDynamics
	int pauseAnimation(); // sets mode to AM_PAUSED, calls updateDynamics
	int updateAnimation(); // updates the 'atime' console variable if mode is AM_PLAYING, calls updateDynamics
	int setAnimationTime(double t); // sets the 'atime' console variable to 't'
	int forwardAnimationTime(double dt);
	int m_animationMode; // AM_X
	double m_lastAnimationUpdate;

	// network connections
	netServer **m_netServers;
	int m_nbNetServers;
	std::string m_defaultNetPort;
	bool m_displayNetworkCommands;
	std::set<std::string > m_netVarChanges; // message send to all clients on next poll . . .

	void closeNetServers();
	void openNetServer(const char *port);
	void closeNetServer(const char *port);
	void pollNetServers();
	void displayNetStatus();
	std::string createNetMessage(const std::set<std::string> &names) ;
	

protected:
	float *getColorPtr(const char *colorName);
	int newDynStmt(consoleStmtListStmt *stmt);
};

//inline bool operator==(const state::stringPtr a, const state::stringPtr b) {return (*a.ptr) == (*b.ptr);}

extern state *g_state;
extern const char *g_version;

// prints to the console
extern int cprintf(const char *fmt, ...);


#endif /* _STATE_H_ */
