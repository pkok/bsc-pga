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

#ifndef _TYPE_SET_H_
#define _TYPE_SET_H_

#include "fontparse.h"
#include "typesetbox.h"
#include "liststack.h"

// font
enum {
	tsfRegular,
	tsfBold,
	tsfItalic,
	tsfGreek,
	tsfMath // math is a combination of regular (numbers) and italic
};

// mode 
enum {
	tsmText,
	tsmEquation
};

// alignment
enum {
	tsaLeft,
	tsaRight,
	tsaCenter,
	tsaJustify,
	tsaVLine = 256, // vertical line, used in tabulars
	tsaVSpace // vertical space, used in tabulars
};

typedef struct tsCharData_s {
	int c;
	double x, y;
	double size;
	int color; // color not implemented yet
} tsCharData;

typedef struct tsLineData_s {
	int nbVertices;
	double *xy;
	float width;
	int type; // GL_LINES, GL_LINE_LOOP, etc
	int color; // color not implemented yet
} tsLineData;

typedef struct tsPolygonData_s {
	int nbVertices;
	double *xy;
	int type; // GL_POLYGON, GL_QUADS, etc
	int color; // color not implemented yet
} tsPolygonData;

typedef struct tsColorData_s {
	float r, g, b; //, a;
	char *name;
} tsColorData;


class typesetState {
public:
	typesetState();
	~typesetState();

	void initToNothing();
	void reset();

	// parses, but does nothing else (intended for \newcommand feeds and such)
	// But: you do lose all current drawing commands...
	int parse(const char *str);

	// parses, and sets up drawing commands
	int typeset(const char *str, double maxWidth = -1.0);
	double m_width, m_height; // these are set by typeset()

	// draws the input (after typeset() has been called), using OpenGL
	int GLdraw();
	// removes all drawing commands from typeset state (todo)
	int clearDraw(); // remove all drawing commands from the state

	double addChar(int c, double x, double y, int Color); // (returns -1.0 on failure, otherwise the width of the character)
	int addLine(int nbVertices, int type, double *x, double *y, float width, int Color);
	int addPolygon(int nbVertices, int type, double *x, double *y, int Color);

	int font() const;
	int mode() const;
	int align() const;
//	int script() const;
	int color() const;
	double size() const;
	void pos(double &x, double &y) const;
	double posX() const;
	double posY() const;

	int popFont();
	int popMode();
	int popAlign();
//	int popScript();
	int popColor();
	double popSize();
	void popPos();
	inline void popTrans() {popPos();}

	void pushFont(int f);
	void pushMode(int m);
	void pushAlign(int a);
	void pushColor(int c);
////	void pushScript(int a) {m_scriptStack.push(a);};
	void pushSize(double s);
	void pushTrans(double x, double y);
	void pushPos(double x, double y);

	int setInitialFont(int font);
	int setInitialFont(const char *font); // regular, bold, italic, greek
	int setInitialAlign(int align);
	int setInitialMode(const char *mode); // "text", "txt" or "equation", "eqn"
	int setInitialMode(int mode);
	int setInitialSize(double size);
	int setInitialColor(int idx);
	int setAlpha(float alpha);

	int getColor(const char *name); // returns index of color, or -1 on error
	int setColor(const char *name, float r, float g, float b); // adds a color to the list of colors for this state
	int setDefaultColors();
	int clearColors();

	fpNode * getCommand(const char *name);
	int setCommand(const char *name, fpNode *node);
	int clearCommands();


	double m_fontDescent;

protected:

	// custom commands:
	tsItemList<fpNode *> m_command;

	// stacks:
	tsStack<int> m_fontStack; // tsfXXX
	tsStack<int> m_modeStack; // tsmXXX
	tsStack<int> m_alignStack; // tsaXXX
	tsStack<int> m_colorStack; // idx into m_colorList
//	tsStack<int> m_scriptStack; // true (1) or false (0)
	tsStack<double> m_sizeStack; // font size (in pixels)
	tsStack<double> m_posXStack; // drawing position (in pixels)
	tsStack<double> m_posYStack; // drawing position (in pixels)

	// typeset items:
	tsItemList<tsCharData> m_tsChar;
	tsItemList<tsLineData> m_tsLine;
	tsItemList<tsPolygonData> m_tsPolygon;

	// colors:
	tsItemList<tsColorData> m_colorList;

	int m_initialFont;
	int m_initialAlign;
	int m_initialMode;
	double m_initialSize;
	int m_initialColor;
	float m_alpha;

//	const char *m_initialParseMode; // not dynamically allocated, so don't free this 

};





#endif /* _TYPE_SET_H_ */
