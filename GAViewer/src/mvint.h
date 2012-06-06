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

#ifndef _MV_INT_H_
#define _MV_INT_H_

#include "models.h"
#include "gaincludes.h"

/*
Multivector interpretation.
This class can interpret multivectors from
several models of 3D geometry. These models are:

e3ga: euclidean 3D geometric algebra for 3D Euclidean Geometry
p3ga: projective 4D geometric algebra for 3D Euclidean Geometry
c3ga: conformal 5D geometric algebra for 3D Euclidean Geometry
i2ga: conformal 6D image algebra for '2.5D' image manipulation

First the distinction between blade, versors and general multivector is made.
Blades can be interpreted as objects like lines and planes, versors
as operators like translation, rotation and inversion.
*/

#define MVI_NONE 0
#define MVI_NO_INT 255 /* no interpretation */


#define MVI_BLADE (1 << 8)
#define MVI_VERSOR (1 << 9)
#define MVI_NULL (1 << 10)
#define MVI_DUAL (1 << 11)
//#define MVI_CONSTANT (1 << 12)
#define MVI_UNKNOWN 0

// zero
#define MVI_ZERO (MVI_BLADE + 0)

// euclidean
#define MVI_EUCLIDEAN (MVI_BLADE + 8)
#define MVI_SCALAR (MVI_EUCLIDEAN + 0)
#define MVI_VECTOR (MVI_EUCLIDEAN + 1)
#define MVI_BIVECTOR (MVI_EUCLIDEAN + 2)
#define MVI_TRIVECTOR (MVI_EUCLIDEAN + 3)

// free flat
#define MVI_FREE_FLAT (MVI_BLADE + 16)
#define MVI_FREE_SCALAR (MVI_FREE_FLAT + 0)
#define MVI_FREE_VECTOR (MVI_FREE_FLAT + 1)
#define MVI_FREE_BIVECTOR (MVI_FREE_FLAT + 2)
#define MVI_FREE_TRIVECTOR (MVI_FREE_FLAT + 3)
// bound flat
#define MVI_BOUND_FLAT (MVI_BLADE + 64)
#define MVI_FLAT_POINT (MVI_BOUND_FLAT + 2)
#define MVI_LINE (MVI_BOUND_FLAT + 3)
#define MVI_PLANE (MVI_BOUND_FLAT + 4)
#define MVI_SPACE (MVI_BOUND_FLAT + 5) /* ? */
// bound tangent
#define MVI_BOUND_TANGENT (MVI_BLADE + 32)
#define MVI_BOUND_TANGENT_GRADE0 (MVI_BOUND_TANGENT + 0)
#define MVI_POINT MVI_BOUND_TANGENT_GRADE0
#define MVI_BOUND_TANGENT_VECTOR (MVI_BOUND_TANGENT + 1)
#define MVI_BOUND_TANGENT_BIVECTOR (MVI_BOUND_TANGENT + 2)
#define MVI_BOUND_TANGENT_TRIVECTOR (MVI_BOUND_TANGENT + 3)
// sphere
#define MVI_ROUND (MVI_BLADE + 128)
#define MVI_POINT_PAIR (MVI_ROUND + 2)
#define MVI_CIRCLE (MVI_ROUND + 3)
#define MVI_SPHERE (MVI_ROUND + 4)

#define MVI_BLADE_TYPE_MASK (MVI_EUCLIDEAN + MVI_FREE_FLAT + MVI_BOUND_FLAT + MVI_BOUND_TANGENT + MVI_ROUND)

#define MVI_ROTOR (MVI_VERSOR + 0)
#define MVI_ODD_3D_VERSOR (MVI_VERSOR + 1)

// internal constants:
#define MVINT_NB_POINTS 2
#define MVINT_NB_VECTORS 4
#define MVINT_NB_SCALAR 2

