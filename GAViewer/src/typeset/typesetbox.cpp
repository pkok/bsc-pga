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
#include <ctype.h>

#include "typeset.h"
#include "typesetbox.h"
#include "openglfont.h"

//int g_nbBoxAllocated = 0;


/*
 *
 ********************* typesetBox ***************************
 *
 */
typesetBox::typesetBox(typesetState *state, int type) {
	initToNothing();

	m_type = type;

	m_font = state->font();
	m_align = state->align();
	m_mode = state->mode();
	m_fontSize = state->size();
	m_color = state->color();

	m_x = m_y = 0.0;
	m_width = m_ascent = m_descent = 0.0;
//	g_nbBoxAllocated++;
}

typesetBox::typesetBox(const typesetBox *copyBox, int type) {
	initToNothing();

	m_type = copyBox->m_type;

	m_font = copyBox->m_font;
	m_align = copyBox->m_align;
	m_mode = copyBox->m_mode;
	m_fontSize = copyBox->m_fontSize;
	m_color = copyBox->m_color;

//	g_nbBoxAllocated++;
}

typesetBox::~typesetBox() {
	int i;
//	g_nbBoxAllocated--;

	for (i = 0; i < m_nbChildren; i++)
		delete m_child[i];
	if (m_child) free(m_child);

	initToNothing();
}

void typesetBox::initToNothing() {
	m_type = tsbInvalid;
	m_nbChildren = 0;
	m_child = NULL;
	m_x = m_y = m_width = m_ascent = m_descent = -1.0;

	m_font = m_align = m_mode = -1;
	m_fontSize = -1.0;

}

double typesetBox::stretch() {
	return 0.5 * m_width; // default
}

int typesetBox::typeset(typesetState *state) {
	return 0; // default does nothing
}


int typesetBox::insertChild(int idx, typesetBox *box) {
	if ((idx < 0) || (idx > m_nbChildren)) {
		printf("typesetBox::insertChild(): invalid index '%d'\n", idx);
		return -1;
	}

	if ( (m_child = (typesetBox**)realloc(m_child, sizeof(typesetBox*) * (m_nbChildren + 1))) == NULL) {
		printf("typesetBox::insertChild(): memory allocation error\n");
		return -1;
	}

	memmove(m_child + idx + 1, m_child + idx, (m_nbChildren - idx) * sizeof(typesetBox*));
	m_nbChildren++;
	m_child[idx]  = box;

	return 0;
}

int typesetBox::addChild(typesetBox *box) {
	if ( (m_child = (typesetBox**)realloc(m_child, sizeof(typesetBox*) * (m_nbChildren + 1))) == NULL) {
		printf("typesetBox::addChild(): memory allocation error\n");
		return -1;
	}

	m_child[m_nbChildren++] = box;

	return 0;
}

typesetBox *typesetBox::lastBox() {
	if (m_nbChildren <= 0) return NULL;
	return m_child[m_nbChildren-1];
}

typesetBox *typesetBox::lastBoxOfType(const int *type) {
	int i, j;

	for (i = m_nbChildren-1; i >= 0; i--) {
		j = 0;
		while (type[j] > tsbInvalid) {
			if (m_child[i]->m_type == type[j])
				return m_child[i];
			j++;
		}
	}
	return 0;
}

typesetBox *typesetBox::lastBoxNotOfType(const int *type) {
	int i, j;

	for (i = m_nbChildren-1; i >= 0; i--) {
		j = 0;
		while (type[j] > tsbInvalid) {
			if (m_child[i]->m_type == type[j])
				break;
			j++;
		}
		if (type[j] <= tsbInvalid) return m_child[i];
	}
	return 0;

}

int typesetBox::fontBase(int font) {
	if ((font < 0) || (font > tsfMath)) return -1;

	if (font == tsfMath) font = tsfItalic;

	const int fontLength = 200;
	return (font - tsfRegular) * fontLength;
}

int *typesetBox::convertStr(const char *asciiStr) {
	int l, i;
	int *fontStr = (int *)calloc(sizeof(int), (l = (int)strlen(asciiStr)) + 1);
	int base = fontBase(m_font);

	if ((fontStr == NULL) || (base < 0)) {
		if (fontStr) free(fontStr);
		return NULL;
	}

	if (m_font == tsfMath) { // do conversion based on alpha or other
		for (i = 0; i < l; i++) {
			if (isalpha(asciiStr[i]))
				fontStr[i] = (unsigned char)asciiStr[i] + fontBase(tsfItalic);
			else fontStr[i] = (unsigned char)asciiStr[i] + fontBase(tsfRegular);
		}
	}
	else for (i = 0; i < l; i++)
		fontStr[i] = (unsigned char)asciiStr[i] + base;

	fontStr[i] = 0;

	return fontStr;
}

int *typesetBox::convertChr(int c) {
	if ((c < 0) || (c > 255)) return NULL;
	char str[2] = {c, 0};
	return convertStr(str);
}

int typesetBox::fontStrlen(const int *fontStr) {
	if (fontStr == NULL) return 0;
	int i = 0;
	while (fontStr[i]) i++;
	return i;
}

int typesetBox::strSize(typesetState *state, const int *fontStr, double &width, double &ascent, double &descent) {
	if (fontStr == NULL) width = ascent = descent = 0.0;
	else {
		ascent = (1.0 - state->m_fontDescent) * m_fontSize;
		descent = -state->m_fontDescent * m_fontSize;
		//height = m_fontSize;
		width = m_fontSize * oglfStringWidth(fontStr);
	}
	return 0;
}

int typesetBox::removeChild(int idx) {
	if ((idx < 0) || (idx >= m_nbChildren)) return 0;

	if (m_child[idx]) delete m_child[idx];

	m_nbChildren--;
	memmove(m_child + idx, m_child + idx + 1, sizeof(typesetBox*) * (m_nbChildren - idx));

	return 0;
}

int typesetBox::removeChild(const typesetBox *ptr) {
	int i;
	for (i = m_nbChildren-1; i >= 0 ;i--)
		if (m_child[i] == ptr)
			return removeChild(ptr);
	return -1;
}

int typesetBox::setPos(double x, double y) {
	m_x = x;
	m_y = y;

	return 0;
}

int typesetBox::eqnOperator() {
	return ((m_type == tsbWord) && (m_mode == tsmEquation) && (((tsWordBox*)this)->eqnOperator()));
}

int typesetBox::whiteSpace() {
	return (m_type == tsbWhiteSpace);
}


/*
 *
 ********************* tsVBox ***************************
 *
 */
tsVBox::tsVBox(typesetState *state) : typesetBox(state, tsbV)  {
	initToNothing();
}

tsVBox::~tsVBox() {
	initToNothing();
}

void tsVBox::initToNothing() {

}

int tsVBox::setup(typesetState *state, struct fpNode_s *rootNode) {
	tsHBox *HBox;
	int err;
	double h = 0;
	double w = 0;

	struct fpNode_s *currentNode = fpDescentLeft(rootNode);
	struct fpNode_s *nextNode = NULL;

	// setup all HBoxes
	do {
		if (nextNode) currentNode = nextNode;
		nextNode = NULL;
		HBox = new tsHBox(state);
		if (err = HBox->setup(state, currentNode, &nextNode, rootNode)) {
			delete HBox;
			break;
		}
		HBox->setAlignment(); 
		HBox->spaceEqnOperators(state);
		HBox->deleteTrailingWhiteSpace();
		HBox->computeSize();
		addChild(HBox);
		w = dmax(w, HBox->m_width);
		h += HBox->m_ascent - HBox->m_descent;
	} while (nextNode);

	if (m_nbChildren && m_child[0]) {
		m_ascent = m_child[0]->m_ascent;
		m_descent = m_ascent - h;
		m_width = w;
	}
	else m_ascent = m_descent = 0.0; 

	return 0;
}

int tsVBox::typeset(typesetState *state, double maxWidth /*= -1.0*/) {
	tsHBox *HBox, *HBox2;
	int err = 0, i, j, k;

	state->pushTrans(m_x, m_y);

	// make this next stuff a function for typesetBox class???
	double x, y, h;
	if (maxWidth > 0.0) { // If there is a maximum width, spread long HBoxes over multiple HBoxes
//		maxWidth = 0.0;
		for (i = 0; i < m_nbChildren; i++) {
			x = 0.0;

			// find out how much children will fit in an HBox
			HBox = (tsHBox*)m_child[i];
			for (j = 0; j < HBox->m_nbChildren; j++) {
				if ((j == 0) || (x + HBox->m_child[j]->m_width <= maxWidth))
					x += HBox->m_child[j]->m_width;
				else break;
			}
	
			if (j != HBox->m_nbChildren) { // transfer these children to the new HBox
				HBox2 = new tsHBox(HBox);
				for (k = 0; k < j; k++) {
					HBox2->addChild(HBox->m_child[0]);
					HBox->m_child[0] = NULL;
					HBox->removeChild(0);
				}
				insertChild(i, HBox2);
			HBox2->deleteTrailingWhiteSpace();
			HBox2->computeSize();
			}
			else HBox->computeSize();
		}
	}
	else { // Otherwise, measure the longest HBox, set that as the max width
		maxWidth = 0.0;
		for (i = 0; i < m_nbChildren; i++) {
			x = 0.0;
			HBox = (tsHBox*)m_child[i];
			HBox->computeSize();
			maxWidth = dmax(HBox->m_width, maxWidth);
		}
	}
//	printf("maxWidth: %f\n", maxWidth);

	// typeset all HBoxes
	h = 0.0;
	y = m_ascent;
	for (i = 0; i < m_nbChildren; i++) {
		HBox = (tsHBox*)m_child[i];
		y -= HBox->m_ascent;
		HBox->m_maxWidth = maxWidth;
		HBox->setPos(0.0, y);
		HBox->typeset(state);
		y -= -HBox->m_descent;
//		h += HBox->m_ascent-HBox->m_descent;
	}

//	m_ascent = -y;
	m_descent = y;
	m_width = maxWidth;

	state->popTrans();

	return err;
}


/*
 *
 ********************* tsHBox ***************************
 *
 */
tsHBox::tsHBox(typesetState *state) : typesetBox(state, tsbH) {
	initToNothing();
}

tsHBox::tsHBox(const tsHBox *copyBox) : typesetBox(copyBox, tsbH) {
	initToNothing();
}


tsHBox::~tsHBox() {
	initToNothing();
}

void tsHBox::initToNothing() {
	m_maxWidth = -1.0;
}

