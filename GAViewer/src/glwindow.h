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

#ifndef _GLWINDOW_H_
#define _GLWINDOW_H_

#ifdef WIN32
#pragma warning( disable : 4311 4312 4244 )
#endif

#include "gl_includes.h"

#include <FL/Fl_Gl_Window.H>

#include "gaincludes.h"

class object;

class glwindow : public Fl_Gl_Window {
public:
	glwindow(int X, int Y, int W, int H, const char *L);
	~glwindow();

	void initToNothing();


	virtual void draw();
	virtual int handle(int);

	void drawScene();

	// position & orientation of camera (todo: create functions that to set these variables; these functions should call clearRecentPicks());
	e3ga m_posI;
	e3ga m_oriI;
	e3ga &getCamOri();
	void setCamOri(const e3ga &R);
	e3ga &getCamPos();
	void setCamPos(const e3ga &t);


	void beginglDraw();
	void endglDraw();

	void setupViewport();
	void setup3DProjection();
	void setup2DOrtho();
	void setupEyeTransform();

/*	void setupClippingPlanes();
	void enableClippingPlanes();
	void disableClippingPlanes();*/

	/// sets m_defaultFrustumNear and m_defaultFrustumFar
	/// If insensible values are provided (zero, negative, or near > far), resets to default
	void setNearFarClipPlanes(double near, double far);

	void pushTransform();
	void popTransform();

	// returns the object at pixel [x, y]; loops thorugh all objects at that location if mouse location is the same in consecutive clicks
	object *pick(int x, int y, int repeastLastPick, int storeTranslationZ); // if repeastLastPick is true, the last pick will be repeated (even if it's at the same [x, y])

	// if no all set to -1, object picking (GL_SELECT) is active
	// The first two coordinates are x and y of the cursor
	// The next two are the area the picking should extend to (use 0,0 for the cursor pixel only)
	int m_pick[4], m_mousePickMode; 

	// these array/function are used to cycle through all objects at a specific location
	int m_nbRecentPicks;
	struct recentPick {
		int x, y, repeastLastPick;
		object *obj;
	} *m_recentPicks;
	int inRecentPickRange(int x, int y);
	int pickedRecently(object *obj, int x, int y, int repeastLastPick);
	int clearRecentPicks();
	int addRecentPick(object *obj, int x, int y, int repeastLastPick);

	// used to force transparent objects to render into the depth buffer
	inline int depthMaskAllowedOff() {return m_depthMaskAllowedOff; };
	int m_depthMaskAllowedOff;

	int m_mouseButtons; // mouse button state at the time of the last 'push'

	/// used as the default values when glFrustum is called
	double m_defaultFrustumNear, m_defaultFrustumFar;


	double m_translationDepth; // the depth at which the last translate selection was done
	double m_frustumWidth, m_frustumHeight, m_frustumNear, m_frustumFar; // set every time glFrustum is called
	int vectorAtDepth(double depth, double vx, double vy, e3ga &v);

	// screenshot
	int performScreenShot();
	bool m_screenShotActive;
	int m_ssViewportWidth, m_ssViewportHeight;
	double m_ssStartX, m_ssEndX;
	double m_ssStartY, m_ssEndY;

	// viewport & width height info for text object
//	void getRenderViewport(GLdouble vp[4]);
	GLdouble getRenderWidth();
	GLdouble getRenderHeight();


};

#endif /* _GLWINDOW_H_ */
