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

#ifndef _TYPESETBOX_H_
#define _TYPESETBOX_H_

#include "liststack.h"

// box types
enum {
	tsbInvalid = -1,
	tsbV,
	tsbH,
	tsbWord,
	tsbSqrt,
	tsbFrac,
	tsbNumber,
	tsbTabular,
	tsbWhiteSpace,
	tsbScript,
	tsbPar,
	tsbHat
};

class typesetState;
class tsScriptBox;

class typesetBox {
public:
	typesetBox(typesetState *state, int type);
	typesetBox(const typesetBox *copyBox, int type);
	virtual ~typesetBox();

	void initToNothing();

	int m_font; // tsfXXX
	int m_align; // tsaXXX
	int m_mode; // tsmXXX
	double m_fontSize; // font size
	int m_color; // idx into state color list

	int m_type; // tsbXXX

	int insertChild(int idx, typesetBox *box);
	int addChild(typesetBox *box);
	int removeChild(int idx);
	int removeChild(const typesetBox *ptr);
	int m_nbChildren;
	typesetBox **m_child;
	// parent required / easy??

	int setPos(double x, double y);

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	double m_x, m_y;
	double m_width, m_ascent, m_descent;

	// return true if operator / whitespace
	int eqnOperator();
	int whiteSpace();


protected:
	typesetBox *lastBox(); //returns the most recent child box in this box
	typesetBox *lastBoxOfType(const int *type); // type terminated with tsbInvalid (-1)
	typesetBox *lastBoxNotOfType(const int *type); // type terminated with tsbInvalid (-1)

	int *convertStr(const char *asciiStr); // takes an ASCII string, returns the string converted to 'font' string, according to 'm_font'
	int *convertChr(int c);
	int fontStrlen(const int *fontStr);
	int strSize(typesetState *state, const int *fontStr, double &width, double &ascent, double &descent);
	int fontBase(int font); // returns the base (in the final 'output' font) of a font
	int lookupGreekSymbol(const char *name);
	int lookupSpecialSymbol(const char *name);

	inline double dmin(double x, double y) {return (x < y) ? x : y;};
	inline double dmax(double x, double y) {return (x > y) ? x : y;};


	// returns the first option in an optionlist
	// if 'warnMultiple' is true, a warning is printed if there are multiple options in the list
	// 'callStr' (the calling function) and 'cmdStr' (the command being processed) are used for error messages
	int getFirstOption(struct fpNode_s *optionListNode, struct fpNode_s **firstOption, 
						   int warnMultiple, const char *callStr, const char *cmdStr);

	// returns the 'n' options in an optionlist
	// if 'warn' is true, a warning is printed if there are to few or to much options in the list
	// 'callStr' (the calling function) and 'cmdStr' (the command being processed) are used for error messages
	// 'nb' is used to receive the required number of options and to return the number of options found
	int getOptions(int &nb, struct fpNode_s *optionListNode, struct fpNode_s *option[], 
						   int warn, const char *callStr, const char *cmdStr);

};


class tsVBox : public typesetBox {
public:
	tsVBox(typesetState *state);
	virtual ~tsVBox();

	void initToNothing();

	int setup(typesetState *state, struct fpNode_s *node);
	int typeset(typesetState *state, double maxWidth = -1.0);

};


class tsHBox : public typesetBox {
public:
	tsHBox(typesetState *state);
	tsHBox(const tsHBox *copyBox);
	virtual ~tsHBox();

	void initToNothing();

	int setup(typesetState *state, 
				  struct fpNode_s *currentNode, struct fpNode_s **nextNode, 
				  struct fpNode_s *rootNode);

	virtual int typeset(typesetState *state);


	int computeSize();

	// maybe call these all from one function:
	int deleteTrailingWhiteSpace(); // removes all white space boxes from the end of this HBox
	int spaceEqnOperators(typesetState *state);
	int setAlignment();

	double m_maxWidth;

protected:
	int setupCommand(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode);

	// the following functions process font, align, mode, color, scale commands...
	int setFont(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int font);

	int setAlignment(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int alignment);

	int setMode(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int mode);

	int setColor(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode,
						 int colorIdx);

	int scale(typesetState *state, 
						 struct fpNode_s *currentNode, struct fpNode_s **nextNode);

	int handleFAMCommand(struct fpNode_s *currentNode, 
							struct fpNode_s **nextNode,
							struct fpNode_s **lastNode,
							const char *cmdStr);

	int setupCommandNoOption(typesetState *state, 
		struct fpNode_s *currentNode, struct fpNode_s **nextNode,
		int *newLine);


	// scans backward, deleting all nodes not suitable for script, 
	// returns suitable first box found, turns it into a script box if neccessary 
	// returns negative on error
	int getScriptBox(typesetState *state, tsScriptBox **scriptBox);

	int	processNewColor(typesetState *state, struct fpNode_s *currentNode);

