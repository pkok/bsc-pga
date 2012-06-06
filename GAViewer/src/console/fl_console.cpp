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
#include <stdarg.h>


#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>

#include "fl_console.h"

Fl_Console::Fl_Console(int X, int Y, int W, int H, const char* l) : Fl_Text_Editor(X, Y, W, H, l) {
	initToNothing();

	max_history(100);

	m_textBuffer = new Fl_Text_Buffer();
	m_textBuffer->add_modify_callback(modifyCallback, this);
	buffer(m_textBuffer);

	prompt(">> ");
	newPrompt();

	add_key_binding(FL_Enter, FL_TEXT_EDITOR_ANY_STATE, kf_Enter);
	add_key_binding(FL_KP_Enter, FL_TEXT_EDITOR_ANY_STATE, kf_Enter);

	add_key_binding(FL_Up, 0, Fl_Console::kf_Up);
	add_key_binding(FL_Down, 0, Fl_Console::kf_Down);
	add_key_binding(FL_Left, 0, Fl_Console::kf_Left);
	add_key_binding(FL_Left, FL_CTRL,  Fl_Console::kf_c_Left);
	add_key_binding(FL_Right, 0, Fl_Console::kf_Right);
	add_key_binding(FL_Home, 0, Fl_Console::kf_Home);
	add_key_binding(FL_End, 0, Fl_Console::kf_End);
	add_key_binding(FL_Page_Up, 0, Fl_Console::kf_Page_Up);
	add_key_binding(FL_Page_Down, 0, Fl_Console::kf_Page_Down);
	add_key_binding('e', FL_CTRL, Fl_Console::kf_parenthesis_jump);
	add_key_binding(FL_BackSpace, FL_TEXT_EDITOR_ANY_STATE, kf_Backspace);

//	default_key_function(kf_Default);

}

Fl_Console::~Fl_Console() {
	clear();

//	printf("Delete Fl_Console (todo: fix the bug...)!\n");
	// I don't understand how I should the text buffer.
	// This can cause a either crash (segfault-like) or an internal error
//	buffer(NULL);
//	if (m_textBuffer) delete m_textBuffer;

	if (m_prompt) free(m_prompt);

	if (m_commandCallback) free(m_commandCallback);
	if (m_commandCallbackArg) free(m_commandCallbackArg);


	initToNothing();
}

void Fl_Console::initToNothing() {
	m_prompt = NULL;
	m_promptPos = 0;

	m_modifySelf = 0;

	m_textBuffer = NULL;

	m_nbCommandCallback = 0;
	m_commandCallbackArg = NULL;
	m_commandCallback = NULL;

	m_commandHistory = NULL;
	m_commandHistoryLength = 0;
	m_commandHistoryPos = 0;
	m_maxCommandHistory = -1;
	m_callingCallbacks = 0;
}

	// temp test
int Fl_Console::handle(int event) {
	int res = Fl_Text_Editor::handle(event);

	// never put cursor before prompt
	if (insert_position() < m_promptPos)
		insert_position(m_promptPos);
	return res;

}

void Fl_Console::max_history(int nb) {
	int i;
	if (nb < 1) return; // always at least 1 history required...
	else if (nb < m_commandHistoryLength) {
		for (i = 0; i < m_commandHistoryLength - nb; i++)
			if (m_commandHistory[i]) free(m_commandHistory[i]);

		memmove(m_commandHistory, m_commandHistory + i, sizeof(char*) * (m_commandHistoryLength-nb));

		m_commandHistoryPos -= m_commandHistoryLength - nb;
		m_commandHistoryLength = 0;
	}
	m_maxCommandHistory = nb;
}

void Fl_Console::clear() {
	clear_history();
	clear_buffer();
}

void Fl_Console::clear_history() {
	int i;
	for (i = 0; i < m_commandHistoryLength; i++)
		if (m_commandHistory[i]) free(m_commandHistory[i]);
	if (m_commandHistory) free (m_commandHistory);
	m_commandHistory = NULL;
	m_commandHistoryLength = 0;
	m_commandHistoryPos = 0;
}

void Fl_Console::clear_buffer() {
	m_modifySelf = 1;
	buffer()->text(" \n");
	m_modifySelf = 0;
	newPrompt();
//	buffer()->remove(0, buffer()->length()-1);
//	buffer()->clear_rectangular(0, 10000000, 0, 10000000);
}


