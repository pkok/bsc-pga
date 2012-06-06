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


#include "glwindow.h"
#include "util.h"
#include "osdep.h"
#include "object.h"
#include "draw.h"
#include "geosphere.h"
#include "uistate.h"

int drawVector(const GAIM_FLOAT tail[3], const GAIM_FLOAT dir[3], GAIM_FLOAT scale) {
	TubeDraw &T = gui_state->m_tubeDraw;

	GLboolean l;
	const GAIM_FLOAT rotStep = 2 * M_PI / 32;
	GAIM_FLOAT z;
	e3ga rt, n, rti;
	float rotM[16];

	if (scale == 0.0) return 0;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if (tail)
		glTranslated(tail[0], tail[1], tail[2]);
	glScaled(scale, scale, scale);

	// draw the stick of the vector
	glGetBooleanv(GL_LIGHTING, &l);
	glDisable(GL_LIGHTING);
	T.begin(GL_LINES);
	T.vertex3d(0.0, 0.0, 0.0);
	T.vertex3d(0.96 * dir[0], 0.96 * dir[1], 0.96 * dir[2]);
	T.end();
/*	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.96 * dir[0], 0.96 * dir[1], 0.96 * dir[2]);
	glEnd();*/
	if (l) glEnable(GL_LIGHTING);

	glPushMatrix();

	// translate to head of vector
	glTranslated(dir[0], dir[1], dir[2]);

	if (gui_state->m_vectorHeadSize >= 0.0) { // temp test for fixed vector head size
		glScaled(1.0 / scale, 1.0 / scale, 1.0 / scale);
		glScaled(gui_state->m_vectorHeadSize, gui_state->m_vectorHeadSize, gui_state->m_vectorHeadSize);
	}
	else {
		glScaled(-gui_state->m_vectorHeadSize, -gui_state->m_vectorHeadSize, -gui_state->m_vectorHeadSize);
		if (scale > 1.0) {
			glScaled(1.0 / scale, 1.0 / scale, 1.0 / scale);
			double s = pow(scale, 0.75);
			glScaled(s, s, s);
		}
	}


	// rotate e3 to vector direction
	e3gaRve3(rt, e3ga(GRADE1, dir[0], dir[1], dir[2]));
	e3gaRotorToOpenGLMatrix(rt, rotM);
	glMultMatrixf(rotM);

//	glDisable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
/*
	// ---If normals are not required:	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3d(0.0, 0.0, 0.0);			
	for (z = 0; z <= 2 * M_PI + 0.01; z += 2 * M_PI / 16) {
		// no normals?
		glVertex3d(0.1 * cos(z), 0.1 * sin(z), -0.25);
	}
	glEnd();*/

	// ---Otherwise:
	rt = (-0.5 * rotStep * e3ga::e1 ^ e3ga::e2).exp();
	rti = rt.inverse(); n = e3ga::e1;
	glBegin(GL_QUADS);
	for (z = 0; z < 2 * M_PI; z += rotStep) {
		glNormal3dv(n[GRADE1]);
		glVertex3d(0.1 * cos(z), 0.1 * sin(z), -0.25);
		glVertex3d(0.0, 0.0, 0.00);
		n = (rt * n * rti)(GRADE1);
		glNormal3dv(n[GRADE1]);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.1 * cos(z + rotStep), 0.1 * sin(z + rotStep), -0.25);
	}
	glEnd();

	n = e3ga::e1;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3dv((-(e3ga&)e3ga::e3)[GRADE1]);
	glVertex3d(0.0f, 0.0f, -0.25);
	for (z = 0; z <= 2 * M_PI + 1e-3; z += rotStep) {
		glVertex3d(0.1 * cos(z), 0.1 * sin(z), -0.25);
	}
	glEnd();

	glDisable(GL_CULL_FACE);

	glPopMatrix();


	// draw the stick of the vector
/*	glGetBooleanv(GL_LIGHTING, &l);
	glDisable(GL_LIGHTING);
//	glBegin(GL_LINES);
	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(0.98 * dir[0], 0.98 * dir[1], 0.98 * dir[2]);
	glEnd();
	if (l) glEnable(GL_LIGHTING);*/

	glPopMatrix();

	return 0;
}


