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

double factorize_blade(const l3ga &B, int grade, l3ga (&factors)[7]);
int is_parallel(l3ga &a, l3ga &b, double epsilon);

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
  l3ga tmp, factors[7];
  int i;
  double s, x, y, z;
  int null_vectors = 0;
  int ideal_lines = 0;

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
    s = factorize_blade(X, grade, factors);
    switch (grade) {
      case 0: // ******************** scalar
        m_type |= MVI_SCALAR;
        m_scalar[0] = X.scalar();
        break;
      case 1: // ******************** line, screw, kine
        //if (fabs(X2) < epsilon) {
          if (fabs(X[GRADE1][L3GA_E01]) < epsilon &&
              fabs(X[GRADE1][L3GA_E02]) < epsilon &&
              fabs(X[GRADE1][L3GA_E03]) < epsilon) {
            m_type |= MVI_IDEAL_LINE;
            printf("ideal line\n");
            /*
            scalar 0: weight
            vector 0: normal/reciprocal direction
            */
            //tmp.lcem(X,X);
            //m_scalar[0] = sqrt(tmp.scalar());
            m_scalar[0] = sqrt(X[GRADE1][L3GA_E23] * X[GRADE1][L3GA_E23] + X[GRADE1][L3GA_E31] * X[GRADE1][L3GA_E31] + X[GRADE1][L3GA_E12] * X[GRADE1][L3GA_E12]);

            m_vector[0][0] = X[GRADE1][L3GA_E23] / m_scalar[0];
            m_vector[0][1] = X[GRADE1][L3GA_E31] / m_scalar[0];
            m_vector[0][2] = X[GRADE1][L3GA_E12] / m_scalar[0];
          }
          else {
            if (fabs(X2) < epsilon) {
              m_type |= MVI_LINE;
              printf("line\n");
              /*
              scalar 0: weight
              point 0: point closest to origin
              vector 0: direction of line
              */


              m_scalar[0] = sqrt(X[GRADE1][L3GA_E01] * X[GRADE1][L3GA_E01] + X[GRADE1][L3GA_E02] * X[GRADE1][L3GA_E02] + X[GRADE1][L3GA_E03] * X[GRADE1][L3GA_E03]);
            }
            else {
              m_type |= MVI_SCREW;
              printf("screw\n");
              /*
              scalar 0: weight
              scalar 1: pitch (translation distance over 1 rotation)
              scalar 2: rotation direction; -1 is clockwise, 1 is ccw
              point 0: point closest to origin
              vector 0: direction of line
              */


              m_scalar[0] = sqrt(lcem(X, X).scalar());
              m_scalar[1] = sqrt(X[GRADE1][L3GA_E01] * X[GRADE1][L3GA_E01] + X[GRADE1][L3GA_E02] * X[GRADE1][L3GA_E02] + X[GRADE1][L3GA_E03] * X[GRADE1][L3GA_E03])/sqrt(X[GRADE1][L3GA_E23] * X[GRADE1][L3GA_E23] + X[GRADE1][L3GA_E31] * X[GRADE1][L3GA_E31] + X[GRADE1][L3GA_E12] * X[GRADE1][L3GA_E12]);
              m_scalar[2] = -(X[GRADE1][L3GA_E23] + X[GRADE1][L3GA_E31] + X[GRADE1][L3GA_E12]) / sqrt(X[GRADE1][L3GA_E23] * X[GRADE1][L3GA_E23] + X[GRADE1][L3GA_E31] * X[GRADE1][L3GA_E31] + X[GRADE1][L3GA_E12] * X[GRADE1][L3GA_E12]);
              if (m_scalar[2] < -epsilon) {
                m_scalar[2] = -1;
              }
              else if (m_scalar[2] > epsilon) {
                m_scalar[2] = 1;
              }
              else {
                m_scalar[2] = 0;
              }
            }
            // 6D-vector = [d, m]
            // direction = d
            // moment = m
            // distance = crossprod(m, d)
            // weight = sqrt(distance^2)

            m_vector[0][0] = X[GRADE1][L3GA_E01] / m_scalar[0];
            m_vector[0][1] = X[GRADE1][L3GA_E02] / m_scalar[0];
            m_vector[0][2] = X[GRADE1][L3GA_E03] / m_scalar[0];

            m_point[0][0] = ((X[GRADE1][L3GA_E12] * m_vector[0][1]) - (X[GRADE1][L3GA_E31] * m_vector[0][2])) / m_scalar[0];
            m_point[0][1] = ((X[GRADE1][L3GA_E23] * m_vector[0][2]) - (X[GRADE1][L3GA_E12] * m_vector[0][0])) / m_scalar[0];
            m_point[0][2] = ((X[GRADE1][L3GA_E31] * m_vector[0][0]) - (X[GRADE1][L3GA_E23] * m_vector[0][1])) / m_scalar[0];

          }

          m_valid = 1;
        //}
        // TODO: screw motion, kine
        //else {
        if (!m_valid) {
          m_type |= MVI_UNKNOWN;
          m_valid = 0;
        }
        break;
      case 2: // ******************** line pencil, skew line pair, 'line tangent', 'dual regulus pencil'
        for (i = 0; i < grade && factors[i].grade(); ++i) {
          if (fabs((factors[i] << factors[i]).scalar()) < epsilon) {
            ++null_vectors;
          }
          if (fabs(factors[i][GRADE1][L3GA_E01]) < epsilon &&
              fabs(factors[i][GRADE1][L3GA_E02]) < epsilon &&
              fabs(factors[i][GRADE1][L3GA_E03]) < epsilon) {
            ++ideal_lines;
          }
        } 
        if (null_vectors == 2) { 
          if (fabs(X2) < epsilon) {
            // Detect if lines are parallel.
            // Line L1=(a:b) and L2=(x:y) are parallel when:
            // c = a[i] / x[i]
            if (ideal_lines == null_vectors) {
              m_type |= MVI_IDEAL_LINE_PENCIL;
              printf("pencil of ideal lines\n");
              /*
              scalar 0: weight
              vector 0: normal
              vector 1: orthogonal to vector 0 and 2
              vector 2: orthogonal to vector 0 and 1
              */
              m_scalar[0] = s;

              printf("f1: %s\nf2: %s\n", factors[0].string(), factors[1].string());
              z = sqrt((factors[0][GRADE1][L3GA_E23] * factors[0][GRADE1][L3GA_E23]) + (factors[0][GRADE1][L3GA_E31] * factors[0][GRADE1][L3GA_E31]) + (factors[0][GRADE1][L3GA_E12] * factors[0][GRADE1][L3GA_E12]));
              m_vector[1][0] = -factors[0][GRADE1][L3GA_E23] / z;
              m_vector[1][1] = -factors[0][GRADE1][L3GA_E31] / z;
              m_vector[1][2] = -factors[0][GRADE1][L3GA_E12] / z;

              z = sqrt((factors[1][GRADE1][L3GA_E23] * factors[1][GRADE1][L3GA_E23]) + (factors[1][GRADE1][L3GA_E31] * factors[1][GRADE1][L3GA_E31]) + (factors[1][GRADE1][L3GA_E12] * factors[1][GRADE1][L3GA_E12]));
              m_vector[2][0] = factors[1][GRADE1][L3GA_E23] / z;
              m_vector[2][1] = factors[1][GRADE1][L3GA_E31] / z;
              m_vector[2][2] = factors[1][GRADE1][L3GA_E12] / z;

              m_vector[0][0] = (m_vector[1][1] * m_vector[2][2]) - (m_vector[1][2] * m_vector[2][1]);
              m_vector[0][1] = (m_vector[1][2] * m_vector[2][0]) - (m_vector[1][0] * m_vector[2][2]);
              m_vector[0][2] = (m_vector[1][0] * m_vector[2][1]) - (m_vector[1][1] * m_vector[2][0]);
            }
            else if (is_parallel(factors[0], factors[1], epsilon)) {
              m_type |= MVI_RULED_PLANE;
              printf("ruled plane\n");
              /*
              scalar 0: weight;
              point 0: point on plane closest to chosen origin
              vector 0: normal
              vector 1: line direction
              vector 2: orthogonal to vector 0 and 1
              */
              m_scalar[0] = s;

              m_point[0][0] = sqrt(fabs(s)/2.0) * 0.5 * (factors[0][GRADE1][L3GA_E23] + factors[1][GRADE1][L3GA_E23]);
              m_point[0][1] = sqrt(fabs(s)/2.0) * 0.5 * (factors[0][GRADE1][L3GA_E31] + factors[1][GRADE1][L3GA_E31]);
              m_point[0][2] = -sqrt(fabs(s)/2.0) * 0.5 * (factors[0][GRADE1][L3GA_E12] + factors[1][GRADE1][L3GA_E12]);

              /*
              z = sqrt((factors[1][GRADE1][L3GA_E23] * factors[1][GRADE1][L3GA_E23]) + (factors[1][GRADE1][L3GA_E31] * factors[1][GRADE1][L3GA_E31]) + (factors[1][GRADE1][L3GA_E12] * factors[1][GRADE1][L3GA_E12]));
              m_point[0][0] = 0.5 * (factors[0][GRADE1][L3GA_E23] + factors[1][GRADE1][L3GA_E23] / z);
              m_point[0][1] = 0.5 * (factors[0][GRADE1][L3GA_E31] + factors[1][GRADE1][L3GA_E31] / z);
              m_point[0][2] = 0.5 * (factors[0][GRADE1][L3GA_E12] + factors[1][GRADE1][L3GA_E12] / z);
              */

              z = sqrt((factors[0][GRADE1][L3GA_E01] * factors[0][GRADE1][L3GA_E01]) + (factors[0][GRADE1][L3GA_E02] * factors[0][GRADE1][L3GA_E02]) + (factors[0][GRADE1][L3GA_E03] * factors[0][GRADE1][L3GA_E03]));
              m_vector[1][0] = -factors[0][GRADE1][L3GA_E01] / z;
              m_vector[1][1] = -factors[0][GRADE1][L3GA_E02] / z;
              m_vector[1][2] = -factors[0][GRADE1][L3GA_E03] / z;

              z = sqrt((factors[0][GRADE1][L3GA_E23] * factors[0][GRADE1][L3GA_E23]) + (factors[0][GRADE1][L3GA_E31] * factors[0][GRADE1][L3GA_E31]) + (factors[0][GRADE1][L3GA_E12] * factors[0][GRADE1][L3GA_E12]));
              if (fabs(z) < epsilon) {
                z = sqrt((factors[1][GRADE1][L3GA_E01] * factors[1][GRADE1][L3GA_E01]) + (factors[1][GRADE1][L3GA_E02] * factors[1][GRADE1][L3GA_E02]) + (factors[1][GRADE1][L3GA_E03] * factors[1][GRADE1][L3GA_E03]));
                if (fabs(z) >= epsilon) {
                  m_vector[1][0] = -factors[1][GRADE1][L3GA_E01] / z;
                  m_vector[1][1] = -factors[1][GRADE1][L3GA_E02] / z;
                  m_vector[1][2] = -factors[1][GRADE1][L3GA_E03] / z;
                }

                z = sqrt((factors[1][GRADE1][L3GA_E23] * factors[1][GRADE1][L3GA_E23]) + (factors[1][GRADE1][L3GA_E31] * factors[1][GRADE1][L3GA_E31]) + (factors[1][GRADE1][L3GA_E12] * factors[1][GRADE1][L3GA_E12]));
                m_vector[2][0] = factors[1][GRADE1][L3GA_E23] / z;
                m_vector[2][1] = factors[1][GRADE1][L3GA_E31] / z;
                m_vector[2][2] = factors[1][GRADE1][L3GA_E12] / z;
              }
              else {
                m_vector[2][0] = factors[0][GRADE1][L3GA_E23] / z;
                m_vector[2][1] = factors[0][GRADE1][L3GA_E31] / z;
                m_vector[2][2] = factors[0][GRADE1][L3GA_E12] / z;
              }

              m_vector[0][0] = (m_vector[1][1] * m_vector[2][2]) - (m_vector[1][2] * m_vector[2][1]);
              m_vector[0][1] = (m_vector[1][2] * m_vector[2][0]) - (m_vector[1][0] * m_vector[2][2]);
              m_vector[0][2] = (m_vector[1][0] * m_vector[2][1]) - (m_vector[1][1] * m_vector[2][0]);

              if (m_vector[1][0] != m_vector[1][0]) printf("v1 is NaN\n");
              if (m_vector[2][0] != m_vector[2][0]) printf("v2 is NaN; z is %2f\n", z);
              if (m_vector[0][0] != m_vector[0][0]) printf("v0 is NaN\n");
            }
            else {
              m_type |= MVI_LINE_PENCIL;
              printf("line pencil\n");
              /*
              scalar 0: weight
              point 0: center
              vector 0: normal
              vector 1: orthogonal to vector 0 and 2
              vector 2: orthogonal to vector 0 and 1
              */
              m_scalar[0] = s;

              // point of intersection is:
              //   cross(factor1_m, factor2_m) / dot(factor1_d, factor2_m)
              z = (factors[0][GRADE1][L3GA_E01] * factors[1][GRADE1][L3GA_E23]) + (factors[0][GRADE1][L3GA_E02] * factors[1][GRADE1][L3GA_E31]) + (factors[0][GRADE1][L3GA_E03] * factors[1][GRADE1][L3GA_E12]);

              m_point[0][0] = ((factors[0][GRADE1][L3GA_E12] * factors[1][GRADE1][L3GA_E31]) - (factors[0][GRADE1][L3GA_E31] * factors[1][GRADE1][L3GA_E12])) / z;
              m_point[0][1] = ((factors[0][GRADE1][L3GA_E23] * factors[1][GRADE1][L3GA_E12]) - (factors[0][GRADE1][L3GA_E12] * factors[1][GRADE1][L3GA_E23])) / z;
              m_point[0][2] = ((factors[0][GRADE1][L3GA_E31] * factors[1][GRADE1][L3GA_E23]) - (factors[0][GRADE1][L3GA_E23] * factors[1][GRADE1][L3GA_E31])) / z;

              // normal to direction is:
              //    cross(factor1_d, factor2_d)
              m_vector[0][0] = ((factors[0][GRADE1][L3GA_E02] * factors[1][GRADE1][L3GA_E03]) - (factors[0][GRADE1][L3GA_E03] * factors[1][GRADE1][L3GA_E02])) / z;
              m_vector[0][1] = ((factors[0][GRADE1][L3GA_E03] * factors[1][GRADE1][L3GA_E01]) - (factors[0][GRADE1][L3GA_E01] * factors[1][GRADE1][L3GA_E03])) / z;
              m_vector[0][2] = ((factors[0][GRADE1][L3GA_E01] * factors[1][GRADE1][L3GA_E02]) - (factors[0][GRADE1][L3GA_E02] * factors[1][GRADE1][L3GA_E01])) / z;

              z = sqrt((m_vector[0][0] * m_vector[0][0]) + (m_vector[0][1] * m_vector[0][1]) + (m_vector[0][2] * m_vector[0][2]));
              m_vector[0][0] /= z;
              m_vector[0][1] /= z;
              m_vector[0][2] /= z;

              z = sqrt((factors[0][GRADE1][L3GA_E23] * factors[0][GRADE1][L3GA_E23]) + (factors[0][GRADE1][L3GA_E31] * factors[0][GRADE1][L3GA_E31]) + (factors[0][GRADE1][L3GA_E12] * factors[0][GRADE1][L3GA_E12]));
              m_vector[1][0] = factors[0][GRADE1][L3GA_E23] / z;
              m_vector[1][1] = factors[0][GRADE1][L3GA_E31] / z;
              m_vector[1][2] = factors[0][GRADE1][L3GA_E12] / z;

              m_vector[2][0] = (m_vector[0][1] * m_vector[1][2]) - (m_vector[0][2] * m_vector[1][1]);
              m_vector[2][1] = (m_vector[0][2] * m_vector[1][0]) - (m_vector[0][0] * m_vector[1][2]);
              m_vector[2][2] = (m_vector[0][0] * m_vector[1][1]) - (m_vector[0][1] * m_vector[1][0]);
            }
          }
          else {
            m_type |= MVI_LINE_PAIR;
            printf("line pair\n");
            /*
            scalar 0: weight;
            scalar 1: signed radius(? is that meaningful? --> not set!)
            point 0: point closest to origin of line 1
            vector 0: direction of line 1
            point 1: point closest to origin of line 2
            vector 1: direction of line 2
            */
            mvInt l1, l2, _tmp;
            l1.interpret(factors[0]);
            l2.interpret(factors[1]);
            if (l1.m_type & MVI_IDEAL) {
              m_type |= MVI_IDEAL_LINE_PAIR;
              /*
              scalar 0: weight;
              scalar 1: signed radius(? is that meaningful? --> not set!)
              vector 0: normal to the ideal line
              point 1: point closest to origin of the real line
              vector 1: direction of the real line
              */

              // TODO: Better name for this blade.
              // TODO: second, real line has always the same orientation.
            }
            else if (l2.m_type & MVI_IDEAL) {
              m_type |= MVI_IDEAL_LINE_PAIR;
              _tmp = l1;
              l1 = l2;
              l2 = _tmp;
            }

            m_scalar[0] = s;
            m_point[0][0] = l1.m_point[0][0];
            m_point[0][1] = l1.m_point[0][1];
            m_point[0][2] = l1.m_point[0][2];
            m_vector[0][0] = l1.m_vector[0][0];
            m_vector[0][1] = l1.m_vector[0][1];
            m_vector[0][2] = l1.m_vector[0][2];

            m_point[1][0] = l2.m_point[0][0];
            m_point[1][1] = l2.m_point[0][1];
            m_point[1][2] = l2.m_point[0][2];
            m_vector[1][0] = l2.m_vector[0][0];
            m_vector[1][1] = l2.m_vector[0][1];
            m_vector[1][2] = l2.m_vector[0][2];
          }
        }
        /*
        else if (null_vectors == 1) {
          // line tangent
        }
        else if (null_vectors == 0) {
          // dual regulus pencil?
        }
        */
        else {
          m_type |= MVI_UNKNOWN;
          printf("grade 2 unknown; X2: %e; f0: %s; f1: %s\n", X2, factors[0].string(), factors[1].string());
          m_valid = 0;
        }
        break;
      case 3: // ******************** line bundle/point, fied of lines/plane, regulus, double wheel pencil, ...
      case 4: // ******************** regulus pencil, dual line pair, parabolic linear congruence, "[hyperbolic linear congruence], bundle + field"
      case 5: // ******************** regulus bundle, rotation invariants, translation invariants
      case 6: // ******************** pseudoscalar
      default:
        m_type |= MVI_UNKNOWN;
        printf("grade >2 unknown\n");
        m_valid = 0;
        break;
    }
  }
  // TODO: Add interpretation for versors
  else {
    m_type |= MVI_UNKNOWN;
    printf("unknown versor\n");
    m_valid = 0;
  }

  return 0;
}


