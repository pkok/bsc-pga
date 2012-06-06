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


#include "uistate.h"
#include "object.h"
#include "glwindow.h"
#include "typeset/openglfont.h"
#include "util.h"
#include "state.h"
#include "typeset/typeset.h"
#include "pngwrapper.h"

// constructor for fixed position
textObject::textObject(const char *text, const e3ga &pos, const std::string &name /*= std::string("")*/, int creationFlags /*= 0*/, int labelFlags /*= 0*/, int width /* = -1*/) : object(OT_TEXT, name, creationFlags) {
	initToNothing();
	m_text = strdup(text);
	m_userWidth = width;
	m_pos = pos;

	m_properties = OP_HIDE | OP_FGCOLOR | OP_BGCOLOR | OP_OLCOLOR | OP_FONTSIZE | OP_NAME | OP_DESCRIPTION;

	m_flags = labelFlags ^ (labelFlags & LABEL_DYNAMIC); // force dynamic off
	m_tsMode = g_state->m_tsMode;
	m_tsFont = g_state->m_tsFont;

	if (m_flags & LABEL_IMAGE)
		initImage();

}

// constructor for fixed/dynamic position
textObject::textObject(const char *text, const std::string &pointName, const std::string &name /*= std::string("")*/, int creationFlags /*= 0*/, int labelFlags /*= 0*/, int width /* = -1*/) : object(OT_TEXT, name, creationFlags) {
	initToNothing();
	m_text = strdup(text);
	m_userWidth = width;

	m_properties = OP_FGCOLOR | OP_BGCOLOR | OP_OLCOLOR | OP_FONTSIZE | OP_NAME | OP_DESCRIPTION;
	m_flags = labelFlags;

	if (m_flags & LABEL_DYNAMIC) {
		m_pointName = pointName;
	}
	else {
		object *o = g_state->getObjectPtrByName(pointName);
		const GAIM_FLOAT *pos = o->getPoint(0), null[3] = {0.0, 0.0, 0.0};
		m_pos.setVector((pos) ? pos : null);
	}

	m_tsMode = g_state->m_tsMode;
	m_tsFont = g_state->m_tsFont;

	if (m_flags & LABEL_IMAGE)
		initImage();

}

textObject::~textObject() {
	if (m_text) free(m_text);
//	if (m_pointName) free(m_pointName);
	//if (m_imagePixels) free(m_imagePixels);

	freeImage();

	initToNothing();
}

void textObject::initToNothing() {
	m_text = NULL;
	m_pos = 0;
	m_flags = 0;
//	m_pointName = NULL;

	m_width = m_height = 0.0;

	m_tsMode = NULL;
	m_tsFont = NULL;

	m_imageWidth = m_imageHeight = -1;
	m_textureWidth = m_textureHeight = -1;
	m_textureName = GL_INVALID_TEXTURE_NAME;
	//m_imagePixels = NULL;

}

int textObject::initImage() {
	int err, y, x;
	// in image mode, foreground color can not be controlled // todo????
	//m_properties = m_properties ^ (m_properties & OP_FGCOLOR);

	// set OpenGL context
	gui_state->m_glWindow->make_current(); 

	// clear OpenGL error
	if ( (err = glGetError()) != GL_NO_ERROR) {
		cprintf("textObject::initImage(): Warning: OpenGL error '%s' (%d) detected (at function entry)\n", gluErrorString(err), err);
	}

	// load image
	unsigned char *pixels = NULL;
	if ( (err = loadPNG(m_text, &pixels , &m_imageWidth, &m_imageHeight, 0)) != 0) {
		cprintf("textObject::initImage(): could not load image '%s'\n", m_text);

		freeImage();
		m_tsMode = "verbatim";
		m_flags = m_flags ^ (m_flags & LABEL_IMAGE);
		return 0;
	}

	// check texture size
	GLint maxTexSize = 0;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTexSize);
	if ((m_imageWidth > maxTexSize) || (m_imageHeight > maxTexSize)) {
		cprintf("textObject::initImage(): image too large (%d x %d) to fit into OpenGL texture (max %d x %d)\n", 
			m_imageWidth, m_imageHeight, maxTexSize, maxTexSize);

		free(pixels);
		freeImage();
		m_tsMode = "verbatim";
		m_flags = m_flags ^ (m_flags & LABEL_IMAGE);
		return 0;
	}

	// compute nearest width/height of a power of 2
	m_textureWidth = (int)(pow(2.0, ceil(log((double)m_imageWidth) / log(2.0))) + 0.1); // +0.1 to compensate for fp round off
	m_textureHeight = (int)(pow(2.0, ceil(log((double)m_imageHeight) / log(2.0))) + 0.1); // +0.1 to compensate for fp round off
