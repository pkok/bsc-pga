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

#include <string.h>
#include <math.h>

#include "../state.h"
#include "../mvint.h"
#include "console.h"
#include "consolevariable.h"
#include "../object.h"
//#include "consoleparse.h"

int consoleVariable::m_tempVarCount = 1;

consoleVariable::consoleVariable(const std::string &pname, const consoleVariable *cv) {
	initToNothing();
	if (cv->model() == MVI_E3GA) set((pname.length() > 0) ? pname : cv->name(), &cv->e());
	else if (cv->model() == MVI_P3GA) set((pname.length() > 0) ? pname : cv->name(), &cv->p());
	else if (cv->model() == MVI_C3GA) set((pname.length() > 0) ? pname : cv->name(), &cv->c());
	else if (cv->model() == MVI_C5GA) set((pname.length() > 0) ? pname : cv->name(), &cv->c5());
	else if (cv->model() == MVI_I2GA) set((pname.length() > 0) ? pname : cv->name(), &cv->i2());

	// copy other properties
	m_op = cv->op();
	m_flags = cv->m_flags;
	m_drawMode = cv->m_drawMode ^ (cv->m_drawMode & (((cv->m_forceFlags & OFF_HIDE) ? 0 : OD_HIDE) | OD_HIDE_ALWAYS)); // never inherit hide (unless forced) or hide always
	m_creationFlags = cv->m_creationFlags;
	m_forceFlags = cv->m_forceFlags;
	int i;
	for (i = 0; i < 4; i++)
		m_color[i] = cv->m_color[i];

}


consoleVariable::consoleVariable(const std::string &name, const e3ga *mv) {
	initToNothing();
	set(name, mv);
}

consoleVariable::consoleVariable(const std::string &name, const p3ga *mv) {
	initToNothing();
	set(name, mv);
}

consoleVariable::consoleVariable(const std::string &name, const c3ga *mv) {
	initToNothing();
	set(name, mv);
}

consoleVariable::consoleVariable(const std::string &name, const c5ga *mv) {
	initToNothing();
	set(name, mv);
}

consoleVariable::consoleVariable(const std::string &name, const i2ga *mv) {
	initToNothing();
	set(name, mv);
}

consoleVariable::consoleVariable(const std::string &name, const e3ga &mv) {
	initToNothing();
	set(name, &mv);
}

consoleVariable::consoleVariable(const std::string &name, const p3ga &mv) {
	initToNothing();
	set(name, &mv);
}

consoleVariable::consoleVariable(const std::string &name, const c3ga &mv) {
	initToNothing();
	set(name, &mv);
}

consoleVariable::consoleVariable(const std::string &name, const c5ga &mv) {
	initToNothing();
	set(name, &mv);
}

consoleVariable::consoleVariable(const std::string &name, const i2ga &mv) {
	initToNothing();
	set(name, &mv);
}

consoleVariable::consoleVariable(const consoleVariable &cv) {
	initToNothing();
	set(cv);
}


consoleVariable::~consoleVariable() {
	deleteMV();

	initToNothing();
}

void consoleVariable::initToNothing() {
	m_mv = NULL;
	m_op = 0;
	m_flags = 0;
	m_next = NULL;

	m_creationFlags = 0;
	m_drawMode = 0;
	m_forceFlags = 0;
	int i;
	for (i = 0; i < 4; i++) m_color[i] = 0.0f;
}

void consoleVariable::deleteMV() {
	if (m_mv) {
		switch(model()) {
		case MVI_E3GA:
			delete (e3ga*)m_mv;
			break;
		case MVI_P3GA:
			delete (p3ga*)m_mv;
			break;
		case MVI_C3GA:
			delete (c3ga*)m_mv;
			break;
		case MVI_C5GA:
			delete (c5ga*)m_mv;
			break;
		case MVI_I2GA:
			delete (i2ga*)m_mv;
			break;
		}
	}
	m_mv = NULL;
}

consoleVariable& consoleVariable::operator=(const consoleVariable &cv) {
	if (&cv != this) set(cv);
	return *this;
}

void consoleVariable::set(const consoleVariable &cv) {
	name(cv.name());

	m_model = cv.model();
	m_op = cv.op();
	m_flags = cv.m_flags;

	deleteMV();
	switch(cv.model()) {
	case MVI_E3GA:
		m_mv = new e3ga(*(e3ga*)cv.m_mv);
		break;
	case MVI_P3GA:
		m_mv = new p3ga(*(p3ga*)cv.m_mv);
		break;
	case MVI_C3GA:
		m_mv = new c3ga(*(c3ga*)cv.m_mv);
		break;
	case MVI_C5GA:
		m_mv = new c5ga(*(c5ga*)cv.m_mv);
		break;
	case MVI_I2GA:
		m_mv = new i2ga(*(i2ga*)cv.m_mv);
		break;
	}

	m_drawMode = cv.drawMode();
	m_forceFlags = cv.forceFlags();
	color4(cv.color());
}

int consoleVariable::set(const std::string &pname, const e3ga *mv) {
	int err;
	if (err = name(pname)) return err;

	int i;
	m_drawMode = OD_MAGNITUDE; //| OD_ORI;
	for (i = 0; i < 4; i++) m_color[i] = g_state->m_fgColor[i];

	m_mv = (void*)(new e3ga(*mv));

	/*if (I) m_int = new mvInt(I);
	else m_int = new mvInt(e());*/
	m_model = MVI_E3GA;

	return (m_mv == NULL) ? -1 : 0;
}

int consoleVariable::set(const std::string &pname, const p3ga *mv) {
	int err;
	if (err = name(pname)) return err;

	int i;
	m_drawMode = OD_MAGNITUDE; // | OD_ORI;
	for (i = 0; i < 4; i++) m_color[i] = g_state->m_fgColor[i];

	m_mv = (void*)(new p3ga(*mv));

/*	if (I) m_int = new mvInt(I);
	else m_int = new mvInt(p());*/
	m_model = MVI_P3GA;

	return (m_mv == NULL) ? -1 : 0;
}

int consoleVariable::set(const std::string &pname, const c3ga *mv) {
	int err;
	if (err = name(pname)) return err;

	int i;
	m_drawMode = OD_MAGNITUDE; // | OD_ORI;
	for (i = 0; i < 4; i++) m_color[i] = g_state->m_fgColor[i];

	m_mv = (void*)(new c3ga(*mv));

	m_model = MVI_C3GA;

	return (m_mv == NULL) ? -1 : 0;
}