int drawBivector(const GAIM_FLOAT base[3], const GAIM_FLOAT normal[3], const GAIM_FLOAT ortho1[3], 
				 const GAIM_FLOAT ortho2[3], GAIM_FLOAT scale, int method /*= DRAW_BV_CIRCLE*/, 
				 int flags /* = 0 */, object *o /*= NULL*/) {
	TubeDraw &T = gui_state->m_tubeDraw;
	const GAIM_FLOAT rotStep = 2 * M_PI / 64;
	GAIM_FLOAT x, y;
	e3ga rt;
	float rotM[16];

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if (base) glTranslated(base[0], base[1], base[2]);

//	printf("method = %d %d\n", method, DRAW_BV_PARALLELOGRAM);
//	printf("scale = %f,\n", scale);
	// scale bivector

	if ((method != DRAW_BV_PARALLELOGRAM) &&
		(method != DRAW_BV_PARALLELOGRAM_NO_VECTORS)) {
		glScaled(scale, scale, scale);

		// rotate e3 to normal direction
		e3gaRve3(rt, e3ga(GRADE1, normal[0], normal[1], normal[2])); 
		e3gaRotorToOpenGLMatrix(rt, rotM);
		glMultMatrixf(rotM);
	}
	else {
		e3ga o1(GRADE1, ortho1);
		e3ga o2(GRADE1, ortho2);
		// scale is based on _circle_, re-scale for square:
		double size = scale * scale * M_PI / sqrt((o1 ^ o2).norm_a());
		double _scale = sqrt(size);
//		printf("Would scale by %f (scale = %f)\n", _scale, scale);
//		printf("o1: %f %f %f\n", ortho1[0], ortho1[1], ortho1[2]);
//		printf("o2: %f %f %f\n", ortho2[0], ortho2[1], ortho2[2]);
		glScaled(_scale, _scale, _scale);
	}

	switch(method) {
	case DRAW_BV_CIRCLE:
		if (o->fgColor(3) > 0.0)  {
			// draw the filled-in circle (back)
			glNormal3d(0.0, 0.0, 1.0);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0.0, 0.0, 0.0);
			for (x = 0; x < M_PI * 2.0 + 0.001; x += rotStep)
				glVertex2d(cos(x), sin(x));
			glEnd();

			// draw the filled-in circle (front)
			glNormal3d(0.0, 0.0, -1.0);
			if (flags & 0x01) glPolygonMode(GL_FRONT,  GL_LINE);
			glBegin(GL_TRIANGLE_FAN);
			glVertex3d(0.0, 0.0, 0.0);
			for (x = 0; x < M_PI * 2.0 + 0.001; x += rotStep)
				glVertex2d(-cos(x), sin(x));
			glEnd();
			if (flags & 0x01) glPolygonMode(GL_FRONT,  GL_FILL);
		}

		// draw the outline
		glDisable(GL_LIGHTING);
		if (o) o->setOlColor();
		T.begin(GL_LINE_LOOP);
		for (x = 0; x < M_PI * 2.0; x += rotStep)
			T.vertex2d(cos(x), sin(x));
		T.end();
		/*	glBegin(GL_LINE_LOOP);
		for (x = 0; x < M_PI * 2.0; x += rotStep)
			glVertex2d(cos(x), sin(x));
		glEnd();*/

		if (flags & 0x01) {
			// draw 6 little 'hooks' along the edge of the circle
			for (x = 0; x < 6; x++) {
				T.begin(GL_LINES);
				T.vertex2d(1.0, 0.0);
				T.vertex2d(1.0, -0.5);
				T.end();
				/*glBegin(GL_LINES);
				glVertex2d(1.0, 0.0);
				glVertex2d(1.0, -0.3);
				glEnd();*/
				glRotated(360 / 6, 0.0, 0.0, 1.0);
			}

			// draw a normal vector
/*			glBegin(GL_LINES);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3d(0.0, 0.0, 1.0);
			glEnd();*/
		}

		break;
	case DRAW_BV_PARALLELOGRAM:
	case DRAW_BV_PARALLELOGRAM_NO_VECTORS:
		// front
		glNormal3dv(normal);
		glBegin(GL_QUADS);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3dv(ortho1);
		glVertex3d(ortho1[0] + ortho2[0], ortho1[1] + ortho2[1], ortho1[2] + ortho2[2]);
		glVertex3dv(ortho2);
		glEnd();

		// back
		/*if ((method != DRAW_BV_PARALLELOGRAM) && 
			(flags & 0x01)) glPolygonMode(GL_FRONT,  GL_LINE);*/
		if (flags & 0x01) glPolygonMode(GL_FRONT,  GL_LINE);
		glNormal3d(-normal[0], -normal[1], -normal[2]);
		glBegin(GL_QUADS);
		glVertex3dv(ortho2);
		glVertex3d(ortho1[0] + ortho2[0], ortho1[1] + ortho2[1], ortho1[2] + ortho2[2]);
		glVertex3dv(ortho1);
		glVertex3d(0.0, 0.0, 0.0);
		glEnd();
		if (flags & 0x01) glPolygonMode(GL_FRONT,  GL_FILL);

		// vectors
		if (method != DRAW_BV_PARALLELOGRAM_NO_VECTORS) {
			glPolygonMode(GL_FRONT_AND_BACK, (o->m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
			if (o) o->setBgColor();
			drawVector(NULL, ortho1, 1.0);
			if (o->m_drawMode & OD_SHADE) glEnable(GL_LIGHTING); // has been turned off by drawVector()
			drawVector(ortho1, ortho2, 1.0);

			// outline 
			/*
			glDisable(GL_LIGHTING);
			if (o) o->setOlColor();
			//glBegin(GL_LINE_LOOP);
			glVertex3d(0.0, 0.0, 0.0);
			glVertex3dv(ortho1);
			glVertex3d(ortho1[0] + ortho2[0], ortho1[1] + ortho2[1], ortho1[2] + ortho2[2]);
			glVertex3dv(ortho2);
			glEnd();*/

			// draw a normal vector
			if (flags & 0x01) {
				T.begin(GL_LINES);
				T.vertex3d(0.0, 0.0, 0.0);
				T.vertex3dv(normal);
				T.end();
/*				glBegin(GL_LINES);
				glVertex3d(0.0, 0.0, 0.0);
				glVertex3dv(normal);
				glEnd();*/
			}
		}

		break;
	case DRAW_BV_CROSS:
	case DRAW_BV_CURLYTAIL:
		glDisable(GL_LIGHTING);
		T.begin(GL_LINE_STRIP);
		for (y = 0; y <= M_PI *2 + 0.001; y += M_PI * 2 / 64)
			T.vertex2d(-sqrt(y / (2 * M_PI)) * sin(y), sqrt(y / (2 * M_PI)) * cos(y));
		T.end();
		break;
	case DRAW_BV_SWIRL:
		glDisable(GL_LIGHTING);
		for (x = 0; x < 4; x++) {
			T.begin(GL_LINE_STRIP);
			for (y = 0; y <= M_PI / 2 + 0.001; y += M_PI / (2 * 16)) {
				T.vertex2d((1.0 - sin(y)), cos(y));
			}
			T.end();
			glRotated(90, 0.0, 0.0, 1.0);
		}
		break;
	default:
		glPopMatrix();
		return -1;
	}

	glPopMatrix();

	return 0;
}

int drawTriVector(const GAIM_FLOAT base[3], GAIM_FLOAT scale, GAIM_FLOAT vector[][3], int method /*= DRAW_TV_SPHERE*/, int flags /*= 0*/, object *o /*= NULL*/) {
	TubeDraw &T = gui_state->m_tubeDraw;

	GAIM_FLOAT scaleSign = (scale < 0.0) ? -1.0 : 1.0;
	if ((method == DRAW_TV_PARALLELEPIPED) ||
		(method == DRAW_TV_PARALLELEPIPED_NO_VECTORS)) {
		if (vector == NULL) drawTriVector(base, scale, NULL, DRAW_TV_SPHERE, flags, o);

		// adjust scale for cube
		scale = scaleSign * pow(scaleSign * scale, 1.0 / 3.0);
	}
	else {
		// adjust scale for sphere
		scale = scaleSign * pow(scaleSign * scale / ((4.0/3.0) * M_PI), 1.0 / 3.0);
	}

//	printf("Draw scale: %f\n", scale);

	int i, j, vtxIdx;
	GAIM_FLOAT z, s = (scale < 0.0) ? -1.0 : 1.0, f;
	const GAIM_FLOAT zMax = 4 * M_PI;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if (base) glTranslated(base[0], base[1], base[2]);
	glScaled(fabs(scale), fabs(scale), fabs(scale));

	switch(method) {
	case DRAW_TV_SPHERE:
		gsDraw(g_sphereSphere, ((flags & 0x01) ? s * 0.1 : 0.0));
		break;
	case DRAW_TV_CROSS:
	case DRAW_TV_CURLYTAIL:
		// mag & ori nog niet helemaal goed....
		if (flags & 0x01) glScaled(s, fabs(s), fabs(s));
		glDisable(GL_LIGHTING);
		T.begin(GL_LINE_STRIP);
		for (z = -zMax; z <= zMax; z += 0.1) {
			f = z / zMax;
			f = sqrt(1 - f * f);
			T.vertex3d(/*s * */1.0 * f * cos(z), 1.0 * f * sin(z), 1.0 * z / zMax);
		}
		T.end();
		break;

	case DRAW_TV_PARALLELEPIPED:
	case DRAW_TV_PARALLELEPIPED_NO_VECTORS:
		if (flags & 0x01) glScaled(s, fabs(s), fabs(s));

		// maybe define vertices of the 'cube'
		{
			GAIM_FLOAT vertex[8][3];
			int vertexVectors[8][3] = 
			{{-1, -1, -1}, // -
			{0, -1, -1},  // 0
			{0, 1, -1}, // 0 + 1
			{1, -1, -1}, // 1
			{2, -1, -1}, // 2
			{0, 2, -1},  // 0 + 2
			{0, 1, 2}, // 0 + 1 + 2
			{1, 2, -1}}; // 1 + 2
			
			int polygon[6][4] = 
			{{0, 1, 5, 4},
			{0, 4, 7, 3},
			{4, 5, 6, 7},
			{1, 2, 6, 5},
			{6, 2, 3, 7},
			{0, 3, 2, 1}};

			for (i = 0; i < 8; i++) {
				vertex[i][0] = vertex[i][1] = vertex[i][2] = 0.0;
				for (j = 0; j < 3; j++) {
					if ( (vtxIdx = vertexVectors[i][j]) < 0) continue;
					vertex[i][0] += vector[vtxIdx][0];
					vertex[i][1] += vector[vtxIdx][1];
					vertex[i][2] += vector[vtxIdx][2];
				}
			}

			glBegin(GL_QUADS);
			for (i = 0; i < 6; i++) {
				e3ga v1(GRADE1, vertex[polygon[i][0]]);
				e3ga v2(GRADE1, vertex[polygon[i][1]]);
				e3ga v3(GRADE1, vertex[polygon[i][3]]);
				e3ga normal(scaleSign * ((v2 - v1) ^ (v3 - v1)).dual());
				glNormal3dv(normal[GRADE1]);
				if (scale >= 0.0)
					for (j = 0; j < 4; j++) glVertex3dv(vertex[polygon[i][j]]);
				else for (j = 3; j >= 0; j--) glVertex3dv(vertex[polygon[i][j]]);
				
			}
			glEnd();

			if (method == DRAW_TV_PARALLELEPIPED) {
				// draw the vectors
				if (o) o->setBgColor();
				drawVector(vertex[0], vector[0], 1.0);
				if (o->m_drawMode & OD_SHADE) glEnable(GL_LIGHTING); // has been turned off by drawVector()
				drawVector(vertex[1], vector[1], 1.0);
				if (o->m_drawMode & OD_SHADE) glEnable(GL_LIGHTING); // has been turned off by drawVector()
				drawVector(vertex[2], vector[2], 1.0);
				if (o->m_drawMode & OD_SHADE) glEnable(GL_LIGHTING); // has been turned off by drawVector()
			}
		}

		break;
	default:
		glPopMatrix();
		return -1;
	}

	glPopMatrix();

	return 0;
}
