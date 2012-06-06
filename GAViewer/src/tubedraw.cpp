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


#include "tubedraw.h"
#include "osdep.h"
#include "p3ga/p3ga.h"

e3ga rotorFromVectorToVector(const e3ga &v1, const e3ga &v2) {
	if ((v1 % v2).scalar() < -0.99999f) {
		// (near) 180 degree rotation:
		e3ga tmp = v1 << (v1 ^ v2);
		double n2 = tmp.norm_a();
		if (n2 != 0.0f) tmp = tmp.normal();
		else
			tmp = ((v1 ^ e3ga::e1).norm_a() > (v1 ^ e3ga::e2).norm_a()) ? e3ga::e1 : e3ga::e2;
		return (v1 ^ tmp).normal();
	}
	else {
		GAIM_FLOAT s = (GAIM_FLOAT)sqrt(2.0 * (1.0f + (v2 % v1).scalar()));
		return (1.0 + v2 * v1) * (1.0f / s);
	}
}


TubeDraw::TubeDraw() {
	m_what = -1;

	m_lineWidth = 2.0;

	m_nbSegments = 6;

	m_useOpenGL = false;
}

void TubeDraw::begin(int what) {
	if (m_useOpenGL) {
		glLineWidth((float)m_lineWidth);
		glBegin(what);
	}
	else {
		m_vertices.clear();
		m_what = what;
	}

}

void TubeDraw::end() {
	// actually draw stuff
	if (m_useOpenGL) {
		glEnd();
	}
	else {
		if (m_vertices.size() < 2) return;

		if (m_what == GL_LINE_LOOP) {
			// if loop: last vertex = first vertex
			m_vertices.push_back(m_vertices[0]);
		}
		else if (m_what == GL_LINE_STRIP) {
			// last vertex = extra copy of last vertex
			m_vertices.push_back(m_vertices[m_vertices.size()-1]);
		}

		// vector of segment vertices (m_nbSegments for each enty in m_vertices)
		unsigned int startIdx = 0;
		unsigned int endIdx = (unsigned int)m_vertices.size();

		std::vector<e3ga> tubeVertices(m_nbSegments * (endIdx - startIdx));
		std::vector<e3ga> tubeDirections(endIdx - startIdx);
	
		// compute initial vertices (factor the dual of the first direction, or use e1 if l = 0)
		e3ga prevDir;
		{
			// first direction
			e3ga dir = m_vertices[startIdx+1] - m_vertices[startIdx];
			if (dir.norm_a() == 0) dir = e3ga::e1;
			else dir = dir.normal();
			prevDir = dir;
			tubeDirections[0] = dir;

			// get factors:
			e3ga plane = dir.dual();
			e3ga factors[2];
			plane.factor(factors);

			// construct first segments:
			for (int i = 0; i < m_nbSegments; i++) {
				double a = (double)i * 2 * M_PI / m_nbSegments;
				tubeVertices[startIdx * m_nbSegments + i] = factors[0] * cos(a) + factors[1] * sin(a);
			}
		}

		// then use minimal rotation to get from one to the next
		startIdx++;
		while ((startIdx+1) < endIdx) {
			// compute direction of this segment:
			e3ga newDir = m_vertices[startIdx+1] - m_vertices[startIdx];
			if (newDir.norm_a() == 0) newDir = prevDir;
			else newDir = newDir.normal();
			tubeDirections[startIdx] = newDir;

			// compute rotor from prev segment to current segment
			e3ga R = rotorFromVectorToVector(prevDir, newDir);
			e3ga Ri = R.inverse();

			// rotate all vertices of the previous segment:
			for (int i = 0; i < m_nbSegments; i++) {
				tubeVertices[startIdx * m_nbSegments + i] = 
					(R * tubeVertices[(startIdx-1) * m_nbSegments + i] * Ri)(GRADE1);
			}

			prevDir = newDir;
			startIdx++;
		}
		startIdx = 0;

		// DRAW:
		// if GL_LINES, just go ahead, no averaging required
		if (m_what == GL_LINES) {
			for (unsigned int i = 0; (i+1) < m_vertices.size(); i += 2) {
				// only change: overwrite all odd segments:
				for (int s = 0; s < m_nbSegments; s++)
					tubeVertices[(i+1) * m_nbSegments + s] = tubeVertices[i * m_nbSegments + s];

				drawTubeCap(i, tubeVertices, false);
				drawTubeSegment(i, tubeVertices);
				drawTubeCap(i+1, tubeVertices, true);
			}
		}
		else {
			if (m_what == GL_LINE_STRIP) {
				drawTubeCap(0, tubeVertices, false);
				drawTubeCap((int)m_vertices.size()-2, tubeVertices, true);
			}

			// average segments:
			std::vector<e3ga> avgTubeVertices(m_nbSegments * (endIdx - startIdx));
			int i = 1;
			if (m_what == GL_LINE_LOOP) i = 0;
			else {
				for (int s = 0; s < m_nbSegments; s++)
					avgTubeVertices[0 * m_nbSegments + s] = tubeVertices[0 * m_nbSegments + s];
			}

			// test: don't average, but intersect edges!
			for (; i < (int)m_vertices.size(); i++) {
				int prevIdx = i-1;
				if (prevIdx < 0) prevIdx = ((int)m_vertices.size()) - 2;
				const e3ga &td1 = tubeDirections[i];
				const e3ga &td2 = tubeDirections[prevIdx];
				p3ga d1(GRADE1, td1[GRADE1][0], td1[GRADE1][1], td1[GRADE1][2], 0);
				p3ga d2(GRADE1, td2[GRADE1][0], td2[GRADE1][1], td2[GRADE1][2], 0);

				for (int s = 0; s < m_nbSegments; s++) {
					const e3ga &tp1 = tubeVertices[i * m_nbSegments + s];
					const e3ga &tp2 = tubeVertices[prevIdx * m_nbSegments + s];

					p3ga p1(GRADE1, tp1[GRADE1][0], tp1[GRADE1][1], tp1[GRADE1][2], 1);
					p3ga p2(GRADE1, tp2[GRADE1][0], tp2[GRADE1][1], tp2[GRADE1][2], 1);

					p3ga L1 = p1 ^ d1;
					p3ga L2 = p2 ^ d2;

					if ((p1 ^ p2).norm_a() < 1e-7) {
						avgTubeVertices[i * m_nbSegments + s] = tp1;
					}
					else {
						p3ga P = p1 ^ d1 ^ p2;
						p3ga I = (L1 << P) << L2;
						GAIM_FLOAT Iw = I[GRADE1][3];
						avgTubeVertices[i * m_nbSegments + s] = e3ga(GRADE1, I[GRADE1][0] / Iw, I[GRADE1][1] / Iw, I[GRADE1][2] / Iw);
					}
				}
			}

			/*
			// average them:
			for (; i < (int)m_vertices.size(); i++) {
				int prevIdx = i-1;
				if (prevIdx < 0) prevIdx = ((int)m_vertices.size()) - 2;
				for (int s = 0; s < m_nbSegments; s++) {
					avgTubeVertices[i * m_nbSegments + s] = 
                        (tubeVertices[i * m_nbSegments + s] + tubeVertices[prevIdx * m_nbSegments + s]).normal();
				}
			}
			*/
			
			// actually draw 
			unsigned int nbVert = (unsigned int)m_vertices.size();
			if (m_what == GL_LINE_STRIP) {
				nbVert--;
			}
			for (unsigned int i = 0; (i+1) < nbVert; i ++) {
				drawTubeSegment(i, avgTubeVertices);
			}
		}
	}
}

