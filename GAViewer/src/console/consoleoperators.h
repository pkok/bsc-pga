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

#ifndef _CONSOLE_OPERATORS_H_
#define _CONSOLE_OPERATORS_H_

// console binary operators
#define CBO_GP 0 // 'space' (implicit, doesn't exist)
#define CBO_ASSIGNMENT 1 // '='
#define CBO_IGP 2 // '/'
#define CBO_OP 3 // '^'
#define CBO_IP 4 // '.'
#define CBO_SCP 5 // '*'
#define CBO_ADDITION 6 // '+'
#define CBO_SUBTRACTION 7 // '-'
#define CBO_MEET 8 // '&'
#define CBO_JOIN 9 // '|'
#define CBO_EQUAL 10 // '=='
#define CBO_LESS 11 // '<'
#define CBO_GREATER 12 // '>'
#define CBO_LE 13 // '<='
#define CBO_GE 14 // '>='
#define CBO_AND 15 // '&&'
#define CBO_OR 16 // '||'
#define CBO_NE 17 // '!='
#define CBO_NB_OPS 18
#define CBO_MASK 0xFF

// console unary operators (masks)
#define CUO_NEGATION (1 << 8) // '-'
#define CUO_INVERSION (2 << 8) // '!'
#define CUO_REVERSION (4 << 8) // '~'
#define CUO_MASK (0xFF << 8)

#endif /* _CONSOLE_OPERATORS_H_ */
