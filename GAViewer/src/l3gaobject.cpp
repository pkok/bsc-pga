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

#include "gl_includes.h"

#include "object.h"
#include "glwindow.h"
#include "state.h"
#include "util.h"
#include "osdep.h"
#include "draw.h"
#include "geosphere.h"
#include "uistate.h"

Fl_Menu_Item gui_l3gaIdealLineDrawMethods[] = {
	{"Curve", 0, NULL, (void*)DRAW_LINE_CURVE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_LINE_CURLYTAIL, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKS, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKCROSSES, 0},
	{"Horizon, radius", 0, NULL, (void*)DRAW_IDEAL_LINE_RADIUS, 0},
	{"Horizon, hooks", 0, NULL, (void*)DRAW_IDEAL_LINE_HOOKS, 0},
	{0}
};

Fl_Menu_Item gui_l3gaLineDrawMethods[] = {
	{"Curve", 0, NULL, (void*)DRAW_LINE_CURVE, 0},
	{"Curly tail", 0, NULL, (void*)DRAW_LINE_CURLYTAIL, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKS, 0},
	{"Hooks", 0, NULL, (void*)DRAW_LINE_HOOKCROSSES, 0},
	{0}
};

Fl_Menu_Item gui_l3gaScrewDrawMethods[] = {
  {"Single screw", 0, NULL, (void*)DRAW_SCREW_SPIRAL, 0},
  {"Screw line", 0, NULL, (void*)DRAW_SCREW_LINE, 0},
  {0}
};

Fl_Menu_Item gui_l3gaIdealPencilDrawMethods[] = {
  {"Horizon, radius", 0, NULL, (void*)DRAW_IDEAL_LINE_RADIUS, 0},
  {"Horizon, hooks", 0, NULL, (void*)DRAW_IDEAL_LINE_HOOKS, 0},
  {0}
};

Fl_Menu_Item gui_l3gaRuledPlaneMethods[] = {
  {"Lines", 0, NULL, (void*)DRAW_RULED_PLANE, 0},
  {0}
};

Fl_Menu_Item gui_l3gaPencilDrawMethods[] = {
  {"Lines", 0, NULL, (void*)DRAW_PENCIL, 0},
  {0}
};