// According to factorization algorithm in Dorst et al., p.535.
double factorize_blade(const l3ga &B, int grade, l3ga (&factors)[7]) {
  static const int num_basis_blades[] = {1, 6, 15, 20, 15, 6, 1};
  static const l3ga b[6] = {l3ga::e01, l3ga::e23, l3ga::e02, l3ga::e31, l3ga::e03, l3ga::e12};
  l3ga terminal = l3ga(1, 0.0);
  int k = grade, K = 1 << k;
  int basis_blades = num_basis_blades[k];
  double s = lcem(B, B).scalar();
  l3ga Bc = B / s;
  l3ga fi;
  l3ga E;
  l3ga e[6];
  l3ga tmp1, tmp2;
  int i = 0, max_i = 0, j = 0;
  double coordinates[20] = {0};

  if (k < 0) {
    // B is not an n-vector.
    return 0;
  }

  factors[k] = terminal;

  // If B is scalar, then we're quickly finished.
  if (k == 0) {
    factors[0] = B;
  }
  else {
    // Find the basis blade E of B with the largest coordinate.
    for (i = 0; i < basis_blades; ++i) {
      if (fabs(B[K][max_i]) < fabs(B[K][i])) {
        max_i = i;
      }
    }
    coordinates[max_i] = B[K][max_i];
    E.set(K, coordinates);

    // Determine the k basis vectors e[i] that span E.
    for (i = 0; (i < 6) && (j < k); ++i) {
      tmp1.lcem(b[i], E);
      // if b[i] is in E, add b[i] to e.
      if (tmp1.grade() > 0 || fabs(tmp1.scalar()) >= 1e-6) {
        e[j++] = b[i];
      }
    }

    // For all but one of the basis vectors e[i] of E:
    for (i = 0; i < (k - 1); ++i) {
      // Project e[i] onto Bc
      tmp1.scpem(B, B.reverse());
      if (fabs(tmp1.scalar()) > 0.0) {
        tmp1.set(GRADE0, (1.0/tmp1.scalar()));
      }
      tmp1.gpem(Bc, tmp1);
      tmp2.lcem(e[i], Bc);
      fi.gpem(tmp2, tmp1);
      // Normalize fi. Add it to the list of factors.
      tmp1.lcem(fi, fi);
      factors[i].gpem(fi, l3ga(1.0 / sqrt(tmp1.scalar())));
      // Update Bc
      tmp1.scpem(fi, fi.reverse());
      tmp1.gpem(fi, l3ga(1.0 / tmp1.scalar()));
      Bc.lcem(tmp1, Bc);
    }
    factors[k - 1] = Bc;
  }
  return s;
}

