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
#include "uistate.h"

/*
#define DRAW_PG_FILLED 0
#define DRAW_PG_LINE_STRIP 1
#define DRAW_PG_LINE_LOOP 2

#define DRAW_SP_DEFAULT 0
#define DRAW_SP_VECTOR 1

Fl_Menu_Item gui_polygonMethods[] = {
	{"Filled", 0, NULL, (void*)DRAW_PG_FILLED, 0},
	{"Line strip", 0, NULL, (void*)DRAW_PG_LINE_STRIP, 0},
	{"Line loop", 0, NULL, (void*)DRAW_PG_LINE_LOOP, 0},
	{0}
};

Fl_Menu_Item gui_simplexMethods[] = {
	{"Default", 0, NULL, (void*)DRAW_SP_DEFAULT, 0},
	{"Vector", 0, NULL, (void*)DRAW_SP_VECTOR, 0},
	{0}
};
*/

meshObject::meshObject(const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/) : object(OT_MESH, name, drawMode, creationFlags) {
	initToNothing();

	m_properties = OP_HIDE | OP_FGCOLOR | OP_NAME | OP_DESCRIPTION | OP_DRAWMODE;// | OP_DRAWMETHOD;

	m_drawMode |= OD_SHADE;


/*	m_dmMenuIdx = 0;
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;
*/
	m_mode = creationFlags;

//	createParaboloid();

	// force any f the three 'shading' modes
	if (!(m_mode & (OC_COMPUTE_NORMALS_FLAT | OC_COMPUTE_NORMALS_GOURAUD | OC_SPECIFY_NORMALS))) {
		m_mode |= OC_COMPUTE_NORMALS_FLAT;
	}
}

meshObject::~meshObject() {
	freeFaces();
	freeVertices(); 

	initToNothing();
}

void meshObject::initToNothing() {
	m_mode = 0;


	m_normalsValid = 0;
	m_nbVertices = m_maxVertices = 0;
	m_vertex = NULL;
	m_nbFaces = m_maxFaces = 0;
	m_face = NULL;
}

int meshObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err, v, f;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const meshObject *pO = (const meshObject *)o;

	// detect change
	if ((m_nbVertices != pO->m_nbVertices) ||
		(m_nbFaces != pO->m_nbFaces) ||
		(m_mode != pO->m_mode)) propertiesChanged |= OP_DESCRIPTION;

	// release resources
	if ( (err = freeFaces()) != 0) return err;
	if ( (err = freeVertices()) != 0) return err;

	// copy
	m_mode = pO->m_mode;

	if ( (err = ensureVertices(pO->m_nbVertices)) != 0) return err;
	for (v = 0; v < pO->m_nbVertices; v++) {
		memcpy(m_vertex + v, pO->m_vertex + v, sizeof(struct vertex));
		if (m_vertex[v].nlName) m_vertex[v].nlName = strdup(m_vertex[v].nlName);
		if (m_vertex[v].posName) m_vertex[v].posName = strdup(m_vertex[v].posName);
	}

	if ( (err = ensureFaces(pO->m_nbFaces)) != 0) return err;
	for (f = 0; f < pO->m_nbFaces; f++) {
		m_face[f].nbVtx = pO->m_face[f].nbVtx;
		memcpy(m_face[f].nl, pO->m_face[f].nl, sizeof(GAIM_FLOAT) * 3);
		if ( (m_face[f].vtxIdx = (int*)calloc(sizeof(int), m_face[f].nbVtx)) == NULL) return -1;
		memcpy(m_face[f].vtxIdx, pO->m_face[f].vtxIdx, sizeof(int) * m_face[f].nbVtx);
	}


	return 0;
}

int meshObject::pick(glwindow *window) {
	return draw(window);
}

