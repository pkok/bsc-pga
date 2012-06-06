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

#include <string.h>

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

Fl_Menu_Item gui_p3gaLineDrawMethods[] = {
	{"Curve", 0, NULL, (void*)DRAW_LINE_CURVE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_LINE_CURLYTAIL, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKS, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKCROSSES, 0},
	{0}
};


Fl_Menu_Item gui_p3gaBivectorDrawMethods[] = {
	{"Circle", 0, NULL, (void*)DRAW_BV_CIRCLE, 0},
	{"Parallelogram", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM, 0},
	{"Parallelogram w.o. vectors", 0, NULL, (void*)DRAW_BV_PARALLELOGRAM_NO_VECTORS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_BV_CURLYTAIL, 0},
	{"Swirl", 0, NULL, (void*)DRAW_BV_SWIRL, 0},
	{0}
};

Fl_Menu_Item gui_p3gaTrivectorDrawMethods[] = {
	{"Sphere", 0, NULL, (void*)DRAW_TV_SPHERE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CROSS, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_TV_CURLYTAIL, 0},
	{0}
};



p3gaObject::p3gaObject(const p3ga &mv, const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) : object(OT_P3GA, name, drawMode, creationFlags) {
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
				m_dmMenu = gui_p3gaLineDrawMethods;
				m_dmMenuIdx = DRAW_LINE_HOOKS;
			}
			else if (m_int.type() == MVI_BIVECTOR) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_p3gaBivectorDrawMethods;
				m_dmMenuIdx = DRAW_BV_CIRCLE;
			}
			else if (m_int.type() == MVI_TRIVECTOR) {
				m_properties |= OP_DRAWMETHOD;
				m_dmMenu = gui_p3gaTrivectorDrawMethods;
				m_dmMenuIdx = DRAW_TV_SPHERE;
			}
		}
	}

	// override draw method with user setting
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;
}

p3gaObject::~p3gaObject() {
	initToNothing();
}

void p3gaObject::initToNothing() {
	m_mv = 0;
}

int p3gaObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const p3gaObject *p3gaO = (const p3gaObject *)o;

	if ((m_mv - p3gaO->m_mv).norm_a() != 0.0)
		propertiesChanged |= OP_DESCRIPTION;
	m_mv = p3gaO->m_mv;
	m_int.copy(&p3gaO->m_int);

	return 0;
}

