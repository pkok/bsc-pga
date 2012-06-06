#ifndef _PNG_H_
#define _PNG_H_

/*
loadPNG():
filename: name of the file where the data should be written to
pixels:	array of pixels (format: RGBRGB etc etc, topdown, left-to-right, width x height)

returns negative on error, 0 on success
*/
int loadPNG(const char *filename, unsigned char **pixels, int *width, int *height);

#endif /* _PNG_H_ */
