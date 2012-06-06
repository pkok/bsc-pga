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
#include <string.h>
#include <math.h>
#include <time.h>

#include <FL/Fl.H>
#include "gl_includes.h"


#include "glwindow.h"
#include "state.h"
#include "uistate.h"
#include "object.h"
#include "util.h"
#include "typeset/openglfont.h"
#include "geosphere.h"
#include "osdep.h"
#include "console/consolevariable.h"
#include "console/consolescope.h"

static GLubyte s_polygonStipplePattern[] = {
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 
	0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 0X33, 
	0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC, 0XCC
};

glwindow::glwindow(int X, int Y, int W, int H, const char *L) : Fl_Gl_Window (X, Y, W, H, L) {
	initToNothing();

	setNearFarClipPlanes(-1.0, -1.0); // reset near and far clip planes

	setCamPos(11 * e3ga::e3);
	setCamOri(e3ga(1));// identity rotation

	m_depthMaskAllowedOff = 1;


	box(FL_NO_BOX);

}

glwindow::~glwindow() {
	clearRecentPicks();

	initToNothing();
}

void glwindow::initToNothing() {
	m_nbRecentPicks = 0;
	m_recentPicks = NULL;
	m_mouseButtons = m_mousePickMode = 0;
	memset(m_pick, -1, sizeof(int) * 4);

	/*m_pos.setVector(0.0, 0.0, 0.0);
	m_rot.setScalar(0.0f);*/
	m_depthMaskAllowedOff = 0;

	m_translationDepth = -1;
	m_frustumWidth = m_frustumHeight = -1.0;
	m_frustumNear = m_frustumFar = -1.0;

	m_screenShotActive = false;
}

void glwindow::setNearFarClipPlanes(double n, double f) {
	if ((n > f) || (n <= 0.0) || (f <= 0.0)) {
		m_defaultFrustumNear = 0.95;
		m_defaultFrustumFar = 100.0;
	}
	else {
		m_defaultFrustumNear = n;
		m_defaultFrustumFar = f;
	}
}


e3ga & glwindow::getCamOri() {
	static e3ga ori;
	if (g_state && (g_state->m_globalScope->externalLookupVariable("camori", 1, ori) == 0)) {
		// nothing to do...
	}
	else ori = 1.0;
	return ori;
}

void glwindow::setCamOri(const e3ga &R) {
	if (g_state) {
		g_state->m_globalScope->externalAssignVariable("camori", R, OD_HIDE | OD_HIDE_ALWAYS);
		g_state->updateDynStmts();
	}

}

e3ga & glwindow::getCamPos() {
	static e3ga pos;
	if (g_state && (g_state->m_globalScope->externalLookupVariable("campos", 1, pos) == 0)) {
		// nothing to do...
	}
	else pos = -11.0 * e3ga::e3;
	return pos;
/*	static e3ga def(GRADE1, 0.0, 0.0, -11.0);
	consoleVariable *cv;
	if (g_state) {
		if (g_state->m_globalScope->lookupVariable("campos", 1, &cv) == 0) {
			consoleVariable *pos = cv->castToE3ga();
			delete cv;
			return pos->e();
		}
	}

	cprintf("glwindow::getCamPos(): could not get 'campos' from global scope\n");
	return def;*/
}

void glwindow::setCamPos(const e3ga &t) {
	if (g_state) {
		g_state->m_globalScope->externalAssignVariable("campos", t, OD_HIDE | OD_HIDE_ALWAYS | OD_MAGNITUDE);
//		g_state->m_globalScope->assignVariable(new consoleVariable("campos", e3ga(0.0)), new consoleVariable("", t));
		g_state->updateDynStmts();
	}

}



static int glwindowObjectCompare(const void *elem1, const void *elem2 ) {
	object *o1 = *(object**)elem1;
	object *o2 = *(object**)elem2;

	float o1Val = o1->drawSortValue(), o2Val = o2->drawSortValue();
	
	return (o1Val < o2Val) ? -1 : ((o1Val > o2Val) ? 1 : 0);
}

void glwindow::draw() {
	m_screenShotActive = false;

	// not in picking mode
	memset(m_pick, -1, sizeof(int) * 4);

	// load font
	if (oglffont("verdana256x256") < 0) {
		printf("textObject::draw(): could not set font\n");
	}

	beginglDraw();

	if (gui_state && (gui_state->m_screenShotOnNextRedraw > 0)) {
		if (gui_state->m_screenShotOnNextRedraw == 1)
			performScreenShot();
		else {
			gui_state->m_screenShotOnNextRedraw--;
		}
	}

	drawScene();

	endglDraw();
}

