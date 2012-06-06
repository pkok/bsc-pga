/*
Gaigen, Copyright (c) 2001-2002, University of Amsterdam

Copying, use and development for education and research purposes 
permitted as long as this license is not removed from the files.

All rights for commercial use reserved; for more information
contact Daniel Fontijne (fontijne@science.uva.nl)

This software is unsupported.
*/

#ifndef _SOFT_PIC_H_
#define _SOFT_PIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define SP_COLOR 0x01
#define SP_ALPHA  0x02
#define SP_DONT_ALLOC 0x04

#define SP_UNCOMPRESSED 0x00
#define SP_PURE 0x01
#define SP_MIXED_RUN_LENGTH 0x02

#define SP_RED_CHANNEL 0x80
#define SP_GREEN_CHANNEL 0x40
#define SP_BLUE_CHANNEL 0x20
#define SP_ALPHA_CHANNEL 0x10

#define SP_HEADER_LENGTH 104
#define SP_CHANNELPACKET_LENGTH 4

#define SPERR_OK 0
#define SPERR_ANY -1
#define SPERR_FILEOPEN -2
#define SPERR_FILEREAD -3
#define SPERR_FILEFORMAT -4
#define SPERR_MEM -5
#define SPERR_DECODE -6
#define SPERR_FILEWRITE -7

#define SP_MAGIC 0x5380f634

#define SP_MAGIC_OFFSET 0 
#define SP_VERSION_OFFSET 4
#define SP_COMMENT_OFFSET 8
#define SP_ID_OFFSET 88
#define SP_WIDTH_OFFSET 92
#define SP_HEIGHT_OFFSET 94
#define SP_RATIO_OFFSET 96
#define SP_FIELDS_OFFSET 100 
#define SP_PAD_OFFSET 102


typedef struct SoftPICInfo_s {
	char comment[81];
	float version;
	float ratio;
	int fields;
	int channels;
} SoftPICInfo;

/*
Returns 0 on success, negative on failed
*/
int loadSoftPIC(const char *filename, unsigned char **pixels, int *width, int *height, int flags = SP_COLOR, SoftPICInfo *info = NULL);
int loadSoftPICEx(unsigned char *data, int dataLength, unsigned char **pixels, int *width, int *height, int flags /* = SP_COLOR */, SoftPICInfo *info /* = NULL */);


/*
Returns 0 on success, negative on failure
*/
int saveSoftPIC(const char *filename, unsigned char *pixels, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* _SOFT_PIC_H_ */