//	printf("Width: %d -> %d\nHeight: %d -> %d\n", m_imageWidth, m_textureWidth, m_imageHeight, m_textureHeight);

	// pad image with blanks to make its width/height be a power of 2
	pixels = (unsigned char *)realloc(pixels, m_textureWidth * m_textureHeight * 3);
	for (y = m_imageHeight - 1; y >= 0; y--) {
		memmove(pixels + y * m_textureWidth * 3, pixels + y * m_imageWidth * 3, m_imageWidth * 3); // move the row
		for (x = m_imageWidth; x < m_textureWidth; x++) { // clamp horizontal
			pixels[(y * m_textureWidth + x) * 3 + 0] = pixels[(y * m_textureWidth + m_imageWidth-1) * 3 + 0];
			pixels[(y * m_textureWidth + x) * 3 + 1] = pixels[(y * m_textureWidth + m_imageWidth-1) * 3 + 1];
			pixels[(y * m_textureWidth + x) * 3 + 2] = pixels[(y * m_textureWidth + m_imageWidth-1) * 3 + 2];
		}
	}
	for (y = m_imageHeight; y < m_textureHeight; y++) // clamp vertical
		memcpy(pixels + y * m_textureWidth * 3, pixels + (m_imageHeight-1) * m_textureWidth * 3, m_textureWidth * 3);

    // create opengl texture
    glGenTextures(1, &m_textureName);
    glBindTexture(GL_TEXTURE_2D, m_textureName);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// no mip mapping required; these images are display at approx. the native size
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_textureWidth, m_textureHeight, 0,
            GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// check OpenGL error
	if ( (err = glGetError()) != GL_NO_ERROR) {
		cprintf("textObject::initImage(): Warning: OpenGL error '%s' (%d) detected (at function exit)\n", gluErrorString(err), err);
	}

	// free resources
	free(pixels);

	return 0;
}

int textObject::freeImage() {
	if (m_textureName != GL_INVALID_TEXTURE_NAME) {
		// make OpenGL context valid
		gui_state->m_glWindow->make_current(); 
		// delete the texture
		glDeleteTextures(1, &m_textureName);
	}
	m_textureName = GL_INVALID_TEXTURE_NAME;
	m_imageWidth = m_imageHeight = -1;
	m_textureWidth = m_textureHeight = -1;
	return 0;
}

int textObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;

	// free displaylist, texture
	freeDisplayList();
	freeImage();

	// copy properties
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const textObject *textO = (const textObject *)o;
	if (strcmp(m_text, textO->m_text)) {
		free(m_text);
		m_text = strdup(textO->m_text);
		propertiesChanged |= OP_DESCRIPTION;
	}
	m_pos = textO->m_pos;
	m_flags = textO->m_flags;

	m_tsMode = textO->m_tsMode;
	m_tsFont = textO->m_tsFont;

	// if required, init image
	if (m_flags & LABEL_IMAGE) initImage();

	return 0;
}


int textObject::setFontSize(float size) {
	// free displaylist
	freeDisplayList();

	return object::setFontSize(size);
}