int tsHBox::typeset(typesetState *state) {
	state->pushTrans(m_x, m_y);

	int i;
	double x = 0.0, y = 0.0, w;
	double wd, s;

	// position all children
	switch (m_align) {
	case tsaLeft:
		for (i = 0; i < m_nbChildren; i++) {
			m_child[i]->setPos(x, y);
			x += m_child[i]->m_width;
		}
		break;
	case tsaRight:
		for (i = 0; i < m_nbChildren; i++) {
			m_child[i]->setPos(m_maxWidth - m_width + x, y);
			x += m_child[i]->m_width;
		}
		break;
	case tsaCenter:
		for (i = 0; i < m_nbChildren; i++) {
			m_child[i]->setPos((m_maxWidth - m_width) / 2.0 + x, y);
			x += m_child[i]->m_width;
		}
		break;
	case tsaJustify:
		// compute how much to grow
		wd = m_maxWidth - m_width;

		// compute how much stretch there is.
		s = 1e-10;
		for (i = 0; i < m_nbChildren; i++)
			s += m_child[i]->stretch();
		
		// position/resize all children
		wd = wd / s;
		for (i = 0; i < m_nbChildren; i++) {
			w = m_child[i]->m_width + wd * m_child[i]->stretch();
			m_child[i]->m_width = w;
			m_child[i]->setPos(x, y);
			x += w;
		}
		break;
	}


	// typeset all children
	for (i = 0; i < m_nbChildren; i++) {
		m_child[i]->typeset(state);
	}

	state->popTrans();

	return 0;
}


int tsHBox::setup(typesetState *state, 
				  struct fpNode_s *currentNode, struct fpNode_s **nextNode, 
				  struct fpNode_s *rootNode) {
	int err;
	struct fpNode_s *rhc = NULL; // right hand child (of sentence)
	int newLine = 0;

	typesetBox *tsBox;
	tsWordBox *wordBox = NULL;
	tsScriptBox *scriptBox = NULL;

	do {
		*nextNode = NULL;

		if (currentNode->type != fpnSentence) {
			printf("tsHBox::setup(): can only process 'sentence' nodes, not nodes of type '%d':\n", currentNode->type);
			fontParsePrintInput(currentNode->inputIdx, 16, 16);
			return -1; // the main box can only process sentences
		}

		if ( (currentNode->nbChildren >= 2) && ((rhc = currentNode->child[1]) != NULL)) {
			switch(rhc->type) {
			case fpnWordWord:
				// create a new word box, add to this hbox
				wordBox = new tsWordBox(state, rhc);
				// todo: in non-script math mode, detect operators, add operator spacing
				addChild(wordBox);
				break;
			case fpnWordWhiteSpace:
				// create a new white space box, add to this hbox
				if (state->mode() == tsmText) {
					if (((tsBox = lastBox()) == NULL) || 
						(tsBox->m_type == tsbWhiteSpace)) break; // don't add whitespace if there already is whitespace
					addChild(new tsWhiteSpaceBox(state, rhc)); 
				}
				break;
			case fpnWordNumber:
				addChild(new tsNumberBox(state, rhc));
				break;
			case fpnWordSpecialChar:
				// create a new word box, add to this hbox
				addChild(new tsWordBox(state, rhc)); // in math mode, this constructor should identify operators and add spacing appropriately
				break;
			case fpnWordSuperscript:
				// scans backward, deleting all nodes not suitable for script, returns suitable first box found, turns it into a script box if neccessary 
				if (err = getScriptBox(state, &scriptBox)) return err;
				scriptBox->addSuperscript(state, rhc);
				break;
			case fpnWordSubscript:
				if (err = getScriptBox(state, &scriptBox)) return err;
				scriptBox->addSubscript(state, rhc);
				break;
			case fpnWordCommand:
				// handle this complicated stuff in a seperate function
				if (err = setupCommand(state, currentNode, nextNode)) return err; // nextNode can change
				break;
			case fpnWordCommandNoOption:
				if (err = setupCommandNoOption(state, currentNode, nextNode, &newLine)) return err; // nextNode can change
				break;
			case fpnWordCommandArg:
				printf("tsHBox::setup(): unsubstituted command argument '%d' (ignoring): \n", rhc->nb);
				fontParsePrintInput(rhc->inputIdx, 16, 16);
				break;
			default:
				printf("tsHBox::setup(): unknown node of type '%d':\n", rhc->type);
				fontParsePrintInput(rhc->inputIdx, 16, 16);
				return -1;
			}
		}
		else {
			// NULL sentence (ignore, these are side effects of some tree manipulations)
		}

		if ((!*nextNode) && currentNode->flags) {
			// handle popping of state
			if (currentNode->flags & fpfPopFont) {
				state->popFont();
			}
			if (currentNode->flags & fpfPopMode) {
				state->popMode();
			}
			if (currentNode->flags & fpfPopAlign) {
				state->popAlign();
			}
			if (currentNode->flags & fpfPopSize) {
				state->popSize();
			}
			if (currentNode->flags & fpfPopColor) {
				state->popColor();
			}
		}	

		// go to next node to be processed, or break loop
		if (*nextNode) currentNode = *nextNode;
		else if ((currentNode == rootNode) || (currentNode->parent == NULL)) break; // root node found
		else currentNode = currentNode->parent;

		if (newLine) {
			*nextNode = currentNode;
			return 0;
		}


	} while (1); // loop until we are all the way up the parse tree

	return 0;
}


int tsHBox::setupCommand(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode) {
	struct fpNode_s *rhc = currentNode->child[1]; // right hand child (of sentence)
	struct fpNode_s *cmdNode;
	int err, c;
	const char *cmdStr = rhc->str+1;
	struct fpNode_s *option = NULL, *sentence = NULL, *word = NULL;

	// new custom command
	if (!strcmp(cmdStr, "newcommand")) {
		return processNewCommand(state, currentNode);
	}

	// new custom color
	else if (!strcmp(cmdStr, "newcolor")) {
		return processNewColor(state, currentNode);
	}

	// use of custom command
	else if (cmdNode = state->getCommand(cmdStr)) {
		return processCustomCommand(state, currentNode, nextNode, cmdNode);
	}

	// color change commands
	else if ( (c = state->getColor(cmdStr)) >= 0) {
		return setColor(state, currentNode, nextNode, c);
	}

	// font command
	else if ((!strcmp(cmdStr, "regular")) || (!strcmp(cmdStr, "fr"))) {
		if (err = setFont(state, currentNode, nextNode, tsfRegular)) return err;
	}
	else if ((!strcmp(cmdStr, "bold")) || (!strcmp(cmdStr, "fb"))) {
		if (err = setFont(state, currentNode, nextNode, tsfBold)) return err;
	}
	else if ((!strcmp(cmdStr, "italic")) || (!strcmp(cmdStr, "fi"))) {
		if (err = setFont(state, currentNode, nextNode, tsfItalic)) return err;
	}
	else if ((!strcmp(cmdStr, "greek")) || (!strcmp(cmdStr, "fg"))) {
		if (err = setFont(state, currentNode, nextNode, tsfGreek)) return err;
	}

	// scale command
	else if (!strcmp(cmdStr, "scale")) {
		if (err = scale(state, currentNode, nextNode)) return err;
	}

	// alignment command
	else if ((!strcmp(cmdStr, "left")) || (!strcmp(cmdStr, "al"))) {
		if (err = setAlignment(state, currentNode, nextNode, tsaLeft)) return err;
	}
	else if ((!strcmp(cmdStr, "right")) || (!strcmp(cmdStr, "ar"))) {
		if (err = setAlignment(state, currentNode, nextNode, tsaRight)) return err;
	}
	else if ((!strcmp(cmdStr, "center")) || (!strcmp(cmdStr, "ac"))) {
		if (err = setAlignment(state, currentNode, nextNode, tsaCenter)) return err;
	}
	else if ((!strcmp(cmdStr, "justify")) || (!strcmp(cmdStr, "aj"))) {
		if (err = setAlignment(state, currentNode, nextNode, tsaJustify)) return err;
	}

	// mode change commands
	else if (!strcmp(cmdStr, "txt")) {
		if (err = setMode(state, currentNode, nextNode, tsmText)) return err;
	}
	else if (!strcmp(cmdStr, "eqn")) {
		if (err = setMode(state, currentNode, nextNode, tsmEquation)) return err;
	}

	// white space commands, carriage return
	else if (!strcmp(cmdStr, "ws")) {
		if (err = getFirstOption(rhc->child[0], &option, 1, 
			"tsHBox::setupCommand()", "ws")) return err;
		if ((option->nbChildren == 0) || 
			(option->child[0]->type != fpnSentence)) return -1;
		sentence = fpDescentLeft(option->child[0]);
		if (sentence != option->child[0]) {
			printf("tsHBox::setupCommand(): warning: to many arguments to whitespace command:\n");
			fontParsePrintInput(sentence->inputIdx, 16, 16);
		}
		word = sentence->child[1];
		if ((word->type != fpnWordWord) && 
			(word->type != fpnWordNumber)) {
			printf("tsHBox::setupCommand(): invalid whitespace width:\n");
			fontParsePrintInput(word->inputIdx, 16, 16);
			return -1;
		}

		tsWhiteSpaceBox *whiteSpaceBox;
		double width = atof(word->str);
		if (width > 0.0) {
			addChild(whiteSpaceBox = new tsWhiteSpaceBox(state, width));
			whiteSpaceBox->m_forced = 1;
		}
		else {
			printf("tsHBox::setupCommand(): invalid whitespace width '%s':\n", word->str);
			fontParsePrintInput(word->inputIdx, 16, 16);
		}
	}

	else if (!strcmp(cmdStr, "tabular")) {
		addChild(new tsTabularBox(state, currentNode));
		return 0;
	}

	// 'construction' commands (equation mode only)
	else if (state->mode() == tsmEquation) {
		if (!strcmp(cmdStr, "frac")) {
			addChild(new tsFracBox(state, currentNode));
			return 0;
		}
		else if (!strcmp(cmdStr, "sqrt")) {
			addChild(new tsSqrtBox(state, currentNode));
			return 0;
		}
		else if ((!strcmp(cmdStr, "hat")) || (!strcmp(cmdStr, "widehat")) ||
			(!strcmp(cmdStr, "tilde")) || (!strcmp(cmdStr, "widetilde")) ||
			(!strcmp(cmdStr, "bar")) || (!strcmp(cmdStr, "widebar"))) {
			addChild(new tsHatBox(state, currentNode));
			return 0;
		}
		else if (!strcmp(cmdStr, "par")) {
			addChild(new tsParBox(state, currentNode));
			return 0;
		}
		// todo: sin cos exp??
		else {
			// unknown command in equation mode
			printf("tsHBox::setupCommand(): Unknown command '%s' in mode '%s':\n", cmdStr, (state->mode() == tsmEquation) ? "equation" : "text");
			fontParsePrintInput(rhc->inputIdx, 16, 16);
			return 0;
		}
	}

	// unknown command (at least in 'general' (->text) mode)
	else {
		printf("tsHBox::setupCommand(): Unknown command '%s' in mode '%s':\n", cmdStr, (state->mode() == tsmEquation) ? "equation" : "text");
		fontParsePrintInput(rhc->inputIdx, 16, 16);
		return 0;
	}

	return 0;
}

