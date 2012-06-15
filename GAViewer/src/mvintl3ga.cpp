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

int mvInt::interpret(const l3ga &X, int creationFlags /* = 0*/) {
  l3ga I3real(l3ga::e01 ^ l3ga::e02 ^ l3ga::e03);
  l3ga I3ideal(l3ga::e23 ^ l3ga::e31 ^ l3ga::e12);
  l3ga e01(l3ga::e01);
  l3ga e02(l3ga::e02);
  l3ga e03(l3ga::e03);
  l3ga e23(l3ga::e23);
  l3ga e31(l3ga::e31);
  l3ga e12(l3ga::e12);

  const GAIM_FLOAT epsilon = 1e-6; // rather arbitrary limit on fp-noise
  l3ga tmp;

  m_type = 0;
  m_type = MVI_L3GA;

  //TODO: dualize? (copied from mvint[cp]3ga.cpp; why?) 
  

  // check for zero euclidean norm multivectors
  if (X.norm_a() < epsilon) { // *********** zero blade
    m_type |= MVI_ZERO;
    m_valid = 1;
    return 0;
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

    return 0;
  }

  if (type == GA_BLADE) { // ************************ all blades *********************
    GAIM_FLOAT X2 = (X * X).scalar(), weight2;
    switch (grade) {
      case 0: // ******************** scalar
        m_type |= MVI_SCALAR;
        m_scalar[0] = X.scalar();
        break;
      case 1: // ******************** line, screw, kine
        if (fabs(X2) < epsilon) {
          if (fabs(X[GRADE1][L3GA_E01]) < epsilon &&
              fabs(X[GRADE1][L3GA_E02]) < epsilon &&
              fabs(X[GRADE1][L3GA_E03]) < epsilon) {
            m_type |= MVI_IDEAL_LINE;
            /*
            scalar 0: weight
            vector 0: normal/reciprocal direction
            */
            tmp.lcem(X,X);
            m_scalar[0] = sqrt(tmp.scalar());

            m_vector[0][0] = X[GRADE1][L3GA_E23] / m_scalar[0];
            m_vector[0][1] = X[GRADE1][L3GA_E31] / m_scalar[0];
            m_vector[0][2] = X[GRADE1][L3GA_E12] / m_scalar[0];
          }
          else {
            m_type |= MVI_LINE;
            /*
            scalar 0: weight
            point 0: point closest to origin
            vector 0: direction of line
            */
            // 6D-vector = [d, m]
            // direction = d
            // moment = m
            // distance = crossprod(m, d)
            // weight = sqrt(distance^2)
            tmp.lcem(X,X);
            m_scalar[0] = sqrt(tmp.scalar());

            m_vector[0][0] = X[GRADE1][L3GA_E01] / m_scalar[0];
            m_vector[0][1] = X[GRADE1][L3GA_E02] / m_scalar[0];
            m_vector[0][2] = X[GRADE1][L3GA_E03] / m_scalar[0];

            m_point[0][0] = (X[GRADE1][L3GA_E31] * X[GRADE1][L3GA_E03]) - (X[GRADE1][L3GA_E12] * X[GRADE1][L3GA_E02]);
            m_point[0][1] = (X[GRADE1][L3GA_E12] * X[GRADE1][L3GA_E01]) - (X[GRADE1][L3GA_E23] * X[GRADE1][L3GA_E03]);
            m_point[0][2] = (X[GRADE1][L3GA_E23] * X[GRADE1][L3GA_E02]) - (X[GRADE1][L3GA_E31] * X[GRADE1][L3GA_E01]);
          }

          m_valid = 1;
        }
        // TODO: screw motion, kine

      case 2: // ******************** line pencil, skew line pair, 'line tangent', 'dual regulus pencil'
      case 3: // ******************** line bundle/point, fied of lines/plane, regulus, double wheel pencil, ...
      case 4: // ******************** regulus pencil, dual line pair, parabolic linear congruence, "[hyperbolic linear congruence], bundle + field"
      case 5: // ******************** regulus bundle, rotation invariants, translation invariants
      case 6: // ******************** pseudoscalar
      default:
        m_type |= MVI_UNKNOWN;
        m_valid = 0;
        break;
    }
  }
  // TODO: Add interpretation for versors
  else {
    m_type |= MVI_UNKNOWN;
    m_valid = 0;
  }

  return 0;
}
