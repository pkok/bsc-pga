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

#include "../gl_includes.h"

#include "typeset.h"
#include "openglfont.h"

#include "../util.h"

typesetState::typesetState() {
	initToNothing();
	
	reset();
	setDefaultColors();

	m_initialFont = tsfRegular;
	m_initialAlign = tsaLeft;
	m_initialMode = tsmText;
	m_initialSize = 12.0;
	m_initialColor = getColor("black");
	m_fontDescent = 0.25;

//	m_initialParseMode = "text";
}

typesetState::~typesetState() {
	reset();
	clearCommands();
	clearColors();

	initToNothing();
}

void typesetState::initToNothing() {
	m_alpha = 1.0;
	m_fontDescent = -1.0;

	m_width = m_height = -1.0; // these are set by typeset()

	m_initialFont = m_initialAlign = m_initialMode = m_initialColor = -1;
	m_initialSize = -1.0;
//	m_initialParseMode = NULL;
}

void typesetState::reset() {
	m_fontStack.clear();
	m_modeStack.clear();
	m_alignStack.clear();
//	m_scriptStack.clear();
	m_sizeStack.clear();
	m_posXStack.clear();
	m_posYStack.clear();
	m_colorStack.clear();

	clearDraw();

	m_fontStack.push(m_initialFont);
	m_modeStack.push(m_initialMode);
	m_alignStack.push(m_initialAlign);
	m_sizeStack.push(m_initialSize);
	m_colorStack.push(m_initialColor);
//	m_scriptStack.push(0);
	m_posXStack.push(0.0);
	m_posYStack.push(0.0);

}

//extern int g_nbFPAllocated;

// parses, but does nothing else (intended for \newcommand feeds and such)
// But: you do lose all current drawing commands...
int typesetState::parse(const char *str) {
	// reset to initial state
	reset();

	// parse
	fpNode *node = fontParse(str, (m_initialMode == tsmEquation) ? "e" : "t");
	if (node == NULL) {
		printf("typesetState::typeset(): could not parse string.\n");
		return -1;
	}

	// setup (this creates an entire tree of boxes, but we'll delete those immidiately)
	tsVBox *VBox = new tsVBox(this);
	VBox->setup(this, node);
	delete VBox;

	// free parse tree
	fpNodeFree(node);

	// reset to initial state (this does not lose new commands)
	reset();

	return 0;
}

int typesetState::typeset(const char *str, double maxWidth /*= -1.0*/) {
	// reset to initial state
	reset();

	// parse
	fpNode *node = fontParse(str, (m_initialMode == tsmEquation) ? "e" : "t");
	if (node == NULL) {
		printf("typesetState::typeset(): could not parse string.\n");
		return -1;
	}

//	fpNodePrint(node);

	// typeset
	tsVBox *VBox = new tsVBox(this);
	VBox->setup(this, node);
	reset();		 // reset all to initial state
//	pushTrans(0.0, -VBox->m_descent);
	pushTrans(0.0, -VBox->m_ascent); // todo OK?
	VBox->typeset(this, maxWidth);
	popTrans();

	// free parse tree
	fpNodeFree(node);

	// set width, height
	m_width = VBox->m_width;
	m_height = VBox->m_ascent - VBox->m_descent;

	// free the box (all the drawing commands are in m_tsXXX now)
	delete VBox;

	return 0;
}

int typesetState::GLdraw() {
	int i, j, t;
	float w = -1.0f;
	tsColorData *color;

    // draw characters
	oglfPrintCharRawBegin();
	for (i = 0; i < m_tsChar.m_nb; i++) {
		color = &(m_colorList[m_tsChar[i].color]);
//		printf("Color '%d': %f %f %f\n", m_tsChar[i].color, color->r, color->g, color->b);
		glColor4f(color->r, color->g, color->b, m_alpha);
		oglfPrintCharRaw(m_tsChar[i].c, (float)m_tsChar[i].x, (float)m_tsChar[i].y - (float)m_fontDescent * (float)m_tsChar[i].size, (float)m_tsChar[i].size);
	}
	oglfPrintCharRawEnd();

    // draw lines
	t = -1;
	for (i = 0; i < m_tsLine.m_nb; i++) {
		color = &(m_colorList[m_tsLine[i].color]);
		glColor4f(color->r, color->g, color->b, m_alpha);

		// change line type if required
/*		if (m_tsLine[i].type != t) {
			if (t != -1) glEnd();
			glBegin(t = m_tsLine[i].type);
		}*/

		// change width if required
		if (m_tsLine[i].width != w)
			glLineWidth(w = m_tsLine[i].width);

		// draw the vertices
		glBegin(m_tsLine[i].type);
		for (j = 0; j < m_tsLine[i].nbVertices; j++) {
			glVertex2dv(m_tsLine[i].xy + j * 2);
		}
		glEnd();
	}
	//glEnd();

	glDisable(GL_CULL_FACE);
	// draw polygons
	for (i = 0; i < m_tsPolygon.m_nb; i++) {
		color = &(m_colorList[m_tsPolygon[i].color]);
		glColor4f(color->r, color->g, color->b, m_alpha);

		glBegin(m_tsPolygon[i].type);
		// draw the vertices
		for (j = 0; j < m_tsPolygon[i].nbVertices; j++)
			glVertex2dv(m_tsPolygon[i].xy + j * 2);
		glEnd();
	}



	return 0;
}


