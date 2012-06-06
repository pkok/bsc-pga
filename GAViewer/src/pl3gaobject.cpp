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
#include <math.h>

#include "gl_includes.h"

#include "object.h"
#include "glwindow.h"
#include "state.h"
#include "util.h"
#include "osdep.h"
#include "draw.h"
#include "geosphere.h"
#include "uistate.h"

#define DRAW_LINE_CURVE 0
#define DRAW_LINE_CURLYTAIL 1
#define DRAW_LINE_HOOKS 2
#define DRAW_LINE_HOOKCROSSES 3

//Grade 1
Fl_Menu_Item gui_pl3gaLineDrawMethods[] = {
	{"Curve", 0, NULL, (void*)DRAW_LINE_CURVE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_LINE_CURLYTAIL, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKS, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKCROSSES, 0},
	{0}
};

Fl_Menu_Item gui_pl3gaScrewDrawMethods[0];
Fl_Menu_Item gui_pl3gaKineDrawMethods[0];

//Grade 2
Fl_Menu_Item gui_pl3gaLinePencilDrawMethods[0];
Fl_Menu_Item gui_pl3gaLinePairDrawMethods[0];
Fl_Menu_Item gui_pl3gaLineTangentDrawMethods[0];
Fl_Menu_Item gui_pl3gaDualRegulusPencilDrawMethods[0];

//Grade 3
Fl_Menu_Item gui_pl3gaLineBundleDrawMethods[0];
Fl_Menu_Item gui_pl3gaLineFieldDrawMethods[0];
Fl_Menu_Item gui_pl3gaRegulusDrawMethods[0];
Fl_Menu_Item gui_pl3gaDoubleWheelPencilDrawMethods[0];

//Grade 4
Fl_Menu_Item gui_pl3gaRegulusPencilDrawMethods[0];
Fl_Menu_Item gui_pl3gaParabolicLineCongruenceDrawMethods[0];
Fl_Menu_Item gui_pl3gaLinePairDualDrawMethods[0];
Fl_Menu_Item gui_pl3gaLineFieldAndBundleDrawMethods[0];

//Grade 5
Fl_Menu_Item gui_pl3gaLineDualDrawMethods[0];
Fl_Menu_Item gui_pl3gaRegulusBundleDrawMethods[0];


pl3gaObject::pl3gaObject(const pl3ga &mv, const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) 
	: object(OT_I2GA, name, drawMode, creationFlags) {
	initToNothing();
	m_mv = mv;
	m_int.interpret(m_mv, creationFlags);

	// set general properties
	m_properties = OP_NAME | OP_DESCRIPTION;

	// unless the object is of unknown type, set the drawing properties
	if (m_int.m_type != MVI_UNKNOWN) {
		m_properties |= OP_HIDE | OP_FGCOLOR | OP_DRAWMODE;
		if (m_int.versor()) m_properties |= OP_BGCOLOR | OP_OLCOLOR;

		if (!(forceFlags & OFF_SHADE))
			m_drawMode |= OD_SHADE;

		// set draw method + menu
		if (m_int.blade()) {
			// some examples:
/*			if (m_int.type() == MVI_LINE) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_pl3gaLineDrawMethods;
				m_dmMenuIdx = DRAW_LINE_HOOKS;
			}
			else if ((m_int.type() == MVI_FREE_BIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_BIVECTOR)) {
			}
			else if ((m_int.type() == MVI_FREE_TRIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_TRIVECTOR)) {
			}
			else if (m_int.type() == MVI_POINT_PAIR) {
			}*/
		}
	}

	// override draw method with user setting
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;
}

pl3gaObject::~pl3gaObject() {
	initToNothing();
}

void pl3gaObject::initToNothing() {
	m_mv = 0;
}

int pl3gaObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const pl3gaObject *pl3gaO = (const pl3gaObject *)o;

	if ((m_mv - pl3gaO->m_mv).norm_a() != 0.0)
		propertiesChanged |= OP_DESCRIPTION;
	m_mv = pl3gaO->m_mv;
	m_int.copy(&pl3gaO->m_int);

	return 0;
}

int pl3gaObject::pick(glwindow *window) {
	return draw(window);
}

int pl3gaObject::draw(glwindow *window) {
	// draws nothing yet
	return  0;
}

int pl3gaObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	// can not translate yet
	return 0;
}


int pl3gaObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	buf[0] = 0;

	if (m_int.type() == MVI_UNKNOWN) {
		if (sl) sprintf(buf, "%s: unknown pl3ga object", m_name.c_str());
		else sprintf(buf, "Unknown pl3ga object.\nCoordinates: %s", m_mv.string());
	}

	return 0;
}

float pl3gaObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

std::string pl3gaObject::toString(const char *floatPrec /* = "%e" */) {
	return std::string("\"" + m_name + "\" = " +  m_mv.string(floatPrec));
}