int consoleVariable::set(const std::string &pname, const c5ga *mv) {
	int err;
	if (err = name(pname)) return err;

	int i;
	m_drawMode = OD_MAGNITUDE; // | OD_ORI;
	for (i = 0; i < 4; i++) m_color[i] = g_state->m_fgColor[i];

	m_mv = (void*)(new c5ga(*mv));

	m_model = MVI_C5GA;

	return (m_mv == NULL) ? -1 : 0;
}

int consoleVariable::set(const std::string &pname, const i2ga *mv) {
	int err;
	if (err = name(pname)) return err;

	int i;
	m_drawMode = OD_MAGNITUDE; // | OD_ORI;
	for (i = 0; i < 4; i++) m_color[i] = g_state->m_fgColor[i];

	m_mv = (void*)(new i2ga(*mv));

	m_model = MVI_I2GA;

	return (m_mv == NULL) ? -1 : 0;
}



e3ga &consoleVariable::e() const {
	static e3ga null;
	return (model() == MVI_E3GA) ? *(e3ga*)m_mv : null;
}

p3ga &consoleVariable::p() const {
	static p3ga null;
	return (model() == MVI_P3GA) ? *(p3ga*)m_mv : null;
}

c3ga &consoleVariable::c() const {
	static c3ga null;
	return (model() == MVI_C3GA) ? *(c3ga*)m_mv : null;
}

c5ga &consoleVariable::c5() const {
	static c5ga null;
	return (model() == MVI_C5GA) ? *(c5ga*)m_mv : null;
}

i2ga &consoleVariable::i2() const {
	static i2ga null;
	return (model() == MVI_I2GA) ? *(i2ga*)m_mv : null;
}

int consoleVariable::model() const {
	return m_model;
}

mvInt *consoleVariable::interpretation() const {
	mvInt *mvi = NULL;
	switch(model()) {
	case MVI_E3GA:
		mvi = new mvInt(e());
		break;
	case MVI_P3GA:
		mvi = new mvInt(p());
		break;
	case MVI_C3GA:
		mvi = new mvInt(c());
		break;
	case MVI_C5GA:
		mvi = new mvInt(c5());
		break;
	case MVI_I2GA:
		mvi = new mvInt(i2());
		break;
	}
	return mvi;
}

int consoleVariable::grade() const {
	int grade = -1, type = 0;
	switch(model()) {
	case MVI_E3GA:
		type = e().mvType(&grade); 
		break;
	case MVI_P3GA:
		type = p().mvType(&grade); 
		break;
	case MVI_C3GA:
		type = c().mvType(&grade); 
		break;
	case MVI_C5GA:
		type = c5().mvType(&grade); 
		break;
	case MVI_I2GA:
		type = i2().mvType(&grade); 
		break;
	}

	if (type == GA_BLADE)
		grade = (int)(log((double)grade) / log((double)2) + 0.45);
	else grade = -1;

	return grade;
}


int consoleVariable::print(const char *str) const {
	switch (model()) {
	case MVI_E3GA:
		e().print(str, "%f");
		break;
	case MVI_P3GA:
		p().print(str, "%f");
		break;
	case MVI_C3GA:
		c().print(str, "%f");
		break;
	case MVI_C5GA:
		c5().print(str, "%f");
		break;
	case MVI_I2GA:
		i2().print(str, "%f");
		break;
	default:
		printf("%s: unknown model\n", str);
		break;
	}
	return 0;
}

const char *consoleVariable::string() const {
	switch (model()) {
	case MVI_E3GA:
		return e().string("%e");
		
	case MVI_P3GA:
		return p().string("%e");
		
	case MVI_C3GA:
		return c().string("%e");
		
	case MVI_C5GA:
		return c5().string("%e");
		
	case MVI_I2GA:
		return i2().string("%e");
		
	default:
		return "unknown model";
		
	}
	
}


int consoleVariable::isTrue() const {
	switch (model()) {
	case MVI_E3GA:
		return (e().norm_a() != 0.0);
		break;
	case MVI_P3GA:
		return (p().norm_a() != 0.0);
		break;
	case MVI_C3GA:
		return (c().norm_a() != 0.0);
		break;
	case MVI_C5GA:
		return (c5().norm_a() != 0.0);
		break;
	case MVI_I2GA:
		return (i2().norm_a() != 0.0);
		break;
	}
	return 0;
}

GAIM_FLOAT consoleVariable::scalar() const {
	switch (model()) {
	case MVI_E3GA:
		return e().scalar();
		break;
	case MVI_P3GA:
		return p().scalar();
		break;
	case MVI_C3GA:
		return c().scalar();
		break;
	case MVI_C5GA:
		return c5().scalar();
		break;
	case MVI_I2GA:
		return i2().scalar();
		break;
	}
	return 0;
}

int consoleVariable::name(const std::string &name) {
/*	char tmpName[64];
	if (m_name) free(m_name);

	if (name == NULL) {
		sprintf(tmpName, "temporary console variable %d", m_tempVarCount++);
		name = tmpName;
	}

	return ((m_name = strdup(name)) == NULL) ? -1 : 0;*/
	m_name = name;
	return 0;
}

const std::string &consoleVariable::name() const {
	return m_name;
}

int consoleVariable::nameEquals(const std::string &name) const {
	/*if ((pname == NULL) || (name() == NULL)) return 0;
	return (!strcmp(pname, name()));*/
	return (m_name == name);
}


int consoleVariable::op() const {
//	printf("Get cv: %08X, op = %d\n", this, m_op);
	return m_op;
}

int consoleVariable::op(int o) {
	m_op = o;
//	printf("Set cv: %08X, op = %d\n", this, m_op);
	return 0;
}

int consoleVariable::getFlag(int flag) const {
	return (m_flags & flag);
}

int consoleVariable::setFlag(int flag, int val) {
	m_flags = (m_flags ^ (m_flags & flag)) | (val ? flag : 0);
	return 0;
}


/*int consoleVariable::constant(int c) {
	return setFlag(CVF_CONSTANT, c);
}
int consoleVariable::constant() const {
	return getFlag(CVF_CONSTANT);
}*/
int consoleVariable::rhs(int c) {
	return setFlag(CVF_RHS, c);
}
int consoleVariable::rhs() const {
	return getFlag(CVF_RHS);
}
int consoleVariable::lhs(int c) {
	return setFlag(CVF_LHS, c);
}
int consoleVariable::lhs() const {
	return getFlag(CVF_LHS);
}

