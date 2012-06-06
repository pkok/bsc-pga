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

#include "state.h"
#include "uistate.h"
#include "mainwindow.h"
#include "object.h"
#include "glwindow.h"
#include "gaincludes.h"
#include "util.h"
#include "console/consolestatement.h"
#include "console/consolecontrol.h"
#include "console/consolescope.h"
#include "console/consolevariable.h"

#include <algorithm>
#include <functional>

static inline void printColor(FILE *F, const char *colName, float c[4]) {
	fprintf(F, "%s %f %f %f %f\n", colName, c[0], c[1], c[2], c[3]);
}

int state::writeStateToGeoFile(const char *filename) {
	int i;
	state::OI oi;

	FILE *F = fopen(filename, "w+");
	if (F == NULL) {
		cprintf("state::writeStateToGeoFile(): can not open '%s' for writing.\n", filename);
		return -1;
	}

	fprintf(F, "clear\n");

	for (i = 0; i < 3; i++)
		fprintf(F, "factor e3ga %d [%s]\n", i + 1, m_e3gaFactor[i].string("%2.15e"));
	for (i = 0; i < 4; i++)
		fprintf(F, "factor p3ga %d [%s]\n", i + 1, m_p3gaFactor[i].string("%2.15e"));
	for (i = 0; i < 5; i++)
		fprintf(F, "factor c3ga %d [%s]\n", i + 1, m_c3gaFactor[i].string("%2.15e"));

	// first output every object
	for (oi = g_state->m_objects.begin(); oi != g_state->m_objects.end(); oi++) {
//		printf("Writing %s\n", m_object[i]->m_name);
		oi->second->writeToGeoFile(F);
	}
	// output current global state

	fprintf(F, "title \"%s\"\n", gui_state->m_mainWindow->label());
	printColor(F, "fgcolor", m_fgColor);
	printColor(F, "bgcolor", m_bgColor);
	printColor(F, "olcolor", m_olColor);
	printColor(F, "cvcolor", m_cvColor);

	fprintf(F, "fontsize %f\n", m_fontSize);
	fprintf(F, "clip %f\n", m_clipDistance);

	//float m_poFactor, m_poUnits; // polygon offset todo???
	
	// todo: size of window / console???

	fprintf(F, "tsmode %s\n", m_tsMode);
	fprintf(F, "tsfont %s\n", m_tsFont);

	fprintf(F, "eyepos [%s]\n", gui_state->m_glWindow->getCamPos().string("%e"));
	e3ga B;
	rotor2Bivector(B, gui_state->m_glWindow->getCamOri());
	fprintf(F, "eyeori [%s]\n", (-B).string("%e"));

	writeConsoleControlsToGeoFile(F); 

	for (i = 0; i < (int)m_dynStmt.size(); i++) {
		char *str = m_dynStmt[i].ds()->string(0,0);
		if (str) {
			if (m_dynStmt[i].name().size())
				fprintf(F, "console dynamic{%s : %s}\n", m_dynStmt[i].name().c_str(), str);
			else fprintf(F, "console dynamic{%s}\n", str); 
			free(str);
		}
	}

	// todo: store animation state??
	
	// constants
	m_globalScope->writeConstantsToGeoFile(F);

	fclose(F);

	return 0;
}

int consoleGlobalScope::writeConstantsToGeoFile(FILE *F) {
	for (UCI I = m_userConstants.begin(); I != m_userConstants.end(); I++) {
		fprintf(F, "console add_const(%s = %s);\n", I->first.c_str(), I->second.string());
	}
	return 0;
}




int consoleControlBool::writeToGeoFile(FILE *F) {
	fprintf(F, "console ctrl_bool(%s = %d);\n", name(), lookupValueBool());

	return 0;
}

int consoleControlRange::writeToGeoFile(FILE *F) {
	if (m_valueSlider) {
		fprintf(F, "console ctrl_range(%s = %e, %e, %e, %e);\n", name(), lookupValue(), 
			m_valueSlider->minimum(), m_valueSlider->maximum(), m_valueSlider->step());
	}

	return 0;
}

