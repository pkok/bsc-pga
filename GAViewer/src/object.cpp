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

#include "state.h"
#include "osdep.h"
#include "uistate.h"
#include "glwindow.h"

#include "gl_includes.h"

#include "object.h"

using namespace std;

int object::m_objectCount = 1;

object::object(int type, const std::string &name /*= std::string("")*/,  int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) {
	initToNothing();

	m_type = type;
	m_drawMode = drawMode;

//	m_retainDrawPropertiesOnCopy = ((creationFlags & OC_RETAIN_DRAW_PROPERTIES_ON_COPY) != 0);

	// set name (or default name)
	if ((name == "") || (name == "untitled"))
		m_name = "object_" + m_objectCount;
	else m_name = name;
	m_objectCount++;
}

object::~object() {
	//if (m_name) free(m_name);
	freeDisplayList();

	initToNothing();
}

void object::initToNothing() {
	m_name = "";
	m_type = OT_NOTHING;
	m_properties = 0;
	memset(m_fgColor, 0, sizeof(float) * 4);
	memset(m_bgColor, 0, sizeof(float) * 4);
	memset(m_olColor, 0, sizeof(float) * 4);
	m_fontSize = -1.0;
	m_drawMode = 0;

	m_dmMenu = NULL;
	m_dmMenuIdx = -1;

	m_poFactor = m_poUnits = 0.0;

	m_fadeStartTime = m_fadeEndTime = -1.0f;
	m_fadeCurrentFactor = m_fadeStartFactor = m_fadeEndFactor = 1.0;
	m_fadeAction = FADE_NO_FADE;

//	m_retainDrawPropertiesOnCopy = 0;

	m_displayList = GL_INVALID_DISPLAY_LIST;
}

int object::copy(const object *o, int &propertiesChanged, int forceFlag /*= -1*/) {
	propertiesChanged = 0;
	if ((o->m_type != m_type) || (m_dmMenu != o->m_dmMenu) ||
		(m_properties != o->m_properties)) {
//		printf("object::copy(): attempt to copy incompatable objects '%s' <- '%s'\n", m_name, o->m_name);
		return -1;
	}


	if ((m_properties & OP_NAME) && (m_name == o->m_name)) {
		propertiesChanged |= OP_NAME;
		//free(m_name);
		m_name = o->m_name;
	}

	//if (!o->m_retainDrawPropertiesOnCopy) {

	if (forceFlag & OFF_COLOR) {
		if ((m_properties & OP_FGCOLOR) && (memcmp(m_fgColor, o->m_fgColor, 3 * sizeof(float))))
			propertiesChanged |= OP_FGCOLOR;
		if ((m_properties & OP_BGCOLOR) && (memcmp(m_bgColor, o->m_bgColor, 3 * sizeof(float))))
			propertiesChanged |= OP_BGCOLOR;
		if ((m_properties & OP_OLCOLOR) && (memcmp(m_olColor, o->m_olColor, 3 * sizeof(float))))
			propertiesChanged |= OP_OLCOLOR;

		copyColors(o);
	}

	if (forceFlag & OFF_ALPHA) {
		if ((m_properties & OP_FGCOLOR) && (m_fgColor[3] != o->m_fgColor[3]))
			propertiesChanged |= OP_FGCOLOR;
		if ((m_properties & OP_BGCOLOR) && (m_bgColor[3] != o->m_bgColor[3]))
			propertiesChanged |= OP_BGCOLOR;
		if ((m_properties & OP_OLCOLOR) && (m_olColor[3] != o->m_olColor[3]))
			propertiesChanged |= OP_OLCOLOR;

		copyAlphas(o);
	}

	if ((m_properties & OP_DRAWMODE) && (m_drawMode != o->m_drawMode)) {
		propertiesChanged |= OP_DRAWMODE;

//		const int drawModeFlags = OFF_STIPPLE | OFF_ORI | OFF_WIREFRAME |
	//		OFF_SHADE | OFF_MAGNITUDE | OFF_HIDE | OFF_OUTLINE;

		m_drawMode = (m_drawMode ^ (m_drawMode & forceFlag)) | (forceFlag & o->m_drawMode);
	}

	if ((m_properties & OP_DRAWMETHOD) && (m_dmMenuIdx != o->m_dmMenuIdx)) {
		if (forceFlag & OFF_DRAWMETHOD) {
			propertiesChanged |= OP_DRAWMETHOD;
			m_dmMenuIdx = o->m_dmMenuIdx;
		}
	}


	if ((m_properties & OP_FONTSIZE) && (m_fontSize != o->m_fontSize)) {
		propertiesChanged |= OP_FONTSIZE;
		m_fontSize = o->m_fontSize;
		// fs change 1
	}

	return 0;
}

int object::description(char *buf, int bufLen, int sl /* = 0 */) {
	if (!sl) sprintf(buf, "No description available");
	else sprintf(buf, "%s: no description available", m_name.c_str());
	return 0;
}