int meshObject::draw(glwindow *window) {
//	window->enableClippingPlanes();

//	glLineWidth((float)gui_state->m_lineWidth);

	// handle transparency (btw: objects are not yet sorted on depth yet....
	if (window->depthMaskAllowedOff() && (fgColor(3) < 0.99)) {
		glDepthMask(GL_FALSE); // don't write in depth buffer
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE);
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

//	glPolygonMode(GL_FRONT_AND_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
	glPolygonMode(GL_FRONT, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
//	glPolygonMode(GL_BACK, (m_drawMode & OD_WIREFRAME) ? GL_LINE : GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glMatrixMode(GL_MODELVIEW);

	return drawMesh(g_state);

	return 0;
}
/*	
int meshObject::drawParaboloid(glwindow *window) {
	double z, h1, h2;
	const double zAdd = 0.08, zMax = 3.0;
	const int nbQuads = 32;
	int i;
	e3ga x1, x2, b;
	e3ga paraAxis = e3ga::e3;
	e3ga paraPlane = paraAxis.dual();
	e3ga R = ((M_PI / nbQuads) * paraPlane).exp();

	for (z = 0.000; z <= zMax; z += zAdd) {
		x1 = z * z * e3ga::e1; // hacky, tricky, this should just be a factor from paraPlane
		x2 = (z + zAdd) * (z + zAdd) * e3ga::e1; // hacky, tricky, this should just be a factor from paraPlane

		h1 = z * z * z * z;
		h2 = (z + zAdd) * (z + zAdd) * (z + zAdd) * (z + zAdd);

		glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= nbQuads; i++) {
			b = (x1 << paraPlane) ^ (x1 - (x1 << x1) * paraAxis); b = b / sqrt(b.norm_a());
			glNormal3dv((b.dual())[GRADE1]);
			glVertex3dv((x1 -0.5*h1 * paraAxis)[GRADE1]);

			b = (x2 << paraPlane) ^ (x2 - (x2 << x2) * paraAxis); b = b / sqrt(b.norm_a());
			glNormal3dv((b.dual())[GRADE1]);
			glVertex3dv((x2 -0.5*h2 * paraAxis)[GRADE1]);

			x1 = (R * x1 * R.inverse())(GRADE1);
			x2 = (R * x2 * R.inverse())(GRADE1);
		}
		glEnd();
	}

	return 0;
}

int meshObject::createParaboloid() {
	double z, h1, h2;
	const double zAdd = 0.08, zMax = 3.0;
	const int nbQuads = 32;
	int i, j, nbVtx = 0, vtxIdx[4];
	e3ga x1, x2, b;
	e3ga paraAxis = e3ga::e3;
	e3ga paraPlane = paraAxis.dual();
	e3ga R = ((M_PI / nbQuads) * paraPlane).exp();

	// create vertices
	for (z = 0.0; z <= zMax; z += zAdd) {
		x1 = z * z * e3ga::e1; // hacky, tricky, this should just be any factor from paraPlane
		x2 = (z + zAdd) * (z + zAdd) * e3ga::e1; // hacky, tricky, this should just be a factor from paraPlane

		h1 = z * z * z * z;
		h2 = (z + zAdd) * (z + zAdd) * (z + zAdd) * (z + zAdd);

		for (i = 0; i < nbQuads; i++) {
			b = (x1 << paraPlane) ^ (x1 - (x1 << x1) * paraAxis); b = b / sqrt(b.norm_a());

			setVertexNormal(nbVtx, (b.dual())[GRADE1]);
			setVertexPos(nbVtx, (x1 -0.5*h1 * paraAxis)[GRADE1]);
			nbVtx++;

			x1 = (R * x1 * R.inverse())(GRADE1);
			x2 = (R * x2 * R.inverse())(GRADE1);
		}
	}

	// create faces
	i = 0;
	while (i < nbVtx - 2 * nbQuads) {	
		for (j = 0; j < nbQuads; j++) {
			vtxIdx[0] = i + j;
			vtxIdx[1] = i + j + nbQuads;
			vtxIdx[2] = i + ((j + 1) % nbQuads) + nbQuads;
			vtxIdx[3] = i + ((j + 1) % nbQuads);
			addFace(4, vtxIdx);
		}
		i += j;
	}

	m_mode |= OC_SPECIFY_NORMALS;
	return 0;
}
*/

float meshObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

int meshObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	if (sl) {
		sprintf(buf, "%s: mesh object", m_name.c_str());
	}
	else {
		int idx;
		buf[0] = 0;

		idx = 0;
		idx += sprintf(buf + idx, "Mesh\n%d faces, %d vertices", m_nbFaces, m_nbVertices);

		// todo..
	}
	
	return 0;
}


