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

int mvInt::interpret(const c3ga &X, int creationFlags /* = 0*/) {
	c3ga I(c3ga::e1 ^ c3ga::e2 ^ c3ga::e3);
	c3ga no(c3ga::no), ni(c3ga::ni);
	c3ga nino(ni ^ no), noni(no ^ ni);

	const GAIM_FLOAT epsilon = 1e-6; // rather arbitrary limit on fp-noise
	c3ga Xd, tmp;

	initToNothing();

	m_type = 0;
	m_type = MVI_C3GA;

	// todo: dualize?


	// check for zero euclidean norm multivectors
	if (X.norm_a() < epsilon) { // *********************** zero blade *******************************
		m_type |= MVI_ZERO;
		m_valid = 1;
		return 0;/*c3gaZero(X); todo */
	}

	// determine the type of the multivectors 
	int grade, type = X.mvType(&grade, epsilon); // temp todo test epsilon

	grade = (int)(log((double)grade) / log((double)2) + 0.45);
	if (creationFlags & OC_BLADE) type = GA_BLADE; // force blade interpretation
	else if (creationFlags & OC_VERSOR) type = GA_VERSOR; // force versor interpretation
	// maybe allow force null, dual, and other properties?
	
	if (type == GA_MULTIVECTOR) {
		m_type |= MVI_UNKNOWN;
		m_valid = 0;

		return 0; /* c3gaUnknown(X); todo */
	}

	if (type == GA_BLADE) { // ************************************* all blades *************************************
		GAIM_FLOAT X2 = (X * X).scalar(), weight2;
		c3ga opniX(ni ^ X), ipniX(ni << X);
		c3ga attitude, pos;

		int X2zero = (fabs(X2) < epsilon);
		int opniXzero = (opniX.norm_a() < epsilon);
		int ipniXzero = (ipniX.norm_a() < epsilon);

		if (opniXzero && ipniXzero) { // *********************** free flat *******************************
			attitude = -(X >> no);
			weight2 = (attitude << attitude).scalar();
			return c3gaFreeFlat(X, grade, attitude, weight2); 
		}
		else if (opniXzero && (!ipniXzero)) { // *********************** bound flat *******************************
			attitude = noni << X;
			pos = ((noni) << X) << X.inverse(); // reverse is also good?
			weight2 = (attitude << attitude).scalar();

			return c3gaBoundFlat(X, grade, attitude, pos, weight2); 
		}
		else if ((!opniXzero) && ipniXzero) { // *********************** dual bound flat *******************************
			attitude = nino << X.dual();
			//pos = (noni ^ X) * X.inverse();
			pos = X.inverse() << (noni ^ X);
			weight2 = (attitude << attitude).scalar();

			m_type ^= MVI_DUAL;
			return c3gaBoundFlat(X.dual(), 5 - grade, attitude, pos, weight2); 
		}
		else if ((!opniXzero) && (!ipniXzero) && X2zero) { // *********************** bound tangent *******************************
//			attitude = ni << X; // (this is what the paper says, but it is wrong...?)
			attitude = nino << (ni ^ X); // (this one works)
			pos = (X >> ni).inverse() << X;
			weight2 = (attitude << attitude).scalar();

			return c3gaBoundTangent(X, grade, attitude, pos, weight2); 
		}
		else if ((!opniXzero) && (!ipniXzero) && (!X2zero)) { // *********************** (dual or non-dual) round *******************************
			c3ga niX(ni ^ X);
			GAIM_FLOAT niX2 = (niX * niX).scalar();
//			attitude = no << (ni ^ X);
			attitude = nino << (ni ^ X); // this is what you want...
			pos = (X * ni * X) / (2.0 * niX2);
			weight2 = ((grade & 1) ? -1.0 : 1.0) * (X << X).scalar() / niX2;

			return c3gaRound(X, grade, attitude, pos, weight2); 
		}
		else {
			m_type |= MVI_UNKNOWN;
			m_valid = 0;
		}
	}
	// todo: versors & such
	else {
		m_type |= MVI_UNKNOWN;
		m_valid = 0;
	}

	return 0;
}

