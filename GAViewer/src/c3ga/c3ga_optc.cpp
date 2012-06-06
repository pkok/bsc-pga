
/*
Gaigen 1.0, Copyright (c) 2001-2010, University of Amsterdam

Copying, use and development for education and research purposes 
permitted as long as this license is not removed from the files.

All rights for commercial use reserved; for more information
contact Daniel Fontijne (fontijne@science.uva.nl)

This software is unsupported.
*/
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void c3gai_null(double *dest, int length) {
	memset(dest, 0, length * sizeof(double));
}

void c3gai_general_gp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
			c[5] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[7] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[10] += - an[3] * bn[1] + an[1] * bn[3] ;
			c[11] += - an[3] * bn[2] + an[2] * bn[3] ;
			c[12] += - an[4] * bn[0] + an[0] * bn[4] ;
			c[13] += - an[4] * bn[1] + an[1] * bn[4] ;
			c[14] += - an[4] * bn[2] + an[2] * bn[4] ;
			c[15] += - an[4] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] + an[4] * bn[3] + an[3] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] + an[4] * bn[4] + an[3] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] + an[4] * bn[5] + an[3] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] - an[4] * bn[9] ;
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[3] * bn[0] - an[1] * bn[3] + an[0] * bn[4] ;
			c[18] += + an[3] * bn[1] - an[2] * bn[3] + an[0] * bn[5] ;
			c[19] += + an[3] * bn[2] - an[2] * bn[4] + an[1] * bn[5] ;
			c[20] += + an[4] * bn[0] - an[1] * bn[6] + an[0] * bn[7] ;
			c[21] += + an[4] * bn[1] - an[2] * bn[6] + an[0] * bn[8] ;
			c[22] += + an[4] * bn[2] - an[2] * bn[7] + an[1] * bn[8] ;
			c[23] += + an[4] * bn[3] - an[3] * bn[6] + an[0] * bn[9] ;
			c[24] += + an[4] * bn[4] - an[3] * bn[7] + an[1] * bn[9] ;
			c[25] += + an[4] * bn[5] - an[3] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] - an[4] * bn[1] - an[3] * bn[4] ;
			c[7] += - an[1] * bn[0] - an[4] * bn[2] - an[3] * bn[5] ;
			c[8] += + an[0] * bn[0] - an[4] * bn[3] - an[3] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] - an[3] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] - an[3] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] + an[4] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] + an[4] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[4] * bn[0] + an[2] * bn[4] - an[1] * bn[5] + an[0] * bn[6] ;
			c[28] += - an[4] * bn[1] + an[3] * bn[4] - an[1] * bn[7] + an[0] * bn[8] ;
			c[29] += - an[4] * bn[2] + an[3] * bn[5] - an[2] * bn[7] + an[0] * bn[9] ;
			c[30] += - an[4] * bn[3] + an[3] * bn[6] - an[2] * bn[8] + an[1] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += + an[4] * bn[0] + an[3] * bn[1] ;
			c[17] += + an[2] * bn[0] + an[3] * bn[2] ;
			c[18] += - an[1] * bn[0] + an[3] * bn[3] ;
			c[19] += + an[0] * bn[0] + an[3] * bn[4] ;
			c[20] += + an[2] * bn[1] - an[4] * bn[2] ;
			c[21] += - an[1] * bn[1] - an[4] * bn[3] ;
			c[22] += + an[0] * bn[1] - an[4] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += - an[3] * bn[0] ;
			c[27] += + an[4] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[1] * bn[0] ;
			c[8] += + an[2] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += + an[4] * bn[0] ;
			c[11] += + an[5] * bn[0] ;
			c[12] += + an[6] * bn[0] ;
			c[13] += + an[7] * bn[0] ;
			c[14] += + an[8] * bn[0] ;
			c[15] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[1] + an[1] * bn[2] - an[6] * bn[3] - an[3] * bn[4] ;
			c[2] += - an[0] * bn[0] + an[2] * bn[2] - an[7] * bn[3] - an[4] * bn[4] ;
			c[3] += - an[1] * bn[0] - an[2] * bn[1] - an[8] * bn[3] - an[5] * bn[4] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[9] * bn[3] ;
			c[5] += - an[6] * bn[0] - an[7] * bn[1] - an[8] * bn[2] + an[9] * bn[4] ;
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[4] * bn[0] - an[3] * bn[1] + an[0] * bn[3] ;
			c[18] += + an[5] * bn[0] - an[3] * bn[2] + an[1] * bn[3] ;
			c[19] += + an[5] * bn[1] - an[4] * bn[2] + an[2] * bn[3] ;
			c[20] += + an[7] * bn[0] - an[6] * bn[1] + an[0] * bn[4] ;
			c[21] += + an[8] * bn[0] - an[6] * bn[2] + an[1] * bn[4] ;
			c[22] += + an[8] * bn[1] - an[7] * bn[2] + an[2] * bn[4] ;
			c[23] += + an[9] * bn[0] - an[6] * bn[3] + an[3] * bn[4] ;
			c[24] += + an[9] * bn[1] - an[7] * bn[3] + an[4] * bn[4] ;
			c[25] += + an[9] * bn[2] - an[8] * bn[3] + an[5] * bn[4] ;
		}
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
			c[6] += + an[2] * bn[1] - an[1] * bn[2] - an[7] * bn[3] + an[6] * bn[4] - an[4] * bn[6] + an[3] * bn[7] ;
			c[7] += - an[2] * bn[0] + an[0] * bn[2] - an[8] * bn[3] + an[6] * bn[5] - an[5] * bn[6] + an[3] * bn[8] ;
			c[8] += + an[1] * bn[0] - an[0] * bn[1] - an[8] * bn[4] + an[7] * bn[5] - an[5] * bn[7] + an[4] * bn[8] ;
			c[9] += - an[4] * bn[0] - an[5] * bn[1] - an[9] * bn[3] + an[0] * bn[4] + an[1] * bn[5] + an[3] * bn[9] ;
			c[10] += + an[3] * bn[0] - an[5] * bn[2] - an[0] * bn[3] - an[9] * bn[4] + an[2] * bn[5] + an[4] * bn[9] ;
			c[11] += + an[3] * bn[1] + an[4] * bn[2] - an[1] * bn[3] - an[2] * bn[4] - an[9] * bn[5] + an[5] * bn[9] ;
			c[12] += - an[7] * bn[0] - an[8] * bn[1] + an[9] * bn[6] + an[0] * bn[7] + an[1] * bn[8] - an[6] * bn[9] ;
			c[13] += + an[6] * bn[0] - an[8] * bn[2] - an[0] * bn[6] + an[9] * bn[7] + an[2] * bn[8] - an[7] * bn[9] ;
			c[14] += + an[6] * bn[1] + an[7] * bn[2] - an[1] * bn[6] - an[2] * bn[7] + an[9] * bn[8] - an[8] * bn[9] ;
			c[15] += + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] - an[3] * bn[6] - an[4] * bn[7] - an[5] * bn[8] ;
			c[26] += + an[5] * bn[0] - an[4] * bn[1] + an[3] * bn[2] + an[2] * bn[3] - an[1] * bn[4] + an[0] * bn[5] ;
			c[27] += + an[8] * bn[0] - an[7] * bn[1] + an[6] * bn[2] + an[2] * bn[6] - an[1] * bn[7] + an[0] * bn[8] ;
			c[28] += + an[9] * bn[0] - an[7] * bn[3] + an[6] * bn[4] + an[4] * bn[6] - an[3] * bn[7] + an[0] * bn[9] ;
			c[29] += + an[9] * bn[1] - an[8] * bn[3] + an[6] * bn[5] + an[5] * bn[6] - an[3] * bn[8] + an[1] * bn[9] ;
			c[30] += + an[9] * bn[2] - an[8] * bn[4] + an[7] * bn[5] + an[5] * bn[7] - an[4] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] + an[7] * bn[1] + an[8] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] - an[6] * bn[1] + an[8] * bn[3] - an[3] * bn[4] + an[5] * bn[6] + an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] - an[6] * bn[2] - an[7] * bn[3] - an[3] * bn[5] - an[4] * bn[6] + an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
			c[16] += - an[8] * bn[1] + an[7] * bn[2] - an[6] * bn[3] - an[5] * bn[4] + an[4] * bn[5] - an[3] * bn[6] ;
			c[17] += - an[5] * bn[0] - an[9] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[4] * bn[7] - an[3] * bn[8] ;
			c[18] += + an[4] * bn[0] - an[2] * bn[1] - an[9] * bn[2] + an[0] * bn[3] + an[5] * bn[7] - an[3] * bn[9] ;
			c[19] += - an[3] * bn[0] + an[1] * bn[1] - an[0] * bn[2] - an[9] * bn[3] + an[5] * bn[8] - an[4] * bn[9] ;
			c[20] += - an[8] * bn[0] + an[9] * bn[4] + an[2] * bn[5] - an[1] * bn[6] - an[7] * bn[7] + an[6] * bn[8] ;
			c[21] += + an[7] * bn[0] - an[2] * bn[4] + an[9] * bn[5] + an[0] * bn[6] - an[8] * bn[7] + an[6] * bn[9] ;
			c[22] += - an[6] * bn[0] + an[1] * bn[4] - an[0] * bn[5] + an[9] * bn[6] - an[8] * bn[8] + an[7] * bn[9] ;
			c[23] += + an[7] * bn[1] + an[8] * bn[2] - an[4] * bn[4] - an[5] * bn[5] + an[0] * bn[8] + an[1] * bn[9] ;
			c[24] += - an[6] * bn[1] + an[8] * bn[3] + an[3] * bn[4] - an[5] * bn[6] - an[0] * bn[7] + an[2] * bn[9] ;
			c[25] += - an[6] * bn[2] - an[7] * bn[3] + an[3] * bn[5] + an[4] * bn[6] - an[1] * bn[7] - an[2] * bn[8] ;
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] - an[6] * bn[3] + an[5] * bn[4] - an[4] * bn[5] + an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += + an[8] * bn[0] + an[5] * bn[1] + an[9] * bn[2] ;
			c[7] += - an[7] * bn[0] - an[4] * bn[1] + an[9] * bn[3] ;
			c[8] += + an[6] * bn[0] + an[3] * bn[1] + an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] - an[4] * bn[2] - an[5] * bn[3] ;
			c[10] += + an[1] * bn[0] + an[3] * bn[2] - an[5] * bn[4] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[2] * bn[1] + an[7] * bn[2] + an[8] * bn[3] ;
			c[13] += + an[1] * bn[1] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += - an[0] * bn[1] - an[6] * bn[3] - an[7] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
			c[26] += - an[9] * bn[0] + an[5] * bn[2] - an[4] * bn[3] + an[3] * bn[4] ;
			c[27] += + an[9] * bn[1] - an[8] * bn[2] + an[7] * bn[3] - an[6] * bn[4] ;
			c[28] += + an[8] * bn[0] - an[5] * bn[1] + an[2] * bn[3] - an[1] * bn[4] ;
			c[29] += - an[7] * bn[0] + an[4] * bn[1] - an[2] * bn[2] + an[0] * bn[4] ;
			c[30] += + an[6] * bn[0] - an[3] * bn[1] + an[1] * bn[2] - an[0] * bn[3] ;
		}
		if (bn = b[5]) {
			c[16] += + an[9] * bn[0] ;
			c[17] += - an[5] * bn[0] ;
			c[18] += + an[4] * bn[0] ;
			c[19] += - an[3] * bn[0] ;
			c[20] += + an[8] * bn[0] ;
			c[21] += - an[7] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[1] * bn[0] ;
			c[18] += + an[2] * bn[0] ;
			c[19] += + an[3] * bn[0] ;
			c[20] += + an[4] * bn[0] ;
			c[21] += + an[5] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += + an[7] * bn[0] ;
			c[24] += + an[8] * bn[0] ;
			c[25] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[6] += + an[0] * bn[2] - an[4] * bn[3] - an[1] * bn[4] ;
			c[7] += - an[0] * bn[1] - an[5] * bn[3] - an[2] * bn[4] ;
			c[8] += + an[0] * bn[0] - an[6] * bn[3] - an[3] * bn[4] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[7] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[3] * bn[2] - an[8] * bn[3] ;
			c[11] += + an[2] * bn[0] + an[3] * bn[1] - an[9] * bn[3] ;
			c[12] += - an[4] * bn[1] - an[5] * bn[2] + an[7] * bn[4] ;
			c[13] += + an[4] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += + an[5] * bn[0] + an[6] * bn[1] + an[9] * bn[4] ;
			c[15] += + an[7] * bn[0] + an[8] * bn[1] + an[9] * bn[2] ;
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[6] * bn[0] + an[5] * bn[1] - an[4] * bn[2] + an[0] * bn[4] ;
			c[28] += - an[8] * bn[0] + an[7] * bn[1] - an[4] * bn[3] + an[1] * bn[4] ;
			c[29] += - an[9] * bn[0] + an[7] * bn[2] - an[5] * bn[3] + an[2] * bn[4] ;
			c[30] += - an[9] * bn[1] + an[8] * bn[2] - an[6] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[1] * bn[7] + an[2] * bn[8] + an[7] * bn[9] ;
			c[2] += + an[0] * bn[1] - an[4] * bn[3] + an[6] * bn[5] - an[1] * bn[6] + an[3] * bn[8] + an[8] * bn[9] ;
			c[3] += - an[0] * bn[0] - an[5] * bn[3] - an[6] * bn[4] - an[2] * bn[6] - an[3] * bn[7] + an[9] * bn[9] ;
			c[4] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[2] - an[7] * bn[3] - an[8] * bn[4] - an[9] * bn[5] ;
			c[5] += - an[4] * bn[0] - an[5] * bn[1] - an[6] * bn[2] + an[7] * bn[6] + an[8] * bn[7] + an[9] * bn[8] ;
			c[16] += + an[6] * bn[3] - an[5] * bn[4] + an[4] * bn[5] + an[3] * bn[6] - an[2] * bn[7] + an[1] * bn[8] ;
			c[17] += + an[3] * bn[1] - an[2] * bn[2] + an[8] * bn[3] - an[7] * bn[4] + an[0] * bn[5] + an[1] * bn[9] ;
			c[18] += - an[3] * bn[0] + an[1] * bn[2] + an[9] * bn[3] - an[0] * bn[4] - an[7] * bn[5] + an[2] * bn[9] ;
			c[19] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[3] + an[9] * bn[4] - an[8] * bn[5] + an[3] * bn[9] ;
			c[20] += + an[6] * bn[1] - an[5] * bn[2] - an[8] * bn[6] + an[7] * bn[7] + an[0] * bn[8] - an[4] * bn[9] ;
			c[21] += - an[6] * bn[0] + an[4] * bn[2] - an[9] * bn[6] - an[0] * bn[7] + an[7] * bn[8] - an[5] * bn[9] ;
			c[22] += + an[5] * bn[0] - an[4] * bn[1] + an[0] * bn[6] - an[9] * bn[7] + an[8] * bn[8] - an[6] * bn[9] ;
			c[23] += - an[8] * bn[0] - an[9] * bn[1] + an[4] * bn[4] + an[5] * bn[5] - an[1] * bn[7] - an[2] * bn[8] ;
			c[24] += + an[7] * bn[0] - an[9] * bn[2] - an[4] * bn[3] + an[6] * bn[5] + an[1] * bn[6] - an[3] * bn[8] ;
			c[25] += + an[7] * bn[1] + an[8] * bn[2] - an[5] * bn[3] - an[6] * bn[4] + an[2] * bn[6] + an[3] * bn[7] ;
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] + an[6] * bn[3] - an[5] * bn[4] + an[4] * bn[5] - an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
			c[6] += - an[6] * bn[2] + an[5] * bn[3] - an[3] * bn[5] + an[2] * bn[6] - an[8] * bn[7] + an[7] * bn[8] ;
			c[7] += + an[6] * bn[1] - an[4] * bn[3] + an[3] * bn[4] - an[1] * bn[6] - an[9] * bn[7] + an[7] * bn[9] ;
			c[8] += - an[5] * bn[1] + an[4] * bn[2] - an[2] * bn[4] + an[1] * bn[5] - an[9] * bn[8] + an[8] * bn[9] ;
			c[9] += + an[3] * bn[0] + an[8] * bn[1] + an[9] * bn[2] - an[0] * bn[3] - an[1] * bn[8] - an[2] * bn[9] ;
			c[10] += - an[2] * bn[0] - an[7] * bn[1] + an[0] * bn[2] + an[9] * bn[3] + an[1] * bn[7] - an[3] * bn[9] ;
			c[11] += + an[1] * bn[0] - an[0] * bn[1] - an[7] * bn[2] - an[8] * bn[3] + an[2] * bn[7] + an[3] * bn[8] ;
			c[12] += + an[6] * bn[0] - an[8] * bn[4] - an[9] * bn[5] - an[0] * bn[6] + an[4] * bn[8] + an[5] * bn[9] ;
			c[13] += - an[5] * bn[0] + an[7] * bn[4] + an[0] * bn[5] - an[9] * bn[6] - an[4] * bn[7] + an[6] * bn[9] ;
			c[14] += + an[4] * bn[0] - an[0] * bn[4] + an[7] * bn[5] + an[8] * bn[6] - an[5] * bn[7] - an[6] * bn[8] ;
			c[15] += + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] - an[1] * bn[4] - an[2] * bn[5] - an[3] * bn[6] ;
			c[26] += - an[9] * bn[1] + an[8] * bn[2] - an[7] * bn[3] - an[3] * bn[7] + an[2] * bn[8] - an[1] * bn[9] ;
			c[27] += + an[9] * bn[4] - an[8] * bn[5] + an[7] * bn[6] + an[6] * bn[7] - an[5] * bn[8] + an[4] * bn[9] ;
			c[28] += + an[9] * bn[0] - an[6] * bn[2] + an[5] * bn[3] + an[3] * bn[5] - an[2] * bn[6] + an[0] * bn[9] ;
			c[29] += - an[8] * bn[0] + an[6] * bn[1] - an[4] * bn[3] - an[3] * bn[4] + an[1] * bn[6] - an[0] * bn[8] ;
			c[30] += + an[7] * bn[0] - an[5] * bn[1] + an[4] * bn[2] + an[2] * bn[4] - an[1] * bn[5] + an[0] * bn[7] ;
		}
		if (bn = b[4]) {
			c[1] += - an[6] * bn[0] - an[3] * bn[1] - an[8] * bn[2] - an[9] * bn[3] ;
			c[2] += + an[5] * bn[0] + an[2] * bn[1] + an[7] * bn[2] - an[9] * bn[4] ;
			c[3] += - an[4] * bn[0] - an[1] * bn[1] + an[7] * bn[3] + an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
			c[5] += - an[0] * bn[1] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
			c[16] += + an[9] * bn[2] - an[8] * bn[3] + an[7] * bn[4] ;
			c[17] += - an[9] * bn[0] + an[3] * bn[3] - an[2] * bn[4] ;
			c[18] += + an[8] * bn[0] - an[3] * bn[2] + an[1] * bn[4] ;
			c[19] += - an[7] * bn[0] + an[2] * bn[2] - an[1] * bn[3] ;
			c[20] += + an[9] * bn[1] - an[6] * bn[3] + an[5] * bn[4] ;
			c[21] += - an[8] * bn[1] + an[6] * bn[2] - an[4] * bn[4] ;
			c[22] += + an[7] * bn[1] - an[5] * bn[2] + an[4] * bn[3] ;
			c[23] += - an[6] * bn[0] + an[3] * bn[1] - an[0] * bn[4] ;
			c[24] += + an[5] * bn[0] - an[2] * bn[1] + an[0] * bn[3] ;
			c[25] += - an[4] * bn[0] + an[1] * bn[1] - an[0] * bn[2] ;
		}
		if (bn = b[5]) {
			c[6] += + an[9] * bn[0] ;
			c[7] += - an[8] * bn[0] ;
			c[8] += + an[7] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
			c[11] += + an[1] * bn[0] ;
			c[12] += - an[6] * bn[0] ;
			c[13] += + an[5] * bn[0] ;
			c[14] += - an[4] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[1] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += + an[3] * bn[0] ;
			c[30] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[16] += - an[1] * bn[3] - an[0] * bn[4] ;
			c[17] += - an[0] * bn[2] - an[2] * bn[3] ;
			c[18] += + an[0] * bn[1] - an[3] * bn[3] ;
			c[19] += - an[0] * bn[0] - an[4] * bn[3] ;
			c[20] += - an[1] * bn[2] + an[2] * bn[4] ;
			c[21] += + an[1] * bn[1] + an[3] * bn[4] ;
			c[22] += - an[1] * bn[0] + an[4] * bn[4] ;
			c[23] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[24] += - an[2] * bn[0] + an[4] * bn[2] ;
			c[25] += - an[3] * bn[0] - an[4] * bn[1] ;
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[1] * bn[5] + an[0] * bn[8] + an[2] * bn[9] ;
			c[7] += - an[1] * bn[4] - an[0] * bn[7] + an[3] * bn[9] ;
			c[8] += + an[1] * bn[3] + an[0] * bn[6] + an[4] * bn[9] ;
			c[9] += - an[0] * bn[2] - an[2] * bn[4] - an[3] * bn[5] ;
			c[10] += + an[0] * bn[1] + an[2] * bn[3] - an[4] * bn[5] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[1] * bn[2] + an[2] * bn[7] + an[3] * bn[8] ;
			c[13] += + an[1] * bn[1] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += - an[1] * bn[0] - an[3] * bn[6] - an[4] * bn[7] ;
			c[15] += - an[2] * bn[0] - an[3] * bn[1] - an[4] * bn[2] ;
			c[26] += - an[4] * bn[3] + an[3] * bn[4] - an[2] * bn[5] + an[0] * bn[9] ;
			c[27] += + an[4] * bn[6] - an[3] * bn[7] + an[2] * bn[8] - an[1] * bn[9] ;
			c[28] += + an[4] * bn[1] - an[3] * bn[2] + an[1] * bn[5] - an[0] * bn[8] ;
			c[29] += - an[4] * bn[0] + an[2] * bn[2] - an[1] * bn[4] + an[0] * bn[7] ;
			c[30] += + an[3] * bn[0] - an[2] * bn[1] + an[1] * bn[3] - an[0] * bn[6] ;
		}
		if (bn = b[3]) {
			c[1] += + an[1] * bn[3] + an[0] * bn[6] + an[2] * bn[8] + an[3] * bn[9] ;
			c[2] += - an[1] * bn[2] - an[0] * bn[5] - an[2] * bn[7] + an[4] * bn[9] ;
			c[3] += + an[1] * bn[1] + an[0] * bn[4] - an[3] * bn[7] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[0] + an[2] * bn[1] + an[3] * bn[2] + an[4] * bn[3] ;
			c[5] += + an[1] * bn[0] - an[2] * bn[4] - an[3] * bn[5] - an[4] * bn[6] ;
			c[16] += + an[4] * bn[7] - an[3] * bn[8] + an[2] * bn[9] ;
			c[17] += - an[4] * bn[2] + an[3] * bn[3] - an[0] * bn[9] ;
			c[18] += + an[4] * bn[1] - an[2] * bn[3] + an[0] * bn[8] ;
			c[19] += - an[3] * bn[1] + an[2] * bn[2] - an[0] * bn[7] ;
			c[20] += + an[4] * bn[5] - an[3] * bn[6] + an[1] * bn[9] ;
			c[21] += - an[4] * bn[4] + an[2] * bn[6] - an[1] * bn[8] ;
			c[22] += + an[3] * bn[4] - an[2] * bn[5] + an[1] * bn[7] ;
			c[23] += - an[4] * bn[0] + an[1] * bn[3] - an[0] * bn[6] ;
			c[24] += + an[3] * bn[0] - an[1] * bn[2] + an[0] * bn[5] ;
			c[25] += - an[2] * bn[0] + an[1] * bn[1] - an[0] * bn[4] ;
		}
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
			c[6] += + an[4] * bn[3] - an[3] * bn[4] ;
			c[7] += - an[4] * bn[2] + an[2] * bn[4] ;
			c[8] += + an[3] * bn[2] - an[2] * bn[3] ;
			c[9] += + an[4] * bn[0] - an[0] * bn[4] ;
			c[10] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[11] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[12] += - an[4] * bn[1] + an[1] * bn[4] ;
			c[13] += + an[3] * bn[1] - an[1] * bn[3] ;
			c[14] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[15] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[1] += - an[4] * bn[0] ;
			c[2] += + an[3] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[1] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[0]) {
			c[31] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[26] += - an[0] * bn[3] ;
			c[27] += + an[0] * bn[4] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += - an[0] * bn[1] ;
			c[30] += + an[0] * bn[0] ;
		}
		if (bn = b[2]) {
			c[16] += + an[0] * bn[9] ;
			c[17] += - an[0] * bn[5] ;
			c[18] += + an[0] * bn[4] ;
			c[19] += - an[0] * bn[3] ;
			c[20] += + an[0] * bn[8] ;
			c[21] += - an[0] * bn[7] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += - an[0] * bn[2] ;
			c[24] += + an[0] * bn[1] ;
			c[25] += - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[6] += + an[0] * bn[9] ;
			c[7] += - an[0] * bn[8] ;
			c[8] += + an[0] * bn[7] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += - an[0] * bn[2] ;
			c[11] += + an[0] * bn[1] ;
			c[12] += - an[0] * bn[6] ;
			c[13] += + an[0] * bn[5] ;
			c[14] += - an[0] * bn[4] ;
			c[15] += - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += - an[0] * bn[4] ;
			c[2] += + an[0] * bn[3] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_scp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_op(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
			c[5] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[7] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[10] += - an[3] * bn[1] + an[1] * bn[3] ;
			c[11] += - an[3] * bn[2] + an[2] * bn[3] ;
			c[12] += - an[4] * bn[0] + an[0] * bn[4] ;
			c[13] += - an[4] * bn[1] + an[1] * bn[4] ;
			c[14] += - an[4] * bn[2] + an[2] * bn[4] ;
			c[15] += - an[4] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[3] * bn[0] - an[1] * bn[3] + an[0] * bn[4] ;
			c[18] += + an[3] * bn[1] - an[2] * bn[3] + an[0] * bn[5] ;
			c[19] += + an[3] * bn[2] - an[2] * bn[4] + an[1] * bn[5] ;
			c[20] += + an[4] * bn[0] - an[1] * bn[6] + an[0] * bn[7] ;
			c[21] += + an[4] * bn[1] - an[2] * bn[6] + an[0] * bn[8] ;
			c[22] += + an[4] * bn[2] - an[2] * bn[7] + an[1] * bn[8] ;
			c[23] += + an[4] * bn[3] - an[3] * bn[6] + an[0] * bn[9] ;
			c[24] += + an[4] * bn[4] - an[3] * bn[7] + an[1] * bn[9] ;
			c[25] += + an[4] * bn[5] - an[3] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[4] * bn[0] + an[2] * bn[4] - an[1] * bn[5] + an[0] * bn[6] ;
			c[28] += - an[4] * bn[1] + an[3] * bn[4] - an[1] * bn[7] + an[0] * bn[8] ;
			c[29] += - an[4] * bn[2] + an[3] * bn[5] - an[2] * bn[7] + an[0] * bn[9] ;
			c[30] += - an[4] * bn[3] + an[3] * bn[6] - an[2] * bn[8] + an[1] * bn[9] ;
		}
		if (bn = b[4]) {
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[1] * bn[0] ;
			c[8] += + an[2] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += + an[4] * bn[0] ;
			c[11] += + an[5] * bn[0] ;
			c[12] += + an[6] * bn[0] ;
			c[13] += + an[7] * bn[0] ;
			c[14] += + an[8] * bn[0] ;
			c[15] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[4] * bn[0] - an[3] * bn[1] + an[0] * bn[3] ;
			c[18] += + an[5] * bn[0] - an[3] * bn[2] + an[1] * bn[3] ;
			c[19] += + an[5] * bn[1] - an[4] * bn[2] + an[2] * bn[3] ;
			c[20] += + an[7] * bn[0] - an[6] * bn[1] + an[0] * bn[4] ;
			c[21] += + an[8] * bn[0] - an[6] * bn[2] + an[1] * bn[4] ;
			c[22] += + an[8] * bn[1] - an[7] * bn[2] + an[2] * bn[4] ;
			c[23] += + an[9] * bn[0] - an[6] * bn[3] + an[3] * bn[4] ;
			c[24] += + an[9] * bn[1] - an[7] * bn[3] + an[4] * bn[4] ;
			c[25] += + an[9] * bn[2] - an[8] * bn[3] + an[5] * bn[4] ;
		}
		if (bn = b[2]) {
			c[26] += + an[5] * bn[0] - an[4] * bn[1] + an[3] * bn[2] + an[2] * bn[3] - an[1] * bn[4] + an[0] * bn[5] ;
			c[27] += + an[8] * bn[0] - an[7] * bn[1] + an[6] * bn[2] + an[2] * bn[6] - an[1] * bn[7] + an[0] * bn[8] ;
			c[28] += + an[9] * bn[0] - an[7] * bn[3] + an[6] * bn[4] + an[4] * bn[6] - an[3] * bn[7] + an[0] * bn[9] ;
			c[29] += + an[9] * bn[1] - an[8] * bn[3] + an[6] * bn[5] + an[5] * bn[6] - an[3] * bn[8] + an[1] * bn[9] ;
			c[30] += + an[9] * bn[2] - an[8] * bn[4] + an[7] * bn[5] + an[5] * bn[7] - an[4] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] - an[6] * bn[3] + an[5] * bn[4] - an[4] * bn[5] + an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[1] * bn[0] ;
			c[18] += + an[2] * bn[0] ;
			c[19] += + an[3] * bn[0] ;
			c[20] += + an[4] * bn[0] ;
			c[21] += + an[5] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += + an[7] * bn[0] ;
			c[24] += + an[8] * bn[0] ;
			c[25] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[6] * bn[0] + an[5] * bn[1] - an[4] * bn[2] + an[0] * bn[4] ;
			c[28] += - an[8] * bn[0] + an[7] * bn[1] - an[4] * bn[3] + an[1] * bn[4] ;
			c[29] += - an[9] * bn[0] + an[7] * bn[2] - an[5] * bn[3] + an[2] * bn[4] ;
			c[30] += - an[9] * bn[1] + an[8] * bn[2] - an[6] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] + an[6] * bn[3] - an[5] * bn[4] + an[4] * bn[5] - an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[1] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += + an[3] * bn[0] ;
			c[30] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[0]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
}