void glwindow::drawScene() {
	int i;

	glDepthMask(GL_TRUE);
	glClearColor(g_state->m_cvColor[0], g_state->m_cvColor[1], 
		g_state->m_cvColor[2], g_state->m_cvColor[3]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set all kinds of GL stuff
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	GLfloat light0Pos[4] = {0.0f, 0.0f, 1.0f, 0.0f};
	GLfloat light1Pos[4] = {0.7f, 0.0f, 0.7f, 0.0f};
	GLfloat light0Diffuse[4] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat light0Specular[4] = {0.8f, 0.8f, 0.8f, 1.0f};
	GLfloat light1Diffuse[4] = {0.35f, 0.35f, 0.35f, 1.0f};
	GLfloat light1Specular[4] = {0.35f, 0.35f, 0.35f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1Specular);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
	glLightfv(GL_LIGHT1, GL_POSITION, light1Pos);

	glLineStipple(1, 0x0F0F);
	glPolygonStipple(s_polygonStipplePattern);

	// setup transformation, clipping planes
	setup3DProjection();
	setupEyeTransform();
//	setupClippingPlanes();

	// draw the objects
	int nbo = g_state->m_objects.size(), t = 0;
	state::OI oi;
	if (nbo) { // todo: maybe, during sorting, add (or subtract???) the avg z-value of the objects? such that far objects are drawn before near objects (especially for text labels??)
		object **o = (object**)calloc(sizeof(object*), nbo);
		nbo = 0;
		for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++) {
			if (!(oi->second->m_drawMode & OD_HIDE))
				o[nbo++] = oi->second;
		}
		//memcpy(o, g_state->m_object, sizeof(object*) * nbo);
		qsort(o, nbo, sizeof(object*), glwindowObjectCompare);
		for (i = 0; i < nbo; i++) {
			if (g_state->m_labelsAlwaysOnTop && (o[i]->m_type == OT_TEXT) && (!t)) { // disable clipping planes, clear the depth buffer for the labels
				t = 1;
				glDepthMask(GL_TRUE);
				glClear(GL_DEPTH_BUFFER_BIT);
			}
			if ((o[i]->m_poFactor != 0.0) || (o[i]->m_poFactor != 0.0)) {
				glEnable(GL_POLYGON_OFFSET_FILL);
				glEnable(GL_POLYGON_OFFSET_LINE);
				glEnable(GL_POLYGON_OFFSET_POINT);
				glPolygonOffset(o[i]->m_poFactor, o[i]->m_poFactor);
			}
			else {
				glDisable(GL_POLYGON_OFFSET_FILL);
				glDisable(GL_POLYGON_OFFSET_LINE);
				glDisable(GL_POLYGON_OFFSET_POINT);
			}
			o[i]->draw(this);
		}
		free(o);
	}

	if (g_state->m_inputWait && gui_state->m_fullscreen) {
		// draw a small red 'W' in the lower right corner while waiting
		glLineWidth(1.0);
		glDisable(GL_LIGHTING);
		setup2DOrtho();
		glColor4f(1.0, 0.0, 0.0, 1.0);
		glBegin(GL_LINE_STRIP);
		float Wx = (float)(w() - 40);
		float Wy = 40.0;
		float Wh = 17.0, Ww = 25.0;
		for (i = 0; i < 5; i++)
			glVertex3f(Wx + (float)i * Ww / 5.0f, Wy - ((i & 1) ? Wh : 0.0), -2.0f);
		glEnd();
	}
}


object *glwindow::pick(int x, int y, int repeastLastPick, int storeTranslationDepth) {
	m_screenShotActive = false;

	int i;
	int nbo = g_state->m_objects.size();
	if (nbo == 0) return NULL;

	// disable clipping (causes trouble with Mesa during picking)
//	int clippingPlanes = g_state->m_clippingPlanesEnabled;
//	g_state->m_clippingPlanesEnabled = 0;
	
	m_pick[0] = x;
	m_pick[1] = y;
	m_pick[2] = 1;
	m_pick[3] = 1;

	make_current();

	GLuint *sb = (GLuint*)calloc(nbo, 4 * sizeof(GLuint));
	glSelectBuffer(nbo * 4 * sizeof(int), sb);
	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	beginglDraw();
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	setup3DProjection();
	setupEyeTransform();
//	setupClippingPlanes();


