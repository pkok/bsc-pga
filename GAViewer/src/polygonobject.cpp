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

polygonObject::polygonObject(const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/) : object(OT_POLYGON, name, drawMode, creationFlags) {
	initToNothing();

	m_properties = OP_HIDE | OP_FGCOLOR | OP_OLCOLOR | OP_NAME | OP_DESCRIPTION | OP_DRAWMODE | OP_DRAWMETHOD;

	m_drawMode |= OD_SHADE;

	setSimplex(0); // polygon by default

	m_dmMenuIdx = 0;
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;

	m_mode = creationFlags;

}

polygonObject::~polygonObject() {
	freeAllVertices(); 

	initToNothing();
}

void polygonObject::initToNothing() {
	m_nbVertices = 0;
	m_vertexName = NULL;
	m_vertex = NULL;
	m_mode = 0;
	m_simplex = 0;
}

int polygonObject::setSimplex(int simplex) {
	m_simplex = simplex;
	if (m_simplex) {
		m_dmMenu = gui_simplexMethods;
	}
	else {
		m_dmMenu = gui_polygonMethods;
	}
	return 0;
}


int polygonObject::freeAllVertices() {
	int i;
	if (m_vertexName) {
		for (i = 0; i < m_nbVertices; i++)
			free (m_vertexName[i]);
		free(m_vertexName);
	}
	if (m_vertex) {
		free(m_vertex);
	}
	m_nbVertices = 0;
	m_vertex = NULL;
	m_vertexName = NULL;
	return 0;
}

int polygonObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err, i;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const polygonObject *pO = (const polygonObject *)o;

	// detect change
	if ((m_nbVertices != pO->m_nbVertices) ||
		(m_mode != pO->m_mode)) propertiesChanged |= OP_DESCRIPTION;
	else {
		if (m_mode == OC_DYNAMIC) {
			for (i = 0; i < pO->m_nbVertices; i++)
				if (strcmp(m_vertexName[i], pO->m_vertexName[i]))
					propertiesChanged |= OP_DESCRIPTION;
		}
		else {
			if ((m_vertex == NULL) || memcmp(m_vertex, pO->m_vertex, sizeof(GAIM_FLOAT) * 3 * pO->m_nbVertices))
				propertiesChanged |= OP_DESCRIPTION;
		}
	}

	// copy
	if ( (err = freeAllVertices()) != 0) return err;

	m_mode = pO->m_mode;
	m_simplex = pO->m_simplex;

	if (m_mode == OC_DYNAMIC) {
		m_vertexName = (char**)calloc(sizeof(char*), pO->m_nbVertices);
		for (i = 0; i < pO->m_nbVertices; i++)
			m_vertexName[i] = strdup(pO->m_vertexName[i]);
	}
	else {
		m_vertex = (GAIM_FLOAT*)calloc(sizeof(GAIM_FLOAT) * 3, pO->m_nbVertices);
		memcpy(m_vertex, pO->m_vertex, sizeof(GAIM_FLOAT) * 3 * pO->m_nbVertices);
	}
	m_nbVertices = pO->m_nbVertices;

	return 0;
}

int polygonObject::pick(glwindow *window) {
	return draw(window);
}

int polygonObject::draw(glwindow *window) {
//	window->enableClippingPlanes();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glLineWidth((float)gui_state->m_lineWidth);

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

	if (m_simplex) return drawSimplex(window);
	else return drawPolygon(window);
}

int polygonObject::drawPolygon(glwindow *window) {
	TubeDraw &T = gui_state->m_tubeDraw;
	

	int i;

	// compute the normal
	e3ga n(((e3ga(GRADE1, getVertex(1)) - e3ga(GRADE1, getVertex(0))) ^
			  (e3ga(GRADE1, getVertex(2)) - e3ga(GRADE1, getVertex(0)))).dual());

	glNormal3dv(n[GRADE1]);

	if (m_dmMenuIdx == DRAW_PG_FILLED) {
		glPolygonMode(GL_FRONT, GL_FILL);
		glBegin(GL_POLYGON);
		for (i = 0; i < m_nbVertices; i++)
			glVertex3dv(getVertex(i));
		glEnd();
		glNormal3dv((-n)[GRADE1]);
		glBegin((m_drawMode & OD_ORI) ? GL_LINE_LOOP : GL_POLYGON);
		for (i = m_nbVertices - 1; i >= 0 ; i--)
			glVertex3dv(getVertex(i));
		glEnd();
		if (m_drawMode & OD_OUTLINE) {
			setOlColor();
			glDisable(GL_LIGHTING);
			T.begin(GL_LINE_LOOP);
			for (i = 0; i < m_nbVertices; i++)
				T.vertex3dv(getVertex(i));
			T.end();
		}
	}
	else if ((m_dmMenuIdx == DRAW_PG_LINE_STRIP) ||
		(m_dmMenuIdx == DRAW_PG_LINE_LOOP)) {
		glDisable(GL_LIGHTING);
		glBegin((m_dmMenuIdx == DRAW_PG_LINE_STRIP) ? GL_LINE_STRIP : GL_LINE_LOOP);
		for (i = 0; i < m_nbVertices; i++)
			glVertex3dv(getVertex(i));
		glEnd();
	}

	return 0;
}

