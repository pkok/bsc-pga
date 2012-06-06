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

#ifndef _PNG_H_
#define _PNG_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
This header provides simple ways to load and save .png files.
*/

/*
Possible flags for loadPNG()
*/
#define PNG_NO_ALLOC 0x01		// don't allocate memory for pixels; application will do that


void pngConvertFilename(char *filename);

/*
savePNG():
filename: name of the file where the data should be written to
pixels:	array of pixels (format: RGBRGB etc etc, topdown, left-to-right, width x height)

returns 0 on success, -1 on failure
*/
int savePNG(const char *filename, const unsigned char *pixels, int width, int height);

/*
loadPNG():
filename: name of the file where the data should be written to
pixels:	array of pixels (format: RGBRGB etc etc, topdown, left-to-right, width x height)
flags: can be 0 or PNG_NO_ALLOC. If 0, the function will allocate memory to store the
pixels in.

returns 0 on success, -1 on failure
*/
int loadPNG(const char *filename, unsigned char **pixels, int *width, int *height, int flags);

// does the same as loadPNG, but reads from memory instead of file
int loadPNGEx(const unsigned char *buf, int bufLength, unsigned char **pixels, int *width, int *height, int flags);

#ifdef __cplusplus
}
#endif

#endif /* _PNG_H_ */
