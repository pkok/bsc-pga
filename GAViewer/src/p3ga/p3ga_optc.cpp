
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

void p3gai_null(double *dest, int length) {
	memset(dest, 0, length * sizeof(double));
}

void p3gai_general_gp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[0] * bn[1] ;
			c[7] += + an[0] * bn[2] ;
			c[8] += + an[0] * bn[3] ;
			c[9] += + an[0] * bn[4] ;
			c[10] += + an[0] * bn[5] ;
		}
		if (bn = b[3]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[0] * bn[1] ;
			c[13] += + an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[15] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
			c[5] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[6] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[7] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[8] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[9] += - an[3] * bn[1] + an[1] * bn[3] ;
			c[10] += - an[3] * bn[2] + an[2] * bn[3] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] - an[3] * bn[3] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] - an[3] * bn[4] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] - an[3] * bn[5] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
			c[11] += + an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[12] += + an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[13] += + an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[14] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[5] += + an[0] * bn[3] + an[3] * bn[0] ;
			c[6] += + an[1] * bn[3] + an[3] * bn[1] ;
			c[7] += + an[2] * bn[3] + an[3] * bn[2] ;
			c[8] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[9] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[10] += - an[0] * bn[1] + an[1] * bn[0] ;
			c[15] += - an[3] * bn[3] + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += - an[3] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[1] * bn[0] ;
			c[7] += + an[2] * bn[0] ;
			c[8] += + an[3] * bn[0] ;
			c[9] += + an[4] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] + an[3] * bn[3] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] + an[4] * bn[3] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] + an[5] * bn[3] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] ;
			c[11] += + an[5] * bn[1] - an[4] * bn[2] + an[0] * bn[3] ;
			c[12] += - an[5] * bn[0] + an[3] * bn[2] + an[1] * bn[3] ;
			c[13] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[3] ;
			c[14] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
			c[5] += - an[1] * bn[2] + an[2] * bn[1] + an[5] * bn[4] - an[4] * bn[5] ;
			c[6] += + an[0] * bn[2] - an[2] * bn[0] - an[5] * bn[3] + an[3] * bn[5] ;
			c[7] += - an[0] * bn[1] + an[1] * bn[0] + an[4] * bn[3] - an[3] * bn[4] ;
			c[8] += - an[4] * bn[2] + an[5] * bn[1] + an[2] * bn[4] - an[1] * bn[5] ;
			c[9] += + an[3] * bn[2] - an[5] * bn[0] - an[2] * bn[3] + an[0] * bn[5] ;
			c[10] += - an[3] * bn[1] + an[4] * bn[0] + an[1] * bn[3] - an[0] * bn[4] ;
			c[15] += + an[5] * bn[2] + an[4] * bn[1] + an[3] * bn[0] + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[3] - an[4] * bn[2] + an[5] * bn[1] ;
			c[2] += - an[1] * bn[3] + an[3] * bn[2] - an[5] * bn[0] ;
			c[3] += - an[2] * bn[3] - an[3] * bn[1] + an[4] * bn[0] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
			c[11] += - an[3] * bn[3] - an[1] * bn[2] + an[2] * bn[1] ;
			c[12] += - an[4] * bn[3] + an[0] * bn[2] - an[2] * bn[0] ;
			c[13] += - an[5] * bn[3] - an[0] * bn[1] + an[1] * bn[0] ;
			c[14] += + an[5] * bn[2] + an[4] * bn[1] + an[3] * bn[0] ;
		}
		if (bn = b[4]) {
			c[5] += - an[3] * bn[0] ;
			c[6] += - an[4] * bn[0] ;
			c[7] += - an[5] * bn[0] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[1] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[5] += + an[3] * bn[0] + an[0] * bn[3] ;
			c[6] += + an[3] * bn[1] + an[1] * bn[3] ;
			c[7] += + an[3] * bn[2] + an[2] * bn[3] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[10] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[15] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[3] * bn[3] ;
		}
		if (bn = b[2]) {
			c[1] += - an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[2] += - an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[3] += - an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
			c[11] += - an[1] * bn[2] + an[2] * bn[1] + an[3] * bn[3] ;
			c[12] += + an[0] * bn[2] - an[2] * bn[0] + an[3] * bn[4] ;
			c[13] += - an[0] * bn[1] + an[1] * bn[0] + an[3] * bn[5] ;
			c[14] += - an[0] * bn[3] - an[1] * bn[4] - an[2] * bn[5] ;
		}
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
			c[5] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[6] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[7] += - an[0] * bn[1] + an[1] * bn[0] ;
			c[8] += + an[0] * bn[3] - an[3] * bn[0] ;
			c[9] += + an[1] * bn[3] - an[3] * bn[1] ;
			c[10] += + an[2] * bn[3] - an[3] * bn[2] ;
		}
		if (bn = b[4]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[3] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[15] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[11] += - an[0] * bn[0] ;
			c[12] += - an[0] * bn[1] ;
			c[13] += - an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += - an[0] * bn[3] ;
			c[6] += - an[0] * bn[4] ;
			c[7] += - an[0] * bn[5] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[0] * bn[1] ;
			c[10] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_lcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[0] * bn[1] ;
			c[7] += + an[0] * bn[2] ;
			c[8] += + an[0] * bn[3] ;
			c[9] += + an[0] * bn[4] ;
			c[10] += + an[0] * bn[5] ;
		}
		if (bn = b[3]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[0] * bn[1] ;
			c[13] += + an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[15] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] - an[3] * bn[3] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] - an[3] * bn[4] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] - an[3] * bn[5] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
		}
		if (bn = b[3]) {
			c[5] += + an[0] * bn[3] + an[3] * bn[0] ;
			c[6] += + an[1] * bn[3] + an[3] * bn[1] ;
			c[7] += + an[2] * bn[3] + an[3] * bn[2] ;
			c[8] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[9] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[10] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[4]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += - an[3] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[3] - an[4] * bn[2] + an[5] * bn[1] ;
			c[2] += - an[1] * bn[3] + an[3] * bn[2] - an[5] * bn[0] ;
			c[3] += - an[2] * bn[3] - an[3] * bn[1] + an[4] * bn[0] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[5] += - an[3] * bn[0] ;
			c[6] += - an[4] * bn[0] ;
			c[7] += - an[5] * bn[0] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[1] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[3] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_op(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[0] * bn[1] ;
			c[7] += + an[0] * bn[2] ;
			c[8] += + an[0] * bn[3] ;
			c[9] += + an[0] * bn[4] ;
			c[10] += + an[0] * bn[5] ;
		}
		if (bn = b[3]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[0] * bn[1] ;
			c[13] += + an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[15] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[5] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[6] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[7] += - an[1] * bn[0] + an[0] * bn[1] ;
			c[8] += - an[3] * bn[0] + an[0] * bn[3] ;
			c[9] += - an[3] * bn[1] + an[1] * bn[3] ;
			c[10] += - an[3] * bn[2] + an[2] * bn[3] ;
		}
		if (bn = b[2]) {
			c[11] += + an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[12] += + an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[13] += + an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[14] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[15] += - an[3] * bn[3] + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[1] * bn[0] ;
			c[7] += + an[2] * bn[0] ;
			c[8] += + an[3] * bn[0] ;
			c[9] += + an[4] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
		}
		if (bn = b[1]) {
			c[11] += + an[5] * bn[1] - an[4] * bn[2] + an[0] * bn[3] ;
			c[12] += - an[5] * bn[0] + an[3] * bn[2] + an[1] * bn[3] ;
			c[13] += + an[4] * bn[0] - an[3] * bn[1] + an[2] * bn[3] ;
			c[14] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[15] += + an[5] * bn[2] + an[4] * bn[1] + an[3] * bn[0] + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[15] += - an[0] * bn[0] - an[1] * bn[1] - an[2] * bn[2] + an[3] * bn[3] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[15] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_scp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_hip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] - an[3] * bn[3] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] - an[3] * bn[4] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] - an[3] * bn[5] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
		}
		if (bn = b[3]) {
			c[5] += + an[0] * bn[3] + an[3] * bn[0] ;
			c[6] += + an[1] * bn[3] + an[3] * bn[1] ;
			c[7] += + an[2] * bn[3] + an[3] * bn[2] ;
			c[8] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[9] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[10] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[4]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += - an[3] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] + an[3] * bn[3] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] + an[4] * bn[3] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] + an[5] * bn[3] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[3] - an[4] * bn[2] + an[5] * bn[1] ;
			c[2] += - an[1] * bn[3] + an[3] * bn[2] - an[5] * bn[0] ;
			c[3] += - an[2] * bn[3] - an[3] * bn[1] + an[4] * bn[0] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[5] += - an[3] * bn[0] ;
			c[6] += - an[4] * bn[0] ;
			c[7] += - an[5] * bn[0] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[1] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[1]) {
			c[5] += + an[3] * bn[0] + an[0] * bn[3] ;
			c[6] += + an[3] * bn[1] + an[1] * bn[3] ;
			c[7] += + an[3] * bn[2] + an[2] * bn[3] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[10] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[1] += - an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[2] += - an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[3] += - an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[3] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[1]) {
			c[11] += - an[0] * bn[0] ;
			c[12] += - an[0] * bn[1] ;
			c[13] += - an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += - an[0] * bn[3] ;
			c[6] += - an[0] * bn[4] ;
			c[7] += - an[0] * bn[5] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[0] * bn[1] ;
			c[10] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_mhip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[0] * bn[1] ;
			c[7] += + an[0] * bn[2] ;
			c[8] += + an[0] * bn[3] ;
			c[9] += + an[0] * bn[4] ;
			c[10] += + an[0] * bn[5] ;
		}
		if (bn = b[3]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[0] * bn[1] ;
			c[13] += + an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[15] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] - an[3] * bn[3] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] - an[3] * bn[4] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] - an[3] * bn[5] ;
			c[4] += + an[0] * bn[3] + an[1] * bn[4] + an[2] * bn[5] ;
		}
		if (bn = b[3]) {
			c[5] += + an[0] * bn[3] + an[3] * bn[0] ;
			c[6] += + an[1] * bn[3] + an[3] * bn[1] ;
			c[7] += + an[2] * bn[3] + an[3] * bn[2] ;
			c[8] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[9] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[10] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[4]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += - an[3] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[1] * bn[0] ;
			c[7] += + an[2] * bn[0] ;
			c[8] += + an[3] * bn[0] ;
			c[9] += + an[4] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] + an[3] * bn[3] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] + an[4] * bn[3] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] + an[5] * bn[3] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[3] - an[4] * bn[2] + an[5] * bn[1] ;
			c[2] += - an[1] * bn[3] + an[3] * bn[2] - an[5] * bn[0] ;
			c[3] += - an[2] * bn[3] - an[3] * bn[1] + an[4] * bn[0] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[5] += - an[3] * bn[0] ;
			c[6] += - an[4] * bn[0] ;
			c[7] += - an[5] * bn[0] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[1] * bn[0] ;
			c[10] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[5] += + an[3] * bn[0] + an[0] * bn[3] ;
			c[6] += + an[3] * bn[1] + an[1] * bn[3] ;
			c[7] += + an[3] * bn[2] + an[2] * bn[3] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[10] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[1] += - an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[2] += - an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[3] += - an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[4]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
			c[4] += - an[3] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[15] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[11] += - an[0] * bn[0] ;
			c[12] += - an[0] * bn[1] ;
			c[13] += - an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += - an[0] * bn[3] ;
			c[6] += - an[0] * bn[4] ;
			c[7] += - an[0] * bn[5] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[0] * bn[1] ;
			c[10] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_general_rcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	p3gai_null(c, 16);
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
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] + an[3] * bn[3] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[5] += + an[0] * bn[0] ;
			c[6] += + an[1] * bn[0] ;
			c[7] += + an[2] * bn[0] ;
			c[8] += + an[3] * bn[0] ;
			c[9] += + an[4] * bn[0] ;
			c[10] += + an[5] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] + an[3] * bn[3] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] + an[4] * bn[3] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] + an[5] * bn[3] ;
			c[4] += - an[3] * bn[0] - an[4] * bn[1] - an[5] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] - an[3] * bn[3] - an[4] * bn[4] - an[5] * bn[5] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[11] += + an[0] * bn[0] ;
			c[12] += + an[1] * bn[0] ;
			c[13] += + an[2] * bn[0] ;
			c[14] += + an[3] * bn[0] ;
		}
		if (bn = b[1]) {
			c[5] += + an[3] * bn[0] + an[0] * bn[3] ;
			c[6] += + an[3] * bn[1] + an[1] * bn[3] ;
			c[7] += + an[3] * bn[2] + an[2] * bn[3] ;
			c[8] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[9] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[10] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[1] += - an[3] * bn[0] - an[2] * bn[4] + an[1] * bn[5] ;
			c[2] += - an[3] * bn[1] + an[2] * bn[3] - an[0] * bn[5] ;
			c[3] += - an[3] * bn[2] - an[1] * bn[3] + an[0] * bn[4] ;
			c[4] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[0] += - an[3] * bn[3] - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
	}
	if (an = a[4]) {
		if (bn = b[0]) {
			c[15] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[11] += - an[0] * bn[0] ;
			c[12] += - an[0] * bn[1] ;
			c[13] += - an[0] * bn[2] ;
			c[14] += + an[0] * bn[3] ;
		}
		if (bn = b[2]) {
			c[5] += - an[0] * bn[3] ;
			c[6] += - an[0] * bn[4] ;
			c[7] += - an[0] * bn[5] ;
			c[8] += - an[0] * bn[0] ;
			c[9] += - an[0] * bn[1] ;
			c[10] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
			c[4] += + an[0] * bn[3] ;
		}
		if (bn = b[4]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
}

void p3gai_opt_om_01x01(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] ;
}