int typesetState::setInitialMode(const char *mode) {
	if ((mode[0] != 't') && (mode[0] != 'T') && (mode[0] != 'e') && (mode[0] != 'E'))
		return -1;

	setInitialMode(((mode[0] == 'e') || (mode[0] == 'E')) ? tsmEquation : tsmText);
	return 0;
}

int typesetState::getColor(const char *name) {
	int i;
	for (i = 0; i < m_colorList.m_nb; i++) {
		if (!strcmp(name, m_colorList[i].name))
			return i;
	}
	return -1;
}

int typesetState::setColor(const char *name, float r, float g, float b) { //, float a /* = 1.0 */) {
	int i;

	if ( (i = getColor(name)) >= 0) {
//		printf("Set color '%s' (%d) to %f %f %f\n", name, i, r, g, b);
		m_colorList[i].r = r;
		m_colorList[i].g = g;
		m_colorList[i].b = b;
		//m_colorList[i].b = a;
		return 0;
	}
	tsColorData c;
	c.r = r;
	c.g = g;
	c.b = b;
	//c.a = a;
	if ( (c.name = strdup(name)) == NULL) return -1;
	m_colorList.add(&c);

	return 0;
}

int typesetState::clearColors() {
	int i;
	for (i = 0; i < m_colorList.m_nb; i++) {
		if (m_colorList[i].name) free(m_colorList[i].name);
	}
	m_colorList.clear();

	return 0;
}

int typesetState::setDefaultColors() {
	int i;
	const char *cn[] = {
		"red", "green", "blue", "magenta", "yellow", "cyan", "black", "white", "grey", "gray", NULL
	};
	float c[4];

	i = 0;
	while (cn[i]) {
		::getColor(cn[i], c);
		setColor(cn[i], c[0], c[1], c[2]);
		i++;
	}
/*
	
	setColor("red", 1.0, 0.0, 0.0);
	setColor("green", 0.0, 1.0, 0.0);
	setColor("blue", 0.0, 0.0, 1.0);
	setColor("magenta", 1.0, 0.0, 1.0);
	setColor("yellow", 1.0, 1.0, 0.0);
	setColor("cyan", 0.0, 1.0, 1.0);
	setColor("black", 0.0, 0.0, 0.0);
	setColor("white", 1.0, 1.0, 1.0);
	setColor("grey", 0.5f, 0.5f, 0.5f);
	setColor("gray", 0.5f, 0.5f, 0.5f);
*/
	return 0;
}


int typesetState::font() const {return m_fontStack.top();};
int typesetState::mode() const {return m_modeStack.top();};
int typesetState::align() const {return m_alignStack.top();};
int typesetState::color() const {return m_colorStack.top();};
//int typesetState::script() const {return m_scriptStack.top();};
double typesetState::size() const {return m_sizeStack.top();};
void typesetState::pos(double &x, double &y) const {x = m_posXStack.top(); y = m_posYStack.top();};
double typesetState::posX() const {return m_posXStack.top();};
double typesetState::posY() const {return m_posYStack.top();};

int typesetState::popFont() {return m_fontStack.pop();};
int typesetState::popMode() {return m_modeStack.pop();};
int typesetState::popAlign() {return m_alignStack.pop();};
int typesetState::popColor() {return m_colorStack.pop();};
//int typesetState::popScript() {return m_scriptStack.pop();};
double typesetState::popSize() {return m_sizeStack.pop();};
void typesetState::popPos() {m_posXStack.pop(); m_posYStack.pop(); } 

void typesetState::pushFont(int f) {m_fontStack.push(f);};
void typesetState::pushMode(int m) {m_modeStack.push(m);};
void typesetState::pushAlign(int a) {m_alignStack.push(a);};
void typesetState::pushColor(int c) {m_colorStack.push(c);};
////	void pushScript(int a) {m_scriptStack.push(a);};
void typesetState::pushSize(double s) {m_sizeStack.push(s);};
void typesetState::pushTrans(double x, double y) {pushPos(posX() + x, posY() + y);};
void typesetState::pushPos(double x, double y) {m_posXStack.push(x); m_posYStack.push(y); };