l3gaObject::l3gaObject(const l3ga &mv, const std::string &name /*= std::string("")*/, int drawMode /*= 0*/, int creationFlags /*= 0*/, int forceFlags /*= 0*/) 
	: object(OT_L3GA, name, drawMode, creationFlags) {
	initToNothing();
	m_mv = mv;
	m_int.interpret(m_mv, creationFlags);

	// set general properties
	m_properties = OP_NAME | OP_DESCRIPTION;

	// unless the object is of unknown type, set the drawing properties
	if (m_int.m_type != MVI_UNKNOWN) {
		m_properties |= OP_HIDE | OP_FGCOLOR | OP_DRAWMODE;
		if (m_int.versor()) m_properties |= OP_BGCOLOR | OP_OLCOLOR;

		if (!(forceFlags & OFF_SHADE))
			m_drawMode |= OD_SHADE;

		// set draw method + menu
		if (m_int.blade()) {
      switch (m_int.type()) {
        case MVI_ZERO:
          // don't draw anything
          break;
        case MVI_SCALAR:
          // don't draw anything
          break;
        case MVI_IDEAL_LINE:
          m_properties |= OP_DRAWMETHOD;
          m_drawMode |= OD_STIPPLE;
          m_dmMenu = gui_l3gaIdealLineDrawMethods;
          m_dmMenuIdx = DRAW_IDEAL_LINE_RADIUS;
          break;
        case MVI_LINE:
          m_properties |= OP_DRAWMETHOD;
          m_dmMenu = gui_l3gaLineDrawMethods;
          m_dmMenuIdx = DRAW_LINE_HOOKS;
          break;
        case MVI_SCREW:
          m_properties |= OP_DRAWMETHOD;
          m_drawMode |= OD_ORI;
          m_dmMenu = gui_l3gaScrewDrawMethods;
          m_dmMenuIdx = DRAW_SCREW_SPIRAL;
          break;
        case MVI_IDEAL_LINE_PENCIL:
          m_properties |= OP_DRAWMETHOD;
          m_drawMode |= OD_STIPPLE;
          m_dmMenu = gui_l3gaIdealPencilDrawMethods;
          m_dmMenuIdx = DRAW_IDEAL_LINE_RADIUS;
          break;
        case MVI_RULED_PLANE:
          m_properties |= OP_DRAWMETHOD;
          m_dmMenu = gui_l3gaRuledPlaneMethods;
          m_dmMenuIdx = DRAW_RULED_PLANE;
          break;
        case MVI_LINE_PENCIL:
          m_properties |= OP_DRAWMETHOD;
          m_dmMenu = gui_l3gaPencilDrawMethods;
          m_dmMenuIdx = DRAW_PENCIL;
          break;
        case MVI_LINE_PAIR:
          m_properties |= OP_DRAWMETHOD;
          m_dmMenu = gui_l3gaLineDrawMethods;
          m_dmMenuIdx = DRAW_LINE_HOOKS;
          break;
        case MVI_IDEAL_LINE_PAIR:
          m_properties |= OP_DRAWMETHOD;
          m_dmMenuIdx = DRAW_LINE_CURVE;
          break;
        case MVI_POINT:
          m_properties |= OP_DRAWMETHOD;
          break;
        case MVI_SPACE: // pseudoscalar
          // don't draw anything
          break;
			}
      /*
			else if ((m_int.type() == MVI_FREE_BIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_BIVECTOR)) {
			}
			else if ((m_int.type() == MVI_FREE_TRIVECTOR) || (m_int.type() == MVI_BOUND_TANGENT_TRIVECTOR)) {
			}
			else if (m_int.type() == MVI_POINT_PAIR) {
			}
      */
		}
	}

	// override draw method with user setting
	if (creationFlags & OC_DM7)
		m_dmMenuIdx = ((creationFlags & OC_DM7) >> OC_DMBASE) - 1;
}

l3gaObject::~l3gaObject() {

	initToNothing();
}

void l3gaObject::initToNothing() {
	m_mv = 0;
}

int l3gaObject::copy(const object *o, int &propertiesChanged, int forceFlags /*= -1*/) {
	int err;
	if ( (err = object::copy(o, propertiesChanged, forceFlags)) != 0) return err;
	const l3gaObject *l3gaO = (const l3gaObject *)o;

	if ((m_mv - l3gaO->m_mv).norm_a() != 0.0)
		propertiesChanged |= OP_DESCRIPTION;
	m_mv = l3gaO->m_mv;
	m_int.copy(&l3gaO->m_int);

	return 0;
}

int l3gaObject::pick(glwindow *window) {
	return draw(window);
}