int p3gaObject::pick(glwindow *window) {
	return draw(window);
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
int p3gaObject::draw(glwindow *window) {
	TubeDraw &T = gui_state->m_tubeDraw;
	GAIM_FLOAT x, y, z, c, scale, scaleSign;
	int s;
	e3ga e3gaR;
	float rotM[16];

	if (m_type == MVI_UNKNOWN) return 0;

//	window->enableClippingPlanes();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	glLineWidth((float)gui_state->m_lineWidth);

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
	GAIM_FLOAT stepSize = 0.1;
	GAIM_FLOAT scaleConst = g_state->m_clipDistance * sqrt(2.0);
	GAIM_FLOAT scaleMag = 1.0;
	if (m_int.blade()) {
/*		if (m_int.type() == MVI_FREE_BIVECTOR)
			printf("Draw type %d\n", m_int.type());*/
		switch (m_int.type()) {
		case MVI_ZERO:
			// don't draw anything
			break;
		case MVI_SCALAR:
			// don't draw anything
			break;
		case MVI_FREE_SCALAR:
			// don't draw anything
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
			/*if (m_drawMode & OD_MAGNITUDE) {
				scale = scaleSign * pow((fabs(m_int.m_scalar[0]) * 3.0) / (4 * M_PI), 1.0 / 3.0);
			}
			else scale = scaleSign;*/

			drawTriVector(NULL, (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : scaleSign, 
				NULL, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
			break;
		case MVI_POINT:
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			glPushMatrix();
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);
			glScaled(0.1, 0.1, 0.1);
			if (m_drawMode & OD_MAGNITUDE)
				glScaled(fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]));

			gsDraw(g_pointSphere, (m_drawMode & OD_ORI) ? 0.01 * m_int.m_scalar[0] : 0.0);
			glPopMatrix();
			break;
		case MVI_LINE: // todo: put this code in sep. func. (combined with c3ga line)
			glDisable(GL_LIGHTING);
			glPushMatrix();
			// translate to point on line 
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);

			// rotate e3 to line direction
			e3gaRve3(e3gaR, e3ga(GRADE1, m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2]));
			e3gaRotorToOpenGLMatrix(e3gaR, rotM);
			glMultMatrixf(rotM);

			// draw line
			T.begin(GL_LINE_STRIP);
			for (z = -scaleConst; z <= scaleConst; z += stepSize * scaleConst)
				T.vertex3d(0.0, 0.0, z);
			T.end();

			// draw 'orientation'
			if (m_drawMode & OD_ORI) { 

				switch (m_dmMenuIdx) {
				case DRAW_LINE_CURVE:
					// option 1: some kind of curve along the line
					if (m_drawMode & OD_MAGNITUDE)
						glScaled(0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]));
					else glScaled(0.5, 0.5, 0.5);

					T.begin(GL_LINE_STRIP);
					for (z = -scaleConst; z < scaleConst; z += 1.0 / 32)
						T.vertex3d(sin(z) * sin(z * M_PI * 2), sin(z) * cos(z * M_PI * 2), z);
					T.end();
					break;
				case DRAW_LINE_CURLYTAIL:
					// option 2: curly tails
					glTranslated(0.0, 0.0, -scaleConst);
					for (c = 0.0; c <= 1.0; c += stepSize) {
						glPushMatrix();
						// if magnitude: scale
						if (m_drawMode & OD_MAGNITUDE)
							glScaled(0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]));
						else glScaled(0.5, 0.5, 0.5);

						T.begin(GL_LINE_STRIP);
						for (z = 0.0; z < 1.0; z += 1.0 / 64)
							T.vertex3d(sqrt(z) * sin(z * M_PI * 2), sqrt(z) * cos(z * M_PI * 2), -2.0 * (-0.5 + z) * stepSize * scaleConst);
						T.end();

						glPopMatrix();
						glTranslated(0.0, 0.0, 2.0 * stepSize * scaleConst);
					}
					break;
				case DRAW_LINE_HOOKS:
				case DRAW_LINE_HOOKCROSSES:
					// option 3: little hooks 
					glTranslated(0.0, 0.0, -scaleConst);
					for (c = 0.0; c < 1.0; c += stepSize) {
						glPushMatrix();
						// if magnitude: scale
						if (m_drawMode & OD_MAGNITUDE)
							glScaled(0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]));
						else glScaled(0.5, 0.5, 0.5);

						T.begin(GL_LINE_STRIP);
						T.vertex3d(-0.25, 0.0, -1.0);
						T.vertex3d(0.0, 0.0, 0.0);
						T.vertex3d(0.25, 0.0, -1.0);
						T.end();

						glPopMatrix();
						glRotated(90, 0.0, 0.0, 1.0);
						glTranslated(0.0, 0.0, 2.0 * stepSize * scaleConst);
					}
					break;
				}
			}

			glPopMatrix();
			break;
		case MVI_PLANE: // todo: put this code in sep. func. (combined with c3ga plane)
			for (s = 0; s < 2; s++) { // draw both front and back side individually
				if (s == 0) { // front
					glPolygonMode(GL_FRONT, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
					glNormal3dv(m_int.m_vector[0]); 
				}
				else { // back
					glPolygonMode(GL_FRONT, ((m_drawMode & OD_WIREFRAME) || (m_drawMode & OD_ORI)) ? GL_LINE : GL_FILL);
					glNormal3d(-m_int.m_vector[0][0], -m_int.m_vector[0][1], -m_int.m_vector[0][2]); 
				}
				for (y = -scaleConst; y < scaleConst - stepSize * scaleConst; y += stepSize * scaleConst) {
					glBegin(GL_QUAD_STRIP);
					for (x = -scaleConst; x < scaleConst; x += stepSize * scaleConst) {
						glVertex3d(
							m_int.m_point[0][0] + x * m_int.m_vector[1][0] + ((s == 0) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][0],
							m_int.m_point[0][1] + x * m_int.m_vector[1][1] + ((s == 0) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][1],
							m_int.m_point[0][2] + x * m_int.m_vector[1][2] + ((s == 0) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][2]);
						glVertex3d(
							m_int.m_point[0][0] + x * m_int.m_vector[1][0] + ((s == 1) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][0],
							m_int.m_point[0][1] + x * m_int.m_vector[1][1] + ((s == 1) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][1],
							m_int.m_point[0][2] + x * m_int.m_vector[1][2] + ((s == 1) ? (y + stepSize * scaleConst) : y) * m_int.m_vector[2][2]);
					}
					glEnd();
				}
			}

			if (m_drawMode & OD_ORI) { // draw normals
				if (m_drawMode & OD_MAGNITUDE) scaleMag *= m_int.m_scalar[0];
				glDisable(GL_LIGHTING);
				T.begin(GL_LINES);
				for (y = -scaleConst; y <= scaleConst; y += stepSize * scaleConst) {
					for (x = -scaleConst; x <= scaleConst; x += stepSize * scaleConst) {
						T.vertex3d(
							m_int.m_point[0][0] + x * m_int.m_vector[1][0] + y * m_int.m_vector[2][0],
							m_int.m_point[0][1] + x * m_int.m_vector[1][1] + y * m_int.m_vector[2][1],
							m_int.m_point[0][2] + x * m_int.m_vector[1][2] + y * m_int.m_vector[2][2]);
						T.vertex3d(
							m_int.m_point[0][0] + x * m_int.m_vector[1][0] + y * m_int.m_vector[2][0] + scaleMag *  m_int.m_vector[0][0],
							m_int.m_point[0][1] + x * m_int.m_vector[1][1] + y * m_int.m_vector[2][1] + scaleMag *  m_int.m_vector[0][1],
							m_int.m_point[0][2] + x * m_int.m_vector[1][2] + y * m_int.m_vector[2][2] + scaleMag *  m_int.m_vector[0][2]);
					}
				}
				T.end();
			}
			break;
		default:
			cprintf("Can not (yet) draw the blade object #%d\n", m_int.type());
			break;
		}
	}
	else {
		if (m_int.type() != MVI_UNKNOWN)
			cprintf("Can not (yet) draw the object #%d\n", m_int.type());
		return 0;
	}

	return 0;
}