static struct {
	const char *name;
	int chr;
}s_greekToSymbol[] = {
	{"alpha", 'a'},
	{"beta", 'b'},
	{"gamma", 'g'},
	{"delta", 'd'},
	{"epsilon", 'e'},
	{"zeta", 'z'},
	{"eta", 'h'},
	{"theta", 'q'},
	{"iota", 'i'},
	{"kappa", 'k'},
	{"lambda", 'l'},
	{"mu", 'm'},
	{"nu", 'n'},
	{"xi", 'x'},
	{"omikron", 'o'},
	{"pi", 'p'},
	{"rho", 'r'},
	{"sigma", 's'},
	{"tau", 't'},
	{"upsilon", 'u'},
	{"phi", 'f'},
	{"chi", 'c'},
	{"psi", 'y'},
	{"omega", 'w'},
	{NULL, -1}
};
int typesetBox::lookupGreekSymbol(const char *name) {
	int i = 0, l = (int)strlen(name), upper = 0;
	if ((l == 0) || (l > 15)) return -1;
	char nc[16];

	strcpy(nc, name);
	if (isupper(nc[0])) {
		upper = 1;
		nc[0] -= 'A' - 'a';
	}

	while (s_greekToSymbol[i].name) {
		if (!strcmp(nc, s_greekToSymbol[i].name))
			return fontBase(tsfGreek) + s_greekToSymbol[i].chr + upper * ('A' - 'a');
		i++;
	}

	return -1;
}

int typesetBox::lookupSpecialSymbol(const char *name) {
	const struct {
		char name[16];
		int c;
	} table[] = { // if you add an operator, always add it to the 's_operatorIdx' array as well!
		{"gp", 800},
		{"ip", 801},
		{"op", 802},
		{"lc", 803},
		{"rc", 804},
		{"infty", 805},
		{"inf", 805},
		{"cp", 806},
		{"end", -1}
	};

	int i = 0;
	while (table[i].c >= 0) {
		if (!strcmp(name, table[i].name)) return table[i].c;
		i++;
	}

	return -1;
}


int tsHBox::setupCommandNoOption(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int *newLine) {
	struct fpNode_s *rhc = currentNode->child[1]; // right hand child (of sentence)
	int c;
	const char *cmdStr = rhc->str+1;
	struct fpNode_s *cmdNode;
	
	if (cmdNode = state->getCommand(cmdStr)) { // use of custom command
		return processCustomCommand(state, currentNode, nextNode, cmdNode);
	}
	else if ( (c = lookupGreekSymbol(cmdStr)) >= 0) {
		return addChild(new tsWordBox(state, c));
	}
	else if ( (c = lookupSpecialSymbol(cmdStr)) >= 0) {
		return addChild(new tsWordBox(state, c));
	}
	else if (!strcmp(cmdStr, "ws")) { // white space command
		return addChild(new tsWhiteSpaceBox(state, rhc)); 
	}
	else if ((!strcmp(cmdStr, "newline")) || (!strcmp(cmdStr, "\\"))) { // new line command
		*newLine = 1;
		return 0;
	}
	else if ((!strcmp(cmdStr, "backslash")) || (!strcmp(cmdStr, "bs"))) { // new line command
		return addChild(new tsWordBox(state, "\\"));
	}
	else {
		printf("tsHBox::setupCommandNoOption(): Unknown optionless command '%s' in mode '%s'\n", cmdStr, (state->mode() == tsmEquation) ? "equation" : "text");
		fontParsePrintInput(rhc->inputIdx, 16, 16);
		return 0;
	}

	return 0;
}


int tsHBox::computeSize() {
	int i;
	double ascent = 0.0, descent = 0.0;
	m_width = m_ascent = m_descent = 0.0;

	for (i = 0; i < m_nbChildren; i++) {
		m_width += m_child[i]->m_width;

		ascent = m_child[i]->m_y + m_child[i]->m_ascent;
		descent = m_child[i]->m_y + m_child[i]->m_descent;

		m_descent = dmin(m_descent, descent);
		m_ascent = dmax(m_ascent, ascent);
	}

	return 0;
}


// scans backward, deleting all nodes not suitable for script, 
// returns suitable first box found, turns it into a script box if neccessary 
// returns negative on error
int tsHBox::getScriptBox(typesetState *state, tsScriptBox **scriptBox) {
	int i = m_nbChildren - 1;
	int type;

	for (; i >= 0; i--) {
		type = m_child[i]->m_type;
		if ((type == tsbWhiteSpace) && 
			(!((tsWhiteSpaceBox*)m_child[i])->m_forced)) removeChild(i);
		else break;
	}
	if (i < 0) return -1;
	
	// if this already is a script box, return it
	if (m_child[i]->m_type == tsbScript) {
		*scriptBox = (tsScriptBox *)m_child[i];
		return 0;
	}

	m_child[i] = *scriptBox = new tsScriptBox(state, m_child[i]);

	return 0;
}


int tsHBox::setFont(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int font) {
	int err;
	struct fpNode_s *lastNode;
	if (err = handleFAMCommand(currentNode, nextNode, &lastNode, "font"))
		return 0; // this part of the sentence is simply ignored...

	// change the font
	//if (lastNode->parent)
	lastNode->flags |= fpfPopFont; // make sure the font gets popped one the sentence has been parsed
	state->pushFont(font); // push the font

	return 0;
}

int tsHBox::setAlignment(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int alignment) {
	int err;
	struct fpNode_s *lastNode;
	if (err = handleFAMCommand(currentNode, nextNode, &lastNode, "alignment"))
		return 0; // this part of the sentence is simply ignored...

	// change the alignment
	//if (lastNode->parent)
	lastNode->flags |= fpfPopAlign; // make sure the alignment gets popped one the sentence has been parsed
	state->pushAlign(alignment); // push the alignment

	return 0;
}

int tsHBox::setMode(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int mode) {
	int err;
	struct fpNode_s *lastNode;
	if (err = handleFAMCommand(currentNode, nextNode, &lastNode, "mode"))
		return 0; // this part of the sentence is simply ignored...

	//printf("setMode %d\n", mode);
	// change the mode
	if (mode == tsmEquation) {
		lastNode->flags |= fpfPopMode | fpfPopFont; // make sure the mode + font gets popped one the sentence has been parsed
		state->pushMode(mode); // push the mode
		state->pushFont(tsfMath); // push the font
	}
	else if (mode == tsmText) {
		lastNode->flags |= fpfPopMode | fpfPopFont; // make sure the mode + font gets popped one the sentence has been parsed
		state->pushMode(mode); // push the mode
		state->pushFont(tsfRegular); // push the font
	}
	else {
		lastNode->flags |= fpfPopMode; // make sure the mode gets popped one the sentence has been parsed
		state->pushMode(mode); // push the mode
	}
	return 0;
}

int tsHBox::setColor(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int colorIdx) {
	int err;
	struct fpNode_s *lastNode;
	if (err = handleFAMCommand(currentNode, nextNode, &lastNode, "color"))
		return err;

	// change the mode
	lastNode->flags |= fpfPopColor; // make sure the color gets popped one the sentence has been parsed
	state->pushColor(colorIdx); // push the color

	return 0;
}

int typesetBox::getFirstOption(struct fpNode_s *optionListNode, struct fpNode_s **firstOption, 
						   int warnMultiple, const char *callStr, const char *cmdStr) {
	// get the option 
	if (warnMultiple && (optionListNode->child[0] != NULL)) {
		printf("%s: warning: too many options in option list for %s command:\n", callStr, cmdStr);
		fontParsePrintInput(optionListNode->inputIdx, 16, 16);
	}
	*firstOption = fpDescentLeft(optionListNode);
	if ((*firstOption)->child[1] == NULL) {
		*firstOption = NULL;
		printf("%s: error: no option for %s command:\n", callStr, cmdStr);
		fontParsePrintInput(optionListNode->inputIdx, 16, 16);
		return -1;
	}
	*firstOption = (*firstOption)->child[1];

	return 0;
}

// returns the 'n' options in an optionlist
// if 'warn' is > 0, a warning is printed if there are to few or to much options in the list, and an error is returned
// if warn is < 0, an error is never returned
// 'callStr' (the calling function) and 'cmdStr' (the command being processed) are used for error messages
// 'nb' is used to receive the required number of options and to return the number of options found
int typesetBox::getOptions(int &nb, struct fpNode_s *optionListNode, struct fpNode_s *option[], 
					   int warn, const char *callStr, const char *cmdStr) {
	struct fpNode_s *currentOption = fpDescentLeft(optionListNode);
	int i = 0, j, endOfListReached = 0;

	if (optionListNode == NULL) return -1;
	if (nb == 0) return 0;

	// loop through all options, store them in the array supplied by the user
	do {
		option[i++] = currentOption->child[1];
		if (currentOption == optionListNode) {
			endOfListReached = 1;
			break;
		}
		currentOption = currentOption->parent;
	} while (i < nb);
	j = i;
	for (; j < nb; j++) option[j] = NULL;


	// check number of options is correct
	if (i < nb) { // too little
		if (warn > 0) {
			printf("%s: warning: too little options in option list for %s command:\n", callStr, cmdStr);
			fontParsePrintInput(optionListNode->inputIdx, 16, 16);
		}
		nb = i;
		return (warn < 0) ? 0 : -1;
	}
	if ((!endOfListReached) && warn) {// too many
		printf("%s: warning: too many options in option list for %s command:\n", callStr, cmdStr);
		fontParsePrintInput(optionListNode->inputIdx, 16, 16);
	}

	return 0;
}

int tsHBox::handleFAMCommand(struct fpNode_s *currentNode, 
							struct fpNode_s **nextNode,
							struct fpNode_s **lastNode,
							const char *cmdStr) {
	struct fpNode_s *commandNode = currentNode->child[1]; // right hand child of sentence
	struct fpNode_s *optionListNode = commandNode->child[0]; // left hand child of command
	struct fpNode_s *optionNode; // the option which has the sentence in it
	struct fpNode_s *sentenceNode; 
	struct fpNode_s *lastSentenceNode; 
	int err;

	// get the option 
	if (err = getFirstOption(optionListNode, &optionNode, 1, "tsHBox::handleFAMCommand()", cmdStr))
		return err;

	// get first sentence and last sentence node
	sentenceNode = optionNode->child[0];
	if ((sentenceNode == NULL) || (sentenceNode->type != fpnSentence)) {
		printf("tsHBox::handleFAMCommand(): warning: %s command with no effect:\n", cmdStr);
		fontParsePrintInput(commandNode->inputIdx, 16, 16);
		return -1;
	}
	lastSentenceNode = fpDescentLeft(sentenceNode);

	// set the return data
	*nextNode = lastSentenceNode;
	*lastNode = currentNode;

	// update the tree (insert sentence into main tree)
	lastSentenceNode->child[0] = currentNode->child[0];
	if (currentNode->child[0])
		currentNode->child[0]->parent = lastSentenceNode;

	sentenceNode->parent = currentNode;
	currentNode->child[0] = sentenceNode;

	// get rid of everything we don't need anymore
	optionNode->child[0] = NULL; // otherwise we release the sentence...
	fpNodeFree(commandNode);
	currentNode->child[1] = NULL; // remove the link to 'commandNode'

	return 0;
}