void object::setFgColor() {
	// todo: add alpha fade?
	GLfloat ambientColor[4] = {m_fgColor[0] * g_state->m_ambient, m_fgColor[1] * g_state->m_ambient, m_fgColor[2] * g_state->m_ambient, m_fgColor[3]};
	GLfloat diffuseColor[4] = {m_fgColor[0] * g_state->m_diffuse, m_fgColor[1] * g_state->m_diffuse, m_fgColor[2] * g_state->m_diffuse, m_fgColor[3]};
	ambientColor[3] *= m_fadeCurrentFactor;	diffuseColor[3] *= m_fadeCurrentFactor;
	glColor4f(m_fgColor[0], m_fgColor[1], m_fgColor[2], m_fgColor[3] * m_fadeCurrentFactor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
}

void object::setBgColor() {
	
	GLfloat ambientColor[4] = {m_bgColor[0] * g_state->m_ambient, m_bgColor[1] * g_state->m_ambient, m_bgColor[2] * g_state->m_ambient, m_bgColor[3]};
	GLfloat diffuseColor[4] = {m_bgColor[0] * g_state->m_diffuse, m_bgColor[1] * g_state->m_diffuse, m_bgColor[2] * g_state->m_diffuse, m_bgColor[3]};
	ambientColor[3] *= m_fadeCurrentFactor;	diffuseColor[3] *= m_fadeCurrentFactor;
	glColor4f(m_bgColor[0], m_bgColor[1], m_bgColor[2], m_bgColor[3] * m_fadeCurrentFactor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
}

void object::setOlColor() {
	
	GLfloat ambientColor[4] = {m_olColor[0] * g_state->m_ambient, m_olColor[1] * g_state->m_ambient, m_olColor[2] * g_state->m_ambient, m_olColor[3]};
	GLfloat diffuseColor[4] = {m_olColor[0] * g_state->m_diffuse, m_olColor[1] * g_state->m_diffuse, m_olColor[2] * g_state->m_diffuse, m_olColor[3]};
	ambientColor[3] *= m_fadeCurrentFactor;	diffuseColor[3] *= m_fadeCurrentFactor;
	glColor4f(m_olColor[0], m_olColor[1], m_olColor[2], m_olColor[3] * m_fadeCurrentFactor);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColor);
}

int object::copyColors(const object *o) {
	memcpy(m_fgColor, o->m_fgColor, sizeof(float) * 3);
	memcpy(m_bgColor, o->m_bgColor, sizeof(float) * 3);
	memcpy(m_olColor, o->m_olColor, sizeof(float) * 3);
	return 0;
}

int object::copyAlphas(const object *o) {
	m_fgColor[3] = o->m_fgColor[3];
	m_bgColor[3] = o->m_bgColor[3];
	m_olColor[3] = o->m_olColor[3];
	return 0;
}

void object::setFgColor(const float c[4]) {
	memcpy(m_fgColor, c, sizeof(float) * 4);
}
void object::setBgColor(const float c[4]) {
	memcpy(m_bgColor, c, sizeof(float) * 4);
}
void object::setOlColor(const float c[4]) {
	memcpy(m_olColor, c, sizeof(float) * 4);
}

void object::setFgColor(const double c[4]) {
	for (int i = 0; i < 4; i++) m_fgColor[i] = (float)c[i];
	colorFgChanged();
}
void object::setBgColor(const double c[4]) {
	for (int i = 0; i < 4; i++) m_bgColor[i] = (float)c[i];
	colorBgChanged();
}
void object::setOlColor(const double c[4]) {
	for (int i = 0; i < 4; i++) m_olColor[i] = (float)c[i];
	colorOlChanged();
}

void object::setFgAlpha(float alpha) {
	m_fgColor[3] = alpha;
	colorFgChanged();
}
void object::setBgAlpha(float alpha) {
	m_bgColor[3] = alpha;
	colorBgChanged();
}
void object::setOlAlpha(float alpha) {
	m_olColor[3] = alpha;
	colorOlChanged();
}

// retrieve a component [0 .. 3] from a color
float object::fgColor(int idx) {
	return ((idx < 0) || (idx > 3)) ? 0.0f : (m_fgColor[idx] * ((idx == 3) ? m_fadeCurrentFactor : 1.0f));
}
float object::bgColor(int idx) {
	return ((idx < 0) || (idx > 3)) ? 0.0f : (m_bgColor[idx] * ((idx == 3) ? m_fadeCurrentFactor : 1.0f));
}
float object::olColor(int idx) {
	return ((idx < 0) || (idx > 3)) ? 0.0f : (m_olColor[idx] * ((idx == 3) ? m_fadeCurrentFactor : 1.0f));
}

const float *object::fgColor() const {
	return m_fgColor;
}
const float *object::bgColor() const {
	return m_bgColor;
}
const float *object::olColor() const {
	return m_olColor;
}


int object::toggleHide() {
	m_drawMode = m_drawMode ^ OD_HIDE;
	return 0;
}

int object::hide() {
	m_drawMode = m_drawMode | OD_HIDE;
	return 0;
}

int object::show() {
	m_drawMode = m_drawMode & (0XFFFFFFFF ^ OD_HIDE);
	return 0;
}

const GAIM_FLOAT *object::getPoint(int idx) {
	if (this == NULL) return NULL;
	else if (m_type == OT_E3GA) return ((e3gaObject*)this)->m_int.m_point[idx];
	else if (m_type == OT_P3GA) return ((p3gaObject*)this)->m_int.m_point[idx];
	else if (m_type == OT_C3GA) return ((c3gaObject*)this)->m_int.m_point[idx];
	else if (m_type == OT_C5GA) return ((c5gaObject*)this)->m_int.m_point[idx];
	else if (m_type == OT_I2GA) return ((i2gaObject*)this)->m_int.m_point[idx];
	else if (m_type == OT_TEXT) return ((textObject*)this)->m_pos[GRADE1];
	else if (m_type == OT_POLYGON) {
		const polygonObject *p = (polygonObject *)this;
		if (idx >= p->m_nbVertices) return NULL;
		return ((p->m_mode & OC_DYNAMIC) 
			? g_state->getObjectPtrByName(p->m_vertexName[idx])->getPoint(0) 
			: (p->m_vertex + idx * 3));
	}
	// todo: return first point of mesh?
	else return NULL;
}

const GAIM_FLOAT *object::getNormal(int idx) {
	if (this == NULL) return NULL;
	else if (m_type == OT_E3GA) return ((e3gaObject*)this)->m_int.m_vector[idx];
	else if (m_type == OT_P3GA) return ((p3gaObject*)this)->m_int.m_vector[idx];
	else if (m_type == OT_C3GA) return ((c3gaObject*)this)->m_int.m_vector[idx];
	else if (m_type == OT_C5GA) return ((c5gaObject*)this)->m_int.m_vector[idx];
	else if (m_type == OT_I2GA) return ((i2gaObject*)this)->m_int.m_vector[idx];
	else if (m_type == OT_TEXT) return ((textObject*)this)->m_pos[GRADE1];
	// todo: fix this for more type of normals (c3ga?)
	else return NULL;
}


int object::update(double currentTime) {
	if (m_fadeAction != FADE_NO_FADE) {
		gui_state->m_glWindow->redraw();

		if ((g_state->m_bookmarkSearch) || 
			(currentTime >= m_fadeEndTime)) { // end fade

			m_fadeCurrentFactor = m_fadeEndFactor;

			if (m_fadeAction == FADE_REMOVE) {
				throw removeObjectException();
				/*g_state->removeObject(this); // this _deletes_ this object...
				return 0; // ...so we must return*/
			}
			else if (m_fadeAction == FADE_HIDE)	{
				hide();
			}
			
			m_fadeAction = FADE_NO_FADE;
		}
		else { // just fade
			m_fadeCurrentFactor = (float)
				(m_fadeStartFactor + (m_fadeEndFactor - m_fadeStartFactor) *
				(currentTime - m_fadeStartTime) / (m_fadeEndTime - m_fadeStartTime));

			// fade influences all colors:
			colorFgChanged();
			colorBgChanged();
			colorOlChanged();
		}
	}


	return 0;
}

int object::setFade(double duration, float target, int action, float startFadeFactor /*= -1.0*/) {

	m_fadeStartTime = u_timeGet();
	m_fadeEndTime = m_fadeStartTime + duration;
	m_fadeStartFactor = (startFadeFactor >= 0.0) ? startFadeFactor : m_fadeCurrentFactor;
	m_fadeEndFactor = target;
	m_fadeAction = ((action < FADE_NO_FADE) || (action > FADE_REMOVE)) ? FADE_NOTHING : action;

	// update immediately
	update(m_fadeStartTime);

	return 0;
}


int object::setFontSize(float size) {
	if (size < 1e-5f) size = 1e-5f;
	m_fontSize = size;
	return 0;
}

// these functions get called when the color (or alpha) has changed
void object::colorFgChanged() {
}
void object::colorBgChanged() {
}
void object::colorOlChanged() {
}

void object::textScaleChanged() {
}


int object::allocDisplayList() {
	if (m_displayList != GL_INVALID_DISPLAY_LIST)
		freeDisplayList();
	// todo: error checking
	m_displayList = glGenLists(1);
	return 0;
}

int object::freeDisplayList() {
	if (m_displayList == GL_INVALID_DISPLAY_LIST) return 0;

	// todo: error checking
	glDeleteLists(m_displayList, 1);
	m_displayList = GL_INVALID_DISPLAY_LIST;
	return 0;
}

int object::translate(glwindow *window, double z, double motionX, double motionY) {
	printf("Translate %f, %f %f\n", z, motionX, motionY);


	return 0;
}

std::string object::toString(const char *floatPrec) {
	return "";
}
