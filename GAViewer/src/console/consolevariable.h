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

#ifndef _CONSOLE_VARIABLE_H_
#define _CONSOLE_VARIABLE_H_

#include <string>

#include "../gaincludes.h"
#include "../mvint.h"


#define CVF_CONSTANT (1 << 0)
#define CVF_ANY_MODEL (1 << 28)
#define CVF_RHS (1 << 29)
#define CVF_LHS (1 << 30)
#define CVF_GLOBAL (1 << 27)
#define CVF_FUNCTION_ARGUMENT (1 << 26)

class consoleScope;

class consoleVariable {
friend class consoleScope;
public:
	consoleVariable() {initToNothing();};
	consoleVariable(const std::string &name, const consoleVariable *cv);
	consoleVariable(const std::string &name, const e3ga &mv);
	consoleVariable(const std::string &name, const p3ga &mv);
	consoleVariable(const std::string &name, const c3ga &mv);
	consoleVariable(const std::string &name, const c5ga &mv);
	consoleVariable(const std::string &name, const i2ga &mv);
	consoleVariable(const std::string &name, const e3ga *mv);
	consoleVariable(const std::string &name, const p3ga *mv);
	consoleVariable(const std::string &name, const c3ga *mv);
	consoleVariable(const std::string &name, const c5ga *mv);
	consoleVariable(const std::string &name, const i2ga *mv);
	consoleVariable(const consoleVariable &cv);
	~consoleVariable();

	void initToNothing();

	consoleVariable& operator=(const consoleVariable &cv);

	int set(const std::string &name, const e3ga *mv);
	int set(const std::string &name, const p3ga *mv);
	int set(const std::string &name, const c3ga *mv);
	int set(const std::string &name, const c5ga *mv);
	int set(const std::string &name, const i2ga *mv);
	void set(const consoleVariable &cv);

	/*int constant(int c); // set constant to true or false
	int constant() const; // returns constant*/

	int rhs(int c); // set rhs to true or false
	int rhs() const; // returns rhs
	int lhs(int c); // set lhs to true or false
	int lhs() const; // returns lhs

	int global(int g); // set global to true or false
	int global() const; // returns global

	int functionArgument(int g); // set function argument to true or false
	int functionArgument() const; // returns function argument

	void next(consoleVariable *pnext); // set/gets next in list (if any)
	consoleVariable *next();
	consoleVariable *m_next;

	static void castC5gaToC3ga(const c5ga &vc, c3ga &vp);

	consoleVariable *castToE3ga() const;
	consoleVariable *castToP3ga() const;
	consoleVariable *castToC3ga() const;
	consoleVariable *castToC5ga() const;
	consoleVariable *castToI2ga() const;

	e3ga &e() const;
	p3ga &p() const;
	c3ga &c() const;
	c5ga &c5() const;
	i2ga &i2() const;

	//mvInt *I() const;
	int model() const;
	mvInt *interpretation() const;
	int grade() const;

	int name(const std::string &name); //const char *name);
	const std::string &name() const;
	int nameEquals(const std::string &name) const;

	int op() const;
	int op(int o);

	int drawMode() const;
	int drawMode(int mode);
	int creationFlags() const;
	int creationFlags(int flags);
	int forceFlags() const ;
	const float *color() const;
	int color4(const float c[4]);
	int color3(const float c[3]);
	int color4(float r, float g, float b, float a);
	int color3(float r, float g, float b);
	int alpha(float alpha);
	float alpha() const;

	// keep track off what draw properties have been explicitly set by the user
	int modifiedColor();
	int modifiedAlpha();
	int modifiedDrawMethod();
	int modifiedHide();
	int modifiedStipple();
	int modifiedOri();
	int modifiedMute();
	int modifiedWireframe();
	int modifiedOutline();
	int modifiedMagnitude();
	int modifiedShade();

	int isTrue() const; // return this != 0.0
	GAIM_FLOAT scalar() const; // return the scalar part of this

	int print(const char *str) const;
	const char *string() const;
protected:
	std::string m_name;
	void *m_mv;
	int m_model;
	int m_op; // operator (as in consoleoperators.h)

	int getFlag(int flag) const;
	int setFlag(int flag, int val);
	int m_flags; // CVF_XXX

	// properties used when this variable is assigned to an object
	int m_drawMode;
	int m_creationFlags;
	int m_forceFlags;
	float m_color[4];

	consoleVariable *castE3gaToP3ga() const;
	consoleVariable *castE3gaToC3ga() const;
	consoleVariable *castE3gaToC5ga() const;
	consoleVariable *castE3gaToI2ga() const;

	consoleVariable *castP3gaToE3ga() const;
	consoleVariable *castP3gaToC3ga() const;
	consoleVariable *castP3gaToC5ga() const;
	consoleVariable *castP3gaToI2ga() const;

	consoleVariable *castC3gaToE3ga() const;
	consoleVariable *castC3gaToP3ga() const;
	consoleVariable *castC3gaToC5ga() const;
	consoleVariable *castC3gaToI2ga() const;

	consoleVariable *castI2gaToE3ga() const;
	consoleVariable *castI2gaToP3ga() const;
	consoleVariable *castI2gaToC3ga() const;
	consoleVariable *castI2gaToC5ga() const;

	consoleVariable *castC5gaToE3ga() const;
	consoleVariable *castC5gaToP3ga() const;
	consoleVariable *castC5gaToC3ga() const;
	consoleVariable *castC5gaToI2ga() const;

	void deleteMV();

	static int m_tempVarCount;
};
#endif /* _CONSOLE_VARIABLE_H_ */
