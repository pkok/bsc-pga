#ifndef _GAVIEWER_GL_INCLUDES_H_
#define _GAVIEWER_GL_INCLUDES_H_

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __MACH__
#include <opengl/gl.h>
#include <opengl/glu.h>
#else 
#include <GL/gl.h>
#include <GL/glu.h>
#endif


#endif /* _GAVIEWER_GL_INCLUDES_H_ */