void c3gai_general_lcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] + an[4] * bn[3] + an[3] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] + an[4] * bn[4] + an[3] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] + an[4] * bn[5] + an[3] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] - an[4] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] - an[4] * bn[1] - an[3] * bn[4] ;
			c[7] += - an[1] * bn[0] - an[4] * bn[2] - an[3] * bn[5] ;
			c[8] += + an[0] * bn[0] - an[4] * bn[3] - an[3] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] - an[3] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] - an[3] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] + an[4] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] + an[4] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += + an[4] * bn[0] + an[3] * bn[1] ;
			c[17] += + an[2] * bn[0] + an[3] * bn[2] ;
			c[18] += - an[1] * bn[0] + an[3] * bn[3] ;
			c[19] += + an[0] * bn[0] + an[3] * bn[4] ;
			c[20] += + an[2] * bn[1] - an[4] * bn[2] ;
			c[21] += - an[1] * bn[1] - an[4] * bn[3] ;
			c[22] += + an[0] * bn[1] - an[4] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += - an[3] * bn[0] ;
			c[27] += + an[4] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] + an[7] * bn[1] + an[8] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] - an[6] * bn[1] + an[8] * bn[3] - an[3] * bn[4] + an[5] * bn[6] + an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] - an[6] * bn[2] - an[7] * bn[3] - an[3] * bn[5] - an[4] * bn[6] + an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += + an[8] * bn[0] + an[5] * bn[1] + an[9] * bn[2] ;
			c[7] += - an[7] * bn[0] - an[4] * bn[1] + an[9] * bn[3] ;
			c[8] += + an[6] * bn[0] + an[3] * bn[1] + an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] - an[4] * bn[2] - an[5] * bn[3] ;
			c[10] += + an[1] * bn[0] + an[3] * bn[2] - an[5] * bn[4] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[2] * bn[1] + an[7] * bn[2] + an[8] * bn[3] ;
			c[13] += + an[1] * bn[1] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += - an[0] * bn[1] - an[6] * bn[3] - an[7] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
		}
		if (bn = b[5]) {
			c[16] += + an[9] * bn[0] ;
			c[17] += - an[5] * bn[0] ;
			c[18] += + an[4] * bn[0] ;
			c[19] += - an[3] * bn[0] ;
			c[20] += + an[8] * bn[0] ;
			c[21] += - an[7] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[4]) {
			c[1] += - an[6] * bn[0] - an[3] * bn[1] - an[8] * bn[2] - an[9] * bn[3] ;
			c[2] += + an[5] * bn[0] + an[2] * bn[1] + an[7] * bn[2] - an[9] * bn[4] ;
			c[3] += - an[4] * bn[0] - an[1] * bn[1] + an[7] * bn[3] + an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
			c[5] += - an[0] * bn[1] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
		}
		if (bn = b[5]) {
			c[6] += + an[9] * bn[0] ;
			c[7] += - an[8] * bn[0] ;
			c[8] += + an[7] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
			c[11] += + an[1] * bn[0] ;
			c[12] += - an[6] * bn[0] ;
			c[13] += + an[5] * bn[0] ;
			c[14] += - an[4] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
		}
		if (bn = b[5]) {
			c[1] += - an[4] * bn[0] ;
			c[2] += + an[3] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[1] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_rcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
			c[5] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[1] * bn[0] ;
			c[8] += + an[2] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += + an[4] * bn[0] ;
			c[11] += + an[5] * bn[0] ;
			c[12] += + an[6] * bn[0] ;
			c[13] += + an[7] * bn[0] ;
			c[14] += + an[8] * bn[0] ;
			c[15] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[1] + an[1] * bn[2] - an[6] * bn[3] - an[3] * bn[4] ;
			c[2] += - an[0] * bn[0] + an[2] * bn[2] - an[7] * bn[3] - an[4] * bn[4] ;
			c[3] += - an[1] * bn[0] - an[2] * bn[1] - an[8] * bn[3] - an[5] * bn[4] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[9] * bn[3] ;
			c[5] += - an[6] * bn[0] - an[7] * bn[1] - an[8] * bn[2] + an[9] * bn[4] ;
		}
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[1] * bn[0] ;
			c[18] += + an[2] * bn[0] ;
			c[19] += + an[3] * bn[0] ;
			c[20] += + an[4] * bn[0] ;
			c[21] += + an[5] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += + an[7] * bn[0] ;
			c[24] += + an[8] * bn[0] ;
			c[25] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[6] += + an[0] * bn[2] - an[4] * bn[3] - an[1] * bn[4] ;
			c[7] += - an[0] * bn[1] - an[5] * bn[3] - an[2] * bn[4] ;
			c[8] += + an[0] * bn[0] - an[6] * bn[3] - an[3] * bn[4] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[7] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[3] * bn[2] - an[8] * bn[3] ;
			c[11] += + an[2] * bn[0] + an[3] * bn[1] - an[9] * bn[3] ;
			c[12] += - an[4] * bn[1] - an[5] * bn[2] + an[7] * bn[4] ;
			c[13] += + an[4] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += + an[5] * bn[0] + an[6] * bn[1] + an[9] * bn[4] ;
			c[15] += + an[7] * bn[0] + an[8] * bn[1] + an[9] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[1] * bn[7] + an[2] * bn[8] + an[7] * bn[9] ;
			c[2] += + an[0] * bn[1] - an[4] * bn[3] + an[6] * bn[5] - an[1] * bn[6] + an[3] * bn[8] + an[8] * bn[9] ;
			c[3] += - an[0] * bn[0] - an[5] * bn[3] - an[6] * bn[4] - an[2] * bn[6] - an[3] * bn[7] + an[9] * bn[9] ;
			c[4] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[2] - an[7] * bn[3] - an[8] * bn[4] - an[9] * bn[5] ;
			c[5] += - an[4] * bn[0] - an[5] * bn[1] - an[6] * bn[2] + an[7] * bn[6] + an[8] * bn[7] + an[9] * bn[8] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[1] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += + an[3] * bn[0] ;
			c[30] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[16] += - an[1] * bn[3] - an[0] * bn[4] ;
			c[17] += - an[0] * bn[2] - an[2] * bn[3] ;
			c[18] += + an[0] * bn[1] - an[3] * bn[3] ;
			c[19] += - an[0] * bn[0] - an[4] * bn[3] ;
			c[20] += - an[1] * bn[2] + an[2] * bn[4] ;
			c[21] += + an[1] * bn[1] + an[3] * bn[4] ;
			c[22] += - an[1] * bn[0] + an[4] * bn[4] ;
			c[23] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[24] += - an[2] * bn[0] + an[4] * bn[2] ;
			c[25] += - an[3] * bn[0] - an[4] * bn[1] ;
		}
		if (bn = b[2]) {
			c[6] += + an[1] * bn[5] + an[0] * bn[8] + an[2] * bn[9] ;
			c[7] += - an[1] * bn[4] - an[0] * bn[7] + an[3] * bn[9] ;
			c[8] += + an[1] * bn[3] + an[0] * bn[6] + an[4] * bn[9] ;
			c[9] += - an[0] * bn[2] - an[2] * bn[4] - an[3] * bn[5] ;
			c[10] += + an[0] * bn[1] + an[2] * bn[3] - an[4] * bn[5] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[1] * bn[2] + an[2] * bn[7] + an[3] * bn[8] ;
			c[13] += + an[1] * bn[1] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += - an[1] * bn[0] - an[3] * bn[6] - an[4] * bn[7] ;
			c[15] += - an[2] * bn[0] - an[3] * bn[1] - an[4] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += + an[1] * bn[3] + an[0] * bn[6] + an[2] * bn[8] + an[3] * bn[9] ;
			c[2] += - an[1] * bn[2] - an[0] * bn[5] - an[2] * bn[7] + an[4] * bn[9] ;
			c[3] += + an[1] * bn[1] + an[0] * bn[4] - an[3] * bn[7] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[0] + an[2] * bn[1] + an[3] * bn[2] + an[4] * bn[3] ;
			c[5] += + an[1] * bn[0] - an[2] * bn[4] - an[3] * bn[5] - an[4] * bn[6] ;
		}
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[0]) {
			c[31] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[26] += - an[0] * bn[3] ;
			c[27] += + an[0] * bn[4] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += - an[0] * bn[1] ;
			c[30] += + an[0] * bn[0] ;
		}
		if (bn = b[2]) {
			c[16] += + an[0] * bn[9] ;
			c[17] += - an[0] * bn[5] ;
			c[18] += + an[0] * bn[4] ;
			c[19] += - an[0] * bn[3] ;
			c[20] += + an[0] * bn[8] ;
			c[21] += - an[0] * bn[7] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += - an[0] * bn[2] ;
			c[24] += + an[0] * bn[1] ;
			c[25] += - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[6] += + an[0] * bn[9] ;
			c[7] += - an[0] * bn[8] ;
			c[8] += + an[0] * bn[7] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += - an[0] * bn[2] ;
			c[11] += + an[0] * bn[1] ;
			c[12] += - an[0] * bn[6] ;
			c[13] += + an[0] * bn[5] ;
			c[14] += - an[0] * bn[4] ;
			c[15] += - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += - an[0] * bn[4] ;
			c[2] += + an[0] * bn[3] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_hip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] + an[4] * bn[3] + an[3] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] + an[4] * bn[4] + an[3] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] + an[4] * bn[5] + an[3] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] - an[4] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] - an[4] * bn[1] - an[3] * bn[4] ;
			c[7] += - an[1] * bn[0] - an[4] * bn[2] - an[3] * bn[5] ;
			c[8] += + an[0] * bn[0] - an[4] * bn[3] - an[3] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] - an[3] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] - an[3] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] + an[4] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] + an[4] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += + an[4] * bn[0] + an[3] * bn[1] ;
			c[17] += + an[2] * bn[0] + an[3] * bn[2] ;
			c[18] += - an[1] * bn[0] + an[3] * bn[3] ;
			c[19] += + an[0] * bn[0] + an[3] * bn[4] ;
			c[20] += + an[2] * bn[1] - an[4] * bn[2] ;
			c[21] += - an[1] * bn[1] - an[4] * bn[3] ;
			c[22] += + an[0] * bn[1] - an[4] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += - an[3] * bn[0] ;
			c[27] += + an[4] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[1]) {
			c[1] += + an[0] * bn[1] + an[1] * bn[2] - an[6] * bn[3] - an[3] * bn[4] ;
			c[2] += - an[0] * bn[0] + an[2] * bn[2] - an[7] * bn[3] - an[4] * bn[4] ;
			c[3] += - an[1] * bn[0] - an[2] * bn[1] - an[8] * bn[3] - an[5] * bn[4] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[9] * bn[3] ;
			c[5] += - an[6] * bn[0] - an[7] * bn[1] - an[8] * bn[2] + an[9] * bn[4] ;
		}
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] + an[7] * bn[1] + an[8] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] - an[6] * bn[1] + an[8] * bn[3] - an[3] * bn[4] + an[5] * bn[6] + an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] - an[6] * bn[2] - an[7] * bn[3] - an[3] * bn[5] - an[4] * bn[6] + an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += + an[8] * bn[0] + an[5] * bn[1] + an[9] * bn[2] ;
			c[7] += - an[7] * bn[0] - an[4] * bn[1] + an[9] * bn[3] ;
			c[8] += + an[6] * bn[0] + an[3] * bn[1] + an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] - an[4] * bn[2] - an[5] * bn[3] ;
			c[10] += + an[1] * bn[0] + an[3] * bn[2] - an[5] * bn[4] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[2] * bn[1] + an[7] * bn[2] + an[8] * bn[3] ;
			c[13] += + an[1] * bn[1] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += - an[0] * bn[1] - an[6] * bn[3] - an[7] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
		}
		if (bn = b[5]) {
			c[16] += + an[9] * bn[0] ;
			c[17] += - an[5] * bn[0] ;
			c[18] += + an[4] * bn[0] ;
			c[19] += - an[3] * bn[0] ;
			c[20] += + an[8] * bn[0] ;
			c[21] += - an[7] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[1]) {
			c[6] += + an[0] * bn[2] - an[4] * bn[3] - an[1] * bn[4] ;
			c[7] += - an[0] * bn[1] - an[5] * bn[3] - an[2] * bn[4] ;
			c[8] += + an[0] * bn[0] - an[6] * bn[3] - an[3] * bn[4] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[7] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[3] * bn[2] - an[8] * bn[3] ;
			c[11] += + an[2] * bn[0] + an[3] * bn[1] - an[9] * bn[3] ;
			c[12] += - an[4] * bn[1] - an[5] * bn[2] + an[7] * bn[4] ;
			c[13] += + an[4] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += + an[5] * bn[0] + an[6] * bn[1] + an[9] * bn[4] ;
			c[15] += + an[7] * bn[0] + an[8] * bn[1] + an[9] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[1] * bn[7] + an[2] * bn[8] + an[7] * bn[9] ;
			c[2] += + an[0] * bn[1] - an[4] * bn[3] + an[6] * bn[5] - an[1] * bn[6] + an[3] * bn[8] + an[8] * bn[9] ;
			c[3] += - an[0] * bn[0] - an[5] * bn[3] - an[6] * bn[4] - an[2] * bn[6] - an[3] * bn[7] + an[9] * bn[9] ;
			c[4] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[2] - an[7] * bn[3] - an[8] * bn[4] - an[9] * bn[5] ;
			c[5] += - an[4] * bn[0] - an[5] * bn[1] - an[6] * bn[2] + an[7] * bn[6] + an[8] * bn[7] + an[9] * bn[8] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[4]) {
			c[1] += - an[6] * bn[0] - an[3] * bn[1] - an[8] * bn[2] - an[9] * bn[3] ;
			c[2] += + an[5] * bn[0] + an[2] * bn[1] + an[7] * bn[2] - an[9] * bn[4] ;
			c[3] += - an[4] * bn[0] - an[1] * bn[1] + an[7] * bn[3] + an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
			c[5] += - an[0] * bn[1] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
		}
		if (bn = b[5]) {
			c[6] += + an[9] * bn[0] ;
			c[7] += - an[8] * bn[0] ;
			c[8] += + an[7] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
			c[11] += + an[1] * bn[0] ;
			c[12] += - an[6] * bn[0] ;
			c[13] += + an[5] * bn[0] ;
			c[14] += - an[4] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[1]) {
			c[16] += - an[1] * bn[3] - an[0] * bn[4] ;
			c[17] += - an[0] * bn[2] - an[2] * bn[3] ;
			c[18] += + an[0] * bn[1] - an[3] * bn[3] ;
			c[19] += - an[0] * bn[0] - an[4] * bn[3] ;
			c[20] += - an[1] * bn[2] + an[2] * bn[4] ;
			c[21] += + an[1] * bn[1] + an[3] * bn[4] ;
			c[22] += - an[1] * bn[0] + an[4] * bn[4] ;
			c[23] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[24] += - an[2] * bn[0] + an[4] * bn[2] ;
			c[25] += - an[3] * bn[0] - an[4] * bn[1] ;
		}
		if (bn = b[2]) {
			c[6] += + an[1] * bn[5] + an[0] * bn[8] + an[2] * bn[9] ;
			c[7] += - an[1] * bn[4] - an[0] * bn[7] + an[3] * bn[9] ;
			c[8] += + an[1] * bn[3] + an[0] * bn[6] + an[4] * bn[9] ;
			c[9] += - an[0] * bn[2] - an[2] * bn[4] - an[3] * bn[5] ;
			c[10] += + an[0] * bn[1] + an[2] * bn[3] - an[4] * bn[5] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[1] * bn[2] + an[2] * bn[7] + an[3] * bn[8] ;
			c[13] += + an[1] * bn[1] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += - an[1] * bn[0] - an[3] * bn[6] - an[4] * bn[7] ;
			c[15] += - an[2] * bn[0] - an[3] * bn[1] - an[4] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += + an[1] * bn[3] + an[0] * bn[6] + an[2] * bn[8] + an[3] * bn[9] ;
			c[2] += - an[1] * bn[2] - an[0] * bn[5] - an[2] * bn[7] + an[4] * bn[9] ;
			c[3] += + an[1] * bn[1] + an[0] * bn[4] - an[3] * bn[7] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[0] + an[2] * bn[1] + an[3] * bn[2] + an[4] * bn[3] ;
			c[5] += + an[1] * bn[0] - an[2] * bn[4] - an[3] * bn[5] - an[4] * bn[6] ;
		}
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
		}
		if (bn = b[5]) {
			c[1] += - an[4] * bn[0] ;
			c[2] += + an[3] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[1] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[1]) {
			c[26] += - an[0] * bn[3] ;
			c[27] += + an[0] * bn[4] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += - an[0] * bn[1] ;
			c[30] += + an[0] * bn[0] ;
		}
		if (bn = b[2]) {
			c[16] += + an[0] * bn[9] ;
			c[17] += - an[0] * bn[5] ;
			c[18] += + an[0] * bn[4] ;
			c[19] += - an[0] * bn[3] ;
			c[20] += + an[0] * bn[8] ;
			c[21] += - an[0] * bn[7] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += - an[0] * bn[2] ;
			c[24] += + an[0] * bn[1] ;
			c[25] += - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[6] += + an[0] * bn[9] ;
			c[7] += - an[0] * bn[8] ;
			c[8] += + an[0] * bn[7] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += - an[0] * bn[2] ;
			c[11] += + an[0] * bn[1] ;
			c[12] += - an[0] * bn[6] ;
			c[13] += + an[0] * bn[5] ;
			c[14] += - an[0] * bn[4] ;
			c[15] += - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += - an[0] * bn[4] ;
			c[2] += + an[0] * bn[3] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_mhip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
			c[5] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] - an[4] * bn[3] - an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] + an[4] * bn[3] + an[3] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] + an[4] * bn[4] + an[3] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] + an[4] * bn[5] + an[3] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] - an[4] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] - an[4] * bn[1] - an[3] * bn[4] ;
			c[7] += - an[1] * bn[0] - an[4] * bn[2] - an[3] * bn[5] ;
			c[8] += + an[0] * bn[0] - an[4] * bn[3] - an[3] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] - an[3] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] - an[3] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] + an[4] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] + an[4] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += + an[4] * bn[0] + an[3] * bn[1] ;
			c[17] += + an[2] * bn[0] + an[3] * bn[2] ;
			c[18] += - an[1] * bn[0] + an[3] * bn[3] ;
			c[19] += + an[0] * bn[0] + an[3] * bn[4] ;
			c[20] += + an[2] * bn[1] - an[4] * bn[2] ;
			c[21] += - an[1] * bn[1] - an[4] * bn[3] ;
			c[22] += + an[0] * bn[1] - an[4] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += - an[3] * bn[0] ;
			c[27] += + an[4] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[1] * bn[0] ;
			c[8] += + an[2] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += + an[4] * bn[0] ;
			c[11] += + an[5] * bn[0] ;
			c[12] += + an[6] * bn[0] ;
			c[13] += + an[7] * bn[0] ;
			c[14] += + an[8] * bn[0] ;
			c[15] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[1] + an[1] * bn[2] - an[6] * bn[3] - an[3] * bn[4] ;
			c[2] += - an[0] * bn[0] + an[2] * bn[2] - an[7] * bn[3] - an[4] * bn[4] ;
			c[3] += - an[1] * bn[0] - an[2] * bn[1] - an[8] * bn[3] - an[5] * bn[4] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[9] * bn[3] ;
			c[5] += - an[6] * bn[0] - an[7] * bn[1] - an[8] * bn[2] + an[9] * bn[4] ;
		}
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] + an[3] * bn[6] + an[4] * bn[7] + an[5] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] + an[7] * bn[1] + an[8] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] - an[6] * bn[1] + an[8] * bn[3] - an[3] * bn[4] + an[5] * bn[6] + an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] - an[6] * bn[2] - an[7] * bn[3] - an[3] * bn[5] - an[4] * bn[6] + an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += + an[8] * bn[0] + an[5] * bn[1] + an[9] * bn[2] ;
			c[7] += - an[7] * bn[0] - an[4] * bn[1] + an[9] * bn[3] ;
			c[8] += + an[6] * bn[0] + an[3] * bn[1] + an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] - an[4] * bn[2] - an[5] * bn[3] ;
			c[10] += + an[1] * bn[0] + an[3] * bn[2] - an[5] * bn[4] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[2] * bn[1] + an[7] * bn[2] + an[8] * bn[3] ;
			c[13] += + an[1] * bn[1] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += - an[0] * bn[1] - an[6] * bn[3] - an[7] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
		}
		if (bn = b[5]) {
			c[16] += + an[9] * bn[0] ;
			c[17] += - an[5] * bn[0] ;
			c[18] += + an[4] * bn[0] ;
			c[19] += - an[3] * bn[0] ;
			c[20] += + an[8] * bn[0] ;
			c[21] += - an[7] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[1] * bn[0] ;
			c[18] += + an[2] * bn[0] ;
			c[19] += + an[3] * bn[0] ;
			c[20] += + an[4] * bn[0] ;
			c[21] += + an[5] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += + an[7] * bn[0] ;
			c[24] += + an[8] * bn[0] ;
			c[25] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[6] += + an[0] * bn[2] - an[4] * bn[3] - an[1] * bn[4] ;
			c[7] += - an[0] * bn[1] - an[5] * bn[3] - an[2] * bn[4] ;
			c[8] += + an[0] * bn[0] - an[6] * bn[3] - an[3] * bn[4] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] - an[7] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[3] * bn[2] - an[8] * bn[3] ;
			c[11] += + an[2] * bn[0] + an[3] * bn[1] - an[9] * bn[3] ;
			c[12] += - an[4] * bn[1] - an[5] * bn[2] + an[7] * bn[4] ;
			c[13] += + an[4] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[14] += + an[5] * bn[0] + an[6] * bn[1] + an[9] * bn[4] ;
			c[15] += + an[7] * bn[0] + an[8] * bn[1] + an[9] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[2] + an[4] * bn[4] + an[5] * bn[5] + an[1] * bn[7] + an[2] * bn[8] + an[7] * bn[9] ;
			c[2] += + an[0] * bn[1] - an[4] * bn[3] + an[6] * bn[5] - an[1] * bn[6] + an[3] * bn[8] + an[8] * bn[9] ;
			c[3] += - an[0] * bn[0] - an[5] * bn[3] - an[6] * bn[4] - an[2] * bn[6] - an[3] * bn[7] + an[9] * bn[9] ;
			c[4] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[2] - an[7] * bn[3] - an[8] * bn[4] - an[9] * bn[5] ;
			c[5] += - an[4] * bn[0] - an[5] * bn[1] - an[6] * bn[2] + an[7] * bn[6] + an[8] * bn[7] + an[9] * bn[8] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] + an[1] * bn[4] + an[2] * bn[5] + an[3] * bn[6] + an[7] * bn[7] + an[8] * bn[8] + an[9] * bn[9] ;
		}
		if (bn = b[4]) {
			c[1] += - an[6] * bn[0] - an[3] * bn[1] - an[8] * bn[2] - an[9] * bn[3] ;
			c[2] += + an[5] * bn[0] + an[2] * bn[1] + an[7] * bn[2] - an[9] * bn[4] ;
			c[3] += - an[4] * bn[0] - an[1] * bn[1] + an[7] * bn[3] + an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
			c[5] += - an[0] * bn[1] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
		}
		if (bn = b[5]) {
			c[6] += + an[9] * bn[0] ;
			c[7] += - an[8] * bn[0] ;
			c[8] += + an[7] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
			c[11] += + an[1] * bn[0] ;
			c[12] += - an[6] * bn[0] ;
			c[13] += + an[5] * bn[0] ;
			c[14] += - an[4] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[1] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += + an[3] * bn[0] ;
			c[30] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[16] += - an[1] * bn[3] - an[0] * bn[4] ;
			c[17] += - an[0] * bn[2] - an[2] * bn[3] ;
			c[18] += + an[0] * bn[1] - an[3] * bn[3] ;
			c[19] += - an[0] * bn[0] - an[4] * bn[3] ;
			c[20] += - an[1] * bn[2] + an[2] * bn[4] ;
			c[21] += + an[1] * bn[1] + an[3] * bn[4] ;
			c[22] += - an[1] * bn[0] + an[4] * bn[4] ;
			c[23] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[24] += - an[2] * bn[0] + an[4] * bn[2] ;
			c[25] += - an[3] * bn[0] - an[4] * bn[1] ;
		}
		if (bn = b[2]) {
			c[6] += + an[1] * bn[5] + an[0] * bn[8] + an[2] * bn[9] ;
			c[7] += - an[1] * bn[4] - an[0] * bn[7] + an[3] * bn[9] ;
			c[8] += + an[1] * bn[3] + an[0] * bn[6] + an[4] * bn[9] ;
			c[9] += - an[0] * bn[2] - an[2] * bn[4] - an[3] * bn[5] ;
			c[10] += + an[0] * bn[1] + an[2] * bn[3] - an[4] * bn[5] ;
			c[11] += - an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[12] += - an[1] * bn[2] + an[2] * bn[7] + an[3] * bn[8] ;
			c[13] += + an[1] * bn[1] - an[2] * bn[6] + an[4] * bn[8] ;
			c[14] += - an[1] * bn[0] - an[3] * bn[6] - an[4] * bn[7] ;
			c[15] += - an[2] * bn[0] - an[3] * bn[1] - an[4] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += + an[1] * bn[3] + an[0] * bn[6] + an[2] * bn[8] + an[3] * bn[9] ;
			c[2] += - an[1] * bn[2] - an[0] * bn[5] - an[2] * bn[7] + an[4] * bn[9] ;
			c[3] += + an[1] * bn[1] + an[0] * bn[4] - an[3] * bn[7] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[0] + an[2] * bn[1] + an[3] * bn[2] + an[4] * bn[3] ;
			c[5] += + an[1] * bn[0] - an[2] * bn[4] - an[3] * bn[5] - an[4] * bn[6] ;
		}
		if (bn = b[4]) {
			c[0] += - an[1] * bn[0] - an[0] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] ;
		}
		if (bn = b[5]) {
			c[1] += - an[4] * bn[0] ;
			c[2] += + an[3] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[1] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[0]) {
			c[31] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[26] += - an[0] * bn[3] ;
			c[27] += + an[0] * bn[4] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += - an[0] * bn[1] ;
			c[30] += + an[0] * bn[0] ;
		}
		if (bn = b[2]) {
			c[16] += + an[0] * bn[9] ;
			c[17] += - an[0] * bn[5] ;
			c[18] += + an[0] * bn[4] ;
			c[19] += - an[0] * bn[3] ;
			c[20] += + an[0] * bn[8] ;
			c[21] += - an[0] * bn[7] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += - an[0] * bn[2] ;
			c[24] += + an[0] * bn[1] ;
			c[25] += - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[6] += + an[0] * bn[9] ;
			c[7] += - an[0] * bn[8] ;
			c[8] += + an[0] * bn[7] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += - an[0] * bn[2] ;
			c[11] += + an[0] * bn[1] ;
			c[12] += - an[0] * bn[6] ;
			c[13] += + an[0] * bn[5] ;
			c[14] += - an[0] * bn[4] ;
			c[15] += - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += - an[0] * bn[4] ;
			c[2] += + an[0] * bn[3] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[0] ;
			c[5] += - an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void c3gai_general_gpem(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
			c[5] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[7] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[10] += - an[3] * bn[1] + an[1] * bn[3] ;
			c[11] += - an[3] * bn[2] + an[2] * bn[3] ;
			c[12] += - an[4] * bn[0] + an[0] * bn[4] ;
			c[13] += - an[4] * bn[1] + an[1] * bn[4] ;
			c[14] += - an[4] * bn[2] + an[2] * bn[4] ;
			c[15] += - an[4] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[3] - an[4] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] - an[3] * bn[4] - an[4] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] - an[3] * bn[5] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] - an[4] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] + an[3] * bn[9] ;
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[3] * bn[0] - an[1] * bn[3] + an[0] * bn[4] ;
			c[18] += + an[3] * bn[1] - an[2] * bn[3] + an[0] * bn[5] ;
			c[19] += + an[3] * bn[2] - an[2] * bn[4] + an[1] * bn[5] ;
			c[20] += + an[4] * bn[0] - an[1] * bn[6] + an[0] * bn[7] ;
			c[21] += + an[4] * bn[1] - an[2] * bn[6] + an[0] * bn[8] ;
			c[22] += + an[4] * bn[2] - an[2] * bn[7] + an[1] * bn[8] ;
			c[23] += + an[4] * bn[3] - an[3] * bn[6] + an[0] * bn[9] ;
			c[24] += + an[4] * bn[4] - an[3] * bn[7] + an[1] * bn[9] ;
			c[25] += + an[4] * bn[5] - an[3] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] + an[3] * bn[1] + an[4] * bn[4] ;
			c[7] += - an[1] * bn[0] + an[3] * bn[2] + an[4] * bn[5] ;
			c[8] += + an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] + an[4] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] + an[4] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] + an[4] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] - an[3] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] - an[3] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] - an[3] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[4] * bn[0] + an[2] * bn[4] - an[1] * bn[5] + an[0] * bn[6] ;
			c[28] += - an[4] * bn[1] + an[3] * bn[4] - an[1] * bn[7] + an[0] * bn[8] ;
			c[29] += - an[4] * bn[2] + an[3] * bn[5] - an[2] * bn[7] + an[0] * bn[9] ;
			c[30] += - an[4] * bn[3] + an[3] * bn[6] - an[2] * bn[8] + an[1] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += - an[3] * bn[0] - an[4] * bn[1] ;
			c[17] += + an[2] * bn[0] - an[4] * bn[2] ;
			c[18] += - an[1] * bn[0] - an[4] * bn[3] ;
			c[19] += + an[0] * bn[0] - an[4] * bn[4] ;
			c[20] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[21] += - an[1] * bn[1] + an[3] * bn[3] ;
			c[22] += + an[0] * bn[1] + an[3] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += + an[4] * bn[0] ;
			c[27] += - an[3] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[1] * bn[0] ;
			c[8] += + an[2] * bn[0] ;
			c[9] += + an[3] * bn[0] ;
			c[10] += + an[4] * bn[0] ;
			c[11] += + an[5] * bn[0] ;
			c[12] += + an[6] * bn[0] ;
			c[13] += + an[7] * bn[0] ;
			c[14] += + an[8] * bn[0] ;
			c[15] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[1] + an[1] * bn[2] + an[3] * bn[3] + an[6] * bn[4] ;
			c[2] += - an[0] * bn[0] + an[2] * bn[2] + an[4] * bn[3] + an[7] * bn[4] ;
			c[3] += - an[1] * bn[0] - an[2] * bn[1] + an[5] * bn[3] + an[8] * bn[4] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] + an[9] * bn[4] ;
			c[5] += - an[6] * bn[0] - an[7] * bn[1] - an[8] * bn[2] - an[9] * bn[3] ;
			c[16] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[2] ;
			c[17] += + an[4] * bn[0] - an[3] * bn[1] + an[0] * bn[3] ;
			c[18] += + an[5] * bn[0] - an[3] * bn[2] + an[1] * bn[3] ;
			c[19] += + an[5] * bn[1] - an[4] * bn[2] + an[2] * bn[3] ;
			c[20] += + an[7] * bn[0] - an[6] * bn[1] + an[0] * bn[4] ;
			c[21] += + an[8] * bn[0] - an[6] * bn[2] + an[1] * bn[4] ;
			c[22] += + an[8] * bn[1] - an[7] * bn[2] + an[2] * bn[4] ;
			c[23] += + an[9] * bn[0] - an[6] * bn[3] + an[3] * bn[4] ;
			c[24] += + an[9] * bn[1] - an[7] * bn[3] + an[4] * bn[4] ;
			c[25] += + an[9] * bn[2] - an[8] * bn[3] + an[5] * bn[4] ;
		}
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
			c[6] += + an[2] * bn[1] - an[1] * bn[2] + an[4] * bn[3] - an[3] * bn[4] + an[7] * bn[6] - an[6] * bn[7] ;
			c[7] += - an[2] * bn[0] + an[0] * bn[2] + an[5] * bn[3] - an[3] * bn[5] + an[8] * bn[6] - an[6] * bn[8] ;
			c[8] += + an[1] * bn[0] - an[0] * bn[1] + an[5] * bn[4] - an[4] * bn[5] + an[8] * bn[7] - an[7] * bn[8] ;
			c[9] += - an[4] * bn[0] - an[5] * bn[1] + an[0] * bn[4] + an[1] * bn[5] + an[9] * bn[6] - an[6] * bn[9] ;
			c[10] += + an[3] * bn[0] - an[5] * bn[2] - an[0] * bn[3] + an[2] * bn[5] + an[9] * bn[7] - an[7] * bn[9] ;
			c[11] += + an[3] * bn[1] + an[4] * bn[2] - an[1] * bn[3] - an[2] * bn[4] + an[9] * bn[8] - an[8] * bn[9] ;
			c[12] += - an[7] * bn[0] - an[8] * bn[1] - an[9] * bn[3] + an[0] * bn[7] + an[1] * bn[8] + an[3] * bn[9] ;
			c[13] += + an[6] * bn[0] - an[8] * bn[2] - an[9] * bn[4] - an[0] * bn[6] + an[2] * bn[8] + an[4] * bn[9] ;
			c[14] += + an[6] * bn[1] + an[7] * bn[2] - an[9] * bn[5] - an[1] * bn[6] - an[2] * bn[7] + an[5] * bn[9] ;
			c[15] += + an[6] * bn[3] + an[7] * bn[4] + an[8] * bn[5] - an[3] * bn[6] - an[4] * bn[7] - an[5] * bn[8] ;
			c[26] += + an[5] * bn[0] - an[4] * bn[1] + an[3] * bn[2] + an[2] * bn[3] - an[1] * bn[4] + an[0] * bn[5] ;
			c[27] += + an[8] * bn[0] - an[7] * bn[1] + an[6] * bn[2] + an[2] * bn[6] - an[1] * bn[7] + an[0] * bn[8] ;
			c[28] += + an[9] * bn[0] - an[7] * bn[3] + an[6] * bn[4] + an[4] * bn[6] - an[3] * bn[7] + an[0] * bn[9] ;
			c[29] += + an[9] * bn[1] - an[8] * bn[3] + an[6] * bn[5] + an[5] * bn[6] - an[3] * bn[8] + an[1] * bn[9] ;
			c[30] += + an[9] * bn[2] - an[8] * bn[4] + an[7] * bn[5] + an[5] * bn[7] - an[4] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[7] * bn[4] - an[8] * bn[5] - an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] + an[3] * bn[1] - an[5] * bn[3] + an[6] * bn[4] - an[8] * bn[6] - an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] + an[3] * bn[2] + an[4] * bn[3] + an[6] * bn[5] + an[7] * bn[6] - an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
			c[16] += + an[5] * bn[1] - an[4] * bn[2] + an[3] * bn[3] + an[8] * bn[4] - an[7] * bn[5] + an[6] * bn[6] ;
			c[17] += - an[5] * bn[0] + an[2] * bn[2] - an[1] * bn[3] + an[9] * bn[4] - an[7] * bn[7] + an[6] * bn[8] ;
			c[18] += + an[4] * bn[0] - an[2] * bn[1] + an[0] * bn[3] + an[9] * bn[5] - an[8] * bn[7] + an[6] * bn[9] ;
			c[19] += - an[3] * bn[0] + an[1] * bn[1] - an[0] * bn[2] + an[9] * bn[6] - an[8] * bn[8] + an[7] * bn[9] ;
			c[20] += - an[8] * bn[0] - an[9] * bn[1] + an[2] * bn[5] - an[1] * bn[6] + an[4] * bn[7] - an[3] * bn[8] ;
			c[21] += + an[7] * bn[0] - an[9] * bn[2] - an[2] * bn[4] + an[0] * bn[6] + an[5] * bn[7] - an[3] * bn[9] ;
			c[22] += - an[6] * bn[0] - an[9] * bn[3] + an[1] * bn[4] - an[0] * bn[5] + an[5] * bn[8] - an[4] * bn[9] ;
			c[23] += + an[7] * bn[1] + an[8] * bn[2] - an[4] * bn[4] - an[5] * bn[5] + an[0] * bn[8] + an[1] * bn[9] ;
			c[24] += - an[6] * bn[1] + an[8] * bn[3] + an[3] * bn[4] - an[5] * bn[6] - an[0] * bn[7] + an[2] * bn[9] ;
			c[25] += - an[6] * bn[2] - an[7] * bn[3] + an[3] * bn[5] + an[4] * bn[6] - an[1] * bn[7] - an[2] * bn[8] ;
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] - an[6] * bn[3] + an[5] * bn[4] - an[4] * bn[5] + an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += - an[5] * bn[0] - an[8] * bn[1] - an[9] * bn[2] ;
			c[7] += + an[4] * bn[0] + an[7] * bn[1] - an[9] * bn[3] ;
			c[8] += - an[3] * bn[0] - an[6] * bn[1] - an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] + an[7] * bn[2] + an[8] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[11] += - an[0] * bn[0] - an[6] * bn[3] - an[7] * bn[4] ;
			c[12] += - an[2] * bn[1] - an[4] * bn[2] - an[5] * bn[3] ;
			c[13] += + an[1] * bn[1] + an[3] * bn[2] - an[5] * bn[4] ;
			c[14] += - an[0] * bn[1] + an[3] * bn[3] + an[4] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
			c[26] += + an[9] * bn[1] - an[8] * bn[2] + an[7] * bn[3] - an[6] * bn[4] ;
			c[27] += - an[9] * bn[0] + an[5] * bn[2] - an[4] * bn[3] + an[3] * bn[4] ;
			c[28] += + an[8] * bn[0] - an[5] * bn[1] + an[2] * bn[3] - an[1] * bn[4] ;
			c[29] += - an[7] * bn[0] + an[4] * bn[1] - an[2] * bn[2] + an[0] * bn[4] ;
			c[30] += + an[6] * bn[0] - an[3] * bn[1] + an[1] * bn[2] - an[0] * bn[3] ;
		}
		if (bn = b[5]) {
			c[16] += - an[9] * bn[0] ;
			c[17] += + an[8] * bn[0] ;
			c[18] += - an[7] * bn[0] ;
			c[19] += + an[6] * bn[0] ;
			c[20] += - an[5] * bn[0] ;
			c[21] += + an[4] * bn[0] ;
			c[22] += - an[3] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[1] * bn[0] ;
			c[18] += + an[2] * bn[0] ;
			c[19] += + an[3] * bn[0] ;
			c[20] += + an[4] * bn[0] ;
			c[21] += + an[5] * bn[0] ;
			c[22] += + an[6] * bn[0] ;
			c[23] += + an[7] * bn[0] ;
			c[24] += + an[8] * bn[0] ;
			c[25] += + an[9] * bn[0] ;
		}
		if (bn = b[1]) {
			c[6] += + an[0] * bn[2] + an[1] * bn[3] + an[4] * bn[4] ;
			c[7] += - an[0] * bn[1] + an[2] * bn[3] + an[5] * bn[4] ;
			c[8] += + an[0] * bn[0] + an[3] * bn[3] + an[6] * bn[4] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] + an[7] * bn[4] ;
			c[10] += + an[1] * bn[0] - an[3] * bn[2] + an[8] * bn[4] ;
			c[11] += + an[2] * bn[0] + an[3] * bn[1] + an[9] * bn[4] ;
			c[12] += - an[4] * bn[1] - an[5] * bn[2] - an[7] * bn[3] ;
			c[13] += + an[4] * bn[0] - an[6] * bn[2] - an[8] * bn[3] ;
			c[14] += + an[5] * bn[0] + an[6] * bn[1] - an[9] * bn[3] ;
			c[15] += + an[7] * bn[0] + an[8] * bn[1] + an[9] * bn[2] ;
			c[26] += - an[3] * bn[0] + an[2] * bn[1] - an[1] * bn[2] + an[0] * bn[3] ;
			c[27] += - an[6] * bn[0] + an[5] * bn[1] - an[4] * bn[2] + an[0] * bn[4] ;
			c[28] += - an[8] * bn[0] + an[7] * bn[1] - an[4] * bn[3] + an[1] * bn[4] ;
			c[29] += - an[9] * bn[0] + an[7] * bn[2] - an[5] * bn[3] + an[2] * bn[4] ;
			c[30] += - an[9] * bn[1] + an[8] * bn[2] - an[6] * bn[3] + an[3] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[2] - an[1] * bn[4] - an[2] * bn[5] - an[4] * bn[7] - an[5] * bn[8] - an[7] * bn[9] ;
			c[2] += + an[0] * bn[1] + an[1] * bn[3] - an[3] * bn[5] + an[4] * bn[6] - an[6] * bn[8] - an[8] * bn[9] ;
			c[3] += - an[0] * bn[0] + an[2] * bn[3] + an[3] * bn[4] + an[5] * bn[6] + an[6] * bn[7] - an[9] * bn[9] ;
			c[4] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[2] + an[7] * bn[6] + an[8] * bn[7] + an[9] * bn[8] ;
			c[5] += - an[4] * bn[0] - an[5] * bn[1] - an[6] * bn[2] - an[7] * bn[3] - an[8] * bn[4] - an[9] * bn[5] ;
			c[16] += - an[3] * bn[3] + an[2] * bn[4] - an[1] * bn[5] - an[6] * bn[6] + an[5] * bn[7] - an[4] * bn[8] ;
			c[17] += + an[3] * bn[1] - an[2] * bn[2] + an[0] * bn[5] - an[8] * bn[6] + an[7] * bn[7] - an[4] * bn[9] ;
			c[18] += - an[3] * bn[0] + an[1] * bn[2] - an[0] * bn[4] - an[9] * bn[6] + an[7] * bn[8] - an[5] * bn[9] ;
			c[19] += + an[2] * bn[0] - an[1] * bn[1] + an[0] * bn[3] - an[9] * bn[7] + an[8] * bn[8] - an[6] * bn[9] ;
			c[20] += + an[6] * bn[1] - an[5] * bn[2] + an[8] * bn[3] - an[7] * bn[4] + an[0] * bn[8] + an[1] * bn[9] ;
			c[21] += - an[6] * bn[0] + an[4] * bn[2] + an[9] * bn[3] - an[7] * bn[5] - an[0] * bn[7] + an[2] * bn[9] ;
			c[22] += + an[5] * bn[0] - an[4] * bn[1] + an[9] * bn[4] - an[8] * bn[5] + an[0] * bn[6] + an[3] * bn[9] ;
			c[23] += - an[8] * bn[0] - an[9] * bn[1] + an[4] * bn[4] + an[5] * bn[5] - an[1] * bn[7] - an[2] * bn[8] ;
			c[24] += + an[7] * bn[0] - an[9] * bn[2] - an[4] * bn[3] + an[6] * bn[5] + an[1] * bn[6] - an[3] * bn[8] ;
			c[25] += + an[7] * bn[1] + an[8] * bn[2] - an[5] * bn[3] - an[6] * bn[4] + an[2] * bn[6] + an[3] * bn[7] ;
			c[31] += + an[9] * bn[0] - an[8] * bn[1] + an[7] * bn[2] + an[6] * bn[3] - an[5] * bn[4] + an[4] * bn[5] - an[3] * bn[6] + an[2] * bn[7] - an[1] * bn[8] + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
			c[6] += + an[3] * bn[2] - an[2] * bn[3] + an[6] * bn[5] - an[5] * bn[6] + an[8] * bn[7] - an[7] * bn[8] ;
			c[7] += - an[3] * bn[1] + an[1] * bn[3] - an[6] * bn[4] + an[4] * bn[6] + an[9] * bn[7] - an[7] * bn[9] ;
			c[8] += + an[2] * bn[1] - an[1] * bn[2] + an[5] * bn[4] - an[4] * bn[5] + an[9] * bn[8] - an[8] * bn[9] ;
			c[9] += + an[3] * bn[0] - an[0] * bn[3] - an[8] * bn[4] - an[9] * bn[5] + an[4] * bn[8] + an[5] * bn[9] ;
			c[10] += - an[2] * bn[0] + an[0] * bn[2] + an[7] * bn[4] - an[9] * bn[6] - an[4] * bn[7] + an[6] * bn[9] ;
			c[11] += + an[1] * bn[0] - an[0] * bn[1] + an[7] * bn[5] + an[8] * bn[6] - an[5] * bn[7] - an[6] * bn[8] ;
			c[12] += + an[6] * bn[0] + an[8] * bn[1] + an[9] * bn[2] - an[0] * bn[6] - an[1] * bn[8] - an[2] * bn[9] ;
			c[13] += - an[5] * bn[0] - an[7] * bn[1] + an[9] * bn[3] + an[0] * bn[5] + an[1] * bn[7] - an[3] * bn[9] ;
			c[14] += + an[4] * bn[0] - an[7] * bn[2] - an[8] * bn[3] - an[0] * bn[4] + an[2] * bn[7] + an[3] * bn[8] ;
			c[15] += + an[4] * bn[1] + an[5] * bn[2] + an[6] * bn[3] - an[1] * bn[4] - an[2] * bn[5] - an[3] * bn[6] ;
			c[26] += + an[9] * bn[4] - an[8] * bn[5] + an[7] * bn[6] + an[6] * bn[7] - an[5] * bn[8] + an[4] * bn[9] ;
			c[27] += - an[9] * bn[1] + an[8] * bn[2] - an[7] * bn[3] - an[3] * bn[7] + an[2] * bn[8] - an[1] * bn[9] ;
			c[28] += + an[9] * bn[0] - an[6] * bn[2] + an[5] * bn[3] + an[3] * bn[5] - an[2] * bn[6] + an[0] * bn[9] ;
			c[29] += - an[8] * bn[0] + an[6] * bn[1] - an[4] * bn[3] - an[3] * bn[4] + an[1] * bn[6] - an[0] * bn[8] ;
			c[30] += + an[7] * bn[0] - an[5] * bn[1] + an[4] * bn[2] + an[2] * bn[4] - an[1] * bn[5] + an[0] * bn[7] ;
		}
		if (bn = b[4]) {
			c[1] += + an[3] * bn[0] + an[6] * bn[1] + an[8] * bn[2] + an[9] * bn[3] ;
			c[2] += - an[2] * bn[0] - an[5] * bn[1] - an[7] * bn[2] + an[9] * bn[4] ;
			c[3] += + an[1] * bn[0] + an[4] * bn[1] - an[7] * bn[3] - an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
			c[5] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
			c[16] += - an[9] * bn[2] + an[8] * bn[3] - an[7] * bn[4] ;
			c[17] += + an[9] * bn[1] - an[6] * bn[3] + an[5] * bn[4] ;
			c[18] += - an[8] * bn[1] + an[6] * bn[2] - an[4] * bn[4] ;
			c[19] += + an[7] * bn[1] - an[5] * bn[2] + an[4] * bn[3] ;
			c[20] += - an[9] * bn[0] + an[3] * bn[3] - an[2] * bn[4] ;
			c[21] += + an[8] * bn[0] - an[3] * bn[2] + an[1] * bn[4] ;
			c[22] += - an[7] * bn[0] + an[2] * bn[2] - an[1] * bn[3] ;
			c[23] += - an[6] * bn[0] + an[3] * bn[1] - an[0] * bn[4] ;
			c[24] += + an[5] * bn[0] - an[2] * bn[1] + an[0] * bn[3] ;
			c[25] += - an[4] * bn[0] + an[1] * bn[1] - an[0] * bn[2] ;
		}
		if (bn = b[5]) {
			c[6] += - an[9] * bn[0] ;
			c[7] += + an[8] * bn[0] ;
			c[8] += - an[7] * bn[0] ;
			c[9] += - an[6] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
			c[11] += - an[4] * bn[0] ;
			c[12] += + an[3] * bn[0] ;
			c[13] += - an[2] * bn[0] ;
			c[14] += + an[1] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[1] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += + an[3] * bn[0] ;
			c[30] += + an[4] * bn[0] ;
		}
		if (bn = b[1]) {
			c[16] += + an[0] * bn[3] + an[1] * bn[4] ;
			c[17] += - an[0] * bn[2] + an[2] * bn[4] ;
			c[18] += + an[0] * bn[1] + an[3] * bn[4] ;
			c[19] += - an[0] * bn[0] + an[4] * bn[4] ;
			c[20] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[21] += + an[1] * bn[1] - an[3] * bn[3] ;
			c[22] += - an[1] * bn[0] - an[4] * bn[3] ;
			c[23] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[24] += - an[2] * bn[0] + an[4] * bn[2] ;
			c[25] += - an[3] * bn[0] - an[4] * bn[1] ;
			c[31] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += - an[0] * bn[5] - an[1] * bn[8] - an[2] * bn[9] ;
			c[7] += + an[0] * bn[4] + an[1] * bn[7] - an[3] * bn[9] ;
			c[8] += - an[0] * bn[3] - an[1] * bn[6] - an[4] * bn[9] ;
			c[9] += - an[0] * bn[2] + an[2] * bn[7] + an[3] * bn[8] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[6] + an[4] * bn[8] ;
			c[11] += - an[0] * bn[0] - an[3] * bn[6] - an[4] * bn[7] ;
			c[12] += - an[1] * bn[2] - an[2] * bn[4] - an[3] * bn[5] ;
			c[13] += + an[1] * bn[1] + an[2] * bn[3] - an[4] * bn[5] ;
			c[14] += - an[1] * bn[0] + an[3] * bn[3] + an[4] * bn[4] ;
			c[15] += - an[2] * bn[0] - an[3] * bn[1] - an[4] * bn[2] ;
			c[26] += + an[4] * bn[6] - an[3] * bn[7] + an[2] * bn[8] - an[1] * bn[9] ;
			c[27] += - an[4] * bn[3] + an[3] * bn[4] - an[2] * bn[5] + an[0] * bn[9] ;
			c[28] += + an[4] * bn[1] - an[3] * bn[2] + an[1] * bn[5] - an[0] * bn[8] ;
			c[29] += - an[4] * bn[0] + an[2] * bn[2] - an[1] * bn[4] + an[0] * bn[7] ;
			c[30] += + an[3] * bn[0] - an[2] * bn[1] + an[1] * bn[3] - an[0] * bn[6] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[3] - an[1] * bn[6] - an[2] * bn[8] - an[3] * bn[9] ;
			c[2] += + an[0] * bn[2] + an[1] * bn[5] + an[2] * bn[7] - an[4] * bn[9] ;
			c[3] += - an[0] * bn[1] - an[1] * bn[4] + an[3] * bn[7] + an[4] * bn[8] ;
			c[4] += + an[0] * bn[0] - an[2] * bn[4] - an[3] * bn[5] - an[4] * bn[6] ;
			c[5] += + an[1] * bn[0] + an[2] * bn[1] + an[3] * bn[2] + an[4] * bn[3] ;
			c[16] += - an[4] * bn[7] + an[3] * bn[8] - an[2] * bn[9] ;
			c[17] += + an[4] * bn[5] - an[3] * bn[6] + an[1] * bn[9] ;
			c[18] += - an[4] * bn[4] + an[2] * bn[6] - an[1] * bn[8] ;
			c[19] += + an[3] * bn[4] - an[2] * bn[5] + an[1] * bn[7] ;
			c[20] += - an[4] * bn[2] + an[3] * bn[3] - an[0] * bn[9] ;
			c[21] += + an[4] * bn[1] - an[2] * bn[3] + an[0] * bn[8] ;
			c[22] += - an[3] * bn[1] + an[2] * bn[2] - an[0] * bn[7] ;
			c[23] += - an[4] * bn[0] + an[1] * bn[3] - an[0] * bn[6] ;
			c[24] += + an[3] * bn[0] - an[1] * bn[2] + an[0] * bn[5] ;
			c[25] += - an[2] * bn[0] + an[1] * bn[1] - an[0] * bn[4] ;
		}
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
			c[6] += - an[4] * bn[3] + an[3] * bn[4] ;
			c[7] += + an[4] * bn[2] - an[2] * bn[4] ;
			c[8] += - an[3] * bn[2] + an[2] * bn[3] ;
			c[9] += - an[4] * bn[1] + an[1] * bn[4] ;
			c[10] += + an[3] * bn[1] - an[1] * bn[3] ;
			c[11] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[12] += + an[4] * bn[0] - an[0] * bn[4] ;
			c[13] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[14] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[15] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[5]) {
			c[1] += + an[4] * bn[0] ;
			c[2] += - an[3] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[1] * bn[0] ;
			c[5] += + an[0] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[0]) {
			c[31] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[26] += + an[0] * bn[4] ;
			c[27] += - an[0] * bn[3] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += - an[0] * bn[1] ;
			c[30] += + an[0] * bn[0] ;
		}
		if (bn = b[2]) {
			c[16] += - an[0] * bn[9] ;
			c[17] += + an[0] * bn[8] ;
			c[18] += - an[0] * bn[7] ;
			c[19] += + an[0] * bn[6] ;
			c[20] += - an[0] * bn[5] ;
			c[21] += + an[0] * bn[4] ;
			c[22] += - an[0] * bn[3] ;
			c[23] += - an[0] * bn[2] ;
			c[24] += + an[0] * bn[1] ;
			c[25] += - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[6] += - an[0] * bn[9] ;
			c[7] += + an[0] * bn[8] ;
			c[8] += - an[0] * bn[7] ;
			c[9] += - an[0] * bn[6] ;
			c[10] += + an[0] * bn[5] ;
			c[11] += - an[0] * bn[4] ;
			c[12] += + an[0] * bn[3] ;
			c[13] += - an[0] * bn[2] ;
			c[14] += + an[0] * bn[1] ;
			c[15] += - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += + an[0] * bn[4] ;
			c[2] += - an[0] * bn[3] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += - an[0] * bn[1] ;
			c[5] += + an[0] * bn[0] ;
		}
		if (bn = b[5]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void c3gai_general_lcem(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
			c[5] += + an[0] * bn[4] ;
		}
		if (bn = b[2]) {
			c[6] += + an[0] * bn[0] ;
			c[7] += + an[0] * bn[1] ;
			c[8] += + an[0] * bn[2] ;
			c[9] += + an[0] * bn[3] ;
			c[10] += + an[0] * bn[4] ;
			c[11] += + an[0] * bn[5] ;
			c[12] += + an[0] * bn[6] ;
			c[13] += + an[0] * bn[7] ;
			c[14] += + an[0] * bn[8] ;
			c[15] += + an[0] * bn[9] ;
		}
		if (bn = b[3]) {
			c[16] += + an[0] * bn[0] ;
			c[17] += + an[0] * bn[1] ;
			c[18] += + an[0] * bn[2] ;
			c[19] += + an[0] * bn[3] ;
			c[20] += + an[0] * bn[4] ;
			c[21] += + an[0] * bn[5] ;
			c[22] += + an[0] * bn[6] ;
			c[23] += + an[0] * bn[7] ;
			c[24] += + an[0] * bn[8] ;
			c[25] += + an[0] * bn[9] ;
		}
		if (bn = b[4]) {
			c[26] += + an[0] * bn[0] ;
			c[27] += + an[0] * bn[1] ;
			c[28] += + an[0] * bn[2] ;
			c[29] += + an[0] * bn[3] ;
			c[30] += + an[0] * bn[4] ;
		}
		if (bn = b[5]) {
			c[31] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[0] - an[2] * bn[1] - an[3] * bn[3] - an[4] * bn[6] ;
			c[2] += + an[0] * bn[0] - an[2] * bn[2] - an[3] * bn[4] - an[4] * bn[7] ;
			c[3] += + an[0] * bn[1] + an[1] * bn[2] - an[3] * bn[5] - an[4] * bn[8] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] - an[4] * bn[9] ;
			c[5] += + an[0] * bn[6] + an[1] * bn[7] + an[2] * bn[8] + an[3] * bn[9] ;
		}
		if (bn = b[3]) {
			c[6] += + an[2] * bn[0] + an[3] * bn[1] + an[4] * bn[4] ;
			c[7] += - an[1] * bn[0] + an[3] * bn[2] + an[4] * bn[5] ;
			c[8] += + an[0] * bn[0] + an[3] * bn[3] + an[4] * bn[6] ;
			c[9] += - an[1] * bn[1] - an[2] * bn[2] + an[4] * bn[7] ;
			c[10] += + an[0] * bn[1] - an[2] * bn[3] + an[4] * bn[8] ;
			c[11] += + an[0] * bn[2] + an[1] * bn[3] + an[4] * bn[9] ;
			c[12] += - an[1] * bn[4] - an[2] * bn[5] - an[3] * bn[7] ;
			c[13] += + an[0] * bn[4] - an[2] * bn[6] - an[3] * bn[8] ;
			c[14] += + an[0] * bn[5] + an[1] * bn[6] - an[3] * bn[9] ;
			c[15] += + an[0] * bn[7] + an[1] * bn[8] + an[2] * bn[9] ;
		}
		if (bn = b[4]) {
			c[16] += - an[3] * bn[0] - an[4] * bn[1] ;
			c[17] += + an[2] * bn[0] - an[4] * bn[2] ;
			c[18] += - an[1] * bn[0] - an[4] * bn[3] ;
			c[19] += + an[0] * bn[0] - an[4] * bn[4] ;
			c[20] += + an[2] * bn[1] + an[3] * bn[2] ;
			c[21] += - an[1] * bn[1] + an[3] * bn[3] ;
			c[22] += + an[0] * bn[1] + an[3] * bn[4] ;
			c[23] += - an[1] * bn[2] - an[2] * bn[3] ;
			c[24] += + an[0] * bn[2] - an[2] * bn[4] ;
			c[25] += + an[0] * bn[3] + an[1] * bn[4] ;
		}
		if (bn = b[5]) {
			c[26] += + an[4] * bn[0] ;
			c[27] += - an[3] * bn[0] ;
			c[28] += + an[2] * bn[0] ;
			c[29] += - an[1] * bn[0] ;
			c[30] += + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
		}
		if (bn = b[3]) {
			c[1] += - an[2] * bn[0] - an[4] * bn[1] - an[5] * bn[2] - an[7] * bn[4] - an[8] * bn[5] - an[9] * bn[7] ;
			c[2] += + an[1] * bn[0] + an[3] * bn[1] - an[5] * bn[3] + an[6] * bn[4] - an[8] * bn[6] - an[9] * bn[8] ;
			c[3] += - an[0] * bn[0] + an[3] * bn[2] + an[4] * bn[3] + an[6] * bn[5] + an[7] * bn[6] - an[9] * bn[9] ;
			c[4] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] + an[6] * bn[7] + an[7] * bn[8] + an[8] * bn[9] ;
			c[5] += - an[0] * bn[4] - an[1] * bn[5] - an[2] * bn[6] - an[3] * bn[7] - an[4] * bn[8] - an[5] * bn[9] ;
		}
		if (bn = b[4]) {
			c[6] += - an[5] * bn[0] - an[8] * bn[1] - an[9] * bn[2] ;
			c[7] += + an[4] * bn[0] + an[7] * bn[1] - an[9] * bn[3] ;
			c[8] += - an[3] * bn[0] - an[6] * bn[1] - an[9] * bn[4] ;
			c[9] += - an[2] * bn[0] + an[7] * bn[2] + an[8] * bn[3] ;
			c[10] += + an[1] * bn[0] - an[6] * bn[2] + an[8] * bn[4] ;
			c[11] += - an[0] * bn[0] - an[6] * bn[3] - an[7] * bn[4] ;
			c[12] += - an[2] * bn[1] - an[4] * bn[2] - an[5] * bn[3] ;
			c[13] += + an[1] * bn[1] + an[3] * bn[2] - an[5] * bn[4] ;
			c[14] += - an[0] * bn[1] + an[3] * bn[3] + an[4] * bn[4] ;
			c[15] += - an[0] * bn[2] - an[1] * bn[3] - an[2] * bn[4] ;
		}
		if (bn = b[5]) {
			c[16] += - an[9] * bn[0] ;
			c[17] += + an[8] * bn[0] ;
			c[18] += - an[7] * bn[0] ;
			c[19] += + an[6] * bn[0] ;
			c[20] += - an[5] * bn[0] ;
			c[21] += + an[4] * bn[0] ;
			c[22] += - an[3] * bn[0] ;
			c[23] += - an[2] * bn[0] ;
			c[24] += + an[1] * bn[0] ;
			c[25] += - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
		}
		if (bn = b[4]) {
			c[1] += + an[3] * bn[0] + an[6] * bn[1] + an[8] * bn[2] + an[9] * bn[3] ;
			c[2] += - an[2] * bn[0] - an[5] * bn[1] - an[7] * bn[2] + an[9] * bn[4] ;
			c[3] += + an[1] * bn[0] + an[4] * bn[1] - an[7] * bn[3] - an[8] * bn[4] ;
			c[4] += - an[0] * bn[0] + an[4] * bn[2] + an[5] * bn[3] + an[6] * bn[4] ;
			c[5] += - an[0] * bn[1] - an[1] * bn[2] - an[2] * bn[3] - an[3] * bn[4] ;
		}
		if (bn = b[5]) {
			c[6] += - an[9] * bn[0] ;
			c[7] += + an[8] * bn[0] ;
			c[8] += - an[7] * bn[0] ;
			c[9] += - an[6] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
			c[11] += - an[4] * bn[0] ;
			c[12] += + an[3] * bn[0] ;
			c[13] += - an[2] * bn[0] ;
			c[14] += + an[1] * bn[0] ;
			c[15] += - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
		}
		if (bn = b[5]) {
			c[1] += + an[4] * bn[0] ;
			c[2] += - an[3] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[1] * bn[0] ;
			c[5] += + an[0] * bn[0] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[5]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void c3gai_general_scpem(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	c3gai_null(c, 32);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] - an[6] * bn[6] - an[7] * bn[7] - an[8] * bn[8] - an[9] * bn[9] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] + an[4] * bn[4] ;
		}
	}
	if (an = a[5]) {
		if (bn = b[5]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void c3gai_opt_om_01x01(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] ;
}

void c3gai_opt_om_05x05(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] + a[4] * b[4] ;
	c[1] = + a[5] * b[0] + a[6] * b[1] + a[7] * b[2] + a[8] * b[3] + a[9] * b[4] ;
	c[2] = + a[10] * b[0] + a[11] * b[1] + a[12] * b[2] + a[13] * b[3] + a[14] * b[4] ;
	c[3] = + a[15] * b[0] + a[16] * b[1] + a[17] * b[2] + a[18] * b[3] + a[19] * b[4] ;
	c[4] = + a[20] * b[0] + a[21] * b[1] + a[22] * b[2] + a[23] * b[3] + a[24] * b[4] ;
}

