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

#include <string.h>
#include <math.h>

#include "util.h"
#include "osdep.h"

void e3gaRotorToOpenGLMatrix(const e3ga &rot, float rotM[16]) {
	e3ga_om om;
	e3ga vi[3], ri = rot.inverse(); // vi = vector images; ri = rot inverse
	vi[0] = (rot * e3ga::e1 * ri)(GRADE1);
	vi[1] = (rot * e3ga::e2 * ri)(GRADE1);
	vi[2] = (rot * e3ga::e3 * ri)(GRADE1);
	om.initOuterMorphism(vi);
	float rotM2[16] = {
		(float)om.c[1 + 0 * 3 + 0], (float)om.c[1 + 1 * 3 + 0], (float)om.c[1 + 2 * 3 + 0], 0,
		(float)om.c[1 + 0 * 3 + 1], (float)om.c[1 + 1 * 3 + 1], (float)om.c[1 + 2 * 3 + 1], 0,
		(float)om.c[1 + 0 * 3 + 2], (float)om.c[1 + 1 * 3 + 2], (float)om.c[1 + 2 * 3 + 2], 0,
		0, 0, 0, 1
	};
	memcpy(rotM, rotM2, sizeof(float)*16);
}


void GLmatrixVectorMul(const double m[16], const double v[4], double r[4]) {
	int i, j;
	for (i = 0; i < 4; i++) {
		r[i] = 0;
		for (j = 0; j < 4; j++)
			r[i] += m[j * 4 + i] * v[j];
	}
}

int e3gaRve3(e3ga &R, const e3ga &v) {
	R = 1.0 + v.normal() * e3ga::e3;
	if (sqrt(R.norm_a()) < 1e-8) R = e3ga::e3 ^ e3ga::e1; // any 180 degree rot in a plane containing e3?
	return 0;
}

int p3gaRve3(p3ga &R, const p3ga &v) {
	R = 1.0 + v.normal() * p3ga::e3;
	if (sqrt(R.norm_a()) < 1e-8) R = p3ga::e3 ^ p3ga::e1; // any 180 degree rot in a plane containing e3?
	return 0;
}

int c3gaRve3(c3ga &R, const c3ga &v) {
	R = 1.0 + v.normal() * c3ga::e3;
	if (sqrt(R.norm_a()) < 1e-8) R = c3ga::e3 ^ c3ga::e1; // any 180 degree rot in a plane containing e3?
	return 0;
}




int rotor2Bivector(e3ga &B, const e3ga &R) {
	e3ga Rn(R / sqrt(R.norm_a()));
	GAIM_FLOAT ca = Rn.scalar();
	if ((Rn(GRADE2).norm_a() < 1e-9) || (sin(acos(ca)) < 1e-9))  B = 0;
	else B = (acos(ca) * Rn / sin(acos(ca)))(GRADE2);
	
	return 0;
}

static int setColor(float c[4], float r, float g, float b, float a) {
	c[0] = r; c[1] = g; c[2] = b; c[3] = a;
	return 0;
}

int getColor(const char *name, float c[4]) {
	if ((!strcmpnc(name, "r")) || (!strcmpnc(name, "red"))) return setColor(c, 1.0, 0.0, 0.0, 1.0);
	else if ((!strcmpnc(name, "g")) || (!strcmpnc(name, "green"))) return setColor(c, 0.0, 1.0, 0.0, 1.0);
	else if ((!strcmpnc(name, "b")) || (!strcmpnc(name, "blue"))) return setColor(c, 0.0, 0.0, 1.0, 1.0);
	else if ((!strcmpnc(name, "w")) || (!strcmpnc(name, "white"))) return setColor(c, 1.0, 1.0, 1.0, 1.0);
	else if ((!strcmpnc(name, "m")) || (!strcmpnc(name, "magenta"))) return setColor(c, 1.0, 0.0, 1.0, 1.0);
	else if ((!strcmpnc(name, "y")) || (!strcmpnc(name, "yellow"))) return setColor(c, 1.0, 1.0, 0.0, 1.0);
	else if ((!strcmpnc(name, "c")) || (!strcmpnc(name, "cyan"))) return setColor(c, 0.0, 1.0, 1.0, 1.0);
	else if ((!strcmpnc(name, "k")) || (!strcmpnc(name, "black"))) return setColor(c, 0.0, 0.0, 0.0, 1.0);
	else if ((!strcmpnc(name, "grey")) || (!strcmpnc(name, "gray"))) return setColor(c, 0.5f, 0.5f, 0.5f, 1.0f);
	return -1;
}