// this function simulates the 3D->2D window transformation of OpenGL
int textObject::windowCoordinates(const double ptWorld[3], double ptWindow[2]) {
	double pt1[4], pt2[4];
	pt1[0] = ptWorld[0]; pt1[1] = ptWorld[1]; pt1[2] = ptWorld[2]; pt1[3] = 1;
	GLmatrixVectorMul(m_mvMatrix, pt1, pt2);
	GLmatrixVectorMul(m_pjMatrix, pt2, pt1);
	ptWindow[0] = (pt1[0] / pt1[3] + 1.0) * m_viewport[2] / 2.0 + m_viewport[0];
	ptWindow[1] = (pt1[1] / pt1[3] + 1.0) * m_viewport[3] / 2.0 + m_viewport[1];

	return 0;
}

int textObject::wcUnitXY(double &ux, double &uy) {
	double pt[4], c[3][2];
	pt[0] = pt[1] = pt[2] = 0.0; pt[3] = 1.0;
	windowCoordinates(pt, c[0]);
	pt[0] = m_mvMatrix[0 * 4 + 0]; pt[1] = m_mvMatrix[1 * 4 + 0];
	pt[2] = m_mvMatrix[2 * 4 + 0]; pt[3] = 1.0;
	windowCoordinates(pt, c[1]);
	pt[0] = m_mvMatrix[0 * 4 + 1]; pt[1] = m_mvMatrix[1 * 4 + 1];
	pt[2] = m_mvMatrix[2 * 4 + 1]; pt[3] = 1.0;
	windowCoordinates(pt, c[2]);
	ux = 1.0 / (c[1][0] - c[0][0]);
	uy = 1.0 / (c[2][1] - c[0][1]);
	return 0;
}