int Fl_Console::newPrompt() {
	Fl_Text_Buffer* buf = buffer();
	if ((m_prompt == NULL) || (buf == NULL)) return -1;

	m_modifySelf = 1;

	// append carriage return if not at the start of a line
	int l = buf->length()-1;
	if (l < 0) l = 0;
	if ((l != buf->line_start(l)) &&
		(buf->text()[l] != '\n')) {
			buf->append("\n");
			m_diary += "\n";
	}

	// append the prompt
	buf->append(m_prompt);
	m_diary += m_prompt;

	l = buf->length()-1; // remove -1, +1?
	insert_position(l+1); // change: +1
	show_insert_position();

	m_modifySelf = 0;

	// reset the state
	m_promptPos = l+1;
	m_commandHistoryPos = m_commandHistoryLength;

	return 0;
}

int Fl_Console::commandEnter() {
	int err;

	insert_position(buffer()->length());

	char *str = command();
	if (str == NULL) return 0;
/*	if (strlen(str) < 1) {
		free(str);
		return 0;
	}*/
	buffer()->append("\n");

	// add to command history
	if (err = addCommandHistory(str)) return err;
//	printf("Add to command history '%s'\n", str);
	str = m_commandHistory[m_commandHistoryLength-1];
//	printf("Returned from to command history '%s'\n", str);


	// add to diary:
	m_diary += str;
	m_diary += "\n";

	// call callback
	callCommandCallbacks(str);
	//printf("Command: '%s'\n", str);

	return 0;
}

char *Fl_Console::command() {
	Fl_Text_Buffer* buf = buffer();
	if (buf == NULL) return NULL;
	int l = buf->length(); //-1;
	if ((m_promptPos < 0) || (m_promptPos > l)) return NULL;

	char *str = (char*)malloc(l - m_promptPos +1);
	memcpy(str, buf->text() + m_promptPos, l - m_promptPos);
	str[l - m_promptPos] = 0;

	return str;
}

int Fl_Console::command(const char *str) {
	Fl_Text_Buffer* buf = buffer();
	if (buf == NULL) return -1;
	int l = buf->length();
	if ((m_promptPos < 0) || (m_promptPos > l)) return -1;

	m_modifySelf = 1;
	buf->remove(m_promptPos, l);
	buf->append(str);
	insert_position(buf->length());
	show_insert_position();
	m_modifySelf = 0;

	return 0;
}

void Fl_Console::prompt(const char *str) {
	if (str == NULL) return;
	int l = (int)strlen(str) + 1;
	if ( (m_prompt = (char*)realloc(m_prompt, l)) == NULL) return;
	memcpy(m_prompt, str, l);
	return;
}

const char *Fl_Console::prompt() {
	return m_prompt;
}

int Fl_Console::addCommandHistory(char *str) {
	if (str == NULL) return 0;

	// check for duplicates
	if (m_commandHistoryLength &&
		(!strcmp(m_commandHistory[m_commandHistoryLength-1], str))) {
		free(str);
		return 0;
	}

	// check upper limit of history length
	if (m_commandHistoryLength == m_maxCommandHistory) {
		if (m_commandHistory[0]) free(m_commandHistory[0]);
		memmove(m_commandHistory + 0, m_commandHistory + 1, sizeof(char*) * (m_commandHistoryLength - 1));
		m_commandHistoryLength--;
	}

	// add command string to history
	m_commandHistory = (char**)realloc(m_commandHistory, sizeof(char*) * (m_commandHistoryLength + 1));
	if (m_commandHistory == NULL) return -1;
	m_commandHistory[m_commandHistoryLength++] = str;


	return 0;
}


void Fl_Console::add_command_callback(Command_Func func, void *cbArg) {
	if (func == NULL) return;

	m_nbCommandCallback++;
	m_commandCallbackArg = (void**)realloc(m_commandCallbackArg, sizeof(void*) * m_nbCommandCallback);
	m_commandCallback = (Command_Func*)realloc(m_commandCallback, sizeof(Command_Func) * m_nbCommandCallback);
	if ((m_commandCallbackArg == NULL) || (m_commandCallback == NULL))
		return;
	m_commandCallbackArg[m_nbCommandCallback - 1] = cbArg;
	m_commandCallback[m_nbCommandCallback - 1] = func;
}