int l3gaObject::draw(glwindow *window) {
	// draws nothing meaningful yet (only sphere at origin for scalar)
	TubeDraw &T = gui_state->m_tubeDraw;
	GAIM_FLOAT x, y, z, c, scale, scaleSign;
	int s;
	e3ga e3gaR;
	float rotM[16];
  std::string _type;

	if (m_type == MVI_UNKNOWN) return 0;

//	window->enableClippingPlanes();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	glLineWidth((float)gui_state->m_lineWidth);

	// handle transparency (btw: objects are not yet sorted on depth yet....
	if (window->depthMaskAllowedOff() && (fgColor(3) < 0.99)) {
		glDepthMask(GL_FALSE); // don't write in depth buffer
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else {
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	setFgColor();

	if (m_drawMode & OD_SHADE) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	if (m_drawMode & OD_STIPPLE) {
		glEnable(GL_POLYGON_STIPPLE);
		glEnable(GL_LINE_STIPPLE);
	}
	else {
		glDisable(GL_POLYGON_STIPPLE);
		glDisable(GL_LINE_STIPPLE);
	}

	glMatrixMode(GL_MODELVIEW);
	GAIM_FLOAT stepSize = 0.1;
	GAIM_FLOAT scaleConst = g_state->m_clipDistance * sqrt(2.0);
	GAIM_FLOAT scaleMag = 1.0;
  double dir[3] = {1.0, 0.0, 0.0};

  if (m_int.blade()) {
    switch (m_int.type()) {
      case MVI_ZERO:
        // don't draw anything
        break;
      case MVI_SCALAR:
        // don't draw anything
        break;
      case MVI_IDEAL_LINE:
        drawIdealLine(NULL, m_int.m_vector[0], m_int.m_scalar[0], m_dmMenuIdx, m_drawMode, this);
        break;
      case MVI_LINE:
        drawLine(m_int.m_point[0], m_int.m_vector[0], m_int.m_scalar[0], m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
        break;
      case MVI_SCREW:
        drawScrew(m_int.m_point[0], m_int.m_vector[0], m_int.m_scalar[0], m_int.m_scalar[1], m_dmMenuIdx, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
        break;
      case MVI_IDEAL_LINE_PENCIL:
        drawCirclePencil(NULL, m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2], m_int.m_scalar[0], m_dmMenuIdx, m_drawMode, this);
        break;
      case MVI_RULED_PLANE:
        drawRuledPlane(m_int.m_point[0], m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2], m_int.m_scalar[0], DRAW_RULED_PLANE, 0, this);
        break;
      case MVI_LINE_PENCIL:
        /*
        scalar 0: weight
        point 0: point
        vector 0: m_int.m_vector[0]
        vector 1: orthogonal to vector 0 and 2
        vector 2: orthogonal to vector 0 and 1
        */
        scale = (m_drawMode & OD_MAGNITUDE)
          ? sqrt(fabs(m_int.m_scalar[0]) / M_PI) 
          : 1.0;
        drawLinePencil(m_int.m_point[0], scale, m_int.m_vector[0], m_int.m_vector[1], m_int.m_vector[2], m_dmMenuIdx, m_drawMode, this);
        break;
      case MVI_LINE_PAIR:
        if (m_int.dual()) {
          drawDualLinePair(m_int.m_point[0], m_int.m_vector[0], m_int.m_point[1], m_int.m_vector[1], m_int.m_scalar[0], m_dmMenuIdx, m_drawMode, this);
        }
        else {
          drawLine(m_int.m_point[0], m_int.m_vector[0], m_int.m_scalar[0], m_dmMenuIdx, m_drawMode, this);
          drawLine(m_int.m_point[1], m_int.m_vector[1], m_int.m_scalar[0], m_dmMenuIdx, m_drawMode, this);
        }
        break;
      case MVI_IDEAL_LINE_PAIR:
        drawLine(m_int.m_point[1], m_int.m_vector[1], m_int.m_scalar[0], DRAW_LINE_HOOKS, (m_drawMode & OD_ORI) ? 0x01 : 0, this);
        glEnable(GL_POLYGON_STIPPLE);
        glEnable(GL_LINE_STIPPLE);
        drawIdealLine(m_int.m_point[0], m_int.m_vector[0], m_int.m_scalar[0], DRAW_IDEAL_LINE_HOOKS, m_drawMode, this);
        break;
      case MVI_POINT:
        drawPoint(m_int.m_point[0], m_int.m_scalar[0], 0, this);
        break;
      case MVI_SPACE:
        // don't draw anything
        break;
      default:
        break;
    }
  }
  else {
    if (m_int.type() != MVI_UNKNOWN)
      printf("Can not (yet) draw the object #%d\n", m_int.type());
    return 0;
  }

	return  0;
}

int l3gaObject::translate(glwindow *window, double depth, double motionX, double motionY) {
	// can not translate yet
  static l3ga t1(0.5 * l3ga::e12 ^ l3ga::e31), 
              t2(0.5 * l3ga::e23 ^ l3ga::e12), 
              t3(0.5 * l3ga::e31 ^ l3ga::e23), 
              r1(0.5 * ((l3ga::e03 ^ l3ga::e23) - (l3ga::e01 ^ l3ga::e12))),
              r2(0.5 * ((l3ga::e02 ^ l3ga::e12) - (l3ga::e03 ^ l3ga::e31))),
              r3(0.5 * ((l3ga::e01 ^ l3ga::e31) - (l3ga::e02 ^ l3ga::e23)));
	e3ga v;
	window->vectorAtDepth(depth, motionX, -motionY, v);
  l3ga versor;
  int modified = 0;

  if (m_int.blade()) {
    switch (m_int.type()) {
      case MVI_ZERO:
      case MVI_SCALAR:
      case MVI_LINE:
      case MVI_SCREW:
      case MVI_RULED_PLANE:
      case MVI_LINE_PENCIL:
      case MVI_LINE_PAIR:
      case MVI_IDEAL_LINE_PAIR:
      case MVI_POINT:
      case MVI_SPACE:
      default:
        // translate; default behavior when dragging objects.
        versor = (v[GRADE1][E3GA_E3] * t3).exp() * (v[GRADE1][E3GA_E2] * t2).exp() * (v[GRADE1][E3GA_E1] * t1).exp();
        m_mv = versor.inverse() * m_mv * versor;
        modified = 1;
        break;
      case MVI_IDEAL_LINE:
      case MVI_IDEAL_LINE_PENCIL:
        // rotate; these elements are translation invariant.
        versor = (v[GRADE1][E3GA_E3] * r3).exp() * (v[GRADE1][E3GA_E2] * r2).exp() * (v[GRADE1][E3GA_E1] * r1).exp();
        m_mv = versor.inverse() * m_mv * versor;
        modified = 1;
        break;
    }
  }

  if (modified) {
		m_int.interpret(m_mv); // reinterpret
		g_state->modified(m_name);
  }

	return 0;
}


int l3gaObject::description(char *buf, int bufLen, int sl /* = 0 */) {
	buf[0] = 0;

	if (m_int.type() == MVI_UNKNOWN) {
		if (sl) sprintf(buf, "%s: unknown l3ga object", m_name.c_str());
		else sprintf(buf, "Unknown l3ga object.\nCoordinates: %s", m_mv.string());
	}
  else if (m_int.blade()) {
    switch (m_int.type()) {
    case MVI_SCALAR: // scalar 0: weight
        if (sl) sprintf(buf, "%s: l3ga scalar%s, weight: %f", m_name.c_str(), (m_int.dual()) ? " dual" : "", m_int.m_scalar[0]);
			else sprintf(buf, "l3ga scalar%s\nWeight: %f", 
				(m_int.dual()) ? " dual" : "",
				m_int.m_scalar[0]); 
			break;
    case MVI_LINE: // scalar 0: weight; point 0: closest to origin; vector 0: direction of line
      if (sl) sprintf(buf, "%s: l3ga line%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

      else sprintf(buf, "l3ga line%s\nWeight: %f\nDirection: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? " dual" : "",
          m_int.m_scalar[0], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
          m_mv.string());
      /*
      else sprintf(buf, "l3ga line%s\nWeight: %f\nd = [%2.2f, %2.2f, %2.2f]\nm = [%2.2f, %2.2f, %2.2f]",
          (m_int.dual()) ? " dual" : "",
          m_int.m_scalar[0],
          m_mv[GRADE1][L3GA_E01],
          m_mv[GRADE1][L3GA_E02],
          m_mv[GRADE1][L3GA_E03],
          m_mv[GRADE1][L3GA_E23],
          m_mv[GRADE1][L3GA_E31],
          m_mv[GRADE1][L3GA_E12]);
          */
      break;
    case MVI_SCREW:
      if (sl) sprintf(buf, "%s: l3ga screw%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

      else sprintf(buf, "l3ga screw%s\nWeight: %f\nPitch: %f\nDirection: %2.2f %2.2f %2.2f\nPoint closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? " dual" : "",
          m_int.m_scalar[0], 
          m_int.m_scalar[1], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
          m_mv.string());
      break;
    case MVI_IDEAL_LINE:
      if (sl) sprintf(buf, "%s: l3ga line%s at infinity", m_name.c_str(), (m_int.dual()) ? " dual" : "");

      else sprintf(buf, "l3ga line%s at infinity\nWeight: %f\nDirection: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? " dual" : "",
          m_int.m_scalar[0], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_mv.string());
      break;
    case MVI_IDEAL_LINE_PENCIL:
      if (sl) sprintf(buf, "%s: l3ga %sline pencil at infinity", m_name.c_str(), (m_int.dual()) ? "dual " : "");

      else sprintf(buf, "l3ga %sline pencil at infinity\nWeight: %f\nNormal: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? "dual " : "",
          m_int.m_scalar[0], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_mv.string());
      break;
    case MVI_RULED_PLANE:
    case MVI_LINE_PENCIL:
      if (sl) sprintf(buf, "%s: l3ga %sline pencil", m_name.c_str(), (m_int.dual()) ? "dual " : "");

      else sprintf(buf, "l3ga %sline pencil\nWeight: %f\nNormal: %2.2f %2.2f %2.2f\nCenter:%2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? "dual " : "",
          m_int.m_scalar[0], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2],
          m_mv.string());
      break;
    case MVI_IDEAL_LINE_PAIR:
    case MVI_LINE_PAIR:
      if (sl) sprintf(buf, "%s: l3ga %sline pair", m_name.c_str(), (m_int.dual())? "dual " : "");

      else sprintf(buf, "l3ga %sline pair\nWeight: %f\nDirection 1: %2.2f %2.2f %2.2f\nPoint 1 closest to origin: %2.2f %2.2f %2.2f\nDirection 2: %2.2f %2.2f %2.2f\nPoint 2 closest to origin: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? "dual " : "",
          m_int.m_scalar[0], 
          m_int.m_vector[0][0], m_int.m_vector[0][1], m_int.m_vector[0][2], 
          m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
          m_int.m_vector[1][0], m_int.m_vector[1][1], m_int.m_vector[1][2], 
          m_int.m_point[1][0], m_int.m_point[1][1], m_int.m_point[1][2], 
          m_mv.string());
      break;
    case MVI_POINT: 
      if (sl) sprintf(buf, "%s: l3ga point%s", m_name.c_str(), (m_int.dual()) ? " dual" : "");

      else sprintf(buf, "l3ga point%s\nWeight: %f\nPoint: %2.2f %2.2f %2.2f\nCoordinates: %s", 
          (m_int.dual()) ? " dual" : "",
          m_int.m_scalar[0], 
          m_int.m_point[0][0], m_int.m_point[0][1], m_int.m_point[0][2], 
          m_mv.string());
      break;
    case MVI_SPACE: // scalar 0: weight
      if (sl) sprintf(buf, "%s: l3ga %spseudoscalar, weight: %f", m_name.c_str(), (m_int.dual()) ? "dual " : "", m_int.m_scalar[0]);
      else sprintf(buf, "l3ga %spseudoscalar\nWeight: %f", 
          (m_int.dual()) ? "dual " : "",
          m_int.m_scalar[0]); 
      break;
    default:
      if (sl) sprintf(buf, "%s: unknown l3ga blade.", m_name.c_str());
      else sprintf(buf, "Unknown l3ga blade.\nCoordinates: %s", m_mv.string());
      break;
    }
  }
  else if (m_int.versor()) {
    if (sl) sprintf(buf, "%s: l3ga object", m_name.c_str());
    else sprintf(buf, "l3ga object\nCoordinates: %s", m_mv.string());
  }
  else {
		if (sl) sprintf(buf, "%s: unknown l3ga object", m_name.c_str());
		else sprintf(buf, "Unknown l3ga object.\nCoordinates: %s", m_mv.string());
  }
    

	return 0;
}

float l3gaObject::drawSortValue() {
	return (fgColor(3) == 1.0) ? 1.0f : 2.0f;
}

std::string l3gaObject::toString(const char *floatPrec /* = "%e" */) {
	return std::string("\"" + m_name + "\" = " +  m_mv.string(floatPrec));
}