int textObject::draw(glwindow *window) {
	int err;

	double textScale = gui_state->m_textScale;

	// setup text:
	if (m_flags & LABEL_IMAGE) { // image
		if (m_flags & LABEL_FULLSCREEN) {
			textScale = 1.0;

			if ((m_width != window->getRenderWidth()) ||
				(m_height != window->getRenderHeight())) {
				freeDisplayList();
			}
			m_width = window->getRenderWidth();
			m_height = window->getRenderHeight();
		}
		else if (m_flags & LABEL_WIDTH) {
			m_width = m_userWidth;
			m_height = m_userWidth * m_imageHeight / m_imageWidth;
		}
		else {
			m_width = m_imageWidth * m_fontSize;
			m_height = m_imageHeight * m_fontSize;
		}
	}
	else if ((m_tsMode == NULL) || (m_tsMode[0] == 'v') || (m_tsMode[0] == 'V')) { // plain direct use of font
		m_width = m_fontSize * oglfprintfWidth(m_text);
		m_height = m_fontSize;
	}
	else { // typeset
		if (m_displayList == GL_INVALID_DISPLAY_LIST) {
			typesetState *tss = g_state->m_typesetState;
			if ( (err = tss->setInitialMode(m_tsMode)) != 0) return 0;
			if ( (err = tss->setInitialFont(m_tsFont)) != 0)  return 0;
			tss->setInitialSize(m_fontSize);
			tss->setColor("current", fgColor(0), fgColor(1), fgColor(2));
			tss->setAlpha(fgColor(3));
			if ( (err = tss->setInitialColor(tss->getColor("current"))) != 0)  return 0;
			if (m_flags & LABEL_WIDTH)
				err = tss->typeset(m_text, m_userWidth);
			else err = tss->typeset(m_text, -1);

			if (err) return 0;
//			if (err = tss->typeset("1 + 2", -1)) return 0;

			m_width = (int)ceil(tss->m_width);
			m_height = (int)ceil(tss->m_height);
			//printf("%f x %f\n", m_width, m_height);
		}
	}

	// dpi here: scale up m_width, m_height according to DPI?
	// this is done such that translation is set correctly
	m_width *= textScale;
	m_height *= textScale;

//	window->disableClippingPlanes();
	glDisable(GL_LIGHTING);
	glDisable(GL_POLYGON_STIPPLE);
	glDisable(GL_LINE_STIPPLE);

	if (m_flags & LABEL_DYNAMIC)  {
		object *o = g_state->getObjectPtrByName(m_pointName);
		const GAIM_FLOAT *pos = o->getPoint(0), null[3] = {0.0, 0.0, 0.0};
		m_pos.setVector((pos) ? pos : null);
	}

	GLfloat lineWidth;
	glGetFloatv(GL_LINE_WIDTH, &lineWidth);
	glLineWidth(1.0 * textScale); // dpi scale here!!! (linewidth doesn't glScale())

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	if (!(m_flags & LABEL_2D))  {
		glTranslated(m_pos[GRADE1][0], m_pos[GRADE1][1], m_pos[GRADE1][2]);
	}

	// store info in member variables; this info is reused during the pick() function
	glGetDoublev(GL_MODELVIEW_MATRIX, m_mvMatrix);
	// We just don't care about rotation-> we want 'world x axis' to be aligned with 'window x axis' 
	// (so don't do anything funny with projection or viewport...)
	m_mvMatrix[0 * 4 + 1] = m_mvMatrix[0 * 4 + 2] = 
	m_mvMatrix[1 * 4 + 0] = m_mvMatrix[1 * 4 + 2] = 
	m_mvMatrix[2 * 4 + 0] = m_mvMatrix[2 * 4 + 1] = 0.0;
	m_mvMatrix[0 * 4 + 0] = m_mvMatrix[1 * 4 + 1] = m_mvMatrix[2 * 4 + 2] = 1.0;

	if ((m_flags & LABEL_2D)) { // get rid of translation
		m_mvMatrix[3 * 4 + 0] = m_mvMatrix[3 * 4 + 1] = 0.0;
		m_mvMatrix[3 * 4 + 2] = -1.0;
	}

	glLoadMatrixd(m_mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, m_pjMatrix);
	glGetDoublev(GL_VIEWPORT, m_viewport);

	double ux, uy;
	wcUnitXY(ux, uy);
	glScaled(ux, uy, 1.0);
	
	if (m_flags & LABEL_2D) {
		// handle all the flags:
		glMatrixMode(GL_MODELVIEW);

		// first for the x-axis
		if (m_flags & LABEL_ACX) {
			glTranslatef(-(float)m_width / 2, 0.0f, 0.0f);
		}
		else {
			if (m_flags & LABEL_CX);// glTranslatef((float)window->getRenderWidth() / 2, 0.0f, 0.0f);
			else if (m_flags & LABEL_NX) glTranslatef((float)window->getRenderWidth()/2.0 - m_width, 0.0f, 0.0f);
			else if (m_flags & LABEL_PX) glTranslatef(-(float)window->getRenderWidth()/2.0, 0.0f, 0.0f);
			glTranslatef(((m_flags & LABEL_NX) ? -1.0f : 1.0f) * m_pos[GRADE1][0], 0.0f, 0.0f);
		}

		// then for the y-axis
		if (m_flags & LABEL_CY);// glTranslatef(0.0f, (float)window->getRenderHeight() / 2, 0.0f);
		else if (m_flags & LABEL_PY) glTranslatef(0.0f, (float)window->getRenderHeight()/2.0, 0.0f);
		else if (m_flags & LABEL_NY) glTranslatef(0.0f, -(float)window->getRenderHeight()/2.0 + m_height, 0.0f);
		glTranslatef(0.0, ((m_flags & LABEL_PY) ? -1.0f : 1.0f) * m_pos[GRADE1][1], 0.0f);

		glGetDoublev(GL_MODELVIEW_MATRIX, m_mvMatrix);
	}
//cmd("tsmode text"); cmd("label lab [e1 + e2] \"text \\ text \\ text \" 2d px ny");

	double b = 0;
	if (window->depthMaskAllowedOff() && ( (b = (fgColor(3) + bgColor(3) + olColor(3))) < 2.99) ) {
//		printf("Alpha enabled!\n");
		glDepthMask(GL_FALSE); // don't write in depth buffer
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	else {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	/*
	Don't understand exactly what's going on with the polygon offset in here....
	Why do I have to use negative values???
	Disabled the polygon offset for now. Let's see if it is really required
	*/

	// scale m_width, m_height back?
	// The actual scaling of the OpenGL rendering is done through glScale (see below)
	m_width /= textScale;
	m_height /= textScale;


	if (m_displayList != GL_INVALID_DISPLAY_LIST) {
		glCallList(m_displayList);
	}
	else {
		// generate a new display list, unless this is an image
		allocDisplayList();
		glNewList(m_displayList, GL_COMPILE_AND_EXECUTE);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		// dpi here: glScale(to required scale)
		glScaled(textScale, textScale, textScale);

		glDisable(GL_CULL_FACE);

		int flip = -1;//(m_flags & LABEL_2D) ? -1 : 1;

		// fill the background
		if (bgColor(3) > 0.0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			setBgColor();
			glBegin(GL_QUADS);
			glVertex2i(-2, flip * -2);
			glVertex2i((int)m_width + 2, flip * -2);
			glVertex2i((int)m_width + 2, flip * ((int)m_height + 2));
			glVertex2i(-2, flip * ((int)m_height + 2));
			glEnd();
		}

		// draw the outline
	//	glEnable(GL_POLYGON_OFFSET_LINE);
	//	glPolygonOffset(-1.0, -1.0);
		if (olColor(3) > 0.0) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			setOlColor();
			glBegin(GL_QUADS);
			glVertex2i(-2, flip * -2);
			glVertex2i((int)m_width + 2, flip * -2);
			glVertex2i((int)m_width + 2, flip *((int)m_height + 2));
			glVertex2i(-2, flip * ((int)m_height + 2));
			glEnd();
		}

		if (m_flags & LABEL_IMAGE) {
			setFgColor(); // get the fg alpha

			glTranslatef(0.0, -m_height, 0.0);

			/*if (!(m_flags & LABEL_FULLSCREEN))
				glScalef(m_fontSize, m_fontSize, m_fontSize);*/

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_TEXTURE_2D);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			glBindTexture(GL_TEXTURE_2D, m_textureName);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0, (float)m_imageHeight / m_textureHeight);
			glVertex2i(0, 0);

			glTexCoord2f((float)m_imageWidth / m_textureWidth, (float)m_imageHeight / m_textureHeight);
			glVertex2i((int)m_width, 0);

			glTexCoord2d((float)m_imageWidth / m_textureWidth, 0.0);
			glVertex2i((int)m_width, (int)m_height);

			glTexCoord2d(0.0, 0.0);
			glVertex2i(0, (int)m_height);
			glEnd();

			glDisable(GL_TEXTURE_2D);
		}
		else {
			// draw the text
		//	glEnable(GL_POLYGON_OFFSET_FILL);
		//	glPolygonOffset(-1.0, -1.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			setFgColor();
			glEnable(GL_TEXTURE_2D);

			if ((m_tsMode[0] == 'v') || (m_tsMode[0] == 'V')) {
				// draw using OpenGL and font system
				glScalef(m_fontSize, m_fontSize, m_fontSize); // dpi here
				glTranslatef(0.0, -1.0, 0.0);
				oglfprintf(m_text);
			}
			else {
				// draw using OpenGL & typesetting system
				g_state->m_typesetState->GLdraw(); 
				g_state->m_typesetState->clearDraw();
			}
			glDisable(GL_TEXTURE_2D);
		}

		glEnable(GL_CULL_FACE);

		//dpi here: unscale -> not required?

		glPopMatrix();

		glEndList();
	}