void Fl_Console::remove_command_callback(Command_Func func, void *cbArg) {
	int i;
	for (i = 0; i < m_nbCommandCallback; i++) {
		if ((m_commandCallbackArg[i] == cbArg) &&
			(m_commandCallback[i] == func)) {
			memmove(m_commandCallbackArg + i, m_commandCallbackArg + i + 1, sizeof(void*) * (m_nbCommandCallback - i - 1));
			memmove(m_commandCallback + i, m_commandCallback + i + 1, sizeof(Command_Func*) * (m_nbCommandCallback - i - 1));
			m_nbCommandCallback--;
			i--;
		}
	}
}

int Fl_Console::callCommandCallbacks(const char *str) {
	int i;
	m_callingCallbacks = 1;
	for (i = 0; i < m_nbCommandCallback; i++)
		m_commandCallback[i](str, m_commandCallbackArg[i]);
	m_callingCallbacks = 0;
	return 0;
}

#define INITIAL_BUF_SIZE (128 * 1024)

int Fl_Console::cprintf(const char *fmt, va_list &ap) {
	int l;
	static char *buf = (char*)malloc(INITIAL_BUF_SIZE);
	static int bufLength = INITIAL_BUF_SIZE;
	int s = bufLength / 2 - 1;

	do {
		s = s * 2;
		if (s > bufLength) { // this reallocation loop doesn't actually work correctly on Linux, because vsnprintf() eats the 'ap' list. So I used a huge initial buffer size as a temporary measure.
			if ( (buf = (char*)realloc(buf, (bufLength = s))) == NULL) {
				fprintf(stderr, "cprintf(): memory allocation error for %d bytes\n", s);
				return -1;
			}
		}
		
	} // pay attention: while...
#ifdef WIN32
	  while ( (l = _vsnprintf(buf, s - 1, fmt, ap)) < 0);
#else
	  while ( (l = vsnprintf(buf, s - 1, fmt, ap)) >= (s-1));
#endif
	  buf[l] = 0;

	  return cprint(buf);
}

int Fl_Console::cprintf(const char *fmt, ...) {
	va_list	ap;
	va_start(ap, fmt);

	return cprintf(fmt, ap);
}

int Fl_Console::cprint(const char *str, int insert /* = 0 */) {
	if (str == NULL) return -1;
	int l = (int)strlen(str);
	if (l == 0) return 0;
	char *currentCmdString = NULL;
	
	if (!insert) {
		if (!m_callingCallbacks) {
			currentCmdString = command();
			command("");
		}
		insert_position(buffer()->length());
		buffer()->append(str);

		m_diary += str;
//		printf("New diary:\n\"%s\"\n", m_diary.c_str());
	}
	else {
		buffer()->insert(insert_position(), str);
		insert_position(insert_position() + l);
	}

	if (currentCmdString) {
		newPrompt();
		command(currentCmdString);
		free(currentCmdString);
	}

	return l;
}

int Fl_Console::handleSelect(Fl_Console *con) {
	int s, e;
	if (con->buffer()->selected()) {
		con->buffer()->selection_position(&s, &e);
		con->buffer()->unselect();

		e = (e > s) ? e : s;
		if (e > con->m_promptPos)
			con->insert_position(e);
		else con->insert_position(con->buffer()->length()-1);
		con->show_insert_position();	
	}
	return 0;
}

/*int Fl_Console::kf_Default(int key, Fl_Text_Editor* e) {
	printf("Default!\n");
	return 0;
}*/

int Fl_Console::kf_Enter(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);
	con->commandEnter();
	con->newPrompt();

	return 1;
}

int Fl_Console::kf_Up(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);
	char *str = con->command();

//	printf("%d vs %d\n", con->m_commandHistoryPos, con->m_commandHistoryLength);
	// is this code still OK?:
	if ((con->m_commandHistoryPos > 0)) {// &&
	//	((con->m_commandHistoryPos != con->m_commandHistoryLength))) {
		/*(con->m_promptPos == (con->buffer()->length()))))/* ||
		(str && (!strcmp(str, con->m_commandHistory[con->m_commandHistoryPos])))))*/
		con->m_commandHistoryPos--;
//		printf("Setting command '%s'\n", con->m_commandHistory[con->m_commandHistoryPos]);
		con->command(con->m_commandHistory[con->m_commandHistoryPos]);
	}

	if(str) free(str);

	return 1;
}
int Fl_Console::kf_Down(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);

	if (con->m_commandHistoryPos < (con->m_commandHistoryLength-1)) {
		con->m_commandHistoryPos++;
		con->command(con->m_commandHistory[con->m_commandHistoryPos]);
	}
	else if (con->m_commandHistoryPos == (con->m_commandHistoryLength-1)) {
		con->m_commandHistoryPos++;
		con->command(" ");
	}

	return 1;
}