	// draw the objects in picking mode
	int t = 0;
	object **o = (object**)calloc(sizeof(object*), nbo);
	nbo = 0;
	state::OI oi;
	for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++) 
		if (!(oi->second->m_drawMode & OD_HIDE))
			o[nbo++] = oi->second;
	//memcpy(o, g_state->m_object, sizeof(object*) * nbo);
	qsort(o, nbo, sizeof(object*), glwindowObjectCompare);
	for (i = 0; i < nbo; i++) {
		glLoadName(i);
		if (g_state->m_labelsAlwaysOnTop && (o[i]->m_type == OT_TEXT) && (!t)) { // disable clipping planes, clear the depth buffer for the labels
			t = 1;
			glDepthMask(GL_TRUE);
			glClear(GL_DEPTH_BUFFER_BIT); // no need to do this in GL_SELECT mode???
		}
		o[i]->pick(this);
	}

	endglDraw();

	// get the number of hit records
	int nb = glRenderMode(GL_RENDER);

	// get closest object
	int idx;
	object *obj = NULL, *tmpObj;
	GLuint oZ;
	int repI;

	for (repI = 0; repI < 2; repI++) { // loop twice (recent pick cleared after first loop)
		idx = 0;
		oZ = 0XFFFFFFFF;

		for (i = 0; i < nb; i++) {
			if (sb[idx] != 1) {obj = NULL; break;}
			tmpObj = o[sb[idx + 3]];

			if ((sb[idx + 1] < oZ) || (obj && g_state->m_labelsAlwaysOnTop && (obj->m_type != OT_TEXT))) {
				if ((obj == NULL) ||
					((obj->m_type != OT_TEXT) && (sb[idx + 1] < oZ)) ||
					(!g_state->m_labelsAlwaysOnTop) ||
					(tmpObj->m_type == OT_TEXT)) {

					if (!pickedRecently(tmpObj, x, y, repeastLastPick)) { // check if not already picked
						obj = tmpObj;
						oZ = sb[idx + 1];
					}
				}
			}
			idx += 4;
		}
		if (obj) break; // we have found an object; don't clear the recent picks buffer

		clearRecentPicks();
	}

	free(sb);
	free(o);

	// add object to recent pick list
	if (obj) addRecentPick(obj, x, y, repeastLastPick);

	if (obj && storeTranslationDepth) {// determine depth
		
		glDrawBuffer(GL_BACK);
		glReadBuffer(GL_BACK);

		memset(m_pick, -1, sizeof(int) * 4);

		glDepthMask(GL_TRUE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		setup3DProjection();
		setupEyeTransform();

		m_depthMaskAllowedOff = 0; // force transparent objects to write in the depth buffer
		obj->draw(this);
		m_depthMaskAllowedOff = 1; 

		// get pixel depth at that location
		GLfloat zPixelWindowCoordinates, zPixelWorldCoordinates;
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &zPixelWindowCoordinates);

		if (zPixelWindowCoordinates < 1.0) { // zPixelWindowCoordinates == 1.0 this means that you probably missed the object
			// undo OpenGL viewport transformation etc etc 
			zPixelWorldCoordinates = -m_frustumFar*m_frustumNear/(m_frustumFar-m_frustumNear) / 
				(zPixelWindowCoordinates - 0.5 * (m_frustumFar+m_frustumNear)/(m_frustumFar-m_frustumNear) - 0.5);
			m_translationDepth = zPixelWorldCoordinates;
//			printf("z: %f %f\n", zPixelWindowCoordinates, zPixelWorldCoordinates);
		}
	}
	else m_translationDepth = -1.0;



//	g_state->m_clippingPlanesEnabled = clippingPlanes;
	
	return obj;
}

int glwindow::inRecentPickRange(int x, int y) {
	if (m_nbRecentPicks <= 0) return 0;
	return (m_recentPicks && 
		(fabs((double)(m_recentPicks[m_nbRecentPicks-1].x - x)) <= m_pick[2]) && 
		(fabs((double)(m_recentPicks[m_nbRecentPicks-1].y - y)) <= m_pick[3]));
}

int glwindow::pickedRecently(object *obj, int x, int y, int repeastLastPick) { 
	int i, nb;
	if (!inRecentPickRange(x, y)) {
		clearRecentPicks();
		return 0;
	}

	nb = m_nbRecentPicks - (repeastLastPick && (!m_recentPicks[m_nbRecentPicks-1].repeastLastPick));

	for (i = 0; i < nb; i++)
		if (m_recentPicks[i].obj == obj) return 1;

	return 0;
}

