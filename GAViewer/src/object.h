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

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "gl_includes.h"

#ifdef WIN32
#pragma warning( disable : 4311 4312 4244 )
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string>

// object types
#define OT_NOTHING 0
#define OT_TEXT 1 
#define OT_E3GA 2
#define OT_P3GA 3
#define OT_C3GA 4
#define OT_POLYGON 5
#define OT_MESH 6
#define OT_I2GA 7
#define OT_C5GA 8
// more to come

#include "gaincludes.h"

#include "mvint.h"

/*
!
When adding or changing properties below, always consider
if writestate.cpp should be adjusted correspondingly.
!
*/

class state;
class glwindow;
struct Fl_Menu_Item;

// Object Properties
#define OP_FGCOLOR (1 << 0)
#define OP_BGCOLOR (1 << 1)
#define OP_OLCOLOR (1 << 2)
#define OP_FONTSIZE (1 << 3)
#define OP_NAME (1 << 4)
#define OP_DESCRIPTION (1 << 5)
#define OP_DRAWMODE (1 << 6)
#define OP_DRAWMETHOD (1 << 7)
#define OP_HIDE (1 << 8)
// more to come...

// object draw instruction
#define OD_STIPPLE (1 << 0)
#define OD_ORI (1 << 1)  // normals and the like
#define OD_WIREFRAME (1 << 3)
#define OD_SHADE (1 << 4)
#define OD_MAGNITUDE (1 << 5)
#define OD_HIDE (1 << 6)
#define OD_OUTLINE (1 << 7)
#define OD_HIDE_ALWAYS (1 << 8) // will not even be shown by select/hide window
#define OD_MUTE (1 << 9)
// more to come...

// object force  flags (used in object::copy)
#define OFF_STIPPLE OD_STIPPLE
#define OFF_ORI OD_ORI
#define OFF_WIREFRAME OD_WIREFRAME
#define OFF_SHADE OD_SHADE
#define OFF_MAGNITUDE OD_MAGNITUDE
#define OFF_HIDE OD_HIDE
#define OFF_OUTLINE OD_OUTLINE
#define OFF_MUTE OD_MUTE

#define OFF_COLOR (1 << 15)
#define OFF_ALPHA (1 << 16)
#define OFF_DRAWMETHOD (1 << 17)

// object creation instruction
#define OC_GRADE0 (1 << 0) // force grade X interpretation
#define OC_GRADE1 (1 << 1) // force grade X interpretation
#define OC_GRADE2 (1 << 2) // force grade X interpretation
#define OC_GRADE3 (1 << 3) // force grade X interpretation
#define OC_GRADE4 (1 << 4) // force grade X interpretation
#define OC_GRADE5 (1 << 5) // force grade X interpretation
#define OC_GRADE6 (1 << 6) // force grade X interpretation
#define OC_GRADE7 (1 << 7) // force grade X interpretation
#define OC_GRADE8 (1 << 8) // force grade X interpretation
#define OC_VERSOR (1 << 9) // force versor interpretation
#define OC_BLADE (1 << 10) // force blade interpretation
#define OC_DYNAMIC (1 << 11) // dynamic object (changes if any of it's components change, currrently only the polygon object)
#define OC_COMPUTE_NORMALS_FLAT (1 << 12) // flat shaded mesh (normals automatically computed for each polygon)
#define OC_COMPUTE_NORMALS_GOURAUD (1 << 13) // gouraud shaded mesh (normals automatically computed for each vertex)
#define OC_SPECIFY_NORMALS (1 << 14) // normals specified for each vertex or polygon
//#define OC_RETAIN_DRAW_PROPERTIES_ON_COPY (1 << 15) //  keep color, fontsize, drawmode on copy
// todo: force 'dual' interpretation?

#define OC_FLAT_SHADED (1 << 16) // flat shaded mesh

#define OC_DMBASE 12
#define OC_DM1 (1 << OC_DMBASE) // draw method 1
#define OC_DM2 (2 << OC_DMBASE) // draw method 2
#define OC_DM3 (3 << OC_DMBASE) // draw method 3
#define OC_DM4 (4 << OC_DMBASE) // draw method 4
#define OC_DM5 (5 << OC_DMBASE) // draw method 5
#define OC_DM6 (6 << OC_DMBASE) // draw method 6
#define OC_DM7 (7 << OC_DMBASE) // draw method 7
// more to come...


