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

#include "object.h"
#include "mvint.h"
#include "util.h"
#include "state.h"

int mvInt::interpret(const e3ga &amv, int creationFlags /* = 0*/) {
	e3ga mv(amv);
	const GAIM_FLOAT epsilon = 10e-8, epsilon2 = epsilon * epsilon;
	const GAIM_FLOAT *c;
	e3ga tmp, rt, pe1, pe2, pe3;
	GAIM_FLOAT scale;

	if (creationFlags == 0) creationFlags = m_creationFlags;
	m_creationFlags = creationFlags;

	m_type = MVI_E3GA;

	int grade, type = mv.mvType(&grade), allGrades;

	if (m_creationFlags & OC_VERSOR) type = GA_VERSOR; // force versor interpretation
 	if (m_creationFlags & OC_BLADE) type = GA_BLADE; // force blade interpretation

	allGrades = 0X1FF; // OC_GRADE0 | ... | OC_GRADE8
	if (m_creationFlags & allGrades) { // force grade X interpretation
		grade = m_creationFlags & allGrades;
		mv = mv(grade);
	}

	if (type == GA_BLADE) {
		switch(grade) {
		case GRADE0: // scalar
			m_type |= MVI_SCALAR;
			/*
			scalar 0: magnitude
			*/
			m_scalar[0] = mv.scalar();
			break;
		case GRADE1:
			m_type |= MVI_VECTOR;
			/*
			scalar 0: magnitude
			vector 0: direction
			*/
			m_scalar[0] = sqrt(mv.norm_a());

			c = mv[GRADE1];
			if (fabs(m_scalar[0]) > 0.0) {
				m_vector[0][0] = c[E3GA_E1] / m_scalar[0];
				m_vector[0][1] = c[E3GA_E2] / m_scalar[0];
				m_vector[0][2] = c[E3GA_E3] / m_scalar[0];
			}
			else {
				m_vector[0][0] = m_vector[0][1] = m_vector[0][2] = 0.0;
			}
			m_point[0][0] = m_vector[0][0] * m_scalar[0];
			m_point[0][1] = m_vector[0][1] * m_scalar[0];
			m_point[0][2] = m_vector[0][2] * m_scalar[0];
			break;
		case GRADE2:
			m_type |= MVI_BIVECTOR;
			/*
			scalar 0: magnitude
			vector 0: normal
			vector 1: orthogonal to vector 0 and 2
			vector 2: orthogonal to vector 0 and 1
			*/
			m_scalar[0] = sqrt(mv.norm_a());

			// set vector 0 (normal)
			tmp = mv.dual() / m_scalar[0];
			c = tmp[GRADE1];
			m_vector[0][0] = c[E3GA_E1];
			m_vector[0][1] = c[E3GA_E2];
			m_vector[0][2] = c[E3GA_E3];

			// set vector 1 and 2 (orthogonal to normal)
			if ((g_state->m_e3gaFactor[0].norm_a() > 0.0) && // user factorization
				(g_state->m_e3gaFactor[1].norm_a() > 0.0)) {
				pe1 = ((g_state->m_e3gaFactor[0] << mv) << mv.inverse());
				pe2 = ((g_state->m_e3gaFactor[1] << mv) << mv.inverse());
				scale = (mv / (pe1 ^ pe2)).scalar();
				//mv.print("target: ");
				//(pe1 ^ pe2).print("1: ");
				pe1 *= ((scale < 0.0) ? -1.0 : 1.0) * sqrt(fabs(scale));
				pe2 *= sqrt(fabs(scale));
				//(pe1 ^ pe2).print("2: ");
			}
			else { // auto factorization
				e3gaRve3(rt, tmp);
				pe1 = (rt * e3ga::e1 * rt.inverse())(GRADE1);
				pe2 = (rt * e3ga::e2 * rt.inverse())(GRADE1);
			}
			c = pe1[GRADE1];
			m_vector[1][0] = c[E3GA_E1]; m_vector[1][1] = c[E3GA_E2]; m_vector[1][2] = c[E3GA_E3];
			c = pe2[GRADE1];
			m_vector[2][0] = c[E3GA_E1]; m_vector[2][1] = c[E3GA_E2]; m_vector[2][2] = c[E3GA_E3];
			break;
		case GRADE3: // pseudoscalar / trivector
			m_type |= MVI_TRIVECTOR;

			/*
			scalar 0: magnitude
			*/

			m_scalar[0] = mv[GRADE3][E3GA_I];

			// factor into vector 0, 1, 2
			if ( (scale = (g_state->m_e3gaFactor[0] ^ g_state->m_e3gaFactor[1] ^ g_state->m_e3gaFactor[2]).norm_a()) > 0.0) {
				// factor using the presupplied factors
				pe1 = g_state->m_e3gaFactor[0];
				pe2 = g_state->m_e3gaFactor[1];
				pe3 = g_state->m_e3gaFactor[2];
				scale = pow(sqrt(scale), 1.0 / 3.0);
			}
			else {
				// factor using the basis vectors
				pe1 = e3ga::e1;
				pe2 = e3ga::e2;
				pe3 = e3ga::e3;
				scale = 1.0;
			}

			//printf("Dividing by scale %f\n", scale);

			// scale the factors
			pe1 *= 1.0 / scale;
			pe2 *= 1.0 / scale;
			pe3 *= 1.0 / scale;

			// set the factors
			c = pe1[GRADE1];
			m_vector[0][0] = c[E3GA_E1]; m_vector[0][1] = c[E3GA_E2]; m_vector[0][2] = c[E3GA_E3];
			c = pe2[GRADE1];
			m_vector[1][0] = c[E3GA_E1]; m_vector[1][1] = c[E3GA_E2]; m_vector[1][2] = c[E3GA_E3];
			c = pe3[GRADE1];
			m_vector[2][0] = c[E3GA_E1]; m_vector[2][1] = c[E3GA_E2]; m_vector[2][2] = c[E3GA_E3];
				
			break;
		}
	}
	else if (type == GA_VERSOR) {
		GAIM_FLOAT odd = mv(GRADE1).norm_a() + mv(GRADE3).norm_a();
		GAIM_FLOAT even = mv(GRADE0).norm_a() + mv(GRADE2).norm_a();
		if (odd < even) { // even 3D versor = rotor
			m_type |= MVI_ROTOR;
			/*
			scalar 0: magnitude
			scalar 1: angle
			vector 0: normal
			vector 1: orthogonal to vector 0 and 2
			vector 2: orthogonal to vector 0 and 1
			point 0: position (todo for conformal?)
			*/
			even = sqrt(even);
			m_scalar[0] = even;

			// interpret the bivector part to retrieve plane
			e3ga plane(m_scalar[0] * mv(GRADE2).normal());
			mvInt bivectorInt(plane, OC_BLADE | OC_GRADE2);
			memcpy(m_vector[0], bivectorInt.m_vector[0], sizeof(GAIM_FLOAT) * 3);
			memcpy(m_vector[1], bivectorInt.m_vector[1], sizeof(GAIM_FLOAT) * 3);
			memcpy(m_vector[2], bivectorInt.m_vector[2], sizeof(GAIM_FLOAT) * 3);

			// retrieve the angle
			e3ga Rn(mv / even);
			GAIM_FLOAT ca = Rn.scalar();
			GAIM_FLOAT sa = sqrt(Rn(GRADE2).norm_a());
			if ((sa < epsilon) || (sin(acos(ca)) < epsilon)) m_scalar[1] = 0; // angle = 0 
			else m_scalar[1] = 2.0 * atan2(sa, ca);
			//cprintf("Angle = %f\n", m_scalar[1]);
		}
		else { // odd 3D versor
			m_type |= MVI_ODD_3D_VERSOR;
		}
	}
	else {
		m_type |= MVI_UNKNOWN;
		m_valid = 0;
		return 0;
	}

	m_valid = 1;
	return 0;
}