void p3gai_opt_om_04x04(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] ;
	c[1] = + a[4] * b[0] + a[5] * b[1] + a[6] * b[2] + a[7] * b[3] ;
	c[2] = + a[8] * b[0] + a[9] * b[1] + a[10] * b[2] + a[11] * b[3] ;
	c[3] = + a[12] * b[0] + a[13] * b[1] + a[14] * b[2] + a[15] * b[3] ;
}

void p3gai_opt_om_06x06(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3] + a[4] * b[4] + a[5] * b[5] ;
	c[1] = + a[6] * b[0] + a[7] * b[1] + a[8] * b[2] + a[9] * b[3] + a[10] * b[4] + a[11] * b[5] ;
	c[2] = + a[12] * b[0] + a[13] * b[1] + a[14] * b[2] + a[15] * b[3] + a[16] * b[4] + a[17] * b[5] ;
	c[3] = + a[18] * b[0] + a[19] * b[1] + a[20] * b[2] + a[21] * b[3] + a[22] * b[4] + a[23] * b[5] ;
	c[4] = + a[24] * b[0] + a[25] * b[1] + a[26] * b[2] + a[27] * b[3] + a[28] * b[4] + a[29] * b[5] ;
	c[5] = + a[30] * b[0] + a[31] * b[1] + a[32] * b[2] + a[33] * b[3] + a[34] * b[4] + a[35] * b[5] ;
}