int mvInt::c3gaFreeFlat(const c3ga &X, int grade, const c3ga &attitude, GAIM_FLOAT weight2) {
	m_valid = 1;
	c3ga normal, o, pe1, pe2, rt;

	switch (grade) {
	case 0:
	case 5:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		cprintf("mvInt::c3gaFreeFlat(): grade %d free flats do not exist\n", grade);
		return 0;
	case 1: // free scalar 
		m_type |= MVI_FREE_SCALAR;
		/*
		scalar 0: weight
		*/
		m_scalar[0] = attitude.scalar();
		return 0;
	case 2: // free vector
		m_type |= MVI_FREE_VECTOR;
		/*
		scalar 0: weight
		vector 0: direction
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		o = attitude / m_scalar[0];
		m_vector[0][0] = o[GRADE1][C3GA_E1];
		m_vector[0][1] = o[GRADE1][C3GA_E2];
		m_vector[0][2] = o[GRADE1][C3GA_E3];
		return 0;

	case 3: // free bivector
		m_type |= MVI_FREE_BIVECTOR;
		/*
		scalar 0: weight
		vector 0: normal
		vector 1: orthogonal to vector 0 and 2
		vector 2: orthogonal to vector 0 and 1
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		c3gaFactorBivector(o = attitude / m_scalar[0], m_vector[0], m_vector[1], m_vector[2]);
		return 0;
	case 4: // free trivector
		m_type |= MVI_FREE_TRIVECTOR;
		/*
		scalar 0: weight

		*/
		m_scalar[0] = attitude[GRADE3][C3GA_E1_E2_E3];
		return 0;

	}


	return 0;
}

int mvInt::c3gaBoundFlat(const c3ga &X, int grade, const c3ga &attitude, const c3ga &pos, GAIM_FLOAT weight2) {
	const GAIM_FLOAT *c;
	c3ga o;

	/*
	For all types:
	point 0: point
	*/
	c = pos[GRADE2];
	if (c[C3GA_NO_NI] != 0.0) {
		m_point[0][0] = c[C3GA_E1_NI] / c[C3GA_NO_NI];
		m_point[0][1] = c[C3GA_E2_NI] / c[C3GA_NO_NI];
		m_point[0][2] = c[C3GA_E3_NI] / c[C3GA_NO_NI];
	}


	switch(grade) {
	case 0:
	case 1:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		cprintf("mvInt::c3gaBoundFlat(): grade %d bound flats do not exist\n", grade);
		return 0;
	case 2: // flat point
		m_type |= MVI_FLAT_POINT;
		/*
		scalar 0: weight
		point 0: point
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		m_valid = 1;
		return 0;
	case 3: // line
		m_type |= MVI_LINE;
		/*
		scalar 0: weight
		point 0: point
		vector 0: direction
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		c = attitude[GRADE1];
		m_vector[0][0] = -c[C3GA_E1] / m_scalar[0];
		m_vector[0][1] = -c[C3GA_E2] / m_scalar[0];
		m_vector[0][2] = -c[C3GA_E3] / m_scalar[0];
		m_valid = 1;
		return 0;
	case 4: // plane
		m_type |= MVI_PLANE;
		/*
		scalar 0: weight
		vector 0: normal 
		vector 1: orthogonal to vector 0
		vector 2: orthogonal to vector 0 and vector 1
		point 0: point on plane closest to chosen origin
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		c3gaFactorBivector(o = attitude / m_scalar[0], m_vector[0], m_vector[1], m_vector[2]);
		m_valid = 1;
		return 0;
	case 5: // space?
		// MVI_SPACE
/*		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		cprintf("mvInt::c3gaBoundFlat(): don't know what a grade %d bound flat is\n", grade);*/

		// TODO: Ask Leo this is where the scalars end up?
		m_type ^= MVI_DUAL;
		m_valid = 1;
		m_type |= MVI_SCALAR;
		o = X.dual();
		m_scalar[0] = o.scalar();
		//cprintf("mvInt::c3gaBoundFlat(): don't know what a grade %d bound flat is\n", grade);
		return 0;
	}

	return 0;
}

