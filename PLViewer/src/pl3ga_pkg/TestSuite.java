/*
Patrick de Kok, bachelor thesis 2012
*/
/*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of the <organization> nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
package pl3ga_pkg;
public class TestSuite  extends  pl3ga
{ 
// Missing dependencies definitions:
/**
 * Generates a random float in [0.0 1.0) interval using the java.util.Random
 */
public final static float random_float_dont_mangle_1_returns_float() {
	return (float)NextRandomDouble();
}
public final static void random_float_dont_mangle_1_returns_float_seed(int seed) {
	s_randomGenerator.setSeed(seed);
}

public final static void random_float_dont_mangle_1_returns_float_timeSeed() {
	random_float_dont_mangle_1_returns_float_seed((int)System.currentTimeMillis());
}



/**
 * Generates a random versor.
 * The scale is uniformly distributed over the interval [0 1).
 * The maximum non-zero grade-part is 'grade'.
 * 
 * Only the basis vectors marked in 'basisVectorBitmap' will be used to generate the versor/blade.
 * Use 'basisVectorBitmap = -1' (the default) to use all basisvectors.
 * @return random_versor_dont_mangle_2_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0)
 */
public static mv random_versor_dont_mangle_2_returns_mv(float scale, int grade, int basisVectorBitmap) {
	float minimumNorm = 0.01f;
	float largestCoordinate = 4.0f;
	return random_versor_dont_mangle_2_returns_mv_ex(scale, grade, basisVectorBitmap, minimumNorm, scale * largestCoordinate);
}

/**
 * This version of random_versor_dont_mangle_2_returns_mv() has extra arguments which help to avoid
 * near-singular blades / versors.
 * 
 * Near-singular blades / versors are avoid by testing the norm and largest coordinate
 * of the random blade / versor. If the test does not pass, the function recursively
 * tries to generate another random blade / versor.
 * 
 * 'minimumNorm' is the minimum allowed norm of the blade/versor before scaling. 
 * 'minimumNorm' must be > 0.0 for versors.
 * 
 * 'largestCoordinate' is the largest coordinate allowed after scaling.
 * 
 * @return random_versor_dont_mangle_2_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0)
 */
public static mv random_versor_dont_mangle_2_returns_mv_ex(float scale, int _grade, int basisVectorBitmap, 
		float minimumNorm, float largestCoordinate) 
{
	mv randomVector = new mv();
	//, tmp1, tmp2;
	float[] randomValues = new float[6];
	//float n2, mul;
	int grade = _grade;
	
	// set IR (intermediate result) to 1
	mv IR = new mv (1.0f);

	while (grade > 0) {	// loop until grade == 0
		// fill array with random values
		for (int i = 0; i < 6; i++) 
			randomValues[i] = ((basisVectorBitmap & (1 << i)) == 0)
				? 0.0f 
				: (-1.0f + 2.0f * random_float_dont_mangle_1_returns_float());
		
		// make it a multivector:
		randomVector.set(GroupBitmap.GRADE_1, randomValues);
		
		// multiply 
		IR = gp(IR, randomVector);
		
		// lower grade
		grade--;
	}
	
	// compute norm/multiplier, apply it, or recurse if we happened to create a near-null versor
	float n2 = norm_returns_scalar(IR);
	if ((float)Math.abs(n2) > minimumNorm * minimumNorm) {
		if (n2 != 0.0f) {
			float mul = scale * random_float_dont_mangle_1_returns_float() / n2;
			if (IR.largestCoordinate() * mul < largestCoordinate)
				return gp_dont_mangle_2(IR, mul);
		}
		else if (IR.largestCoordinate() < largestCoordinate)
			return IR;
	}
	
	// try again:
	return random_versor_dont_mangle_2_returns_mv_ex(scale, _grade, basisVectorBitmap, minimumNorm, largestCoordinate); 
}


/**
 * Generates a random blade.
 * The scale is uniformly distributed over the interval [0 1).
 * The maximum non-zero grade-part is 'grade'.
 * 
 * Only the basis vectors marked in 'basisVectorBitmap' will be used to generate the versor/blade.
 * Use 'basisVectorBitmap = -1' (the default) to use all basisvectors.
 * @return random_blade_dont_mangle_6_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0)
 */
public static mv random_blade_dont_mangle_6_returns_mv(float scale, int grade, int basisVectorBitmap) {
	float minimumNorm = 0.01f;
	float largestCoordinate = 4.0f;
	return random_blade_dont_mangle_6_returns_mv_ex(scale, grade, basisVectorBitmap, minimumNorm, scale * largestCoordinate);
}

/**
 * This version of random_blade_dont_mangle_6_returns_mv() has extra arguments which help to avoid
 * near-singular blades / versors.
 * 
 * Near-singular blades / versors are avoid by testing the norm and largest coordinate
 * of the random blade / versor. If the test does not pass, the function recursively
 * tries to generate another random blade / versor.
 * 
 * 'minimumNorm' is the minimum allowed norm of the blade/versor before scaling. 
 * 'minimumNorm' must be > 0.0 for versors.
 * 
 * 'largestCoordinate' is the largest coordinate allowed after scaling.
 * 
 * @return random_blade_dont_mangle_6_returns_mv_ex(arg1, scale, grade, basisVectorBitmap, 0.01, scale * 4.0)
 */
