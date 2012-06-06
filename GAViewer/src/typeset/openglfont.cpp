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

/*
This file contains the implementation for drawing textured OpenGL fonts.
The font description and texture is read from within the executable.

The fonts are created with a seperate program called 'fonttool'.
It allows you to specify were each character is in the texture.

After creation, the text file and the texture are convertex to 'C' code
using bin2c. (see fontdata.cpp and fontdata.h)

They are then linked into the executable
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef WIN32
#include <stdarg.h>
#endif /*WIN32*/

#include "openglfont.h"
//#include "mypng.h"
//#include "../softpic.h"
#include "../pngwrapper.h"

// ****************** customized:
#include "fontdata.h"
// ****************** end of customized


#include "../gl_includes.h"

#define OGLF_MAX_NAME_LENGTH 255

#ifndef GL_VERSION_1_1
#define glGenTextures glGenTexturesEXT
#define glBindTexture glBindTextureEXT
#endif /* GL_VERSION_1_1 */

typedef struct {
    float x, y, w, w2;
} oglfCharInfo;

typedef struct {
    char fontName[OGLF_MAX_NAME_LENGTH + 1];
    char imageName[OGLF_MAX_NAME_LENGTH + 1];

    int nChars;
    float height;
    oglfCharInfo *c;

    GLuint textureName;
} oglfFontInfo;

typedef struct  {
    int currentFont;
    int nFonts;
    oglfFontInfo **fonts;
} oglfThreadInfo;

static void* g_oglfHeap = NULL;
static int g_oglfNThreads = 0;
static oglfThreadInfo g_oglfThreadInfo = {-1, 0, NULL};

inline static oglfThreadInfo *oglfGetThreadInfo() {
    return &g_oglfThreadInfo;
}

inline static void *oglfRealloc(void *ptr, int newSize) {
    return realloc(ptr, newSize);
}

inline static void *oglfMalloc(int size) {
    return oglfRealloc(NULL, size);
}

inline static void oglfFree(void *ptr) {
    free(ptr);
}

oglfFontInfo *oglfNewFont(int h, int nc, const char *fontName, const char *imageName) {
    int i;
    oglfFontInfo *f = (oglfFontInfo *)oglfMalloc(sizeof(oglfFontInfo));
    f->height = (float)h;
    f->nChars = nc;
    strcpy(f->fontName, fontName);
    strcpy(f->imageName, imageName);
    f->c = (oglfCharInfo*)oglfMalloc(sizeof(oglfCharInfo) * nc);
    for (i = 0; i < nc; i++) {
        f->c[i].w = 0;
        f->c[i].x = 0;
        f->c[i].y = 0;
    }
    return f;
}

void oglfDeleteFont(oglfFontInfo *font) {
    oglfFree(font->c);
    oglfFree(font);
}


static int oglfpreprint(va_list *ap, const char *fmt, char **returnBuf) {
    static char *buf = NULL;
    int s = (int)strlen(fmt), l;

#ifndef IRIX62
    static int bufLen = 0;
    do {
        s = s * 4;
        if (s > bufLen)
            buf = (char*)realloc(buf, bufLen = s);
        if (buf == NULL) return -1;

#ifdef WIN32
    } while ( (l = _vsnprintf(buf, s - 1, fmt, *ap)) < 0);
#else
    } while ( (l = vsnprintf(buf, s - 1, fmt, *ap)) < 0);
#endif

#else  /* IRIX62 */

    s = 2048; // constand
    if ((buf = (char*)realloc(buf, s)) == NULL)
    {
        fprintf(stderr,
            "oglfpreprint(): memory allocation error for %d bytes\n", s);
        return -1;
    }
    l = vsprintf(buf, fmt, *ap);

#endif /* IRIX62 */

    *returnBuf = buf;
    return l;
}