void c3gai_opt_om_0Ax0A(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] + a[4] * b[4] + a[5] * b[5] + a[6] * b[6] + a[7] * b[7] + a[8] * b[8] + a[9] * b[9] ;
	c[1] = + a[10] * b[0] + a[11] * b[1] + a[12] * b[2] + a[13] * b[3] + a[14] * b[4] + a[15] * b[5] + a[16] * b[6] + a[17] * b[7] + a[18] * b[8] + a[19] * b[9] ;
	c[2] = + a[20] * b[0] + a[21] * b[1] + a[22] * b[2] + a[23] * b[3] + a[24] * b[4] + a[25] * b[5] + a[26] * b[6] + a[27] * b[7] + a[28] * b[8] + a[29] * b[9] ;
	c[3] = + a[30] * b[0] + a[31] * b[1] + a[32] * b[2] + a[33] * b[3] + a[34] * b[4] + a[35] * b[5] + a[36] * b[6] + a[37] * b[7] + a[38] * b[8] + a[39] * b[9] ;
	c[4] = + a[40] * b[0] + a[41] * b[1] + a[42] * b[2] + a[43] * b[3] + a[44] * b[4] + a[45] * b[5] + a[46] * b[6] + a[47] * b[7] + a[48] * b[8] + a[49] * b[9] ;
	c[5] = + a[50] * b[0] + a[51] * b[1] + a[52] * b[2] + a[53] * b[3] + a[54] * b[4] + a[55] * b[5] + a[56] * b[6] + a[57] * b[7] + a[58] * b[8] + a[59] * b[9] ;
	c[6] = + a[60] * b[0] + a[61] * b[1] + a[62] * b[2] + a[63] * b[3] + a[64] * b[4] + a[65] * b[5] + a[66] * b[6] + a[67] * b[7] + a[68] * b[8] + a[69] * b[9] ;
	c[7] = + a[70] * b[0] + a[71] * b[1] + a[72] * b[2] + a[73] * b[3] + a[74] * b[4] + a[75] * b[5] + a[76] * b[6] + a[77] * b[7] + a[78] * b[8] + a[79] * b[9] ;
	c[8] = + a[80] * b[0] + a[81] * b[1] + a[82] * b[2] + a[83] * b[3] + a[84] * b[4] + a[85] * b[5] + a[86] * b[6] + a[87] * b[7] + a[88] * b[8] + a[89] * b[9] ;
	c[9] = + a[90] * b[0] + a[91] * b[1] + a[92] * b[2] + a[93] * b[3] + a[94] * b[4] + a[95] * b[5] + a[96] * b[6] + a[97] * b[7] + a[98] * b[8] + a[99] * b[9] ;
}

