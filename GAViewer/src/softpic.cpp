/*
Gaigen, Copyright (c) 2001-2002, University of Amsterdam

Copying, use and development for education and research purposes 
permitted as long as this license is not removed from the files.

All rights for commercial use reserved; for more information
contact Daniel Fontijne (fontijne@science.uva.nl)

This software is unsupported.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "softpic.h"
#include "osdep.h"

#define SP_MAX_CHANNELS 2
#define SP_FILEBLOCK_SIZE 8192

float ucharToFloat(const unsigned char a[4]) {
	int f = (a[0] << 24) | (a[1] << 16) | (a[2] << 8) | (a[3] << 0);
	return *(float*)((int*)&f);
}
int ucharToInt(const unsigned char a[4]) {
	return (a[0] << 24) | (a[1] << 16) | (a[2] << 8) | (a[3] << 0);
}
int ucharToShort(const unsigned char a[2]) {
	return (a[0] << 8) | (a[1] << 0);
}

void intToUchar(int i, unsigned char a[4]) {
	a[0] = (i >> 24) & 0xff;
	a[1] = (i >> 16) & 0xff;
	a[2] = (i >> 8) & 0xff;
	a[3] = (i >> 0) & 0xff;
}

void shortToUchar(short i, unsigned char a[4]) {
	a[0] = (i >> 8) & 0xff;
	a[1] = (i >> 0) & 0xff;
}

void floatToUchar(float f, unsigned char a[4]) {
	int i = *((int*)(&f));
	a[0] = (i >> 24) & 0xff;
	a[1] = (i >> 16) & 0xff;
	a[2] = (i >> 8) & 0xff;
	a[3] = (i >> 0) & 0xff;
}

typedef struct  SoftPICChannel_s {
	int chained;
	int size;
	int type;
	int channel;
	int pixelWidth;
} SoftPICChannel;

static int parseChannelPacket(unsigned char a[4], SoftPICChannel *channel) {
	channel->chained = (int)a[0];
	channel->size = (int)a[1];
	channel->type = (int)a[2];
	channel->channel = (int)a[3];

	if (channel->size != 8) return SPERR_FILEFORMAT;
	if (channel->type != SP_MIXED_RUN_LENGTH) return SPERR_FILEFORMAT;
	if ((channel->channel != SP_ALPHA_CHANNEL) &&
		(channel->channel != (SP_RED_CHANNEL | SP_GREEN_CHANNEL | SP_BLUE_CHANNEL))) return SPERR_FILEFORMAT;
	if (channel->chained > 1)  return SPERR_FILEFORMAT;

	if (channel->channel == SP_ALPHA_CHANNEL) channel->pixelWidth = 1;
	else channel->pixelWidth = 3;

	return SPERR_OK;
}

static int decodeLine(unsigned char *data, int *dataIndex, int maxIndex, unsigned char *line, int linelength, int encoding, int nChannels, int pixelWidth) {
	int lineIndex, runlength;
	int i, j;
	switch (encoding) {
	case SP_UNCOMPRESSED:
		printf("decodeLine(): Warning! untested code!\n");
		/* easy as takin' candy from a baby */
		// ((maxIndex - *dataIndex) < linelength) return SPERR_DECODE;

		for (i = 0; i < linelength / pixelWidth; i ++)
			for (j = 0; j < nChannels; j++)
				line[i * pixelWidth + j] = data[*dataIndex + i * nChannels + j];

		*dataIndex += (linelength / pixelWidth) * nChannels;
		break;
	case SP_PURE:
		printf("decodeLine(): Warning! untested code!\n");
		lineIndex = 0;
		while (lineIndex < linelength) {
			runlength = data[*dataIndex];
			(*dataIndex)++;

			for (i = 0; i < runlength; i++)
				for (j = 0; j < nChannels; j++)
					line[lineIndex + i * pixelWidth + j] = data[(*dataIndex) + j];

			lineIndex += runlength * pixelWidth;
			*dataIndex += nChannels + 1;
		}
		break;
	case SP_MIXED_RUN_LENGTH:
		lineIndex = 0;
		while (lineIndex < linelength) {
			runlength = data[*dataIndex];

			if (runlength >= 128) {	// a simple (long or short) run
				if (runlength == 128) {
					runlength = (data[(*dataIndex) + 1] << 8) | (data[(*dataIndex) + 2] << 0);	// ok?
					*dataIndex = *dataIndex + 3; // ok?
				}
				else {
					runlength -= 127;
					*dataIndex = *dataIndex + 1; // ok?
				}

				for (i = 0; i < runlength; i++)
					for (j = 0; j < nChannels; j++)
						line[lineIndex + i * pixelWidth + j] = data[*dataIndex + j];

				lineIndex += runlength * pixelWidth;
				*dataIndex = *dataIndex + nChannels;
			}
			else {	// raw data
				runlength++;
				(*dataIndex)++;
				for (i = 0; i < runlength; i++)
					for (j = 0; j < nChannels; j++)
						line[lineIndex + i * pixelWidth + j] = data[*dataIndex + i * nChannels + j];

				lineIndex += runlength * pixelWidth;
				*dataIndex = *dataIndex + runlength * nChannels;
			}
		}
		break;
	default:
		return SPERR_DECODE;
	}

	return SPERR_OK;
}

