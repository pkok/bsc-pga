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
#include <math.h>

#include "object.h"
#include "mvint.h"
#include "util.h"
#include "state.h"

int mvInt::interpret(const p3ga &X, int creationFlags /* = 0*/) {
	p3ga I(p3ga::e1 ^ p3ga::e2 ^ p3ga::e3);
	p3ga e0(p3ga::e0);
	
	const GAIM_FLOAT epsilon = 1e-6; // rather arbitrary limit on fp-noise
	p3ga Xd, tmp;

	initToNothing();

	m_type = 0;
	m_type = MVI_P3GA;

	// todo: dualize?


	// check for zero euclidean norm multivectors
	if (X.norm_a() < epsilon) { // *********************** zero blade *******************************
		m_type |= MVI_ZERO;
		m_valid = 1;
		return 0;
	}

	// determine the type of the multivectors
	int grade, type = X.mvType(&grade);
	grade = (int)(log((double)grade) / log((double)2) + 0.45);
	if (creationFlags & OC_BLADE) type = GA_BLADE; // force blade interpretation
	else if (creationFlags & OC_VERSOR) type = GA_VERSOR; // force versor interpretation
	// maybe allow force null, dual, and other properties?

	if (type == GA_MULTIVECTOR) {
		m_type |= MVI_UNKNOWN;
		m_valid = 0;
		return 0; 
	}

	if (type == GA_BLADE) { // ************************************* all blades *************************************
		p3ga ipe0X(e0 << X);
		p3ga ori, pos;
		GAIM_FLOAT size2;
		int ipe0Xzero = (ipe0X.norm_a() < epsilon);

		if (ipe0Xzero) { // ************************************* Euclidean subspaces (scalar, vector, bivector, trivector) *************************************
			ori = X;
			size2 = (ori << ori).scalar();
			//cprintf("\n\nEuclidean subspace, grade %d\nOri: %s\nSize2: %f\n", grade, ori.string(), size2);
			return p3gaEuclideanSubspace(X, grade, ori, size2); 
		}
		else { //  ************************************* homogeneous subspaces (point, line, plane, space) *************************************
			ori = e0 << X;
			size2 = (ori << ori).scalar();
			pos = ori << X.inverse();
			//cprintf("\n\nHomogeneous subspace, grade %d\nOri: %s\nPos: %s\nSize2: %f\n", grade, ori.string(), pos.string(), size2);
			return p3gaHomogeneousSubspace(X, grade, ori, pos, size2); 
		}
	}
	// todo: versor & such
	else {
		m_type |= MVI_UNKNOWN;
		m_valid = 0;
	}

	return 0;
}

int mvInt::p3gaEuclideanSubspace(const p3ga &X, int grade, const p3ga &ori, GAIM_FLOAT size2) {
	m_valid = 1;
	p3ga normal, o, pe1, pe2, rt;

	switch (grade) {
	case 4:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		//cprintf("mvInt::p3gaEuclideanSubspace(): grade %d Euclidean subspaces do not exist\n", grade);
		return 0;
	case 0: // scalar 
		m_type |= MVI_SCALAR;
		/*
		scalar 0: magnitude
		*/
		m_scalar[0] = ori.scalar();
		return 0;
	case 1: // vector
		m_type |= MVI_VECTOR;
		/*
		scalar 0: magnitude
		vector 0: direction
		point 0: position of tip
		*/
		m_scalar[0] = sqrt(fabs(size2));
		o = ori / m_scalar[0];
		m_vector[0][0] = o[GRADE1][P3GA_E1];
		m_vector[0][1] = o[GRADE1][P3GA_E2];
		m_vector[0][2] = o[GRADE1][P3GA_E3];

		m_point[0][0] = ori[GRADE1][P3GA_E1];
		m_point[0][1] = ori[GRADE1][P3GA_E2];
		m_point[0][2] = ori[GRADE1][P3GA_E3];
		return 0;

	case 2: // bivector
		m_type |= MVI_BIVECTOR;
		/*
		scalar 0: magnitude
		vector 0: normal
		vector 1: orthogonal to vector 0 and 2
		vector 2: orthogonal to vector 0 and 1
		*/
		m_scalar[0] = sqrt(fabs(size2));
		p3gaFactorBivector(o = ori / m_scalar[0], m_vector[0], m_vector[1], m_vector[2]);
		return 0;
	case 3: // trivector
		m_type |= MVI_TRIVECTOR;
		/*
		scalar 0: magnitude
		*/
		m_scalar[0] = -ori[GRADE3][P3GA_E1_E2_E3];
		return 0;

	}
	return 0;
}