//	glDisable(GL_POLYGON_OFFSET_FILL);
//	glDisable(GL_POLYGON_OFFSET_LINE);
//	glPolygonOffset(0.0, 0.0);

	if (b) {
		glDisable(GL_BLEND);
	}


	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glLineWidth(lineWidth);

	return 0;
}

int textObject::pick(glwindow *window) {
//	window->disableClippingPlanes();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

//	int w = (int)ceil(m_fontSize * oglfprintfWidth(m_text)), h = (int)ceil(m_fontSize);
//	int w = m_width;

	// assumes the model matrix and text position has not changed since last call to draw()
	glLoadMatrixd(m_mvMatrix);

	// todo: set depth test mask?

	double ux, uy;
	wcUnitXY(ux, uy);
	if (!(m_flags & LABEL_2D))
		glScaled(ux, uy, 1.0);


	glDisable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// fill the outline
	int flip = -1 ;// (m_flags & LABEL_2D) ? -1 : 1;
	setOlColor();
	glBegin(GL_QUADS);
	glVertex2i(-2, flip * -2);
	glVertex2i((int)m_width + 2, flip * -2);
	glVertex2i((int)m_width + 2, flip *((int)m_height + 2));
	glVertex2i(-2, flip * ((int)m_height + 2));
	glEnd();

	glEnable(GL_CULL_FACE);

	glPopMatrix();

	return 0;
}