int consoleVariable::global(int g) {
	return setFlag(CVF_GLOBAL, g);
}
int consoleVariable::global() const {
	return getFlag(CVF_GLOBAL);
}

int consoleVariable::functionArgument(int g) {
	return setFlag(CVF_FUNCTION_ARGUMENT, g);
}
int consoleVariable::functionArgument() const {
	return getFlag(CVF_FUNCTION_ARGUMENT);
}


int consoleVariable::drawMode() const{
	return m_drawMode;
}

int consoleVariable::drawMode(int mode) {
	m_drawMode = mode;
	return 0;
}

int consoleVariable::creationFlags()  const{
	return m_creationFlags;
}

int consoleVariable::creationFlags(int flags) {
	m_creationFlags = flags;
	return 0;
}

int consoleVariable::forceFlags() const {
	return m_forceFlags;
}


int consoleVariable::modifiedColor() {
	m_forceFlags |= OFF_COLOR;
	return 0;
}
int consoleVariable::modifiedAlpha() {
	m_forceFlags |= OFF_ALPHA;
	return 0;
}
int consoleVariable::modifiedDrawMethod() {
	m_forceFlags |= OFF_DRAWMETHOD;
	return 0;
}
int consoleVariable::modifiedHide() {
	m_forceFlags |= OFF_HIDE;
	return 0;
}
int consoleVariable::modifiedStipple() {
	m_forceFlags |= OFF_STIPPLE;
	return 0;
}
int consoleVariable::modifiedOri() {
	m_forceFlags |= OFF_ORI;
	return 0;
}
int consoleVariable::modifiedMute() {
	m_forceFlags |= OFF_MUTE;
	return 0;
}
int consoleVariable::modifiedWireframe() {
	m_forceFlags |= OFF_WIREFRAME;
	return 0;
}
int consoleVariable::modifiedOutline() {
	m_forceFlags |= OFF_OUTLINE;
	return 0;
}
int consoleVariable::modifiedMagnitude() {
	m_forceFlags |= OFF_MAGNITUDE;
	return 0;
}
int consoleVariable::modifiedShade() {
	m_forceFlags |= OFF_SHADE;
	return 0;
}

const float *consoleVariable::color() const {
	return m_color;
}


int consoleVariable::color4(float r, float g, float b, float a) {
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	m_color[3] = a;
	return 0;
}

int consoleVariable::color4(const float c[4]) {
	m_color[0] = c[0];
	m_color[1] = c[1];
	m_color[2] = c[2];
	m_color[3] = c[3];
	return 0;
}

int consoleVariable::color3(float r, float g, float b) {
	m_color[0] = r;
	m_color[1] = g;
	m_color[2] = b;
	return 0;
}

int consoleVariable::color3(const float c[3]) {
	m_color[0] = c[0];
	m_color[1] = c[1];
	m_color[2] = c[2];
	return 0;
}

int consoleVariable::alpha(float alpha) {
	m_color[3] = alpha;
	return 0;
}

float consoleVariable::alpha() const {
	return m_color[3];
}


void consoleVariable::next(consoleVariable *pnext) {
	m_next = pnext;
}

consoleVariable *consoleVariable::next() {
	return m_next;
}


consoleVariable *consoleVariable::castE3gaToP3ga() const {
	p3ga vp;
	const e3ga &ve = e();
	vp = 
		// grade 0
		ve.scalar() + 
		// grade 1
		ve[GRADE1][E3GA_E1] * p3ga::e1 + 
		ve[GRADE1][E3GA_E2] * p3ga::e2 + 
		ve[GRADE1][E3GA_E3] * p3ga::e3 + 
		// grade 2
		ve[GRADE2][E3GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) + 
		ve[GRADE2][E3GA_E2_E3] * (p3ga::e2 ^ p3ga::e3) + 
		ve[GRADE2][E3GA_E3_E1] * (p3ga::e3 ^ p3ga::e1) + 
		// grade 3
		ve[GRADE3][E3GA_I] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3);

	vp.compress();
	return new consoleVariable("", vp);
}

consoleVariable *consoleVariable::castE3gaToC3ga() const {
	c3ga vc;
	const e3ga &ve = e();
	vc = 
		// grade 0
		ve.scalar() + 
		// grade 1
		ve[GRADE1][E3GA_E1] * c3ga::e1 + 
		ve[GRADE1][E3GA_E2] * c3ga::e2 + 
		ve[GRADE1][E3GA_E3] * c3ga::e3 + 
		// grade 2
		ve[GRADE2][E3GA_E1_E2] * (c3ga::e1 ^ c3ga::e2) + 
		ve[GRADE2][E3GA_E2_E3] * (c3ga::e2 ^ c3ga::e3) + 
		ve[GRADE2][E3GA_E3_E1] * (c3ga::e3 ^ c3ga::e1) + 
		// grade 3
		ve[GRADE3][E3GA_I] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3);

	vc.compress();
	return new consoleVariable("", vc);
}

consoleVariable *consoleVariable::castE3gaToC5ga() const {
	c5ga vc;
	const e3ga &ve = e();
	vc = 
		// grade 0
		ve.scalar() + 
		// grade 1
		ve[GRADE1][E3GA_E1] * c5ga::e1 + 
		ve[GRADE1][E3GA_E2] * c5ga::e2 + 
		ve[GRADE1][E3GA_E3] * c5ga::e3 + 
		// grade 2
		ve[GRADE2][E3GA_E1_E2] * (c5ga::e1 ^ c5ga::e2) + 
		ve[GRADE2][E3GA_E2_E3] * (c5ga::e2 ^ c5ga::e3) + 
		ve[GRADE2][E3GA_E3_E1] * (c5ga::e3 ^ c5ga::e1) + 
		// grade 3
		ve[GRADE3][E3GA_I] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3);

	vc.compress();
	return new consoleVariable("", vc);
}

