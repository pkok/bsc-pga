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
#include <png.h>
#include "pngwrapper.h"

#include "state.h"

void pngConvertFilename(char *filename) {
	char *p = filename - 1;
	while ( (p = strchr(p + 1, '\\')) != NULL)
		p[0] = '/';
}

int pngCheckPow2(int v) {
	while ((v & 1) == 0) v >>= 1;
	return v == 1;
}

int savePNG(const char *filename, const unsigned char *pixels, int width, int height) {
	if (filename == NULL) return -1;
	char *fname = (char*)malloc(strlen(filename) + 1);
	strcpy(fname, filename);
	pngConvertFilename(fname);

	FILE *fp = fopen(filename, "wb+");
	free(fname);
	if (!fp) {
		cprintf("savePNG(): Could not create %s\n", filename);
		return -1;
	}
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		cprintf("savePNG(): Could not create png struct\n");
		fclose(fp);
		return -1;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		cprintf("Could not create png info struct\n");
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		fclose(fp);
		return -1;
	}

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);	

	png_write_info(png_ptr, info_ptr);

	png_byte **row_pointers = (png_byte **)malloc(sizeof(png_byte*) * height);
	for (int i = 0; i < height; i++)
		row_pointers[i] = (unsigned char*)pixels + width * 3 * i;

	png_write_image(png_ptr, row_pointers);

	free(row_pointers);
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	return 0;
}

static int loadPNGSetup(png_structp &png_ptr, png_infop &info_ptr,  png_infop &end_info, const char *callerStr) {
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
		cprintf("%s: Could not create png struct\n", callerStr);
        return -1;
	}

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
		cprintf("%s: Could not create png info struct\n", callerStr);
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        return -1;
    }

    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
		cprintf("%s: Could not create png end info struct\n", callerStr);
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        return -1;
    }
	return 0;
}

static int loadPNGDecode(unsigned char **pixels, int *width, int *height, int flags,
						 png_structp png_ptr, png_infop info_ptr,  png_infop end_info, 
						 const char *callerStr) {
	// get header info
    png_read_info(png_ptr, info_ptr);

    *width = png_get_image_width(png_ptr, info_ptr);
    *height = png_get_image_height(png_ptr, info_ptr);
	int color_type = png_get_color_type(png_ptr, info_ptr);
    int bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    if (color_type == PNG_COLOR_TYPE_PALETTE && bit_depth <= 8) png_set_expand(png_ptr);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) png_set_expand(png_ptr);
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) png_set_expand(png_ptr);
    if (bit_depth == 16) png_set_strip_16(png_ptr);
	if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);

	// decode
	if (pixels) {
		if (!(flags & PNG_NO_ALLOC))
			*pixels = (unsigned char*)malloc(3 * (*width) * (*height) * sizeof(unsigned char));
		unsigned char **row_pointers = (unsigned char **)malloc(2 * (*height) * sizeof(unsigned char*));

		if ((*pixels == NULL) || (row_pointers == NULL)) {
			cprintf("%s: memory allocation error\n", callerStr);
			if ((!(flags & PNG_NO_ALLOC)) && (*pixels)) free(*pixels);
			if (row_pointers) free(row_pointers);
			return -1;
		}

		int i;
		for (i = 0; i < 2 * (*height); i++) {
			row_pointers[i] = *pixels;
		}
		for (i = 0; i < *height; i++) {
			row_pointers[i] = (*pixels) + (i) * (*width) * 3;
		}
		png_read_image(png_ptr, row_pointers);
		free(row_pointers);

		png_read_end(png_ptr, end_info);
	}
	return 0;
}


int loadPNG(const char *filename, unsigned char **pixels, int *width, int *height, int flags) {
	int err;

	// open file
	if (filename == NULL) return -1;
	FILE *fp = fopen(filename, "rb");

	if (!fp) {
		cprintf("loadPNG(): Could not read %s\n", filename);
		return -1;
	}

	// setup initial stuff
	png_structp png_ptr;
    png_infop info_ptr;
    png_infop end_info;
	if ( (err = loadPNGSetup(png_ptr, info_ptr, end_info, "loadPNG()")) != 0)  {
		fclose(fp);
		return err;
	}

	// init IO
    png_init_io(png_ptr, fp);

	// decode
	if ( (err = loadPNGDecode(pixels, width, height, flags,
						 png_ptr, info_ptr, end_info, "loadPNG()")) != 0)  {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		fclose(fp);
		return err;
	}

	// close up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	fclose(fp);

	return 0;
}

typedef struct loadPNGExStruct {
	const unsigned char *buf;
	int bufLength;
	int bufPos;
} loadPNGExData;


void loadPNGEx_user_read_data(png_structp png_ptr,
							  png_bytep data, png_size_t length) {
	loadPNGExData *lPEd = (loadPNGExData *)png_get_io_ptr(png_ptr);

	// check requested length
	if ((int)length > lPEd->bufLength - lPEd->bufPos) {
		cprintf("loadPNGEx_user_read_data(): too much data requested by libpng, padding with 0\n");

		memset(data + lPEd->bufLength - lPEd->bufPos, 0, length - (lPEd->bufLength - lPEd->bufPos));
		length = lPEd->bufLength - lPEd->bufPos;
	}

	// copy data
	memcpy(data, lPEd->buf + lPEd->bufPos, length);

	// update structure
	lPEd->bufPos += (int)length;

	//return length;

	return;
}

int loadPNGEx(const unsigned char *buf, int bufLength, unsigned char **pixels, int *width, int *height, int flags) {
	int err;

	// check buffer
	if ((buf == NULL) || (bufLength <= 0)) return -1;

	// setup initial stuff
	png_structp png_ptr;
    png_infop info_ptr;
    png_infop end_info;
	if ( (err = loadPNGSetup(png_ptr, info_ptr, end_info, "loadPNGEx()")) != 0)  {
		return err;
	}

	// init IO
	loadPNGExData lPEd = {buf, bufLength, 0};
	png_set_read_fn(png_ptr, &lPEd, loadPNGEx_user_read_data);

	// decode
	if ( (err = loadPNGDecode(pixels, width, height, flags,
						 png_ptr, info_ptr, end_info, "loadPNGEx()")) != 0)  {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return err;
	}

	// close up
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);

	return 0;
}