int mvInt::c3gaBoundTangent(const c3ga &X, int grade, const c3ga &attitude, const c3ga &pos, GAIM_FLOAT weight2) {
	const GAIM_FLOAT *c;
	c3ga o;

	/*
	For all types:
	point 0: point
	*/
	c = pos[GRADE1];
	if (c[C3GA_NO] != 0.0) {
		m_point[0][0] = c[C3GA_E1] / c[C3GA_NO];
		m_point[0][1] = c[C3GA_E2] / c[C3GA_NO];
		m_point[0][2] = c[C3GA_E3] / c[C3GA_NO];
	}

	switch(grade) {
	case 0:
	case 5:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		cprintf("mvInt::c3gaBoundTangent(): grade %d bound tangents do not exist\n", grade);
		return 0;
	case 1: // points
		m_type |= MVI_POINT;
		/*
		scalar 0: weight
		point 0: point
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		m_valid = 1;
		return 0;
	case 2: // bound vector
		m_type |= MVI_BOUND_TANGENT_VECTOR;
		/*
		scalar 0: weight
		point 0: point
		vector 0: direction
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		c = attitude[GRADE1];
		m_vector[0][0] = c[C3GA_E1] / m_scalar[0];
		m_vector[0][1] = c[C3GA_E2] / m_scalar[0];
		m_vector[0][2] = c[C3GA_E3] / m_scalar[0];
		m_valid = 1;
		return 0;
	case 3: // bound bivector
		m_type |= MVI_BOUND_TANGENT_BIVECTOR;
		/*
		scalar 0: weight
		point 0: point
		vector 0: normal 
		vector 1: orthogonal to vector 0
		vector 2: orthogonal to vector 0 and vector 1		
		*/
		m_scalar[0] = sqrt(fabs(weight2));
		c3gaFactorBivector(o = attitude / m_scalar[0], m_vector[0], m_vector[1], m_vector[2]);
		m_valid = 1;
		return 0;
	case 4: // bound trivector
		m_type |= MVI_BOUND_TANGENT_TRIVECTOR;
		/*
		scalar 0: weight
		point 0: point
		*/
		m_scalar[0] = attitude[GRADE3][C3GA_E1_E2_E3];
		m_valid = 1;
		return 0;
	}

	return 0;
}