int meshObject::drawMesh(state *s) {
	int err, f, v;
	struct face *fc;

	// if not in dynamic mode, and we have a display list waiting: execute it
	if ((!(m_mode & OC_DYNAMIC)) && 
		(m_displayList != GL_INVALID_DISPLAY_LIST)) {
		glCallList(m_displayList);
		return 0;
	}

	// compute normals if required
	if (!m_normalsValid) 
		if ( (err = computeNormals(s)) != 0) return err;

	// set colors etc?

	// if not in dynamic mode, start a displaylist
	if (!(m_mode & OC_DYNAMIC)) {
		if ( (err = allocDisplayList()) != 0) return err;
		glNewList(m_displayList, GL_COMPILE_AND_EXECUTE);
	}

	// draw all faces
	int beginPoly = 0;
	if (m_faceType == 3) glBegin(GL_TRIANGLES);
	else if (m_faceType == 4) glBegin(GL_QUADS);
	else beginPoly = 1;
	for (f = 0; f < m_nbFaces; f++) {
		fc = m_face + f;
		if (beginPoly) glBegin(GL_POLYGON);

		if (m_mode & OC_COMPUTE_NORMALS_FLAT) glNormal3dv(fc->nl);

		for (v = 0; v < fc->nbVtx; v++) {
			if (!(m_mode & OC_COMPUTE_NORMALS_FLAT)) glNormal3dv(m_vertex[fc->vtxIdx[v]].nl);
			glVertex3dv(m_vertex[fc->vtxIdx[v]].pos);
//			printf("%d: %f %f %f\n", fc->vtxIdx[v], m_vertex[fc->vtxIdx[v]].pos[0], m_vertex[fc->vtxIdx[v]].pos[1], m_vertex[fc->vtxIdx[v]].pos[2]);
		}

		if (beginPoly) glEnd();
	}
	if (!beginPoly) glEnd();


	// if not in dynamic mode, end displaylist
	if (!(m_mode & OC_DYNAMIC)) {
		glEndList();
	}

	return 0;
}


int meshObject::ensureFaces(int nbFaces) {
	if (nbFaces <= 0) return -1;
	if (nbFaces > m_maxFaces) {
		m_maxFaces = (m_maxFaces * 2 > nbFaces) ? m_maxFaces * 2 : nbFaces;
		if ( (m_face = (struct face*)realloc(m_face, sizeof(struct face) * m_maxFaces)) == NULL) {
			printf("meshObject::ensureFaces(): memory allocation failure for %d bytes\n", (int)(sizeof(struct face) * m_maxFaces));
			return -1;
		}

		if ((m_maxFaces - m_nbFaces) > 0)
			memset(m_face + m_nbFaces, 0, sizeof(struct face) * (m_maxFaces - m_nbFaces));
	}

	return 0;
}

int meshObject::ensureVertices(int nbVertices) {
	if (nbVertices <= 0) return -1;
	if (nbVertices > m_maxVertices) {
		m_maxVertices = (m_maxVertices * 2 > nbVertices) ? m_maxVertices * 2 : nbVertices;
		if ( (m_vertex = (struct vertex*)realloc(m_vertex, sizeof(struct vertex) * m_maxVertices)) == NULL) {
			printf("meshObject::ensureVertices(): memory allocation failure for %d bytes\n", (int)(sizeof(struct vertex) * m_maxVertices));
			return -1;
		}

		if ((m_maxVertices - m_nbVertices) > 0)
			memset(m_vertex + m_nbVertices, 0, sizeof(struct vertex) * (m_maxVertices - m_nbVertices));
	}

	return 0;
}

