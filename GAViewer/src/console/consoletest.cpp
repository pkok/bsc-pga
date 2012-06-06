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

#include "../state.h"
#include "../osdep.h"
#include "consolescope.h"
#include "consolestatement.h"
#include "console.h"
#include "consolevariable.h"
#include "../object.h"

// a = e1, dynamic(b = a ^ e2;); dynamic(for(i = 2; i < 12; i = i + 1) {o[i] = green(alpha(a . e1 ^ e2 i, (i - 1) / 11));});

int consoleTest3() {
	int i;

//	g_state->consoleSourceDirRead("e:/ga/gaviewer/g_files");


//	const char *callStr = "for (;;) {break;}";
//	const char *callStr = "x = origin(); currentOrigin = 0; y = origin(); currentOrigin = 3; z = origin(); ";
//	const char *callStr = "x = origin(); ";
	const char *callStr = "x = go; ";
	consoleStatement *stmt;
	consoleVariable *cv;

	for (i = 0; i < 10000; i++) {
		stmt = NULL;
		stmt = consoleParse(callStr);
		if (stmt != NULL) {
			cv = stmt->execute(g_state->m_globalScope);
			
			if (cv) delete cv;
		}
		if (stmt) delete stmt;
	}



	return 0;
}


int consoleTest2() {
	const char *intersectStr = 
		"function intersect(c3ga arg1, c3ga arg2) {"
		"return (dual(arg1) . arg2);"
		"}";

	const char *ifElseStr = 
		"function max(a, b) {"
		"if (norm(a) > norm(b)) {return a;} else { return b;};"
		"};"
		"function min(a, b) {"
		"if (norm(a) < norm(b)) {return a;} else {return b;};"
		"};";

	const char *forStr = 
		"function myPow(a, n) {"
		"r = 1;"
		"for (c = 0; c < n; c = c + 1) {r = r * a;};"
		"return r;"
		"};";

	const char *whileStr = 
		"function mod(a, n) {"
		"if (n == 0) return 0;"
		"if (a n < 0) {m = -1; n = -n;} else {m = 1;};"
		"while (abs(a) > abs(n)) a = a - n;"
		"return m  * a;"
		"};";



	consoleStatement *stmt;
	consoleVariable *cv;
	stmt = NULL;
	stmt = consoleParse(whileStr);
	if (stmt != NULL) {
		cv = stmt->execute(g_state->m_globalScope);
		if (cv) delete cv;
	}

//	const char *callStr = "i = intersect(e1 ^ e2 ^ e3 ^ ni, (e1+e2) ^ e3 ^ ni);";
//	const char *callStr = "p = c3ga_point(e1) ^ c3ga_point(e2) ^ c3ga_point(e3) ^ ni; l = c3ga_point(e1+e2) ^ c3ga_point(e3) ^ ni; i = intersect(p, l);";
//	const char *callStr = "ma = max(2, 1), mi = min(2, 1),";
//	const char *callStr = "a = myPow(2, 3)";
	const char *callStr = "a = mod(10, -8)";
//	const char *callStr = "e1 ^ e2 ^ ni;";

	double t = u_timeGet();

	int i;
	for (i = 0; i < 10000; i++) {
		stmt = NULL;
		stmt = consoleParse(callStr);
		if (stmt != NULL) {
			cv = stmt->execute(g_state->m_globalScope);
			if (cv) delete cv;
		}
		if (stmt) delete stmt;
	}

	t = u_timeGet() - t;
	printf("t/l = %e; t: %e\n", t / i, t);

	return 0;

}

int consoleTest() {

	/*int x = + + + +1;
	int y = + +x + 1;
	printf("y = %d\n", y); return 0;*/

//	const char *str = "\t       a = ba() + (ca) + dabra + 12345e10 + 1 + ++- 2 * 2.1 * .01e-3 \n 123";

	const char *str1 = "a = b +- c *+ dual;";
	const char *str2 = "a=b+-+-c;";
	const char *str3 = "a;";
	const char *str4 = "a = (b c) (d e);";
	const char *str5 = "a = 1.0; a = 2.0;";
	const char *str6 = "e1 ^ e2 ^ ni ^ no,";
	const char *str7 = "a = e1+e2^e3; print(a)";
	const char *str8 = "a = 1 + e1 + e0 + ni";
	const char *str9 = "cmd(\"fgcolor 1.0 2.0 3.0 4.0\")";
	const char *str10 = "e1 - 2 e2 - e3;";
	const char *str11 = "a = e1; b = ::a";
	const char *returnStr = "return e1;";
	const char *funcStr = 
		"function intersect(c3ga arg1, c3ga arg2) {"
		"return dual(arg1) . arg; "
		"}";

	// return dual(arg1) . arg;

	const char *str = funcStr;

	// todo: some kind of error handling  // reporting

	double t = u_timeGet();

	consoleStatement *stmt;
	consoleVariable *cv;
	int i;
	for (i = 0; i < 1; i++) {
		stmt = NULL;
//		printf("Iter %d ", i);
		stmt = consoleParse(str);
		if (stmt == NULL) continue;
		printf("Exec\n");
		cv = stmt->execute(g_state->m_globalScope);
		if (cv) delete cv;
		delete stmt;
	}

	t = u_timeGet() - t;
	printf("t/l = %e; t: %e\n", t / i, t);

	/*consoleParseSetInputBuf(str, strlen(str));

	printf("Input: '%s'\n", str);

	while (consoleParselex() != ENDOFFILE);*/





	return 0;
}


/*
int func() {
	int a, b, c, d;
	a = 1;
	b = 2;
	c = 3;
	d = 4;
	//a(b);

	int r = (a = b) + (c = d);


	return 0;
}
*/
