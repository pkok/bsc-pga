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

#include <iostream>

#include "../state.h"
#include "../mvint.h"
#include "console.h"
#include "consolefunction.h"
#include "consoleoperators.h"
//#include "consoleparse.h"
#include "consolescope.h"
#include "consolestatement.h"
#include "consolevariable.h"

int consoleFreeCvList(consoleVariable *cv, consoleVariable *exempt = NULL);

// important: adjust when new models are introduced...
static inline int model(int v) {
	return v & (MVI_E3GA | MVI_P3GA | MVI_C3GA | MVI_C5GA | MVI_I2GA | CVF_ANY_MODEL);
}

static inline int compareModel(int m1, int m2) {
	if ((m1 & CVF_ANY_MODEL) || (m2 & CVF_ANY_MODEL)) return 1;
	else return (m1 == m2);
}

static inline int side(int v) {
	return v & (CVF_RHS | CVF_LHS);
}

consoleVariable *consoleExecUnaryFunc(consoleScope *s, const std::string &name, consoleVariable*cv) {
	// temporarily cut the list at 'cv'
	consoleVariable *cvNext = cv->next();
	cv->next(NULL);

	// execute function
	cv = consoleExecFunc(s, name, cv);

	// restore the list
	cv->next(cvNext);

	return cv;
}


consoleVariable *consoleExecFunc(consoleScope *s_in, const std::string &name, consoleVariable*cv) {
	int argType[maxConsoleFuncArg];
	int nbArg = 0, err, i;
	consoleVariable *cvTmp;
	const consoleFunc *f;
	consoleVariable *arg[maxConsoleFuncArg];
	consoleVariable **cvPtr, *cvCast, *cvNext;

	/*cvNext = cv;
	while (cvNext) {
		cvNext = cvNext->next();
	}*/

	// collect point and type of argument into arrays
	cvTmp = cv;
	while (cvTmp) {
		arg[nbArg] = cvTmp;
		argType[nbArg] = cvTmp->model() | cvTmp->lhs() | cvTmp->rhs();
		nbArg++;
		cvTmp = cvTmp->next();
	}

	// find best matching function
	if (err = s_in->lookupFunction(name, 0, nbArg, arg, argType, &f)) { // 0 for not global (todo: not possible to force global func?)
		cprintf("Error: no function '%s' found that matches the arguments\n", name.c_str());
		consoleFreeCvList(cv);
		return (consoleVariable*)consoleVariableScalar("", 0.0);
	}

	// coerce arguments if necessary
	cvPtr = &cv;
	for (i = 0; i < nbArg; i++) {
		if (f->arg[i] & CVF_ANY_MODEL) {
			cvPtr = &(arg[i]->m_next);
			continue;
		}
		if (model(argType[i]) != model(f->arg[i])) {
			// cut list
			cvNext = arg[i]->next();
			arg[i]->next(NULL);

			// coerce
			if (model(f->arg[i]) == MVI_E3GA) {
				if (!(arg[i]->e().norm_a() - arg[i]->e()(GRADE0).norm_a() < 10e-6)) {
					if (!s_in->supressWarnings()) {
						if (s_in->globalScope())
							cprintf("Coerced '%s' to e3ga\n", arg[i]->name().c_str());
						else cprintf("Coerced '%s' to e3ga (in function %s)\n", arg[i]->name().c_str(), s_in->functionName().c_str());
					}
				}
				cvCast = consoleExecFunc(s_in, "cast_e3ga", arg[i]);	
			}
			else if (model(f->arg[i]) == MVI_P3GA) {
				if (!(arg[i]->e().norm_a() - arg[i]->e()(GRADE0).norm_a() < 10e-6)) {
					if (!s_in->supressWarnings()) {
						if (s_in->globalScope())
							cprintf("Coerced '%s' to p3ga\n", arg[i]->name().c_str());
						else cprintf("Coerced '%s' to p3ga (in function %s)\n", arg[i]->name().c_str(), s_in->functionName().c_str());
					}
				}
				cvCast = consoleExecFunc(s_in, "cast_p3ga", arg[i]);
			}
			else if (model(f->arg[i]) == MVI_C3GA) {
				if (!(arg[i]->e().norm_a() - arg[i]->e()(GRADE0).norm_a() < 10e-6)) {
					if (!s_in->supressWarnings()) {
						if (s_in->globalScope())
							cprintf("Coerced '%s' to c3ga\n", arg[i]->name().c_str());
						else cprintf("Coerced '%s' to c3ga (in function %s)\n", arg[i]->name().c_str(), s_in->functionName().c_str());
					}
				}

				cvCast = consoleExecFunc(s_in, "cast_c3ga", arg[i]);
			}
			else if (model(f->arg[i]) == MVI_C5GA) {
				if (!(arg[i]->e().norm_a() - arg[i]->e()(GRADE0).norm_a() < 10e-6)) {
					if (!s_in->supressWarnings()) {
						if (s_in->globalScope())
							cprintf("Coerced '%s' to c5ga\n", arg[i]->name().c_str());
						else cprintf("Coerced '%s' to c5ga (in function %s)\n", arg[i]->name().c_str(), s_in->functionName().c_str());
					}
				}

				cvCast = consoleExecFunc(s_in, "cast_c5ga", arg[i]);
			}
			else if (model(f->arg[i]) == MVI_I2GA) {
				if (!(arg[i]->e().norm_a() - arg[i]->e()(GRADE0).norm_a() < 10e-6)) {
					if (!s_in->supressWarnings()) {
						if (s_in->globalScope())
							cprintf("Coerced '%s' to i2ga\n", arg[i]->name().c_str());
						else cprintf("Coerced '%s' to i2ga (in function %s)\n", arg[i]->name().c_str(), s_in->functionName().c_str());
					}
				}

				cvCast = consoleExecFunc(s_in, "cast_i2ga", arg[i]);
			}
			else {
				if (!s_in->supressErrors()) {
					cprintf("Coerce '%s' failure!\n", arg[i]->name().c_str());
				}
				cvCast = (consoleVariable*)consoleVariableScalar("", 0.0);
			}

			// restore list
			*cvPtr = arg[i] = cvCast;
			cvCast->next(cvNext);
		}

		cvPtr = &(arg[i]->m_next);
	}


	// execute function (call style depends on user or predefined function)
	consoleVariable *result = NULL;
	if (f->funcPtr) { // predefined function
		result = f->funcPtr(s_in, arg);
	}
	else if (f->funcStmt) { // user function (or batch)
		if (f->funcStmt->function()) { // function
			// create a new scope 
			consoleScope *s = new consoleScope(name, s_in);
			// exec
			result = f->funcStmt->execute(s, arg); // todo: temp s_in
			//  delete
			delete s;
		}
		else { // batch
			if (!s_in->globalScope()) {
				cprintf("Error, in function '%s': batch '%s' can only be called in global scope\n", s_in->functionName().c_str(), f->name);
				result = new consoleVariable("", e3ga(0.0));
			}
			else {
				// set batch name
				std::string oldFunctionName = s_in->functionName();
				s_in->functionName(name);

				// exec
				result = f->funcStmt->execute(s_in, arg);

				s_in->functionName(oldFunctionName);
				//free(oldFunctionName);
			}
		}
	}
	else {
		cprintf("Warning: function call '%s' failed (dummy function in scope?), returning 0.0\n", f->name);
		result = new consoleVariable("", e3ga(0.0));
	}

	// everything that comes out of a function can be a 'rhs' argument
	result->rhs(1);

	// copy possible operation of first argument
	if (cv) result->op(cv->op());

	// free resources (but 'result' is exempt)
	consoleFreeCvList(cv, result);

	return result;
}