consoleVariable *consoleVariable::castP3gaToC3ga() const {
	c3ga vc;
	const p3ga &vp = p();
	vc = 
		// grade 0
		vp.scalar() + 
		// grade 1
		vp[GRADE1][P3GA_E1] * c3ga::e1 + 
		vp[GRADE1][P3GA_E2] * c3ga::e2 + 
		vp[GRADE1][P3GA_E3] * c3ga::e3 + 
		vp[GRADE1][P3GA_E0] * c3ga::no + 
		// grade 2
		vp[GRADE2][P3GA_E1_E2] * (c3ga::e1 ^ c3ga::e2) + 
		vp[GRADE2][P3GA_E2_E3] * (c3ga::e2 ^ c3ga::e3) + 
		vp[GRADE2][P3GA_E3_E1] * (c3ga::e3 ^ c3ga::e1) + 
		vp[GRADE2][P3GA_E1_E0] * (c3ga::e1 ^ c3ga::no) + 
		vp[GRADE2][P3GA_E2_E0] * (c3ga::e2 ^ c3ga::no) + 
		vp[GRADE2][P3GA_E3_E0] * (c3ga::e3 ^ c3ga::no) + 
		// grade 3
		vp[GRADE3][P3GA_E2_E3_E0] * (c3ga::e2 ^ c3ga::e3 ^ c3ga::no) + 
		vp[GRADE3][P3GA_E3_E1_E0] * (c3ga::e3 ^ c3ga::e1 ^ c3ga::no) + 
		vp[GRADE3][P3GA_E1_E2_E0] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::no) + 
		vp[GRADE3][P3GA_E1_E2_E3] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3) +
		// grade 4
		vp[GRADE4][P3GA_I] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3 ^ c3ga::no);

	vc.compress();
	return new consoleVariable("", vc);
}
consoleVariable *consoleVariable::castP3gaToC5ga() const {
	c5ga vc;
	const p3ga &vp = p();
	vc = 
		// grade 0
		vp.scalar() + 
		// grade 1
		vp[GRADE1][P3GA_E1] * c5ga::e1 + 
		vp[GRADE1][P3GA_E2] * c5ga::e2 + 
		vp[GRADE1][P3GA_E3] * c5ga::e3 + 
		vp[GRADE1][P3GA_E0] * c5ga::no + 
		// grade 2
		vp[GRADE2][P3GA_E1_E2] * (c5ga::e1 ^ c5ga::e2) + 
		vp[GRADE2][P3GA_E2_E3] * (c5ga::e2 ^ c5ga::e3) + 
		vp[GRADE2][P3GA_E3_E1] * (c5ga::e3 ^ c5ga::e1) + 
		vp[GRADE2][P3GA_E1_E0] * (c5ga::e1 ^ c5ga::no) + 
		vp[GRADE2][P3GA_E2_E0] * (c5ga::e2 ^ c5ga::no) + 
		vp[GRADE2][P3GA_E3_E0] * (c5ga::e3 ^ c5ga::no) + 
		// grade 3
		vp[GRADE3][P3GA_E2_E3_E0] * (c5ga::e2 ^ c5ga::e3 ^ c5ga::no) + 
		vp[GRADE3][P3GA_E3_E1_E0] * (c5ga::e3 ^ c5ga::e1 ^ c5ga::no) + 
		vp[GRADE3][P3GA_E1_E2_E0] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::no) + 
		vp[GRADE3][P3GA_E1_E2_E3] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3) +
		// grade 4
		vp[GRADE4][P3GA_I] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3 ^ c5ga::no);

	vc.compress();
	return new consoleVariable("", vc);
}

consoleVariable *consoleVariable::castP3gaToE3ga() const {
	e3ga ve;
	const p3ga &vp = p();
	ve = 
		// grade 0
		vp.scalar() + 
		// grade 1
		vp[GRADE1][P3GA_E1] * e3ga::e1 + 
		vp[GRADE1][P3GA_E2] * e3ga::e2 + 
		vp[GRADE1][P3GA_E3] * e3ga::e3 + 
		// grade 2
		vp[GRADE2][P3GA_E1_E2] * (e3ga::e1 ^ e3ga::e2) + 
		vp[GRADE2][P3GA_E2_E3] * (e3ga::e2 ^ e3ga::e3) + 
		vp[GRADE2][P3GA_E3_E1] * (e3ga::e3 ^ e3ga::e1) + 
		// grade 3
		vp[GRADE3][P3GA_E1_E2_E3] * (e3ga::e1 ^ e3ga::e2 ^ e3ga::e3);

	ve.compress();
	return new consoleVariable("", ve);
}

consoleVariable *consoleVariable::castC3gaToE3ga() const {
	e3ga ve;
	const c3ga &vc = c();
	ve = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C3GA_E1] * e3ga::e1 + 
		vc[GRADE1][C3GA_E2] * e3ga::e2 + 
		vc[GRADE1][C3GA_E3] * e3ga::e3 + 
		// grade 2
		vc[GRADE2][C3GA_E1_E2] * (e3ga::e1 ^ e3ga::e2) + 
		vc[GRADE2][C3GA_E2_E3] * (e3ga::e2 ^ e3ga::e3) + 
		vc[GRADE2][C3GA_E1_E3] * (e3ga::e1 ^ e3ga::e3) + 
		// grade 3
		vc[GRADE3][C3GA_E1_E2_E3] * (e3ga::e1 ^ e3ga::e2 ^ e3ga::e3);

	ve.compress();
	return new consoleVariable("", ve);
}

consoleVariable *consoleVariable::castC5gaToE3ga() const {
	e3ga ve;
	const c5ga &vc = c5();
	ve = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C5GA_E1] * e3ga::e1 + 
		vc[GRADE1][C5GA_E2] * e3ga::e2 + 
		vc[GRADE1][C5GA_E3] * e3ga::e3 + 
		// grade 2
		vc[GRADE2][C5GA_E1_E2] * (e3ga::e1 ^ e3ga::e2) + 
		vc[GRADE2][C5GA_E2_E3] * (e3ga::e2 ^ e3ga::e3) + 
		vc[GRADE2][C5GA_E1_E3] * (e3ga::e1 ^ e3ga::e3) + 
		// grade 3
		vc[GRADE3][C5GA_E1_E2_E3] * (e3ga::e1 ^ e3ga::e2 ^ e3ga::e3);

	ve.compress();
	return new consoleVariable("", ve);
}