int tsHBox::scale(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode) {
	int err;
	struct fpNode_s *lastNode;
	struct fpNode_s *commandNode = currentNode->child[1]; // right hand child of sentence
	struct fpNode_s *optionListNode = commandNode->child[0]; // left hand child of command
	struct fpNode_s *optionNode; // the option which has the sentence in it
	struct fpNode_s *sentenceNode; 
	struct fpNode_s *lastSentenceNode; 

	// get the 2 options
	struct fpNode_s *option[2];
	int nb = 2;
	if (err = getOptions(nb, optionListNode, option, 1, "tsHBox::scale()", "scale"))
		return 0;

	// get the scale
	optionNode = option[0];
	if ((optionNode->nbChildren == 0) || 
		(optionNode->child[0]->type != fpnSentence)) return -1;
	struct fpNode_s *sentence = fpDescentLeft(optionNode->child[0]);
	struct fpNode_s *word = sentence->child[1];
	if ((word->type != fpnWordWord) && 
		(word->type != fpnWordNumber)) return -1;
	double s = atof(word->str);
	if (s <= 0.0) {
		printf("tsHBox::scale(): invalid scaling '%s'\n", word->str);
		fontParsePrintInput(commandNode->inputIdx, 16, 16);
		return 0;
	}


	// get first sentence and last sentence node
	optionNode = option[1];
	sentenceNode = optionNode->child[0];
	if ((sentenceNode == NULL) || (sentenceNode->type != fpnSentence)) {
		printf("tsHBox::scale(): warning: scale command with no effect:\n");
		fontParsePrintInput(commandNode->inputIdx, 16, 16);
		return 0;
	}
	lastSentenceNode = fpDescentLeft(sentenceNode);

	// set the return data
	*nextNode = lastSentenceNode;
	lastNode = currentNode;

	// update the tree (insert sentence into main tree)
	lastSentenceNode->child[0] = currentNode->child[0];
	if (currentNode->child[0])
		currentNode->child[0]->parent = lastSentenceNode;

	sentenceNode->parent = currentNode;
	currentNode->child[0] = sentenceNode;

	// get rid of everything we don't need anymore
	optionNode->child[0] = NULL; // otherwise we release the sentence...
	fpNodeFree(commandNode);
	currentNode->child[1] = NULL; // remove the link to 'commandNode'

	// change the font
	//if (lastNode->parent)
	lastNode->flags |= fpfPopSize; // make sure the size gets popped one the sentence has been parsed
	state->pushSize(s * state->size()); // push the size

	return 0;
}

// todo: allow for forced whitespace?
int tsHBox::deleteTrailingWhiteSpace() {
	int i = m_nbChildren - 1, err;
	while ((i >=0) && (m_child[i]->m_type == tsbWhiteSpace) && (!((tsWhiteSpaceBox*)m_child[i])->m_forced))
		if (err = removeChild(i--)) return err;
	return 0;
}

int tsHBox::setAlignment() {
	if (m_nbChildren)
		m_align = m_child[m_nbChildren-1]->m_align;

	return 0;
}

int tsHBox::spaceEqnOperators(typesetState *state) {
	int i, err;

	// todo: find out what going on here...
	for (i = 0; i < m_nbChildren; i ++) {
		if (m_child[i]->eqnOperator()) {
			if ((i > 0) && (!(m_child[i-1]->eqnOperator() || m_child[i-1]->whiteSpace()))) {
				// add white space before operator
				if (err = insertChild(i, new tsWhiteSpaceBox(state, 0.1))) return err;
				i++;
			}

			if ((i + 1) < m_nbChildren) {
				if (!(m_child[i+1]->eqnOperator() || m_child[i+1]->whiteSpace())) {
					if (err = insertChild(i+1, new tsWhiteSpaceBox(state, 0.1))) return err;
					i += 2.0; // if this 2.0 is changed to '2', this function does not work correctly with visual C++ 6.0 release build. Is something wrong with the stack?
				}
			}
		}
	}
	return 0;
}


int tsHBox::processNewCommand(typesetState *state, struct fpNode_s *node) {
	struct fpNode_s *cmdNode = node->child[1];
	if (cmdNode == NULL) return -1;

	// get the options (first option is new command name, second option is substitution sentence)
	struct fpNode_s *option[2];
	int nb = 2;
	if ((getOptions(nb, cmdNode->child[0], option, 1, "tsHBox::processNewCommand()", "newcommand")) || (nb != 2)) return -1;

	// retrieve the name of the command
	struct fpNode_s *cmdNameNode = fpDescentLeft(option[0]->child[0]);
	if (( (cmdNameNode = cmdNameNode->child[1]) == NULL) ||
		(cmdNameNode->type != fpnWordCommandNoOption)) {
		printf("tsHBox::processNewCommand(): no command name found in newcommand:\n");
		fontParsePrintInput(cmdNode->inputIdx, 16, 16);
		return 0; // simply ignore newcommand
	}

	// set the command
	struct fpNode_s *cmdSentenceNode;
	if ( (cmdSentenceNode = option[1]->child[0]) == NULL) {
		printf("tsHBox::processNewCommand(): no command sentence found in newcommand:\n");
		fontParsePrintInput(cmdNode->inputIdx, 16, 16);
		return 0; // simply ignore newcommand
	}

	// steal the child from the option (this prevents memory release when the original sentence is freeed)
	option[1]->child[0] = NULL;

	// check for infinite recursion
	if ((fpNodeFindTypeStr(cmdSentenceNode, fpnWordCommand, cmdNameNode->str)) ||
		(fpNodeFindTypeStr(cmdSentenceNode, fpnWordCommandNoOption, cmdNameNode->str))) {
		printf("tsHBox::processNewCommand(): ignoring new command '%s': infinite recursion detected:\n", cmdNameNode->str + 1);
		fontParsePrintInput(cmdSentenceNode->inputIdx, 16, 16);
		fpNodeFree(cmdSentenceNode);
		return 0;
	}

	// set the new command
	state->setCommand(cmdNameNode->str + 1, cmdSentenceNode);

	return 0;
}

int tsHBox::processNewColor(typesetState *state, struct fpNode_s *currentNode) {
	struct fpNode_s *cmdNode = currentNode->child[1];
	if (cmdNode == NULL) return -1;

	// get the options (first option is new command name, second option is substitution sentence)
	struct fpNode_s *option[1];
	int nb = 1;
	if ((getOptions(nb, cmdNode->child[0], option, 1, "tsHBox::processNewColor()", "newcolor")) || (nb != 1)) return -1;

	// retrieve the name of the color
	struct fpNode_s *node = fpDescentLeft(option[0]->child[0]), *colorNameNode;
	if (( (colorNameNode = node->child[1]) == NULL) ||
		(colorNameNode->type != fpnWordWord)) {
		printf("tsHBox::processNewColor(): no color name found in newcolor:\n");
		fontParsePrintInput(cmdNode->inputIdx, 16, 16);
		return 0; // simply ignore newcommand
	}

	int rgbIdx = 0;
	float rgb[3] = {0.0, 0.0, 0.0};
	// retrieve rgb
	while (rgbIdx < 3) {
		// ascent the tree
		node = node->parent;
		if (node == option[0]) break;

		// check type of node
		if (node->child[1] == NULL) continue;
		else if (node->child[1]->type != fpnWordNumber) {
			if (node->child[1]->type != fpnWordWhiteSpace) {
				printf("tsHBox::processNewColor(): ignoring non number input for rgb values:\n");
				fontParsePrintInput(node->child[1]->inputIdx, 16, 16);
			}
			continue;
		}

		// get value
		rgb[rgbIdx++] = (float)atof(node->child[1]->str);
	}
	if (node != option[0]->child[0]) {
		printf("tsHBox::processNewColor(): ignoring extra input for rgb values:\n");
		fontParsePrintInput(node->inputIdx, 16, 16);
	}
	else if (rgbIdx < 3) {
		printf("tsHBox::processNewColor(): to few rgb values, setting unspecified values to 0.0:\n");
		fontParsePrintInput(node->inputIdx, 16, 16);
	}

	state->setColor(colorNameNode->str, rgb[0], rgb[1], rgb[2]);

	return 0;
}


int tsHBox::processCustomCommand(typesetState *state, struct fpNode_s *currentNode, 
								 struct fpNode_s **nextNode, struct fpNode_s *cmdNode) {

	// get the options (0...9)
	if (currentNode->child[1] == NULL) return -1;
	struct fpNode_s *option[9];
	int nbOptions = 9, err;
	if (currentNode->child[1]->child[0]) { // get all options from the option list
		if ( (err = getOptions(nbOptions, currentNode->child[1]->child[0], option, -1, "tsHBox::processCustomCommand()", cmdNode->str)) < 0) return err;
	}
	else nbOptions = 0;

	// duplicate the command node
	cmdNode = fpNodeDuplicate(cmdNode);
	fpNodeSetInputIdx(cmdNode, currentNode->inputIdx);

	// substitute all commands (and check for inifite recursion)
	if (err = fpNodeSubstituteCustomCommandArguments(cmdNode, nbOptions, option, cmdNode->str)) {
		printf("tsHBox::processCustomCommand(): argument substitution failed for custom command '%s': infinite recursion detected:\n", cmdNode->str + 1);
		fontParsePrintInput(cmdNode->inputIdx, 16, 16);
		fpNodeFree(cmdNode);
		return 0;
	}

	// no name string required any more
	if (cmdNode->str) {
		free(cmdNode->str);
		cmdNode->str = NULL;
	}

	// remove the custom command (\cmdName) from the sentence
	fpNodeFree(currentNode->child[1]);
	currentNode->child[1] = NULL;

	// find the end of the cmdNode tree
	struct fpNode_s *lastCmdNode = fpDescentLeft(cmdNode);

	// adjust the tree
	cmdNode->parent = currentNode;
	lastCmdNode->child[0] = currentNode->child[0];
	if (lastCmdNode->child[0]) lastCmdNode->child[0]->parent = lastCmdNode;
	currentNode->child[0] = cmdNode;

	// continue parsing at lastCmdNode
	*nextNode = lastCmdNode;

	return 0;
}

/*
 *
 ********************* tsWordBox ***************************
 *
 */

tsWordBox::tsWordBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbWord) {
	initToNothing();
	if (node->type == fpnWordSpecialChar) init(state, node->nb);
	else init(state, node->str);
}

tsWordBox::tsWordBox(typesetState *state, const char *str) : typesetBox(state, tsbWord) {
	initToNothing();
	init(state, str);
}

tsWordBox::tsWordBox(typesetState *state, int chr) : typesetBox(state, tsbWord) {
	initToNothing();
	m_fontStr = (int*)malloc(2 * sizeof(int));
	if (m_fontStr == NULL) return;
	m_fontStr[0] = chr;
	m_fontStr[1] = 0;
	strSize(state, m_fontStr, m_width, m_ascent, m_descent);
}

tsWordBox::~tsWordBox() {
	if (m_fontStr) free(m_fontStr);
	initToNothing();
}

void tsWordBox::initToNothing() {
	m_fontStr = NULL;
}

int tsWordBox::init(typesetState *state, int chr) {
	m_fontStr = convertChr(chr);
	if (m_fontStr == NULL) return -1;
	strSize(state, m_fontStr, m_width, m_ascent, m_descent);
	return 0;
}