int polygonObject::drawSimplex(glwindow *window) {
	TubeDraw &T = gui_state->m_tubeDraw;
	int i;
	const GAIM_FLOAT *v1, *v2, *v3;
	GAIM_FLOAT tmp[3], l;
	e3ga n, pt[3], hpt, ovc, apt;

	switch (m_nbVertices) {
	case 1:
		drawTriVector(getVertex(0), 0.05, NULL, DRAW_TV_SPHERE, 0, this);
		break;
	case 2:

		v1 = getVertex(0); v2 = getVertex(1); 

		if (m_dmMenuIdx == DRAW_SP_DEFAULT) {
			for (i = 0; i < 3; i++) tmp[i] = 0.5 * (v2[i] - v1[i]);
			l = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
			for (i = 0; i < 3; i++) tmp[i] /= l;

			drawVector(v1, tmp, l);

			glDisable(GL_LIGHTING);
			for (i = 0; i < 3; i++) tmp[i] = 0.5 * (v2[i] + v1[i]);
			T.begin(GL_LINES);
				T.vertex3dv(tmp);
				T.vertex3dv(v2);
			T.end();
		}
		else if (m_dmMenuIdx == DRAW_SP_VECTOR) {
			for (i = 0; i < 3; i++) tmp[i] = (v2[i] - v1[i]);
			l = sqrt(tmp[0] * tmp[0] + tmp[1] * tmp[1] + tmp[2] * tmp[2]);
			for (i = 0; i < 3; i++) tmp[i] /= l;
			drawVector(v1, tmp, l);
		}

		break;
	case 3:
		v1 = getVertex(0); v2 = getVertex(1); v3 = getVertex(2); 

		// compute the normal
		n = (((e3ga(GRADE1, v2) - e3ga(GRADE1, v1)) ^
				  (e3ga(GRADE1, v3) - e3ga(GRADE1, v1))).dual());

		glNormal3dv(n[GRADE1]);
		glBegin(GL_POLYGON);
			for (i = 0; i < m_nbVertices; i++)
				glVertex3dv(getVertex(i));
			glEnd();
		glNormal3dv((-n)[GRADE1]);
		glBegin(GL_POLYGON);
			for (i = m_nbVertices - 1; i >= 0 ; i--)
				glVertex3dv(getVertex(i));
		glEnd();
		if (m_drawMode & OD_OUTLINE) {
			setOlColor();
			glDisable(GL_LIGHTING);
			T.begin(GL_LINE_LOOP);
			for (i = 0; i < m_nbVertices; i++)
				T.vertex3dv(getVertex(i));
			T.end();
		}
		if (m_drawMode & OD_ORI) {
			setOlColor();
			//e3ga n, pt[3], hpt, ovc, apt;
			for (i = 0; i < m_nbVertices; i++)
				pt[i].setVector(getVertex(i));
			T.begin(GL_LINES);
			for (i = 0; i < m_nbVertices; i++) {
				hpt = 0.5 * (pt[i] + pt[(i + 1) % m_nbVertices]);
				ovc = ((pt[(i + 1) % m_nbVertices] - pt[i]) ^ n).dual().normal();
				apt = 0.7 * pt[i] + 0.3 * pt[(i + 1) % m_nbVertices] + 0.1 * ovc;
				T.vertex3dv(hpt[GRADE1]);
				T.vertex3dv(apt[GRADE1]);
			}
			T.end();
		}
		break;
	default:
		return -1;
	}

	return 0;
}


float polygonObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

int polygonObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	if (sl) {
		sprintf(buf, "%s: polygon object", m_name.c_str());
	}
	else {
		int idx, i;
		buf[0] = 0;

		idx = 0;
		idx += sprintf(buf + idx, "Polygon\n");
		idx += sprintf(buf + idx, "Number of vertices: %d\n", m_nbVertices);
		if (m_nbVertices <= 6) {
			if (m_mode & OC_DYNAMIC) {
				for (i = 0; i < m_nbVertices; i++)
					idx += sprintf(buf + idx, "vertex %d: %s\n", i + 1, m_vertexName[i]);
			}
			else {
				for (i = 0; i < m_nbVertices; i++)
					idx += sprintf(buf + idx, "vertex %d: %2.2f %2.2f %2.2f\n", i + 1, m_vertex[i * 3 + 0], m_vertex[i * 3 + 1], m_vertex[i * 3 + 2]);
			}
		}
	}

	return 0;
}

const GAIM_FLOAT *polygonObject::getVertex(int idx) {
	static const GAIM_FLOAT null[3] = {0.0, 0.0, 0.0};

	if ((idx < 0) || (idx >= m_nbVertices)) return null;

	if (m_mode & OC_DYNAMIC) {
		object *o = g_state->getObjectPtrByName(m_vertexName[idx]);
		return (o) ? o->getPoint(0) : null;
	}
	return m_vertex + idx * 3;
}


int polygonObject::addVertex(const char *name) {
	object *o = g_state->getObjectPtrByName(name);
	if (o == NULL) return -1;

	if (m_mode & OC_DYNAMIC) {
		m_vertexName = (char**)realloc(m_vertexName, sizeof(char*) * (m_nbVertices + 1));
		if (m_vertexName == NULL) return -1;
		m_vertexName[m_nbVertices] = strdup(name);
		if (m_vertexName[m_nbVertices] == NULL) return -1;
	}
	else {
		m_vertex = (GAIM_FLOAT*)realloc(m_vertex, sizeof(GAIM_FLOAT) * 3 * (m_nbVertices + 1));
		if (m_vertex == NULL) return -1;
		const GAIM_FLOAT *p = o->getPoint(0);
		if (p) memcpy(m_vertex + m_nbVertices * 3, p, 3 * sizeof(GAIM_FLOAT));
		else memset(m_vertex + m_nbVertices * 3, 0, 3 * sizeof(GAIM_FLOAT));
	}
	m_nbVertices++;
	return 0;
}

	