int glwindow::clearRecentPicks() {
	m_nbRecentPicks = 0;
	if (m_recentPicks) {
		free(m_recentPicks);
		m_recentPicks = NULL;
	}
	return 0;
}

int glwindow::addRecentPick(object *obj, int x, int y, int repeastLastPick) {
	m_recentPicks = (struct recentPick*)realloc(m_recentPicks, sizeof(struct recentPick) * (m_nbRecentPicks + 1));
	m_recentPicks[m_nbRecentPicks].obj = obj;
	m_recentPicks[m_nbRecentPicks].x = x;
	m_recentPicks[m_nbRecentPicks].y = y;
	m_recentPicks[m_nbRecentPicks].repeastLastPick = repeastLastPick;
	m_nbRecentPicks++;

	return 0;
}


void glwindow::beginglDraw() {
	if (!valid()) {
//		printf("Some OpenGL info:\nVendor: %s\nRenderer: %s\nVersion: %s\n", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
		setupViewport();
	}

#ifndef MESA
	glDrawBuffer(GL_BACK);//GL_FRONT_AND_BACK
#endif // !MESA
}


void glwindow::endglDraw() {
#ifndef MESA
	glDrawBuffer(GL_BACK);
#endif // !MESA
}

int glwindow::handle(int event) {
	static int firstx, firsty;
	static int inside; // non-zero if first press inside sphere
	static e3ga firstRot;
	static int lastx = 0;
	static int lasty = 0;
	GAIM_FLOAT motionX, motionY;
	e3ga rx, ry, rz;
	GAIM_FLOAT ax, ay;

	if ((event == FL_PUSH) || (event == FL_RELEASE) || 
		(event == FL_MOVE) || (event == FL_DRAG)) {
		gui_state->mouseMove();
	}

	// change for mouse mode 'here?
	// detect push, release, move, drag
	// if mouse mode

	switch (event) {
	case FL_FOCUS:
		return 1;
	case FL_PUSH:
		if (g_state->m_inputWait && gui_state->m_fullscreen) {
			if ((Fl::event_x() > w() - 40) && (Fl::event_y() > h() - 40)) { // todo: make this '40' a constant (in draw function as well)
				g_state->setInputWaitState(0);
				return 1;
			}
		}

		m_mousePickMode = (Fl::event_state() & FL_CTRL);
		m_mouseButtons = Fl::event_state() & (FL_BUTTON1 | FL_BUTTON2 | FL_BUTTON3);

		if (!m_mousePickMode) {
			firstx = Fl::event_x();
			firsty = Fl::event_y();
			if ( sqrt((double)((w()/2-firstx)*(w()/2-firstx)+
				 (h()/2-firsty)*(h()/2-firsty))) < 0.375*h() ) {
			  inside = 1;
			} else {
			  inside = 0;
			}
			firstRot = getCamOri();
		}
		else if (m_mouseButtons & FL_BUTTON3) { // handle translate/selection
			if (gui_state->m_interactiveMouse)
				gui_state->setCurrentObject(this->pick(Fl::event_x(), h() - Fl::event_y(), 1, 1));
		}

		return 1;
	case FL_RELEASE:

		// handle selection by button 1 or 2
		if (m_mousePickMode && (m_mouseButtons & (FL_BUTTON1 | FL_BUTTON2))) {
			gui_state->setCurrentObject(this->pick(Fl::event_x(), h() - Fl::event_y(), m_mouseButtons & FL_BUTTON2, 0));

			if (m_mouseButtons & FL_BUTTON2) {
				// todo
				if (gui_state->m_currentObject)
					gui_state->m_console->cprint(gui_state->m_currentObject->m_name.c_str(), 1);
			}
			else {
			}
			m_mousePickMode = 0;
		}
		else if (m_mousePickMode && gui_state->m_interactiveMouse && (m_translationDepth > 0.0) && (m_mouseButtons & FL_BUTTON3)) {
			if (gui_state->m_currentObject)
				gui_state->setCurrentObject(gui_state->m_currentObject);
		}

		m_translationDepth = -1.0;

		return 1;
	case FL_MOVE:
		lastx = Fl::event_x();
		lasty = Fl::event_y();
		return 1;
	case FL_DRAG:
		motionX = (float)(Fl::event_x() - firstx);
		motionY = (float)(Fl::event_y() - firsty);
		if (m_mousePickMode) {
			// Checking for damage prevents looping inside the event handler without actually redrawing the GL window.
			// Updating the dynamic statements might take quite some time (>0.1 sec).
			if ((!damage()) && (m_mouseButtons & FL_BUTTON3)) { 
				if (gui_state->m_currentObject && (m_translationDepth > 0.0)) {
					float mul = 1.0f;
					if (Fl::event_state() & FL_SHIFT)
						mul = 0.05f;

					gui_state->m_currentObject->translate(this, m_translationDepth, mul*(lastx - Fl::event_x()), mul*(lasty - Fl::event_y()));
					g_state->updateDynStmts();
				}
			}
			else break; // prevents lastx & lasty from being remembered
		}
		else {
			clearRecentPicks(); // when setOri(), setPos() are implemented, remove this call, since they should do this call

			float mul = 1.0f;
			if (Fl::event_state() & FL_SHIFT)
				mul = 0.1f;

			if (m_mouseButtons & FL_BUTTON1) {

				if ( inside ) {
					// trackball orbiter using GA
					ax = mul* -motionX / 100.0f / 2.0f;
					rx = cos(ax) + sin(ax) * ((e3ga)e3ga::e2 << (e3ga)e3ga::I);
					ay = mul* -motionY / 100.0f / 2.0f;
					ry = cos(ay) + sin(ay) * ((e3ga)e3ga::e1 << (e3ga)e3ga::I);
					setCamOri(rx * ry * firstRot);
				} 
				else {
					motionX = mul* (float)(Fl::event_x() - lastx);
					motionY = mul* (float)(Fl::event_y() - lasty);

					e3ga v1(GRADE1, motionX, -motionY, 0.0); // motion vector
					e3ga v2(GRADE1, Fl::event_x() - 0.5 * w(), -Fl::event_y() + 0.5 * h(), 0.0); // vector from window center to mouse 
					e3ga B(v1 ^ v2 / (0.3 * w() * h()));
					e3ga R(cos(B[GRADE2][E3GA_E1_E2]) + sin(fabs(B[GRADE2][E3GA_E1_E2])) * B.normal()); // R = B.exp();
					R = B.exp();
					setCamOri(R * getCamOri()); 
				}
			}
			if (m_mouseButtons & FL_BUTTON2) {
			  motionX = mul* (float)(Fl::event_x() - lastx);
			  motionY = mul* (float)(Fl::event_y() - lasty);
			  e3ga pos(getCamPos());
			  setCamPos(pos - (motionX*pos[GRADE1][E3GA_E3]/1000.0f) * e3ga::e1 + (motionY*pos[GRADE1][E3GA_E3]/1000.0f)  * e3ga::e2);
			}
			if (m_mouseButtons & FL_BUTTON3) {
				motionX = mul* (float)(Fl::event_x() - lastx);
				motionY = mul* (float)(Fl::event_y() - lasty);
				e3ga pos(getCamPos() + (motionY / 10.0f) * e3ga::e3);
				if (pos[GRADE1][E3GA_E3] < 1.0f) pos += (1.0f - pos[GRADE1][E3GA_E3]) * e3ga::e3;
				if (pos[GRADE1][E3GA_E3] > 100.0f) pos += (100.0f - pos[GRADE1][E3GA_E3]) * e3ga::e3;
				setCamPos(pos);
			}
			redraw();
		}
		lastx = Fl::event_x();
		lasty = Fl::event_y();
		return 1;
	default:
		return Fl_Gl_Window::handle(event);
	}
	return 0;
}