int is_parallel(l3ga &a, l3ga &b, double epsilon) {
  GAIM_FLOAT c_e01 = a[GRADE1][L3GA_E01] / b[GRADE1][L3GA_E01],
             c_e02 = a[GRADE1][L3GA_E02] / b[GRADE1][L3GA_E02],
             c_e03 = a[GRADE1][L3GA_E03] / b[GRADE1][L3GA_E03];
  int e01is0 = (fabs(a[GRADE1][L3GA_E01]) < epsilon) && (fabs(b[GRADE1][L3GA_E01]) < epsilon);
  int e02is0 = (fabs(a[GRADE1][L3GA_E02]) < epsilon) && (fabs(b[GRADE1][L3GA_E02]) < epsilon);
  int e03is0 = (fabs(a[GRADE1][L3GA_E03]) < epsilon) && (fabs(b[GRADE1][L3GA_E03]) < epsilon);

  if ((e01is0 && e02is0) || (e01is0 && e03is0) || (e02is0 && e03is0)) {
    return 1;
  }
  else if (e01is0) {
    return fabs(c_e02 - c_e03) < epsilon;
  }
  else if (e02is0) {
    return fabs(c_e01 - c_e03) < epsilon;
  }
  else if (e03is0) {
    return fabs(c_e01 - c_e02) < epsilon;
  }
  return (fabs(c_e01 - c_e02) < epsilon) 
    && (fabs(c_e02 - c_e03) < epsilon) 
    && (fabs(c_e03 - c_e01) < epsilon);
}