int meshObject::freeFaces() {
	int i;

	if (m_face) {
		for (i = 0; i < m_nbFaces; i++) {
			if (m_face[i].vtxIdx) free(m_face[i].vtxIdx);
		}
		free(m_face);
		m_face = NULL;
	}
	m_nbFaces = m_maxFaces = 0;

	return 0;
}

int meshObject::freeVertices() {
	int i;

	if (m_vertex) {
		for (i = 0; i < m_nbVertices; i++) {
			if (m_vertex[i].posName) free(m_vertex[i].posName);
			if (m_vertex[i].nlName) free(m_vertex[i].nlName);
		}
		free(m_vertex);
		m_vertex = NULL;
	}
	m_nbVertices = m_maxVertices = 0;

	return 0;
}

int meshObject::setVertexPos(int idx, const GAIM_FLOAT p[3]) {
	int err;
	if (m_mode & OC_DYNAMIC) return -1;
	if ( (err = ensureVertices(idx + 1)) != 0) return err;

	meshChanged();
	memcpy(m_vertex[idx].pos, p, sizeof(GAIM_FLOAT)*3);
	m_nbVertices = (m_nbVertices > (idx + 1)) ? m_nbVertices : (idx + 1);

//	printf("setVertexPos(%d, %f %f %f)\n", idx, m_vertex[idx].pos[0], m_vertex[idx].pos[1], m_vertex[idx].pos[2]);
	return 0;
}

int meshObject::setVertexPos(int idx, const char *name) {
	int err;
	if (!(m_mode & OC_DYNAMIC)) // get vertex, set it statically
		setVertexPos(idx, getVertexPos(name));

	if ( (err = ensureVertices(idx + 1)) != 0) return err;

	// copy vertex pos name
	if ( (m_vertex[idx].posName = strdup(name)) == NULL) return -1;

	meshChanged();
	m_nbVertices = (m_nbVertices > (idx + 1)) ? m_nbVertices : (idx + 1);
	return 0;
}

int meshObject::setVertexNormal(int idx, const GAIM_FLOAT n[3]) {
	int err;
	if (m_mode & OC_DYNAMIC) return -1;
	if ( (err = ensureVertices(idx + 1)) != 0) return err;

	meshChanged();
	memcpy(m_vertex[idx].nl, n, sizeof(GAIM_FLOAT)*3);
	m_nbVertices = (m_nbVertices > (idx + 1)) ? m_nbVertices : (idx + 1);
	return 0;
}

int meshObject::setVertexNormal(int idx, const char *name) {
	int err;
	if (!(m_mode & OC_DYNAMIC)) // get normal, set it statically
		setVertexNormal(idx, getVertexNormal(name));

	if ( (err = ensureVertices(idx + 1)) != 0) return err;

	// copy vertex normal name
	if ( (m_vertex[idx].nlName = strdup(name)) == NULL) return -1;

	meshChanged();
	m_nbVertices = (m_nbVertices > (idx + 1)) ? m_nbVertices : (idx + 1);
	return 0;
}


int meshObject::addFace(int nbVtx, const int *vtxIdx) {
	int err;

	if (nbVtx < 3) {
		printf("meshObject::addFace(): invalid face (only %d faces)\n", nbVtx);
		return -1;
	}
	if ( (err = ensureFaces(m_nbFaces + 1)) != 0) return err;

	struct face *fc = m_face + m_nbFaces;

	if ( (fc->vtxIdx = (int*)calloc(nbVtx, sizeof(int))) == NULL) {
		printf("meshObject::addFace(): memory allocation failure for %d bytes\n", (int)(nbVtx * sizeof(int)));
		return -1;
	}
	memcpy(fc->vtxIdx, vtxIdx, nbVtx * sizeof(int));
	fc->nbVtx = nbVtx;

	m_nbFaces++;

	return 0;
}