int mvInt::p3gaHomogeneousSubspace(const p3ga &X, int grade, const p3ga &ori, const p3ga &pos, GAIM_FLOAT size2) {
	m_valid = 1;
	p3ga normal, o, pe1, pe2, rt;
	const GAIM_FLOAT *c;

	/*
	For all types:
	point 0: point
	*/
	c = pos[GRADE1];
	if (c[P3GA_E0] != 0.0) {
		m_point[0][0] = c[P3GA_E1] / c[P3GA_E0];
		m_point[0][1] = c[P3GA_E2] / c[P3GA_E0];
		m_point[0][2] = c[P3GA_E3] / c[P3GA_E0];
	}

	switch (grade) {
	case 0:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		//cprintf("mvInt::p3gaHomogeneousSubspace(): grade %d homogeneous subspaces do not exist\n", grade);
		return 0;
	case 1: // points
		m_type |= MVI_POINT;
		/*
		scalar 0: magnitude
		point 0: point
		*/
		m_scalar[0] = X[GRADE1][P3GA_E0];
		return 0;
	case 2: // line
		m_type |= MVI_LINE;
		/*
		scalar 0: magnitude
		point 0: point
		vector 0: direction
		*/
		m_scalar[0] = sqrt(fabs(size2));
		o = ori / m_scalar[0];
		m_vector[0][0] = o[GRADE1][P3GA_E1];
		m_vector[0][1] = o[GRADE1][P3GA_E2];
		m_vector[0][2] = o[GRADE1][P3GA_E3];
		return 0;
	case 3: // plane
		m_type |= MVI_PLANE;
		/*
		scalar 0: magnitude
		vector 0: normal
		vector 1: orthogonal to vector 0 and 2
		vector 2: orthogonal to vector 0 and 1
		*/
		m_scalar[0] = sqrt(fabs(size2));
		p3gaFactorBivector(o = ori / m_scalar[0], m_vector[0], m_vector[1], m_vector[2]);
		return 0;
	case 4: // space
		m_type |= MVI_SPACE;
		/*
		scalar 0: magnitude
		*/
		m_scalar[0] = ori[GRADE4][P3GA_I];
		return 0;

	}
	return 0;
}

int mvInt::p3gaFactorBivector(const p3ga &B, GAIM_FLOAT *normal, GAIM_FLOAT *factor1, GAIM_FLOAT *factor2) {
	// get normal
	const GAIM_FLOAT *c;
	GAIM_FLOAT scale;
	p3ga nl((B << (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3).inverse()).normal());
	p3ga pe1, pe2, rt;

	// get normal
	c = nl[GRADE1];
	if (normal)
		normal[0] = c[P3GA_E1];	normal[1] = c[P3GA_E2];	normal[2] = c[P3GA_E3];

	// set factor 1 and 2 (orthogonal to normal)
	if ((g_state->m_p3gaFactor[0].norm_a() > 0.0) && // user factorization
		(g_state->m_p3gaFactor[1].norm_a() > 0.0)) {
		pe1 = ((g_state->m_p3gaFactor[0] << B) << B.inverse());
		pe2 = ((g_state->m_p3gaFactor[1] << B) << B.inverse());
	}
	else { // auto factorization
		p3gaRve3(rt, nl); 
		pe1 = (rt * p3ga::e1 * rt.inverse())(GRADE1);
		pe2 = (rt * p3ga::e2 * rt.inverse())(GRADE1);
	}

	// if the bivector wasn't unit, adjust factors
	scale = (B / (pe1 ^ pe2)).scalar();
	pe1 *= ((scale < 0.0) ? -1.0 : 1.0) * sqrt(fabs(scale));
	pe2 *= sqrt(fabs(scale));

	// set factors
	if (factor1) {
		c = pe1[GRADE1];
		factor1[0] = c[P3GA_E1]; factor1[1] = c[P3GA_E2]; factor1[2] = c[P3GA_E3];
	}
	if (factor2) {
		c = pe2[GRADE1];
		factor2[0] = c[P3GA_E1]; factor2[1] = c[P3GA_E2]; factor2[2] = c[P3GA_E3];
	}

	return 0;
}