int tsWordBox::init(typesetState *state, const char *str) {
	m_fontStr = convertStr(str);
	if (m_fontStr == NULL) return -1;
	strSize(state, m_fontStr, m_width, m_ascent, m_descent);
	return 0;
}

static const char *s_operatorChars = "+-=/*^%<>";
static const int s_operatorIdx[] = 
{800, 801, 802, 803, 804, 806, -1}; // just an example...
int tsWordBox::eqnOperator() {
	int i, c;
	if (( (c = m_fontStr[0]) == 0) || (m_fontStr[1] != 0)) return 0; // wrong length

	// all of this depends on font def
	if (c >= 800) { 
		i = 0;
		while (s_operatorIdx[i] >= 0) {
			if (c == s_operatorIdx[i]) return 1;
			i++;
		}
	}
	else {
		c = c % 200;
		i = 0;
		while (s_operatorChars[i]) {
			if (c == s_operatorChars[i]) return 1;
			i++;
		}
	}
	return 0;
}



double tsWordBox::stretch() {
	return 0.2 * m_width;
}

int tsWordBox::typeset(typesetState *state) {
	int l = fontStrlen(m_fontStr), i;
	if (l == 0) return 0;
	double x = 0.0;
	double w, a, d;
	strSize(state, m_fontStr, w, a, d);

	state->pushSize(m_fontSize);
	state->pushTrans(m_x, m_y);

	switch (m_align) {
	case tsaLeft:
		for (i = 0; i < l; i++)
			x += state->addChar(m_fontStr[i], x, 0.0, m_color);
		break;
	case tsaRight:
		for (i = 0; i < l; i++) {
			x += state->addChar(m_fontStr[i], m_width - w + x, 0.0, m_color);
		}
		break;
	case tsaCenter:
		for (i = 0; i < l; i++)
			x += state->addChar(m_fontStr[i], (m_width - w) / 2.0 + x, 0.0, m_color);
		break;
	case tsaJustify:
		if (l == 1) {
			w = (m_width - w) / l;
			x += w / 2;
		}
		else {
			w = (m_width - w) / (l-1);
		}
		for (i = 0; i < l; i++)
			x += state->addChar(m_fontStr[i], x, 0.0, m_color) + w;
		break;
	
	}
	state->popTrans();
	state->popSize();

	return 0;
}


/*
 *
 ********************* tsWhiteSpaceBox ***************************
 *
 */
tsWhiteSpaceBox::tsWhiteSpaceBox(typesetState *state, struct fpNode_s *node) : 
	typesetBox(state, tsbWhiteSpace) {
	initToNothing();
	m_width = m_fontSize / 4; // * nb of spaces?
	m_ascent = (1.0 - state->m_fontDescent) * m_fontSize;
	m_descent = -state->m_fontDescent * m_fontSize;
}

tsWhiteSpaceBox::tsWhiteSpaceBox(typesetState *state, double width) : 
	typesetBox(state, tsbWhiteSpace) {
	initToNothing();
	m_width = width * m_fontSize;
	m_ascent = (1.0 - state->m_fontDescent) * m_fontSize;
	m_descent = -state->m_fontDescent * m_fontSize;
}

tsWhiteSpaceBox::~tsWhiteSpaceBox() {
	initToNothing();
}

void tsWhiteSpaceBox::initToNothing() {
	m_forced = 0;
}

double tsWhiteSpaceBox::stretch() {
	return 0.8 * m_width;
}

/*
 *
 ********************* tsNumberBox ***************************
 *
 */
tsNumberBox::tsNumberBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbNumber) {
	initToNothing();

	state->pushFont(tsfRegular);

	char *base = strdup(node->str);
	if (base == NULL) return;

	// find the e part
	char *epart;
	if ((epart = strchr(base, 'e')) == NULL)
		epart = strchr(base, 'E');
	
	if (epart == NULL) { // no epart, just a simple single word box
		addChild(new tsWordBox(state, base));
		m_width = m_child[0]->m_width;
		m_ascent = m_child[0]->m_ascent;
		m_descent = m_child[0]->m_descent;
	}
	else { // base + epart, create two boxes
		epart++;

		// create epart box (temporarily scale down font)
		state->pushSize(state->size() * 0.8);
		tsWordBox *eBox = new tsWordBox(state, epart);
		state->popSize();

		// create base box
		*epart = 0;
		tsWordBox *bBox = new tsWordBox(state, base);

		// add them to this box
		addChild(bBox);
		eBox->m_x = bBox->m_width;
		eBox->m_y = bBox->m_y + 0.4 * bBox->m_ascent;
		addChild(eBox);

		// set width and height of this box
		m_width = bBox->m_width + eBox->m_width;
		m_ascent = dmax(bBox->m_ascent, eBox->m_y + eBox->m_ascent);
		m_descent = 0;
	}

	state->popFont();

	free(base);
}

tsNumberBox::~tsNumberBox() {
	initToNothing();
}

void tsNumberBox::initToNothing() {

}

double tsNumberBox::stretch() {
	return 0.0001;
}

int tsNumberBox::typeset(typesetState *state) {
	int i;
	state->pushTrans(m_x, m_y);
	for (i = 0; i < m_nbChildren; i++)
		m_child[i]->typeset(state);
	state->popTrans();

	return 0;
}

/*
 *
 ********************* tsScriptBox ***************************
 *
 */

tsScriptBox::tsScriptBox(typesetState *state, typesetBox *baseBox) : typesetBox(state, tsbScript) {
	initToNothing();
	addChild(baseBox);

	computeSize();
}

tsScriptBox::~tsScriptBox() {
	initToNothing();
}

void tsScriptBox::initToNothing() {
	m_subscript = m_superscript = 0;
}

int tsScriptBox::addScript(typesetState *state, struct fpNode_s *node, int super, const char *ssStr) {
	if ((super && m_superscript) || ((!super) && m_subscript)) {
		printf("tsScriptBox::addScript(): warning: multiple %ss (ignoring):\n", ssStr);
		fontParsePrintInput(node->inputIdx, 16, 16);
		return 0;
	}

	struct fpNode_s *nextNode = NULL;
	struct fpNode_s *optionNode = NULL;
	struct fpNode_s *rootNode = NULL;
	struct fpNode_s *currentNode = NULL;

	// find the first option
	optionNode = node->child[0];
	if ((optionNode->nbChildren < 1) || ( (rootNode = optionNode->child[0]) == NULL)) {
		printf("tsScriptBox::addScript(): warning: no text for %s\n", ssStr);
		fontParsePrintInput(node->inputIdx, 16, 16);
		return 0;
	}
	
	currentNode = fpDescentLeft(rootNode);

	state->pushSize(state->size() * 0.6);
	tsHBox *HBox = new tsHBox(state);
	HBox->setup(state, currentNode, &nextNode, rootNode);
	HBox->computeSize();
	HBox->m_maxWidth = HBox->m_width;

	if (nextNode) {
		printf("tsScriptBox::addScript(): warning: carriage return in %s? (ignoring text after carriage return):\n", ssStr);
		fontParsePrintInput(nextNode->inputIdx, 16, 16);
	}
	state->popSize();

	HBox->m_x = m_child[0]->m_x + m_child[0]->m_width;
	if (super) HBox->m_y = m_child[0]->m_y + m_child[0]->m_ascent - 0.8 * (HBox->m_ascent - HBox->m_descent);
	else HBox->m_y = m_child[0]->m_y + m_child[0]->m_descent;
	addChild(HBox);

	computeSize();

	if (super) m_superscript = 1;
	else m_subscript = 1;


	return 0;
}


int tsScriptBox::addSuperscript(typesetState *state, struct fpNode_s *node) {
	return addScript(state, node, 1, "superscript");
}

int tsScriptBox::addSubscript(typesetState *state, struct fpNode_s *node) {
	return addScript(state, node, 0, "subscript");
}

double tsScriptBox::stretch() {
	// todo: something based on the scretch of the children...
	return 0.00001;	
}

int tsScriptBox::typeset(typesetState *state) {
	int i;

	// a script box always typesets in the middle of its box
	double tw = m_width;
	computeSize();

	state->pushTrans(m_x + (tw - m_width) / 2.0, m_y);
	for (i = 0; i < m_nbChildren; i++)
		m_child[i]->typeset(state);
	state->popTrans();
	return 0;
}

int tsScriptBox::computeSize() {
	m_ascent = m_child[0]->m_ascent;
	m_descent = m_child[0]->m_descent;
	if (m_nbChildren == 1) {
		m_width = m_child[0]->m_width;
	}
	else {
		int i;
		double ascent, descent, width;
		m_width = 0.0;

		for (i = 1; i < m_nbChildren; i++) {
			ascent = m_child[i]->m_y + m_child[i]->m_ascent;
			descent = m_child[i]->m_y + m_child[i]->m_descent;
			width = m_child[i]->m_x + m_child[i]->m_width;

			m_descent = dmin(m_descent, descent);
			m_ascent = dmax(m_ascent, ascent);
			m_width = dmax(width, m_width);
		}
	}

	return 0;
}

/*
 *
 ********************* tsFracBox ***************************
 *
 */

tsFracBox::tsFracBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbFrac) {
	initToNothing();

	// get the options
	struct fpNode_s *option[2];
	int nb = 2;
	if ((getOptions(nb, node->child[1]->child[0], option, 1, "tsFracBox::tsFracBox()", "frac")) || (nb != 2)) return;

	// setup the nominator and the denominator
	tsHBox *HBox1 = setup(state, option[0]);
	tsHBox *HBox2 = setup(state, option[1]);

	if (!(HBox1 && HBox2)) { // detect failure
		if (HBox1) delete HBox1;
		if (HBox2) delete HBox2;
		return;
	}

	addChild(HBox1);
	addChild(HBox2);

	m_width = dmax(HBox1->m_width, HBox2->m_width);

	// compute the 'median y' we would like to have
	double h1 = HBox1->m_ascent - HBox1->m_descent;
	double h2 = HBox2->m_ascent - HBox2->m_descent;
//	m_lineY = 0.5 * m_fontSize + 0.5 * (h2 - h1);
	m_lineY = 0.25 * m_fontSize;

	HBox1->m_x = 0.0;
	HBox1->m_y = m_lineY + 0.05 * m_fontSize - HBox1->m_descent;
	if ((HBox1->m_align == tsaLeft) || (HBox1->m_align == tsaRight))
		HBox1->m_align = tsaCenter;

	HBox2->m_x = 0.0;
	HBox2->m_y = m_lineY - 0.05 * m_fontSize - HBox2->m_ascent;
	if ((HBox2->m_align == tsaLeft) || (HBox2->m_align == tsaRight))
		HBox2->m_align = tsaCenter;

	m_ascent = HBox1->m_y + HBox1->m_ascent;
	m_descent = HBox2->m_y + HBox2->m_descent;

}

tsFracBox::~tsFracBox() {
	initToNothing();
}

void tsFracBox::initToNothing() {
	m_lineY = -1.0;
}