/*int textObject::windowCoordinates(double &x, double &y, double &z) {

	// Find out (using OpenGL modelview & projection matrices + viewport transformation) 
	// where the text should be drawn in window coordinates
	// This method has the advantage that clipping does not occur
	double mvMatrix[16];
	double pjMatrix[16];
	double viewport[4];
	double pt1[4], pt2[4];
	glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, pjMatrix);
	glGetDoublev(GL_VIEWPORT, viewport);

	pt1[0] = m_pos[GRADE1][0]; pt1[1] = m_pos[GRADE1][1];
	pt1[2] = m_pos[GRADE1][2]; pt1[3] = 1;

	GLmatrixVectorMul(mvMatrix, pt1, pt2);
	z = pt2[2] / pt2[3];
	GLmatrixVectorMul(pjMatrix, pt2, pt1);
	x = (pt1[0] / pt1[3] + 1.0) * viewport[2] / 2.0 + viewport[0];
	y = (pt1[1] / pt1[3] + 1.0) * viewport[3] / 2.0 + viewport[1];

	return 1;
}*/

float textObject::drawSortValue() {
	GAIM_FLOAT v = ((fgColor(3) + bgColor(3) + olColor(3)) > 2.99) ? 1.0 : 2.0;
	if (g_state->m_labelsAlwaysOnTop) v += 2.0;

	return (float)v;
}

int textObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	if (sl) {
		sprintf(buf, "%s: %s: \n'%s'", m_name.c_str(), (m_flags & LABEL_IMAGE) ? "image" : "text", m_text);
	}
	else {
		sprintf(buf, "%s: \n'%s'", (m_flags & LABEL_IMAGE) ? "image" : "text", m_text);
	}
	return 0;
}

// these functions get called when the color (or alpha) has changed
void textObject::colorFgChanged() {
	freeDisplayList();
}
void textObject::colorBgChanged() {
	freeDisplayList();
}
void textObject::colorOlChanged() {
	freeDisplayList();
}

// this function gets called when the text scale has changed
void textObject::textScaleChanged() {
	freeDisplayList();
}


int textObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	if (m_flags & LABEL_DYNAMIC)  {
		object *o = g_state->getObjectPtrByName(m_pointName);
		if (o) o->translate(window, depth, motionX, motionY);
	}
	else if (m_flags & LABEL_2D) {
		m_pos -= ((m_flags & LABEL_NX) ? -1.0 : 1.0) * (GAIM_FLOAT)motionX * e3ga::e1 + 
			((m_flags & LABEL_NY) ? -1.0 : 1.0) * (GAIM_FLOAT)motionY * e3ga::e2;
	}
	else {
		e3ga v;
		window->vectorAtDepth(depth, motionX, -motionY, v);
		m_pos -= v;
	}

	return 0;
}