int loadSoftPIC(const char *filename, unsigned char **pixels, int *width, int *height, int flags /* = SP_COLOR */, SoftPICInfo *info /* = NULL */) {
	int l, err;
	FILE *F;
	unsigned char *data;

	/* open file */
	if ( (F = fopen(filename, "rb")) == NULL) {
		return SPERR_FILEOPEN;
	}

	// get file length
	if ( (l = fileLength(F)) < 0) {
		fclose(F);
		return l;
	}
	
	if ( (data = (unsigned char *)calloc(1, l)) == NULL) {
		fclose(F);
		return -1;
	}

	if (fread(data, 1, l, F) != l) {
		fclose(F);
		free(data);
		return -1;
	}

	err = loadSoftPICEx(data, l, pixels, width, height, flags, info);

	fclose(F);
	free(data);
	return err;
}


int loadSoftPICEx(unsigned char *data, int dataLength, unsigned char **pixels, int *width, int *height, int flags /* = SP_COLOR */, SoftPICInfo *info /* = NULL */) {
	unsigned char *header;//[104];
	unsigned char *channelData;
//	FILE *F = NULL;
	int magik;
	char comment[81];
	int i, j, k, errcode;
	float version, ratio;
	int fields, linelength, w, h;
	SoftPICChannel channel[2];
	int nPackets;
	unsigned char *line;
//	unsigned char *data = NULL;
	int maxDataLength = 0;
	int /*dataLength,*/ dataIndex;
	int outputChannels, outputPixelWidth, internalPixelWidth;

	/* load header */
	if (dataLength < SP_HEADER_LENGTH) return SPERR_FILEREAD;
	header = data + 0;
	data += SP_HEADER_LENGTH;
	dataLength -= SP_HEADER_LENGTH;

	/* check/read header */
	if ( (magik = ucharToInt(header + SP_MAGIC_OFFSET)) != SP_MAGIC) {
//		fclose(F);
		return SPERR_FILEFORMAT;
	}
	if (ucharToInt(header + SP_ID_OFFSET) != ucharToInt((unsigned char*)"PICT")) {
//		fclose(F);
		return SPERR_FILEFORMAT;
	}
	memset(comment, 0, 81);
	memcpy(comment, header + SP_COMMENT_OFFSET, 80);
	version = ucharToFloat(header + SP_VERSION_OFFSET);
	w = *width = ucharToShort(header + SP_WIDTH_OFFSET);
	h = *height = ucharToShort(header + SP_HEIGHT_OFFSET);
	ratio = ucharToFloat(header + SP_RATIO_OFFSET);
	fields = ucharToShort(header + SP_FIELDS_OFFSET);
	
	/* copy extra info if user wants it */
	if (info) {
		memcpy(info->comment, comment, 81);
		info->version = version;
		info->ratio = ratio;
		info->fields = fields;
		info->channels = 0;
	}

	/* return here if user doesn't want pixels */
	if (pixels == NULL) {
//		fclose(F);
		return SPERR_OK;
	}

	/* load/parse channels */
	outputChannels = linelength = 0;
	internalPixelWidth = 0;
	nPackets = 0;
	while (nPackets < SP_MAX_CHANNELS) {
		/* read from file */
		/*if (fread(channelData, 1, SP_CHANNELPACKET_LENGTH, F) != SP_CHANNELPACKET_LENGTH) {
			fclose(F);
			return SPERR_FILEREAD;
		}*/
		if (dataLength < SP_CHANNELPACKET_LENGTH) return SPERR_FILEREAD;
		channelData = data;
		data += SP_CHANNELPACKET_LENGTH;
		dataLength -= SP_CHANNELPACKET_LENGTH;

		/* parse */
		if ( (errcode = parseChannelPacket(channelData, channel + nPackets)) != SPERR_OK) {
//			fclose(F);
			return errcode;
		}

		if (channel[nPackets].channel == (SP_RED_CHANNEL | SP_GREEN_CHANNEL | SP_BLUE_CHANNEL)) {
			outputChannels |= (flags & SP_COLOR) ? SP_COLOR : 0;
			linelength += w * 3;
			internalPixelWidth += 3;
		}
		if (channel[nPackets].channel == SP_ALPHA_CHANNEL) {
			outputChannels |= (flags & SP_ALPHA) ? SP_ALPHA : 0;
			linelength += w;
			internalPixelWidth += 1;
		}

		if (!channel[nPackets].chained) break;
		nPackets++;
	}

	/* check number of channels */
	if (nPackets == SP_MAX_CHANNELS) {
//		fclose(F);
		return SPERR_FILEFORMAT;
	}
	nPackets++;

	outputPixelWidth = 0;
	if (outputChannels & SP_COLOR) outputPixelWidth += 3;
	if (outputChannels & SP_ALPHA) outputPixelWidth += 1;

	/* allocate destination if required */
	if (!(flags & SP_DONT_ALLOC))
		*pixels = (unsigned char *)malloc(w * h * outputPixelWidth);

	if (0) {}
	else {

		/* allocate memory to decompress data */
		line = (unsigned char *)malloc(linelength);


		dataIndex = 0;
		for (i = 0; i < h; i++) {
			k = 0;
			for (j = 0; j < nPackets; j++) {
				if ( (errcode = decodeLine(data, &dataIndex, dataLength, line + k, linelength, channel[j].type, channel[j].pixelWidth, internalPixelWidth)) != SPERR_OK) {
					printf("Error decoding line %d\n", i);
					free(line);
//					free(pixels);
					return errcode;
				}
				k += channel[j].pixelWidth;
			}
			if (outputChannels == SP_COLOR) {
				for (j = 0; j < w; j++) {
					(*pixels)[(i * w + j) * outputPixelWidth + 0] = line[j * internalPixelWidth + 0];
					(*pixels)[(i * w + j) * outputPixelWidth + 1] = line[j * internalPixelWidth + 1];
					(*pixels)[(i * w + j) * outputPixelWidth + 2] = line[j * internalPixelWidth + 2];
				}
			}
			else if (outputChannels == SP_ALPHA) {
				for (j = 0; j < w; j++) {
					(*pixels)[(i * w + j) * outputPixelWidth + 0] = line[j * internalPixelWidth + 0];
				}
			}
			else if  (outputChannels == (SP_COLOR | SP_ALPHA)) {
				for (j = 0; j < w; j++) {
					(*pixels)[(i * w + j) * outputPixelWidth + 0] = line[j * internalPixelWidth + 0];
					(*pixels)[(i * w + j) * outputPixelWidth + 1] = line[j * internalPixelWidth + 1];
					(*pixels)[(i * w + j) * outputPixelWidth + 2] = line[j * internalPixelWidth + 2];
					(*pixels)[(i * w + j) * outputPixelWidth + 3] = line[j * internalPixelWidth + 3];
				}
			}
		}
		free(line);
	}
//	free(data);


	return SPERR_OK;
}


