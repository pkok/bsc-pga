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

#ifndef _UTIL_H_
#define _UTIL_H_

#include "gaincludes.h"

#ifdef WIN32
#pragma warning(disable:4996)
#endif

/*
Converts a 3D rotor into a OpenGL transformation matrix
*/
void e3gaRotorToOpenGLMatrix(const e3ga &rot, float rotM[16]);

/*
Multiplies a 4x4 OpenGL transformation matrix 'm' with a vector 'v'.
The result goes into 'r'
*/
void GLmatrixVectorMul(const double m[16], const double v[4], double r[4]);

//int c3ga2e3ga(const c3ga &c3gaMv, e3ga &e3gaMv);

// create a rotor that rotates a vector 'v' to e3
int e3gaRve3(e3ga &R, const e3ga &v);
int p3gaRve3(p3ga &R, const p3ga &v);
int c3gaRve3(c3ga &R, const c3ga &v);

inline void c3gaConstructPoint(c3ga &p, GAIM_FLOAT e1c, GAIM_FLOAT e2c, GAIM_FLOAT e3c) {
	p.set(GRADE1, e1c, e2c, e3c, 1.0, -0.5 * (e1c * e1c + e2c * e2c + e3c * e3c));
}

int rotor2Bivector(e3ga &B, const e3ga &R);

// returns in 'c' the color 'name' (for basic colors such as red, green, blue, etc)
int getColor(const char *name, float c[4]);

#endif /* _UTIL_H_ */
