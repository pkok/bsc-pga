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

#ifndef _TUBE_DRAW_H_
#define _TUBE_DRAW_H_

#include <vector>
#include "e3ga/e3ga.h"

/// substitute to draw OpenGL lines as '3D tubes'
class TubeDraw {
public:
	TubeDraw();

	// what = GL_LINES, GL_LINE_STRIP or GL_LINE_LOOP
	void begin(int what);
	void end();

	void vertex2d(double x, double y);
	void vertex3d(double x, double y, double z);
	void vertex2dv(const double *c);
	void vertex3dv(const double *c);

	/// sets line width to 'w'
	void setLineWidth(double w);
	double getLineWidth();

	/// enables / disables forwarding to OpenGL
	void setUseOpenGL(bool v);
	bool getUseOpenGL();

	/// set number of segments used to draw the tube
	void setNbSegments(int nb);

protected:
	/// vertices are collected here (they are not drawn until 'end()' is called)
	std::vector<e3ga> m_vertices;

	/// what to draw (argument to begin(...), GL_LINES, GL_LINE_STRIP or GL_LINE_LOOP)
	int m_what;

	/// either passed to glwidth, or used directly as the radius of the tube
	double m_lineWidth;

	/// How many segments to draw (min = 3)
	int m_nbSegments;

	/** when true, forwards all calls to regular OpenGL . . .
	Otherwise, draws as 3D tubes
	*/
	bool m_useOpenGL;

	void drawTubeSegment(int i, const std::vector<e3ga> &vertices);
	void drawTubeCap(int vIdx, const std::vector<e3ga> &vertices, bool endCap);

};

#endif /* _TUBE_DRAW_H_ */