void c3gai_copy(double *dest, const double *src, int length) {
	memcpy(dest, src, length * sizeof(double));
}

void c3gai_reverse(double *a[]) {
	double *an;
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
		an[6] = -an[6];
		an[7] = -an[7];
		an[8] = -an[8];
		an[9] = -an[9];
	}
	if (an = a[3]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
		an[6] = -an[6];
		an[7] = -an[7];
		an[8] = -an[8];
		an[9] = -an[9];
	}
}

void c3gai_cliffordConjugate(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
	}
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
		an[6] = -an[6];
		an[7] = -an[7];
		an[8] = -an[8];
		an[9] = -an[9];
	}
	if (an = a[5]) {
		an[0] = -an[0];
	}
}

void c3gai_involution(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
	}
	if (an = a[3]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
		an[6] = -an[6];
		an[7] = -an[7];
		an[8] = -an[8];
		an[9] = -an[9];
	}
	if (an = a[5]) {
		an[0] = -an[0];
	}
}

void c3gai_negate(double *dest, const double *src, int length) {
	int i;
	for (i = 0; i < length; i++)
		dest[i] = -src[i];
}

double c3gai_norm_a(const double a[], int nb) {
	int i;
	double norm = 0.0;
	for (i = 0; i < nb; i++)
		norm += a[i] * a[i];
	return norm;
}