#define LABEL_2D (1 << 0) // label coordinates are in 2D window coordinates
#define LABEL_3D (1 << 1) // label coordinates are in 3D world coordinates
#define LABEL_CX (1 << 2) // x-axis origin is in center of window (only in combination with 2D)
#define LABEL_CY (1 << 3) // y-axis origin is in center of window (only in combination with 2D)
#define LABEL_PX (1 << 4) // positive x axis is in towards the right (only in combination with 2D)
#define LABEL_NX (1 << 5) // positive x axis is in towards the left (only in combination with 2D)
#define LABEL_PY (1 << 6) // positive y axis is in towards the bottom (only in combination with 2D)
#define LABEL_NY (1 << 7) // positive y axis is in towards the top (only in combination with 2D)
#define LABEL_ACX (1 << 8) // the label is aligned in the center of the window (overrides all other commands related to the 'X'-axis)
#define LABEL_DYNAMIC (1 << 9) // the label point will follow the original point
#define LABEL_IMAGE (1 << 10) // the label is an image
#define LABEL_FULLSCREEN (1 << 11) // (only in combination with LABEL_IMAGE) scales the image to fullscreen, ignoring fontsize
#define LABEL_WIDTH (1 << 12) // label width set explicity. For images, the image height scales uniformly. Text is typeset to fit within the width
// more to come...

#define FADE_NO_FADE -1
#define FADE_NOTHING 0
#define FADE_HIDE 1
#define FADE_REMOVE 2

class removeObjectException {
public:
	removeObjectException() {};
	~removeObjectException() {};
};

class object {
public:
	object(int type, const std::string &name = NULL, int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~object();
	void initToNothing();

	std::string m_name;
	int m_type; // OT_XXX

	virtual int pick(glwindow *window) = 0;
	virtual int draw(glwindow *window) = 0;
	virtual float drawSortValue() = 0;
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlag = -1);
	virtual int update(double currentTime);
	virtual int setFontSize(float size);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");

	int hide();
	int show();
	int toggleHide();

	int copyColors(const object *o);
	int copyAlphas(const object *o);

// other properties:
	float m_fontSize; // height of font in pixels
	int m_drawMode; // a bitwise or of OD_XXX value
	float m_poFactor, m_poUnits; // polygon offset

	// fading stuff
	int setFade(double duration, float target, int action, float startFadeFactor = -1.0);
	double m_fadeStartTime, m_fadeEndTime;
	float m_fadeCurrentFactor; // all alpha is multiplied with this
	float m_fadeStartFactor; 
	float m_fadeEndFactor; 
	int m_fadeAction; // action to perform after fade is done (FADE_XXX)



	inline int hidden() {
		return (((m_drawMode & OD_HIDE) != 0) && (!(m_drawMode & OD_HIDE_ALWAYS)));
	};

	// returns the first point from the mv interpretation (if this is a multivector object)
	const GAIM_FLOAT *getPoint(int idx);
	const GAIM_FLOAT *getNormal(int idx);

	Fl_Menu_Item *m_dmMenu;
	int m_dmMenuIdx;

	// Bitwise 'or' of OP_XXX values that are relevant to this object (is set by subclass).
	// This is used by the UI to hide and show the appropriate widgets
	int m_properties; 

	// set the color
	void setFgColor(const float c[4]);
	void setBgColor(const float c[4]);
	void setOlColor(const float c[4]);
	void setFgColor(const double c[4]);
	void setBgColor(const double c[4]);
	void setOlColor(const double c[4]);
	void setFgAlpha(float alpha);
	void setBgAlpha(float alpha);
	void setOlAlpha(float alpha);

	// set OpenGL color
	void setFgColor();
	void setBgColor();
	void setOlColor();

	// retrieve a component [0 .. 3] from a color
	float fgColor(int idx);
	float bgColor(int idx);
	float olColor(int idx);

	// retrieve pointer to color
	const float *fgColor() const;
	const float *bgColor() const;
	const float *olColor() const;

