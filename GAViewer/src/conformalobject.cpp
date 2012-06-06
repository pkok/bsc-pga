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

// Copyright 2002-2010, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

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
int conformalObject::draw(glwindow *window) {
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
			// draw stippled point at the origin ('infinity')
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);

			glPushMatrix();
			glScaled(gui_state->m_pointSize, gui_state->m_pointSize, gui_state->m_pointSize);
			if (m_drawMode & OD_MAGNITUDE)
				glScaled(fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]));

			gsDraw(g_pointSphere, (m_drawMode & OD_ORI) ? 0.01 * m_int.m_scalar[0] : 0.0);
			glPopMatrix();

			break;
		case MVI_FREE_VECTOR:
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			drawVector(NULL, m_int.m_vector[0], (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : 1.0);
			break;
		case MVI_FREE_BIVECTOR:
			scale = (m_drawMode & OD_MAGNITUDE)
				? sqrt(fabs(m_int.m_scalar[0]) / M_PI)
				: 1.0;

			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			drawBivector(NULL, m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2],
				 scale, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);

			break;
		case MVI_FREE_TRIVECTOR:
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);

			scaleSign = (m_int.m_scalar[0] < 0.0) ? -1.0 : 1.0;
			/*if (m_drawMode & OD_MAGNITUDE) {
				scale = pow((fabs(m_int.m_scalar[0]) * 3.0) / (4 * M_PI), 1.0 / 3.0);
			}
			else scale = scaleSign;*/
		
			drawTriVector(NULL, (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : scaleSign, 
				NULL, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
			break;
		case MVI_POINT:
		case MVI_FLAT_POINT:
			glDisable(GL_LIGHTING);
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			glPushMatrix();
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);
			glScaled(gui_state->m_pointSize, gui_state->m_pointSize, gui_state->m_pointSize);
			if (m_drawMode & OD_MAGNITUDE)
				glScaled(fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]));

			gsDraw(g_pointSphere, (m_drawMode & OD_ORI) ? 0.01 * m_int.m_scalar[0] : 0.0);
			glPopMatrix();
			break;
		case MVI_LINE: // todo: put this code in sep. func. (combined with p3ga line)
			glDisable(GL_LIGHTING);
			glPushMatrix();
			// translate to point on line 
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);

			// rotate e3 to line direction
			e3gaRve3(e3gaR, e3ga(GRADE1, m_int.m_vector[0]));
			e3gaRotorToOpenGLMatrix(e3gaR, rotM);
			glMultMatrixf(rotM);

			// draw line
			T.begin(GL_LINE_STRIP);
			for (z = -scaleConst; z <= scaleConst; z += stepSize * scaleConst)
				T.vertex3d(0.0, 0.0, z);
			T.end();
			/*glBegin(GL_LINE_STRIP);
			for (z = -scaleConst; z <= scaleConst; z += stepSize * scaleConst)
				glVertex3d(0.0, 0.0, z);
			glEnd();*/

			// draw 'orientation'
			if (m_drawMode & OD_ORI) { 
				// todo: flip orientation of this stuff
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
					/*glBegin(GL_LINE_STRIP);
					for (z = -scaleConst; z < scaleConst; z += 1.0 / 32)
						glVertex3d(sin(z) * sin(z * M_PI * 2), sin(z) * cos(z * M_PI * 2), z);
					glEnd();*/
					break;
				case DRAW_LINE_CURLYTAIL:
					// option 2: curly tails
					glTranslated(0.0, 0.0, -scaleConst);
					for (c = 0.0; c <= 1.0; c += stepSize) {
						glPushMatrix();
						// if weight: scale
						if (m_drawMode & OD_MAGNITUDE)
							glScaled(0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]));
						else glScaled(0.5, 0.5, 0.5);

						T.begin(GL_LINE_STRIP);
						for (z = 0.0; z < 1.0; z += 1.0 / 64)
							T.vertex3d(sqrt(z) * sin(z * M_PI * 2), sqrt(z) * cos(z * M_PI * 2), -2.0 * (-0.5 + z) * stepSize * scaleConst);
						T.end();
						/*glBegin(GL_LINE_STRIP);
						for (z = 0.0; z < 1.0; z += 1.0 / 64)
							glVertex3d(sqrt(z) * sin(z * M_PI * 2), sqrt(z) * cos(z * M_PI * 2), -2.0 * (-0.5 + z) * stepSize * scaleConst);
						glEnd();*/

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
						// if weight: scale
						if (m_drawMode & OD_MAGNITUDE)
							glScaled(0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]), 0.5 * fabs(m_int.m_scalar[0]));
						else glScaled(0.5, 0.5, 0.5);

						T.begin(GL_LINE_STRIP);
						T.vertex3d(-0.25, 0.0, -1.0);
						T.vertex3d(0.0, 0.0, 0.0);
						T.vertex3d(0.25, 0.0, -1.0);
						T.end();
						/*glBegin(GL_LINE_STRIP);
						glVertex3d(-0.25, 0.0, -1.0);
						glVertex3d(0.0, 0.0, 0.0);
						glVertex3d(0.25, 0.0, -1.0);
						glEnd();*/

						glPopMatrix();
						glRotated(90, 0.0, 0.0, 1.0);
						glTranslated(0.0, 0.0, 2.0 * stepSize * scaleConst);
					}
					break;
				}
			}

			glPopMatrix();
			break;
		case MVI_PLANE: // todo: put this code in sep. func. (combined with c3ga line)
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
				//printf("Y: %f, X: %f\n", x, y);
				T.end();
			}
			break;

		case MVI_BOUND_TANGENT_VECTOR:
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			drawVector(m_int.m_point[0], m_int.m_vector[0], (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : 1.0);
			break;
		case MVI_BOUND_TANGENT_BIVECTOR:
			scale = (m_drawMode & OD_MAGNITUDE)
				? sqrt(fabs(m_int.m_scalar[0]) / M_PI) 
				: 1.0;

			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			drawBivector(m_int.m_point[0], m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2],
				 scale, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
			break;
		case MVI_BOUND_TANGENT_TRIVECTOR:
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);

			scaleSign = (m_int.m_scalar[0] < 0.0) ? -1.0 : 1.0;
			/*if (m_drawMode & OD_MAGNITUDE) {
				scale = pow((fabs(m_int.m_scalar[0]) * 3.0) / (4 * M_PI), 1.0 / 3.0);
			}
			else scale = scaleSign;*/
		
			drawTriVector(m_int.m_point[0], (m_drawMode & OD_MAGNITUDE) ? m_int.m_scalar[0] : scaleSign, 
				NULL, m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
			break;
		case MVI_POINT_PAIR:
			glDisable(GL_LIGHTING);
			if (m_dmMenuIdx == DRAW_PP_LINE_SEGMENT) {
				T.begin(GL_LINES);
				T.vertex3dv(m_int.m_point[1]);
				T.vertex3dv(m_int.m_point[2]);
				T.end();
				/*				glBegin(GL_LINES);
				glVertex3dv(m_int.m_point[1]);
				glVertex3dv(m_int.m_point[2]);
				glEnd();
				*/
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
				glPushMatrix();
				glTranslated(m_int.m_point[1][0], m_int.m_point[1][1], m_int.m_point[1][2]);
				glScaled(gui_state->m_pointSize, gui_state->m_pointSize, gui_state->m_pointSize);
				if (m_drawMode & OD_MAGNITUDE)
					glScaled(fabs(m_int.m_scalar[1]), fabs(m_int.m_scalar[1]), fabs(m_int.m_scalar[1]));
				gsDraw(g_pointSphere, (m_drawMode & OD_ORI) ? 0.01 * m_int.m_scalar[0] : 0.0);
				glPopMatrix();
				glPushMatrix();
				glTranslated(m_int.m_point[2][0], m_int.m_point[2][1], m_int.m_point[2][2]);
				glScaled(gui_state->m_pointSize, gui_state->m_pointSize, gui_state->m_pointSize);
				if (m_drawMode & OD_MAGNITUDE)
					glScaled(fabs(m_int.m_scalar[1]), fabs(m_int.m_scalar[1]), fabs(m_int.m_scalar[1]));
				gsDraw(g_pointSphere, (m_drawMode & OD_ORI) ? 0.01 * m_int.m_scalar[0] : 0.0);
				glPopMatrix();
			}

			if ( ((m_dmMenuIdx == DRAW_PP_CONNECTED_ON_ORI) && (m_drawMode & OD_ORI)) ||
				(m_dmMenuIdx == DRAW_PP_CONNECTED)) {
				T.begin(GL_LINES);
				T.vertex3dv(m_int.m_point[1]);
				T.vertex3dv(m_int.m_point[2]);
				T.end();
				/*glBegin(GL_LINES);
				glVertex3dv(m_int.m_point[1]);
				glVertex3dv(m_int.m_point[2]);
				glEnd();*/

				if (m_drawMode & OD_ORI) {
					GAIM_FLOAT dir[3];
					GAIM_FLOAT l = sqrt(m_int.m_vector[1][0] * m_int.m_vector[1][0] + 
						m_int.m_vector[1][1] * m_int.m_vector[1][1] + 
						m_int.m_vector[1][2] * m_int.m_vector[1][2]);
					dir[0] = m_int.m_vector[1][0] / l;
					dir[1] = m_int.m_vector[1][1] / l;
					dir[2] = m_int.m_vector[1][2] / l;
					drawVector(m_int.m_point[1], dir, 0.55 * l);
				}
			}
			break;
		case MVI_CIRCLE:
			{
			glDisable(GL_LIGHTING);
			glPushMatrix();
			// translate to center, scalar to radius 
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);
			double scale = m_int.m_scalar[0];
			//glScaled(m_int.m_scalar[0], m_int.m_scalar[0], m_int.m_scalar[0]);

			// rotate e3 to plane normal
			e3gaRve3(e3gaR, e3ga(GRADE1, m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2]));
			e3gaRotorToOpenGLMatrix(e3gaR, rotM);
			glMultMatrixf(rotM);

			// draw circle
			{
				T.begin(GL_LINE_LOOP);
				for (x = 0; x < M_PI * 2; x += (M_PI * 2) / 64)
					T.vertex2d(scale * sin(x), scale * cos(x));
				T.end();
			}

			/*		glBegin(GL_LINE_LOOP);
				for (x = 0; x < M_PI * 2; x += (M_PI * 2) / 64)
					glVertex2d(sin(x), cos(x));
			glEnd();

			*/

			// draw 6 little 'hooks' along the edge of the circle
			if (m_drawMode & OD_ORI) {
				for (x = 0; x < 6; x++) {
					T.begin(GL_LINES);
					T.vertex2d(scale * 1.0, 0.0);
					T.vertex2d(scale * 1.0, scale * -((m_drawMode & OD_MAGNITUDE) ? fabs(m_int.m_scalar[1]) : 1.0) * 0.3);
					T.end();
					/*glBegin(GL_LINES);
					glVertex2d(1.0, 0.0);
					glVertex2d(1.0, -((m_drawMode & OD_MAGNITUDE) ? fabs(m_int.m_scalar[1]) : 1.0) * 0.3);
					glEnd();*/
					glRotated(360 / 6, 0.0, 0.0, 1.0);
				}

				// draw a normal vector (removed)
			/*	glBegin(GL_LINES);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(0.0, 0.0, (m_drawMode & OD_MAGNITUDE) ? fabs(m_int.m_scalar[1]) : 1.0);
				glEnd();*/
			}

			glPopMatrix();
			}
			break;
		case MVI_SPHERE:
			glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			glPushMatrix();
			glTranslated(m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2]);
			glScaled(fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]), fabs(m_int.m_scalar[0]));
			scaleMag *= (m_int.m_scalar[1] < 0.0) ? -1.0 : 1.0;
			if (m_drawMode & OD_MAGNITUDE) scaleMag *= fabs(m_int.m_scalar[1]);
			gsDraw(g_sphereSphere, (m_drawMode & OD_ORI) ? 0.1 * scaleMag : 0.0);
			glPopMatrix();
			break;
		default:
			printf("Can not (yet) drawn the blade object #%d\n", m_int.type());
			break;
		}
	}
	else {
		if (m_int.type() != MVI_UNKNOWN)
			printf("Can not (yet) drawn the object #%d\n", m_int.type());
		return 0;
	}

	return 0;
}