// the font name is ignored
int oglffont(const char *fontName) {
    int nc, h, i, j, x, y, w;
    oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;
    char imageName[OGLF_MAX_NAME_LENGTH + 16];
    unsigned char *pixels = NULL;
    int width, height;

    if (info == NULL) return 0;

    // todo: test (something like) this!
    //    if (!g_State->m_OpenGLContextValid) return 0;

    // check if current font is requested font
    if ((info->currentFont >= 0) &&
        (!strcmp(info->fonts[info->currentFont]->fontName, fontName)))
        return 1;
    else
    {
        // check if font is already loaded
        for (i = 0; i < info->nFonts; i++)
            if (!strcmp(info->fonts[i]->fontName, fontName)) {
                info->currentFont = i;
                return 1;
            }

		// ****************** load font from memory:
		int idx = 0;
		const char *fontDescStr = (const char*)fontDesc;
        if (sscanf(fontDescStr + idx, "number of chars: %d\n", &nc) != 1) {
            fprintf(stderr, "oglffont(): could not sscanf() number of chars\n");
            return 0;
        }
		while (fontDescStr[idx] != 0x0a) idx++; idx++; // skip to next line
        if (sscanf(fontDescStr + idx, "height: %d\n", &h) != 1) {
            fprintf(stderr, "oglffont(): could not sscanf() height\n");
            return 0;
        }
		while (fontDescStr[idx] != 0x0a) idx++; idx++; // skip to next line
        if (sscanf(fontDescStr + idx, "image filename: %s\n", imageName) != 1) {
            fprintf(stderr, "oglffont(): could not sscanf() image filename\n");
            return 0;
        }
		while (fontDescStr[idx] != 0x0a) idx++; idx++; // skip to next line

        fontInfo = oglfNewFont(h, nc, fontName, imageName);

        for (i = 0; i < nc; i++) {
            if (sscanf(fontDescStr + idx, "char %d: %d %d %d\n", &j, &x, &y, &w) != 4) {
                fprintf(stderr, "oglffont(): could not sscanf() char %d\n", i);
                oglfDeleteFont(fontInfo);
                return 0;
            }
			while (fontDescStr[idx] != 0x0a) idx++; idx++; // skip to next line
            if (j != i) {
                fprintf(stderr,
                    "oglffont(): invalid character index %d (should be %d)\n",
                    j, i);
                oglfDeleteFont(fontInfo);
                return 0;
            }
            fontInfo->c[i].x = (float)x;
            fontInfo->c[i].y = (float)y;
            fontInfo->c[i].w = (float)w;
        }

		// ****************** load font texture from memory: 
		if (loadPNGEx(fontImage, fontImageLength , &pixels, &width, &height, 0) != 0) {
            fprintf(stderr, "oglffont(): Could not load %s\n",
                fontInfo->imageName);
            oglfDeleteFont(fontInfo);
            return 0;
        }


        // create opengl texture
        glGenTextures(1, &(fontInfo->textureName));
        glBindTexture(GL_TEXTURE_2D, fontInfo->textureName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

/*
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_LINEAR_MIPMAP_LINEAR);
*/

        unsigned char *laPixels = (unsigned char*)malloc(width * height);
        for (i = 0; i < width * height; i++)
        {
            laPixels[i] = 255-(pixels[i*3+0]+pixels[i*3+1]+pixels[i*3+2])/3;
        }

		// todo: is this OK?
//#ifndef GL_VERSION_1_1
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_ALPHA, width, height, GL_ALPHA,
            GL_UNSIGNED_BYTE, laPixels);
//#else
        /*glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0,
            GL_ALPHA, GL_UNSIGNED_BYTE, laPixels);*/
//#endif /* GL_VERSION_1_1 */

        free(pixels);
        free(laPixels);

        // adjust texture coordinates for image size
        for (i = 0; i < nc; i++) {
            fontInfo->c[i].w2 = fontInfo->c[i].w / fontInfo->height;
            fontInfo->c[i].w /= width;
            fontInfo->c[i].x /= width;
            fontInfo->c[i].y /= height;
        }
        fontInfo->height /= height;

        // add new font to font list
        info->fonts = (oglfFontInfo**)
            oglfRealloc(info->fonts, (info->nFonts+1)*sizeof(oglfFontInfo*));
        info->fonts[info->nFonts] = fontInfo;
        info->currentFont = info->nFonts;
        info->nFonts++;
        return 1;
    }
}

// outputs a single characted, returns width of character
static float oglChar(const oglfFontInfo *fontInfo, int c, float x, float y) {
	const oglfCharInfo *charInfo = fontInfo->c + c;
    glTexCoord2f(charInfo->x, charInfo->y + fontInfo->height);
    glVertex2f(x, y + 0.0f);
    glTexCoord2f(charInfo->x + charInfo->w, charInfo->y + fontInfo->height);
    glVertex2f(x + charInfo->w2, y + 0.0f);
    glTexCoord2f(charInfo->x + charInfo->w, charInfo->y);
    glVertex2f(x + charInfo->w2, y + 1.0f);
    glTexCoord2f(charInfo->x, charInfo->y);
    glVertex2f(x, y + 1.0f);
	return charInfo->w2;
}