int consoleControlSelection::writeToGeoFile(FILE *F) {
	fprintf(F, "console ctrl_select(%s = %e", name(), lookupValue());

	int i = 0;
	while (m_menuItems[i].text) {
		fprintf(F, ", %s = %e", m_menuItems[i].text, m_menuValues[i]);
		i++;
	}

	fprintf(F, ");\n");

	return 0;
}

int consoleControl::writeToGeoFileMemFun(FILE *F) {
	return writeToGeoFile(F);
}

int state::writeConsoleControlsToGeoFile(FILE *F) {
	for (std::vector<consoleControl*>::const_iterator I = m_consoleControls.begin();
		I != m_consoleControls.end(); I++)
		(*I)->writeToGeoFileMemFun(F);
	
	
	/*
	// keep? or is this not portable or just MS???? Fuck the STL!

	std::for_each(m_consoleControls.begin(), m_consoleControls.end(), 
		std::bind2nd(std::mem_fun1(&consoleControl::writeToGeoFileMemFun), F) );
*/
	return 0;
}


int object::writeToGeoFile(FILE *F) {

	printColor(F, "fgcolor", m_fgColor);
	printColor(F, "bgcolor", m_bgColor);
	printColor(F, "olcolor", m_olColor);

	fprintf(F, "fontsize %f\n", m_fontSize);


	return 0;
}

int object::writeToGeoFileProperties(FILE *F) {
	// m_dmMenuIdx
	// m_drawMode

	if (m_drawMode & OD_HIDE) fprintf(F, "hide ");
	if (m_drawMode & OD_STIPPLE) fprintf(F, "stipple ");
	if (m_drawMode & OD_ORI) fprintf(F, "orientation ");
	if (m_drawMode & OD_WIREFRAME) fprintf(F, "wireframe ");
	if (m_drawMode & OD_MAGNITUDE) fprintf(F, "magnitude ");
	if (m_drawMode & OD_SHADE) fprintf(F, "shade ");
	if (m_drawMode & OD_OUTLINE) fprintf(F, "outline ");

	if (m_dmMenuIdx >= 0) fprintf(F, "dm%d", m_dmMenuIdx+1);


		/*
		else if (!strcmpnc(str[i], "versor")) creationFlags |= OC_VERSOR;
		else if (!strcmpnc(str[i], "blade")) creationFlags |= OC_BLADE;
		*/

	return 0;
}

int e3gaObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);

	fprintf(F, "e3ga \"%s\" [%s] ", m_name.c_str(), m_mv.string("%2.20e"));
	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}


int p3gaObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);

	fprintf(F, "p3ga \"%s\" [%s] ", m_name.c_str(), m_mv.string("%2.20e"));
	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}

int c3gaObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);

	fprintf(F, "c3ga \"%s\" [%s] ", m_name.c_str(), m_mv.string("%2.20e"));
	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}

int c5gaObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);

	fprintf(F, "c5ga \"%s\" [%s] ", m_name.c_str(), m_mv.string("%2.20e"));
	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}

int i2gaObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);

	fprintf(F, "i2ga \"%s\" [%s] ", m_name.c_str(), m_mv.string("%2.20e"));
	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}

int textObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);
	char labelPosName[1024];

	// fix saving for labels.. remember image possibilyt

	// print out typeset mode & font
	fprintf(F, "tsmode %s\n", m_tsMode);
	fprintf(F, "tsfont %s\n", m_tsFont);

	// get label position
	if (!(m_flags & LABEL_DYNAMIC))
		sprintf(labelPosName, "[%s]", m_pos.string("%e"));
	else sprintf(labelPosName, "\"%s\"", m_pointName.c_str());

	fprintf(F, "label \"%s\" %s \"%s\" ", m_name.c_str(), labelPosName, m_text);

	if (m_flags & LABEL_2D) fprintf(F, "flag_2d ");
	if (m_flags & LABEL_3D) fprintf(F, "flag_3d ");
	if (m_flags & LABEL_CX) fprintf(F, "flag_cx ");
	if (m_flags & LABEL_CY) fprintf(F, "flag_cy ");
	if (m_flags & LABEL_PX) fprintf(F, "flag_px ");
	if (m_flags & LABEL_PY) fprintf(F, "flag_py ");
	if (m_flags & LABEL_NX) fprintf(F, "flag_nx ");
	if (m_flags & LABEL_NY) fprintf(F, "flag_ny ");
	if (m_flags & LABEL_ACX) fprintf(F, "flag_acx ");
	if (m_flags & LABEL_DYNAMIC) fprintf(F, "flag_dynamic ");
	if (m_flags & LABEL_IMAGE) fprintf(F, "flag_image ");
	if (m_flags & LABEL_FULLSCREEN) fprintf(F, "flag_fullscreen ");

	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;
}

int polygonObject::writeToGeoFile(FILE *F) {
	object::writeToGeoFile(F);
	int i;

	// todo: maybe make temp vertices indices a global var? increment on each use, reset on new save?

	// write vertices
	for (i = 0; i < m_nbVertices; i++) {
		fprintf(F, "e3ga \"%s vertex %d\" [%s] hide \n", m_name.c_str(), i, e3ga(GRADE1, m_vertex + i * 3).string("%2.20e"));
	}

	fprintf(F, "%s \"%s\" %d ", (m_simplex) ? "simplex" : "polygon", m_name.c_str(), m_nbVertices);

	for (i = 0; i < m_nbVertices; i++) {
		if (m_mode & OC_DYNAMIC) {
			fprintf(F, "\"%s\" ", m_vertexName[i]);
		}
		else {
			fprintf(F, "\"%s vertex %d\" ", m_name.c_str(), i);
		}
	}

	if (m_mode & OC_DYNAMIC) fprintf(F, "dynamic ");

	writeToGeoFileProperties(F);
	fprintf(F, "\n");
	return 0;

}


int meshObject::writeToGeoFile(FILE *F) {
	int i, j;
	object::writeToGeoFile(F);

	fprintf(F, "mesh \"%s\" ", m_name.c_str());

	if (m_mode & OC_DYNAMIC) fprintf(F, "dynamic "); 

	if (m_mode & OC_COMPUTE_NORMALS_FLAT) fprintf(F, "compute_normals_flat ");
	else if (m_mode & OC_COMPUTE_NORMALS_GOURAUD) fprintf(F, "compute_normals_gouraud ");
	else if (m_mode & OC_SPECIFY_NORMALS) fprintf(F, "specify_normals ");

	writeToGeoFileProperties(F);
	fprintf(F, "\n");

	for (i = 0; i < m_nbVertices; i++) {
		if (m_vertex[i].posName)
			fprintf(F, "meshvertex \"%s\" %d \"%s\"\n", m_name.c_str(), i, m_vertex[i].posName);
		else 
			fprintf(F, "meshvertex \"%s\" %d [%s]\n", m_name.c_str(), i, e3ga(GRADE1, m_vertex[i].pos).string("%e"));

		if (m_vertex[i].nlName)
			fprintf(F, "meshnormal \"%s\" %d \"%s\"\n", m_name.c_str(), i, m_vertex[i].nlName);
		else 
			fprintf(F, "meshnormal \"%s\" %d [%s]\n", m_name.c_str(), i, e3ga(GRADE1, m_vertex[i].nl).string("%e"));
	}

	for (i = 0; i < m_nbFaces; i++) {
		fprintf(F, "meshface \"%s\" ", m_name.c_str());
	
		for (j = 0; j < m_face[i].nbVtx; j++)
			fprintf(F, "%d ", m_face[i].vtxIdx[j]);

		fprintf(F, "\n");
	}

	return 0;
}