consoleVariable *consoleVariable::castC3gaToP3ga() const {
	p3ga vp;
	const c3ga &vc = c();
	vp = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C3GA_E1] * p3ga::e1 + 
		vc[GRADE1][C3GA_E2] * p3ga::e2 + 
		vc[GRADE1][C3GA_E3] * p3ga::e3 + 
		vc[GRADE1][C3GA_NO] * p3ga::e0 + 
		// grade 2
		vc[GRADE2][C3GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) + 
		vc[GRADE2][C3GA_E2_E3] * (p3ga::e2 ^ p3ga::e3) + 
		vc[GRADE2][C3GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) + 
		vc[GRADE2][C3GA_E1_NO] * (p3ga::e1 ^ p3ga::e0) + 
		vc[GRADE2][C3GA_E2_NO] * (p3ga::e2 ^ p3ga::e0) + 
		vc[GRADE2][C3GA_E3_NO] * (p3ga::e3 ^ p3ga::e0) + 
		// grade 3
		vc[GRADE3][C3GA_E2_E3_NO] * (p3ga::e2 ^ p3ga::e3 ^ p3ga::e0) + 
		vc[GRADE3][C3GA_E1_E3_NO] * (p3ga::e1 ^ p3ga::e3 ^ p3ga::e0) + 
		vc[GRADE3][C3GA_E1_E2_NO] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e0) + 
		vc[GRADE3][C3GA_E1_E2_E3] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3) +
		// grade 4
		vc[GRADE4][C3GA_E1_E2_E3_NO] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3 ^ p3ga::e0);

	vp.compress();
	return new consoleVariable("", vp);
}

consoleVariable *consoleVariable::castC5gaToP3ga() const {
	p3ga vp;
	const c5ga &vc = c5();
	vp = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C5GA_E1] * p3ga::e1 + 
		vc[GRADE1][C5GA_E2] * p3ga::e2 + 
		vc[GRADE1][C5GA_E3] * p3ga::e3 + 
		vc[GRADE1][C5GA_NO] * p3ga::e0 + 
		// grade 2
		vc[GRADE2][C5GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) + 
		vc[GRADE2][C5GA_E2_E3] * (p3ga::e2 ^ p3ga::e3) + 
		vc[GRADE2][C5GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) + 
		vc[GRADE2][C5GA_E1_NO] * (p3ga::e1 ^ p3ga::e0) + 
		vc[GRADE2][C5GA_E2_NO] * (p3ga::e2 ^ p3ga::e0) + 
		vc[GRADE2][C5GA_E3_NO] * (p3ga::e3 ^ p3ga::e0) + 
		// grade 3
		vc[GRADE3][C5GA_E2_E3_NO] * (p3ga::e2 ^ p3ga::e3 ^ p3ga::e0) + 
		vc[GRADE3][C5GA_E1_E3_NO] * (p3ga::e1 ^ p3ga::e3 ^ p3ga::e0) + 
		vc[GRADE3][C5GA_E1_E2_NO] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e0) + 
		vc[GRADE3][C5GA_E1_E2_E3] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3) +
		// grade 4
		vc[GRADE4][C5GA_E1_E2_E3_NO] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e3 ^ p3ga::e0);

	vp.compress();
	return new consoleVariable("", vp);
}

consoleVariable *consoleVariable::castC5gaToC3ga() const {
	c3ga vp;
	castC5gaToC3ga(c5(), vp);

	return new consoleVariable("", vp);
}

void consoleVariable::castC5gaToC3ga(const c5ga &vc, c3ga &vp) {
	// grade 0
	vp = vc.scalar();

	// grade 1
	if (vc.gradeUsage() & GRADE1) {
		vp +=
			vc[GRADE1][C5GA_E1] * c3ga::e1 + 
			vc[GRADE1][C5GA_E2] * c3ga::e2 + 
			vc[GRADE1][C5GA_E3] * c3ga::e3 + 
			vc[GRADE1][C5GA_NO] * c3ga::no + 
			vc[GRADE1][C5GA_NI] * c3ga::ni;
	}
	// grade 2
	if (vc.gradeUsage() & GRADE2) {
		vp +=
			vc[GRADE2][C5GA_E1_E2] * (c3ga::e1 ^ c3ga::e2) + 
			vc[GRADE2][C5GA_E1_E3] * (c3ga::e1 ^ c3ga::e3) + 
			vc[GRADE2][C5GA_E2_E3] * (c3ga::e2 ^ c3ga::e3) + 
			vc[GRADE2][C5GA_E1_NO] * (c3ga::e1 ^ c3ga::no) + 
			vc[GRADE2][C5GA_E2_NO] * (c3ga::e2 ^ c3ga::no) + 
			vc[GRADE2][C5GA_E3_NO] * (c3ga::e3 ^ c3ga::no) + 
			vc[GRADE2][C5GA_E1_NI] * (c3ga::e1 ^ c3ga::ni) + 
			vc[GRADE2][C5GA_E2_NI] * (c3ga::e2 ^ c3ga::ni) + 
			vc[GRADE2][C5GA_E3_NI] * (c3ga::e3 ^ c3ga::ni) + 
			vc[GRADE2][C5GA_NO_NI] * (c3ga::no ^ c3ga::ni);
	}
	// grade 3
	if (vc.gradeUsage() & GRADE3) {
		vp +=
			vc[GRADE3][C5GA_E1_E2_E3] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3) + 
			vc[GRADE3][C5GA_E1_E2_NO] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::no) + 
			vc[GRADE3][C5GA_E1_E3_NO] * (c3ga::e1 ^ c3ga::e3 ^ c3ga::no) + 
			vc[GRADE3][C5GA_E2_E3_NO] * (c3ga::e2 ^ c3ga::e3 ^ c3ga::no) + 
			vc[GRADE3][C5GA_E1_E2_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::ni) + 
			vc[GRADE3][C5GA_E1_E3_NI] * (c3ga::e1 ^ c3ga::e3 ^ c3ga::ni) + 
			vc[GRADE3][C5GA_E2_E3_NI] * (c3ga::e2 ^ c3ga::e3 ^ c3ga::ni) + 
			vc[GRADE3][C5GA_E1_NO_NI] * (c3ga::e1 ^ c3ga::no ^ c3ga::ni) + 
			vc[GRADE3][C5GA_E2_NO_NI] * (c3ga::e2 ^ c3ga::no ^ c3ga::ni) + 
			vc[GRADE3][C5GA_E3_NO_NI] * (c3ga::e3 ^ c3ga::no ^ c3ga::ni);
	}
	// grade 4
	if (vc.gradeUsage() & GRADE4) {
		vp +=
			vc[GRADE4][C5GA_E1_E2_E3_NO] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3 ^ c3ga::no) +
			vc[GRADE4][C5GA_E1_E2_E3_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3 ^ c3ga::ni) +
			vc[GRADE4][C5GA_E1_E2_NO_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::no ^ c3ga::ni) +
			vc[GRADE4][C5GA_E1_E3_NO_NI] * (c3ga::e1 ^ c3ga::e3 ^ c3ga::no ^ c3ga::ni) +
			vc[GRADE4][C5GA_E2_E3_NO_NI] * (c3ga::e2 ^ c3ga::e3 ^ c3ga::no ^ c3ga::ni);
	}
	// grade 5
	if (vc.gradeUsage() & GRADE5) {
		vp +=
			vc[GRADE5][C5GA_E1_E2_E3_NO_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::e3 ^ c3ga::no ^ c3ga::ni);
	}

	vp.compress();
}

