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
#include "draw.h"
#include "uistate.h"
#include "osdep.h"

Fl_Menu_Item gui_e3gaBivectorDrawMethods[] = {
	{"Circle", 0, NULL, (void*)DRAW_BV_CIRCLE, 0},
	{"Parallelogram", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM, 0},
	{"Parallelogram w.o. vectors", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM_NO_VECTORS, 0},
//	{"Cross", 0, NULL, (void*)DRAW_BV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CURLYTAIL, 0},
	{"Swirl", 0, NULL, (void*)DRAW_BV_SWIRL, 0},
	{0}
};

Fl_Menu_Item gui_e3gaTrivectorDrawMethods[] = {
	{"Sphere", 0, NULL, (void*)DRAW_TV_SPHERE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CURLYTAIL, 0},
	{"Parallelepiped", 0, NULL, (void*)DRAW_TV_PARALLELEPIPED, 0},
	{"Parallelepiped w.o. vectors", 0, NULL, (void*)DRAW_TV_PARALLELEPIPED_NO_VECTORS, 0},
	{0}
};

e3gaObject::e3gaObject(const e3ga &mv, const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) : object(OT_E3GA, name, drawMode, creationFlags, forceFlags) {
	initToNothing();
	m_mv = mv;
	m_int.interpret(m_mv, creationFlags);

	m_properties = OP_FGCOLOR | OP_NAME | OP_DESCRIPTION | OP_DRAWMODE;

	if (!(forceFlags & OFF_SHADE))
		m_drawMode |= OD_SHADE;

	if (m_int.type() != MVI_UNKNOWN)
		m_properties |= OP_HIDE;

	switch (m_int.type()) {
	case MVI_BIVECTOR:
		m_properties |= OP_DRAWMETHOD;
		m_dmMenu = gui_e3gaBivectorDrawMethods;
		m_dmMenuIdx = 0;
		break;
	case MVI_TRIVECTOR:
		m_properties |= OP_DRAWMETHOD;
		m_dmMenu = gui_e3gaTrivectorDrawMethods;
		m_dmMenuIdx = 0;
		break;
	}

	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;

}

e3gaObject::~e3gaObject() {

	initToNothing();
}

void e3gaObject::initToNothing() {
	m_mv = 0;
}

int e3gaObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const e3gaObject *e3gaO = (const e3gaObject *)o;

	if ((m_mv - e3gaO->m_mv).norm_a() != 0.0)
		propertiesChanged |= OP_DESCRIPTION;
	m_mv = e3gaO->m_mv;
	m_int.copy(&e3gaO->m_int);
	return 0;
}


int e3gaObject::pick(glwindow *window) {
	return draw(window);
}

int e3gaObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	e3ga v;
	GAIM_FLOAT m, mnew;

	int modified = 0;
	switch (m_int.type()) {
	case MVI_VECTOR:
		window->vectorAtDepth(depth, motionX, -motionY, v);
		m_mv -= v;
		modified = 1;
		break;
	case MVI_SCALAR:
	case MVI_BIVECTOR:
	case MVI_TRIVECTOR:
		m = sqrt(m_mv.norm_a());
		mnew = (m + (GAIM_FLOAT)(-motionX + motionY) / 30.0);
		if (mnew < 0.0001) mnew = m;
		m_mv = (m_mv / m) * mnew;
		modified = 1;
		break;
	case MVI_ROTOR:
		break;
	default:
		break;
	}

	if (modified) {
		m_int.interpret(m_mv); // reinterpret
		g_state->modified(m_name);
	}


	return 0;
}