int consoleFreeCvList(consoleVariable *cv, consoleVariable *exempt /* = NULL */) {
	if (cv == NULL) return 0;
	consoleFreeCvList(cv->next(), exempt);
	cv->next(NULL);
	if (cv != exempt) delete cv;
	return 0;
}

std::string getFuncStringNameWithArguments(const consoleFunc *f, int argNames) {
	std::string nameWithArguments(f->name);

	nameWithArguments += "(";

	if (f->funcStmt) { // user function
		consoleFuncArgSpecListStmt *asl = f->funcStmt->argSpecList();
		consoleFuncArgSpecStmt *s;

		// add all arguments
		int i = 0;
		while (s = asl->argSpec(i)) {
			nameWithArguments += ((i == 0) ? "" : ", ");

			switch (s->model()) {
			case MVI_E3GA:
				nameWithArguments += "e3ga ";
				break;
			case MVI_P3GA:
				nameWithArguments += "p3ga ";
				break;
			case MVI_C3GA:
				nameWithArguments += "c3ga ";
				break;
			case MVI_C5GA:
				nameWithArguments += "c5ga ";
				break;
			case MVI_I2GA:
				nameWithArguments += "i2ga ";
				break;
			default:
				nameWithArguments += " ";
				break;

			}
			if (argNames) nameWithArguments += s->name();

			i++;
		}
	}
	else { // hard coded function
		// add all arguments
		int i = 0;
		for (i = 0; i < f->nbArg; i++) {
			nameWithArguments += ((i == 0) ? "" : ", ");

			switch (model(f->arg[i])) {
			case MVI_E3GA:
				nameWithArguments += "e3ga ";
				break;
			case MVI_P3GA:
				nameWithArguments += "p3ga ";
				break;
			case MVI_C3GA:
				nameWithArguments += "c3ga ";
				break;
			case MVI_C5GA:
				nameWithArguments += "c5ga ";
				break;
			case MVI_I2GA:
				nameWithArguments += "i2ga ";
				break;
			default:
				nameWithArguments += " ";
				break;
			}
		}
	}
	nameWithArguments += ")";
	return nameWithArguments;
}