int mvInt::c3gaRound(const c3ga &X, int grade, const c3ga &attitude, const c3ga &pos, GAIM_FLOAT weight2) {
	if (grade == 1) { // filter out dual spheres
		m_type ^= MVI_DUAL;
		// maybe put a '-' over here: -X.dual()? or adjust attitude, pos?
		// todo...
		return c3gaRound(-X.dual(), 5 - grade, -attitude.dual(), -pos, -1.0 * weight2);
	}

	// compute some basic properties
	c3ga nX;
	const GAIM_FLOAT *c;
	GAIM_FLOAT r = sqrt(fabs(weight2));
	c3ga o(attitude / r), pt1, pt2, v1, v2, v3;
	GAIM_FLOAT sr = r * ((weight2 > 0.0) ? 1.0 : -1.0), n;

	/*
	For all types:
	scalar 0: signed radius
	*/
	m_scalar[0] = sr;

	/*
	For all types:
	scalar 1: signed weight
	*/
	c3ga leoAtt = -0.5 * c3ga::ni * X *c3ga::ni;
	GAIM_FLOAT leoSqWeight = (c3ga::no << leoAtt).norm_b();
	m_scalar[1] = sqrt(fabs(leoSqWeight)) * ((leoSqWeight < 0.0) ? -1.0 : 1.0);

	/*
	For all types:
	point 0: point
	*/
	c = pos[GRADE1];
	if (c[C3GA_NO] != 0.0) {
		m_point[0][0] = c[C3GA_E1] / c[C3GA_NO];
		m_point[0][1] = c[C3GA_E2] / c[C3GA_NO];
		m_point[0][2] = c[C3GA_E3] / c[C3GA_NO];
	}

	switch (grade) {
	case 0:
	case 5:
		m_valid = 0;
		m_type |= MVI_UNKNOWN;
		cprintf("mvInt::c3gaRound(): grade %d rounds do not exist\n", grade);
		return 0;
	case 2: // point pair
		m_type |= MVI_POINT_PAIR;
		/*
		scalar 0: signed radius
		scalar 1: weight
		point 0: center point
		point 1: point 1
		point 2: point 2
		vector 0: ???
		vector 1: attitude
		*/

		n = sqrt(fabs((X << X).scalar()));
		v1 = c3ga::ni << X;
		v2 = n * v1;
		v3 = -v1 << X;

		pt1 = v3 + v2;
		pt2 = v3 - v2;

		nX = attitude.normal() * (2.0 * sr);

		c = nX[GRADE1];
		m_vector[1][0] = ((m_scalar[0] < 0.0) ? -1.0 : 1.0) * c[C3GA_E1];
		m_vector[1][1] = ((m_scalar[0] < 0.0) ? -1.0 : 1.0) * c[C3GA_E2];
		m_vector[1][2] = ((m_scalar[0] < 0.0) ? -1.0 : 1.0) * c[C3GA_E3];

		m_point[1][0] = m_point[0][0] - 0.5 * m_vector[1][0];
		m_point[1][1] = m_point[0][1] - 0.5 * m_vector[1][1];
		m_point[1][2] = m_point[0][2] - 0.5 * m_vector[1][2];

		m_point[2][0] = m_point[0][0] + 0.5 * m_vector[1][0];
		m_point[2][1] = m_point[0][1] + 0.5 * m_vector[1][1];
		m_point[2][2] = m_point[0][2] + 0.5 * m_vector[1][2];

		m_valid = 1;
		return 0;
	case 3: // circle
		m_type |= MVI_CIRCLE;
		/*
		scalar 0: signed radius
		scalar 1: weight
		point 0: center point
		vector 0: normal 
		vector 1: orthogonal to vector 0
		vector 2: orthogonal to vector 0 and vector 1		
		*/
		
		c3gaFactorBivector(o, m_vector[0], m_vector[1], m_vector[2]);

		m_valid = 1;
		return 0;
	case 4: // sphere
		m_type |= MVI_SPHERE;
		/*
		scalar 0: signed radius
		scalar 1: weight
		point 0: center point
		*/
		// temp test: is this weight ok?? (the sign???)
		m_scalar[1] = -(X << (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3 ^ c3ga::ni)).scalar();

		m_valid = 1;
		return 0;
	}

	// todo...

	return 0;
}

int mvInt::c3gaFactorBivector(const c3ga &B, GAIM_FLOAT *normal, GAIM_FLOAT *factor1, GAIM_FLOAT *factor2) {
	// get normal
	const GAIM_FLOAT *c;
	GAIM_FLOAT scale;
	c3ga nl((B << (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3).inverse()).normal());
	c3ga pe1, pe2, rt;

	// get normal
	c = nl[GRADE1];
	if (normal)
		normal[0] = c[C3GA_E1];	normal[1] = c[C3GA_E2];	normal[2] = c[C3GA_E3];

	// set factor 1 and 2 (orthogonal to normal)
	if ((g_state->m_c3gaFactor[0].norm_a() > 0.0) && // user factorization
		(g_state->m_c3gaFactor[1].norm_a() > 0.0)) {
		pe1 = ((g_state->m_c3gaFactor[0] << B) << B.inverse());
		pe2 = ((g_state->m_c3gaFactor[1] << B) << B.inverse());
	}
	else { // auto factorization
		c3gaRve3(rt, nl);
		pe1 = (rt * c3ga::e1 * rt.inverse())(GRADE1);
		pe2 = (rt * c3ga::e2 * rt.inverse())(GRADE1);
	}

	// if the bivector wasn't unit, adjust factors
	scale = (B / (pe1 ^ pe2)).scalar();
	pe1 *= ((scale < 0.0) ? -1.0 : 1.0) * sqrt(fabs(scale));
	pe2 *= sqrt(fabs(scale));

	// set factors
	if (factor1) {
		c = pe1[GRADE1];
		factor1[0] = c[C3GA_E1]; factor1[1] = c[C3GA_E2]; factor1[2] = c[C3GA_E3];
	}
	if (factor2) {
		c = pe2[GRADE1];
		factor2[0] = c[C3GA_E1]; factor2[1] = c[C3GA_E2]; factor2[2] = c[C3GA_E3];
	}

	return 0;
}


