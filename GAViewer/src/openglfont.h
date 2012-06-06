/*
This file contains the header for OpenGL fonts.
OpenGL fonts render textured fonts.
These are read from .fnt text-files, containing the font
description, and from .png files, containing the textures

'_CAVE_' #define must be set for cave/multiprocessing/shared mem usage

Depends on "png.cpp", "mypng.h" and libpng for loading .png files

*/

#ifndef _OPENGL_FONT_
#define _OPENGL_FONT_

#include "gl_includes.h"

/* 
sets 'fontName' as the current font for this thread / process.
Loads font from 'fontName.fnt'.
*/
int oglffont(const char *fontName);

/*
generic printf for OpenGL fonts
Assumes texturing is enabled (glEnable(GL_TEXTURE_2D))
returns number of characters written, or -1 on error
*/
int oglfprintf(const char *fmt, ...);

/*
Returns length of string in pixels when drawn in the current font
*/
float oglfprintfpixlen(const char *fmt, ...);

/*
Draws _one_ character 'c' at position [x, y] 
VERY inefficient...
*/
int oglfchar(int c, float x, float y);

#ifdef _CAVE_
// initializes OpenGL fonts & terminates in CAVE environment
int oglfinit(void *Heap);
void oglfquit();
#endif /* _CAVE_ */


#endif /* _OPENGL_FONT_*/
