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

#ifndef _GEOSPHERE_H_
#define _GEOSPHERE_H_

#include "gaincludes.h"

typedef struct geosphereFace_s {
	int v[3];
	int child[4];

	e3ga plane;
	GAIM_FLOAT d;
	int depth;

	int neighbour[3];	// the neighbours of each edge

	int contourIntersect[3];
	int contourVisited;
} geosphereFace;


typedef struct geosphere_s {
	int nbVertices, maxVertices;
	e3ga *vertex;

	int nbFaces, maxFaces;
	geosphereFace *face;

	int nbPrimitives;
	int depth;
} geosphere;

// sphere used for drawing points (low sub division)
extern geosphere *g_pointSphere;
// sphere used for drawing spheres (high sub division)
extern geosphere *g_sphereSphere;

int gsCompute(geosphere **sPtr, int depth);
int gsFree(geosphere **sPtr);

// normal: draw (scaled) normal (> 0.0) or not
void gsDraw(geosphere * sphere, GAIM_FLOAT normal = 0.0);

#endif // _GEOSPHERE_H_