int Fl_Console::kf_Left(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);

	if (con->insert_position() > con->m_promptPos)
		con->move_left();

	return 1;
}

int Fl_Console::kf_c_Left(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	kf_ctrl_move(key, e);
	if (con->insert_position() < con->m_promptPos) {
		con->insert_position(con->m_promptPos);
		con->show_insert_position();
	}

	return 1;
}


int Fl_Console::kf_Right(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
  	handleSelect(con);
	con->move_right();

	return 1;
}

int Fl_Console::kf_Home(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);
	
    con->insert_position(con->m_promptPos);
	con->show_insert_position();

	return 1;
}
int Fl_Console::kf_End(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);

    con->insert_position(con->buffer()->length());
	con->show_insert_position();

	return 1;
}
int Fl_Console::kf_Page_Up(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);
//	printf("Page_Up!\n");
	return 0;
}
int Fl_Console::kf_Page_Down(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;
	handleSelect(con);
//	printf("Page_Down!\n");
	return 1;
}

int Fl_Console::kf_Backspace(int key, Fl_Text_Editor* e) {
	Fl_Console *con = (Fl_Console *)e;

	int start, end, tmp;
	if (con->buffer()->selected()) {
		con->buffer()->selection_position(&start, &end);

		if (start > end) {
			tmp = start;
			start = end;
			end = tmp;
		}

		if (start < con->m_promptPos) {
			con->buffer()->unselect();
			con->insert_position(end);
			con->show_insert_position();
		}
	}
	if (con->insert_position() > con->m_promptPos)
		return Fl_Text_Editor::kf_backspace(key, e);

	return 1;
}

#define PT_NONE 0
#define PT_ROUND_OPEN 1
#define PT_ROUND_CLOSE -1
#define PT_CURLY_OPEN 2
#define PT_CURLY_CLOSE -2
#define PT_SQUARE_OPEN 3
#define PT_SQUARE_CLOSE -3

static int s_parType(char p) {
	if (p == '(') return PT_ROUND_OPEN;
	else if (p == ')') return PT_ROUND_CLOSE;
	if (p == '{') return PT_CURLY_OPEN;
	else if (p == '}') return PT_CURLY_CLOSE;
	if (p == '[') return PT_SQUARE_OPEN;
	else if (p == ']') return PT_SQUARE_CLOSE;
	return 	PT_NONE;
}

int Fl_Console::kf_parenthesis_jump(int key, Fl_Text_Editor* e) {
	const char *text = e->buffer()->text();
	int ip = e->insert_position(); // 'ip' = insert_position

	int parCount[4] = {0, 0, 0, 0};

	int p = s_parType(text[ip]); // 'p' = parenthesis

	if (p == PT_NONE) p = s_parType(text[--ip]);
	if (p == PT_NONE) return 0;

	int ps; // 'ps' = parenthesis that we search
	int dir; // the direction in which we search
	if (p < 0) {
		ps = -p;
		parCount[ps] = -1;
		dir = -1;
	}
	else {
		ps = p;
		parCount[ps] = 1;
		dir = 1;
	}

	ip += dir;

	while (text[ip] && (ip >= ((Fl_Console*)e)->m_promptPos)) { // search in text until the parenthesis we are looking for has been found
		int i = s_parType(text[ip]);
		parCount[(i < 0) ? -i : i] += (i < 0) ? -1 : 1;

		if (parCount[ps] == 0) { // found our matching parenthesis!
			e->insert_position(ip);
			return 1;
		}

		ip += dir;
	}

	return 1;
}

void Fl_Console::modifyCallback(int pos, int nInserted, int nDeleted,
                                  int nRestyled, const char* deletedText,
                                  void* cbArg) {
	Fl_Console *con = (Fl_Console *)cbArg;

	if ((!con->m_modifySelf) && (nInserted || nDeleted) && (pos < con->m_promptPos)) {
		con->m_modifySelf = 1;
		con->buffer()->undo();
		con->insert_position(con->buffer()->length());
		con->show_insert_position();
		con->m_modifySelf = 0;
	}
}


void Fl_Console::deactivate() {
	color(FL_GRAY); 
	Fl_Text_Editor::deactivate();
}
void Fl_Console::activate() {
	color(FL_WHITE);
	Fl_Text_Editor::activate();
}