int typesetState::setInitialFont(int font) {
	m_initialFont = font;
	return 0;
}

int typesetState::setInitialFont(const char *font) {
	if (font == NULL) return -1;
	char f = font[0];

	if ((f == 'r') || (f == 'R')) return setInitialFont(tsfRegular);
	else if ((f == 'b') || (f == 'B')) return setInitialFont(tsfBold);
	else if ((f == 'i') || (f == 'I')) return setInitialFont(tsfItalic);
	else if ((f == 'g') || (f == 'G')) return setInitialFont(tsfGreek);
	else {
		printf("typesetState::setInitialFont(): unknown font '%s'\n", font);
		return -1;
	}
}


int typesetState::setInitialAlign(int align) {
	m_initialAlign = align;
	return 0;
}

int typesetState::setInitialMode(int mode) {
	m_initialMode = mode;
	return 0;
}

int typesetState::setInitialSize(double size) {
	m_initialSize = size;
	return 0;
}

int typesetState::setInitialColor(int idx) {
	if ((idx < 0) || (idx >= m_colorList.m_nb)) return -1;
	//printf("Set initial color to %d\n", idx);
	m_initialColor = idx;
	return 0;
}

double typesetState::addChar(int c, double x, double y, int Color) {
	tsCharData d;
	d.c = c;
	d.x = x + posX();
	d.y = y + posY();
	d.size = size();
	d.color = Color;

/*	tsColorData *color;
	color = &(m_colorList[Color]);
	printf("addChar(): color '%d': %f %f %f\n", Color, color->r, color->g, color->b);*/

	if (m_tsChar.add(&d)) return -1;
	else return d.size * oglfCharWidth(c);
}

int typesetState::addLine(int nbVertices, int type, double *x, double *y, float width, int Color) {
	tsLineData d;
	int i;

	if (nbVertices <= 1) return 0;
	if ( (d.xy = (double*)malloc(sizeof(double) * 2 * nbVertices)) == NULL) {
		printf("typesetState::addLine(): memory allocation failure for '%d' bytes\n", sizeof(double) * 2 * nbVertices);
		return -1;
	}
	d.nbVertices = nbVertices;
	d.color = Color;
	d.width = width;
	d.type = type;

	for (i = 0; i < nbVertices; i++) {
		d.xy[i * 2] = x[i] + posX();
		d.xy[i * 2 + 1] = y[i] + posY();
	}

	return m_tsLine.add(&d);
}

int typesetState::addPolygon(int nbVertices, int type, double *x, double *y, int Color) {
	tsPolygonData d;
	int i;

	if (nbVertices <= 2) return 0;
	if ( (d.xy = (double*)malloc(sizeof(double) * 2 * nbVertices)) == NULL) {
		printf("typesetState::addPolygon(): memory allocation failure for '%d' bytes\n", sizeof(double) * 2 * nbVertices);
		return -1;
	}
	d.nbVertices = nbVertices;
	d.color = Color;
	d.type = type;

	for (i = 0; i < nbVertices; i++) {
		d.xy[i * 2] = x[i] + posX();
		d.xy[i * 2 + 1] = y[i] + posY();
	}

	return m_tsPolygon.add(&d);
}

fpNode * typesetState::getCommand(const char *name) {
	int i;

	for (i = 0; i < m_command.m_nb; i++) {
		if (m_command[i] &&
			(!strcmp(m_command[i]->str, name))) 
			return m_command[i];
	}

	return NULL;
}

int typesetState::setCommand(const char *name, fpNode *node) {
	int i;

	// set sentence 'name' = command name
	if (node->str) return -1;
	if ( (node->str = strdup(name)) == NULL) return -1;

	for (i = 0; i < m_command.m_nb; i++) {
		if (m_command[i] &&
			(!strcmp(m_command[i]->str, name)))  {
				fpNodeFree((fpNode*)m_command.m_item[i]);
				m_command.m_item[i] = node;
				return 0;
		}
	}
	m_command.add(&node);

	return 0;
}

int typesetState::clearCommands() {
	int i;
	for (i = 0; i < m_command.m_nb; i++) {
		if (m_command[i]) fpNodeFree(m_command[i]);
	}
	m_command.clear();

	return 0;
}

int typesetState::setAlpha(float alpha) {
	m_alpha = alpha;
	return 0;
}

int typesetState::clearDraw() {
	int i;
	for (i = 0; i < m_tsLine.m_nb; i++)
		if (m_tsLine[i].xy) free(m_tsLine[i].xy);
	for (i = 0; i < m_tsPolygon.m_nb; i++)
		if (m_tsPolygon[i].xy) free(m_tsPolygon[i].xy);
	m_tsChar.clear();
	m_tsLine.clear();
	m_tsPolygon.clear();

	return 0;
}