consoleVariable *consoleVariable::castC3gaToC5ga() const {
	c5ga vp;
	const c3ga &vc = c();

	// grade 0
	if (vc.gradeUsage() & GRADE0) {
		vp += vc.scalar();
	}

	// grade 1
	if (vc.gradeUsage() & GRADE1) {
		vp += 
			vc[GRADE1][C3GA_E1] * c5ga::e1 + 
			vc[GRADE1][C3GA_E2] * c5ga::e2 + 
			vc[GRADE1][C3GA_E3] * c5ga::e3 + 
			vc[GRADE1][C3GA_NO] * c5ga::no + 
			vc[GRADE1][C3GA_NI] * c5ga::ni;
	}

	// grade 2
	if (vc.gradeUsage() & GRADE2) {
		vp += 
			vc[GRADE2][C3GA_E1_E2] * (c5ga::e1 ^ c5ga::e2) + 
			vc[GRADE2][C3GA_E1_E3] * (c5ga::e1 ^ c5ga::e3) + 
			vc[GRADE2][C3GA_E2_E3] * (c5ga::e2 ^ c5ga::e3) + 
			vc[GRADE2][C3GA_E1_NO] * (c5ga::e1 ^ c5ga::no) + 
			vc[GRADE2][C3GA_E2_NO] * (c5ga::e2 ^ c5ga::no) + 
			vc[GRADE2][C3GA_E3_NO] * (c5ga::e3 ^ c5ga::no) + 
			vc[GRADE2][C3GA_E1_NI] * (c5ga::e1 ^ c5ga::ni) + 
			vc[GRADE2][C3GA_E2_NI] * (c5ga::e2 ^ c5ga::ni) + 
			vc[GRADE2][C3GA_E3_NI] * (c5ga::e3 ^ c5ga::ni) + 
			vc[GRADE2][C3GA_NO_NI] * (c5ga::no ^ c5ga::ni);
	}

	// grade 3
	if (vc.gradeUsage() & GRADE3) {
		vp += 
			vc[GRADE3][C3GA_E1_E2_E3] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3) + 
			vc[GRADE3][C3GA_E1_E2_NO] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::no)+ 
			vc[GRADE3][C3GA_E1_E3_NO] * (c5ga::e1 ^ c5ga::e3 ^ c5ga::no) + 
			vc[GRADE3][C3GA_E2_E3_NO] * (c5ga::e2 ^ c5ga::e3 ^ c5ga::no) + 
			vc[GRADE3][C3GA_E1_E2_NI] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::ni)  + 
			vc[GRADE3][C3GA_E1_E3_NI] * (c5ga::e1 ^ c5ga::e3 ^ c5ga::ni) + 
			vc[GRADE3][C3GA_E2_E3_NI] * (c5ga::e2 ^ c5ga::e3 ^ c5ga::ni) + 
			vc[GRADE3][C3GA_E1_NO_NI] * (c5ga::e1 ^ c5ga::no ^ c5ga::ni) + 
			vc[GRADE3][C3GA_E2_NO_NI] * (c5ga::e2 ^ c5ga::no ^ c5ga::ni) + 
			vc[GRADE3][C3GA_E3_NO_NI] * (c5ga::e3 ^ c5ga::no ^ c5ga::ni);
	}

	// grade 4
	if (vc.gradeUsage() & GRADE4) {
		vp += 
			vc[GRADE4][C3GA_E1_E2_E3_NO] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3 ^ c5ga::no) +
			vc[GRADE4][C3GA_E1_E2_E3_NI] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3 ^ c5ga::ni) +
			vc[GRADE4][C3GA_E1_E2_NO_NI] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::no ^ c5ga::ni) +
			vc[GRADE4][C3GA_E1_E3_NO_NI] * (c5ga::e1 ^ c5ga::e3 ^ c5ga::no ^ c5ga::ni) +
			vc[GRADE4][C3GA_E2_E3_NO_NI] * (c5ga::e2 ^ c5ga::e3 ^ c5ga::no ^ c5ga::ni);
	}

	// grade 5
	if (vc.gradeUsage() & GRADE5) {
		vp += 
			vc[GRADE5][C3GA_I] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::e3 ^ c5ga::no ^ c5ga::ni);
	}

	vp.compress();
	return new consoleVariable("", vp);
}


consoleVariable *consoleVariable::castE3gaToI2ga() const {
	i2ga vi2;
	const e3ga &ve = e();

	// only e1, e2 are preserved
	vi2 = 
		// grade 0
		ve.scalar() + 
		// grade 1
		ve[GRADE1][E3GA_E1] * i2ga::e1 + 
		ve[GRADE1][E3GA_E2] * i2ga::e2 + 
		// grade 2
		ve[GRADE2][E3GA_E1_E2] * (i2ga::e1 ^ i2ga::e2);

	vi2.compress();
	return new consoleVariable("", vi2);
}

consoleVariable *consoleVariable::castP3gaToI2ga() const {
	i2ga vi2;
	const p3ga &vp = p();

	// e1, e2, e0 (-> no) are preserved
	vi2 = 
		// grade 0
		vp.scalar() + 
		// grade 1
		vp[GRADE1][P3GA_E1] * i2ga::e1 + 
		vp[GRADE1][P3GA_E2] * i2ga::e2 + 
		vp[GRADE1][P3GA_E0] * i2ga::no + 
		// grade 2
		vp[GRADE2][P3GA_E1_E2] * (i2ga::e1 ^ i2ga::e2) +
		vp[GRADE2][P3GA_E1_E0] * (i2ga::e1 ^ i2ga::no) +
		vp[GRADE2][P3GA_E2_E0] * (i2ga::e2 ^ i2ga::no) +
		// grade 3
		vp[GRADE2][P3GA_E1_E2_E0] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::no);

	vi2.compress();
	return new consoleVariable("", vi2);
}