int oglfprintf(const char *fmt, ...) {
    oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;

    va_list    ap;
    va_start(ap, fmt);
    int l;
    char *buf;

    if ((info == NULL) || (info->currentFont == -1)) return -1;

    int i;
    float x, y;

    if ( (l = oglfpreprint(&ap, fmt, &buf)) < 0) {
        return -1;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // draw all using OpenGL
    fontInfo = info->fonts[info->currentFont];
    glBindTexture(GL_TEXTURE_2D, fontInfo->textureName);
    y = x = 0.0f;
    glBegin(GL_QUADS);
    for (i = 0; i < l; i++) {
        if (((unsigned char*)buf)[i] == '\n') {    // goto next line
            x = 0.0f;
            y -= 1.0f;
            continue;
        }
		x += oglChar(fontInfo, ((unsigned char*)buf)[i], x, y);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    return l;
}

float oglfprintfWidth(const char *fmt, ...) {
    oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;
    oglfCharInfo *charInfo;

    va_list    ap;
    va_start(ap, fmt);
    int l;
    char *buf;

    if ((info == NULL) || (info->currentFont == -1)) return -1;

    if ( (l = oglfpreprint(&ap, fmt, &buf)) < 0) {
        return -1;
    }

    fontInfo = info->fonts[info->currentFont];

    int i;
    float x = 0.0f;
    for (i = 0; i < l; i++) {
        charInfo = fontInfo->c + ((unsigned char*)buf)[i];
        x += charInfo->w2;
    }

    return x;
}

int oglfPrintChar(int c, float x, float y) {
    oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;

    if ((info == NULL) || (info->currentFont == -1)) return 0;
    fontInfo = info->fonts[info->currentFont];
    if ((c >= fontInfo->nChars) || (c < 0)) return 0;

    // draw using OpenGL
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, fontInfo->textureName);

    glBegin(GL_QUADS);
		oglChar(fontInfo, c, x, y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);


    return 1;
}

/*
Raw character printing
*/
static oglfFontInfo *oglfCharRawFontInfo = NULL;
void oglfPrintCharRaw(int c, float x, float y, float s) {
	if (oglfCharRawFontInfo == NULL) return;
	const oglfCharInfo *charInfo = oglfCharRawFontInfo->c + c;
    glTexCoord2f(charInfo->x, charInfo->y + oglfCharRawFontInfo->height);
    glVertex2f(x, y);
    glTexCoord2f(charInfo->x + charInfo->w, charInfo->y + oglfCharRawFontInfo->height);
    glVertex2f(x + s * charInfo->w2, y);
    glTexCoord2f(charInfo->x + charInfo->w, charInfo->y);
    glVertex2f(x + s * charInfo->w2, y + s);
    glTexCoord2f(charInfo->x, charInfo->y);
    glVertex2f(x, y + s);
}
void oglfPrintCharRawBegin() {
    oglfThreadInfo *info = oglfGetThreadInfo();
	if (info->currentFont < 0) return;
    oglfCharRawFontInfo = info->fonts[info->currentFont];

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, oglfCharRawFontInfo->textureName);
    glBegin(GL_QUADS);
}
void oglfPrintCharRawEnd() {
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
	oglfCharRawFontInfo = NULL;
}



float oglfCharWidth(int c) {
	oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;

    if ((info == NULL) || (info->currentFont == -1)) return 0;
    fontInfo = info->fonts[info->currentFont];

	return fontInfo->c[c].w2;
}

int oglfPrintString(const int *cStr, float x, float y) {
	int c;
	int i = 0;
    oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;

    if ((info == NULL) || (info->currentFont == -1)) return 0;
    fontInfo = info->fonts[info->currentFont];

    // draw using OpenGL
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D, fontInfo->textureName);

    glBegin(GL_QUADS);

	while (c = cStr[i]) {
	    if ((c >= fontInfo->nChars) || (c < 0)) continue;

		oglChar(fontInfo, c, x, y);
		x += fontInfo->c[c].w2;

		i++;
	}
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);


    return i;
}

float oglfStringWidth(const int *cStr) {
	float w = 0.0;
	int i = 0, c;

	oglfThreadInfo *info = oglfGetThreadInfo();
    oglfFontInfo *fontInfo;

    if ((info == NULL) || (info->currentFont == -1)) return 0;
    fontInfo = info->fonts[info->currentFont];

	while (c = cStr[i]) {
	    if ((c >= fontInfo->nChars) || (c < 0)) continue;
		w += fontInfo->c[c].w2;
		i++;
	}


	return w;
}