/*
This class stores interpretations of multivectors.
m_type specifies the interpretation. It is a bitwise or
of MVI_XXX values.
Use the  type(), model(), blade() and versor() member functions
to retrieve partial info on the type.

The properties of the multivector interpretation are stored in 
'm_point', 'm_vector' and  'm_scalar'. What is stored where and
how exactly depends on the type of multivector.
*/
class mvInt {
public:
	mvInt();
	mvInt(const mvInt *I);
	mvInt(const e3ga &mv, int creationFlags = 0);
	mvInt(const p3ga &mv, int creationFlags = 0);
	mvInt(const c3ga &mv, int creationFlags = 0);
	mvInt(const c5ga &mv, int creationFlags = 0);
	mvInt(const i2ga &mv, int creationFlags = 0);
	~mvInt();
	void initToNothing();

	int copy(const mvInt *I);

	// interprets a multvector. Return 0 on success, -1 if the multivector can not be interpreted
	int interpret(const e3ga &mv, int creationFlags = 0);
	int interpret(const p3ga &mv, int creationFlags = 0);
	int interpret(const c3ga &mv, int creationFlags = 0);
	int interpret(const c5ga &mv, int creationFlags = 0);
	int interpret(const i2ga &mv, int creationFlags = 0);

	int m_type;
	inline const int type() {return (m_type & 0x7FF);};
	inline const int model() {return (m_type & (7 << 13));};
	inline const int blade() {return ((m_type & MVI_BLADE) != 0);};
	inline const int versor() {return ((m_type & MVI_VERSOR) != 0);};
	inline const int null() {return ((m_type & MVI_NULL) != 0);};
	inline const int dual() {return ((m_type & MVI_DUAL) != 0);};

//	inline const int constant() {return ((m_type & MVI_CONSTANT) != 0);};
//	inline void setConstant() {m_type |= MVI_CONSTANT;}

	// All multivectors are analyzed into points, vectors and scalar,
	// stored in these arrays:
	GAIM_FLOAT m_point[MVINT_NB_POINTS][3]; // vector from the origin to the point
	GAIM_FLOAT m_vector[MVINT_NB_VECTORS][3]; // vectors
	GAIM_FLOAT m_scalar[MVINT_NB_SCALAR];

	int m_valid; // true if the interpretation of the object succeeded


protected:

	int c3gaFreeFlat(const c3ga &X, int grade, const c3ga &ori, GAIM_FLOAT size2); 
	int c3gaBoundFlat(const c3ga &X, int grade, const c3ga &ori, const c3ga &pos, GAIM_FLOAT size2); 
	int c3gaBoundTangent(const c3ga &X, int grade, const c3ga &ori, const c3ga &pos, GAIM_FLOAT size2); 
	int c3gaRound(const c3ga &X, int grade, const c3ga &ori, const c3ga &pos, GAIM_FLOAT size2); 
	// Factors 'B' into factor 1 and factor 2, taking into account possible user factorization (g_state->m_c3gaFactor[0] & g_state->m_c3gaFactor[1])
	// Also returns the unit normal vector. If {normal, factor1, factor2} is NULL, it isn't set
	int c3gaFactorBivector(const c3ga &B, GAIM_FLOAT *normal, GAIM_FLOAT *factor1, GAIM_FLOAT *factor2);

	int p3gaEuclideanSubspace(const p3ga &X, int grade, const p3ga &ori, GAIM_FLOAT size2);
	int p3gaHomogeneousSubspace(const p3ga &X, int grade, const p3ga &ori, const p3ga &pos, GAIM_FLOAT size2);
	// Factors 'B' into factor 1 and factor 2, taking into account possible user factorization (g_state->m_p3gaFactor[0] & g_state->m_p3gaFactor[1])
	// Also returns the unit normal vector. If {normal, factor1, factor2} is NULL, it isn't set
	int p3gaFactorBivector(const p3ga &B, GAIM_FLOAT *normal, GAIM_FLOAT *factor1, GAIM_FLOAT *factor2);

	int m_creationFlags;

};


#endif /* _MV_INT_H_ */