inline int getColor(unsigned char *pixel) {
	return (pixel[0] << 16) | (pixel[1] << 8) | (pixel[2] << 0);
}


int saveSoftPIC(const char *filename, unsigned char *pixels, int width, int height) {
	unsigned char header[SP_HEADER_LENGTH], *line;
	unsigned char packet[SP_CHANNELPACKET_LENGTH];
	FILE *F;
	int compressed = 1;
	int i, j, k;
	int prevColor, curColor, rl;
	unsigned char buf[16];

	/* open file */
	if ( (F = fopen(filename, "wb+")) == NULL) {
		return SPERR_FILEOPEN;
	}

	/* init header */
	intToUchar(SP_MAGIC, header + SP_MAGIC_OFFSET);
	floatToUchar(2.62f, header + SP_VERSION_OFFSET);
	memset(header + SP_COMMENT_OFFSET, 0, 80);
	strcpy((char*)header + SP_COMMENT_OFFSET, "saveSoftPic() by Daniel Fontijne");
	strcpy((char*)header + SP_ID_OFFSET, "PICT");
	shortToUchar((short)width, header + SP_WIDTH_OFFSET);
	shortToUchar((short)height, header + SP_HEIGHT_OFFSET);
	floatToUchar(1.0f, header + SP_RATIO_OFFSET);
	shortToUchar((short)0, header + SP_FIELDS_OFFSET);
	shortToUchar((short)0, header + SP_PAD_OFFSET);

	/* write header */
	if (fwrite(header, 1, SP_HEADER_LENGTH, F) != SP_HEADER_LENGTH) {
		fclose(F);
		return SPERR_FILEWRITE;
	}

	/* init packet */
	packet[0] = 1;
	packet[1] = 8;
	packet[2] = (compressed) ? SP_MIXED_RUN_LENGTH : SP_UNCOMPRESSED;
	packet[3] = SP_RED_CHANNEL | SP_GREEN_CHANNEL | SP_BLUE_CHANNEL;

	/* write packets */
	if (fwrite(packet, 1, SP_CHANNELPACKET_LENGTH, F) != SP_CHANNELPACKET_LENGTH) {
		fclose(F);
		return SPERR_FILEWRITE;
	}

	packet[0] = 0;
	packet[1] = 8;
	packet[2] = (compressed) ? SP_MIXED_RUN_LENGTH : SP_UNCOMPRESSED;
	packet[3] = SP_ALPHA_CHANNEL;


	/* write packets */
	if (fwrite(packet, 1, SP_CHANNELPACKET_LENGTH, F) != SP_CHANNELPACKET_LENGTH) {
		fclose(F);
		return SPERR_FILEWRITE;
	}

	/* write image data */
	if (compressed) {
		for (i = 0; i < height; i++) {

			/* write rgb data */
			line = pixels + width * i * 3;
			j = 0;
			while (j < width * 3) {
				k = j;
				if (j == (width-1) * 3) { /* only one pixel left on line */
					buf[0] = 0;	// raw, one byte
					buf[1] = line[j + 0];
					buf[2] = line[j + 1];
					buf[3] = line[j + 2];
					if (fwrite(buf, 4, 1, F) != 1) {
						fclose(F);
						return SPERR_FILEWRITE;
					}
					j += 3;
					continue;
				}

				/* multiple pixels left; determine run or raw*/
				prevColor = getColor(line + j);
				curColor = getColor(line + j + 3);

				if (prevColor == curColor) { /* run */
					j += 6;
					while ((getColor(line + j) == curColor) && (j < width * 3)) j += 3;

					rl = (j - k) / 3;
					if (rl < 128) { /* short run */
						buf[0] = rl + 127;
						buf[1] = line[k + 0];
						buf[2] = line[k + 1];
						buf[3] = line[k + 2];
						rl = 4;
					}
					else { /* long run */
						buf[0] = 128;
						buf[1] = (rl >> 8) & 0xff;
						buf[2] = (rl >> 0) & 0xff;
						buf[3] = line[k + 0];
						buf[4] = line[k + 1];
						buf[5] = line[k + 2];
						rl = 6;
					}

					if (fwrite(buf, rl, 1, F) != 1) {
						fclose(F);
						return SPERR_FILEWRITE;
					}
				}
				else { /* raw */
					j += 6;
					rl = 2;
					while ((curColor != getColor(line + j)) && (j < width * 3) && (rl < 126)) {
						curColor = getColor(line + j);
						j += 3;
						rl++;
					}
					buf[0] = rl-1;
					if (fwrite(buf, 1, 1, F) != 1) {
						fclose(F);
						return SPERR_FILEWRITE;
					}
					if (fwrite(line + k, 3, rl, F) != rl) {
						fclose(F);
						return SPERR_FILEWRITE;
					}
				}
			}

			/* write alpha data */
			rl = width;
			buf[0] = 128;
			buf[1] = (rl >> 8) & 0xff;
			buf[2] = (rl >> 0) & 0xff;
			buf[3] = 255;
			rl = 4;
			if (fwrite(buf, rl, 1, F) != 1) {
				fclose(F);
				return SPERR_FILEWRITE;
			}
		}
	}
	else {
		if (fwrite(pixels, 1, width * height * 3, F) != width * height * 3) {
			fclose(F);
			return SPERR_FILEWRITE;
		}
	}

	fclose(F);

	return SPERR_OK;
}

