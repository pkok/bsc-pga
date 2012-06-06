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

#ifndef _FL_CONSOLE_H_
#define _FL_CONSOLE_H_

#include <string>
#include <FL/Fl_Text_Editor.H>

#ifdef SUN
//#include <sys/varargs.h>
#endif /* SUN */

class Fl_Console : public Fl_Text_Editor {
public:
    typedef void (*Command_Func)(const char *cmd, void *cbArg);

    Fl_Console(int X, int Y, int W, int H, const char* l = 0);
    virtual ~Fl_Console();

	// deactivate & activate with colors
	void deactivate();
	void activate();

	// temp test
	virtual int handle(int);

	// returns diary, clears diary
	std::string diary() {
		std::string d = m_diary;
		m_diary.clear();
		return d;
	}

	// gets and sets the command prompt
	void prompt(const char *str);
	const char *prompt();

	// adds and removes callbacks
	void add_command_callback(Command_Func func, void *cbArg);
	void remove_command_callback(Command_Func func, void *cbArg);

	// gets and sets the maximum length of the command history
	void max_history(int nb);
	inline int max_history() {return m_maxCommandHistory;}

	void clear(); // clears both command history and buffer
	void clear_history(); // clears command history
	void clear_buffer(); // clears text buffer

	int cprintf(const char *fmt, ...); // prints formatted to console
	int cprintf(const char *fmt, va_list &ap); // prints formatted to console (caller must do {va_list ap; va_start(ap, fmt);} itself)
	int cprint(const char *str, int insert = 0 ); // prints unformatted to console

protected:
	int commandEnter(); // processes the current command
	int newPrompt(); // spawns a new command prompt at the end of the file

	char *command(); // returns, in a malloced() string, the current command after the prompt
	int command(const char *str); // sets the current command after the prompt

	int m_nbCommandCallback; // how many command callbacks
	void **m_commandCallbackArg; // the arguments that will be passed to the callbacks
	Command_Func *m_commandCallback; // the callback functions
	int callCommandCallbacks(const char *str);
	int m_callingCallbacks; // true while callbacks are being called

	char *m_prompt; // command prompt, e.g. ">> " (the default)
	int m_promptPos; // current first position after the prompt (-1 if none)

	int m_modifySelf; // true if the widget is modifying itself (used to block infinite recursion in modify callback)

	int addCommandHistory(char *str); // adds a command to the command history
	char **m_commandHistory;
	int m_commandHistoryLength; // number of commands in m_commandHistory
	int m_commandHistoryPos; // the current command (for browsing)
	int m_maxCommandHistory;

	Fl_Text_Buffer *m_textBuffer;

	void initToNothing();

//	static int kf_Default(int key, Fl_Text_Editor* e);
	static int kf_Enter(int key, Fl_Text_Editor* e);
	static int kf_Up(int key, Fl_Text_Editor* e);
	static int kf_Down(int key, Fl_Text_Editor* e);
	static int kf_Left(int key, Fl_Text_Editor* e);
	static int kf_c_Left(int key, Fl_Text_Editor* e);
	static int kf_Right(int key, Fl_Text_Editor* e);
	static int kf_Home(int key, Fl_Text_Editor* e);
	static int kf_End(int key, Fl_Text_Editor* e);
	static int kf_Page_Up(int key, Fl_Text_Editor* e);
	static int kf_Page_Down(int key, Fl_Text_Editor* e);
	static int kf_Backspace(int key, Fl_Text_Editor* e);
	static int kf_parenthesis_jump(int key, Fl_Text_Editor* e);
	static int handleSelect(Fl_Console *con);
	static void modifyCallback(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg);

	std::string m_diary;
};


#endif /* _FL_CONSOLE_H_ */