consoleVariable *consoleVariable::castC3gaToI2ga() const {
	i2ga vi2;
	const c3ga &vc = c();

	// e1, e2, ni, no are preserved
	vi2 = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C3GA_E1] * i2ga::e1 + 
		vc[GRADE1][C3GA_E2] * i2ga::e2 + 
		vc[GRADE1][C3GA_NO] * i2ga::no + 
		vc[GRADE1][C3GA_NI] * i2ga::ni + 
		// grade 2
		vc[GRADE2][C3GA_E1_E2] * (i2ga::e1 ^ i2ga::e2) +
		vc[GRADE2][C3GA_E1_NO] * (i2ga::e1 ^ i2ga::no) +
		vc[GRADE2][C3GA_E2_NO] * (i2ga::e2 ^ i2ga::no) +
		vc[GRADE2][C3GA_E1_NI] * (i2ga::e1 ^ i2ga::ni) +
		vc[GRADE2][C3GA_E2_NI] * (i2ga::e2 ^ i2ga::ni) +
		vc[GRADE2][C3GA_NO_NI] * (i2ga::no ^ i2ga::ni) +
		// grade 3
		vc[GRADE2][C3GA_E1_E2_NO] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::no) + 
		vc[GRADE2][C3GA_E1_E2_NI] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::ni) + 
		vc[GRADE2][C3GA_E1_NO_NI] * (i2ga::e1 ^ i2ga::no ^ i2ga::ni) + 
		vc[GRADE2][C3GA_E2_NO_NI] * (i2ga::e2 ^ i2ga::no ^ i2ga::ni) + 
		// grade 4
		vc[GRADE2][C3GA_E1_E2_NO_NI] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::no ^ i2ga::ni);

	vi2.compress();
	return new consoleVariable("", vi2);

}

consoleVariable *consoleVariable::castC5gaToI2ga() const {
	i2ga vi2;
	const c5ga &vc = c5();

	// e1, e2, ni, no are preserved
	vi2 = 
		// grade 0
		vc.scalar() + 
		// grade 1
		vc[GRADE1][C5GA_E1] * i2ga::e1 + 
		vc[GRADE1][C5GA_E2] * i2ga::e2 + 
		vc[GRADE1][C5GA_NO] * i2ga::no + 
		vc[GRADE1][C5GA_NI] * i2ga::ni + 
		// grade 2
		vc[GRADE2][C5GA_E1_E2] * (i2ga::e1 ^ i2ga::e2) +
		vc[GRADE2][C5GA_E1_NO] * (i2ga::e1 ^ i2ga::no) +
		vc[GRADE2][C5GA_E2_NO] * (i2ga::e2 ^ i2ga::no) +
		vc[GRADE2][C5GA_E1_NI] * (i2ga::e1 ^ i2ga::ni) +
		vc[GRADE2][C5GA_E2_NI] * (i2ga::e2 ^ i2ga::ni) +
		vc[GRADE2][C5GA_NO_NI] * (i2ga::no ^ i2ga::ni) +
		// grade 3
		vc[GRADE2][C5GA_E1_E2_NO] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::no) + 
		vc[GRADE2][C5GA_E1_E2_NI] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::ni) + 
		vc[GRADE2][C5GA_E1_NO_NI] * (i2ga::e1 ^ i2ga::no ^ i2ga::ni) + 
		vc[GRADE2][C5GA_E2_NO_NI] * (i2ga::e2 ^ i2ga::no ^ i2ga::ni) + 
		// grade 4
		vc[GRADE2][C5GA_E1_E2_NO_NI] * (i2ga::e1 ^ i2ga::e2 ^ i2ga::no ^ i2ga::ni);

	vi2.compress();
	return new consoleVariable("", vi2);

}

consoleVariable *consoleVariable::castI2gaToE3ga() const {
	e3ga ve;
	const i2ga &vi2 = i2();

	// only e1, e2 are preserved
	ve = 
		// grade 0
		vi2.scalar() + 
		// grade 1
		vi2[GRADE1][I2GA_E1] * e3ga::e1 + 
		vi2[GRADE1][I2GA_E2] * e3ga::e2 + 
		// grade 2
		vi2[GRADE2][I2GA_E1_E2] * (e3ga::e1 ^ e3ga::e2);

	ve.compress();
	return new consoleVariable("", ve);
}

consoleVariable *consoleVariable::castI2gaToP3ga() const {
	p3ga vp;
	const i2ga &vi2 = i2();

	// e1, e2, e0 (-> no) are preserved
	vp = 
		// grade 0
		vi2.scalar() + 
		// grade 1
		vi2[GRADE1][I2GA_E1] * p3ga::e1 + 
		vi2[GRADE1][I2GA_E2] * p3ga::e2 + 
		vi2[GRADE1][I2GA_NO] * p3ga::e0 + 
		// grade 2
		vi2[GRADE2][I2GA_E1_E2] * (p3ga::e1 ^ p3ga::e2) +
		vi2[GRADE2][I2GA_E1_NO] * (p3ga::e1 ^ p3ga::e0) +
		vi2[GRADE2][I2GA_E2_NO] * (p3ga::e2 ^ p3ga::e0) +
		// grade 3
		vi2[GRADE2][I2GA_E1_E2_NO] * (p3ga::e1 ^ p3ga::e2 ^ p3ga::e0);

	vp.compress();
	return new consoleVariable("", vp);
}