void c3gai_addSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] + b[i];
}

void c3gai_add(const double *a[6], const double *b[6], double *c[6]) {
	double const *an, *bn;
	double *cn;

	if (cn = c[0]) {
		bn = b[0];
		if ((an = a[0]) && bn) {
			cn[0] = an[0] + bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = bn[0];
		}
	}
	if (cn = c[1]) {
		bn = b[1];
		if ((an = a[1]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
			cn[3] = an[3] + bn[3];
			cn[4] = an[4] + bn[4];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
			cn[4] = bn[4];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
			cn[3] = an[3] + bn[3];
			cn[4] = an[4] + bn[4];
			cn[5] = an[5] + bn[5];
			cn[6] = an[6] + bn[6];
			cn[7] = an[7] + bn[7];
			cn[8] = an[8] + bn[8];
			cn[9] = an[9] + bn[9];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
			cn[6] = an[6];
			cn[7] = an[7];
			cn[8] = an[8];
			cn[9] = an[9];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
			cn[4] = bn[4];
			cn[5] = bn[5];
			cn[6] = bn[6];
			cn[7] = bn[7];
			cn[8] = bn[8];
			cn[9] = bn[9];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
			cn[3] = an[3] + bn[3];
			cn[4] = an[4] + bn[4];
			cn[5] = an[5] + bn[5];
			cn[6] = an[6] + bn[6];
			cn[7] = an[7] + bn[7];
			cn[8] = an[8] + bn[8];
			cn[9] = an[9] + bn[9];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
			cn[6] = an[6];
			cn[7] = an[7];
			cn[8] = an[8];
			cn[9] = an[9];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
			cn[4] = bn[4];
			cn[5] = bn[5];
			cn[6] = bn[6];
			cn[7] = bn[7];
			cn[8] = bn[8];
			cn[9] = bn[9];
		}
	}
	if (cn = c[4]) {
		bn = b[4];
		if ((an = a[4]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
			cn[3] = an[3] + bn[3];
			cn[4] = an[4] + bn[4];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
			cn[4] = bn[4];
		}
	}
	if (cn = c[5]) {
		bn = b[5];
		if ((an = a[5]) && bn) {
			cn[0] = an[0] + bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = bn[0];
		}
	}
}

void c3gai_subSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] - b[i];
}