int p3gaObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	e3ga v;
	GAIM_FLOAT m, mnew;
	window->vectorAtDepth(depth, motionX, -motionY, v);
	p3ga t(GRADE1, v[GRADE1][E3GA_E1], v[GRADE1][E3GA_E2], v[GRADE1][E3GA_E3], 0);

	int modified = 0;
	switch (m_int.type()) {
	case MVI_VECTOR:
		m_mv -= t;
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
	case MVI_POINT:
	case MVI_LINE: 
	case MVI_PLANE: 
		m_mv = m_mv - (t ^ (p3ga::e0 << m_mv));
		modified = 1;
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



int p3gaObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	buf[0] = 0;

	if (m_int.type() == MVI_UNKNOWN) {
		if (sl) sprintf(buf, "%s: unknown p3ga object.", m_name.c_str());

		else sprintf(buf, "Unknown p3ga object.\nCoordinates: %s", m_mv.string());
	}
	else if (m_int.blade()) {
		switch (m_int.type()) {
		case MVI_SCALAR:
	/*
	scalar 0: magnitude
	*/
			if (sl) sprintf(buf, "%s: p3ga scalar%s, magnitude: %f", m_name.c_str(), (m_int.dual()) ? " dual" : "", m_int.m_scalar[0]);

			else sprintf(buf, "p3ga scalar%s\nMagnitude: %f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_mv.string());
			break;

		case MVI_VECTOR:
	/*
	vector 0: vector direction
	scalar 0: vector magnitude
	*/
			if (sl) sprintf(buf, "%s: p3ga vector%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga vector%s\nMagnitude: %f\nDirection: %2.2f %2.2f %2.2f\nCoordinates: %s", 
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
			if (sl) sprintf(buf, "%s: p3ga bivector%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga bivector%s\nMagnitude: %f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				m_mv.string());
			break;
		case MVI_TRIVECTOR:
	/*
	scalar 0: trivector magnitude
	*/
			if (sl) sprintf(buf, "%s: p3ga trivector%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga trivector%s\nMagnitude: %f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_mv.string());
			break;
		case MVI_LINE:
	/*
	scalar 0: magnitude
	point 0: point
	vector 0: direction
	*/
			if (sl) sprintf(buf, "%s: p3ga line%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga line%s\nMagnitude: %f\nDirection: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_mv.string());

			break;
		case MVI_PLANE:
	/*
	scalar 0: magnitude
	vector 0: normal 
	vector 1: orthogonal to vector 0
	vector 2: orthogonal to vector 0 and vector 1
	point 0: point on plane closest to chosen origin
	*/
			if (sl) sprintf(buf, "%s: p3ga plane%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga plane%s\nMagnitude: %f\nNormal: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_mv.string());
			break;
		case MVI_POINT:
	/*
	scalar 0: magnitude
	point 0: point
	*/
			if (sl) sprintf(buf, "%s: p3ga point%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "p3ga point%s\nMagnitude: %f\nPoint: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_mv.string());
			break;
		default:
			if (sl) sprintf(buf, "%s: unknown p3ga blade.", m_name.c_str());

			else sprintf(buf, "Unknown p3ga blade.\nCoordinates: %s", m_mv.string());
			break;
		}
	}
	else if (m_int.versor()) {
		if (sl) sprintf(buf, "%s: p3ga versor", m_name.c_str());


		else sprintf(buf, "p3ga versor\nCoordinates: %s", m_mv.string());
	}
	else {
		if (sl) sprintf(buf, "%s: unknown p3ga object.", m_name.c_str());

		else sprintf(buf, "Unknown p3ga object.\nCoordinates: %s", m_mv.string());
	}

	return 0;
}

float p3gaObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

std::string p3gaObject::toString(const char *floatPrec /* = "%e" */) {
	return std::string("\"" + m_name + "\" = " +  m_mv.string(floatPrec));
}