int meshObject::computeNormals(state *s) {
	int v, f;
	struct face *fc;
//	static const GAIM_FLOAT null[3] = {0.0f, 0.0f, 0.0f};
	e3ga v1, v2, v3, nl;
	GAIM_FLOAT l;

	// first of all check the faces / vertices?
	m_faceType = 0; // nb of vertices for each face is constant? if so, this will be >= 3
	for (f = 0; f < m_nbFaces; f++) {
		fc = m_face + f;
		// check vertices
		for (v = 0; v < fc->nbVtx; v++)
			if ((fc->vtxIdx[v] < 0) || (fc->vtxIdx[v] >= m_nbVertices)) {
				printf("meshObject::computeNormals(): invalid face, vertex index out of range (%d >= %d)\n", fc->vtxIdx[v], m_nbVertices);
				return -1;
			}

		// check face type
		if (m_faceType < 0) continue;
		else if (m_faceType == 0) m_faceType = fc->nbVtx;
		else if (m_faceType != fc->nbVtx) m_faceType = -1;
	}

	// get all vertex positions & possibly normals if in dynamic mode
	if (m_mode & OC_DYNAMIC) {
		for (v = 0; v < m_nbVertices; v++) {
			memcpy(m_vertex[v].pos, getVertexPos(m_vertex[v].posName), 3 * sizeof(GAIM_FLOAT));
			if (m_mode & OC_SPECIFY_NORMALS)
				memcpy(m_vertex[v].nl, getVertexNormal(m_vertex[v].nlName), 3 * sizeof(GAIM_FLOAT));
		}
	}
	

	if ((m_mode & OC_COMPUTE_NORMALS_GOURAUD) || (m_mode & OC_COMPUTE_NORMALS_FLAT)) {
		// compute face normals
		for (f = 0; f < m_nbFaces; f++) {
			fc = m_face + f;

			v1.setVector(m_vertex[fc->vtxIdx[0]].pos);
			v2.setVector(m_vertex[fc->vtxIdx[1]].pos);
			v3.setVector(m_vertex[fc->vtxIdx[2]].pos);
			nl = ((v2 - v1) ^ (v3 - v1)).dual().normal();
			memcpy(fc->nl, nl[GRADE1], 3 * sizeof(GAIM_FLOAT));
		}
	}

	if (m_mode & OC_COMPUTE_NORMALS_GOURAUD) {
		// set all vtx normals to 0
		for (v = 0; v < m_nbVertices; v++) {
			memset(m_vertex[v].nl, 0, 3 * sizeof(GAIM_FLOAT));
		}

		// compute vertex normals
		for (f = 0; f < m_nbFaces; f++) {
			fc = m_face + f;
			// check vertices
			for (v = 0; v < fc->nbVtx; v++) {
				m_vertex[fc->vtxIdx[v]].nl[0] += fc->nl[0];
				m_vertex[fc->vtxIdx[v]].nl[1] += fc->nl[1];
				m_vertex[fc->vtxIdx[v]].nl[2] += fc->nl[2];
			}
		}

		// normalize normals
		for (v = 0; v < m_nbVertices; v++) {
			l = sqrt(m_vertex[v].nl[0] * m_vertex[v].nl[0] +  m_vertex[v].nl[1] * m_vertex[v].nl[1] + m_vertex[v].nl[2] * m_vertex[v].nl[2]);
			m_vertex[v].nl[0] /= l;
			m_vertex[v].nl[1] /= l;
			m_vertex[v].nl[2] /= l;			
		}
	}

	m_normalsValid = 1;

	return 0;
}


int meshObject::meshChanged() {
	m_normalsValid = 0;
	return freeDisplayList();
}

const GAIM_FLOAT *meshObject::getVertexPos(const char *name) {
	static const GAIM_FLOAT null[3] = {0.0, 0.0, 0.0};

	object *o = g_state->getObjectPtrByName(name);
	return (o) ? o->getPoint(0) : null;
}

const GAIM_FLOAT *meshObject::getVertexNormal(const char *name) {
	static const GAIM_FLOAT null[3] = {0.0, 0.0, 0.0};

	object *o = g_state->getObjectPtrByName(name);
	return (o) ? o->getNormal(0) : null;
}