consoleVariable *consoleVariable::castI2gaToC3ga() const {
	c3ga vc;
	const i2ga &vi2 = i2();

	// e1, e2, ni, no are preserved
	vc = 
		// grade 0
		vi2.scalar() + 
		// grade 1
		vi2[GRADE1][I2GA_E1] * c3ga::e1 + 
		vi2[GRADE1][I2GA_E2] * c3ga::e2 + 
		vi2[GRADE1][I2GA_NO] * c3ga::no + 
		vi2[GRADE1][I2GA_NI] * c3ga::ni + 
		// grade 2
		vi2[GRADE2][I2GA_E1_E2] * (c3ga::e1 ^ c3ga::e2) +
		vi2[GRADE2][I2GA_E1_NO] * (c3ga::e1 ^ c3ga::no) +
		vi2[GRADE2][I2GA_E2_NO] * (c3ga::e2 ^ c3ga::no) +
		vi2[GRADE2][I2GA_E1_NI] * (c3ga::e1 ^ c3ga::ni) +
		vi2[GRADE2][I2GA_E2_NI] * (c3ga::e2 ^ c3ga::ni) +
		vi2[GRADE2][I2GA_NO_NI] * (c3ga::no ^ c3ga::ni) +
		// grade 3
		vi2[GRADE2][I2GA_E1_E2_NO] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::no) + 
		vi2[GRADE2][I2GA_E1_E2_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::ni) + 
		vi2[GRADE2][I2GA_E1_NO_NI] * (c3ga::e1 ^ c3ga::no ^ c3ga::ni) + 
		vi2[GRADE2][I2GA_E2_NO_NI] * (c3ga::e2 ^ c3ga::no ^ c3ga::ni) + 
		// grade 4
		vi2[GRADE2][I2GA_E1_E2_NO_NI] * (c3ga::e1 ^ c3ga::e2 ^ c3ga::no ^ c3ga::ni);

	vc.compress();
	return new consoleVariable("", vc);

}

consoleVariable *consoleVariable::castI2gaToC5ga() const {
	c5ga vc;
	const i2ga &vi2 = i2();

	// e1, e2, ni, no are preserved
	vc = 
		// grade 0
		vi2.scalar() + 
		// grade 1
		vi2[GRADE1][I2GA_E1] * c5ga::e1 + 
		vi2[GRADE1][I2GA_E2] * c5ga::e2 + 
		vi2[GRADE1][I2GA_NO] * c5ga::no + 
		vi2[GRADE1][I2GA_NI] * c5ga::ni + 
		// grade 2
		vi2[GRADE2][I2GA_E1_E2] * (c5ga::e1 ^ c5ga::e2) +
		vi2[GRADE2][I2GA_E1_NO] * (c5ga::e1 ^ c5ga::no) +
		vi2[GRADE2][I2GA_E2_NO] * (c5ga::e2 ^ c5ga::no) +
		vi2[GRADE2][I2GA_E1_NI] * (c5ga::e1 ^ c5ga::ni) +
		vi2[GRADE2][I2GA_E2_NI] * (c5ga::e2 ^ c5ga::ni) +
		vi2[GRADE2][I2GA_NO_NI] * (c5ga::no ^ c5ga::ni) +
		// grade 3
		vi2[GRADE2][I2GA_E1_E2_NO] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::no) + 
		vi2[GRADE2][I2GA_E1_E2_NI] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::ni) + 
		vi2[GRADE2][I2GA_E1_NO_NI] * (c5ga::e1 ^ c5ga::no ^ c5ga::ni) + 
		vi2[GRADE2][I2GA_E2_NO_NI] * (c5ga::e2 ^ c5ga::no ^ c5ga::ni) + 
		// grade 4
		vi2[GRADE2][I2GA_E1_E2_NO_NI] * (c5ga::e1 ^ c5ga::e2 ^ c5ga::no ^ c5ga::ni);

	vc.compress();
	return new consoleVariable("", vc);

}


consoleVariable *consoleVariable::castToE3ga() const {
	switch (model()) {
	case MVI_E3GA:
		return new consoleVariable("", e());
		break;
	case MVI_P3GA:
		return castP3gaToE3ga();
		break;
	case MVI_C3GA:
		return castC3gaToE3ga();
		break;
	case MVI_C5GA:
		return castC5gaToE3ga();
		break;
	case MVI_I2GA:
		return castI2gaToE3ga();
		break;
	}
	return NULL;
}

consoleVariable *consoleVariable::castToP3ga() const {
	switch (model()) {
	case MVI_E3GA:
		return castE3gaToP3ga();
		break;
	case MVI_P3GA:
		return new consoleVariable("", p());
		break;
	case MVI_C3GA:
		return castC3gaToP3ga();
		break;
	case MVI_C5GA:
		return castC5gaToP3ga();
		break;
	case MVI_I2GA:
		return castI2gaToP3ga();
		break;
	}
	return NULL;
}

consoleVariable *consoleVariable::castToC3ga() const {
	switch (model()) {
	case MVI_E3GA:
		return castE3gaToC3ga();
		break;
	case MVI_P3GA:
		return castP3gaToC3ga();
		break;
	case MVI_C3GA:
		return new consoleVariable("", c());
		break;
	case MVI_C5GA:
		return castC5gaToC3ga();
		break;
	case MVI_I2GA:
		return castI2gaToC3ga();
		break;
	}
	return NULL;
}

consoleVariable *consoleVariable::castToC5ga() const {
	switch (model()) {
	case MVI_E3GA:
		return castE3gaToC5ga();
		break;
	case MVI_P3GA:
		return castP3gaToC5ga();
		break;
	case MVI_C3GA:
		return castC3gaToC5ga();
		break;
	case MVI_C5GA:
		return new consoleVariable("", c5());
		break;
	case MVI_I2GA:
		return castI2gaToC5ga();
		break;
	}
	return NULL;
}

consoleVariable *consoleVariable::castToI2ga() const {
	switch (model()) {
	case MVI_E3GA:
		return castE3gaToI2ga();
		break;
	case MVI_P3GA:
		return castP3gaToI2ga();
		break;
	case MVI_C3GA:
		return castC3gaToI2ga();
		break;
	case MVI_C5GA:
		return castC5gaToI2ga();
		break;
	case MVI_I2GA:
		return new consoleVariable("", i2());
		break;
	}
	return NULL;
}

void *consoleVariableScalar(const char *name, double val) {
	e3ga tmp(val);
	consoleVariable *cv = new consoleVariable(name, tmp);
	cv->rhs(1);
	return cv;
}

void consoleVariableSetLhs(void *cv, int v) {
	((consoleVariable *)cv)->lhs(v);
}

void consoleVariableSetRhs(void *cv, int v) {
	((consoleVariable *)cv)->rhs(v);
}


int consoleVariableSetOperator(void *cv, int op) {
	return ((consoleVariable*)cv)->op(op);
}

int consolePrintVariableModel(void *cv) {
	printf("consolePrintVariableType: %08X\n", ((consoleVariable*)cv)->model());
	return 0;
}

void consoleVariableFree(void *cv) {
	if (cv) {
		delete (consoleVariable*)cv;
	}
}