	static int m_objectCount;

	// this function gets called when the text scale has changed
	virtual void textScaleChanged();
protected:
	// these functions get called when the color (or alpha) has changed
	virtual void colorFgChanged();
	virtual void colorBgChanged();
	virtual void colorOlChanged();


	// display list
	GLuint m_displayList;
	int allocDisplayList();
	int freeDisplayList();

	int writeToGeoFileProperties(FILE *F);

//	int m_retainDrawPropertiesOnCopy; // true or false

private:
	float m_fgColor[4]; // foreground color rgba [0.0, 1.0]
	float m_bgColor[4]; // background color rgba [0.0, 1.0]
	float m_olColor[4];  // outline color rgba [0.0, 1.0]

};

class e3gaObject : public object {
public:
	e3gaObject(const e3ga &mv, const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~e3gaObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");


	e3ga m_mv;
	mvInt m_int;
};

class p3gaObject : public object {
public:
	p3gaObject(const p3ga &mv, const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~p3gaObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");

	p3ga m_mv;
	mvInt m_int;
};

class conformalObject : public object {
public:
	conformalObject(int type, const std::string &name = NULL, int drawMode = 0, int creationFlags = 0, int forceFlags = 0) : 
		object(type, name, drawMode, creationFlags, forceFlags) {}
	virtual ~conformalObject() {}
	virtual int draw(glwindow *window);

	/// shared description between c3ga and c5ga
	int description(const c3ga &mv, int dim, char *buf, int bufLen, int sl);

	mvInt m_int;
};


class c3gaObject : public conformalObject {
public:
	c3gaObject(const c3ga &mv, const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~c3gaObject();
	void initToNothing();

	virtual int pick(glwindow *window);
//	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");

	c3ga m_mv;
};

class c5gaObject : public conformalObject {
public:
	c5gaObject(const c5ga &mv, const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~c5gaObject();
	void initToNothing();

	virtual int pick(glwindow *window);
//	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");

	c5ga m_mv;
};

class i2gaObject : public object {
public:
	i2gaObject(const i2ga &mv, const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0, int forceFlags = 0);
	virtual ~i2gaObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);
	virtual int translate(glwindow *window, double depth, double motionX, double motionY);
	virtual std::string toString(const char *floatPrec = "%e");

	i2ga m_mv;
	mvInt m_int;
};

class textObject : public object {
public:
	textObject(const char *text, const e3ga &pos, const std::string &name = std::string(""), int creationFlags = 0, int labelFlags = 0, int width = -1);
	textObject(const char *text, const std::string &pointName, const std::string &name = std::string(""), int creationFlags = 0, int labelFlags = 0, int width = -1);
	virtual ~textObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int setFontSize(float size);
	virtual int writeToGeoFile(FILE *F);

	virtual int translate(glwindow *window, double depth, double motionX, double motionY);

	char *m_text;
	std::string m_pointName;
	e3ga m_pos;
	int m_flags;

protected:
	// Computes the window coordinates where the text should be drawn.
	// This means: apply the OpenGL modelview, projection and viewport operations
	// Return '1' if the text is not clipped. Window coordinates are returned in 'x' and 'y'
	// 'z' is the depth value
//	int windowCoordinates(double &x, double &y, double &z);
	int windowCoordinates(const double ptWorld[3], double ptWindow[3]);

	// returns the length of a unit vector in the x and y direction in window coordinates
	int wcUnitXY(double &ux, double &uy);

	/*
	During the 'draw()' function, the coordinates where this text is drawn are stored.
	This info is required during the 'pick()' function. This is because the labels act
	weirdly. They are drawn as 2D object, but move like 3D objects (they always
	stay the same size, even though they are 'tied' to a 3D point in space).
	*/
	double m_dc[3]; // drawing coordinates

	/*
	During the 'draw()' function, this info is stored.
	This info is required during the 'pick()' function. This is because some
	of this info is different during the pick() function but we _do_ want
	to draw exactly as in the draw() function.
	*/
	double m_mvMatrix[16];
	double m_pjMatrix[16];
	double m_viewport[4];