/*
This function should draw the multivector interpretation.
The interpretation is stored in m_int (see mivnt.h for class).
Check the this->m_drawMode variable (controlled through UI) 
to see how you should draw the object. It is a bitwise or of the 
following:
#define OD_STIPPLE (1 << 0)
#define OD_ORI (1 << 1)  // normals and the like
#define OD_WIREFRAME (1 << 3)
#define OD_SHADE (1 << 4)
#define OD_MAGNITUDE (1 << 5)
*/
int e3gaObject::draw(glwindow *window) {
	TubeDraw &T = gui_state->m_tubeDraw;

	GAIM_FLOAT scale, scaleSign;

	if (m_type == MVI_UNKNOWN) return 0;

//	window->enableClippingPlanes();

	// handle transparency (btw: objects are not yet sorted on depth yet....
	if (window->depthMaskAllowedOff() && (fgColor(3) < 0.99)) {
		glDepthMask(GL_FALSE); // don't write in depth buffer
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	setFgColor();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	glLineWidth((float)gui_state->m_lineWidth);

	if (m_drawMode & OD_SHADE) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	if (m_drawMode & OD_STIPPLE) {
		glEnable(GL_POLYGON_STIPPLE);
		glEnable(GL_LINE_STIPPLE);
	}
	else {
		glDisable(GL_POLYGON_STIPPLE);
		glDisable(GL_LINE_STIPPLE);
	}

	glMatrixMode(GL_MODELVIEW);
	
	switch (m_int.type()) {
	case MVI_SCALAR:
		break;
	case MVI_VECTOR:
		glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
		drawVector(NULL, m_int.m_vector[0], (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : 1.0);
		break;
	case MVI_BIVECTOR:
		scale = (m_drawMode & OD_MAGNITUDE)
			? sqrt(fabs(m_int.m_scalar[0]) / M_PI) 
			: 1.0;

		glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
		drawBivector(NULL, m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2],
			 scale, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
		break;
	case MVI_TRIVECTOR:
		glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);

		scaleSign = (m_int.m_scalar[0] < 0.0) ? -1.0 : 1.0;

		drawTriVector(NULL, (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : scaleSign, 
			m_int.m_vector, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
		break;
	case MVI_ROTOR:

		// a = green(e1 + e2), b = blue(e2 + e3), dynamic{R = a b,} dynamic{c = R b / R,}

		if (m_int.m_scalar[1] > 0.0001) {
			scale = (m_drawMode & OD_MAGNITUDE)
				? sqrt(fabs(m_int.m_scalar[0]) / M_PI) 
				: 1.0;
			
			// draw plane of rotation
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			drawBivector(NULL, m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2],
				 scale, DRAW_BV_CIRCLE, 0 /*(m_drawMode & OD_ORI) ? 0x01 : 0*/, this);

			// draw 'angle of rotation'
			setOlColor();
			e3ga v(GRADE1, m_int.m_vector[1]), R, b(GRADE1, m_int.m_vector[0]);
			b = -b.dual();
			v = v.normal() * 0.8 * scale;
			
			int nbSteps, i;
			const GAIM_FLOAT ainc = 0.05 * M_PI;

		{
				T.begin(GL_LINE_STRIP);
				T.vertex3dv(v[GRADE1]);

				nbSteps = (int)(m_int.m_scalar[1] / ainc) + 1;
				R = (((0.5 * m_int.m_scalar[1]) / nbSteps) * b).exp();
				for (i = 0; i < nbSteps; i++) {
					v = (R * v / R)(GRADE1);
					T.vertex3dv(v[GRADE1]);
				}
				T.end();
			}

			{
				// add arrowhead
				R = (0.01 * b).exp();
				v = (R * v / R)(GRADE1);
		//		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				T.begin(GL_LINE_STRIP);
				T.vertex3dv((0.93 * v + 0.13 * (v << b))[GRADE1]);
				T.vertex3dv(v[GRADE1]);
				T.vertex3dv((1.05 * v + 0.15 * (v << b))[GRADE1]);
				T.end();
			}

		}

		break;
	default:
		if (m_int.type() != MVI_UNKNOWN) {
		//	cprintf("e3gaObject::draw(): can not draw object #%d\n", m_int.type());
		}
		break;
	}

	return 0;
}

float e3gaObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

int e3gaObject::description(char *buf, int bufLen, int sl /* = 0 */) {

	buf[0] = 0;
	switch (m_int.type()) {
	case MVI_SCALAR:
/*
scalar 0: magnitude
*/
		if (sl) sprintf(buf, "%s: e3ga scalar%s, magnitude: %f", m_name.c_str(), (m_int.dual()) ? " dual" : "", m_int.m_scalar[0]);

		else sprintf(buf, "e3ga scalar%s\nMagnitude: %f\nCoordinates: %s", 
			(m_int.dual()) ? " dual" : "",
			m_int.m_scalar[0], 
			m_mv.string());
		break;
	case MVI_VECTOR:
/*
vector 0: vector direction
scalar 0: vector magnitude
*/
		if (sl) sprintf(buf, "%s: e3ga vector%s", m_name.c_str(), (m_int.dual()) ? " dual" :  "");

		else sprintf(buf, "e3ga vector%s\nMagnitude: %f\nDirection: %2.2f %2.2f %2.2f\nCoordinates: %s", 
			(m_int.dual()) ? " dual" : "",
			m_int.m_scalar[0], 
			m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
			m_mv.string());
		break;
	case MVI_BIVECTOR:
/*
vector 0: bivector normal
vector 1: orthogonal to vector 0
vector 2: orthogonal to vector 0 and vector 1
scalar 0: bivector magnitude
*/
		if (sl) sprintf(buf, "%s: e3ga bivector%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

		else sprintf(buf, "e3ga bivector%s\nMagnitude: %f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
			(m_int.dual()) ? " dual" : "",
			m_int.m_scalar[0], 
			m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
			m_mv.string());
		break;
	case MVI_TRIVECTOR:
/*
scalar 0: trivector magnitude
*/
		if (sl) sprintf(buf, "%s: e3ga trivector%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

		else sprintf(buf, "e3ga trivector%s\nMagnitude: %f\nCoordinates: %s", 
			(m_int.dual()) ? " dual" : "",
			m_int.m_scalar[0], 
			m_mv.string());
		break;
	case MVI_ROTOR:
		/*
		scalar 0: magnitude
		scalar 1: angle
		vector 0: normal
		vector 1: orthogonal to vector 0 and 2
		vector 2: orthogonal to vector 0 and 1
		point 0: position
		*/
		if (sl) sprintf(buf, "%s: e3ga rotor%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

		else sprintf(buf, "e3ga rotor%s\nAngle: %f\nMagnitude: %f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
			(m_int.dual()) ? " dual" : "",
			m_int.m_scalar[1], 
			m_int.m_scalar[0], 
			m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
			m_mv.string());
		break;
	default:
		if (sl) sprintf(buf, "%s: unknown e3ga object.", m_name.c_str());

		else sprintf(buf, "Unknown e3ga object.\nCoordinates: %s", m_mv.string());
		break;
	}

	return 0;
}

std::string e3gaObject::toString(const char *floatPrec /* = "%e" */) {
	return std::string("\"" + m_name + "\" = " +  m_mv.string(floatPrec));
}