tsHBox *tsFracBox::setup(typesetState *state, struct fpNode_s *option) {
	int err;
	struct fpNode_s *nextNode = NULL;
	struct fpNode_s *rootNode = NULL;
	struct fpNode_s *currentNode = NULL;

	rootNode = option->child[0];
	currentNode = fpDescentLeft(rootNode);

	state->pushSize(state->size() * 0.9); // scale down a little
	tsHBox *HBox = new tsHBox(state);
	if (err = HBox->setup(state, currentNode, &nextNode, rootNode)) {
		delete HBox;
		return NULL;
	}
	state->popSize();

	// round this all up into one call?
	HBox->setAlignment();
	HBox->spaceEqnOperators(state);
	HBox->deleteTrailingWhiteSpace();
	HBox->computeSize();

	if (nextNode) {
		printf("tsFracBox::setup(): warning: carriage return in frac command? (ignoring text after carriage return):\n");
		fontParsePrintInput(nextNode->inputIdx, 16, 16);
	}

	return HBox;
}

double tsFracBox::stretch() {
	int i;
	double s = 0.0;
	for (i = 0; i < 2; i++) {
		s = dmax(s, m_child[i]->stretch());
	}
	return s;
}

int tsFracBox::typeset(typesetState *state) {
	int i;
	state->pushTrans(m_x, m_y);

	double px[2] = {0.0, m_width}, py[2] = {m_lineY, m_lineY};
	state->addLine(2, GL_LINES, px, py, (float)m_fontSize / 25.0f, m_color);

	for (i = 0; i < m_nbChildren; i++) {
		((tsHBox*)m_child[i])->m_maxWidth = m_width;
		m_child[i]->typeset(state);
	}
	state->popTrans();

	return 0;
}

/*
 *
 ********************* tsSqrtBox ***************************
 *
 */

tsSqrtBox::tsSqrtBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbSqrt) {
	initToNothing();
	int err;

	// get the options
	struct fpNode_s *option[2];
	int nb = 2;
	getOptions(nb, node->child[1]->child[0], option, 0, "tsSqrtBox::tsSqrtBox()", "sqrt");
	if (nb < 1) return;

	// setup the contents
	tsHBox *HBox1 = setup(state, option[0], 1.0);
	if (!HBox1) return; // detect failure
	double height = HBox1->m_ascent - HBox1->m_descent + 0.1 * m_fontSize;

	// setup the 'power(?)' 
	tsHBox *HBox2 = (option[1]) ? setup(state, option[1], 0.5 * height / m_fontSize) : NULL;

	err = addChild(HBox1);
	if (HBox2) err |= addChild(HBox2);
	if (err) {
		delete HBox1;
		if (HBox2) delete HBox2;
		return;
	}

	HBox1->m_x = height * (0.3 + 0.2);
	m_width = HBox1->m_x + HBox1->m_width + 0.1 * m_fontSize;

	// compute the pos/size HBox1 should have
	if (height < m_fontSize * 1.5) {
		HBox1->m_y = 0.0;
		m_ascent = HBox1->m_ascent + 0.05 * m_fontSize;
		m_descent = HBox1->m_descent - 0.05 * m_fontSize;
	}
	else {
		m_ascent = 0.55 * m_fontSize + 0.5 * height;
		m_descent = 0.45 * m_fontSize - 0.5 * height;
		HBox1->m_y = m_ascent - HBox1->m_ascent;
	}
	if ((HBox1->m_align == tsaLeft) || (HBox1->m_align == tsaRight))
		HBox1->m_align = tsaCenter;

	// compute the pos HBox2 should have
	if (HBox2) {
		HBox2->m_x = 0.5 * (0.5 * height - HBox2->m_width);
		HBox2->m_y = m_ascent - HBox2->m_ascent;
		if ((HBox2->m_align == tsaLeft) || (HBox2->m_align == tsaRight))
			HBox2->m_align = tsaCenter;
	}

}

tsSqrtBox::~tsSqrtBox() {
	initToNothing();
}

void tsSqrtBox::initToNothing() {
}

tsHBox *tsSqrtBox::setup(typesetState *state, struct fpNode_s *option, double scale) {
	int err;
	struct fpNode_s *nextNode = NULL;
	struct fpNode_s *rootNode = NULL;
	struct fpNode_s *currentNode = NULL;

	rootNode = option->child[0];
	currentNode = fpDescentLeft(rootNode);

	state->pushSize(state->size() * scale);
	tsHBox *HBox = new tsHBox(state);
	if (err = HBox->setup(state, currentNode, &nextNode, rootNode)) {
		delete HBox;
		return NULL;
	}
	state->popSize();

	// round this all up into one call?
	HBox->setAlignment();
	HBox->spaceEqnOperators(state);
	HBox->deleteTrailingWhiteSpace();
	HBox->computeSize();

	if (nextNode) {
		printf("tsSqrtBox::setup(): warning: carriage return in sqrt command? (ignoring text after carriage return):\n");
		fontParsePrintInput(nextNode->inputIdx, 16, 16);
	}

	return HBox;
}

double tsSqrtBox::stretch() {
	double s = 0.0;
	s = dmax(s, m_child[0]->stretch());
	return s;
}

int tsSqrtBox::typeset(typesetState *state) {
	state->pushTrans(m_x, m_y);

	double h = m_ascent - m_descent;
	double px[4] = {0.0, h * 0.2, h * 0.5, m_width};
	double py[4] = {0.7 * m_ascent + 0.3 * m_descent, m_descent + 0.02 * m_fontSize, m_ascent - 0.02 * m_fontSize, m_ascent - 0.02 * m_fontSize};
	state->addLine(4, GL_LINE_STRIP, px, py, (float)m_fontSize / 25.0f, m_color);

	/*
	// just a test with polygons...
	double px2[4] = {0.0, m_width, m_width, 0.0};
	double py2[4] = {0.0, 0.0, m_fontSize / 15.0, m_fontSize / 15.0};
	state->addPolygon(4, GL_QUADS, px2, py2, m_color);
*/

	((tsHBox*)m_child[0])->m_maxWidth = m_width - m_child[0]->m_x;
	m_child[0]->typeset(state);
	if ((m_nbChildren > 1) && m_child[1]) {
		((tsHBox*)m_child[1])->m_maxWidth = m_child[1]->m_width;
		m_child[1]->typeset(state);
	}
	
	state->popTrans();

	return 0;
}

/*
 *
 ********************* tsParBox ***************************
 *
 */

static parDesc s_roundPar[] = {
	{0.1903, 0.5, 0.3081, 0.5, 0.25},
	{0.1234, 0.4177, 0.2151, 0.3936, 0.25},
	{0.0632, 0.3074, 0.1508, 0.2816, 0.25},
	{0.0146, 0.1539, 0.1061, 0.1437, 0.25},
	{0.0, 0.0, 0.0905, 0.0, 0.0},
	{-1.0, -1.0, -1.0, -1.0}
};

static parDesc  s_squarePar[] = {
	{0.2644, 0.5, 0.2644, 0.4394, 0.0},
	{0.0, 0.5, 0.0918, 0.4394, 1.0},
	{0.0, 0.0, 0.0918, 0.0, 0.0},
	{-1.0, -1.0, -1.0, -1.0}
};

static parDesc  s_curlyPar[] = {
	{0.482, 0.5, 0.4808, 0.4396, 0.0},
	{0.3957, 0.5, 0.4068, 0.4388, 0.0},
	{0.3205, 0.4943, 0.3492, 0.4246, 0.0},
	{0.2529, 0.4534, 0.3158, 0.4004, 0.0},
	{0.21, 0.3844, 0.2983, 0.3649, 0.0},
	{0.1991, 0.3089, 0.2903, 0.3089, 1.0},
	{0.1991, 0.2299, 0.2903, 0.2299, 0.0},
	{0.1886, 0.1564, 0.2717, 0.1233, 0.0},
	{0.1559, 0.0983, 0.2146, 0.0549, 0.0},
	{0.0937, 0.0576, 0.1418, 0.0, 0.0},
	{0.0, 0.0478, 0.0, 0.0, 0.0},
	{-1.0, -1.0, -1.0, -1.0}
};

tsParBox::tsParBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbPar) {
	initToNothing();
	int err;

	// get the options
	struct fpNode_s *option[2]; // option[0] is parentheses, option[1] is contents
	int nb = 2;
	if (err = getOptions(nb, node->child[1]->child[0], option, 1, "tsParBox::tsParBox()", "Par"))
		return;

	// retrieve the brackets
	struct fpNode_s *leftPar;
	struct fpNode_s *rightPar;
	if ((option[0]->child[0] == NULL) || (option[0]->child[0]->child[0] == NULL) ||
		((leftPar =   option[0]->child[0]->child[0]->child[1]) == NULL) ||
		((rightPar = option[0]->child[0]->child[1]) == NULL) ||
		(leftPar->type != fpnWordSpecialChar) || 
		(rightPar->type != fpnWordSpecialChar)) {
		printf("tsParBox::tsParBox(): Could not retrieve the parentheses:\n");
		fontParsePrintInput(node->inputIdx, 16, 16);
		return;
	}

	if (leftPar->nb == '(') m_leftPar = s_roundPar;
	else if (leftPar->nb == '[') m_leftPar = s_squarePar;
	else m_leftPar = s_curlyPar;

	if (rightPar->nb == ')') m_rightPar = s_roundPar;
	else if (rightPar->nb == ']') m_rightPar = s_squarePar;
	else m_rightPar = s_curlyPar;

	m_leftWidth = parWidth(m_leftPar) + 0.05 * m_fontSize;
	m_rightWidth = parWidth(m_rightPar) + 0.05 * m_fontSize;

	// setup the contents
	tsHBox *HBox = setup(state, option[1], 1.0);
	if (!HBox) return;
	if (err = addChild(HBox)) {
		delete HBox;
		return;
	}

	HBox->m_x = m_leftWidth;
	m_width = HBox->m_x + HBox->m_width + m_rightWidth;

	m_ascent = HBox->m_ascent;
	m_descent = HBox->m_descent;
}

tsParBox::~tsParBox() {
	initToNothing();
}

void tsParBox::initToNothing() {
	m_leftPar = m_rightPar = NULL;
	m_leftWidth = m_rightWidth = 0.0;
}

tsHBox *tsParBox::setup(typesetState *state, struct fpNode_s *option, double scale) {
	int err;
	struct fpNode_s *nextNode = NULL;
	struct fpNode_s *rootNode = NULL;
	struct fpNode_s *currentNode = NULL;

	rootNode = option->child[0];
	currentNode = fpDescentLeft(rootNode);

	state->pushSize(state->size() * scale);
	tsHBox *HBox = new tsHBox(state);
	if (err = HBox->setup(state, currentNode, &nextNode, rootNode)) {
		delete HBox;
		return NULL;
	}
	state->popSize();

	// round this all up into one call?
	HBox->setAlignment();
	HBox->spaceEqnOperators(state);
	HBox->deleteTrailingWhiteSpace();
	HBox->computeSize();

	if (nextNode) {
		printf("tsParBox::setup(): warning: carriage return in par command?:\n");
		fontParsePrintInput(nextNode->inputIdx, 16, 16);
	}

	return HBox;
}