void TubeDraw::drawTubeSegment(int vIdx, const std::vector<e3ga> &vertices) {
	double lw = m_lineWidth / 250.0;

	int vIdxp1 = vIdx + 1;
	if (m_what == GL_LINE_LOOP)
		if (vIdxp1 > (int)(m_vertices.size()-2)) vIdxp1 = 0;
	// use QUAD_STRIP to draw each segment, set normals properly
	glBegin(GL_QUAD_STRIP);
	for (int _i = 0; _i <= m_nbSegments; _i++) {
		int i = (_i)%m_nbSegments;
		const e3ga &n1 = vertices[vIdx * m_nbSegments + i];
		glNormal3dv(n1[GRADE1]);
		glVertex3dv((m_vertices[vIdx] + lw * n1)[GRADE1]);

		const e3ga &n2 = vertices[(vIdxp1) * m_nbSegments + i];
		glNormal3dv(n2[GRADE1]);
		glVertex3dv((m_vertices[vIdxp1] + lw * n2)[GRADE1]);
	}
	glEnd();
}


void TubeDraw::drawTubeCap(int vIdx, const std::vector<e3ga> &vertices, bool endCap) {
	double lw = m_lineWidth / 250.0;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3dv((vertices[vIdx * m_nbSegments + 0] ^ vertices[vIdx * m_nbSegments + 1]).dual().normal()[GRADE1]);
	glVertex3dv(m_vertices[vIdx][GRADE1]);
	for (int _i = 0; _i <= m_nbSegments; _i++) {
		int i = (_i)%m_nbSegments;
		if (endCap) i = m_nbSegments - 1 - i; // flip order on end cap
		const e3ga &n1 = vertices[vIdx * m_nbSegments + i];
		glVertex3dv((m_vertices[vIdx] + lw * n1)[GRADE1]);
	}
	glEnd();
}


void TubeDraw::vertex2d(double x, double y) {
	vertex3d(x, y, 0.0);
}

void TubeDraw::vertex3d(double x, double y, double z) {
	if (m_useOpenGL) {
		glVertex3d(x, y, z);
	}
	else {
		m_vertices.push_back(e3ga(GRADE1, x, y, z));
	}
}

void TubeDraw::vertex2dv(const double *c) {
	vertex3d(c[0], c[1], 0.0);
}

void TubeDraw::vertex3dv(const double *c) {
	vertex3d(c[0], c[1], c[2]);
}

/// sets line width to 'w'
void TubeDraw::setLineWidth(double w) {
	m_lineWidth = w;
}

/// enables / disables forwarding to OpenGL
void TubeDraw::setUseOpenGL(bool v) {
	m_useOpenGL = v;
}

void TubeDraw::setNbSegments(int nb) {
	m_nbSegments = nb;
}

double TubeDraw::getLineWidth() {
	return m_lineWidth;
}

bool TubeDraw::getUseOpenGL() {
	return m_useOpenGL;
}