public static mv random_blade_dont_mangle_6_returns_mv_ex(float scale, int _grade, int basisVectorBitmap, 
		float minimumNorm, float largestCoordinate) 
{
	mv randomVector = new mv();
	//, tmp1, tmp2;
	float[] randomValues = new float[6];
	//float n2, mul;
	int grade = _grade;
	
	// set IR (intermediate result) to 1
	mv IR = new mv (1.0f);

	while (grade > 0) {	// loop until grade == 0
		// fill array with random values
		for (int i = 0; i < 6; i++) 
			randomValues[i] = ((basisVectorBitmap & (1 << i)) == 0)
				? 0.0f 
				: (-1.0f + 2.0f * random_float_dont_mangle_1_returns_float());
		
		// make it a multivector:
		randomVector.set(GroupBitmap.GRADE_1, randomValues);
		
		// multiply 
		IR = op(IR, randomVector);
		
		// lower grade
		grade--;
	}
	
	// compute norm/multiplier, apply it, or recurse if we happened to create a near-null versor
	float n2 = norm_returns_scalar(IR);
	if ((float)Math.abs(n2) > minimumNorm * minimumNorm) {
		if (n2 != 0.0f) {
			float mul = scale * random_float_dont_mangle_1_returns_float() / n2;
			if (IR.largestCoordinate() * mul < largestCoordinate)
				return gp_dont_mangle_2(IR, mul);
		}
		else if (IR.largestCoordinate() < largestCoordinate)
			return IR;
	}
	
	// try again:
	return random_blade_dont_mangle_6_returns_mv_ex(scale, _grade, basisVectorBitmap, minimumNorm, largestCoordinate); 
}
/**
 * Generates a random float in [0.0 1.0) interval using the java.util.Random
 */
public final static float random_float_dont_mangle_79() {
	return (float)NextRandomDouble();
}
public final static void random_float_dont_mangle_79_seed(int seed) {
	s_randomGenerator.setSeed(seed);
}

public final static void random_float_dont_mangle_79_timeSeed() {
	random_float_dont_mangle_79_seed((int)System.currentTimeMillis());
}

/**
 * Returns geometric product of mv and mv.
 */
