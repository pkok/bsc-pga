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
This file contains the header for OpenGL fonts.
OpenGL fonts render textured fonts.
These are read from .fnt text-files, containing the font
description, and from .png files, containing the textures

'_CAVE_' #define must be set for cave/multiprocessing/shared mem usage

Depends on "png.cpp", "mypng.h" and libpng for loading .png files

*/

#ifndef _OPENGL_FONT_
#define _OPENGL_FONT_

#include "../gl_includes.h"

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
float oglfprintfWidth(const char *fmt, ...);

/*
Draws _one_ character 'c' at position [x, y] 
*/
int oglfPrintChar(int c, float x, float y);

/*
Raw, single character, single threaded printing:
Sequence:
oglfPrintCharRawBegin();
n X oglfPrintCharRaw(c, x, y);
oglfPrintCharRawEnd();
*/
void oglfPrintCharRaw(int c, float x, float y, float s);
void oglfPrintCharRawBegin();
void oglfPrintCharRawEnd();

/*
Returns the width of a single character
*/
float oglfCharWidth(int c);

// todo: unformatted, raw string functions
/*
Draws an unformatted string of characters, terminated with 0
*/
int oglfPrintString(const int *c, float x, float y);
/*
Returns the width of an unformatted string of characters, terminated with 0
*/
float oglfStringWidth(const int *c);

#endif /* _OPENGL_FONT_*/
