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

#include "mvint.h"

/*
Multivector interpretation code is spread over multiple files.
e3ga: mvinte3ga.cpp
p3ga: mvintp3ga.cpp
c3ga: mvintc3ga.cpp
i2ga: mvinti2ga.cpp
*/

mvInt::mvInt() {
	initToNothing();
}

mvInt::mvInt(const mvInt *I) {
	initToNothing();
	copy(I);
}

mvInt::mvInt(const e3ga &mv, int creationFlags /*= 0 */) {
	initToNothing();
	interpret(mv, creationFlags);
}

mvInt::mvInt(const p3ga &mv, int creationFlags /*= 0 */) {
	initToNothing();
	interpret(mv, creationFlags);
}

mvInt::mvInt(const c3ga &mv, int creationFlags /*= 0 */) {
	initToNothing();
	interpret(mv, creationFlags);
}

mvInt::mvInt(const c5ga &mv, int creationFlags /*= 0 */) {
	initToNothing();
	interpret(mv, creationFlags);
}

mvInt::mvInt(const i2ga &mv, int creationFlags /*= 0 */) {
	initToNothing();
	interpret(mv, creationFlags);
}

mvInt::~mvInt() {
	initToNothing();
}

void mvInt::initToNothing() {
	int i;
	for (i = 0; i < MVINT_NB_POINTS; i++)
		m_point[i][0] = m_point[i][1] = m_point[i][2] = (GAIM_FLOAT)0.0;
	for (i = 0; i < MVINT_NB_VECTORS; i++)
		m_vector[i][0] = m_vector[i][1] = m_vector[i][2] = (GAIM_FLOAT)0.0;
	for (i = 0; i < MVINT_NB_SCALAR; i++)
		m_scalar[i] = (GAIM_FLOAT)0.0;
	m_type = MVI_NONE;
	m_valid = 0;
	m_creationFlags = 0;
}

int mvInt::copy(const mvInt *I) {
	int i;
	for (i = 0; i < MVINT_NB_POINTS; i++)
		memcpy(m_point[i], I->m_point[i], sizeof(m_point[i]));
	for (i = 0; i < MVINT_NB_VECTORS; i++)
		memcpy(m_vector[i], I->m_vector[i], sizeof(m_vector[i]));
	for (i = 0; i < MVINT_NB_SCALAR; i++)
		m_scalar[i] = I->m_scalar[i];
	m_type = I->m_type;
	return 0;
}