public final static mv gp_dont_mangle_81_returns_mv(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__0_0_0(ac[0], bc[0], cc[0]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__0_1_1(ac[0], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__0_2_2(ac[0], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__0_3_3(ac[0], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__0_4_4(ac[0], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__0_5_5(ac[0], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__0_6_6(ac[0], bc[6], cc[6]);
		}
	}
	if (ac[1] != null) {
		if (bc[0] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__1_0_1(ac[1], bc[0], cc[1]);
		}
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__1_1_0(ac[1], bc[1], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__1_1_2(ac[1], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__1_2_1(ac[1], bc[2], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__1_2_3(ac[1], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__1_3_2(ac[1], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__1_3_4(ac[1], bc[3], cc[4]);
		}
		if (bc[4] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__1_4_3(ac[1], bc[4], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__1_4_5(ac[1], bc[4], cc[5]);
		}
		if (bc[5] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__1_5_4(ac[1], bc[5], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__1_5_6(ac[1], bc[5], cc[6]);
		}
		if (bc[6] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__1_6_5(ac[1], bc[6], cc[5]);
		}
	}
	if (ac[2] != null) {
		if (bc[0] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__2_0_2(ac[2], bc[0], cc[2]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__2_1_1(ac[2], bc[1], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__2_1_3(ac[2], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__2_2_0(ac[2], bc[2], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__2_2_2(ac[2], bc[2], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__2_2_4(ac[2], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__2_3_1(ac[2], bc[3], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__2_3_3(ac[2], bc[3], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__2_3_5(ac[2], bc[3], cc[5]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__2_4_2(ac[2], bc[4], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__2_4_4(ac[2], bc[4], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__2_4_6(ac[2], bc[4], cc[6]);
		}
		if (bc[5] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__2_5_3(ac[2], bc[5], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__2_5_5(ac[2], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__2_6_4(ac[2], bc[6], cc[4]);
		}
	}
	if (ac[3] != null) {
		if (bc[0] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__3_0_3(ac[3], bc[0], cc[3]);
		}
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__3_1_2(ac[3], bc[1], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__3_1_4(ac[3], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__3_2_1(ac[3], bc[2], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__3_2_3(ac[3], bc[2], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__3_2_5(ac[3], bc[2], cc[5]);
		}
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__3_3_0(ac[3], bc[3], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__3_3_2(ac[3], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__3_3_4(ac[3], bc[3], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__3_3_6(ac[3], bc[3], cc[6]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__3_4_1(ac[3], bc[4], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__3_4_3(ac[3], bc[4], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__3_4_5(ac[3], bc[4], cc[5]);
		}
		if (bc[5] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__3_5_2(ac[3], bc[5], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__3_5_4(ac[3], bc[5], cc[4]);
		}
		if (bc[6] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__3_6_3(ac[3], bc[6], cc[3]);
		}
	}
	if (ac[4] != null) {
		if (bc[0] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__4_0_4(ac[4], bc[0], cc[4]);
		}
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__4_1_3(ac[4], bc[1], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__4_1_5(ac[4], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__4_2_2(ac[4], bc[2], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__4_2_4(ac[4], bc[2], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__4_2_6(ac[4], bc[2], cc[6]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__4_3_1(ac[4], bc[3], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__4_3_3(ac[4], bc[3], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__4_3_5(ac[4], bc[3], cc[5]);
		}
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__4_4_0(ac[4], bc[4], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__4_4_2(ac[4], bc[4], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__4_4_4(ac[4], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__4_5_1(ac[4], bc[5], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__4_5_3(ac[4], bc[5], cc[3]);
		}
		if (bc[6] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__4_6_2(ac[4], bc[6], cc[2]);
		}
	}
	if (ac[5] != null) {
		if (bc[0] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__5_0_5(ac[5], bc[0], cc[5]);
		}
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__5_1_4(ac[5], bc[1], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__5_1_6(ac[5], bc[1], cc[6]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__5_2_3(ac[5], bc[2], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__5_2_5(ac[5], bc[2], cc[5]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__5_3_2(ac[5], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__5_3_4(ac[5], bc[3], cc[4]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__5_4_1(ac[5], bc[4], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__5_4_3(ac[5], bc[4], cc[3]);
		}
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__5_5_0(ac[5], bc[5], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__5_5_2(ac[5], bc[5], cc[2]);
		}
		if (bc[6] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__5_6_1(ac[5], bc[6], cc[1]);
		}
	}
	if (ac[6] != null) {
		if (bc[0] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp__internal_euclidean_metric__6_0_6(ac[6], bc[0], cc[6]);
		}
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp__internal_euclidean_metric__6_1_5(ac[6], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp__internal_euclidean_metric__6_2_4(ac[6], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp__internal_euclidean_metric__6_3_3(ac[6], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp__internal_euclidean_metric__6_4_2(ac[6], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp__internal_euclidean_metric__6_5_1(ac[6], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp__internal_euclidean_metric__6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
// Testing code declarations:
// Testing code inline definitions:
// Testing code definitions:

static int test_metric_default_mv(int NB_TESTS_SCALER) 
{
	int i, j;
	float[] arr = new float[6];
	float dif;
	mv A;
	mv[] bv = new mv[6];
	float[] M = new float[]{
		0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f	}; // metric matrix

	// get all basis vectors

	pl3ga.zero_6(arr);
	arr[0] = 1.0f;
	bv[0] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[1] = 1.0f;
	bv[1] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[2] = 1.0f;
	bv[2] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[3] = 1.0f;
	bv[3] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[4] = 1.0f;
	bv[4] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[5] = 1.0f;
	bv[5] = new mv(GroupBitmap.GROUP_1, arr);

	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			A = gp(bv[i], bv[j]);
			dif = M[i * 6 + j] - A.get_scalar();
			if ((dif < -1E-06f) || (dif > 1E-06f)) {
				Console.WriteLine("test_metric_default_mv() test failed for " + BasisVectorNames[i] + " " + BasisVectorNames[j]);
				return 0;
			}
		}
	}
	
	return 1;
}

static int test_metric__internal_euclidean_metric__mv(int NB_TESTS_SCALER) 
{
	int i, j;
	float[] arr = new float[6];
	float dif;
	mv A;
	mv[] bv = new mv[6];
	float[] M = new float[]{
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f	}; // metric matrix

	// get all basis vectors

	pl3ga.zero_6(arr);
	arr[0] = 1.0f;
	bv[0] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[1] = 1.0f;
	bv[1] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[2] = 1.0f;
	bv[2] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[3] = 1.0f;
	bv[3] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[4] = 1.0f;
	bv[4] = new mv(GroupBitmap.GROUP_1, arr);

	pl3ga.zero_6(arr);
	arr[5] = 1.0f;
	bv[5] = new mv(GroupBitmap.GROUP_1, arr);

	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			A = gp_dont_mangle_81_returns_mv(bv[i], bv[j]);
			dif = M[i * 6 + j] - A.get_scalar();
			if ((dif < -1E-06f) || (dif > 1E-06f)) {
				Console.WriteLine("test_metric__internal_euclidean_metric__mv() test failed for " + BasisVectorNames[i] + " " + BasisVectorNames[j]);
				return 0;
			}
		}
	}
	
	return 1;
}

static int test_parse_mv(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 256;
	mv A, B, C;
	String str;
	
	int i, basisVectorBitmap = -1;

	for (i = 0; i < NB_LOOPS; i++) {
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_79(), (int)(random_float_dont_mangle_79() * 6.5f), basisVectorBitmap);
		
		str = A.toString(
			"%2.20e"
		
		);
		
		try {
			B = parse(str);
		} catch (ParseException ex) {
			Console.WriteLine("parse() test failed: " + ex.toString());
			return 0; // failure
		}

		C = subtract(A, B);

		if (C.largestCoordinate() > 1E-06f) {
			Console.WriteLine("parse() test failed (largest coordinate: " + C.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	
	return 1; // success
}

static int test_add_dont_mangle_89(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C;
	int i, g;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		
		// B = -A
		B = negate(A);
		
		C = add(A, B);
		
		// check
		if (C.largestCoordinate() > 9.9999999999999991E-06f) {
			Console.WriteLine("add() test failed");
			return 0; // failure
		}
		
	}
	return 1; // success
}

static int test_subtract_dont_mangle_84(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C;
	int i, g;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		
		B = A;
		
		C = subtract(A, B);
		
		// check
		if (C.largestCoordinate() > 9.9999999999999991E-06f) {
			Console.WriteLine("subtract() test failed");
			return 0; // failure
		}
		
	}
	return 1; // success
}

static int test_applyOM_dont_mangle_86(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	float[] OMmatrix = new float[6 * 6];
	int i, d, d2;
	int nbRandomVectors;
	om randomOM;
	mv[] randomVectors = new mv[6];
	mv[] OMrandomVectors = new mv[6];
	mv op1, op2, dif;
	int basisVectorBitmap = -1;
	int vectorGrade = 1;

	for (i = 0; i < NB_LOOPS; i++) {
		// init random outermorphism matrix
		for (d2 = 0; d2 < 6 * 6; d2++)
			OMmatrix[d2] = random_float_dont_mangle_1_returns_float();
		
		// init random OM
		randomOM = new om(OMmatrix);
		
		// get n < 6 random vectors stored in GMV
		nbRandomVectors = (int)(6.0f * random_float_dont_mangle_1_returns_float());
		if (nbRandomVectors < 1) nbRandomVectors = 1;
		for (d = 0; d < nbRandomVectors; d++) {
			randomVectors[d] = random_blade_dont_mangle_6_returns_mv(random_float_dont_mangle_1_returns_float(), vectorGrade, basisVectorBitmap);
			OMrandomVectors[d] = applyOM(randomOM, randomVectors[d]);
		}
		
		// compute outer product of randomVectors, OMrandomVectors
		op1 = randomVectors[0];
		op2 = OMrandomVectors[0];
		for (d = 1; d < nbRandomVectors; d++) {
			op1 = op(op1, randomVectors[d]);
			op2 = op(op2, OMrandomVectors[d]);
		}
		
		// apply OM to op1
		op1 = applyOM(randomOM, op1);
		
		// test equality
		dif = subtract(op1, op2);
		if (dif.largestCoordinate() > 1E-06f) {
			Console.WriteLine("applyOM() test failed (largest coordinate = " + dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
		
	return 1; // success
}

static int test_applyVersor_dont_mangle_85(int NB_TESTS_SCALER) {
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	float baseScale = 0.5f;
	int g, i;
	float s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	int versorBasisVectorBitmap = 0; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		V = random_versor_dont_mangle_2_returns_mv(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0f)
			continue;		
		
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		X = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);
		s = baseScale + random_float_dont_mangle_1_returns_float();
		Y = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = new mv(applyVersor(V, X));
		VY = new mv(applyVersor(V, Y));
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyVersor() test failed (metric test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyVersor(IV, VX);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyVersor() test failed (inverse test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_applyUnitVersor_dont_mangle_87(int NB_TESTS_SCALER) {
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	float baseScale = 0.5f;
	int g, i;
	float s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	mv tmp;
	int versorBasisVectorBitmap = 0; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		V = random_versor_dont_mangle_2_returns_mv(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0f)
			continue;		
		
		tmp = unit(V);
		V = tmp;
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		X = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);
		s = baseScale + random_float_dont_mangle_1_returns_float();
		Y = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = new mv(applyUnitVersor(V, X));
		VY = new mv(applyUnitVersor(V, Y));
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyUnitVersor() test failed (metric test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyUnitVersor(IV, VX);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyUnitVersor() test failed (inverse test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_applyVersorWI_dont_mangle_96(int NB_TESTS_SCALER) {
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	float baseScale = 0.5f;
	int g, i;
	float s;
	mv V, IV, X, Y, VX, VY, IVVX, XdY, VXdVY, dif;
	mv tmp;
	int versorBasisVectorBitmap = 0; // note: random versors restricted to Euclidean basis vectors.
	int bladeBasisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor and its inverse. Optionally make versor unit.
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		V = random_versor_dont_mangle_2_returns_mv(s, g, versorBasisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0f)
			continue;		
		
		tmp = unit(V);
		V = tmp;
		IV = versorInverse(V);

		// get two random blades		
		s = baseScale + random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		X = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);
		s = baseScale + random_float_dont_mangle_1_returns_float();
		Y = random_blade_dont_mangle_6_returns_mv(s, g, bladeBasisVectorBitmap);

		// apply versor to blades
		VX = new mv(applyVersorWI(V, X, IV));
		VY = new mv(applyVersorWI(V, Y, IV));
		
		// compute inner product
		XdY = mhip(X, Y);
		VXdVY = mhip(VX, VY);
		
		// see if inner products are equal (versor application should not change metric)
		dif = subtract(XdY, VXdVY);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyVersorWI() test failed (metric test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
		
		// apply inverse transformation to VX
		IVVX = applyVersorWI(IV, VX, V);
		
		// see if X equals IVVX
		dif = subtract(X, IVVX);
		if (dif.largestCoordinate() > (9.9999999999999991E-05f )) {
			Console.WriteLine("applyVersorWI() test failed (inverse test) (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_dual_dont_mangle_88(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_6_returns_mv(random_float_dont_mangle_1_returns_float(), (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		B = dual(A);
		
		C = undual(B);
		
		// check if equal to original:
		dif = subtract(A, C);
		if (dif.largestCoordinate() > 1E-06f) {
			Console.WriteLine("dual() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_undual_dont_mangle_93(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, dif;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_6_returns_mv(random_float_dont_mangle_1_returns_float(), (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		B = undual(A);
		
		C = dual(B);
		
		// check if equal to original:
		dif = subtract(A, C);
		if (dif.largestCoordinate() > 1E-06f) {
			Console.WriteLine("undual() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_equals_dont_mangle_90(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C;
	float s, eps = 0.2f;
	int g, i;
	boolean e, l;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		B = random_versor_dont_mangle_2_returns_mv(1.1f * eps, g, basisVectorBitmap);
		C = add(B, A);
		
		// check if equals thinks A if is equal to itself
		e = equals(A, A, eps);
		if (!e) {
			Console.WriteLine("equals() failed (variable not equal to itself)\n");
			return 0; // failure
		}
		
		// check if equals thinks A if is equal C
		e = equals(A, C, eps);
		
		// use mv_largestCoordinate() to verify
		l = !(B.largestCoordinate() > eps);
		
		if (e != l) {
			Console.WriteLine("equals() test failed");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_extractGrade_dont_mangle_92(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, G0, G1, G2, G3, G4, G5, G6;
	int i;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float(), (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		// split it up into groups/grades:
		G0 = extractGrade(A, GroupBitmap.GROUP_0);
		G1 = extractGrade(A, GroupBitmap.GROUP_1);
		G2 = extractGrade(A, GroupBitmap.GROUP_2);
		G3 = extractGrade(A, GroupBitmap.GROUP_3);
		G4 = extractGrade(A, GroupBitmap.GROUP_4);
		G5 = extractGrade(A, GroupBitmap.GROUP_5);
		G6 = extractGrade(A, GroupBitmap.GROUP_6);
		// sum all into 'B'
		B = new mv();
		B = add(B, G0);
		B = add(B, G1);
		B = add(B, G2);
		B = add(B, G3);
		B = add(B, G4);
		B = add(B, G5);
		B = add(B, G6);

		// check if equal to original:
		C = subtract(A, B);
		if (C.largestCoordinate() > 1E-06f) {
			Console.WriteLine("extractGrade() test failed (largestCoordinate = " + (double)C.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_gp_dont_mangle_106(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 256;
	mv A, B, C, D, E, V1, V2;
	int i;
	int o;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		o = (random_float_dont_mangle_1_returns_float() < 0.5f) ? 0 : 1; // even or odd?
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float(), ((int)(random_float_dont_mangle_1_returns_float() * 6.5f) & 0xFFFE) + o, basisVectorBitmap);
		B = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float(), ((int)(random_float_dont_mangle_1_returns_float() * 6.5f) & 0xFFFE) + o, basisVectorBitmap);
		C = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float(), ((int)(random_float_dont_mangle_1_returns_float() * 6.5f) & 0xFFFE) + o, basisVectorBitmap);
		
		{ // test (A+B) C = A C + B C
			// D = A + B
			D = add(A, B);
			// V1 = D C
			V1 = gp(D, C);
			// D = A C
			D = gp(A, C);
			// E = B C
			E = gp(B, C);
			// V2 = D + E
			V2 = add(D, E);
			// test equality
			D = subtract(V1, V2);
			// use mv_largestCoordinate() to verify
			if (D.largestCoordinate() > 0.001f) {
				Console.WriteLine("gp() test failed on '(A+B) C = A C + B C' (dif=" + D.largestCoordinate() + ")");
				return 0; // failure
			}
		}
		
		{ // test A (B+C) = A B + A C
			// D = B + C
			D = add(B, C);
			// V1 = A D
			V1 = gp(A, D);
			// D = A B
			D = gp(A, B);
			// E = A C
			E = gp(A, C);
			// V2 = D + E
			V2 = add(D, E);
			// test equality
			D = subtract(V1, V2);
			// use largestCoordinate() to verify
			if (D.largestCoordinate() > 9.9999999999999991E-05f) {
				Console.WriteLine("gp() test failed on 'A (B+C) = A B + A C' (dif=" + D.largestCoordinate() + ")");
				return 0; // failure
			}
		}
		
		{ // test A (B C) = (A B) C
			// D = B C
			D = gp(B, C);
			// V1 = A D
			V1 = gp(A, D);
			// D = A B
			D = gp(A, B);
			// V2 = D C
			V2 = gp(D, C);
			// test equality
			D = subtract(V1, V2);
			// use largestCoordinate() to verify
			if (D.largestCoordinate() > 9.9999999999999991E-05f) {
				Console.WriteLine("gp() test failed on 'A (B C) = (A B) C' (dif=" + D.largestCoordinate() + ")");
				return 0; // failure
			}
		}		
	}
	return 1; // success
}

static int test_hp_dont_mangle_91(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, dif;
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		
		// copy it to another versor
		B = new mv(A);
		
		// set coordinates of B to random values (which may not be zero)
		for (g = 0; g < 7; g++) {
			if (B.m_c[g] == null) continue;
			for (int e = 0; e < B.m_c[g].length; e++) {
				B.m_c[g][e] = 0.5f + random_float_dont_mangle_1_returns_float();
			}
		}
		
		// do hadamard product
		C = hp(A, B);
		
		// invert coordinates of B manually
		for (g = 0; g < 7; g++) {
			if (B.m_c[g] == null) continue;
			for (int e = 0; e < B.m_c[g].length; e++) {
				B.m_c[g][e] = 1.0f / B.m_c[g][e];
			}
		}

		// do inverse hadamard product
		D = hp(C, B);
		
		// check if equal to original:
		dif = subtract(A, D);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("hp() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_ihp_dont_mangle_94(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, dif;
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		
		// copy it to another versor
		B = new mv(A);
		
		// set coordinates of B to random values (which may not be zero)
		for (g = 0; g < 7; g++) {
			if (B.m_c[g] == null) continue;
			for (int e = 0; e < B.m_c[g].length; e++) {
				B.m_c[g][e] = 0.5f + random_float_dont_mangle_1_returns_float();
			}
		}
		
		// do hadamard product
		C = ihp(A, B);
		
		// invert coordinates of B manually
		for (g = 0; g < 7; g++) {
			if (B.m_c[g] == null) continue;
			for (int e = 0; e < B.m_c[g].length; e++) {
				B.m_c[g][e] = 1.0f / B.m_c[g][e];
			}
		}

		// do inverse hadamard product
		D = ihp(C, B);
		
		// check if equal to original:
		dif = subtract(A, D);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("ihp() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_igp_dont_mangle_100(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, IB, C, D, E;
	int i;
	int basisVectorBitmap = -1;

	for (i = 0; i < NB_LOOPS; i++) {
		// get two random versors
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float() + 0.5f, (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		B = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float() + 0.5f, (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		C = igp(A, B);
		
		// get versor inverse of B, compute A * versorInverse(B)
		IB = versorInverse(B);
		D = gp(A, IB);
		
		E = subtract(C, D);
		
		if (E.largestCoordinate() > 0.001f) {
			Console.WriteLine("igp() test failed (largestCoordinate of E = " + E.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_increment_dont_mangle_95(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, one;
	int i, g;
	int basisVectorBitmap = -1;

	one = new mv(1.0f);

	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float() + 0.5f, g, basisVectorBitmap);
		
		// increment/decrement
		B = increment(A);
		
		// undo the increment/decrement
		C = subtract(B, one);
		
		// see if (A - (B-1)) == 0
		D = subtract(A, C);
		
		if (D.largestCoordinate() > 1E-06f) {
			Console.WriteLine("increment() test failed (largestCoordinate of D = " + (double)D.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_decrement_dont_mangle_102(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, one;
	int i, g;
	int basisVectorBitmap = -1;

	one = new mv(-1.0f);

	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float() + 0.5f, g, basisVectorBitmap);
		
		// increment/decrement
		B = decrement(A);
		
		// undo the increment/decrement
		C = subtract(B, one);
		
		// see if (A - (B-1)) == 0
		D = subtract(A, C);
		
		if (D.largestCoordinate() > 1E-06f) {
			Console.WriteLine("decrement() test failed (largestCoordinate of D = " + (double)D.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_hip_dont_mangle_97(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using hip()
		C = new mv(hip(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if ((ga == 0) || (gb == 0)) E = new mv(0.0f);
		else E = extractGrade(D, Grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("hip() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_mhip_dont_mangle_101(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using mhip()
		C = new mv(mhip(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D, Grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("mhip() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_lc_dont_mangle_107(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using lc()
		C = new mv(lc(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if (ga > gb) E = new mv(0.0f);
		else E = extractGrade(D, Grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("lc() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_rc_dont_mangle_105(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using rc()
		C = new mv(rc(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		if (ga < gb) E = new mv(0.0f);
		else E = extractGrade(D, Grades[gd]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("rc() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_sp_dont_mangle_98(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using sp()
		C = new mv(sp(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D, Grades[0]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("sp() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_norm_dont_mangle_103(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, reverseA, tmp;
	
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	float n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);
		
		// compute norm
		n1 = norm(A);
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n2 = tmp.get_scalar();
		n2 = (float)Math.sqrt(Math.abs(n2));
		
		// check if equal to original:
		if (Math.abs(n1 - n2) > 1E-06f) {
			Console.WriteLine("norm() test failed (difference = " + (double)Math.abs(n1 - n2) + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_norm2_dont_mangle_104(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, reverseA, tmp;
	
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	float n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);
		
		// compute norm
		n1 = norm2(A);
		
		// compute norm manually (A . reverse(A))
		reverseA = reverse(A);
		tmp = gp(A, reverseA);
		n2 = tmp.get_scalar();
		
		// check if equal to original:
		if (Math.abs(n1 - n2) > 1E-06f) {
			Console.WriteLine("norm2() test failed (difference = " + (double)Math.abs(n1 - n2) + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_op_dont_mangle_99_1(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, C, D, E, dif;
	int i, ga, gb, gd;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		s = random_float_dont_mangle_1_returns_float();
		gb = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		B = random_blade_dont_mangle_6_returns_mv(s, gb, basisVectorBitmap);
		
		// compute product using op()
		C = new mv(op(A, B));
		
		// simulate product using geometric product & grade part selection
		D = gp(A, B);
		gd = (ga > gb) ? ga - gb : gb - ga;
		E = extractGrade(D,  Grades[ga + gb]);

		// check if equal:
		dif = subtract(C, E);
		if (dif.largestCoordinate() > 9.9999999999999991E-05f) {
			Console.WriteLine("op() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_op_dont_mangle_99_2(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B;
	int i, ga;
	float s;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		ga = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		if (ga == 0) continue; // do not perform this test for grade 0
		A = random_blade_dont_mangle_6_returns_mv(s, ga, basisVectorBitmap);
		
		// compute A ^ A (should be zero)
		B = op(A, A);
		
		// check if B is zero:
		if (B.largestCoordinate() > 9.9999999999999991E-06f) {
			Console.WriteLine("op() test failed (largestCoordinate = " + (double)B.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_exp_dont_mangle_108(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, expA, sinhA, coshA, S, dif, tmp1; //, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0f * random_float_dont_mangle_1_returns_float();
		g = 2;
		A = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);
		
		if (random_float_dont_mangle_1_returns_float() > 0.5f) { // make sure that 'A' is not always a blade
			s = random_float_dont_mangle_1_returns_float();
			tmp1 = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0.0316227766016838f) { // sinh, cosh precision is very low
			Console.WriteLine("exp() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_sinh_dont_mangle_112(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, expA, sinhA, coshA, S, dif, tmp1; //, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0f * random_float_dont_mangle_1_returns_float();
		g = 2;
		A = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);
		
		if (random_float_dont_mangle_1_returns_float() > 0.5f) { // make sure that 'A' is not always a blade
			s = random_float_dont_mangle_1_returns_float();
			tmp1 = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0.0316227766016838f) { // sinh, cosh precision is very low
			Console.WriteLine("sinh() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_cosh_dont_mangle_115(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, expA, sinhA, coshA, S, dif, tmp1; //, tmp2;
	int i, g;
	int basisVectorBitmap = -1;
	float s;
	int order = 12;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade of grade 2
		s = 2.0f * random_float_dont_mangle_1_returns_float();
		g = 2;
		A = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);
		
		if (random_float_dont_mangle_1_returns_float() > 0.5f) { // make sure that 'A' is not always a blade
			s = random_float_dont_mangle_1_returns_float();
			tmp1 = random_blade_dont_mangle_6_returns_mv(s, g, basisVectorBitmap);	
			A = add(A, tmp1);
			//A = tmp2;
		}

		// apply sinh, cosh, exp functions
		expA = exp(A, order);
		sinhA = sinh(A, order);
		coshA = cosh(A, order);
		
		// sum sinh and cosh
		S = add(coshA, sinhA);
		
		// test that sinh+cosh == exp
		dif = subtract(expA, S);
		if (dif.largestCoordinate() > 0.0316227766016838f) { // sinh, cosh precision is very low
			Console.WriteLine("cosh() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_negate_dont_mangle_117(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	float s, dif;
	int[] signTable = new int[]{-1, -1, -1, -1, -1, -1, -1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = negate(A);
		
		// check grade
		for (n = 0; n <= 6; n++) {
			GA = extractGrade(A, Grades[n]);
			GB = extractGrade(B, Grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				Console.WriteLine("negate() test failed (grade usage does not match)");
				return 0; // failure
			}
			
			// check each coordinate of each groups which is still present after the grade selection
			for (int m = 0; m < 7; m++) {
				if (GA.m_c[m] != null) {
					for (c = 0; c < GA.m_c[m].length; c++) {
						dif = (float)Math.abs(GA.m_c[m][c] * (float)signTable[n] - GB.m_c[m][c]);
						if (dif > 1E-06f) {
							Console.WriteLine("negate() test failed (dif = " + dif + ")");
							return 0; // failure
						}
					}
				}
			}
		}
		
	}
	return 1; // success
}

static int test_reverse_dont_mangle_110(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	float s, dif;
	int[] signTable = new int[]{1, 1, -1, -1, 1, 1, -1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = reverse(A);
		
		// check grade
		for (n = 0; n <= 6; n++) {
			GA = extractGrade(A, Grades[n]);
			GB = extractGrade(B, Grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				Console.WriteLine("reverse() test failed (grade usage does not match)");
				return 0; // failure
			}
			
			// check each coordinate of each groups which is still present after the grade selection
			for (int m = 0; m < 7; m++) {
				if (GA.m_c[m] != null) {
					for (c = 0; c < GA.m_c[m].length; c++) {
						dif = (float)Math.abs(GA.m_c[m][c] * (float)signTable[n] - GB.m_c[m][c]);
						if (dif > 1E-06f) {
							Console.WriteLine("reverse() test failed (dif = " + dif + ")");
							return 0; // failure
						}
					}
				}
			}
		}
		
	}
	return 1; // success
}

static int test_cliffordConjugate_dont_mangle_118(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	float s, dif;
	int[] signTable = new int[]{1, -1, -1, 1, 1, -1, -1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = cliffordConjugate(A);
		
		// check grade
		for (n = 0; n <= 6; n++) {
			GA = extractGrade(A, Grades[n]);
			GB = extractGrade(B, Grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				Console.WriteLine("cliffordConjugate() test failed (grade usage does not match)");
				return 0; // failure
			}
			
			// check each coordinate of each groups which is still present after the grade selection
			for (int m = 0; m < 7; m++) {
				if (GA.m_c[m] != null) {
					for (c = 0; c < GA.m_c[m].length; c++) {
						dif = (float)Math.abs(GA.m_c[m][c] * (float)signTable[n] - GB.m_c[m][c]);
						if (dif > 1E-06f) {
							Console.WriteLine("cliffordConjugate() test failed (dif = " + dif + ")");
							return 0; // failure
						}
					}
				}
			}
		}
		
	}
	return 1; // success
}

static int test_gradeInvolution_dont_mangle_113(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, B, GA, GB;
	int i, c, n, g;
	int basisVectorBitmap = -1;
	float s, dif;
	int[] signTable = new int[]{1, -1, 1, -1, 1, -1, 1};
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);

		// apply function
		B = gradeInvolution(A);
		
		// check grade
		for (n = 0; n <= 6; n++) {
			GA = extractGrade(A, Grades[n]);
			GB = extractGrade(B, Grades[n]);
			
			// check if grade usage matches
			if (GA.gu() != GB.gu()) {
				Console.WriteLine("gradeInvolution() test failed (grade usage does not match)");
				return 0; // failure
			}
			
			// check each coordinate of each groups which is still present after the grade selection
			for (int m = 0; m < 7; m++) {
				if (GA.m_c[m] != null) {
					for (c = 0; c < GA.m_c[m].length; c++) {
						dif = (float)Math.abs(GA.m_c[m][c] * (float)signTable[n] - GB.m_c[m][c]);
						if (dif > 1E-06f) {
							Console.WriteLine("gradeInvolution() test failed (dif = " + dif + ")");
							return 0; // failure
						}
					}
				}
			}
		}
		
	}
	return 1; // success
}

static int test_unit_dont_mangle_114(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A, UA, RUA;
	int i;
	int basisVectorBitmap = -1;
	float n;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_6_returns_mv(random_float_dont_mangle_1_returns_float(), (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		UA = unit(A);
		RUA = reverse(UA);
		n = sp(RUA, UA);
		
		if ((float)(Math.abs(n) - 1.0f) > 9.9999999999999991E-05f) {
			Console.WriteLine("unit() test failed (|norm|-1 = " + (double)(Math.abs((double)n) - 1.0) + ")");
			return 0; // failure
		}

	}
	return 1; // success
}

static int test_versorInverse_dont_mangle_116(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv V, VI, VVI, VIV, X, Y;
	int i;
	int basisVectorBitmap = -1;
	float n1, n2;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random versor
		V = random_versor_dont_mangle_2_returns_mv(random_float_dont_mangle_1_returns_float() + 0.5f, (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		// avoid 'near'-singular versors
		if (V.largestCoordinate() > 2.0f)
			continue;
		
		// compute inverse
		VI = versorInverse(V);
		
		// compute (inverse(V) V) and (V inverse(V))
		VIV = gp(VI, V);
		VVI = gp(V, VI);
		
		// check that scalar parts are 1
		n1 = VIV.get_scalar();
		n2 = VVI.get_scalar();
		
		if (Math.abs(n1 - 1.0f) > 0.001f) {
			Console.WriteLine("versorInverse() test failed |VI . V - 1|= " + (double)Math.abs(n1 - 1.0f) + ")");
			return 0; // failure
		}
		
		if (Math.abs(n2 - 1.0f) > 0.001f) {
			Console.WriteLine("versorInverse() test failed ( |V . VI - 1| = " + (double)Math.abs(n2 - 1.0f) + ")");
			return 0; // failure
		}
		
		// check that other grade parts are zero:
		X = extractGrade(VIV, GroupBitmap.ALL_GROUPS ^ GroupBitmap.GROUP_0);
		Y = extractGrade(VVI, GroupBitmap.ALL_GROUPS ^ GroupBitmap.GROUP_0);
		
		if (X.largestCoordinate() > 0.001f) {
			Console.WriteLine("versorInverse() test failed (largestCoordinate of VIV = " + (double)X.largestCoordinate() + ")");
			return 0; // failure
		}
		
		if (Y.largestCoordinate() > 0.001f) {
			Console.WriteLine("versorInverse() test failed (largestCoordinate of VVI = " + (double)Y.largestCoordinate() + ")");
			return 0; // failure
		}
		
	}
	return 1; // success
}

static int test_zero_dont_mangle_119(int NB_TESTS_SCALER) 
{
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	mv A;
	float s, eps = 0.2f;
	int g, i;
	boolean z, l, c;
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		s = random_float_dont_mangle_1_returns_float();
		g = (int)(random_float_dont_mangle_1_returns_float() * 6.5f);
		A = random_versor_dont_mangle_2_returns_mv(s, g, basisVectorBitmap);
		
		// ask if zero thinks A is zero
		z = zero(A, eps);
		
		// check it yourself
		c = true; // assume it is zero
		for (g = 0; g < 7; g++) {
			if (A.m_c[g] != null) {
				for (int e = 0; e < A.m_c[g].length; e++) {
					if (Math.abs(A.m_c[g][e]) > eps) c = false;
				}
			}
		}
		
		// also use mv_largestCoordinate() to verify
		l = !(A.largestCoordinate() > eps);
		
		if ((c != z) || (l != z)) {
			Console.WriteLine("zero() test failed\n");
			return 0; // failure
		}
	}
	return 1; // success
}

static int test_div_dont_mangle_1_dont_mangle_121(int NB_TESTS_SCALER) {
	int NB_LOOPS = 100 + NB_TESTS_SCALER / 64;
	int i;
	mv A, B, C, dif;
	float divider;
	
	int basisVectorBitmap = -1;
	
	for (i = 0; i < NB_LOOPS; i++) {
		// get random blade
		A = random_blade_dont_mangle_6_returns_mv(random_float_dont_mangle_1_returns_float(), (int)(random_float_dont_mangle_1_returns_float() * 6.5f), basisVectorBitmap);
		
		divider = 0.01f + random_float_dont_mangle_1_returns_float();
		
		B = div_dont_mangle_1(A, divider);
		
		C = gp_dont_mangle_2(B, divider);
		
		// see if C equals A
		dif = subtract(C, A);
		if (dif.largestCoordinate() > (1E-06f )) {
			Console.WriteLine("div_dont_mangle_1() test failed (largestCoordinate = " + (double)dif.largestCoordinate() + ")");
			return 0; // failure
		}
	}

	return 1; // success
}

	static class ConsoleInternal {
		public ConsoleInternal() {}
		public void WriteLine(String line) {
			System.out.println(line);
		}
	}
	
	static ConsoleInternal Console = new ConsoleInternal();

public static void main(String[] args)
{
	int retVal = 0;
	// The number of tests will be proportional to this value.
	// This should become a command-line option
	int NB_TESTS_SCALER = 16384;
	
	// seed random number generators with current time
	random_float_dont_mangle_79_timeSeed();

	// run all test functions
	if (test_metric_default_mv(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_metric__internal_euclidean_metric__mv(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_parse_mv(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_add_dont_mangle_89(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_subtract_dont_mangle_84(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_applyOM_dont_mangle_86(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_applyVersor_dont_mangle_85(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_applyUnitVersor_dont_mangle_87(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_applyVersorWI_dont_mangle_96(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_dual_dont_mangle_88(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_undual_dont_mangle_93(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_equals_dont_mangle_90(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_extractGrade_dont_mangle_92(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_gp_dont_mangle_106(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_hp_dont_mangle_91(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_ihp_dont_mangle_94(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_igp_dont_mangle_100(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_increment_dont_mangle_95(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_decrement_dont_mangle_102(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_hip_dont_mangle_97(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_mhip_dont_mangle_101(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_lc_dont_mangle_107(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_rc_dont_mangle_105(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_sp_dont_mangle_98(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_norm_dont_mangle_103(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_norm2_dont_mangle_104(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_op_dont_mangle_99_1(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_op_dont_mangle_99_2(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_exp_dont_mangle_108(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_sinh_dont_mangle_112(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_cosh_dont_mangle_115(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_negate_dont_mangle_117(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_reverse_dont_mangle_110(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_cliffordConjugate_dont_mangle_118(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_gradeInvolution_dont_mangle_113(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_unit_dont_mangle_114(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_versorInverse_dont_mangle_116(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_zero_dont_mangle_119(NB_TESTS_SCALER) == 0) retVal = -1;
	if (test_div_dont_mangle_1_dont_mangle_121(NB_TESTS_SCALER) == 0) retVal = -1;

	if (retVal != 0) Console.WriteLine("Test failed.\n");
	else Console.WriteLine("Done.\n");	

	System.exit(retVal);
}
} // end of class TestSuite
