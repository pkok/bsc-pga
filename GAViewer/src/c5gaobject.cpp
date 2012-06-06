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
#include "tubedraw.h"
#include "c3gadraw.h"
#include "console/consolevariable.h"


Fl_Menu_Item gui_c5gaLineDrawMethods[] = {
	{"Curve", 0, NULL, (void*)DRAW_LINE_CURVE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_LINE_CURLYTAIL, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKS, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKCROSSES, 0},
	{0}
};


Fl_Menu_Item gui_c5gaBivectorDrawMethods[] = {
	{"Circle", 0, NULL, (void*)DRAW_BV_CIRCLE, 0},
	{"Parallelogram", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM, 0},
	{"Parallelogram w.o. vectors", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM_NO_VECTORS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CURLYTAIL, 0},
	{"Swirl", 0, NULL, (void*)DRAW_BV_SWIRL, 0},
	{0}
};

Fl_Menu_Item gui_c5gaTrivectorDrawMethods[] = {
	{"Sphere", 0, NULL, (void*)DRAW_TV_SPHERE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CURLYTAIL, 0},
	{0}
};



Fl_Menu_Item gui_c5gaPointPairDrawMethods[] = {
	{"Two points, connected when ori is on", 0, NULL, (void*)DRAW_PP_CONNECTED_ON_ORI, 0},
	{"Two points, connected", 0, NULL, (void*)DRAW_PP_CONNECTED, 0},
	{"Two points", 0, NULL, (void*)DRAW_PP_LOOSE, 0},
	{"Line segment", 0, NULL, (void*)DRAW_PP_LINE_SEGMENT, 0},
	{0}
};



c5gaObject::c5gaObject(const c5ga &mv, const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) 
	: conformalObject(OT_C5GA, name, drawMode, creationFlags) {
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
			if (m_int.type() == MVI_LINE) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_c5gaLineDrawMethods;
				m_dmMenuIdx = DRAW_LINE_HOOKS;
			}
			else if ((m_int.type() == MVI_FREE_BIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_BIVECTOR)) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_c5gaBivectorDrawMethods;
				m_dmMenuIdx = DRAW_BV_CIRCLE;
			}
			else if ((m_int.type() == MVI_FREE_TRIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_TRIVECTOR)) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_c5gaTrivectorDrawMethods;
				m_dmMenuIdx = DRAW_TV_SPHERE;
			}
			else if (m_int.type() == MVI_POINT_PAIR) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_c5gaPointPairDrawMethods;
				m_dmMenuIdx = DRAW_PP_CONNECTED_ON_ORI;
			}
		}
	}

	// override draw method with user setting
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;
}

c5gaObject::~c5gaObject() {

	initToNothing();
}

void c5gaObject::initToNothing() {
	m_mv = 0;
}

int c5gaObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const c5gaObject *c5gaO = (const c5gaObject *)o;

	if ((m_mv - c5gaO->m_mv).norm_a() != 0.0)
		propertiesChanged |= OP_DESCRIPTION;
	m_mv = c5gaO->m_mv;
	m_int.copy(&c5gaO->m_int);


	return 0;
}

int c5gaObject::pick(glwindow *window) {
	return draw(window);
}


int c5gaObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	e3ga v;
	window->vectorAtDepth(depth, motionX, -motionY, v);
	c5ga t(GRADE1, v[GRADE1][E3GA_E1], v[GRADE1][E3GA_E2], v[GRADE1][E3GA_E3], 0, 0, 0, 0);
	c5ga tv(1 - 0.5 * (t ^ c5ga::ni));

	int modified = 0;
	if (m_int.blade()) {
		switch (m_int.type()) {
		case MVI_ZERO:
		case MVI_SCALAR:
		case MVI_FREE_SCALAR:
		case MVI_FREE_BIVECTOR:
		case MVI_FREE_TRIVECTOR:
		case MVI_POINT:
		case MVI_FLAT_POINT:
		case MVI_LINE: 
		case MVI_PLANE: 
		case MVI_BOUND_TANGENT_VECTOR:
		case MVI_BOUND_TANGENT_BIVECTOR:
		case MVI_BOUND_TANGENT_TRIVECTOR:
		case MVI_POINT_PAIR:
		case MVI_CIRCLE:
		case MVI_SPHERE:
			m_mv = tv.inverse() * m_mv * tv;
			modified = 1;
			break;
		case MVI_FREE_VECTOR:
			//(c5ga::no << m_mv).print("Inter: ");
			m_mv = ((c5ga::no << m_mv) - t) ^ c5ga::ni;
			modified = 1;
			break;
		}
	}

	if (modified) {
		m_int.interpret(m_mv); // reinterpret
		g_state->modified(m_name);
	}


	return 0;
}


int c5gaObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	int dim = 5;
	c3ga tmp;
	consoleVariable::castC5gaToC3ga(m_mv, tmp);
	return conformalObject::description(tmp, dim, buf, bufLen, sl);
}



float c5gaObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

std::string c5gaObject::toString(const char *floatPrec /* = "%e" */) {
	return std::string("\"" + m_name + "\" = " +  m_mv.string(floatPrec));
}
 