	double m_width, m_height; // width and height (determined on first draw when fresh text is delivered)
	int m_userWidth; // width specified by user (valid only if LABEL_WIDTH is set)

	const char *m_tsMode; // verbatim, text or equation
	const char *m_tsFont; // regular, bold, italic or greek

	int initImage();
	int freeImage();
	int m_imageWidth, m_imageHeight;
	int m_textureWidth, m_textureHeight;
    GLuint m_textureName;

	//unsigned char *m_imagePixels;

	// this function gets called when the text scale has changed
	virtual void textScaleChanged();

protected:
	// these functions get called when the color (or alpha) has changed
	virtual void colorFgChanged();
	virtual void colorBgChanged();
	virtual void colorOlChanged();

};

/*
For now, polygonObjects should be flat and convex.
Todo: maybe add tesselation using GLU
*/
class polygonObject : public object {
public:
	polygonObject(const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0);
	virtual ~polygonObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);

	int setSimplex(int simplex);

	int drawSimplex(glwindow *window);
	int drawPolygon(glwindow *window);

	int freeAllVertices(); 
	int addVertex(const char *name);
	const GAIM_FLOAT *getVertex(int idx);
	int m_nbVertices;
	char **m_vertexName; // name of vertex 'idx'
	GAIM_FLOAT *m_vertex; // coordinates of vertex 'idx'
	
	/*
	If a polygon is dynamic, the coordinates of the vertices will be
	retrieved from the objects each time the polygon is drawn.
	*/
	int m_mode; // dynamic (OC_DYNAMIC) or static (0)

	int m_simplex; // if true, this object is drawn as a simplex (max vertices = 3)
};

/*
*/
class meshObject : public object {
public:
	meshObject(const std::string &name = std::string(""), int drawMode = 0, int creationFlags = 0);
	virtual ~meshObject();
	void initToNothing();

	virtual int pick(glwindow *window);
	virtual int draw(glwindow *window);
	virtual float drawSortValue();
	virtual int description(char *buf, int bufLen, int sl = 0); // if sl is true, return Single Line description
	virtual int copy(const object *o, int &propertiesChanged, int forceFlags = -1);
	virtual int writeToGeoFile(FILE *F);


	// temporary hack...
/*	int drawParaboloid(glwindow *window); //(change to 'create paraboloid)
	int createParaboloid(); //(change to 'create paraboloid)*/

	// vertices & faces
	int setVertexPos(int idx, const GAIM_FLOAT p[3]);
	int setVertexNormal(int idx, const GAIM_FLOAT n[3]);
	int setVertexPos(int idx, const char *name);
	int setVertexNormal(int idx, const char *name);
	int addFace(int nbVtx, const int *vtxIdx);


protected:
	// vertices & faces
	int m_normalsValid; // if false, normals must be recomputed
	int m_faceType; // a number >= 3 if all faces have the same number of vertices
	int meshChanged(); // invalidates normals, frees display list

	int m_nbVertices, m_maxVertices;
	struct vertex {
		GAIM_FLOAT pos[3]; // static position
		GAIM_FLOAT nl[3]; // static or computed normal
		char *posName; // dynamic position
		char *nlName; // dynamic normal
	} *m_vertex;

	int m_nbFaces, m_maxFaces;
	struct face {
		int nbVtx;
		int *vtxIdx;
		GAIM_FLOAT nl[3]; // flat shaded normal
	} *m_face;

	int ensureFaces(int nbFaces);
	int ensureVertices(int nbVertices);
	int freeFaces();
	int freeVertices();
	int computeNormals(state *s);

	int drawMesh(state *s);


	const GAIM_FLOAT *getVertexPos(const char *name);
	const GAIM_FLOAT *getVertexNormal(const char *name);
/*
	int freeAllVertices(); 
	int addVertex(const char *name);
	const GAIM_FLOAT *getVertex(int idx);
	int m_nbVertices;
	char **m_vertexName; // name of vertex 'idx'
	GAIM_FLOAT *m_vertex; // coordinates of vertex 'idx'
*/	
	int m_mode; // dynamic (OC_DYNAMIC) or static (0)
};


#endif /* _OBJECT_H_ */