double tsParBox::stretch() {
	double s = 0.00001;
	if (m_nbChildren)
		s = dmax(s, m_child[0]->stretch());
	return s;
}

int tsParBox::typeset(typesetState *state) {
	state->pushTrans(m_x, m_y);

	// draw the two parentheses
	double h = m_ascent - m_descent;
	setupPar(state, m_leftPar, 0.0, m_descent, h, m_fontSize, 1.0);
	setupPar(state, m_rightPar, m_width, m_descent, h, m_fontSize, -1.0);

	if (m_nbChildren) {
		m_child[0]->m_x = m_leftWidth;
		((tsHBox*)m_child[0])->m_maxWidth = m_width - (m_leftWidth + m_rightWidth);
		m_child[0]->typeset(state);
		
	}
	
	state->popTrans();

	return 0;
}

// draws a parenthesis
int tsParBox::setupPar(typesetState *state, const parDesc *desc, 
					   double x, double y, double h, double fontHeight, double scaleX) {
	double px[40];
	double py[40];

	if (desc == NULL) return -1;

	if (h < fontHeight) h = fontHeight;
	double s = 0.5 * (h - fontHeight);
	double cy;
	int idx, i;

	// upper part
	idx = i = 0;
	cy = y + h;
	while ((desc[i].x1 >= 0.0) && (desc[i].y1 >= 0.0)) {
		px[idx] = x + fontHeight * desc[i].x1 * scaleX;
		py[idx] = cy - fontHeight * (0.5 - desc[i].y1);
		idx++;
		px[idx] = x + fontHeight * desc[i].x2 * scaleX;
		py[idx] = cy - fontHeight * (0.5 - desc[i].y2);
		idx++;
		cy -= s * desc[i].stretchable;
		i++;
	}
	state->addPolygon(idx, GL_QUAD_STRIP, px, py, m_color);

	// lower part
	idx = i = 0;
	cy = y;
	while ((desc[i].x1 >= 0.0) && (desc[i].y1 >= 0.0)) {
		px[idx] = x + fontHeight * desc[i].x1 * scaleX;
		py[idx] = cy + fontHeight * (0.5 - desc[i].y1);
		idx++;
		px[idx] = x + fontHeight * desc[i].x2 * scaleX;
		py[idx] = cy + fontHeight * (0.5 - desc[i].y2);
		idx++;
		cy += s * desc[i].stretchable;
		i++;
	}
	state->addPolygon(idx, GL_QUAD_STRIP, px, py, m_color);

	return 0;
}

double tsParBox::parWidth(const parDesc *desc) {
	int i = 0;
	double w = 0.0;
	if (desc == NULL) return -1.0;
	while ((desc[i].x1 >= 0.0) && (desc[i].y1 >= 0.0)) {
		w = dmax(dmax(w, desc[i].x1 * m_fontSize), desc[i].x2 * m_fontSize);
		i++;
	}
	return w;
}


/*
 *
 ********************* tsHatBox ***************************
 *
 */

// todo: fix/solve ascent
// have ascent for individual characters? Should have it eventually...
tsHatBox::tsHatBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbHat) {
	initToNothing();

	int i;

	// get the hat type
	const char *hatNames[] = {
		"hat",
		"widehat",
		"tilde",
		"widetilde",
		"bar",
		"widebar",
		NULL
	};
	struct fpNode_s *rhc = node->child[1]; // right hand child (of sentence)
	const char *cmdStr = rhc->str+1;
	i = 0;
	while (hatNames[i]) {
		if (!strcmp(cmdStr, hatNames[i])) break;
		i++;
	}
	if (hatNames[i] == NULL) {
		printf("tsHatBox::tsHatBox(): Invalid hat type '%s':\n", cmdStr);
		fontParsePrintInput(node->inputIdx, 16, 16);
		return;
	}
	m_hatType = i;

	// get the options
	struct fpNode_s *option[1];
	int nb = 1;
	if ((getOptions(nb, node->child[1]->child[0], option, 1, "tsHatBox::tsHatBox()", "hat")) || (nb != 1)) return;

	// setup the HBox
	tsHBox *HBox = setup(state, option[0]);

	if (HBox == NULL) return;

	addChild(HBox);

	m_width = HBox->m_width;

	m_ascent = HBox->m_ascent + m_fontSize * 0.1;
	m_descent = HBox->m_descent;

}

tsHatBox::~tsHatBox() {
	initToNothing();
}

void tsHatBox::initToNothing() {
	m_hatType = -1;
}

tsHBox *tsHatBox::setup(typesetState *state, struct fpNode_s *option) {
	int err;
	struct fpNode_s *nextNode = NULL;
	struct fpNode_s *rootNode = NULL;
	struct fpNode_s *currentNode = NULL;

	rootNode = option->child[0];
	currentNode = fpDescentLeft(rootNode);

	tsHBox *HBox = new tsHBox(state);
	if (err = HBox->setup(state, currentNode, &nextNode, rootNode)) {
		delete HBox;
		return NULL;
	}

	// round this all up into one call?
	HBox->setAlignment();
	HBox->spaceEqnOperators(state);
	HBox->deleteTrailingWhiteSpace();
	HBox->computeSize();

	if (nextNode) {
		printf("tsHatBox::setup(): warning: carriage return in hat command?\n");
		fontParsePrintInput(nextNode->inputIdx, 16, 16);
	}

	return HBox;
}

double tsHatBox::stretch() {
	return (m_nbChildren) ? m_child[0]->stretch() : 0.00001;
}


static hatDesc s_hatDesc[] = {
	{0.0, 0.1007, 0.0944, 0.04},
	{0.4379, 0.6916, 0.529, 0.5678},
	{0.6211, 0.6916, 0.529, 0.5678},
	{1.0413, 0.1007, 0.9626, 0.04},
	{-1.0, -1.0, -1.0, -1.0}
};

static hatDesc s_tildeDesc[] = {
	{0.0, 0.1736, 0.0662, 0.0909},
	{0.0864, 0.2944, 0.1359, 0.1693},
	{0.2023, 0.3701, 0.2467, 0.2091},
	{0.3088, 0.3914, 0.3234, 0.212},
	{0.4627, 0.3618, 0.4303, 0.1965},
	{0.7503, 0.2459, 0.6899, 0.0754},
	{0.8722, 0.2175, 0.8544, 0.04},
	{0.9424, 0.2295, 0.9778, 0.0686},
	{1.026, 0.2709, 1.0836, 0.1456},
	{1.1017, 0.35, 1.1715, 0.2589},
	{-1.0, -1.0, -1.0, -1.0}
};

static hatDesc s_barDesc[] = {
	{0.0009, 0.04, 0.0, 0.2659},
	{1.0098, 0.04, 1.0098, 0.2659},
	{-1.0, -1.0, -1.0, -1.0}
};


int tsHatBox::typeset(typesetState *state) {
	int i, idx;
	state->pushTrans(m_x, m_y);

	// set width of box
	((tsHBox*)m_child[0])->m_maxWidth = m_width;

	// select which hat, wide or note
	hatDesc *desc;
	int wide = m_hatType & 1;
	int hatIdx = m_hatType / 2;
	desc = ((hatIdx * 2) == tshHat) ? s_hatDesc : (((hatIdx * 2) == tshTilde) ? s_tildeDesc : s_barDesc);

	// compute hat desc width
	double w = 0.0;
	i = 0;
	while ((desc[i].x1 >= 0) && (desc[i].y1 >= 0)) {
		w = dmax(w, dmax(desc[i].x1, desc[i].x2));
		i++;
	}

	// compute x, y, scale
	double x, y, sx, sy;
	if (wide) {
		x = 0.0;
		y = m_ascent - 0.15 * m_fontSize;
		sx = m_width / w;
		sy = 0.25 * m_fontSize / w;
	}
	else {
		sx = sy = 0.25 * m_fontSize / w;
		x = 0.5 * (m_width - sx * w);
		y = m_ascent - 0.15 * m_fontSize;
	}

	// setup polygons & draw
	double px[40];
	double py[40];
	idx = i = 0;
	while ((desc[i].x1 >= 0.0) && (desc[i].y1 >= 0.0)) {
		px[idx] = x + sx * desc[i].x1;
		py[idx] = y + sy * desc[i].y1;
		idx++;
		px[idx] = x + sx * desc[i].x2;
		py[idx] = y + sy * desc[i].y2;
		idx++;
		i++;
	}
	state->addPolygon(idx, GL_QUAD_STRIP, px, py, m_color);


	// typeset children
	for (i = 0; i < m_nbChildren; i++) {
		((tsHBox*)m_child[i])->m_maxWidth = m_width;
		m_child[i]->typeset(state);
	}
	state->popTrans();

	return 0;
}

/*
 *
 ********************* tsTabularBox ***************************
 *
 */

tsTabularBox::tsTabularBox(typesetState *state, struct fpNode_s *node) : typesetBox(state, tsbTabular) {
	int err, i, j, k;
	tsVBox *box;
	initToNothing();
	struct fpNode_s *cmdNode = node->child[1];

	// set constants
	m_vlWidth = 0.15 * m_fontSize;
	m_hlWidth = 0.10 * m_fontSize;

	// get the options
	struct fpNode_s *option[32];
	int nbOptions = 32;
	if ((getOptions(nbOptions, cmdNode->child[0], option, -1, "tsTabularBox::tsTabularBox()", "tabular")) || (nbOptions < 2)) {
		printf("tsTabularBox::tsTabularBox(): to few arguments to tabular command\n");
		fontParsePrintInput(cmdNode->inputIdx, 16, 16);
		return;
	}

	// parse how many columns, what alignment, etc from the first option
	if ((option[0] == NULL) || (err = setFormat(option[0]))) {
		printf("tsTabularBox::tsTabularBox(): could not parse column format of tabular:\n");
		fontParsePrintInput(cmdNode->child[0]->inputIdx, 16, 16);
		return;
	}

	// setup each row: 
	// chop each option sentence up into smaller sentences, 
	// which are setup by individual VBoxes, 
	// which all are all set to the right alignment
	for (i = 1; i < nbOptions; i++) {
		tsTabularRow*row = new tsTabularRow;
		memset(row, 0, sizeof(tsTabularRow));
		if (err = setupRow(state, row, option[i])) {
			printf("tsTabularBox::tsTabularBox(): error adding row '%d' to tabular\n", i);
			fontParsePrintInput(option[i]->inputIdx, 16, 16);
			deleteRow(row);
		}
		else m_row.add(&row);
	}

	
	double w = 0.0, h = 0.0;
	m_columnWidth.clear();
	m_columnStretch.clear();
	double tempDouble1 = 0.0, tempDouble2 = 10e20;
	for (i = 0; i < m_nbColumns; i++) {
		m_columnWidth.add(&tempDouble1);
		m_columnStretch.add(&tempDouble2);
	}

	// remove all unnecessary entries, pad missing entries with NULLs, get the width and stretch of each column
	// get height of each row
	for (i = 0; i < m_row.m_nb; i++) {
		if (m_row[i]->rowType) { // hline or hspace
			m_row[i]->ascent = m_hlWidth;
			m_row[i]->descent = 0.0;
			h += m_row[i]->ascent;
		}
		else { // ordinary row
			m_row[i]->ascent = m_row[i]->descent = 0.0;

			k = j = 0;
			while (j < m_format.m_nb) {
				if (m_format[j] & tsaVLine) {
					j++;
					continue;
				}

				// pad with NULL boxes
				if (k >= m_row[i]->box.m_nb) {
					printf("tsTabularBox::tsTabularBox(): Padding tabular row %d, column %d with empty VBox:\n", i + 1, k + 1);
					fontParsePrintInput(option[i+1]->inputIdx, 16, 16);
					box = NULL;
					m_row[i]->box.add(&box);
				}

				// set alignment, max column width, max row ascent, max row descent
				if (box = m_row[i]->box[k]) {
//					box->m_align = m_format[j]; (this is too late...)
					m_columnWidth.set(k, dmax(m_columnWidth[k], box->m_width));
					m_columnStretch.set(k, dmin(m_columnStretch[k], box->stretch()));
					m_row[i]->ascent = dmax(m_row[i]->ascent, box->m_ascent);
					m_row[i]->descent = dmin(m_row[i]->descent, box->m_descent);
				}
				k++;
				j++;
			}
			h += m_row[i]->ascent - m_row[i]->descent;
		}
	}

	w = m_vlineWidth;
	for (i = 0; i < m_nbColumns; i++) {
		w += m_columnWidth[i];
	}
	
	// fill in min. width & ascent, descent, 
	m_width = w;
	m_ascent = 0.5 * h + 0.25 * m_fontSize;
		//(h - (1.0 - state->m_fontDescent) * m_fontSize);
	m_descent = -h + m_ascent;

}