int conformalObject::description(const c3ga &mv, int dim, char *buf, int bufLen, int sl /* = 0 */) {
	buf[0] = 0;

	if (m_int.type() == MVI_UNKNOWN) {
		if (sl) sprintf(buf, "%s: unknown c%dga object", m_name.c_str(), dim);

		else sprintf(buf, "Unknown c%dga object.\nCoordinates: %s", dim, mv.string());
	}
	else if (m_int.blade()) {
		switch (m_int.type()) {
		case MVI_FREE_FLAT:
	/*
	scalar 0: magnitude
	*/
			if (sl) sprintf(buf, "%s: c%dga free scalar%s, weight: %f", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "", m_int.m_scalar[0]);

			else sprintf(buf, "c%dga free scalar%s\nWeight: %f\nCoordinates: %s", 
				dim, 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				mv.string());
			break;

		case MVI_FREE_VECTOR:
	/*
	vector 0: vector direction
	scalar 0: vector magnitude
	*/
			if (sl) sprintf(buf, "%s: c%dga free vector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga free vector%s\nWeight: %f\nDirection: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				mv.string());
			break;
		case MVI_FREE_BIVECTOR:
	/*
	vector 0: bivector normal
	vector 1: orthogonal to vector 0
	vector 2: orthogonal to vector 0 and vector 1
	scalar 0: bivector magnitude
	*/
			if (sl) sprintf(buf, "%s: c%dga free bivector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga free bivector%s\nWeight: %f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				mv.string());
			break;
		case MVI_FREE_TRIVECTOR:
	/*
	scalar 0: trivector magnitude
	*/
			if (sl) sprintf(buf, "%s: c%dga free trivector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga free trivector%s\nWeight: %f\nCoordinates: %s", 
				dim, 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				mv.string());
			break;
		case MVI_FLAT_POINT:
	/*
	scalar 0: magnitude
	point 0: point
	*/
			if (sl) sprintf(buf, "%s: c%dga flat point%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga flat point%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());
			break;
		case MVI_LINE:
	/*
	scalar 0: magnitude
	point 0: point
	vector 0: direction
	*/
			if (sl) sprintf(buf, "%s: c%dga line%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga line%s\nWeight: %f\nDirection: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());

			break;
		case MVI_PLANE:
	/*
	scalar 0: magnitude
	vector 0: normal 
	vector 1: orthogonal to vector 0
	vector 2: orthogonal to vector 0 and vector 1
	point 0: point on plane closest to chosen origin
	*/
			if (sl) sprintf(buf, "%s: c%dga plane%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga plane%s\nWeight: %f\nNormal: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());
			break;

		case MVI_POINT:
	/*
	scalar 0: magnitude
	point 0: point
	*/
			if (sl) sprintf(buf, "%s: c%dga point%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga point%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());
			break;
		case MVI_BOUND_TANGENT_VECTOR:
	/*
	scalar 0: magnitude
	point 0: point
	vector 0: direction
	*/
			if (sl) sprintf(buf, "%s: c%dga tangent vector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga tangent vector%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nDirection: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				mv.string());
			break;
		case MVI_BOUND_TANGENT_BIVECTOR:
	/*
	scalar 0: magnitude
	point 0: point
	vector 0: normal 
	vector 1: orthogonal to vector 0
	vector 2: orthogonal to vector 0 and vector 1		
	*/
			if (sl) sprintf(buf, "%s: c%dga tangent bivector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga tangent bivector%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				mv.string());
			break;
		case MVI_BOUND_TANGENT_TRIVECTOR:
	/*
	scalar 0: magnitude
	point 0: point
	*/
			if (sl) sprintf(buf, "%s: c%dga tangent trivector%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga tangent trivector%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], 
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());
			break;
		case MVI_POINT_PAIR:
	/*
	scalar 0: signed radius
	scalar 1: magnitude
	point 0: center point
	point 1: point 1
	point 2: point 2
	*/
			if (sl) sprintf(buf, "%s: c%dga point pair%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga point pair%s\nRadius: %2.2f\nWeight: %2.2f\nPoint 1: %2.2f %2.2f %2.2f\nPoint 2: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], m_int.m_scalar[1], 
				m_int.m_point[1][0], m_int.m_point[1][1], m_int.m_point[1][2], 
				m_int.m_point[2][0], m_int.m_point[2][1], m_int.m_point[2][2], 
				mv.string());
			break;
		case MVI_CIRCLE:
	/*
	scalar 0: signed radius
	scalar 1: magnitude
	point 0: center point
	vector 0: normal 
	vector 1: orthogonal to vector 0
	vector 2: orthogonal to vector 0 and vector 1		
	*/
			if (sl) sprintf(buf, "%s: c%dga circle%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga circle%s\nSigned radius: %2.2f\nWeight: %2.2f\nCenter point: %2.2f %2.2f %2.2f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], m_int.m_scalar[1],
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
				mv.string());
			break;
		case MVI_SPHERE:
	/*
	scalar 0: signed radius
	scalar 1: magnitude
	point 0: center point
	*/
			if (sl) sprintf(buf, "%s: c%dga sphere%s", m_name.c_str(), dim, (m_int.dual()) ? " dual" : "");

			else sprintf(buf, "c%dga sphere%s\nSigned radius: %2.2f\nWeight: %f\nCenter point: %2.2f %2.2f %2.2f\nCoordinates: %s", 
				dim, (m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0], m_int.m_scalar[1],
				m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
				mv.string());
			break;

		default:
			if (sl) sprintf(buf, "%s: unknown c%dga blade", m_name.c_str(), dim);

			else sprintf(buf, "Unknown c%dga blade.\nCoordinates: %s", dim, mv.string());
			break;
		}
	}
	else if (m_int.versor()) {
		if (sl) sprintf(buf, "%s: c%dga versor", m_name.c_str(), dim);

		else sprintf(buf, "c%dga versor\nTakes the origin to: %2.2f %2.2f %2.2f\nCoordinates: %s", 
			dim, m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
			mv.string());
	}
	else {
		if (sl) sprintf(buf, "%s: unknown c%dga object", m_name.c_str(), dim);

		else sprintf(buf, "Unknown c%dga object.\nCoordinates: %s", dim, mv.string());
	}



	return 0;
}
