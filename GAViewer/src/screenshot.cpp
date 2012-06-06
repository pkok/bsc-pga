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
#include <png.h>
#include <string>

#include "glwindow.h"
#include "state.h"
#include "uistate.h"
#include "pngwrapper.h"


int UIstate::setupScreenshot(const std::string &filename, int width, int height, bool alsoWithoutLabels) {

	if ((width * height <= 0) || (width < 0)) {
		cprintf("UIstate::setupScreenshot(): Invalid screenshot size: %d x %d\n", width, height);
	}

	m_screenShotOnNextRedraw = 3; // 3 = #redraws before screenshot
	m_ssFilename = filename;
	m_ssWidth = width;
	m_ssHeight = height;
	m_ssAlsoNoLabels = alsoWithoutLabels;

	m_glWindow->redraw(); // force redraw

	return 0;
}


int glwindow::performScreenShot() {
	gui_state->m_screenShotOnNextRedraw = 0;
	m_screenShotActive = true;

	int ssWidth = gui_state->m_ssWidth, ssHeight = gui_state->m_ssHeight;


	double originalTextScale = gui_state->m_textScale;
	std::string originalFilename = gui_state->m_ssFilename;

	for (int t = 0; t < 2; t++) {
		// handle 'no labels' flag:
		if ((t == 1) && (!gui_state->m_ssAlsoNoLabels)) break;
		if (t == 1) {
			gui_state->setTextScale(0.0);
			std::string::size_type idx = gui_state->m_ssFilename.find(".png");
			if (idx == std::string::npos) {
				gui_state->m_ssFilename += "_wol"; // "wol" = without labels
			}
			else {
				gui_state->m_ssFilename.insert(idx, "_wol"); // "wol" = without labels
			}
		}
	//m_ssAlsoNoLabels
	//m_textScale = 1.0;

		// compute sizes of various stuff
		int glw = w() & 0xFFFFFFFC, glh = h(); // to prevent some weird bug, width must be multiple of 4...

		int nbTilesHor = (ssWidth / glw) + ((ssWidth % glw) != 0);
		int nbTilesVer = (ssHeight / glh) + ((ssHeight % glh) != 0);
		m_ssViewportWidth = (ssWidth / nbTilesHor) & 0xFFFFFFFC; // to prevent some weird bug, width must be multiple of 4...
		m_ssViewportHeight = ssHeight / nbTilesVer;
		int nbTiles = nbTilesHor * nbTilesVer;

		ssWidth = nbTilesHor * m_ssViewportWidth;
		ssHeight = nbTilesVer * m_ssViewportHeight;

		cprintf("Screenshot: size: %d x %d\nFile: %s\n", ssWidth, ssHeight, gui_state->m_ssFilename.c_str());

		// allocate memory
		int rowSize = ssWidth * m_ssViewportHeight * 3;
		int tileSize = m_ssViewportWidth * m_ssViewportHeight * 3;
		unsigned char *pixels = (unsigned char *)malloc(rowSize + tileSize);
		if (pixels == NULL) {
			cprintf("glwindow::performScreenShot(): Could not allocate %d bytes for screenshot\n", rowSize + tileSize);
			return -1;
		}
		unsigned char *tmpPixels = pixels + rowSize;

		// open PNG for saving...
		FILE *fp = fopen(gui_state->m_ssFilename.c_str(), "wb+");

		if (!fp) {
			cprintf("glwindow::performScreenShot(): Could not create %s\n", gui_state->m_ssFilename.c_str());
			m_screenShotActive = false;
			free(pixels);
			return -1;
		}
		png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png_ptr) {
			cprintf("glwindow::performScreenShot(): Could not create png struct\n");
			fclose(fp);
			m_screenShotActive = false;
			free(pixels);
			return -1;
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (!info_ptr) {
			cprintf("glwindow::performScreenShot(): Could not create png info struct\n");
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			fclose(fp);
			m_screenShotActive = false;
			free(pixels);
			return -1;
		}

		png_init_io(png_ptr, fp);

		png_set_IHDR(png_ptr, info_ptr, ssWidth, ssHeight, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);	

		png_write_info(png_ptr, info_ptr);

		// render all tiles
		for (int tileIdx = 0; tileIdx < nbTiles; tileIdx++) {
			int y;

			int tx = tileIdx % nbTilesHor;
			int ty = nbTilesVer - (tileIdx / nbTilesHor) - 1;

			printf("Rendering tile %d / %d\n", tileIdx + 1, nbTiles);

			m_ssStartX = (double)tx / nbTilesHor;
			m_ssEndX = (double)(tx+1) / nbTilesHor;

			m_ssStartY = (double)ty / nbTilesVer;
			m_ssEndY = (double)(ty+1) / nbTilesVer;

			// do more stuff...

			drawScene();

			// capture buffer, copy to pixels

			/* set the read buffer */
			GLint BufferName;
			glGetIntegerv(GL_DRAW_BUFFER, &BufferName);
			glReadBuffer((GLenum)BufferName);

			/* grab pixels */
			glReadPixels(0, 0, m_ssViewportWidth, m_ssViewportHeight, GL_RGB, GL_UNSIGNED_BYTE, tmpPixels);
	/*		char tmpFilename[1024];
			sprintf(tmpFilename, "ss_tile_%d_%d.png", tx, ty);
			savePNG(tmpFilename, tmpPixels, m_ssViewportWidth, m_ssViewportHeight);*/
		
			/* copy tile into image */
			for (y = 0; y < m_ssViewportHeight; y++) {
				memcpy(pixels + (y * ssWidth + tx * m_ssViewportWidth) * 3, 
					tmpPixels + (m_ssViewportHeight - y - 1) * m_ssViewportWidth * 3, 
					m_ssViewportWidth * 3);
			}

			// on end of row: write to file
			if (tx == (nbTilesHor-1)) { 
				printf("Writing row %d to png\n", ty);
				for (y = 0; y < m_ssViewportHeight; y++) {
					png_bytep row_pointer = pixels + y * ssWidth * 3;
					png_write_row(png_ptr, row_pointer);
				}
			}
		}

		// close PNG
		png_write_end(png_ptr, info_ptr);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);

		// release pixels...
		free(pixels);
	}


	gui_state->setTextScale(originalTextScale);
	gui_state->m_ssFilename = originalFilename;


	m_screenShotActive = false;

	return 0;
}