	int processNewCommand(typesetState *state, struct fpNode_s *currentNode);
	int processCustomCommand(typesetState *state, struct fpNode_s *currentNode, struct fpNode_s **nextNode, struct fpNode_s *cmdNode);


};

class tsWordBox : public typesetBox {
public:
	tsWordBox(typesetState *state, struct fpNode_s *node) ;
	tsWordBox(typesetState *state, const char *str);
	tsWordBox(typesetState *state, int chr);
	virtual ~tsWordBox();

	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	int eqnOperator(); //returns true if this is an operator symbol

	int *m_fontStr;
protected:
	int init(typesetState *state, int chr);
	int init(typesetState *state, const char *str);
};

class tsWhiteSpaceBox : public typesetBox {
public:
	tsWhiteSpaceBox(typesetState *state, struct fpNode_s *node);
	tsWhiteSpaceBox(typesetState *state, double width);
	virtual ~tsWhiteSpaceBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 

	int m_forced; // true if this is 'forced' whitespace (i.e., \ws{2.0})
};

class tsNumberBox : public typesetBox {
public:
	tsNumberBox(typesetState *state, struct fpNode_s *node) ;
	virtual ~tsNumberBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);
};

class tsScriptBox : public typesetBox {
public:
	tsScriptBox(typesetState *state, typesetBox *baseBox);
	virtual ~tsScriptBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	int addSuperscript(typesetState *state, struct fpNode_s *node);
	int addSubscript(typesetState *state, struct fpNode_s *node);

	int m_subscript, m_superscript;

protected:
	int computeSize();
	int addScript(typesetState *state, struct fpNode_s *node, int super, const char *ssStr);
};

class tsFracBox : public typesetBox {
public:
	tsFracBox(typesetState *state, struct fpNode_s *node) ;
	virtual ~tsFracBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	double m_lineY;

	tsHBox *setup(typesetState *state, struct fpNode_s *option);
};

class tsSqrtBox : public typesetBox {
public:
	tsSqrtBox(typesetState *state, struct fpNode_s *node);
	virtual ~tsSqrtBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

//	double m_lineY;

	tsHBox *setup(typesetState *state, struct fpNode_s *option, double scale);
};

typedef struct parDesc_s {
	double x1, y1, x2, y2, stretchable;
} parDesc;

class tsParBox : public typesetBox {
public:
	tsParBox(typesetState *state, struct fpNode_s *node);
	virtual ~tsParBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	tsHBox *setup(typesetState *state, struct fpNode_s *option, double scale);

protected:
	double parWidth(const parDesc *desc);
	int setupPar(typesetState *state, const parDesc *par, double x, double y, double h, double fontHeight, double scaleX);
	const parDesc *m_leftPar;
	const parDesc *m_rightPar;
	double m_leftWidth, m_rightWidth;
};

enum {
	tshHat,
	tshWideHat,
	tshTilde,
	tshWideTilde,
	tshBar,
	tshWideBar
};
typedef struct hatDesc_s {
	double x1, y1, x2, y2;
} hatDesc;
class tsHatBox : public typesetBox {
public:
	tsHatBox(typesetState *state, struct fpNode_s *node);
	virtual ~tsHatBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

	tsHBox *setup(typesetState *state, struct fpNode_s *option);

protected:
	int m_hatType; // tshXXX
};


#define tstcLineLeft 1
#define tstcLineRight 2

typedef struct tsTabularRow_s {
	tsItemList<tsVBox *> box;
	double ascent;
	double descent;
	int rowType; // 0 = ordinary, 1 = line, 2 = space
} tsTabularRow;

class tsTabularBox : public typesetBox {
public:
	tsTabularBox(typesetState *state, struct fpNode_s *node);
	virtual ~tsTabularBox();
	void initToNothing();

	virtual double stretch(); // returns how much this box can stretch (horizontally) 
	virtual int typeset(typesetState *state);

//	tsHBox *setup(typesetState *state, struct fpNode_s *option);

protected:
	tsItemList<int> m_format; // format: string of [tsaLeft, tsaRight, tsaCenter, tsaJustify, tsaVLine]
	tsItemList<tsTabularRow*> m_row;
	tsItemList<double> m_columnWidth; // width of each column
	tsItemList<double> m_columnStretch; // stretch of each column

	int setFormat(struct fpNode_s *option);
	void deleteRow(tsTabularRow*row);
	int setupRow(typesetState *state, tsTabularRow*row, struct fpNode_s *option);
	int setupRowEntry(typesetState *state, tsTabularRow*row, struct fpNode_s *sentence);

	double m_vlineWidth; // sum of the width of all vertical lines
	int m_nbColumns; // true number of columns (not including vlines)

	double m_vlWidth, m_hlWidth; // constants: the width of the vertical and horizontal lines (based on m_fontSize)
};


#endif /* _TYPESETBOX_H_ */