void c3gai_sub(const double *a[6], const double *b[6], double *c[6]) {
	double const *an, *bn;
	double *cn;

	if (cn = c[0]) {
		bn = b[0];
		if ((an = a[0]) && bn) {
			cn[0] = an[0] - bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = -bn[0];
		}
	}
	if (cn = c[1]) {
		bn = b[1];
		if ((an = a[1]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
			cn[3] = an[3] - bn[3];
			cn[4] = an[4] - bn[4];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
			cn[4] = -bn[4];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
			cn[3] = an[3] - bn[3];
			cn[4] = an[4] - bn[4];
			cn[5] = an[5] - bn[5];
			cn[6] = an[6] - bn[6];
			cn[7] = an[7] - bn[7];
			cn[8] = an[8] - bn[8];
			cn[9] = an[9] - bn[9];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
			cn[6] = an[6];
			cn[7] = an[7];
			cn[8] = an[8];
			cn[9] = an[9];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
			cn[4] = -bn[4];
			cn[5] = -bn[5];
			cn[6] = -bn[6];
			cn[7] = -bn[7];
			cn[8] = -bn[8];
			cn[9] = -bn[9];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
			cn[3] = an[3] - bn[3];
			cn[4] = an[4] - bn[4];
			cn[5] = an[5] - bn[5];
			cn[6] = an[6] - bn[6];
			cn[7] = an[7] - bn[7];
			cn[8] = an[8] - bn[8];
			cn[9] = an[9] - bn[9];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
			cn[6] = an[6];
			cn[7] = an[7];
			cn[8] = an[8];
			cn[9] = an[9];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
			cn[4] = -bn[4];
			cn[5] = -bn[5];
			cn[6] = -bn[6];
			cn[7] = -bn[7];
			cn[8] = -bn[8];
			cn[9] = -bn[9];
		}
	}
	if (cn = c[4]) {
		bn = b[4];
		if ((an = a[4]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
			cn[3] = an[3] - bn[3];
			cn[4] = an[4] - bn[4];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
			cn[4] = -bn[4];
		}
	}
	if (cn = c[5]) {
		bn = b[5];
		if ((an = a[5]) && bn) {
			cn[0] = an[0] - bn[0];
		}
		else if (an) {
			cn[0] = an[0];
		}
		else {
			cn[0] = -bn[0];
		}
	}
}
#ifdef __cplusplus
}
#endif /* __cplusplus */