void glwindow::pushTransform() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void glwindow::popTransform() {
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void glwindow::setupEyeTransform() {
	// set the transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	m_pos.print("pos: ");
	e3ga pos(getCamPos());
	const GAIM_FLOAT *c = pos[GRADE1];
	glTranslated(-c[0], -c[1], -c[2]);
	float rotM[16];
	e3ga R(getCamOri());
	e3gaRotorToOpenGLMatrix(R, rotM);
	glMultMatrixf(rotM);
}

/*void glwindow::setupClippingPlanes() {
	int i;
	GLdouble eq[6][4] = {
		{1.0, 0.0, 0.0, g_state->m_clipDistance},
		{-1.0, 0.0, 0.0, g_state->m_clipDistance},
		{0.0, 1.0, 0.0, g_state->m_clipDistance},
		{0.0, -1.0, 0.0, g_state->m_clipDistance},
		{0.0, 0.0, 1.0,  g_state->m_clipDistance},
		{0.0, 0.0, -1.0, g_state->m_clipDistance}
	};
	for (i = 0; i < 6; i++)
		glClipPlane(GL_CLIP_PLANE0 + i, eq[i]);
}

void glwindow::enableClippingPlanes() {
	int i;
	if (!g_state->m_clippingPlanesEnabled) disableClippingPlanes();
	else for (i = 0; i < 6; i++) glEnable(GL_CLIP_PLANE0 + i);
}

void glwindow::disableClippingPlanes() {
	int i;
	for (i = 0; i < 6; i++)
		glDisable(GL_CLIP_PLANE0 + i);
}*/


int glwindow::vectorAtDepth(double depth, double vx, double vy, e3ga &v) {
	if ((m_frustumWidth <= 0) || (m_frustumHeight <= 0) ||
		(m_frustumNear <= 0) || (m_frustumFar <= 0)) {
		v = 0;
		return -1;
	}

	e3ga tmp((depth * (double)vx * m_frustumWidth) / (w() * m_frustumNear) * e3ga::e1 + 
		(depth * (double)vy * m_frustumHeight) / (h() * m_frustumNear) * e3ga::e2);


	e3ga R(getCamOri());
	v = (R.inverse() * tmp * R)(GRADE1);

	return 0;
}

void glwindow::setup3DProjection() {
	GLsizei width, height, vpw, vph;

	double ScreenSize = 1200;

	if (m_screenShotActive) {
		width = gui_state->m_ssWidth;
		height = gui_state->m_ssHeight;
		vpw = m_ssViewportWidth;
		vph = m_ssViewportHeight;
		ScreenSize = ScreenSize * sqrt((double)(width * height) / (double)(w() * h()));
	}
	else {
		vpw = width = w();
		vph = height = h();
		m_ssStartX = m_ssStartY = 0.0;
		m_ssEndX = m_ssEndY = 1.0;

	}

	if ((width == 0) || (height == 0)) return;

	glViewport(0, 0, vpw, vph);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if ((m_pick[0] >= 0) && (m_pick[1] >= 0)) { 
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix(m_pick[0], m_pick[1], m_pick[2] * 2 + 1, m_pick[3] * 2 + 1, viewport);
	}

	m_frustumNear = m_defaultFrustumNear;
	m_frustumFar = m_defaultFrustumFar;
	m_frustumWidth = m_frustumNear * width / ScreenSize;
	m_frustumHeight = m_frustumNear * height / ScreenSize;

	glFrustum(
		(GLdouble)-0.5 * m_frustumWidth + m_ssStartX * m_frustumWidth, 
		(GLdouble)-0.5 * m_frustumWidth + m_ssEndX * m_frustumWidth, 
		(GLdouble)-0.5 * m_frustumHeight + m_ssStartY * m_frustumHeight, 
		(GLdouble)-0.5 * m_frustumHeight + m_ssEndY * m_frustumHeight, 
		m_frustumNear, m_frustumFar);

	glMatrixMode(GL_MODELVIEW);
}



void glwindow::setup2DOrtho() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if ((m_pick[0] >= 0) && (m_pick[1] >= 0)) { 
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix(m_pick[0], m_pick[1], m_pick[2] * 2 + 1, m_pick[3] * 2 + 1, viewport);
	}

	GLsizei width, height, vpw, vph;

	if (m_screenShotActive) {
		width = gui_state->m_ssWidth;
		height = gui_state->m_ssHeight;
		vpw = m_ssViewportWidth;
		vph = m_ssViewportHeight;
	}
	else {
		vpw = width = w();
		vph = height = h();
		m_ssStartX = m_ssStartY = 0.0;
		m_ssEndX = m_ssEndY = 1.0;

	}

	glOrtho(0 + m_ssStartX * width, 0 + m_ssEndX * width, 
		0 + m_ssStartY * height, 0 + m_ssEndY * height, 
		1.0, 100.0);

	m_frustumWidth = m_frustumHeight = -1.0;
	m_frustumNear = m_frustumFar = -1.0;

	glMatrixMode(GL_MODELVIEW);
}

void glwindow::setupViewport() {

	// projection constant = near * viewportsize/screensize
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	setup3DProjection();

	// set standard opengl stuff
	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);
}

GLdouble glwindow::getRenderWidth() {
	return (m_screenShotActive) ? gui_state->m_ssWidth : w();
}

GLdouble glwindow::getRenderHeight() {
	return (m_screenShotActive) ? gui_state->m_ssHeight : h();
}
