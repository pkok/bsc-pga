
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

void e3gai_null(double *dest, int length) {
	memset(dest, 0, length * sizeof(double));
}

void e3gai_general_gp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
			c[4] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[5] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
			c[7] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] ;
			c[7] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
			c[4] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[5] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[6] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_lcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_op(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += - an[2] * bn[1] + an[1] * bn[2] ;
			c[5] += + an[2] * bn[0] - an[0] * bn[2] ;
			c[6] += - an[1] * bn[0] + an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[7] += + an[2] * bn[2] + an[1] * bn[1] + an[0] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[7] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
}

void e3gai_general_scp(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_hip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[1]) {
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[1]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_mhip(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
	if (an = a[0]) {
		if (bn = b[0]) {
			c[0] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[0] * bn[1] ;
			c[3] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[7] += + an[0] * bn[0] ;
		}
	}
	if (an = a[1]) {
		if (bn = b[0]) {
			c[1] += + an[0] * bn[0] ;
			c[2] += + an[1] * bn[0] ;
			c[3] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[1] * bn[2] + an[2] * bn[1] ;
			c[2] += + an[0] * bn[2] - an[2] * bn[0] ;
			c[3] += - an[0] * bn[1] + an[1] * bn[0] ;
		}
		if (bn = b[3]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
		if (bn = b[3]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[1] * bn[0] ;
			c[3] += - an[2] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_general_rcont(const double *a[], const double *b[], double *c) {
	const double *an, *bn;
	e3gai_null(c, 8);
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
		}
		if (bn = b[1]) {
			c[0] += + an[0] * bn[0] + an[1] * bn[1] + an[2] * bn[2] ;
		}
	}
	if (an = a[2]) {
		if (bn = b[0]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[1] * bn[0] ;
			c[6] += + an[2] * bn[0] ;
		}
		if (bn = b[1]) {
			c[1] += + an[2] * bn[1] - an[1] * bn[2] ;
			c[2] += - an[2] * bn[0] + an[0] * bn[2] ;
			c[3] += + an[1] * bn[0] - an[0] * bn[1] ;
		}
		if (bn = b[2]) {
			c[0] += - an[2] * bn[2] - an[1] * bn[1] - an[0] * bn[0] ;
		}
	}
	if (an = a[3]) {
		if (bn = b[0]) {
			c[7] += + an[0] * bn[0] ;
		}
		if (bn = b[1]) {
			c[4] += + an[0] * bn[0] ;
			c[5] += + an[0] * bn[1] ;
			c[6] += + an[0] * bn[2] ;
		}
		if (bn = b[2]) {
			c[1] += - an[0] * bn[0] ;
			c[2] += - an[0] * bn[1] ;
			c[3] += - an[0] * bn[2] ;
		}
		if (bn = b[3]) {
			c[0] += - an[0] * bn[0] ;
		}
	}
}

void e3gai_opt_om_01x01(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] ;
}

void e3gai_opt_om_03x03(const double *a, const double *b, double *c) {
	c[0] = + a[0] * b[0] + a[1] * b[1] + a[2] * b[2] ;
	c[1] = + a[3] * b[0] + a[4] * b[1] + a[5] * b[2] ;
	c[2] = + a[6] * b[0] + a[7] * b[1] + a[8] * b[2] ;
}

void e3gai_copy(double *dest, const double *src, int length) {
	memcpy(dest, src, length * sizeof(double));
}

void e3gai_reverse(double *a[]) {
	double *an;
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[3]) {
		an[0] = -an[0];
	}
}

void e3gai_cliffordConjugate(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[2]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
}

void e3gai_involution(double *a[]) {
	double *an;
	if (an = a[1]) {
		an[0] = -an[0];
		an[1] = -an[1];
		an[2] = -an[2];
	}
	if (an = a[3]) {
		an[0] = -an[0];
	}
}

void e3gai_negate(double *dest, const double *src, int length) {
	int i;
	for (i = 0; i < length; i++)
		dest[i] = -src[i];
}

double e3gai_norm_a(const double a[], int nb) {
	int i;
	double norm = 0.0;
	for (i = 0; i < nb; i++)
		norm += a[i] * a[i];
	return norm;
}

void e3gai_addSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] + b[i];
}

void e3gai_add(const double *a[4], const double *b[4], double *c[4]) {
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] + bn[0];
			cn[1] = an[1] + bn[1];
			cn[2] = an[2] + bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = bn[0];
			cn[1] = bn[1];
			cn[2] = bn[2];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
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

void e3gai_subSameGradeUsage(double *c, const double *a, const double *b, int length) {
	int i;
	for (i = 0; i < length; i++)
		c[i] = a[i] - b[i];
}

void e3gai_sub(const double *a[4], const double *b[4], double *c[4]) {
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
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
		}
	}
	if (cn = c[2]) {
		bn = b[2];
		if ((an = a[2]) && bn) {
			cn[0] = an[0] - bn[0];
			cn[1] = an[1] - bn[1];
			cn[2] = an[2] - bn[2];
		}
		else if (an) {
			cn[0] = an[0];
			cn[1] = an[1];
			cn[2] = an[2];
		}
		else {
			cn[0] = -bn[0];
			cn[1] = -bn[1];
			cn[2] = -bn[2];
		}
	}
	if (cn = c[3]) {
		bn = b[3];
		if ((an = a[3]) && bn) {
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