void p3gai_copy(double *dest, const double *src, int length) {
	memcpy(dest, src, length * sizeof(double));
}

void p3gai_reverse(double *a[]) {
	double *an;
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
	}
	if (an = a[3]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
	}
}

void p3gai_cliffordConjugate(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
	}
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
		an[4] = -an[4];
		an[5] = -an[5];
	}
}

void p3gai_involution(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
	}
	if (an = a[3]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
		an[3] = -an[3];
	}
}

void p3gai_negate(double *dest, const double *src, int length) {
	int i;
	for (i = 0; i < length; i++)
		dest[i] = -src[i];
}

double p3gai_norm_a(const double a[], int nb) {
	int i;
	double norm = 0.0;
	for (i = 0; i < nb; i++)
		norm += a[i] * a[i];
	return norm;
}

void p3gai_addSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] + b[i];
}

void p3gai_add(const double *a[5], const double *b[5], double *c[5]) {
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
			cn[4] = bn[4];
			cn[5] = bn[5];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
			cn[3] = an[3] + bn[3];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
			cn[3] = bn[3];
		}
	}
	if (cn = c[4]) {
		bn = b[4];
		if ((an = a[4]) && bn) {
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

void p3gai_subSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] - b[i];
}

void p3gai_sub(const double *a[5], const double *b[5], double *c[5]) {
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
			cn[4] = an[4];
			cn[5] = an[5];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
			cn[4] = -bn[4];
			cn[5] = -bn[5];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
			cn[3] = an[3] - bn[3];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
			cn[3] = an[3];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
			cn[3] = -bn[3];
		}
	}
	if (cn = c[4]) {
		bn = b[4];
		if ((an = a[4]) && bn) {
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