tsTabularBox::~tsTabularBox() {
	int i;

	// todo: remember that all child will be remove automatically
	// delete all rows entries
	for (i = 0; i < m_row.m_nb; i++)
		deleteRow(m_row[i]);

	initToNothing();
}

void tsTabularBox::initToNothing() {
	m_vlineWidth = 0;
	m_vlWidth = m_hlWidth = 0;
}

void tsTabularBox::deleteRow(tsTabularRow*row) {
	int i, err;
	if (row == NULL) return;
	for (i = 0; i < row->box.m_nb; i++) {
		removeChild(row->box[i]);
		if (row->box[i]) {
			if (err = removeChild(row->box[i])) // check for error...
				delete row->box[i]; // .. and delete yourself if error (this means the box was no child o 'this')
		}
	}
	delete row;
}

double tsTabularBox::stretch() {
	// return sum of stretch of each column
	int i;
	double s = 0.00001;
	for (i = 0; i < m_columnStretch.m_nb; i++)
		s += m_columnStretch[i];
	return s;
}

int tsTabularBox::typeset(typesetState *state) {
	state->pushTrans(m_x, m_y);

	if (m_nbColumns == 0) return 0;

	double width; // width as computed by summing the max width of each column + the vlines
	double *columnWidth = (double*)calloc(sizeof(double), m_nbColumns); // column width as computed after taking into account the 'forced' width, as stored in 'm_width'
	double totalStretch = stretch();
	int i, j, k;
	double x, y;
	double lx[2], ly[2];
	tsVBox *box = NULL;

	// determine width of each column
	width = m_vlineWidth;
	for (i = 0; i < m_nbColumns; i++) width += m_columnWidth[i];
	for (i = 0; i < m_nbColumns; i++)
		columnWidth[i] = m_columnWidth[i] + (m_width - width) * m_columnStretch[i] / totalStretch;

	// draw each row
	y = m_ascent;
	for (i = 0; i < m_row.m_nb; i++) {
		x = 0.0;
		if (m_row[i]->rowType) { // hline or hspace
			if (m_row[i]->rowType == 1) { // hline
				lx[0] = x + 0.5 * m_vlWidth; lx[1] = x + m_width - 0.5 * m_vlWidth;
				ly[0] = y - 0.5 * m_row[i]->ascent;
				ly[1] = y - 0.5 * m_row[i]->ascent;

				state->addLine(2, GL_LINES, lx, ly, (float)m_fontSize / 25.0f, m_color);
			}

			y -= m_row[i]->ascent;
			y += m_row[i]->descent;
		}
		else { // ordinary row
			y -= m_row[i]->ascent;
			j = k = 0;
			while (j < m_format.m_nb) {
				if (m_format[j] & tsaVLine) {
					j++;
					x += m_vlWidth;
					continue;
				}

				if (box = m_row[i]->box[k]) {
					box->m_x = x;
					box->m_y = y;
					box->typeset(state, m_columnWidth[k]);
				}
				x += m_columnWidth[k];
				k++;
				j++;
			}

			y += m_row[i]->descent;
		}
	}


	// draw all vlines?
	x = 0.0;
	ly[0] = m_ascent - 0.5 * m_hlWidth;
	ly[1] = m_descent + 0.5 * m_hlWidth;
	j = 0;
	for (i = 0; i < m_format.m_nb; i++) {
		if (m_format[i] == tsaVLine) {
			lx[0] = lx[1] = x +  0.5 * m_vlWidth;
			state->addLine(2, GL_LINES, lx, ly, (float)m_fontSize / 25.0f, m_color);
			x += m_vlWidth;
		}
		else if (m_format[i] == tsaVSpace) {
			x += m_vlWidth;
		}
		else x += columnWidth[j++];
	}

	if (columnWidth) free(columnWidth);

	state->popTrans();

	return 0;
}

int tsTabularBox::setFormat(struct fpNode_s *option) {
	m_format.clear();
	int f, i;
	m_vlineWidth = 0;
	m_nbColumns = 0;

	// get the root node of the sentence
	struct fpNode_s *rootNode, *currentNode, *wordNode;
	if (( (rootNode = option->child[0]) == NULL) ||
		(rootNode->type != fpnSentence)) return -1;

	// get to the first node of the sentence
	currentNode = fpDescentLeft(rootNode);
	
	// summarize the format for easy parsing
	while (currentNode != option) {
		if (wordNode = currentNode->child[1]) {
			if (wordNode->type == fpnWordWord) {
				i = 0;
				while (wordNode->str[i]) {
					switch(wordNode->str[i++]) {
					case 'c':
						f = tsaCenter; 
						break;
					case 'l':
						f = tsaLeft; 
						break;
					case 'r':
						f = tsaRight; 
						break;
					case 'j':
						f = tsaJustify; 
						break;
					default: 
						printf("tsTabularBox::setFormat(): ignoring unknown column format '%c':\n", wordNode->str[i-1]);
						fontParsePrintInput(wordNode->inputIdx + i - 1, 16, 16);
						f = -1;
						break;
					}
					if (f >= 0) {
						m_format.add(&f);
						m_nbColumns++;
					}
				}
			}
			else if (wordNode->type == fpnWordWhiteSpace) {
				f = tsaVSpace;
				for (i = 0; i < wordNode->nb; i++) {
					m_format.add(&f);
					m_vlineWidth += m_vlWidth;
				}
			}
			else if ((wordNode->type == fpnWordSpecialChar) &&
				(wordNode->nb == '|')) {
				f = tsaVLine;
				m_format.add(&f);
				m_vlineWidth += m_vlWidth;
			}
			else {
				printf("tsTabularBox::setFormat(): could not parse node of type '%d' in tabular column format:\n", wordNode->type);
				fontParsePrintInput(wordNode->inputIdx, 16, 16);
			}
		}
		currentNode = currentNode->parent;
	}

/*	printf("Format: ");
	for (i = 0; i < m_format.m_nb;i++) {
		printf("%d ", m_format[i]);
	}
	printf("\n");*/

	return 0;
}

int tsTabularBox::setupRow(typesetState *state, tsTabularRow *row, struct fpNode_s *option) {
	int n = 0, err, amp, fIdx = 0;
	// chop up each sentence into smaller sentences, 
	// setup each sentence, and add it to the row as another column

	// get the root node, last node (= currentNode)
	struct fpNode_s *rootNode, *currentNode, *parentNode;
	if (( (rootNode = option->child[0]) == NULL) ||
		(rootNode->type != fpnSentence)) return -1;
	currentNode = fpDescentLeft(rootNode);

	// check for a horizontal line
	if (currentNode->child[1] &&
		(currentNode->child[1]->type == fpnWordCommandNoOption)) {
		if (!strcmp(currentNode->child[1]->str, "\\hline")) {
			row->rowType = 1; // horizontal line
			return 0;
		}
		else if (!strcmp(currentNode->child[1]->str, "\\hspace")) {
			row->rowType = 2; // horizontal spacing
			return 0;
		}
	}

	row->rowType = 0; // ordinary row

	// loop over all nodes, chop sentence up
	while (currentNode != option) {
		amp = 0;
		if ((currentNode->parent == option) || 
			(amp = (currentNode->child[1] &&
			(currentNode->child[1]->type == fpnWordSpecialChar) &&
			(currentNode->child[1]->nb == '&')))) {
			// end of entry sentence found

			// make currentNode a NULL node
			if (amp) {
				fpNodeFree(currentNode->child[1]);
				currentNode->child[1] = NULL;
			}

			// remember the parent, and remove it
			parentNode = currentNode->parent;
			currentNode->parent = NULL;
			parentNode->child[0] = NULL;

			// push the alignment
			while ((fIdx < m_format.m_nb) && (m_format[fIdx] & tsaVLine)) fIdx++;
			if (fIdx < m_format.m_nb) state->pushAlign(m_format[fIdx]);

			// setup the entry, add the entry to the row
			err = setupRowEntry(state, row, currentNode);
			n++;
			if (err) {
				printf("tsTabularBox::setupRow(): error setting up entry '%d' in tabular row\n", n);
				fontParsePrintInput(currentNode->inputIdx, 16, 16);
			}
			fpNodeFree(currentNode);

			// pop the alignment
			if (fIdx < m_format.m_nb) state->popAlign();
			fIdx++;

			// move on to the next node
			currentNode = parentNode;

			// make sure we add an extra entry when the option ends in a ampersant
			if (amp && (currentNode == option)) { // add one last empty entry
				setupRowEntry(state, row, NULL);
				n++;
			}
		}
		else currentNode = currentNode->parent;
	}

	return 0;
}

int tsTabularBox::setupRowEntry(typesetState *state, tsTabularRow*row, struct fpNode_s *sentence) {
	// if sentence is NULL, allocate an empty sentence
	int sentenceAlloc = 0, err;
	if (sentence == NULL) { // empty vbox
		sentence = fpNodeAlloc(fpnSentence, 0); // todo: check that this is OK...
		sentenceAlloc = 1;
	}

	if (sentence->type != fpnSentence) return -1;

	// typeset
	tsVBox *VBox = new tsVBox(state);
	err = VBox->setup(state, sentence);
	if (!err) row->box.add(&VBox);
	else if (VBox) {
		delete VBox;
		VBox = NULL; // simpy insert a NULL object...
		row->box.add(&VBox);
	}

	// free artificial NULL sentence
	if (sentenceAlloc) fpNodeFree(sentence);

	return 0;
}

