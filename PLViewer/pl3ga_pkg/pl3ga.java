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
public class pl3ga 
{ 

	static protected final String[] typenames = 
		new String[] {
			"mv",
			"float",
			"e01_t",
			"e02_t",
			"e03_t",
			"e12_t",
			"e23_t",
			"e31_t",
			"I3r_t",
			"I3i_t",
			"I6_t",
			"line",
			"idealLine",
			"pencil",
			"idealPencil",
			"mixedPencil",
			"pseudoscalar",
			"evenVersor",
			"oddVersor"
		};
	public static final e01_t e01 = new e01_t();
	public static final e02_t e02 = new e02_t();
	public static final e03_t e03 = new e03_t();
	public static final e12_t e12 = new e12_t();
	public static final e23_t e23 = new e23_t();
	public static final e31_t e31 = new e31_t();
	public static final I3r_t I3r = new I3r_t();
	public static final I3i_t I3i = new I3i_t();
	public static final I6_t I6 = new I6_t();
	public static final line lineE01 = new line(line.coord_e01_e02_e03, 1.0f, 0.0f, 0.0f);
	public static final line lineE02 = new line(line.coord_e01_e02_e03, 0.0f, 1.0f, 0.0f);
	public static final line lineE03 = new line(line.coord_e01_e02_e03, 0.0f, 0.0f, 1.0f);
	public static final idealLine lineE12 = new idealLine(idealLine.coord_e12_e23_e31, 1.0f, 0.0f, 0.0f);
	public static final idealLine lineE23 = new idealLine(idealLine.coord_e12_e23_e31, 0.0f, 1.0f, 0.0f);
	public static final idealLine lineE31 = new idealLine(idealLine.coord_e12_e23_e31, 0.0f, 0.0f, 1.0f);


	/**
	 * The dimension of the space
	 */
	public static final int SpaceDim = 6;
	/**
	 * Number of groups/grades of coordinates in a multivector
	 */
	public static final int NbGroups = 7;
	/**
	 * Is the metric of the space Euclidean? (false or true)
	 */
	public static final boolean MetricEuclidean = false;
	/**
	 * Names of the basis vectors.
	 */
	public static final String[] BasisVectorNames = new String[] {
		"e01", "e02", "e03", "e12", "e23", "e31"
	};
	/**
	 * The constants for the grades, in an array.
	 */
	public static final int[] Grades = {GroupBitmap.GRADE_0, GroupBitmap.GRADE_1, GroupBitmap.GRADE_2, GroupBitmap.GRADE_3, GroupBitmap.GRADE_4, GroupBitmap.GRADE_5, GroupBitmap.GRADE_6, 0, 0, 0, 0, 0, 0, 0};
	/**
	 * The constants for the groups, in an array.
	 */
	public static final int[] Groups = {GroupBitmap.GROUP_0, GroupBitmap.GROUP_1, GroupBitmap.GROUP_2, GroupBitmap.GROUP_3, GroupBitmap.GROUP_4, GroupBitmap.GROUP_5, GroupBitmap.GROUP_6};
	/**
	 * This array can be used to lookup the number of coordinates for a group part of a general multivector.
	 */
	public static final int[] GroupSize = { 1, 6, 15, 20, 15, 6, 1 };
	/**
	 * This array can be used to lookup the number of coordinates based on a group usage bitmap.
	 */
	public static final int[] MvSize = new int[] {
		0, 1, 6, 7, 15, 16, 21, 22, 20, 21, 26, 27, 35, 36, 41, 42, 15, 16, 21, 22, 
		30, 31, 36, 37, 35, 36, 41, 42, 50, 51, 56, 57, 6, 7, 12, 13, 21, 22, 27, 28, 
		26, 27, 32, 33, 41, 42, 47, 48, 21, 22, 27, 28, 36, 37, 42, 43, 41, 42, 47, 48, 
		56, 57, 62, 63, 1, 2, 7, 8, 16, 17, 22, 23, 21, 22, 27, 28, 36, 37, 42, 43, 
		16, 17, 22, 23, 31, 32, 37, 38, 36, 37, 42, 43, 51, 52, 57, 58, 7, 8, 13, 14, 
		22, 23, 28, 29, 27, 28, 33, 34, 42, 43, 48, 49, 22, 23, 28, 29, 37, 38, 43, 44, 
		42, 43, 48, 49, 57, 58, 63, 64	};
	/**
	 * This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector.
	 * Use it to answer 'what is the permutation of the coordinate at index [x]'?
	 */
	public static final double[] BasisElementSignByIndex = new double[]
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	/**
	 * This array of integers contains the 'sign' (even/odd permutation of canonical order) of basis elements in the general multivector.
	 * Use it to answer 'what is the permutation of the coordinate of bitmap [x]'?
	 */
	public static final double[] BasisElementSignByBitmap = new double[]
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	/**
	 * This array of integers contains the order of basis elements in the general multivector.
	 * Use it to answer: 'at what index do I find basis element [x] (x = basis vector bitmap)?'
	 */
	public static final int[] BasisElementIndexByBitmap = new int[]
		{0, 1, 2, 7, 3, 8, 9, 22, 4, 10, 11, 23, 12, 24, 25, 42, 5, 13, 14, 26, 15, 27, 28, 43, 16, 29, 30, 44, 31, 45, 46, 57, 6, 17, 18, 32, 19, 33, 34, 47, 20, 35, 36, 48, 37, 49, 50, 58, 21, 38, 39, 51, 40, 52, 53, 59, 41, 54, 55, 60, 56, 61, 62, 63};
	/**
	 * This array of integers contains the indices of basis elements in the general multivector.
	 * Use it to answer: 'what basis element do I find at index [x]'?
	 */
	public static final int[] BasisElementBitmapByIndex = new int[]
		{0, 1, 2, 4, 8, 16, 32, 3, 5, 6, 9, 10, 12, 17, 18, 20, 24, 33, 34, 36, 40, 48, 7, 11, 13, 14, 19, 21, 22, 25, 26, 28, 35, 37, 38, 41, 42, 44, 49, 50, 52, 56, 15, 23, 27, 29, 30, 39, 43, 45, 46, 51, 53, 54, 57, 58, 60, 31, 47, 55, 59, 61, 62, 63};
	/**
	 * This array of grade of each basis elements in the general multivector.
	 * Use it to answer: 'what is the grade of basis element bitmap [x]'?
	 */
	public static final int[] BasisElementGradeByBitmap = new int[]
		{0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6};
	/**
	 * This array of group of each basis elements in the general multivector.
	 * Use it to answer: 'what is the group of basis element bitmap [x]'?
	 */
	public static final int[] BasisElementGroupByBitmap = new int[]
		{0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6};
	/**
	 * This array of integers contains the order of basis elements in the general multivector.
	 * Use it to answer: 'what basis vectors are in the basis element at position [x]?
	 */
	public static final int[][] BasisElements = new int[][] {
		new int[] {-1},
		new int[] {0, -1},
		new int[] {1, -1},
		new int[] {2, -1},
		new int[] {3, -1},
		new int[] {4, -1},
		new int[] {5, -1},
		new int[] {0, 1, -1},
		new int[] {0, 2, -1},
		new int[] {1, 2, -1},
		new int[] {0, 3, -1},
		new int[] {1, 3, -1},
		new int[] {2, 3, -1},
		new int[] {0, 4, -1},
		new int[] {1, 4, -1},
		new int[] {2, 4, -1},
		new int[] {3, 4, -1},
		new int[] {0, 5, -1},
		new int[] {1, 5, -1},
		new int[] {2, 5, -1},
		new int[] {3, 5, -1},
		new int[] {4, 5, -1},
		new int[] {0, 1, 2, -1},
		new int[] {0, 1, 3, -1},
		new int[] {0, 2, 3, -1},
		new int[] {1, 2, 3, -1},
		new int[] {0, 1, 4, -1},
		new int[] {0, 2, 4, -1},
		new int[] {1, 2, 4, -1},
		new int[] {0, 3, 4, -1},
		new int[] {1, 3, 4, -1},
		new int[] {2, 3, 4, -1},
		new int[] {0, 1, 5, -1},
		new int[] {0, 2, 5, -1},
		new int[] {1, 2, 5, -1},
		new int[] {0, 3, 5, -1},
		new int[] {1, 3, 5, -1},
		new int[] {2, 3, 5, -1},
		new int[] {0, 4, 5, -1},
		new int[] {1, 4, 5, -1},
		new int[] {2, 4, 5, -1},
		new int[] {3, 4, 5, -1},
		new int[] {0, 1, 2, 3, -1},
		new int[] {0, 1, 2, 4, -1},
		new int[] {0, 1, 3, 4, -1},
		new int[] {0, 2, 3, 4, -1},
		new int[] {1, 2, 3, 4, -1},
		new int[] {0, 1, 2, 5, -1},
		new int[] {0, 1, 3, 5, -1},
		new int[] {0, 2, 3, 5, -1},
		new int[] {1, 2, 3, 5, -1},
		new int[] {0, 1, 4, 5, -1},
		new int[] {0, 2, 4, 5, -1},
		new int[] {1, 2, 4, 5, -1},
		new int[] {0, 3, 4, 5, -1},
		new int[] {1, 3, 4, 5, -1},
		new int[] {2, 3, 4, 5, -1},
		new int[] {0, 1, 2, 3, 4, -1},
		new int[] {0, 1, 2, 3, 5, -1},
		new int[] {0, 1, 2, 4, 5, -1},
		new int[] {0, 1, 3, 4, 5, -1},
		new int[] {0, 2, 3, 4, 5, -1},
		new int[] {1, 2, 3, 4, 5, -1},
		new int[] {0, 1, 2, 3, 4, 5, -1}
	};

    // I found sources on the internet which claim that java.util.Random is thread safe.
    // If it turns out not to be thread-safe, port the C# RNG code to Java.
    protected static final java.util.Random s_randomGenerator = new java.util.Random();
    
    protected static final double NextRandomDouble() {
		return s_randomGenerator.nextDouble();
    }

	/** Sets 1 floats to zero. */
	protected final static void zero_1(final float[] dst) {
		dst[0]=0.0f;
	}
	/** Copies 1 floats from 'src' to 'dst.' */
	protected final static void copy_1(final float[] dst, final float[] src) {
			dst[0] = src[0];
	}
	/** Sets 2 floats to zero. */
	protected final static void zero_2(final float[] dst) {
		dst[0]=dst[1]=0.0f;
	}
	/** Copies 2 floats from 'src' to 'dst.' */
	protected final static void copy_2(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
	}
	/** Sets 3 floats to zero. */
	protected final static void zero_3(final float[] dst) {
		dst[0]=dst[1]=dst[2]=0.0f;
	}
	/** Copies 3 floats from 'src' to 'dst.' */
	protected final static void copy_3(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
	}
	/** Sets 4 floats to zero. */
	protected final static void zero_4(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=0.0f;
	}
	/** Copies 4 floats from 'src' to 'dst.' */
	protected final static void copy_4(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
	}
	/** Sets 5 floats to zero. */
	protected final static void zero_5(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=0.0f;
	}
	/** Copies 5 floats from 'src' to 'dst.' */
	protected final static void copy_5(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
	}
	/** Sets 6 floats to zero. */
	protected final static void zero_6(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=0.0f;
	}
	/** Copies 6 floats from 'src' to 'dst.' */
	protected final static void copy_6(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
	}
	/** Sets 7 floats to zero. */
	protected final static void zero_7(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=0.0f;
	}
	/** Copies 7 floats from 'src' to 'dst.' */
	protected final static void copy_7(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
	}
	/** Sets 8 floats to zero. */
	protected final static void zero_8(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=0.0f;
	}
	/** Copies 8 floats from 'src' to 'dst.' */
	protected final static void copy_8(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
	}
	/** Sets 9 floats to zero. */
	protected final static void zero_9(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=0.0f;
	}
	/** Copies 9 floats from 'src' to 'dst.' */
	protected final static void copy_9(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
	}
	/** Sets 10 floats to zero. */
	protected final static void zero_10(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=0.0f;
	}
	/** Copies 10 floats from 'src' to 'dst.' */
	protected final static void copy_10(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
	}
	/** Sets 11 floats to zero. */
	protected final static void zero_11(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=0.0f;
	}
	/** Copies 11 floats from 'src' to 'dst.' */
	protected final static void copy_11(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
	}
	/** Sets 12 floats to zero. */
	protected final static void zero_12(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=dst[11]=0.0f;
	}
	/** Copies 12 floats from 'src' to 'dst.' */
	protected final static void copy_12(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
			dst[11] = src[11];
	}
	/** Sets 13 floats to zero. */
	protected final static void zero_13(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=dst[11]=dst[12]=0.0f;
	}
	/** Copies 13 floats from 'src' to 'dst.' */
	protected final static void copy_13(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
			dst[11] = src[11];
			dst[12] = src[12];
	}
	/** Sets 14 floats to zero. */
	protected final static void zero_14(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=dst[11]=dst[12]=dst[13]=0.0f;
	}
	/** Copies 14 floats from 'src' to 'dst.' */
	protected final static void copy_14(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
			dst[11] = src[11];
			dst[12] = src[12];
			dst[13] = src[13];
	}
	/** Sets 15 floats to zero. */
	protected final static void zero_15(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=dst[11]=dst[12]=dst[13]=dst[14]=0.0f;
	}
	/** Copies 15 floats from 'src' to 'dst.' */
	protected final static void copy_15(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
			dst[11] = src[11];
			dst[12] = src[12];
			dst[13] = src[13];
			dst[14] = src[14];
	}
	/** Sets 16 floats to zero. */
	protected final static void zero_16(final float[] dst) {
		dst[0]=dst[1]=dst[2]=dst[3]=dst[4]=dst[5]=dst[6]=dst[7]=dst[8]=dst[9]=dst[10]=dst[11]=dst[12]=dst[13]=dst[14]=dst[15]=0.0f;
	}
	/** Copies 16 floats from 'src' to 'dst.' */
	protected final static void copy_16(final float[] dst, final float[] src) {
			dst[0] = src[0];
			dst[1] = src[1];
			dst[2] = src[2];
			dst[3] = src[3];
			dst[4] = src[4];
			dst[5] = src[5];
			dst[6] = src[6];
			dst[7] = src[7];
			dst[8] = src[8];
			dst[9] = src[9];
			dst[10] = src[10];
			dst[11] = src[11];
			dst[12] = src[12];
			dst[13] = src[13];
			dst[14] = src[14];
			dst[15] = src[15];
	}
	/** Sets N floats to zero. */
	protected final static void zero_N(final float[] dst, final int N) {
		for (int i = 0; i < N; i++)
			dst[i] = 0.0f;
	}
	/** Copies N floats from 'src' to 'dst'. */
	protected final static void copy_N(final float[] dst, final float[] src, final int N) {
		for (int i = 0; i < N; i++)
			dst[i] = src[i];
	}


	private final static String DEFAULT_FP = "%2.2f";
	private final static String DEFAULT_START = "";
	private final static String DEFAULT_END = "";
	private final static String DEFAULT_MUL = "*";
	private final static String DEFAULT_WEDGE = "^";
	private final static String DEFAULT_PLUS = " + ";
	private final static String DEFAULT_MINUS = " - ";

	/*
	 * These strings determine how the output of string() is formatted.
	 * You can alter them at runtime using setStringFormat(). 
	 */
	protected static String string_fp = DEFAULT_FP;
	protected static String string_start = DEFAULT_START;
	protected static String string_end = DEFAULT_END;
	protected static String string_mul = DEFAULT_MUL;
	protected static String string_wedge = DEFAULT_WEDGE;
	protected static String string_plus = DEFAULT_PLUS;
	protected static String string_minus = DEFAULT_MINUS;
	
	public final static String STRING_FP = "fp";
	public final static String STRING_START = "start";
	public final static String STRING_END = "end";
	public final static String STRING_MUL = "mul";
	public final static String STRING_WEDGE = "wedge";
	public final static String STRING_PLUS = "plus";
	public final static String STRING_MINUS= "minus";

	/**
	 * Sets the formatting of toString().
	 * 
	 * @param what What formatter to set. Valid values: STRING_FP, STRING_START, STRING_END, STRING_MUL, STRING_WEDGE, STRING_PLUS, STRING_MINUS.
	 * @param format The value for 'what'. Use 'null' to set the default value.
	 */
	public final static void setStringFormat(final String what, final String format) {
		if (what.equals(STRING_FP)) 
			string_fp = (format != null) ? format : DEFAULT_FP;
		else if (what.equals(STRING_START)) 
			string_start = (format != null) ? format : DEFAULT_START;
		else if (what.equals(STRING_END)) 
			string_end = (format != null) ? format : DEFAULT_END;
		else if (what.equals(STRING_MUL)) 
			string_mul = (format != null) ? format : DEFAULT_MUL;
		else if (what.equals(STRING_WEDGE)) 
			string_wedge = (format != null) ? format : DEFAULT_WEDGE;
		else if (what.equals(STRING_PLUS)) 
			string_plus = (format != null) ? format : DEFAULT_PLUS;
		else if (what.equals(STRING_MINUS)) 
			string_minus = (format != null) ? format : DEFAULT_MINUS;
		else throw new RuntimeException("invalid argument to setStringFormat(): " + what);
	}
	
   /** Converts a multivector to a String using default float format. */
	public final static String string(final mv_if value) {
		return string(value, null);
	}
	
   /** 
    * Converts a multivector to a String according to a float format like  "%2.2f"
	* @param fp floating point format. Use 'null' for the default format (see setStringFormat()).
	*/
	public final static String string(final mv_if value, String fp) {
		mv obj = value.to_mv();
		StringBuffer result = new StringBuffer();
		int ia = 0; // global index into coordinates (runs from 0 to 63)
		int cnt = 0; // how many coordinates printed so far

		// set up the floating point precision
		if (fp == null) fp = string_fp;

		// start the string
		result.append(string_start);

		// print all coordinates
		for (int g = 0; g < 7; g++) {
			float[] Cg = obj.m_c[g];
			if (Cg != null) {
				for (int b = 0; b < GroupSize[g]; b++) {
					double coord = (double)BasisElementSignByIndex[ia] * Cg[b];
					
					// goal: print [+|-]obj.m_c[k][* basisVector1 ^ ... ^ basisVectorN]
					
					String tmpFloatStr = String.format(fp, Math.abs(coord));

					if (Double.parseDouble(tmpFloatStr) != 0.0) {
						// print [+|-]
						result.append((coord >= 0.0) 
							? ((cnt>0) ? string_plus : "")
							: string_minus);
						// print obj.m_c[k]
						result.append(tmpFloatStr);

						if (g != 0) { // if not grade 0, print [* basisVector1 ^ ... ^ basisVectorN]
							result.append(string_mul);

							// print all basis vectors
							int bei = 0;
							while (BasisElements[ia][bei] >= 0) {
								if (bei > 0)
									result.append(string_wedge);
								result.append(BasisVectorNames[BasisElements[ia][bei]]);
								bei++;
							}
						}

						cnt++;
					}
					ia++;
				}
			}
			else ia += GroupSize[g];
		}

		// if no coordinates printed: 0
		if (cnt == 0) result.append("0");

		// end the string
		result.append(string_end);

		return result.toString();
	}
	

	/**
     *  Simple way to call parser (regardless of whether it is a builtin or ANTLR parser).
     *  
     *  Throws a ParseException on failure.
     *  
     *  When an ANTLR based parser throws an exception, 
     *  all details (like line number and cause) are lost. 
     *  If these details are required, call the ANTLR parser directly.
     * 
     *  @param str The multivector string to be parsed (can be output of mv.ToString()).
     *  @return Multivector value represented by 'str'.
     */
    public final static mv parse(String str) throws ParseException
    {
        return Parser.parse(str, "string");
    }
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 0 -> group 0)
	 */
	protected final static void gp_default_0_0_0(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 1 -> group 1)
	 */
	protected final static void gp_default_0_1_1(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 2 -> group 2)
	 */
	protected final static void gp_default_0_2_2(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
		C[6] += A[0]*B[6];
		C[7] += A[0]*B[7];
		C[8] += A[0]*B[8];
		C[9] += A[0]*B[9];
		C[10] += A[0]*B[10];
		C[11] += A[0]*B[11];
		C[12] += A[0]*B[12];
		C[13] += A[0]*B[13];
		C[14] += A[0]*B[14];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 3 -> group 3)
	 */
	protected final static void gp_default_0_3_3(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
		C[6] += A[0]*B[6];
		C[7] += A[0]*B[7];
		C[8] += A[0]*B[8];
		C[9] += A[0]*B[9];
		C[10] += A[0]*B[10];
		C[11] += A[0]*B[11];
		C[12] += A[0]*B[12];
		C[13] += A[0]*B[13];
		C[14] += A[0]*B[14];
		C[15] += A[0]*B[15];
		C[16] += A[0]*B[16];
		C[17] += A[0]*B[17];
		C[18] += A[0]*B[18];
		C[19] += A[0]*B[19];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 4 -> group 4)
	 */
	protected final static void gp_default_0_4_4(float[] A, float[] B, float[] C) {
		gp_default_0_2_2(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 5 -> group 5)
	 */
	protected final static void gp_default_0_5_5(float[] A, float[] B, float[] C) {
		gp_default_0_1_1(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 6 -> group 6)
	 */
	protected final static void gp_default_0_6_6(float[] A, float[] B, float[] C) {
		gp_default_0_0_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 0 -> group 1)
	 */
	protected final static void gp_default_1_0_1(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 0)
	 */
	protected final static void gp_default_1_1_0(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]+A[1]*B[5]+A[2]*B[3]+A[3]*B[2]+A[4]*B[0]+A[5]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 2)
	 */
	protected final static void gp_default_1_1_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[1]-A[1]*B[0]);
		C[1] += (A[0]*B[2]-A[2]*B[0]);
		C[2] += (A[1]*B[2]-A[2]*B[1]);
		C[3] += (A[0]*B[3]-A[3]*B[0]);
		C[4] += (A[1]*B[3]-A[3]*B[1]);
		C[5] += (A[2]*B[3]-A[3]*B[2]);
		C[6] += (A[0]*B[4]-A[4]*B[0]);
		C[7] += (A[1]*B[4]-A[4]*B[1]);
		C[8] += (A[2]*B[4]-A[4]*B[2]);
		C[9] += (A[3]*B[4]-A[4]*B[3]);
		C[10] += (A[0]*B[5]-A[5]*B[0]);
		C[11] += (A[1]*B[5]-A[5]*B[1]);
		C[12] += (A[2]*B[5]-A[5]*B[2]);
		C[13] += (A[3]*B[5]-A[5]*B[3]);
		C[14] += (A[4]*B[5]-A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 1)
	 */
	protected final static void gp_default_1_2_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[6]-A[1]*B[10]-A[2]*B[3]-A[3]*B[1]-A[5]*B[0]);
		C[1] += (-A[0]*B[7]-A[1]*B[11]-A[2]*B[4]-A[3]*B[2]+A[4]*B[0]);
		C[2] += (-A[0]*B[8]-A[1]*B[12]-A[2]*B[5]+A[4]*B[1]+A[5]*B[2]);
		C[3] += (-A[0]*B[9]-A[1]*B[13]+A[3]*B[5]+A[4]*B[3]+A[5]*B[4]);
		C[4] += (-A[1]*B[14]+A[2]*B[9]+A[3]*B[8]+A[4]*B[6]+A[5]*B[7]);
		C[5] += (A[0]*B[14]+A[2]*B[13]+A[3]*B[12]+A[4]*B[10]+A[5]*B[11]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 3)
	 */
	protected final static void gp_default_1_2_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]-A[1]*B[1]+A[2]*B[0]);
		C[1] += (A[0]*B[4]-A[1]*B[3]+A[3]*B[0]);
		C[2] += (A[0]*B[5]-A[2]*B[3]+A[3]*B[1]);
		C[3] += (A[1]*B[5]-A[2]*B[4]+A[3]*B[2]);
		C[4] += (A[0]*B[7]-A[1]*B[6]+A[4]*B[0]);
		C[5] += (A[0]*B[8]-A[2]*B[6]+A[4]*B[1]);
		C[6] += (A[1]*B[8]-A[2]*B[7]+A[4]*B[2]);
		C[7] += (A[0]*B[9]-A[3]*B[6]+A[4]*B[3]);
		C[8] += (A[1]*B[9]-A[3]*B[7]+A[4]*B[4]);
		C[9] += (A[2]*B[9]-A[3]*B[8]+A[4]*B[5]);
		C[10] += (A[0]*B[11]-A[1]*B[10]+A[5]*B[0]);
		C[11] += (A[0]*B[12]-A[2]*B[10]+A[5]*B[1]);
		C[12] += (A[1]*B[12]-A[2]*B[11]+A[5]*B[2]);
		C[13] += (A[0]*B[13]-A[3]*B[10]+A[5]*B[3]);
		C[14] += (A[1]*B[13]-A[3]*B[11]+A[5]*B[4]);
		C[15] += (A[2]*B[13]-A[3]*B[12]+A[5]*B[5]);
		C[16] += (A[0]*B[14]-A[4]*B[10]+A[5]*B[6]);
		C[17] += (A[1]*B[14]-A[4]*B[11]+A[5]*B[7]);
		C[18] += (A[2]*B[14]-A[4]*B[12]+A[5]*B[8]);
		C[19] += (A[3]*B[14]-A[4]*B[13]+A[5]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 2)
	 */
	protected final static void gp_default_1_3_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]+A[1]*B[10]+A[2]*B[1]+A[3]*B[0]);
		C[1] += (A[0]*B[5]+A[1]*B[11]+A[2]*B[2]-A[5]*B[0]);
		C[2] += (A[0]*B[6]+A[1]*B[12]+A[2]*B[3]+A[4]*B[0]);
		C[3] += (A[0]*B[7]+A[1]*B[13]-A[3]*B[2]-A[5]*B[1]);
		C[4] += (A[0]*B[8]+A[1]*B[14]-A[3]*B[3]+A[4]*B[1]);
		C[5] += (A[0]*B[9]+A[1]*B[15]+A[4]*B[2]+A[5]*B[3]);
		C[6] += (A[1]*B[16]-A[2]*B[7]-A[3]*B[5]-A[5]*B[4]);
		C[7] += (A[1]*B[17]-A[2]*B[8]-A[3]*B[6]+A[4]*B[4]);
		C[8] += (A[1]*B[18]-A[2]*B[9]+A[4]*B[5]+A[5]*B[6]);
		C[9] += (A[1]*B[19]+A[3]*B[9]+A[4]*B[7]+A[5]*B[8]);
		C[10] += (-A[0]*B[16]-A[2]*B[13]-A[3]*B[11]-A[5]*B[10]);
		C[11] += (-A[0]*B[17]-A[2]*B[14]-A[3]*B[12]+A[4]*B[10]);
		C[12] += (-A[0]*B[18]-A[2]*B[15]+A[4]*B[11]+A[5]*B[12]);
		C[13] += (-A[0]*B[19]+A[3]*B[15]+A[4]*B[13]+A[5]*B[14]);
		C[14] += (A[2]*B[19]+A[3]*B[18]+A[4]*B[16]+A[5]*B[17]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 4)
	 */
	protected final static void gp_default_1_3_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]-A[1]*B[2]+A[2]*B[1]-A[3]*B[0]);
		C[1] += (A[0]*B[6]-A[1]*B[5]+A[2]*B[4]-A[4]*B[0]);
		C[2] += (A[0]*B[8]-A[1]*B[7]+A[3]*B[4]-A[4]*B[1]);
		C[3] += (A[0]*B[9]-A[2]*B[7]+A[3]*B[5]-A[4]*B[2]);
		C[4] += (A[1]*B[9]-A[2]*B[8]+A[3]*B[6]-A[4]*B[3]);
		C[5] += (A[0]*B[12]-A[1]*B[11]+A[2]*B[10]-A[5]*B[0]);
		C[6] += (A[0]*B[14]-A[1]*B[13]+A[3]*B[10]-A[5]*B[1]);
		C[7] += (A[0]*B[15]-A[2]*B[13]+A[3]*B[11]-A[5]*B[2]);
		C[8] += (A[1]*B[15]-A[2]*B[14]+A[3]*B[12]-A[5]*B[3]);
		C[9] += (A[0]*B[17]-A[1]*B[16]+A[4]*B[10]-A[5]*B[4]);
		C[10] += (A[0]*B[18]-A[2]*B[16]+A[4]*B[11]-A[5]*B[5]);
		C[11] += (A[1]*B[18]-A[2]*B[17]+A[4]*B[12]-A[5]*B[6]);
		C[12] += (A[0]*B[19]-A[3]*B[16]+A[4]*B[13]-A[5]*B[7]);
		C[13] += (A[1]*B[19]-A[3]*B[17]+A[4]*B[14]-A[5]*B[8]);
		C[14] += (A[2]*B[19]-A[3]*B[18]+A[4]*B[15]-A[5]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 3)
	 */
	protected final static void gp_default_1_4_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[1]-A[1]*B[5]-A[2]*B[0]);
		C[1] += (-A[0]*B[2]-A[1]*B[6]+A[3]*B[0]);
		C[2] += (-A[0]*B[3]-A[1]*B[7]-A[5]*B[0]);
		C[3] += (-A[0]*B[4]-A[1]*B[8]+A[4]*B[0]);
		C[4] += (-A[1]*B[9]+A[2]*B[2]+A[3]*B[1]);
		C[5] += (-A[1]*B[10]+A[2]*B[3]-A[5]*B[1]);
		C[6] += (-A[1]*B[11]+A[2]*B[4]+A[4]*B[1]);
		C[7] += (-A[1]*B[12]-A[3]*B[3]-A[5]*B[2]);
		C[8] += (-A[1]*B[13]-A[3]*B[4]+A[4]*B[2]);
		C[9] += (-A[1]*B[14]+A[4]*B[3]+A[5]*B[4]);
		C[10] += (A[0]*B[9]+A[2]*B[6]+A[3]*B[5]);
		C[11] += (A[0]*B[10]+A[2]*B[7]-A[5]*B[5]);
		C[12] += (A[0]*B[11]+A[2]*B[8]+A[4]*B[5]);
		C[13] += (A[0]*B[12]-A[3]*B[7]-A[5]*B[6]);
		C[14] += (A[0]*B[13]-A[3]*B[8]+A[4]*B[6]);
		C[15] += (A[0]*B[14]+A[4]*B[7]+A[5]*B[8]);
		C[16] += (-A[2]*B[12]-A[3]*B[10]-A[5]*B[9]);
		C[17] += (-A[2]*B[13]-A[3]*B[11]+A[4]*B[9]);
		C[18] += (-A[2]*B[14]+A[4]*B[10]+A[5]*B[11]);
		C[19] += (A[3]*B[14]+A[4]*B[12]+A[5]*B[13]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 5)
	 */
	protected final static void gp_default_1_4_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]+A[4]*B[0]);
		C[1] += (A[0]*B[8]-A[1]*B[7]+A[2]*B[6]-A[3]*B[5]+A[5]*B[0]);
		C[2] += (A[0]*B[11]-A[1]*B[10]+A[2]*B[9]-A[4]*B[5]+A[5]*B[1]);
		C[3] += (A[0]*B[13]-A[1]*B[12]+A[3]*B[9]-A[4]*B[6]+A[5]*B[2]);
		C[4] += (A[0]*B[14]-A[2]*B[12]+A[3]*B[10]-A[4]*B[7]+A[5]*B[3]);
		C[5] += (A[1]*B[14]-A[2]*B[13]+A[3]*B[11]-A[4]*B[8]+A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 5 -> group 4)
	 */
	protected final static void gp_default_1_5_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[0]+A[1]*B[1]);
		C[1] += (A[1]*B[2]-A[2]*B[0]);
		C[2] += (A[1]*B[3]+A[3]*B[0]);
		C[3] += (A[1]*B[4]-A[5]*B[0]);
		C[4] += (A[1]*B[5]+A[4]*B[0]);
		C[5] += (-A[0]*B[2]-A[2]*B[1]);
		C[6] += (-A[0]*B[3]+A[3]*B[1]);
		C[7] += (-A[0]*B[4]-A[5]*B[1]);
		C[8] += (-A[0]*B[5]+A[4]*B[1]);
		C[9] += (A[2]*B[3]+A[3]*B[2]);
		C[10] += (A[2]*B[4]-A[5]*B[2]);
		C[11] += (A[2]*B[5]+A[4]*B[2]);
		C[12] += (-A[3]*B[4]-A[5]*B[3]);
		C[13] += (-A[3]*B[5]+A[4]*B[3]);
		C[14] += (A[4]*B[4]+A[5]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 5 -> group 6)
	 */
	protected final static void gp_default_1_5_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]-A[3]*B[2]+A[4]*B[1]-A[5]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 6 -> group 5)
	 */
	protected final static void gp_default_1_6_5(float[] A, float[] B, float[] C) {
		C[0] += -A[1]*B[0];
		C[1] += A[0]*B[0];
		C[2] += -A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += -A[5]*B[0];
		C[5] += A[4]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 0 -> group 2)
	 */
	protected final static void gp_default_2_0_2(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
		C[6] += A[6]*B[0];
		C[7] += A[7]*B[0];
		C[8] += A[8]*B[0];
		C[9] += A[9]*B[0];
		C[10] += A[10]*B[0];
		C[11] += A[11]*B[0];
		C[12] += A[12]*B[0];
		C[13] += A[13]*B[0];
		C[14] += A[14]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 1)
	 */
	protected final static void gp_default_2_1_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]+A[1]*B[3]+A[10]*B[1]+A[3]*B[2]+A[6]*B[0]);
		C[1] += (-A[0]*B[4]+A[11]*B[1]+A[2]*B[3]+A[4]*B[2]+A[7]*B[0]);
		C[2] += (-A[1]*B[4]+A[12]*B[1]-A[2]*B[5]+A[5]*B[2]+A[8]*B[0]);
		C[3] += (A[13]*B[1]-A[3]*B[4]-A[4]*B[5]-A[5]*B[3]+A[9]*B[0]);
		C[4] += (A[14]*B[1]-A[6]*B[4]-A[7]*B[5]-A[8]*B[3]-A[9]*B[2]);
		C[5] += (-A[10]*B[4]-A[11]*B[5]-A[12]*B[3]-A[13]*B[2]-A[14]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 3)
	 */
	protected final static void gp_default_2_1_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]-A[1]*B[1]+A[2]*B[0]);
		C[1] += (A[0]*B[3]-A[3]*B[1]+A[4]*B[0]);
		C[2] += (A[1]*B[3]-A[3]*B[2]+A[5]*B[0]);
		C[3] += (A[2]*B[3]-A[4]*B[2]+A[5]*B[1]);
		C[4] += (A[0]*B[4]-A[6]*B[1]+A[7]*B[0]);
		C[5] += (A[1]*B[4]-A[6]*B[2]+A[8]*B[0]);
		C[6] += (A[2]*B[4]-A[7]*B[2]+A[8]*B[1]);
		C[7] += (A[3]*B[4]-A[6]*B[3]+A[9]*B[0]);
		C[8] += (A[4]*B[4]-A[7]*B[3]+A[9]*B[1]);
		C[9] += (A[5]*B[4]-A[8]*B[3]+A[9]*B[2]);
		C[10] += (A[0]*B[5]-A[10]*B[1]+A[11]*B[0]);
		C[11] += (A[1]*B[5]-A[10]*B[2]+A[12]*B[0]);
		C[12] += (-A[11]*B[2]+A[12]*B[1]+A[2]*B[5]);
		C[13] += (-A[10]*B[3]+A[13]*B[0]+A[3]*B[5]);
		C[14] += (-A[11]*B[3]+A[13]*B[1]+A[4]*B[5]);
		C[15] += (-A[12]*B[3]+A[13]*B[2]+A[5]*B[5]);
		C[16] += (-A[10]*B[4]+A[14]*B[0]+A[6]*B[5]);
		C[17] += (-A[11]*B[4]+A[14]*B[1]+A[7]*B[5]);
		C[18] += (-A[12]*B[4]+A[14]*B[2]+A[8]*B[5]);
		C[19] += (-A[13]*B[4]+A[14]*B[3]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 0)
	 */
	protected final static void gp_default_2_2_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[14]+A[1]*B[9]+A[10]*B[7]+A[11]*B[11]+A[12]*B[4]+A[13]*B[2]-A[14]*B[0]+A[2]*B[13]+A[3]*B[8]+A[4]*B[12]+A[5]*B[5]+A[6]*B[6]+A[7]*B[10]+A[8]*B[3]+A[9]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 2)
	 */
	protected final static void gp_default_2_2_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[11]-A[0]*B[6]-A[1]*B[4]+A[11]*B[0]+A[2]*B[3]-A[3]*B[2]+A[4]*B[1]+A[6]*B[0]);
		C[1] += (-A[0]*B[12]-A[1]*B[5]-A[1]*B[6]+A[10]*B[2]+A[12]*B[0]-A[2]*B[10]+A[5]*B[1]+A[6]*B[1]);
		C[2] += (A[0]*B[8]-A[1]*B[7]+A[11]*B[2]-A[2]*B[11]-A[2]*B[5]+A[5]*B[2]+A[7]*B[1]-A[8]*B[0]);
		C[3] += (-A[0]*B[13]+A[10]*B[4]+A[13]*B[0]+A[3]*B[5]-A[3]*B[6]-A[4]*B[10]-A[5]*B[3]+A[6]*B[3]);
		C[4] += (A[0]*B[9]+A[11]*B[4]-A[3]*B[7]-A[4]*B[11]+A[4]*B[5]-A[5]*B[4]+A[7]*B[3]-A[9]*B[0]);
		C[5] += (A[1]*B[9]+A[12]*B[4]-A[13]*B[2]+A[2]*B[13]-A[3]*B[8]-A[4]*B[12]+A[8]*B[3]-A[9]*B[1]);
		C[6] += (-A[0]*B[14]+A[1]*B[9]+A[10]*B[7]+A[14]*B[0]+A[3]*B[8]-A[7]*B[10]-A[8]*B[3]-A[9]*B[1]);
		C[7] += (A[11]*B[7]+A[2]*B[9]+A[4]*B[8]-A[6]*B[7]-A[7]*B[11]+A[7]*B[6]-A[8]*B[4]-A[9]*B[2]);
		C[8] += (A[12]*B[7]-A[14]*B[2]+A[2]*B[14]+A[5]*B[8]-A[6]*B[8]-A[7]*B[12]-A[8]*B[5]+A[8]*B[6]);
		C[9] += (A[13]*B[7]-A[14]*B[4]+A[4]*B[14]-A[5]*B[9]-A[6]*B[9]-A[7]*B[13]+A[9]*B[5]+A[9]*B[6]);
		C[10] += (A[1]*B[13]+A[10]*B[11]-A[10]*B[6]-A[11]*B[10]-A[12]*B[3]-A[13]*B[1]+A[3]*B[12]+A[6]*B[10]);
		C[11] += (-A[0]*B[14]-A[10]*B[7]-A[12]*B[4]-A[13]*B[2]+A[14]*B[0]+A[2]*B[13]+A[4]*B[12]+A[7]*B[10]);
		C[12] += (-A[1]*B[14]-A[10]*B[8]-A[11]*B[12]+A[12]*B[11]-A[12]*B[5]+A[14]*B[1]+A[5]*B[12]+A[8]*B[10]);
		C[13] += (-A[10]*B[9]-A[11]*B[13]+A[13]*B[11]+A[13]*B[5]+A[14]*B[3]-A[3]*B[14]-A[5]*B[13]+A[9]*B[10]);
		C[14] += (-A[11]*B[14]+A[12]*B[9]+A[13]*B[8]+A[14]*B[11]+A[14]*B[6]-A[6]*B[14]-A[8]*B[13]-A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 4)
	 */
	protected final static void gp_default_2_2_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]+A[3]*B[2]-A[4]*B[1]+A[5]*B[0]);
		C[1] += (A[0]*B[8]-A[1]*B[7]+A[2]*B[6]+A[6]*B[2]-A[7]*B[1]+A[8]*B[0]);
		C[2] += (A[0]*B[9]-A[3]*B[7]+A[4]*B[6]+A[6]*B[4]-A[7]*B[3]+A[9]*B[0]);
		C[3] += (A[1]*B[9]-A[3]*B[8]+A[5]*B[6]+A[6]*B[5]-A[8]*B[3]+A[9]*B[1]);
		C[4] += (A[2]*B[9]-A[4]*B[8]+A[5]*B[7]+A[7]*B[5]-A[8]*B[4]+A[9]*B[2]);
		C[5] += (A[0]*B[12]-A[1]*B[11]+A[10]*B[2]-A[11]*B[1]+A[12]*B[0]+A[2]*B[10]);
		C[6] += (A[0]*B[13]+A[10]*B[4]-A[11]*B[3]+A[13]*B[0]-A[3]*B[11]+A[4]*B[10]);
		C[7] += (A[1]*B[13]+A[10]*B[5]-A[12]*B[3]+A[13]*B[1]-A[3]*B[12]+A[5]*B[10]);
		C[8] += (A[11]*B[5]-A[12]*B[4]+A[13]*B[2]+A[2]*B[13]-A[4]*B[12]+A[5]*B[11]);
		C[9] += (A[0]*B[14]+A[10]*B[7]-A[11]*B[6]+A[14]*B[0]-A[6]*B[11]+A[7]*B[10]);
		C[10] += (A[1]*B[14]+A[10]*B[8]-A[12]*B[6]+A[14]*B[1]-A[6]*B[12]+A[8]*B[10]);
		C[11] += (A[11]*B[8]-A[12]*B[7]+A[14]*B[2]+A[2]*B[14]-A[7]*B[12]+A[8]*B[11]);
		C[12] += (A[10]*B[9]-A[13]*B[6]+A[14]*B[3]+A[3]*B[14]-A[6]*B[13]+A[9]*B[10]);
		C[13] += (A[11]*B[9]-A[13]*B[7]+A[14]*B[4]+A[4]*B[14]-A[7]*B[13]+A[9]*B[11]);
		C[14] += (A[12]*B[9]-A[13]*B[8]+A[14]*B[5]+A[5]*B[14]-A[8]*B[13]+A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 1)
	 */
	protected final static void gp_default_2_3_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[16]+A[1]*B[7]+A[10]*B[4]+A[11]*B[10]+A[12]*B[1]+A[13]*B[0]+A[2]*B[13]+A[3]*B[5]+A[4]*B[11]+A[5]*B[2]);
		C[1] += (-A[0]*B[17]+A[1]*B[8]+A[2]*B[14]+A[3]*B[6]+A[4]*B[12]+A[5]*B[3]-A[6]*B[4]-A[7]*B[10]-A[8]*B[1]-A[9]*B[0]);
		C[2] += (-A[0]*B[18]+A[1]*B[9]-A[10]*B[6]-A[11]*B[12]-A[12]*B[3]-A[14]*B[0]+A[2]*B[15]-A[6]*B[5]-A[7]*B[11]-A[8]*B[2]);
		C[3] += (-A[0]*B[19]-A[10]*B[8]-A[11]*B[14]+A[13]*B[3]-A[14]*B[1]-A[3]*B[9]-A[4]*B[15]-A[6]*B[7]-A[7]*B[13]+A[9]*B[2]);
		C[4] += (-A[11]*B[17]+A[12]*B[8]+A[13]*B[6]-A[14]*B[4]-A[2]*B[19]-A[4]*B[18]+A[5]*B[9]-A[7]*B[16]+A[8]*B[7]+A[9]*B[5]);
		C[5] += (A[1]*B[19]+A[10]*B[17]+A[12]*B[14]+A[13]*B[12]-A[14]*B[10]+A[3]*B[18]+A[5]*B[15]+A[6]*B[16]+A[8]*B[13]+A[9]*B[11]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 3)
	 */
	protected final static void gp_default_2_3_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[12]+A[0]*B[5]+A[1]*B[3]-A[1]*B[4]+A[11]*B[0]-A[2]*B[10]-A[2]*B[2]+A[5]*B[0]+A[6]*B[0]);
		C[1] += (A[0]*B[14]+A[0]*B[7]+A[11]*B[1]-A[3]*B[3]-A[3]*B[4]-A[4]*B[10]+A[4]*B[2]-A[5]*B[1]+A[6]*B[1]);
		C[2] += (A[0]*B[15]+A[1]*B[7]+A[10]*B[3]+A[12]*B[1]-A[13]*B[0]+A[2]*B[13]-A[3]*B[5]-A[4]*B[11]+A[6]*B[2]);
		C[3] += (-A[0]*B[9]+A[1]*B[8]+A[11]*B[3]+A[2]*B[14]-A[3]*B[6]-A[4]*B[12]+A[7]*B[2]-A[8]*B[1]+A[9]*B[0]);
		C[4] += (A[0]*B[17]-A[1]*B[8]+A[11]*B[4]+A[2]*B[7]-A[3]*B[6]+A[4]*B[5]-A[7]*B[10]-A[8]*B[1]-A[9]*B[0]);
		C[5] += (A[0]*B[18]-A[1]*B[9]+A[10]*B[6]+A[12]*B[4]-A[14]*B[0]+A[2]*B[16]+A[5]*B[5]-A[7]*B[11]-A[8]*B[2]);
		C[6] += (A[11]*B[6]+A[2]*B[17]-A[2]*B[9]+A[5]*B[6]-A[6]*B[6]-A[7]*B[12]+A[7]*B[5]-A[8]*B[3]-A[8]*B[4]);
		C[7] += (A[0]*B[19]+A[10]*B[8]+A[13]*B[4]-A[14]*B[1]+A[3]*B[9]+A[4]*B[16]-A[5]*B[7]-A[7]*B[13]+A[9]*B[2]);
		C[8] += (A[11]*B[8]+A[4]*B[17]+A[4]*B[9]-A[5]*B[8]-A[6]*B[8]-A[7]*B[14]+A[7]*B[7]+A[9]*B[3]-A[9]*B[4]);
		C[9] += (A[12]*B[8]-A[13]*B[6]+A[14]*B[3]-A[2]*B[19]+A[4]*B[18]-A[6]*B[9]-A[7]*B[15]+A[8]*B[7]-A[9]*B[5]);
		C[10] += (-A[0]*B[16]-A[1]*B[14]-A[10]*B[4]-A[12]*B[1]-A[13]*B[0]+A[2]*B[13]-A[3]*B[12]+A[4]*B[11]+A[6]*B[10]);
		C[11] += (-A[1]*B[15]-A[1]*B[16]+A[10]*B[12]-A[10]*B[5]-A[11]*B[11]+A[12]*B[10]-A[12]*B[2]+A[5]*B[11]+A[6]*B[11]);
		C[12] += (A[0]*B[18]-A[1]*B[17]-A[10]*B[6]-A[12]*B[3]-A[14]*B[0]-A[2]*B[15]+A[5]*B[12]+A[7]*B[11]-A[8]*B[10]);
		C[13] += (A[10]*B[14]-A[10]*B[7]-A[11]*B[13]+A[13]*B[10]+A[13]*B[2]+A[3]*B[15]-A[3]*B[16]-A[5]*B[13]+A[6]*B[13]);
		C[14] += (A[0]*B[19]-A[10]*B[8]+A[13]*B[3]-A[14]*B[1]-A[3]*B[17]+A[4]*B[15]-A[5]*B[14]+A[7]*B[13]-A[9]*B[10]);
		C[15] += (A[1]*B[19]-A[10]*B[9]-A[11]*B[15]+A[12]*B[14]-A[13]*B[12]-A[14]*B[2]-A[3]*B[18]+A[8]*B[13]-A[9]*B[11]);
		C[16] += (A[1]*B[19]+A[10]*B[17]-A[11]*B[16]+A[12]*B[7]+A[13]*B[5]+A[14]*B[10]+A[3]*B[18]-A[8]*B[13]-A[9]*B[11]);
		C[17] += (A[12]*B[8]+A[13]*B[6]-A[14]*B[4]+A[2]*B[19]+A[4]*B[18]-A[6]*B[17]+A[7]*B[16]-A[8]*B[14]-A[9]*B[12]);
		C[18] += (-A[11]*B[18]+A[12]*B[17]+A[12]*B[9]-A[14]*B[12]-A[14]*B[5]+A[5]*B[18]-A[6]*B[18]-A[8]*B[15]+A[8]*B[16]);
		C[19] += (-A[11]*B[19]+A[13]*B[17]-A[13]*B[9]-A[14]*B[14]-A[14]*B[7]-A[5]*B[19]-A[6]*B[19]+A[9]*B[15]+A[9]*B[16]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 5)
	 */
	protected final static void gp_default_2_3_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[9]-A[1]*B[8]+A[2]*B[7]+A[3]*B[6]-A[4]*B[5]+A[5]*B[4]-A[6]*B[3]+A[7]*B[2]-A[8]*B[1]+A[9]*B[0]);
		C[1] += (A[0]*B[15]-A[1]*B[14]-A[10]*B[3]+A[11]*B[2]-A[12]*B[1]+A[13]*B[0]+A[2]*B[13]+A[3]*B[12]-A[4]*B[11]+A[5]*B[10]);
		C[2] += (A[0]*B[18]-A[1]*B[17]-A[10]*B[6]+A[11]*B[5]-A[12]*B[4]+A[14]*B[0]+A[2]*B[16]+A[6]*B[12]-A[7]*B[11]+A[8]*B[10]);
		C[3] += (A[0]*B[19]-A[10]*B[8]+A[11]*B[7]-A[13]*B[4]+A[14]*B[1]-A[3]*B[17]+A[4]*B[16]+A[6]*B[14]-A[7]*B[13]+A[9]*B[10]);
		C[4] += (A[1]*B[19]-A[10]*B[9]+A[12]*B[7]-A[13]*B[5]+A[14]*B[2]-A[3]*B[18]+A[5]*B[16]+A[6]*B[15]-A[8]*B[13]+A[9]*B[11]);
		C[5] += (-A[11]*B[9]+A[12]*B[8]-A[13]*B[6]+A[14]*B[3]+A[2]*B[19]-A[4]*B[18]+A[5]*B[17]+A[7]*B[15]-A[8]*B[14]+A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 2)
	 */
	protected final static void gp_default_2_4_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[9]+A[1]*B[2]+A[2]*B[6]+A[3]*B[1]+A[4]*B[5]+A[5]*B[0]);
		C[1] += (-A[0]*B[10]+A[1]*B[3]-A[10]*B[1]-A[11]*B[5]-A[12]*B[0]+A[2]*B[7]);
		C[2] += (-A[0]*B[11]+A[1]*B[4]+A[2]*B[8]+A[6]*B[1]+A[7]*B[5]+A[8]*B[0]);
		C[3] += (-A[0]*B[12]-A[10]*B[2]-A[11]*B[6]+A[13]*B[0]-A[3]*B[3]-A[4]*B[7]);
		C[4] += (-A[0]*B[13]-A[3]*B[4]-A[4]*B[8]+A[6]*B[2]+A[7]*B[6]-A[9]*B[0]);
		C[5] += (-A[0]*B[14]+A[10]*B[4]+A[11]*B[8]-A[14]*B[0]+A[6]*B[3]+A[7]*B[7]);
		C[6] += (-A[11]*B[9]+A[12]*B[2]+A[13]*B[1]-A[2]*B[12]-A[4]*B[10]+A[5]*B[3]);
		C[7] += (-A[2]*B[13]-A[4]*B[11]+A[5]*B[4]+A[7]*B[9]-A[8]*B[2]-A[9]*B[1]);
		C[8] += (A[11]*B[11]-A[12]*B[4]-A[14]*B[1]-A[2]*B[14]+A[7]*B[10]-A[8]*B[3]);
		C[9] += (A[11]*B[13]+A[13]*B[4]-A[14]*B[2]+A[4]*B[14]+A[7]*B[12]+A[9]*B[3]);
		C[10] += (A[1]*B[12]+A[10]*B[9]+A[12]*B[6]+A[13]*B[5]+A[3]*B[10]+A[5]*B[7]);
		C[11] += (A[1]*B[13]+A[3]*B[11]+A[5]*B[8]-A[6]*B[9]-A[8]*B[6]-A[9]*B[5]);
		C[12] += (A[1]*B[14]-A[10]*B[11]-A[12]*B[8]-A[14]*B[5]-A[6]*B[10]-A[8]*B[7]);
		C[13] += (-A[10]*B[13]+A[13]*B[8]-A[14]*B[6]-A[3]*B[14]-A[6]*B[12]+A[9]*B[7]);
		C[14] += (A[12]*B[13]+A[13]*B[11]-A[14]*B[9]+A[5]*B[14]+A[8]*B[12]+A[9]*B[10]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 4)
	 */
	protected final static void gp_default_2_4_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[3]-A[0]*B[8]+A[1]*B[2]+A[11]*B[0]+A[2]*B[6]-A[3]*B[1]-A[4]*B[5]+A[6]*B[0]);
		C[1] += (-A[0]*B[11]+A[1]*B[4]+A[11]*B[1]-A[2]*B[3]+A[2]*B[9]+A[5]*B[1]-A[7]*B[5]-A[8]*B[0]);
		C[2] += (-A[0]*B[13]+A[11]*B[2]-A[3]*B[4]+A[4]*B[3]+A[4]*B[9]-A[5]*B[2]-A[7]*B[6]+A[9]*B[0]);
		C[3] += (-A[0]*B[14]+A[10]*B[4]+A[12]*B[2]-A[13]*B[1]+A[14]*B[0]-A[2]*B[12]+A[4]*B[10]-A[7]*B[7]);
		C[4] += (A[11]*B[4]-A[2]*B[13]+A[4]*B[11]-A[6]*B[4]+A[7]*B[3]-A[7]*B[8]-A[8]*B[2]+A[9]*B[1]);
		C[5] += (A[0]*B[10]+A[1]*B[8]-A[1]*B[9]-A[10]*B[1]-A[12]*B[0]-A[2]*B[7]+A[5]*B[5]+A[6]*B[5]);
		C[6] += (A[0]*B[12]-A[10]*B[2]+A[13]*B[0]-A[3]*B[8]-A[3]*B[9]+A[4]*B[7]-A[5]*B[6]+A[6]*B[6]);
		C[7] += (A[1]*B[12]-A[10]*B[3]+A[10]*B[8]-A[11]*B[7]+A[12]*B[6]-A[13]*B[5]-A[3]*B[10]+A[6]*B[7]);
		C[8] += (-A[0]*B[14]+A[1]*B[13]-A[10]*B[4]+A[14]*B[0]-A[3]*B[11]+A[7]*B[7]-A[8]*B[6]+A[9]*B[5]);
		C[9] += (-A[1]*B[13]+A[12]*B[2]+A[13]*B[1]+A[2]*B[12]-A[3]*B[11]+A[4]*B[10]-A[8]*B[6]-A[9]*B[5]);
		C[10] += (-A[1]*B[14]+A[10]*B[11]-A[11]*B[10]+A[12]*B[3]+A[12]*B[9]-A[14]*B[5]+A[5]*B[10]-A[8]*B[7]);
		C[11] += (A[12]*B[4]+A[14]*B[1]-A[2]*B[14]+A[5]*B[11]-A[6]*B[11]+A[7]*B[10]-A[8]*B[8]-A[8]*B[9]);
		C[12] += (A[10]*B[13]-A[11]*B[12]-A[13]*B[3]+A[13]*B[9]-A[14]*B[6]+A[3]*B[14]-A[5]*B[12]+A[9]*B[7]);
		C[13] += (-A[13]*B[4]+A[14]*B[2]+A[4]*B[14]-A[5]*B[13]-A[6]*B[13]+A[7]*B[12]+A[9]*B[8]-A[9]*B[9]);
		C[14] += (-A[11]*B[14]+A[12]*B[13]-A[13]*B[11]+A[14]*B[3]+A[14]*B[8]-A[6]*B[14]+A[8]*B[12]-A[9]*B[10]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 6)
	 */
	protected final static void gp_default_2_4_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]-A[1]*B[13]+A[10]*B[4]-A[11]*B[3]+A[12]*B[2]-A[13]*B[1]+A[14]*B[0]+A[2]*B[12]+A[3]*B[11]-A[4]*B[10]+A[5]*B[9]-A[6]*B[8]+A[7]*B[7]-A[8]*B[6]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 5 -> group 3)
	 */
	protected final static void gp_default_2_5_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[2]+A[1]*B[0]+A[2]*B[1]);
		C[1] += (-A[0]*B[3]-A[3]*B[0]-A[4]*B[1]);
		C[2] += (-A[0]*B[4]+A[10]*B[0]+A[11]*B[1]);
		C[3] += (-A[0]*B[5]-A[6]*B[0]-A[7]*B[1]);
		C[4] += (-A[2]*B[3]-A[4]*B[2]+A[5]*B[0]);
		C[5] += (A[11]*B[2]-A[12]*B[0]-A[2]*B[4]);
		C[6] += (-A[2]*B[5]-A[7]*B[2]+A[8]*B[0]);
		C[7] += (A[11]*B[3]+A[13]*B[0]+A[4]*B[4]);
		C[8] += (A[4]*B[5]-A[7]*B[3]-A[9]*B[0]);
		C[9] += (-A[11]*B[5]-A[14]*B[0]-A[7]*B[4]);
		C[10] += (A[1]*B[3]+A[3]*B[2]+A[5]*B[1]);
		C[11] += (A[1]*B[4]-A[10]*B[2]-A[12]*B[1]);
		C[12] += (A[1]*B[5]+A[6]*B[2]+A[8]*B[1]);
		C[13] += (-A[10]*B[3]+A[13]*B[1]-A[3]*B[4]);
		C[14] += (-A[3]*B[5]+A[6]*B[3]-A[9]*B[1]);
		C[15] += (A[10]*B[5]-A[14]*B[1]+A[6]*B[4]);
		C[16] += (A[12]*B[3]+A[13]*B[2]+A[5]*B[4]);
		C[17] += (A[5]*B[5]-A[8]*B[3]-A[9]*B[2]);
		C[18] += (-A[12]*B[5]-A[14]*B[2]-A[8]*B[4]);
		C[19] += (A[13]*B[5]-A[14]*B[3]+A[9]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 5 -> group 5)
	 */
	protected final static void gp_default_2_5_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]+A[11]*B[0]-A[2]*B[3]+A[4]*B[2]-A[7]*B[1]);
		C[1] += (-A[0]*B[4]+A[1]*B[3]-A[10]*B[0]-A[3]*B[2]+A[6]*B[1]);
		C[2] += (A[1]*B[5]+A[12]*B[0]-A[2]*B[4]+A[5]*B[2]-A[8]*B[1]);
		C[3] += (-A[13]*B[0]-A[3]*B[5]+A[4]*B[4]-A[5]*B[3]+A[9]*B[1]);
		C[4] += (A[10]*B[5]-A[11]*B[4]+A[12]*B[3]-A[13]*B[2]+A[14]*B[1]);
		C[5] += (-A[14]*B[0]-A[6]*B[5]+A[7]*B[4]-A[8]*B[3]+A[9]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 6 -> group 4)
	 */
	protected final static void gp_default_2_6_4(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
		C[1] += -A[2]*B[0];
		C[2] += A[4]*B[0];
		C[3] += -A[11]*B[0];
		C[4] += A[7]*B[0];
		C[5] += A[1]*B[0];
		C[6] += -A[3]*B[0];
		C[7] += A[10]*B[0];
		C[8] += -A[6]*B[0];
		C[9] += A[5]*B[0];
		C[10] += -A[12]*B[0];
		C[11] += A[8]*B[0];
		C[12] += A[13]*B[0];
		C[13] += -A[9]*B[0];
		C[14] += -A[14]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 0 -> group 3)
	 */
	protected final static void gp_default_3_0_3(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
		C[6] += A[6]*B[0];
		C[7] += A[7]*B[0];
		C[8] += A[8]*B[0];
		C[9] += A[9]*B[0];
		C[10] += A[10]*B[0];
		C[11] += A[11]*B[0];
		C[12] += A[12]*B[0];
		C[13] += A[13]*B[0];
		C[14] += A[14]*B[0];
		C[15] += A[15]*B[0];
		C[16] += A[16]*B[0];
		C[17] += A[17]*B[0];
		C[18] += A[18]*B[0];
		C[19] += A[19]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 2)
	 */
	protected final static void gp_default_3_1_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]+A[1]*B[2]+A[10]*B[1]+A[4]*B[0]);
		C[1] += (-A[0]*B[5]+A[11]*B[1]+A[2]*B[2]+A[5]*B[0]);
		C[2] += (A[0]*B[4]+A[12]*B[1]+A[3]*B[2]+A[6]*B[0]);
		C[3] += (-A[1]*B[5]+A[13]*B[1]-A[2]*B[3]+A[7]*B[0]);
		C[4] += (A[1]*B[4]+A[14]*B[1]-A[3]*B[3]+A[8]*B[0]);
		C[5] += (A[15]*B[1]+A[2]*B[4]+A[3]*B[5]+A[9]*B[0]);
		C[6] += (A[16]*B[1]-A[4]*B[5]-A[5]*B[3]-A[7]*B[2]);
		C[7] += (A[17]*B[1]+A[4]*B[4]-A[6]*B[3]-A[8]*B[2]);
		C[8] += (A[18]*B[1]+A[5]*B[4]+A[6]*B[5]-A[9]*B[2]);
		C[9] += (A[19]*B[1]+A[7]*B[4]+A[8]*B[5]+A[9]*B[3]);
		C[10] += (-A[10]*B[5]-A[11]*B[3]-A[13]*B[2]-A[16]*B[0]);
		C[11] += (A[10]*B[4]-A[12]*B[3]-A[14]*B[2]-A[17]*B[0]);
		C[12] += (A[11]*B[4]+A[12]*B[5]-A[15]*B[2]-A[18]*B[0]);
		C[13] += (A[13]*B[4]+A[14]*B[5]+A[15]*B[3]-A[19]*B[0]);
		C[14] += (A[16]*B[4]+A[17]*B[5]+A[18]*B[3]+A[19]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 4)
	 */
	protected final static void gp_default_3_1_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]-A[1]*B[2]+A[2]*B[1]-A[3]*B[0]);
		C[1] += (A[0]*B[4]-A[4]*B[2]+A[5]*B[1]-A[6]*B[0]);
		C[2] += (A[1]*B[4]-A[4]*B[3]+A[7]*B[1]-A[8]*B[0]);
		C[3] += (A[2]*B[4]-A[5]*B[3]+A[7]*B[2]-A[9]*B[0]);
		C[4] += (A[3]*B[4]-A[6]*B[3]+A[8]*B[2]-A[9]*B[1]);
		C[5] += (A[0]*B[5]-A[10]*B[2]+A[11]*B[1]-A[12]*B[0]);
		C[6] += (A[1]*B[5]-A[10]*B[3]+A[13]*B[1]-A[14]*B[0]);
		C[7] += (-A[11]*B[3]+A[13]*B[2]-A[15]*B[0]+A[2]*B[5]);
		C[8] += (-A[12]*B[3]+A[14]*B[2]-A[15]*B[1]+A[3]*B[5]);
		C[9] += (-A[10]*B[4]+A[16]*B[1]-A[17]*B[0]+A[4]*B[5]);
		C[10] += (-A[11]*B[4]+A[16]*B[2]-A[18]*B[0]+A[5]*B[5]);
		C[11] += (-A[12]*B[4]+A[17]*B[2]-A[18]*B[1]+A[6]*B[5]);
		C[12] += (-A[13]*B[4]+A[16]*B[3]-A[19]*B[0]+A[7]*B[5]);
		C[13] += (-A[14]*B[4]+A[17]*B[3]-A[19]*B[1]+A[8]*B[5]);
		C[14] += (-A[15]*B[4]+A[18]*B[3]-A[19]*B[2]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 1)
	 */
	protected final static void gp_default_3_2_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[13]+A[1]*B[12]+A[10]*B[11]+A[11]*B[4]+A[13]*B[2]-A[16]*B[0]+A[2]*B[5]+A[4]*B[10]+A[5]*B[3]+A[7]*B[1]);
		C[1] += (-A[0]*B[9]-A[1]*B[8]-A[10]*B[7]+A[12]*B[4]+A[14]*B[2]-A[17]*B[0]+A[3]*B[5]-A[4]*B[6]+A[6]*B[3]+A[8]*B[1]);
		C[2] += (-A[0]*B[14]-A[11]*B[7]-A[12]*B[11]+A[15]*B[2]-A[18]*B[0]-A[2]*B[8]-A[3]*B[12]-A[5]*B[6]-A[6]*B[10]+A[9]*B[1]);
		C[3] += (-A[1]*B[14]-A[13]*B[7]-A[14]*B[11]-A[15]*B[4]-A[19]*B[0]+A[2]*B[9]+A[3]*B[13]-A[7]*B[6]-A[8]*B[10]-A[9]*B[3]);
		C[4] += (-A[16]*B[7]-A[17]*B[11]-A[18]*B[4]-A[19]*B[2]-A[4]*B[14]+A[5]*B[9]+A[6]*B[13]+A[7]*B[8]+A[8]*B[12]+A[9]*B[5]);
		C[5] += (-A[10]*B[14]+A[11]*B[9]+A[12]*B[13]+A[13]*B[8]+A[14]*B[12]+A[15]*B[5]+A[16]*B[6]+A[17]*B[10]+A[18]*B[3]+A[19]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 3)
	 */
	protected final static void gp_default_3_2_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[11]-A[0]*B[5]-A[0]*B[6]+A[10]*B[2]-A[12]*B[0]+A[2]*B[2]-A[3]*B[1]+A[4]*B[1]-A[5]*B[0]);
		C[1] += (-A[1]*B[11]+A[1]*B[5]-A[1]*B[6]+A[10]*B[4]-A[14]*B[0]-A[2]*B[4]+A[3]*B[3]+A[4]*B[3]-A[7]*B[0]);
		C[2] += (A[0]*B[13]-A[1]*B[12]+A[11]*B[4]-A[13]*B[2]-A[15]*B[0]-A[2]*B[6]-A[3]*B[10]+A[5]*B[3]-A[7]*B[1]);
		C[3] += (-A[0]*B[9]+A[1]*B[8]+A[12]*B[4]-A[14]*B[2]-A[2]*B[7]-A[3]*B[11]+A[6]*B[3]-A[8]*B[1]+A[9]*B[0]);
		C[4] += (A[0]*B[9]+A[1]*B[8]+A[10]*B[7]-A[17]*B[0]-A[4]*B[11]-A[5]*B[4]+A[6]*B[3]-A[7]*B[2]+A[8]*B[1]);
		C[5] += (A[0]*B[14]+A[11]*B[7]-A[16]*B[2]-A[18]*B[0]+A[2]*B[8]-A[4]*B[12]-A[5]*B[5]-A[6]*B[10]+A[9]*B[1]);
		C[6] += (A[12]*B[7]-A[17]*B[2]+A[3]*B[8]+A[4]*B[8]-A[5]*B[7]-A[6]*B[11]-A[6]*B[5]+A[6]*B[6]+A[9]*B[2]);
		C[7] += (A[1]*B[14]+A[13]*B[7]-A[16]*B[4]-A[19]*B[0]-A[2]*B[9]-A[4]*B[13]+A[7]*B[5]-A[8]*B[10]-A[9]*B[3]);
		C[8] += (A[14]*B[7]-A[17]*B[4]-A[3]*B[9]+A[4]*B[9]-A[7]*B[7]-A[8]*B[11]+A[8]*B[5]+A[8]*B[6]-A[9]*B[4]);
		C[9] += (A[15]*B[7]-A[18]*B[4]+A[19]*B[2]-A[3]*B[14]+A[5]*B[9]+A[6]*B[13]-A[7]*B[8]-A[8]*B[12]+A[9]*B[6]);
		C[10] += (A[0]*B[13]+A[1]*B[12]-A[10]*B[6]-A[11]*B[4]+A[12]*B[3]-A[13]*B[2]+A[14]*B[1]+A[16]*B[0]+A[4]*B[10]);
		C[11] += (-A[10]*B[12]+A[11]*B[11]-A[11]*B[5]-A[11]*B[6]-A[12]*B[10]+A[15]*B[1]+A[16]*B[1]+A[2]*B[12]+A[5]*B[10]);
		C[12] += (A[0]*B[14]+A[10]*B[8]-A[11]*B[7]-A[12]*B[5]+A[15]*B[2]+A[17]*B[1]-A[18]*B[0]+A[3]*B[12]+A[6]*B[10]);
		C[13] += (-A[10]*B[13]+A[13]*B[11]+A[13]*B[5]-A[13]*B[6]-A[14]*B[10]-A[15]*B[3]+A[16]*B[3]-A[2]*B[13]+A[7]*B[10]);
		C[14] += (A[1]*B[14]+A[10]*B[9]-A[13]*B[7]+A[14]*B[5]-A[15]*B[4]+A[17]*B[3]-A[19]*B[0]-A[3]*B[13]+A[8]*B[10]);
		C[15] += (A[11]*B[9]+A[12]*B[13]-A[13]*B[8]-A[14]*B[12]+A[15]*B[11]+A[18]*B[3]-A[19]*B[1]+A[2]*B[14]+A[9]*B[10]);
		C[16] += (-A[10]*B[14]+A[11]*B[9]+A[13]*B[8]+A[16]*B[11]-A[17]*B[10]-A[18]*B[3]-A[19]*B[1]-A[5]*B[13]-A[7]*B[12]);
		C[17] += (A[12]*B[9]+A[14]*B[8]-A[16]*B[7]+A[17]*B[6]-A[18]*B[4]-A[19]*B[2]+A[4]*B[14]-A[6]*B[13]-A[8]*B[12]);
		C[18] += (A[12]*B[14]+A[15]*B[8]-A[16]*B[8]-A[17]*B[12]+A[18]*B[11]-A[18]*B[5]+A[18]*B[6]+A[5]*B[14]-A[9]*B[12]);
		C[19] += (A[14]*B[14]-A[15]*B[9]-A[16]*B[9]-A[17]*B[13]+A[19]*B[11]+A[19]*B[5]+A[19]*B[6]+A[7]*B[14]+A[9]*B[13]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 5)
	 */
	protected final static void gp_default_3_2_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[9]-A[1]*B[8]+A[2]*B[7]-A[3]*B[6]+A[4]*B[5]-A[5]*B[4]+A[6]*B[3]+A[7]*B[2]-A[8]*B[1]+A[9]*B[0]);
		C[1] += (A[0]*B[13]-A[1]*B[12]+A[10]*B[5]-A[11]*B[4]+A[12]*B[3]+A[13]*B[2]-A[14]*B[1]+A[15]*B[0]+A[2]*B[11]-A[3]*B[10]);
		C[2] += (A[0]*B[14]+A[10]*B[8]-A[11]*B[7]+A[12]*B[6]+A[16]*B[2]-A[17]*B[1]+A[18]*B[0]-A[4]*B[12]+A[5]*B[11]-A[6]*B[10]);
		C[3] += (A[1]*B[14]+A[10]*B[9]-A[13]*B[7]+A[14]*B[6]+A[16]*B[4]-A[17]*B[3]+A[19]*B[0]-A[4]*B[13]+A[7]*B[11]-A[8]*B[10]);
		C[4] += (A[11]*B[9]-A[13]*B[8]+A[15]*B[6]+A[16]*B[5]-A[18]*B[3]+A[19]*B[1]+A[2]*B[14]-A[5]*B[13]+A[7]*B[12]-A[9]*B[10]);
		C[5] += (A[12]*B[9]-A[14]*B[8]+A[15]*B[7]+A[17]*B[5]-A[18]*B[4]+A[19]*B[2]+A[3]*B[14]-A[6]*B[13]+A[8]*B[12]-A[9]*B[11]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 0)
	 */
	protected final static void gp_default_3_3_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[19]-A[1]*B[18]-A[10]*B[17]+A[11]*B[8]+A[12]*B[14]+A[13]*B[6]+A[14]*B[12]+A[15]*B[3]-A[16]*B[4]-A[17]*B[10]-A[18]*B[1]-A[19]*B[0]+A[2]*B[9]+A[3]*B[15]-A[4]*B[16]+A[5]*B[7]+A[6]*B[13]+A[7]*B[5]+A[8]*B[11]+A[9]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 2)
	 */
	protected final static void gp_default_3_3_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]+A[0]*B[7]+A[1]*B[12]+A[1]*B[5]+A[10]*B[4]-A[12]*B[1]-A[14]*B[0]+A[2]*B[3]-A[3]*B[2]-A[4]*B[10]-A[5]*B[1]-A[7]*B[0]);
		C[1] += (A[0]*B[15]+A[0]*B[16]-A[10]*B[12]-A[11]*B[3]+A[11]*B[4]+A[12]*B[10]-A[15]*B[0]-A[16]*B[0]+A[2]*B[5]+A[3]*B[11]-A[4]*B[11]-A[5]*B[2]);
		C[2] += (A[0]*B[17]-A[0]*B[9]+A[10]*B[6]-A[12]*B[3]-A[17]*B[0]+A[2]*B[6]+A[3]*B[12]+A[4]*B[5]-A[5]*B[4]-A[6]*B[10]-A[6]*B[2]+A[9]*B[0]);
		C[3] += (-A[1]*B[15]+A[1]*B[16]-A[10]*B[14]+A[13]*B[3]+A[13]*B[4]+A[14]*B[10]+A[15]*B[1]-A[16]*B[1]-A[2]*B[7]-A[3]*B[13]-A[4]*B[13]+A[7]*B[2]);
		C[4] += (A[1]*B[17]+A[1]*B[9]+A[10]*B[8]+A[14]*B[3]-A[17]*B[1]-A[2]*B[8]-A[3]*B[14]+A[4]*B[7]-A[7]*B[4]-A[8]*B[10]+A[8]*B[2]-A[9]*B[1]);
		C[5] += (-A[0]*B[19]+A[1]*B[18]+A[11]*B[8]+A[12]*B[14]-A[13]*B[6]-A[14]*B[12]-A[18]*B[1]+A[19]*B[0]+A[5]*B[7]+A[6]*B[13]-A[7]*B[5]-A[8]*B[11]);
		C[6] += (-A[0]*B[19]-A[1]*B[18]-A[10]*B[17]+A[11]*B[8]+A[13]*B[6]+A[17]*B[10]+A[18]*B[1]+A[19]*B[0]+A[2]*B[9]-A[6]*B[13]-A[8]*B[11]-A[9]*B[2]);
		C[7] += (A[12]*B[8]+A[14]*B[6]-A[17]*B[4]+A[3]*B[9]+A[4]*B[17]-A[5]*B[8]-A[6]*B[14]+A[6]*B[7]-A[7]*B[6]-A[8]*B[12]+A[8]*B[5]-A[9]*B[3]);
		C[8] += (A[12]*B[17]+A[15]*B[6]-A[16]*B[6]-A[17]*B[12]-A[18]*B[3]-A[18]*B[4]+A[3]*B[18]+A[4]*B[18]-A[5]*B[9]-A[6]*B[15]+A[6]*B[16]+A[9]*B[5]);
		C[9] += (A[14]*B[17]-A[15]*B[8]-A[16]*B[8]-A[17]*B[14]+A[19]*B[3]-A[19]*B[4]-A[3]*B[19]+A[4]*B[19]+A[7]*B[9]+A[8]*B[15]+A[8]*B[16]-A[9]*B[7]);
		C[10] += (A[10]*B[16]+A[11]*B[14]-A[11]*B[7]-A[12]*B[13]+A[13]*B[12]-A[13]*B[5]-A[14]*B[11]-A[15]*B[2]-A[16]*B[10]+A[2]*B[15]+A[5]*B[13]+A[7]*B[11]);
		C[11] += (-A[0]*B[19]-A[1]*B[18]-A[11]*B[8]-A[13]*B[6]-A[15]*B[3]+A[16]*B[4]+A[18]*B[1]+A[19]*B[0]+A[3]*B[15]-A[4]*B[16]+A[6]*B[13]+A[8]*B[11]);
		C[12] += (A[10]*B[18]-A[11]*B[17]-A[11]*B[9]-A[12]*B[15]+A[15]*B[12]+A[16]*B[5]+A[17]*B[11]-A[18]*B[10]+A[18]*B[2]-A[2]*B[18]-A[5]*B[16]+A[9]*B[11]);
		C[13] += (A[10]*B[19]-A[13]*B[17]+A[13]*B[9]+A[14]*B[15]-A[15]*B[14]+A[16]*B[7]+A[17]*B[13]-A[19]*B[10]-A[19]*B[2]+A[2]*B[19]-A[7]*B[16]-A[9]*B[13]);
		C[14] += (A[12]*B[19]+A[14]*B[18]-A[15]*B[9]-A[16]*B[17]+A[17]*B[16]-A[18]*B[14]-A[18]*B[7]-A[19]*B[12]-A[19]*B[5]+A[5]*B[19]+A[7]*B[18]+A[9]*B[15]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 4)
	 */
	protected final static void gp_default_3_3_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]+A[0]*B[7]-A[1]*B[12]-A[1]*B[5]+A[10]*B[3]-A[12]*B[1]+A[14]*B[0]+A[2]*B[4]+A[3]*B[10]+A[4]*B[2]-A[5]*B[1]+A[7]*B[0]);
		C[1] += (A[0]*B[17]-A[0]*B[9]+A[10]*B[6]-A[12]*B[4]+A[17]*B[0]+A[2]*B[6]-A[3]*B[5]-A[4]*B[12]-A[5]*B[3]+A[6]*B[10]+A[6]*B[2]-A[9]*B[0]);
		C[2] += (A[1]*B[17]+A[1]*B[9]+A[10]*B[8]-A[14]*B[4]+A[17]*B[1]-A[2]*B[8]+A[3]*B[7]-A[4]*B[14]+A[7]*B[3]+A[8]*B[10]-A[8]*B[2]+A[9]*B[1]);
		C[3] += (-A[0]*B[19]+A[1]*B[18]+A[11]*B[8]-A[13]*B[6]-A[15]*B[4]+A[16]*B[3]+A[18]*B[1]-A[19]*B[0]+A[3]*B[16]-A[4]*B[15]-A[6]*B[13]+A[8]*B[11]);
		C[4] += (A[12]*B[8]-A[14]*B[6]+A[17]*B[3]+A[3]*B[17]+A[4]*B[9]-A[5]*B[8]-A[6]*B[14]+A[6]*B[7]+A[7]*B[6]+A[8]*B[12]-A[8]*B[5]+A[9]*B[4]);
		C[5] += (-A[0]*B[15]-A[0]*B[16]-A[10]*B[5]-A[11]*B[3]+A[11]*B[4]+A[12]*B[2]-A[15]*B[0]-A[16]*B[0]+A[2]*B[12]-A[3]*B[11]+A[4]*B[11]-A[5]*B[10]);
		C[6] += (A[1]*B[15]-A[1]*B[16]-A[10]*B[7]+A[13]*B[3]+A[13]*B[4]-A[14]*B[2]+A[15]*B[1]-A[16]*B[1]-A[2]*B[14]+A[3]*B[13]+A[4]*B[13]-A[7]*B[10]);
		C[7] += (-A[10]*B[15]+A[11]*B[14]-A[11]*B[7]-A[12]*B[13]-A[13]*B[12]+A[13]*B[5]+A[14]*B[11]-A[15]*B[10]-A[16]*B[2]-A[2]*B[16]+A[5]*B[13]-A[7]*B[11]);
		C[8] += (-A[0]*B[19]+A[1]*B[18]+A[10]*B[9]-A[11]*B[8]+A[13]*B[6]-A[17]*B[2]+A[18]*B[1]-A[19]*B[0]-A[2]*B[17]+A[6]*B[13]-A[8]*B[11]+A[9]*B[10]);
		C[9] += (A[0]*B[19]+A[1]*B[18]+A[11]*B[8]-A[12]*B[7]+A[13]*B[6]-A[14]*B[5]+A[18]*B[1]+A[19]*B[0]-A[5]*B[14]+A[6]*B[13]-A[7]*B[12]+A[8]*B[11]);
		C[10] += (-A[10]*B[18]+A[11]*B[17]+A[11]*B[9]-A[12]*B[16]-A[15]*B[5]-A[16]*B[12]+A[17]*B[11]-A[18]*B[10]+A[18]*B[2]+A[2]*B[18]-A[5]*B[15]+A[9]*B[11]);
		C[11] += (A[12]*B[9]-A[15]*B[6]+A[16]*B[6]-A[17]*B[5]+A[18]*B[3]+A[18]*B[4]+A[3]*B[18]+A[4]*B[18]-A[5]*B[17]-A[6]*B[15]+A[6]*B[16]+A[9]*B[12]);
		C[12] += (-A[10]*B[19]+A[13]*B[17]-A[13]*B[9]-A[14]*B[16]+A[15]*B[7]-A[16]*B[14]+A[17]*B[13]-A[19]*B[10]-A[19]*B[2]-A[2]*B[19]+A[7]*B[15]-A[9]*B[13]);
		C[13] += (-A[14]*B[9]+A[15]*B[8]+A[16]*B[8]-A[17]*B[7]-A[19]*B[3]+A[19]*B[4]-A[3]*B[19]+A[4]*B[19]-A[7]*B[17]+A[8]*B[15]+A[8]*B[16]-A[9]*B[14]);
		C[14] += (A[12]*B[19]-A[14]*B[18]+A[15]*B[17]+A[16]*B[9]+A[17]*B[15]-A[18]*B[14]-A[18]*B[7]+A[19]*B[12]+A[19]*B[5]+A[5]*B[19]-A[7]*B[18]+A[9]*B[16]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 6)
	 */
	protected final static void gp_default_3_3_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[19]-A[1]*B[18]-A[10]*B[9]+A[11]*B[8]-A[12]*B[7]-A[13]*B[6]+A[14]*B[5]-A[15]*B[4]+A[16]*B[3]-A[17]*B[2]+A[18]*B[1]-A[19]*B[0]+A[2]*B[17]-A[3]*B[16]+A[4]*B[15]-A[5]*B[14]+A[6]*B[13]+A[7]*B[12]-A[8]*B[11]+A[9]*B[10]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 1)
	 */
	protected final static void gp_default_3_4_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[12]+A[1]*B[10]+A[10]*B[9]-A[11]*B[2]-A[12]*B[6]-A[13]*B[1]-A[14]*B[5]-A[15]*B[0]-A[2]*B[3]-A[3]*B[7]);
		C[1] += (A[0]*B[13]+A[1]*B[11]-A[2]*B[4]-A[3]*B[8]-A[4]*B[9]+A[5]*B[2]+A[6]*B[6]+A[7]*B[1]+A[8]*B[5]+A[9]*B[0]);
		C[2] += (A[0]*B[14]-A[10]*B[11]+A[11]*B[4]+A[12]*B[8]+A[16]*B[1]+A[17]*B[5]+A[18]*B[0]-A[4]*B[10]+A[5]*B[3]+A[6]*B[7]);
		C[3] += (-A[1]*B[14]-A[10]*B[13]-A[13]*B[4]-A[14]*B[8]+A[16]*B[2]+A[17]*B[6]-A[19]*B[0]-A[4]*B[12]-A[7]*B[3]-A[8]*B[7]);
		C[4] += (-A[12]*B[13]-A[14]*B[11]+A[15]*B[4]+A[17]*B[9]-A[18]*B[2]-A[19]*B[1]-A[3]*B[14]-A[6]*B[12]-A[8]*B[10]+A[9]*B[3]);
		C[5] += (A[11]*B[13]+A[13]*B[11]+A[15]*B[8]-A[16]*B[9]-A[18]*B[6]-A[19]*B[5]+A[2]*B[14]+A[5]*B[12]+A[7]*B[10]+A[9]*B[7]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 3)
	 */
	protected final static void gp_default_3_4_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]+A[0]*B[8]-A[0]*B[9]-A[10]*B[1]+A[12]*B[0]-A[2]*B[1]-A[3]*B[5]+A[4]*B[5]+A[5]*B[0]);
		C[1] += (-A[1]*B[3]-A[1]*B[8]-A[1]*B[9]-A[10]*B[2]-A[14]*B[0]+A[2]*B[2]+A[3]*B[6]+A[4]*B[6]-A[7]*B[0]);
		C[2] += (A[0]*B[12]-A[1]*B[10]+A[10]*B[8]-A[11]*B[2]-A[12]*B[6]+A[13]*B[1]+A[14]*B[5]-A[16]*B[0]+A[4]*B[7]);
		C[3] += (A[0]*B[13]-A[1]*B[11]-A[10]*B[4]-A[17]*B[0]-A[4]*B[3]+A[5]*B[2]+A[6]*B[6]-A[7]*B[1]-A[8]*B[5]);
		C[4] += (-A[0]*B[13]-A[1]*B[11]-A[12]*B[2]-A[14]*B[1]+A[2]*B[4]-A[3]*B[3]+A[6]*B[6]+A[8]*B[5]+A[9]*B[0]);
		C[5] += (-A[0]*B[14]+A[10]*B[11]-A[11]*B[4]-A[12]*B[9]-A[15]*B[1]+A[17]*B[5]+A[18]*B[0]-A[3]*B[10]+A[6]*B[7]);
		C[6] += (-A[12]*B[4]-A[17]*B[1]-A[3]*B[11]-A[4]*B[11]+A[5]*B[4]-A[6]*B[3]+A[6]*B[8]+A[6]*B[9]+A[9]*B[1]);
		C[7] += (A[1]*B[14]+A[10]*B[13]+A[13]*B[4]-A[14]*B[9]+A[15]*B[2]+A[17]*B[6]-A[19]*B[0]+A[3]*B[12]-A[8]*B[7]);
		C[8] += (A[14]*B[4]-A[17]*B[2]+A[3]*B[13]-A[4]*B[13]-A[7]*B[4]+A[8]*B[3]-A[8]*B[8]+A[8]*B[9]-A[9]*B[2]);
		C[9] += (-A[12]*B[13]+A[14]*B[11]-A[16]*B[4]-A[17]*B[8]-A[18]*B[2]+A[19]*B[1]-A[4]*B[14]-A[6]*B[12]+A[8]*B[10]);
		C[10] += (A[0]*B[12]+A[1]*B[10]+A[11]*B[2]+A[13]*B[1]+A[15]*B[0]+A[2]*B[8]-A[3]*B[7]-A[5]*B[6]-A[7]*B[5]);
		C[11] += (-A[10]*B[10]+A[11]*B[3]-A[11]*B[8]+A[11]*B[9]+A[12]*B[7]-A[15]*B[5]-A[16]*B[5]+A[2]*B[10]-A[5]*B[7]);
		C[12] += (-A[0]*B[14]+A[11]*B[4]+A[16]*B[1]+A[18]*B[0]+A[2]*B[11]+A[4]*B[10]-A[5]*B[9]-A[6]*B[7]+A[9]*B[5]);
		C[13] += (-A[10]*B[12]-A[13]*B[3]+A[13]*B[8]+A[13]*B[9]-A[14]*B[7]+A[15]*B[6]-A[16]*B[6]-A[2]*B[12]+A[7]*B[7]);
		C[14] += (A[1]*B[14]-A[13]*B[4]+A[16]*B[2]-A[19]*B[0]-A[2]*B[13]+A[4]*B[12]-A[7]*B[9]+A[8]*B[7]-A[9]*B[6]);
		C[15] += (-A[10]*B[14]+A[11]*B[13]-A[13]*B[11]+A[16]*B[3]+A[17]*B[7]-A[18]*B[6]+A[19]*B[5]+A[5]*B[12]-A[7]*B[10]);
		C[16] += (A[11]*B[13]-A[12]*B[12]+A[13]*B[11]-A[14]*B[10]+A[15]*B[3]+A[18]*B[6]+A[19]*B[5]+A[2]*B[14]-A[9]*B[7]);
		C[17] += (A[15]*B[4]-A[18]*B[2]-A[19]*B[1]+A[3]*B[14]-A[5]*B[13]+A[6]*B[12]-A[7]*B[11]+A[8]*B[10]-A[9]*B[8]);
		C[18] += (-A[12]*B[14]+A[15]*B[11]-A[16]*B[11]+A[17]*B[10]-A[18]*B[3]-A[18]*B[8]-A[18]*B[9]-A[5]*B[14]+A[9]*B[10]);
		C[19] += (A[14]*B[14]-A[15]*B[13]-A[16]*B[13]+A[17]*B[12]+A[19]*B[3]+A[19]*B[8]-A[19]*B[9]+A[7]*B[14]-A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 5)
	 */
	protected final static void gp_default_3_4_5(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[13]+A[1]*B[11]+A[10]*B[4]-A[12]*B[2]+A[14]*B[1]-A[17]*B[0]-A[3]*B[9]-A[4]*B[8]+A[6]*B[6]-A[8]*B[5]);
		C[1] += (A[0]*B[12]-A[1]*B[10]-A[10]*B[3]+A[11]*B[2]-A[13]*B[1]+A[16]*B[0]+A[2]*B[9]+A[4]*B[7]-A[5]*B[6]+A[7]*B[5]);
		C[2] += (-A[0]*B[14]+A[11]*B[4]-A[12]*B[3]+A[15]*B[1]-A[18]*B[0]+A[2]*B[11]-A[3]*B[10]-A[5]*B[8]+A[6]*B[7]-A[9]*B[5]);
		C[3] += (A[1]*B[14]-A[13]*B[4]+A[14]*B[3]-A[15]*B[2]+A[19]*B[0]-A[2]*B[13]+A[3]*B[12]+A[7]*B[8]-A[8]*B[7]+A[9]*B[6]);
		C[4] += (-A[10]*B[14]+A[11]*B[13]-A[12]*B[12]-A[13]*B[11]+A[14]*B[10]-A[15]*B[9]+A[16]*B[8]-A[17]*B[7]+A[18]*B[6]-A[19]*B[5]);
		C[5] += (-A[16]*B[4]+A[17]*B[3]-A[18]*B[2]+A[19]*B[1]+A[4]*B[14]-A[5]*B[13]+A[6]*B[12]+A[7]*B[11]-A[8]*B[10]+A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 5 -> group 2)
	 */
	protected final static void gp_default_3_5_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[3]-A[1]*B[2]+A[2]*B[0]+A[3]*B[1]);
		C[1] += (-A[0]*B[4]+A[10]*B[2]-A[11]*B[0]-A[12]*B[1]);
		C[2] += (-A[0]*B[5]-A[4]*B[2]+A[5]*B[0]+A[6]*B[1]);
		C[3] += (A[1]*B[4]+A[10]*B[3]+A[13]*B[0]+A[14]*B[1]);
		C[4] += (A[1]*B[5]-A[4]*B[3]-A[7]*B[0]-A[8]*B[1]);
		C[5] += (-A[10]*B[5]-A[16]*B[0]-A[17]*B[1]-A[4]*B[4]);
		C[6] += (A[12]*B[3]+A[14]*B[2]-A[15]*B[0]+A[3]*B[4]);
		C[7] += (A[3]*B[5]-A[6]*B[3]-A[8]*B[2]+A[9]*B[0]);
		C[8] += (-A[12]*B[5]-A[17]*B[2]+A[18]*B[0]-A[6]*B[4]);
		C[9] += (A[14]*B[5]-A[17]*B[3]-A[19]*B[0]+A[8]*B[4]);
		C[10] += (-A[11]*B[3]-A[13]*B[2]-A[15]*B[1]-A[2]*B[4]);
		C[11] += (-A[2]*B[5]+A[5]*B[3]+A[7]*B[2]+A[9]*B[1]);
		C[12] += (A[11]*B[5]+A[16]*B[2]+A[18]*B[1]+A[5]*B[4]);
		C[13] += (-A[13]*B[5]+A[16]*B[3]-A[19]*B[1]-A[7]*B[4]);
		C[14] += (A[15]*B[5]-A[18]*B[3]-A[19]*B[2]+A[9]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 5 -> group 4)
	 */
	protected final static void gp_default_3_5_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[3]+A[1]*B[2]+A[10]*B[0]-A[4]*B[1]);
		C[1] += (-A[0]*B[5]+A[12]*B[0]+A[3]*B[2]-A[6]*B[1]);
		C[2] += (A[1]*B[5]-A[14]*B[0]-A[3]*B[3]+A[8]*B[1]);
		C[3] += (-A[10]*B[5]+A[12]*B[3]-A[14]*B[2]+A[17]*B[1]);
		C[4] += (-A[17]*B[0]+A[4]*B[5]-A[6]*B[3]+A[8]*B[2]);
		C[5] += (A[0]*B[4]-A[11]*B[0]-A[2]*B[2]+A[5]*B[1]);
		C[6] += (-A[1]*B[4]+A[13]*B[0]+A[2]*B[3]-A[7]*B[1]);
		C[7] += (A[10]*B[4]-A[11]*B[3]+A[13]*B[2]-A[16]*B[1]);
		C[8] += (A[16]*B[0]-A[4]*B[4]+A[5]*B[3]-A[7]*B[2]);
		C[9] += (-A[15]*B[0]+A[2]*B[5]-A[3]*B[4]+A[9]*B[1]);
		C[10] += (-A[11]*B[5]+A[12]*B[4]-A[15]*B[2]+A[18]*B[1]);
		C[11] += (-A[18]*B[0]+A[5]*B[5]-A[6]*B[4]+A[9]*B[2]);
		C[12] += (A[13]*B[5]-A[14]*B[4]+A[15]*B[3]-A[19]*B[1]);
		C[13] += (A[19]*B[0]-A[7]*B[5]+A[8]*B[4]-A[9]*B[3]);
		C[14] += (-A[16]*B[5]+A[17]*B[4]-A[18]*B[3]+A[19]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 6 -> group 3)
	 */
	protected final static void gp_default_3_6_3(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += -A[1]*B[0];
		C[2] += A[10]*B[0];
		C[3] += -A[4]*B[0];
		C[4] += -A[3]*B[0];
		C[5] += A[12]*B[0];
		C[6] += -A[6]*B[0];
		C[7] += -A[14]*B[0];
		C[8] += A[8]*B[0];
		C[9] += A[17]*B[0];
		C[10] += A[2]*B[0];
		C[11] += -A[11]*B[0];
		C[12] += A[5]*B[0];
		C[13] += A[13]*B[0];
		C[14] += -A[7]*B[0];
		C[15] += -A[16]*B[0];
		C[16] += -A[15]*B[0];
		C[17] += A[9]*B[0];
		C[18] += A[18]*B[0];
		C[19] += -A[19]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 0 -> group 4)
	 */
	protected final static void gp_default_4_0_4(float[] A, float[] B, float[] C) {
		gp_default_2_0_2(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 3)
	 */
	protected final static void gp_default_4_1_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]+A[1]*B[0]+A[5]*B[1]);
		C[1] += (-A[0]*B[3]+A[2]*B[0]+A[6]*B[1]);
		C[2] += (A[0]*B[5]+A[3]*B[0]+A[7]*B[1]);
		C[3] += (-A[0]*B[4]+A[4]*B[0]+A[8]*B[1]);
		C[4] += (-A[1]*B[3]-A[2]*B[2]+A[9]*B[1]);
		C[5] += (A[1]*B[5]+A[10]*B[1]-A[3]*B[2]);
		C[6] += (-A[1]*B[4]+A[11]*B[1]-A[4]*B[2]);
		C[7] += (A[12]*B[1]+A[2]*B[5]+A[3]*B[3]);
		C[8] += (A[13]*B[1]-A[2]*B[4]+A[4]*B[3]);
		C[9] += (A[14]*B[1]-A[3]*B[4]-A[4]*B[5]);
		C[10] += (-A[5]*B[3]-A[6]*B[2]-A[9]*B[0]);
		C[11] += (-A[10]*B[0]+A[5]*B[5]-A[7]*B[2]);
		C[12] += (-A[11]*B[0]-A[5]*B[4]-A[8]*B[2]);
		C[13] += (-A[12]*B[0]+A[6]*B[5]+A[7]*B[3]);
		C[14] += (-A[13]*B[0]-A[6]*B[4]+A[8]*B[3]);
		C[15] += (-A[14]*B[0]-A[7]*B[4]-A[8]*B[5]);
		C[16] += (A[10]*B[3]+A[12]*B[2]+A[9]*B[5]);
		C[17] += (A[11]*B[3]+A[13]*B[2]-A[9]*B[4]);
		C[18] += (-A[10]*B[4]-A[11]*B[5]+A[14]*B[2]);
		C[19] += (-A[12]*B[4]-A[13]*B[5]-A[14]*B[3]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 5)
	 */
	protected final static void gp_default_4_1_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]+A[4]*B[0]);
		C[1] += (A[0]*B[5]-A[5]*B[3]+A[6]*B[2]-A[7]*B[1]+A[8]*B[0]);
		C[2] += (A[1]*B[5]-A[10]*B[1]+A[11]*B[0]-A[5]*B[4]+A[9]*B[2]);
		C[3] += (-A[12]*B[1]+A[13]*B[0]+A[2]*B[5]-A[6]*B[4]+A[9]*B[3]);
		C[4] += (A[10]*B[3]-A[12]*B[2]+A[14]*B[0]+A[3]*B[5]-A[7]*B[4]);
		C[5] += (A[11]*B[3]-A[13]*B[2]+A[14]*B[1]+A[4]*B[5]-A[8]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 2)
	 */
	protected final static void gp_default_4_2_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]+A[1]*B[3]+A[2]*B[1]+A[5]*B[4]+A[6]*B[2]-A[9]*B[0]);
		C[1] += (-A[0]*B[12]-A[1]*B[10]-A[10]*B[0]+A[3]*B[1]-A[5]*B[11]+A[7]*B[2]);
		C[2] += (A[0]*B[8]+A[1]*B[6]-A[11]*B[0]+A[4]*B[1]+A[5]*B[7]+A[8]*B[2]);
		C[3] += (A[0]*B[13]-A[12]*B[0]-A[2]*B[10]-A[3]*B[3]-A[6]*B[11]-A[7]*B[4]);
		C[4] += (-A[0]*B[9]-A[13]*B[0]+A[2]*B[6]-A[4]*B[3]+A[6]*B[7]-A[8]*B[4]);
		C[5] += (-A[0]*B[14]-A[14]*B[0]+A[3]*B[6]+A[4]*B[10]+A[7]*B[7]+A[8]*B[11]);
		C[6] += (A[1]*B[13]-A[10]*B[4]-A[12]*B[2]+A[2]*B[12]+A[3]*B[5]-A[9]*B[11]);
		C[7] += (-A[1]*B[9]-A[11]*B[4]-A[13]*B[2]-A[2]*B[8]+A[4]*B[5]+A[9]*B[7]);
		C[8] += (-A[1]*B[14]+A[10]*B[7]+A[11]*B[11]-A[14]*B[2]-A[3]*B[8]-A[4]*B[12]);
		C[9] += (A[12]*B[7]+A[13]*B[11]+A[14]*B[4]-A[2]*B[14]+A[3]*B[9]+A[4]*B[13]);
		C[10] += (A[10]*B[3]+A[12]*B[1]+A[5]*B[13]+A[6]*B[12]+A[7]*B[5]+A[9]*B[10]);
		C[11] += (A[11]*B[3]+A[13]*B[1]-A[5]*B[9]-A[6]*B[8]+A[8]*B[5]-A[9]*B[6]);
		C[12] += (-A[10]*B[6]-A[11]*B[10]+A[14]*B[1]-A[5]*B[14]-A[7]*B[8]-A[8]*B[12]);
		C[13] += (-A[12]*B[6]-A[13]*B[10]-A[14]*B[3]-A[6]*B[14]+A[7]*B[9]+A[8]*B[13]);
		C[14] += (A[10]*B[9]+A[11]*B[13]+A[12]*B[8]+A[13]*B[12]+A[14]*B[5]-A[9]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 4)
	 */
	protected final static void gp_default_4_2_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[11]-A[0]*B[6]+A[1]*B[3]-A[2]*B[1]+A[3]*B[0]+A[5]*B[4]-A[6]*B[2]+A[8]*B[0]);
		C[1] += (A[0]*B[8]-A[1]*B[11]-A[1]*B[5]+A[11]*B[0]+A[3]*B[2]-A[4]*B[1]+A[5]*B[7]-A[9]*B[2]);
		C[2] += (-A[0]*B[9]+A[13]*B[0]-A[2]*B[11]+A[2]*B[5]-A[3]*B[4]+A[4]*B[3]+A[6]*B[7]-A[9]*B[4]);
		C[3] += (-A[0]*B[14]+A[1]*B[13]-A[10]*B[4]+A[12]*B[2]+A[14]*B[0]-A[2]*B[12]-A[4]*B[10]+A[7]*B[7]);
		C[4] += (-A[1]*B[9]-A[11]*B[4]+A[13]*B[2]+A[2]*B[8]-A[3]*B[7]-A[4]*B[11]+A[4]*B[6]+A[8]*B[7]);
		C[5] += (A[0]*B[12]+A[1]*B[10]-A[10]*B[0]-A[5]*B[5]-A[5]*B[6]+A[7]*B[2]-A[8]*B[1]+A[9]*B[1]);
		C[6] += (-A[0]*B[13]-A[12]*B[0]+A[2]*B[10]+A[6]*B[5]-A[6]*B[6]-A[7]*B[4]+A[8]*B[3]+A[9]*B[3]);
		C[7] += (A[10]*B[3]-A[12]*B[1]+A[3]*B[10]+A[5]*B[13]-A[6]*B[12]+A[7]*B[11]-A[7]*B[6]-A[8]*B[10]);
		C[8] += (-A[0]*B[14]+A[11]*B[3]-A[13]*B[1]+A[14]*B[0]+A[4]*B[10]-A[5]*B[9]+A[6]*B[8]-A[7]*B[7]);
		C[9] += (-A[1]*B[13]-A[10]*B[4]+A[11]*B[3]-A[12]*B[2]+A[13]*B[1]-A[2]*B[12]+A[5]*B[9]+A[6]*B[8]);
		C[10] += (A[10]*B[11]-A[10]*B[5]-A[11]*B[10]+A[14]*B[1]-A[3]*B[12]+A[5]*B[14]+A[7]*B[8]-A[9]*B[12]);
		C[11] += (-A[1]*B[14]-A[10]*B[7]-A[11]*B[5]+A[11]*B[6]+A[14]*B[2]-A[4]*B[12]+A[8]*B[8]+A[9]*B[8]);
		C[12] += (A[12]*B[11]+A[12]*B[5]-A[13]*B[10]-A[14]*B[3]+A[3]*B[13]+A[6]*B[14]-A[7]*B[9]-A[9]*B[13]);
		C[13] += (-A[12]*B[7]+A[13]*B[5]+A[13]*B[6]-A[14]*B[4]-A[2]*B[14]+A[4]*B[13]-A[8]*B[9]+A[9]*B[9]);
		C[14] += (A[10]*B[9]+A[11]*B[13]-A[12]*B[8]-A[13]*B[12]+A[14]*B[11]+A[14]*B[6]-A[3]*B[14]-A[8]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 6)
	 */
	protected final static void gp_default_4_2_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]-A[1]*B[13]-A[10]*B[4]+A[11]*B[3]+A[12]*B[2]-A[13]*B[1]+A[14]*B[0]+A[2]*B[12]-A[3]*B[11]+A[4]*B[10]+A[5]*B[9]-A[6]*B[8]+A[7]*B[7]-A[8]*B[6]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 1)
	 */
	protected final static void gp_default_4_3_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[15]+A[1]*B[13]-A[10]*B[1]-A[12]*B[0]+A[2]*B[11]+A[3]*B[2]+A[5]*B[14]+A[6]*B[12]+A[7]*B[3]-A[9]*B[10]);
		C[1] += (-A[0]*B[9]-A[1]*B[7]-A[11]*B[1]-A[13]*B[0]-A[2]*B[5]+A[4]*B[2]-A[5]*B[8]-A[6]*B[6]+A[8]*B[3]+A[9]*B[4]);
		C[2] += (-A[0]*B[18]-A[1]*B[16]+A[10]*B[4]+A[11]*B[10]-A[14]*B[0]-A[3]*B[5]-A[4]*B[11]-A[5]*B[17]-A[7]*B[6]-A[8]*B[12]);
		C[3] += (A[0]*B[19]+A[12]*B[4]+A[13]*B[10]+A[14]*B[1]-A[2]*B[16]+A[3]*B[7]+A[4]*B[13]-A[6]*B[17]+A[7]*B[8]+A[8]*B[14]);
		C[4] += (A[1]*B[19]+A[10]*B[8]+A[11]*B[14]+A[12]*B[6]+A[13]*B[12]+A[14]*B[3]+A[2]*B[18]-A[3]*B[9]-A[4]*B[15]-A[9]*B[17]);
		C[5] += (-A[10]*B[7]-A[11]*B[13]-A[12]*B[5]-A[13]*B[11]-A[14]*B[2]+A[5]*B[19]+A[6]*B[18]-A[7]*B[9]-A[8]*B[15]+A[9]*B[16]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 3)
	 */
	protected final static void gp_default_4_3_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[12]+A[0]*B[5]-A[1]*B[10]-A[1]*B[2]+A[3]*B[0]-A[5]*B[3]+A[5]*B[4]+A[8]*B[0]-A[9]*B[0]);
		C[1] += (-A[0]*B[14]-A[0]*B[7]-A[2]*B[10]+A[2]*B[2]-A[3]*B[1]+A[6]*B[3]+A[6]*B[4]-A[8]*B[1]-A[9]*B[1]);
		C[2] += (-A[0]*B[16]+A[1]*B[13]-A[10]*B[1]+A[12]*B[0]-A[2]*B[11]+A[5]*B[14]-A[6]*B[12]+A[7]*B[4]+A[8]*B[10]);
		C[3] += (-A[0]*B[17]-A[1]*B[7]-A[11]*B[1]+A[13]*B[0]+A[2]*B[5]-A[3]*B[4]-A[4]*B[10]-A[5]*B[8]+A[6]*B[6]);
		C[4] += (A[0]*B[9]-A[1]*B[14]-A[11]*B[1]-A[13]*B[0]-A[2]*B[12]-A[3]*B[3]+A[4]*B[2]+A[5]*B[8]+A[6]*B[6]);
		C[5] += (A[0]*B[18]-A[1]*B[15]-A[10]*B[3]+A[11]*B[10]-A[14]*B[0]-A[4]*B[11]+A[5]*B[17]+A[7]*B[6]-A[9]*B[12]);
		C[6] += (-A[1]*B[17]+A[1]*B[9]-A[11]*B[3]-A[11]*B[4]-A[3]*B[6]-A[4]*B[12]+A[4]*B[5]+A[8]*B[6]+A[9]*B[6]);
		C[7] += (-A[0]*B[19]+A[12]*B[3]+A[13]*B[10]+A[14]*B[1]+A[2]*B[15]+A[4]*B[13]+A[6]*B[17]-A[7]*B[8]-A[9]*B[14]);
		C[8] += (A[13]*B[3]-A[13]*B[4]-A[2]*B[17]-A[2]*B[9]+A[3]*B[8]+A[4]*B[14]-A[4]*B[7]-A[8]*B[8]+A[9]*B[8]);
		C[9] += (A[1]*B[19]+A[10]*B[8]+A[11]*B[14]-A[12]*B[6]-A[13]*B[12]-A[14]*B[4]-A[2]*B[18]-A[4]*B[16]-A[8]*B[17]);
		C[10] += (A[0]*B[15]+A[1]*B[13]+A[10]*B[1]+A[12]*B[0]+A[2]*B[11]-A[5]*B[7]-A[6]*B[5]-A[7]*B[3]+A[8]*B[2]);
		C[11] += (-A[10]*B[10]+A[10]*B[2]+A[3]*B[11]-A[5]*B[15]-A[5]*B[16]+A[7]*B[12]-A[7]*B[5]-A[8]*B[11]+A[9]*B[11]);
		C[12] += (A[0]*B[18]+A[1]*B[16]+A[10]*B[4]+A[11]*B[2]-A[14]*B[0]+A[4]*B[11]+A[5]*B[9]-A[7]*B[6]-A[9]*B[5]);
		C[13] += (-A[12]*B[10]-A[12]*B[2]-A[3]*B[13]+A[6]*B[15]-A[6]*B[16]-A[7]*B[14]+A[7]*B[7]+A[8]*B[13]+A[9]*B[13]);
		C[14] += (-A[0]*B[19]+A[12]*B[4]-A[13]*B[2]+A[14]*B[1]+A[2]*B[16]-A[4]*B[13]-A[6]*B[9]+A[7]*B[8]-A[9]*B[7]);
		C[15] += (-A[10]*B[7]-A[11]*B[13]+A[12]*B[5]+A[13]*B[11]-A[14]*B[10]+A[3]*B[16]+A[5]*B[19]-A[6]*B[18]+A[7]*B[17]);
		C[16] += (-A[10]*B[14]+A[11]*B[13]-A[12]*B[12]+A[13]*B[11]+A[14]*B[2]+A[3]*B[15]+A[5]*B[19]+A[6]*B[18]-A[7]*B[9]);
		C[17] += (-A[1]*B[19]+A[10]*B[8]-A[11]*B[7]+A[12]*B[6]-A[13]*B[5]+A[14]*B[3]-A[2]*B[18]+A[4]*B[15]-A[8]*B[9]);
		C[18] += (A[10]*B[17]+A[10]*B[9]+A[11]*B[15]-A[11]*B[16]-A[14]*B[12]-A[14]*B[5]-A[3]*B[18]-A[8]*B[18]-A[9]*B[18]);
		C[19] += (A[12]*B[17]-A[12]*B[9]-A[13]*B[15]-A[13]*B[16]+A[14]*B[14]+A[14]*B[7]+A[3]*B[19]+A[8]*B[19]-A[9]*B[19]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 5)
	 */
	protected final static void gp_default_4_3_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[17]-A[1]*B[14]-A[11]*B[1]+A[13]*B[0]+A[2]*B[12]-A[4]*B[10]+A[5]*B[8]-A[6]*B[6]+A[8]*B[4]+A[9]*B[3]);
		C[1] += (-A[0]*B[16]+A[1]*B[13]+A[10]*B[1]-A[12]*B[0]-A[2]*B[11]+A[3]*B[10]-A[5]*B[7]+A[6]*B[5]-A[7]*B[4]-A[9]*B[2]);
		C[2] += (A[0]*B[18]-A[1]*B[15]+A[10]*B[3]-A[11]*B[2]+A[14]*B[0]+A[3]*B[12]-A[4]*B[11]+A[5]*B[9]-A[7]*B[6]+A[8]*B[5]);
		C[3] += (-A[0]*B[19]-A[12]*B[3]+A[13]*B[2]-A[14]*B[1]+A[2]*B[15]-A[3]*B[14]+A[4]*B[13]-A[6]*B[9]+A[7]*B[8]-A[8]*B[7]);
		C[4] += (-A[10]*B[14]+A[11]*B[13]+A[12]*B[12]-A[13]*B[11]+A[14]*B[10]+A[5]*B[19]-A[6]*B[18]+A[7]*B[17]-A[8]*B[16]+A[9]*B[15]);
		C[5] += (-A[1]*B[19]+A[10]*B[8]-A[11]*B[7]-A[12]*B[6]+A[13]*B[5]-A[14]*B[4]+A[2]*B[18]-A[3]*B[17]+A[4]*B[16]-A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 0)
	 */
	protected final static void gp_default_4_4_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[14]-A[1]*B[12]-A[10]*B[2]-A[11]*B[6]-A[12]*B[1]-A[13]*B[5]-A[14]*B[0]-A[2]*B[10]+A[3]*B[3]+A[4]*B[7]-A[5]*B[13]-A[6]*B[11]+A[7]*B[4]+A[8]*B[8]+A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 2)
	 */
	protected final static void gp_default_4_4_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[3]-A[0]*B[8]+A[1]*B[6]+A[2]*B[5]+A[3]*B[0]-A[5]*B[2]-A[6]*B[1]+A[8]*B[0]);
		C[1] += (-A[0]*B[10]+A[1]*B[7]+A[10]*B[0]+A[5]*B[8]-A[5]*B[9]-A[7]*B[1]-A[8]*B[5]+A[9]*B[5]);
		C[2] += (-A[0]*B[11]-A[1]*B[3]+A[1]*B[9]+A[11]*B[0]+A[3]*B[1]+A[4]*B[5]-A[5]*B[4]-A[9]*B[1]);
		C[3] += (A[0]*B[12]-A[12]*B[0]-A[2]*B[7]-A[6]*B[8]-A[6]*B[9]+A[7]*B[2]+A[8]*B[6]+A[9]*B[6]);
		C[4] += (A[0]*B[13]-A[13]*B[0]+A[2]*B[3]+A[2]*B[9]-A[3]*B[2]-A[4]*B[6]+A[6]*B[4]-A[9]*B[2]);
		C[5] += (-A[1]*B[12]-A[10]*B[2]-A[11]*B[6]+A[12]*B[1]+A[13]*B[5]+A[2]*B[10]-A[5]*B[13]+A[6]*B[11]);
		C[6] += (-A[0]*B[14]+A[11]*B[6]+A[13]*B[5]+A[14]*B[0]-A[4]*B[7]-A[5]*B[13]-A[6]*B[11]+A[7]*B[4]);
		C[7] += (A[1]*B[13]-A[11]*B[2]-A[13]*B[1]+A[2]*B[11]-A[3]*B[4]+A[4]*B[3]-A[4]*B[8]+A[8]*B[4]);
		C[8] += (A[1]*B[14]-A[10]*B[4]-A[11]*B[8]-A[11]*B[9]-A[14]*B[1]+A[4]*B[10]+A[8]*B[11]+A[9]*B[11]);
		C[9] += (A[12]*B[4]+A[13]*B[8]-A[13]*B[9]+A[14]*B[2]-A[2]*B[14]-A[4]*B[12]-A[8]*B[13]+A[9]*B[13]);
		C[10] += (-A[10]*B[6]-A[12]*B[5]+A[3]*B[7]+A[5]*B[12]+A[6]*B[10]-A[7]*B[3]+A[7]*B[8]-A[8]*B[7]);
		C[11] += (-A[0]*B[14]-A[1]*B[12]+A[10]*B[2]+A[12]*B[1]+A[14]*B[0]-A[2]*B[10]+A[4]*B[7]-A[7]*B[4]);
		C[12] += (A[10]*B[3]+A[10]*B[9]+A[11]*B[7]-A[14]*B[5]-A[3]*B[10]+A[5]*B[14]-A[7]*B[11]-A[9]*B[10]);
		C[13] += (-A[12]*B[3]+A[12]*B[9]-A[13]*B[7]+A[14]*B[6]+A[3]*B[12]-A[6]*B[14]+A[7]*B[13]-A[9]*B[12]);
		C[14] += (A[10]*B[13]-A[11]*B[12]+A[12]*B[11]-A[13]*B[10]+A[14]*B[3]+A[14]*B[8]-A[3]*B[14]-A[8]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 4)
	 */
	protected final static void gp_default_4_4_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[9]+A[1]*B[6]-A[2]*B[5]-A[5]*B[2]+A[6]*B[1]-A[9]*B[0]);
		C[1] += (-A[0]*B[11]+A[1]*B[8]-A[11]*B[0]-A[4]*B[5]-A[5]*B[4]+A[8]*B[1]);
		C[2] += (A[0]*B[13]+A[13]*B[0]-A[2]*B[8]+A[4]*B[6]+A[6]*B[4]-A[8]*B[2]);
		C[3] += (A[11]*B[6]-A[13]*B[5]-A[5]*B[13]+A[6]*B[11]-A[8]*B[9]-A[9]*B[8]);
		C[4] += (A[1]*B[13]-A[11]*B[2]+A[13]*B[1]-A[2]*B[11]+A[4]*B[9]+A[9]*B[4]);
		C[5] += (A[0]*B[10]-A[1]*B[7]+A[10]*B[0]+A[3]*B[5]+A[5]*B[3]-A[7]*B[1]);
		C[6] += (-A[0]*B[12]-A[12]*B[0]+A[2]*B[7]-A[3]*B[6]-A[6]*B[3]+A[7]*B[2]);
		C[7] += (-A[10]*B[6]+A[12]*B[5]+A[5]*B[12]-A[6]*B[10]+A[7]*B[9]+A[9]*B[7]);
		C[8] += (-A[1]*B[12]+A[10]*B[2]-A[12]*B[1]+A[2]*B[10]-A[3]*B[9]-A[9]*B[3]);
		C[9] += (A[0]*B[14]+A[14]*B[0]-A[3]*B[8]+A[4]*B[7]+A[7]*B[4]-A[8]*B[3]);
		C[10] += (-A[10]*B[8]+A[11]*B[7]-A[14]*B[5]-A[5]*B[14]+A[7]*B[11]-A[8]*B[10]);
		C[11] += (A[1]*B[14]+A[10]*B[4]-A[11]*B[3]+A[14]*B[1]-A[3]*B[11]+A[4]*B[10]);
		C[12] += (A[12]*B[8]-A[13]*B[7]+A[14]*B[6]+A[6]*B[14]-A[7]*B[13]+A[8]*B[12]);
		C[13] += (-A[12]*B[4]+A[13]*B[3]-A[14]*B[2]-A[2]*B[14]+A[3]*B[13]-A[4]*B[12]);
		C[14] += (A[10]*B[13]-A[11]*B[12]-A[12]*B[11]+A[13]*B[10]-A[14]*B[9]-A[9]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 5 -> group 1)
	 */
	protected final static void gp_default_4_5_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[4]-A[5]*B[3]-A[6]*B[2]+A[7]*B[0]+A[8]*B[1]);
		C[1] += (-A[0]*B[5]+A[1]*B[3]+A[2]*B[2]-A[3]*B[0]-A[4]*B[1]);
		C[2] += (A[1]*B[4]-A[10]*B[0]-A[11]*B[1]+A[5]*B[5]+A[9]*B[2]);
		C[3] += (A[12]*B[0]+A[13]*B[1]-A[2]*B[4]-A[6]*B[5]+A[9]*B[3]);
		C[4] += (A[11]*B[3]+A[13]*B[2]-A[14]*B[0]-A[4]*B[4]-A[8]*B[5]);
		C[5] += (-A[10]*B[3]-A[12]*B[2]-A[14]*B[1]+A[3]*B[4]+A[7]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 5 -> group 3)
	 */
	protected final static void gp_default_4_5_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[2]+A[1]*B[1]-A[5]*B[0]);
		C[1] += (A[0]*B[3]-A[2]*B[1]+A[6]*B[0]);
		C[2] += (-A[5]*B[3]+A[6]*B[2]-A[9]*B[1]);
		C[3] += (A[1]*B[3]-A[2]*B[2]+A[9]*B[0]);
		C[4] += (A[0]*B[5]-A[4]*B[1]+A[8]*B[0]);
		C[5] += (-A[11]*B[1]-A[5]*B[5]+A[8]*B[2]);
		C[6] += (A[1]*B[5]+A[11]*B[0]-A[4]*B[2]);
		C[7] += (A[13]*B[1]+A[6]*B[5]-A[8]*B[3]);
		C[8] += (-A[13]*B[0]-A[2]*B[5]+A[4]*B[3]);
		C[9] += (A[11]*B[3]-A[13]*B[2]-A[9]*B[5]);
		C[10] += (-A[0]*B[4]+A[3]*B[1]-A[7]*B[0]);
		C[11] += (A[10]*B[1]+A[5]*B[4]-A[7]*B[2]);
		C[12] += (-A[1]*B[4]-A[10]*B[0]+A[3]*B[2]);
		C[13] += (-A[12]*B[1]-A[6]*B[4]+A[7]*B[3]);
		C[14] += (A[12]*B[0]+A[2]*B[4]-A[3]*B[3]);
		C[15] += (-A[10]*B[3]+A[12]*B[2]+A[9]*B[4]);
		C[16] += (A[14]*B[1]+A[7]*B[5]-A[8]*B[4]);
		C[17] += (-A[14]*B[0]-A[3]*B[5]+A[4]*B[4]);
		C[18] += (-A[10]*B[5]+A[11]*B[4]-A[14]*B[2]);
		C[19] += (A[12]*B[5]-A[13]*B[4]+A[14]*B[3]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 6 -> group 2)
	 */
	protected final static void gp_default_4_6_2(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
		C[1] += A[5]*B[0];
		C[2] += -A[1]*B[0];
		C[3] += -A[6]*B[0];
		C[4] += A[2]*B[0];
		C[5] += A[9]*B[0];
		C[6] += -A[8]*B[0];
		C[7] += A[4]*B[0];
		C[8] += A[11]*B[0];
		C[9] += -A[13]*B[0];
		C[10] += A[7]*B[0];
		C[11] += -A[3]*B[0];
		C[12] += -A[10]*B[0];
		C[13] += A[12]*B[0];
		C[14] += -A[14]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 0 -> group 5)
	 */
	protected final static void gp_default_5_0_5(float[] A, float[] B, float[] C) {
		gp_default_1_0_1(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 1 -> group 4)
	 */
	protected final static void gp_default_5_1_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[0]+A[1]*B[1]);
		C[1] += (-A[0]*B[2]+A[2]*B[1]);
		C[2] += (A[0]*B[3]+A[3]*B[1]);
		C[3] += (-A[0]*B[5]+A[4]*B[1]);
		C[4] += (A[0]*B[4]+A[5]*B[1]);
		C[5] += (-A[1]*B[2]-A[2]*B[0]);
		C[6] += (A[1]*B[3]-A[3]*B[0]);
		C[7] += (-A[1]*B[5]-A[4]*B[0]);
		C[8] += (A[1]*B[4]-A[5]*B[0]);
		C[9] += (A[2]*B[3]+A[3]*B[2]);
		C[10] += (-A[2]*B[5]+A[4]*B[2]);
		C[11] += (A[2]*B[4]+A[5]*B[2]);
		C[12] += (-A[3]*B[5]-A[4]*B[3]);
		C[13] += (A[3]*B[4]-A[5]*B[3]);
		C[14] += (A[4]*B[4]+A[5]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 1 -> group 6)
	 */
	protected final static void gp_default_5_1_6(float[] A, float[] B, float[] C) {
		gp_default_1_5_6(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 2 -> group 3)
	 */
	protected final static void gp_default_5_2_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[1]+A[1]*B[2]-A[2]*B[0]);
		C[1] += (-A[0]*B[3]-A[1]*B[4]-A[3]*B[0]);
		C[2] += (A[0]*B[10]+A[1]*B[11]-A[4]*B[0]);
		C[3] += (-A[0]*B[6]-A[1]*B[7]-A[5]*B[0]);
		C[4] += (A[0]*B[5]-A[2]*B[4]-A[3]*B[2]);
		C[5] += (-A[0]*B[12]+A[2]*B[11]-A[4]*B[2]);
		C[6] += (A[0]*B[8]-A[2]*B[7]-A[5]*B[2]);
		C[7] += (A[0]*B[13]+A[3]*B[11]+A[4]*B[4]);
		C[8] += (-A[0]*B[9]-A[3]*B[7]+A[5]*B[4]);
		C[9] += (-A[0]*B[14]-A[4]*B[7]-A[5]*B[11]);
		C[10] += (A[1]*B[5]+A[2]*B[3]+A[3]*B[1]);
		C[11] += (-A[1]*B[12]-A[2]*B[10]+A[4]*B[1]);
		C[12] += (A[1]*B[8]+A[2]*B[6]+A[5]*B[1]);
		C[13] += (A[1]*B[13]-A[3]*B[10]-A[4]*B[3]);
		C[14] += (-A[1]*B[9]+A[3]*B[6]-A[5]*B[3]);
		C[15] += (-A[1]*B[14]+A[4]*B[6]+A[5]*B[10]);
		C[16] += (A[2]*B[13]+A[3]*B[12]+A[4]*B[5]);
		C[17] += (-A[2]*B[9]-A[3]*B[8]+A[5]*B[5]);
		C[18] += (-A[2]*B[14]-A[4]*B[8]-A[5]*B[12]);
		C[19] += (-A[3]*B[14]+A[4]*B[9]+A[5]*B[13]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 2 -> group 5)
	 */
	protected final static void gp_default_5_2_5(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[11]+A[1]*B[7]-A[2]*B[4]+A[3]*B[2]-A[5]*B[0]);
		C[1] += (A[0]*B[10]-A[1]*B[6]+A[2]*B[3]-A[3]*B[1]+A[4]*B[0]);
		C[2] += (-A[0]*B[12]+A[1]*B[8]-A[2]*B[5]+A[4]*B[2]-A[5]*B[1]);
		C[3] += (A[0]*B[13]-A[1]*B[9]+A[3]*B[5]-A[4]*B[4]+A[5]*B[3]);
		C[4] += (-A[1]*B[14]+A[2]*B[13]-A[3]*B[12]+A[4]*B[11]-A[5]*B[10]);
		C[5] += (A[0]*B[14]-A[2]*B[9]+A[3]*B[8]-A[4]*B[7]+A[5]*B[6]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 3 -> group 2)
	 */
	protected final static void gp_default_5_3_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]+A[1]*B[3]-A[2]*B[1]-A[3]*B[0]);
		C[1] += (-A[0]*B[11]-A[1]*B[12]+A[2]*B[10]-A[4]*B[0]);
		C[2] += (A[0]*B[5]+A[1]*B[6]-A[2]*B[4]-A[5]*B[0]);
		C[3] += (A[0]*B[13]+A[1]*B[14]+A[3]*B[10]+A[4]*B[1]);
		C[4] += (-A[0]*B[7]-A[1]*B[8]-A[3]*B[4]+A[5]*B[1]);
		C[5] += (-A[0]*B[16]-A[1]*B[17]-A[4]*B[4]-A[5]*B[10]);
		C[6] += (-A[0]*B[15]+A[2]*B[14]+A[3]*B[12]+A[4]*B[3]);
		C[7] += (A[0]*B[9]-A[2]*B[8]-A[3]*B[6]+A[5]*B[3]);
		C[8] += (A[0]*B[18]-A[2]*B[17]-A[4]*B[6]-A[5]*B[12]);
		C[9] += (-A[0]*B[19]-A[3]*B[17]+A[4]*B[8]+A[5]*B[14]);
		C[10] += (-A[1]*B[15]-A[2]*B[13]-A[3]*B[11]-A[4]*B[2]);
		C[11] += (A[1]*B[9]+A[2]*B[7]+A[3]*B[5]-A[5]*B[2]);
		C[12] += (A[1]*B[18]+A[2]*B[16]+A[4]*B[5]+A[5]*B[11]);
		C[13] += (-A[1]*B[19]+A[3]*B[16]-A[4]*B[7]-A[5]*B[13]);
		C[14] += (-A[2]*B[19]-A[3]*B[18]+A[4]*B[9]+A[5]*B[15]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 3 -> group 4)
	 */
	protected final static void gp_default_5_3_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[10]+A[1]*B[4]-A[2]*B[1]+A[3]*B[0]);
		C[1] += (-A[0]*B[12]+A[1]*B[6]-A[2]*B[3]+A[5]*B[0]);
		C[2] += (A[0]*B[14]-A[1]*B[8]+A[3]*B[3]-A[5]*B[1]);
		C[3] += (-A[1]*B[17]+A[2]*B[14]-A[3]*B[12]+A[5]*B[10]);
		C[4] += (A[0]*B[17]-A[2]*B[8]+A[3]*B[6]-A[5]*B[4]);
		C[5] += (A[0]*B[11]-A[1]*B[5]+A[2]*B[2]-A[4]*B[0]);
		C[6] += (-A[0]*B[13]+A[1]*B[7]-A[3]*B[2]+A[4]*B[1]);
		C[7] += (A[1]*B[16]-A[2]*B[13]+A[3]*B[11]-A[4]*B[10]);
		C[8] += (-A[0]*B[16]+A[2]*B[7]-A[3]*B[5]+A[4]*B[4]);
		C[9] += (A[0]*B[15]-A[1]*B[9]+A[4]*B[3]-A[5]*B[2]);
		C[10] += (-A[1]*B[18]+A[2]*B[15]-A[4]*B[12]+A[5]*B[11]);
		C[11] += (A[0]*B[18]-A[2]*B[9]+A[4]*B[6]-A[5]*B[5]);
		C[12] += (A[1]*B[19]-A[3]*B[15]+A[4]*B[14]-A[5]*B[13]);
		C[13] += (-A[0]*B[19]+A[3]*B[9]-A[4]*B[8]+A[5]*B[7]);
		C[14] += (-A[2]*B[19]+A[3]*B[18]-A[4]*B[17]+A[5]*B[16]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 4 -> group 1)
	 */
	protected final static void gp_default_5_4_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[7]+A[1]*B[8]-A[2]*B[6]-A[3]*B[5]-A[4]*B[0]);
		C[1] += (-A[0]*B[3]-A[1]*B[4]+A[2]*B[2]+A[3]*B[1]-A[5]*B[0]);
		C[2] += (-A[0]*B[10]-A[1]*B[11]+A[2]*B[9]+A[4]*B[1]+A[5]*B[5]);
		C[3] += (A[0]*B[12]+A[1]*B[13]+A[3]*B[9]-A[4]*B[2]-A[5]*B[6]);
		C[4] += (-A[0]*B[14]+A[2]*B[13]+A[3]*B[11]-A[4]*B[4]-A[5]*B[8]);
		C[5] += (-A[1]*B[14]-A[2]*B[12]-A[3]*B[10]+A[4]*B[3]+A[5]*B[7]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 4 -> group 3)
	 */
	protected final static void gp_default_5_4_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]-A[1]*B[1]+A[2]*B[0]);
		C[1] += (-A[0]*B[6]+A[1]*B[2]-A[3]*B[0]);
		C[2] += (A[1]*B[9]-A[2]*B[6]+A[3]*B[5]);
		C[3] += (-A[0]*B[9]+A[2]*B[2]-A[3]*B[1]);
		C[4] += (-A[0]*B[8]+A[1]*B[4]-A[5]*B[0]);
		C[5] += (A[1]*B[11]-A[2]*B[8]+A[5]*B[5]);
		C[6] += (-A[0]*B[11]+A[2]*B[4]-A[5]*B[1]);
		C[7] += (-A[1]*B[13]+A[3]*B[8]-A[5]*B[6]);
		C[8] += (A[0]*B[13]-A[3]*B[4]+A[5]*B[2]);
		C[9] += (A[2]*B[13]-A[3]*B[11]+A[5]*B[9]);
		C[10] += (A[0]*B[7]-A[1]*B[3]+A[4]*B[0]);
		C[11] += (-A[1]*B[10]+A[2]*B[7]-A[4]*B[5]);
		C[12] += (A[0]*B[10]-A[2]*B[3]+A[4]*B[1]);
		C[13] += (A[1]*B[12]-A[3]*B[7]+A[4]*B[6]);
		C[14] += (-A[0]*B[12]+A[3]*B[3]-A[4]*B[2]);
		C[15] += (-A[2]*B[12]+A[3]*B[10]-A[4]*B[9]);
		C[16] += (-A[1]*B[14]+A[4]*B[8]-A[5]*B[7]);
		C[17] += (A[0]*B[14]-A[4]*B[4]+A[5]*B[3]);
		C[18] += (A[2]*B[14]-A[4]*B[11]+A[5]*B[10]);
		C[19] += (-A[3]*B[14]+A[4]*B[13]-A[5]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 5 -> group 0)
	 */
	protected final static void gp_default_5_5_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[4]-A[1]*B[5]+A[2]*B[3]+A[3]*B[2]-A[4]*B[0]-A[5]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 5 -> group 2)
	 */
	protected final static void gp_default_5_5_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[1]+A[1]*B[0]);
		C[1] += (A[1]*B[2]-A[2]*B[1]);
		C[2] += (-A[0]*B[2]+A[2]*B[0]);
		C[3] += (-A[1]*B[3]+A[3]*B[1]);
		C[4] += (A[0]*B[3]-A[3]*B[0]);
		C[5] += (A[2]*B[3]-A[3]*B[2]);
		C[6] += (-A[1]*B[5]+A[5]*B[1]);
		C[7] += (A[0]*B[5]-A[5]*B[0]);
		C[8] += (A[2]*B[5]-A[5]*B[2]);
		C[9] += (-A[3]*B[5]+A[5]*B[3]);
		C[10] += (A[1]*B[4]-A[4]*B[1]);
		C[11] += (-A[0]*B[4]+A[4]*B[0]);
		C[12] += (-A[2]*B[4]+A[4]*B[2]);
		C[13] += (A[3]*B[4]-A[4]*B[3]);
		C[14] += (-A[4]*B[5]+A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 6 -> group 1)
	 */
	protected final static void gp_default_5_6_1(float[] A, float[] B, float[] C) {
		C[0] += A[1]*B[0];
		C[1] += -A[0]*B[0];
		C[2] += -A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[5]*B[0];
		C[5] += -A[4]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 0 -> group 6)
	 */
	protected final static void gp_default_6_0_6(float[] A, float[] B, float[] C) {
		gp_default_0_0_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 1 -> group 5)
	 */
	protected final static void gp_default_6_1_5(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[1];
		C[1] += -A[0]*B[0];
		C[2] += A[0]*B[2];
		C[3] += -A[0]*B[3];
		C[4] += A[0]*B[5];
		C[5] += -A[0]*B[4];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 2 -> group 4)
	 */
	protected final static void gp_default_6_2_4(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
		C[1] += -A[0]*B[2];
		C[2] += A[0]*B[4];
		C[3] += -A[0]*B[11];
		C[4] += A[0]*B[7];
		C[5] += A[0]*B[1];
		C[6] += -A[0]*B[3];
		C[7] += A[0]*B[10];
		C[8] += -A[0]*B[6];
		C[9] += A[0]*B[5];
		C[10] += -A[0]*B[12];
		C[11] += A[0]*B[8];
		C[12] += A[0]*B[13];
		C[13] += -A[0]*B[9];
		C[14] += -A[0]*B[14];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 3 -> group 3)
	 */
	protected final static void gp_default_6_3_3(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += -A[0]*B[10];
		C[3] += A[0]*B[4];
		C[4] += A[0]*B[3];
		C[5] += -A[0]*B[12];
		C[6] += A[0]*B[6];
		C[7] += A[0]*B[14];
		C[8] += -A[0]*B[8];
		C[9] += -A[0]*B[17];
		C[10] += -A[0]*B[2];
		C[11] += A[0]*B[11];
		C[12] += -A[0]*B[5];
		C[13] += -A[0]*B[13];
		C[14] += A[0]*B[7];
		C[15] += A[0]*B[16];
		C[16] += A[0]*B[15];
		C[17] += -A[0]*B[9];
		C[18] += -A[0]*B[18];
		C[19] += A[0]*B[19];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 4 -> group 2)
	 */
	protected final static void gp_default_6_4_2(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
		C[1] += A[0]*B[5];
		C[2] += -A[0]*B[1];
		C[3] += -A[0]*B[6];
		C[4] += A[0]*B[2];
		C[5] += A[0]*B[9];
		C[6] += -A[0]*B[8];
		C[7] += A[0]*B[4];
		C[8] += A[0]*B[11];
		C[9] += -A[0]*B[13];
		C[10] += A[0]*B[7];
		C[11] += -A[0]*B[3];
		C[12] += -A[0]*B[10];
		C[13] += A[0]*B[12];
		C[14] += -A[0]*B[14];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 5 -> group 1)
	 */
	protected final static void gp_default_6_5_1(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[1];
		C[1] += A[0]*B[0];
		C[2] += A[0]*B[2];
		C[3] += -A[0]*B[3];
		C[4] += -A[0]*B[5];
		C[5] += A[0]*B[4];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 6 -> group 0)
	 */
	protected final static void gp_default_6_6_0(float[] A, float[] B, float[] C) {
		gp_default_0_0_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 0 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__0_0_0(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 1 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__0_1_1(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 2 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__0_2_2(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
		C[6] += A[0]*B[6];
		C[7] += A[0]*B[7];
		C[8] += A[0]*B[8];
		C[9] += A[0]*B[9];
		C[10] += A[0]*B[10];
		C[11] += A[0]*B[11];
		C[12] += A[0]*B[12];
		C[13] += A[0]*B[13];
		C[14] += A[0]*B[14];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 3 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__0_3_3(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[0]*B[1];
		C[2] += A[0]*B[2];
		C[3] += A[0]*B[3];
		C[4] += A[0]*B[4];
		C[5] += A[0]*B[5];
		C[6] += A[0]*B[6];
		C[7] += A[0]*B[7];
		C[8] += A[0]*B[8];
		C[9] += A[0]*B[9];
		C[10] += A[0]*B[10];
		C[11] += A[0]*B[11];
		C[12] += A[0]*B[12];
		C[13] += A[0]*B[13];
		C[14] += A[0]*B[14];
		C[15] += A[0]*B[15];
		C[16] += A[0]*B[16];
		C[17] += A[0]*B[17];
		C[18] += A[0]*B[18];
		C[19] += A[0]*B[19];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 4 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__0_4_4(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__0_2_2(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 5 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__0_5_5(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__0_1_1(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 0  x  group 6 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__0_6_6(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__0_0_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 0 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__1_0_1(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__1_1_0(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[0]+A[1]*B[1]+A[2]*B[2]+A[3]*B[3]+A[4]*B[4]+A[5]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 1 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__1_1_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[1]-A[1]*B[0]);
		C[1] += (A[0]*B[2]-A[2]*B[0]);
		C[2] += (A[1]*B[2]-A[2]*B[1]);
		C[3] += (A[0]*B[3]-A[3]*B[0]);
		C[4] += (A[1]*B[3]-A[3]*B[1]);
		C[5] += (A[2]*B[3]-A[3]*B[2]);
		C[6] += (A[0]*B[4]-A[4]*B[0]);
		C[7] += (A[1]*B[4]-A[4]*B[1]);
		C[8] += (A[2]*B[4]-A[4]*B[2]);
		C[9] += (A[3]*B[4]-A[4]*B[3]);
		C[10] += (A[0]*B[5]-A[5]*B[0]);
		C[11] += (A[1]*B[5]-A[5]*B[1]);
		C[12] += (A[2]*B[5]-A[5]*B[2]);
		C[13] += (A[3]*B[5]-A[5]*B[3]);
		C[14] += (A[4]*B[5]-A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__1_2_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[1]*B[0]-A[2]*B[1]-A[3]*B[3]-A[4]*B[6]-A[5]*B[10]);
		C[1] += (A[0]*B[0]-A[2]*B[2]-A[3]*B[4]-A[4]*B[7]-A[5]*B[11]);
		C[2] += (A[0]*B[1]+A[1]*B[2]-A[3]*B[5]-A[4]*B[8]-A[5]*B[12]);
		C[3] += (A[0]*B[3]+A[1]*B[4]+A[2]*B[5]-A[4]*B[9]-A[5]*B[13]);
		C[4] += (A[0]*B[6]+A[1]*B[7]+A[2]*B[8]+A[3]*B[9]-A[5]*B[14]);
		C[5] += (A[0]*B[10]+A[1]*B[11]+A[2]*B[12]+A[3]*B[13]+A[4]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 2 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__1_2_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]-A[1]*B[1]+A[2]*B[0]);
		C[1] += (A[0]*B[4]-A[1]*B[3]+A[3]*B[0]);
		C[2] += (A[0]*B[5]-A[2]*B[3]+A[3]*B[1]);
		C[3] += (A[1]*B[5]-A[2]*B[4]+A[3]*B[2]);
		C[4] += (A[0]*B[7]-A[1]*B[6]+A[4]*B[0]);
		C[5] += (A[0]*B[8]-A[2]*B[6]+A[4]*B[1]);
		C[6] += (A[1]*B[8]-A[2]*B[7]+A[4]*B[2]);
		C[7] += (A[0]*B[9]-A[3]*B[6]+A[4]*B[3]);
		C[8] += (A[1]*B[9]-A[3]*B[7]+A[4]*B[4]);
		C[9] += (A[2]*B[9]-A[3]*B[8]+A[4]*B[5]);
		C[10] += (A[0]*B[11]-A[1]*B[10]+A[5]*B[0]);
		C[11] += (A[0]*B[12]-A[2]*B[10]+A[5]*B[1]);
		C[12] += (A[1]*B[12]-A[2]*B[11]+A[5]*B[2]);
		C[13] += (A[0]*B[13]-A[3]*B[10]+A[5]*B[3]);
		C[14] += (A[1]*B[13]-A[3]*B[11]+A[5]*B[4]);
		C[15] += (A[2]*B[13]-A[3]*B[12]+A[5]*B[5]);
		C[16] += (A[0]*B[14]-A[4]*B[10]+A[5]*B[6]);
		C[17] += (A[1]*B[14]-A[4]*B[11]+A[5]*B[7]);
		C[18] += (A[2]*B[14]-A[4]*B[12]+A[5]*B[8]);
		C[19] += (A[3]*B[14]-A[4]*B[13]+A[5]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__1_3_2(float[] A, float[] B, float[] C) {
		C[0] += (A[2]*B[0]+A[3]*B[1]+A[4]*B[4]+A[5]*B[10]);
		C[1] += (-A[1]*B[0]+A[3]*B[2]+A[4]*B[5]+A[5]*B[11]);
		C[2] += (A[0]*B[0]+A[3]*B[3]+A[4]*B[6]+A[5]*B[12]);
		C[3] += (-A[1]*B[1]-A[2]*B[2]+A[4]*B[7]+A[5]*B[13]);
		C[4] += (A[0]*B[1]-A[2]*B[3]+A[4]*B[8]+A[5]*B[14]);
		C[5] += (A[0]*B[2]+A[1]*B[3]+A[4]*B[9]+A[5]*B[15]);
		C[6] += (-A[1]*B[4]-A[2]*B[5]-A[3]*B[7]+A[5]*B[16]);
		C[7] += (A[0]*B[4]-A[2]*B[6]-A[3]*B[8]+A[5]*B[17]);
		C[8] += (A[0]*B[5]+A[1]*B[6]-A[3]*B[9]+A[5]*B[18]);
		C[9] += (A[0]*B[7]+A[1]*B[8]+A[2]*B[9]+A[5]*B[19]);
		C[10] += (-A[1]*B[10]-A[2]*B[11]-A[3]*B[13]-A[4]*B[16]);
		C[11] += (A[0]*B[10]-A[2]*B[12]-A[3]*B[14]-A[4]*B[17]);
		C[12] += (A[0]*B[11]+A[1]*B[12]-A[3]*B[15]-A[4]*B[18]);
		C[13] += (A[0]*B[13]+A[1]*B[14]+A[2]*B[15]-A[4]*B[19]);
		C[14] += (A[0]*B[16]+A[1]*B[17]+A[2]*B[18]+A[3]*B[19]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 3 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__1_3_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]-A[1]*B[2]+A[2]*B[1]-A[3]*B[0]);
		C[1] += (A[0]*B[6]-A[1]*B[5]+A[2]*B[4]-A[4]*B[0]);
		C[2] += (A[0]*B[8]-A[1]*B[7]+A[3]*B[4]-A[4]*B[1]);
		C[3] += (A[0]*B[9]-A[2]*B[7]+A[3]*B[5]-A[4]*B[2]);
		C[4] += (A[1]*B[9]-A[2]*B[8]+A[3]*B[6]-A[4]*B[3]);
		C[5] += (A[0]*B[12]-A[1]*B[11]+A[2]*B[10]-A[5]*B[0]);
		C[6] += (A[0]*B[14]-A[1]*B[13]+A[3]*B[10]-A[5]*B[1]);
		C[7] += (A[0]*B[15]-A[2]*B[13]+A[3]*B[11]-A[5]*B[2]);
		C[8] += (A[1]*B[15]-A[2]*B[14]+A[3]*B[12]-A[5]*B[3]);
		C[9] += (A[0]*B[17]-A[1]*B[16]+A[4]*B[10]-A[5]*B[4]);
		C[10] += (A[0]*B[18]-A[2]*B[16]+A[4]*B[11]-A[5]*B[5]);
		C[11] += (A[1]*B[18]-A[2]*B[17]+A[4]*B[12]-A[5]*B[6]);
		C[12] += (A[0]*B[19]-A[3]*B[16]+A[4]*B[13]-A[5]*B[7]);
		C[13] += (A[1]*B[19]-A[3]*B[17]+A[4]*B[14]-A[5]*B[8]);
		C[14] += (A[2]*B[19]-A[3]*B[18]+A[4]*B[15]-A[5]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__1_4_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[3]*B[0]-A[4]*B[1]-A[5]*B[5]);
		C[1] += (A[2]*B[0]-A[4]*B[2]-A[5]*B[6]);
		C[2] += (-A[1]*B[0]-A[4]*B[3]-A[5]*B[7]);
		C[3] += (A[0]*B[0]-A[4]*B[4]-A[5]*B[8]);
		C[4] += (A[2]*B[1]+A[3]*B[2]-A[5]*B[9]);
		C[5] += (-A[1]*B[1]+A[3]*B[3]-A[5]*B[10]);
		C[6] += (A[0]*B[1]+A[3]*B[4]-A[5]*B[11]);
		C[7] += (-A[1]*B[2]-A[2]*B[3]-A[5]*B[12]);
		C[8] += (A[0]*B[2]-A[2]*B[4]-A[5]*B[13]);
		C[9] += (A[0]*B[3]+A[1]*B[4]-A[5]*B[14]);
		C[10] += (A[2]*B[5]+A[3]*B[6]+A[4]*B[9]);
		C[11] += (-A[1]*B[5]+A[3]*B[7]+A[4]*B[10]);
		C[12] += (A[0]*B[5]+A[3]*B[8]+A[4]*B[11]);
		C[13] += (-A[1]*B[6]-A[2]*B[7]+A[4]*B[12]);
		C[14] += (A[0]*B[6]-A[2]*B[8]+A[4]*B[13]);
		C[15] += (A[0]*B[7]+A[1]*B[8]+A[4]*B[14]);
		C[16] += (-A[1]*B[9]-A[2]*B[10]-A[3]*B[12]);
		C[17] += (A[0]*B[9]-A[2]*B[11]-A[3]*B[13]);
		C[18] += (A[0]*B[10]+A[1]*B[11]-A[3]*B[14]);
		C[19] += (A[0]*B[12]+A[1]*B[13]+A[2]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 4 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__1_4_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]+A[4]*B[0]);
		C[1] += (A[0]*B[8]-A[1]*B[7]+A[2]*B[6]-A[3]*B[5]+A[5]*B[0]);
		C[2] += (A[0]*B[11]-A[1]*B[10]+A[2]*B[9]-A[4]*B[5]+A[5]*B[1]);
		C[3] += (A[0]*B[13]-A[1]*B[12]+A[3]*B[9]-A[4]*B[6]+A[5]*B[2]);
		C[4] += (A[0]*B[14]-A[2]*B[12]+A[3]*B[10]-A[4]*B[7]+A[5]*B[3]);
		C[5] += (A[1]*B[14]-A[2]*B[13]+A[3]*B[11]-A[4]*B[8]+A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 5 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__1_5_4(float[] A, float[] B, float[] C) {
		C[0] += (A[4]*B[0]+A[5]*B[1]);
		C[1] += (-A[3]*B[0]+A[5]*B[2]);
		C[2] += (A[2]*B[0]+A[5]*B[3]);
		C[3] += (-A[1]*B[0]+A[5]*B[4]);
		C[4] += (A[0]*B[0]+A[5]*B[5]);
		C[5] += (-A[3]*B[1]-A[4]*B[2]);
		C[6] += (A[2]*B[1]-A[4]*B[3]);
		C[7] += (-A[1]*B[1]-A[4]*B[4]);
		C[8] += (A[0]*B[1]-A[4]*B[5]);
		C[9] += (A[2]*B[2]+A[3]*B[3]);
		C[10] += (-A[1]*B[2]+A[3]*B[4]);
		C[11] += (A[0]*B[2]+A[3]*B[5]);
		C[12] += (-A[1]*B[3]-A[2]*B[4]);
		C[13] += (A[0]*B[3]-A[2]*B[5]);
		C[14] += (A[0]*B[4]+A[1]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 5 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__1_5_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]-A[3]*B[2]+A[4]*B[1]-A[5]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 1  x  group 6 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__1_6_5(float[] A, float[] B, float[] C) {
		C[0] += -A[5]*B[0];
		C[1] += A[4]*B[0];
		C[2] += -A[3]*B[0];
		C[3] += A[2]*B[0];
		C[4] += -A[1]*B[0];
		C[5] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 0 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__2_0_2(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
		C[6] += A[6]*B[0];
		C[7] += A[7]*B[0];
		C[8] += A[8]*B[0];
		C[9] += A[9]*B[0];
		C[10] += A[10]*B[0];
		C[11] += A[11]*B[0];
		C[12] += A[12]*B[0];
		C[13] += A[13]*B[0];
		C[14] += A[14]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__2_1_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[1]+A[1]*B[2]+A[10]*B[5]+A[3]*B[3]+A[6]*B[4]);
		C[1] += (-A[0]*B[0]+A[11]*B[5]+A[2]*B[2]+A[4]*B[3]+A[7]*B[4]);
		C[2] += (-A[1]*B[0]+A[12]*B[5]-A[2]*B[1]+A[5]*B[3]+A[8]*B[4]);
		C[3] += (A[13]*B[5]-A[3]*B[0]-A[4]*B[1]-A[5]*B[2]+A[9]*B[4]);
		C[4] += (A[14]*B[5]-A[6]*B[0]-A[7]*B[1]-A[8]*B[2]-A[9]*B[3]);
		C[5] += (-A[10]*B[0]-A[11]*B[1]-A[12]*B[2]-A[13]*B[3]-A[14]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 1 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__2_1_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]-A[1]*B[1]+A[2]*B[0]);
		C[1] += (A[0]*B[3]-A[3]*B[1]+A[4]*B[0]);
		C[2] += (A[1]*B[3]-A[3]*B[2]+A[5]*B[0]);
		C[3] += (A[2]*B[3]-A[4]*B[2]+A[5]*B[1]);
		C[4] += (A[0]*B[4]-A[6]*B[1]+A[7]*B[0]);
		C[5] += (A[1]*B[4]-A[6]*B[2]+A[8]*B[0]);
		C[6] += (A[2]*B[4]-A[7]*B[2]+A[8]*B[1]);
		C[7] += (A[3]*B[4]-A[6]*B[3]+A[9]*B[0]);
		C[8] += (A[4]*B[4]-A[7]*B[3]+A[9]*B[1]);
		C[9] += (A[5]*B[4]-A[8]*B[3]+A[9]*B[2]);
		C[10] += (A[0]*B[5]-A[10]*B[1]+A[11]*B[0]);
		C[11] += (A[1]*B[5]-A[10]*B[2]+A[12]*B[0]);
		C[12] += (-A[11]*B[2]+A[12]*B[1]+A[2]*B[5]);
		C[13] += (-A[10]*B[3]+A[13]*B[0]+A[3]*B[5]);
		C[14] += (-A[11]*B[3]+A[13]*B[1]+A[4]*B[5]);
		C[15] += (-A[12]*B[3]+A[13]*B[2]+A[5]*B[5]);
		C[16] += (-A[10]*B[4]+A[14]*B[0]+A[6]*B[5]);
		C[17] += (-A[11]*B[4]+A[14]*B[1]+A[7]*B[5]);
		C[18] += (-A[12]*B[4]+A[14]*B[2]+A[8]*B[5]);
		C[19] += (-A[13]*B[4]+A[14]*B[3]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__2_2_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[0]-A[1]*B[1]-A[10]*B[10]-A[11]*B[11]-A[12]*B[12]-A[13]*B[13]-A[14]*B[14]-A[2]*B[2]-A[3]*B[3]-A[4]*B[4]-A[5]*B[5]-A[6]*B[6]-A[7]*B[7]-A[8]*B[8]-A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__2_2_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[1]*B[2]-A[10]*B[11]+A[11]*B[10]+A[2]*B[1]-A[3]*B[4]+A[4]*B[3]-A[6]*B[7]+A[7]*B[6]);
		C[1] += (A[0]*B[2]-A[10]*B[12]+A[12]*B[10]-A[2]*B[0]-A[3]*B[5]+A[5]*B[3]-A[6]*B[8]+A[8]*B[6]);
		C[2] += (-A[0]*B[1]+A[1]*B[0]-A[11]*B[12]+A[12]*B[11]-A[4]*B[5]+A[5]*B[4]-A[7]*B[8]+A[8]*B[7]);
		C[3] += (A[0]*B[4]+A[1]*B[5]-A[10]*B[13]+A[13]*B[10]-A[4]*B[0]-A[5]*B[1]-A[6]*B[9]+A[9]*B[6]);
		C[4] += (-A[0]*B[3]-A[11]*B[13]+A[13]*B[11]+A[2]*B[5]+A[3]*B[0]-A[5]*B[2]-A[7]*B[9]+A[9]*B[7]);
		C[5] += (-A[1]*B[3]-A[12]*B[13]+A[13]*B[12]-A[2]*B[4]+A[3]*B[1]+A[4]*B[2]-A[8]*B[9]+A[9]*B[8]);
		C[6] += (A[0]*B[7]+A[1]*B[8]-A[10]*B[14]+A[14]*B[10]+A[3]*B[9]-A[7]*B[0]-A[8]*B[1]-A[9]*B[3]);
		C[7] += (-A[0]*B[6]-A[11]*B[14]+A[14]*B[11]+A[2]*B[8]+A[4]*B[9]+A[6]*B[0]-A[8]*B[2]-A[9]*B[4]);
		C[8] += (-A[1]*B[6]-A[12]*B[14]+A[14]*B[12]-A[2]*B[7]+A[5]*B[9]+A[6]*B[1]+A[7]*B[2]-A[9]*B[5]);
		C[9] += (-A[13]*B[14]+A[14]*B[13]-A[3]*B[6]-A[4]*B[7]-A[5]*B[8]+A[6]*B[3]+A[7]*B[4]+A[8]*B[5]);
		C[10] += (A[0]*B[11]+A[1]*B[12]-A[11]*B[0]-A[12]*B[1]-A[13]*B[3]-A[14]*B[6]+A[3]*B[13]+A[6]*B[14]);
		C[11] += (-A[0]*B[10]+A[10]*B[0]-A[12]*B[2]-A[13]*B[4]-A[14]*B[7]+A[2]*B[12]+A[4]*B[13]+A[7]*B[14]);
		C[12] += (-A[1]*B[10]+A[10]*B[1]+A[11]*B[2]-A[13]*B[5]-A[14]*B[8]-A[2]*B[11]+A[5]*B[13]+A[8]*B[14]);
		C[13] += (A[10]*B[3]+A[11]*B[4]+A[12]*B[5]-A[14]*B[9]-A[3]*B[10]-A[4]*B[11]-A[5]*B[12]+A[9]*B[14]);
		C[14] += (A[10]*B[6]+A[11]*B[7]+A[12]*B[8]+A[13]*B[9]-A[6]*B[10]-A[7]*B[11]-A[8]*B[12]-A[9]*B[13]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 2 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__2_2_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[5]-A[1]*B[4]+A[2]*B[3]+A[3]*B[2]-A[4]*B[1]+A[5]*B[0]);
		C[1] += (A[0]*B[8]-A[1]*B[7]+A[2]*B[6]+A[6]*B[2]-A[7]*B[1]+A[8]*B[0]);
		C[2] += (A[0]*B[9]-A[3]*B[7]+A[4]*B[6]+A[6]*B[4]-A[7]*B[3]+A[9]*B[0]);
		C[3] += (A[1]*B[9]-A[3]*B[8]+A[5]*B[6]+A[6]*B[5]-A[8]*B[3]+A[9]*B[1]);
		C[4] += (A[2]*B[9]-A[4]*B[8]+A[5]*B[7]+A[7]*B[5]-A[8]*B[4]+A[9]*B[2]);
		C[5] += (A[0]*B[12]-A[1]*B[11]+A[10]*B[2]-A[11]*B[1]+A[12]*B[0]+A[2]*B[10]);
		C[6] += (A[0]*B[13]+A[10]*B[4]-A[11]*B[3]+A[13]*B[0]-A[3]*B[11]+A[4]*B[10]);
		C[7] += (A[1]*B[13]+A[10]*B[5]-A[12]*B[3]+A[13]*B[1]-A[3]*B[12]+A[5]*B[10]);
		C[8] += (A[11]*B[5]-A[12]*B[4]+A[13]*B[2]+A[2]*B[13]-A[4]*B[12]+A[5]*B[11]);
		C[9] += (A[0]*B[14]+A[10]*B[7]-A[11]*B[6]+A[14]*B[0]-A[6]*B[11]+A[7]*B[10]);
		C[10] += (A[1]*B[14]+A[10]*B[8]-A[12]*B[6]+A[14]*B[1]-A[6]*B[12]+A[8]*B[10]);
		C[11] += (A[11]*B[8]-A[12]*B[7]+A[14]*B[2]+A[2]*B[14]-A[7]*B[12]+A[8]*B[11]);
		C[12] += (A[10]*B[9]-A[13]*B[6]+A[14]*B[3]+A[3]*B[14]-A[6]*B[13]+A[9]*B[10]);
		C[13] += (A[11]*B[9]-A[13]*B[7]+A[14]*B[4]+A[4]*B[14]-A[7]*B[13]+A[9]*B[11]);
		C[14] += (A[12]*B[9]-A[13]*B[8]+A[14]*B[5]+A[5]*B[14]-A[8]*B[13]+A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__2_3_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[11]*B[10]-A[12]*B[11]-A[13]*B[13]-A[14]*B[16]-A[2]*B[0]-A[4]*B[1]-A[5]*B[2]-A[7]*B[4]-A[8]*B[5]-A[9]*B[7]);
		C[1] += (A[1]*B[0]+A[10]*B[10]-A[12]*B[12]-A[13]*B[14]-A[14]*B[17]+A[3]*B[1]-A[5]*B[3]+A[6]*B[4]-A[8]*B[6]-A[9]*B[8]);
		C[2] += (-A[0]*B[0]+A[10]*B[11]+A[11]*B[12]-A[13]*B[15]-A[14]*B[18]+A[3]*B[2]+A[4]*B[3]+A[6]*B[5]+A[7]*B[6]-A[9]*B[9]);
		C[3] += (-A[0]*B[1]-A[1]*B[2]+A[10]*B[13]+A[11]*B[14]+A[12]*B[15]-A[14]*B[19]-A[2]*B[3]+A[6]*B[7]+A[7]*B[8]+A[8]*B[9]);
		C[4] += (-A[0]*B[4]-A[1]*B[5]+A[10]*B[16]+A[11]*B[17]+A[12]*B[18]+A[13]*B[19]-A[2]*B[6]-A[3]*B[7]-A[4]*B[8]-A[5]*B[9]);
		C[5] += (-A[0]*B[10]-A[1]*B[11]-A[2]*B[12]-A[3]*B[13]-A[4]*B[14]-A[5]*B[15]-A[6]*B[16]-A[7]*B[17]-A[8]*B[18]-A[9]*B[19]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__2_3_3(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[12]-A[11]*B[11]+A[12]*B[10]+A[3]*B[3]-A[4]*B[2]+A[5]*B[1]+A[6]*B[6]-A[7]*B[5]+A[8]*B[4]);
		C[1] += (-A[1]*B[3]+A[10]*B[14]-A[11]*B[13]+A[13]*B[10]+A[2]*B[2]-A[5]*B[0]+A[6]*B[8]-A[7]*B[7]+A[9]*B[4]);
		C[2] += (A[0]*B[3]+A[10]*B[15]-A[12]*B[13]+A[13]*B[11]-A[2]*B[1]+A[4]*B[0]+A[6]*B[9]-A[8]*B[7]+A[9]*B[5]);
		C[3] += (-A[0]*B[2]+A[1]*B[1]+A[11]*B[15]-A[12]*B[14]+A[13]*B[12]-A[3]*B[0]+A[7]*B[9]-A[8]*B[8]+A[9]*B[6]);
		C[4] += (-A[1]*B[6]+A[10]*B[17]-A[11]*B[16]+A[14]*B[10]+A[2]*B[5]-A[3]*B[8]+A[4]*B[7]-A[8]*B[0]-A[9]*B[1]);
		C[5] += (A[0]*B[6]+A[10]*B[18]-A[12]*B[16]+A[14]*B[11]-A[2]*B[4]-A[3]*B[9]+A[5]*B[7]+A[7]*B[0]-A[9]*B[2]);
		C[6] += (-A[0]*B[5]+A[1]*B[4]+A[11]*B[18]-A[12]*B[17]+A[14]*B[12]-A[4]*B[9]+A[5]*B[8]-A[6]*B[0]-A[9]*B[3]);
		C[7] += (A[0]*B[8]+A[1]*B[9]+A[10]*B[19]-A[13]*B[16]+A[14]*B[13]-A[4]*B[4]-A[5]*B[5]+A[7]*B[1]+A[8]*B[2]);
		C[8] += (-A[0]*B[7]+A[11]*B[19]-A[13]*B[17]+A[14]*B[14]+A[2]*B[9]+A[3]*B[4]-A[5]*B[6]-A[6]*B[1]+A[8]*B[3]);
		C[9] += (-A[1]*B[7]+A[12]*B[19]-A[13]*B[18]+A[14]*B[15]-A[2]*B[8]+A[3]*B[5]+A[4]*B[6]-A[6]*B[2]-A[7]*B[3]);
		C[10] += (-A[1]*B[12]-A[12]*B[0]-A[13]*B[1]-A[14]*B[4]+A[2]*B[11]-A[3]*B[14]+A[4]*B[13]-A[6]*B[17]+A[7]*B[16]);
		C[11] += (A[0]*B[12]+A[11]*B[0]-A[13]*B[2]-A[14]*B[5]-A[2]*B[10]-A[3]*B[15]+A[5]*B[13]-A[6]*B[18]+A[8]*B[16]);
		C[12] += (-A[0]*B[11]+A[1]*B[10]-A[10]*B[0]-A[13]*B[3]-A[14]*B[6]-A[4]*B[15]+A[5]*B[14]-A[7]*B[18]+A[8]*B[17]);
		C[13] += (A[0]*B[14]+A[1]*B[15]+A[11]*B[1]+A[12]*B[2]-A[14]*B[7]-A[4]*B[10]-A[5]*B[11]-A[6]*B[19]+A[9]*B[16]);
		C[14] += (-A[0]*B[13]-A[10]*B[1]+A[12]*B[3]-A[14]*B[8]+A[2]*B[15]+A[3]*B[10]-A[5]*B[12]-A[7]*B[19]+A[9]*B[17]);
		C[15] += (-A[1]*B[13]-A[10]*B[2]-A[11]*B[3]-A[14]*B[9]-A[2]*B[14]+A[3]*B[11]+A[4]*B[12]-A[8]*B[19]+A[9]*B[18]);
		C[16] += (A[0]*B[17]+A[1]*B[18]+A[11]*B[4]+A[12]*B[5]+A[13]*B[7]+A[3]*B[19]-A[7]*B[10]-A[8]*B[11]-A[9]*B[13]);
		C[17] += (-A[0]*B[16]-A[10]*B[4]+A[12]*B[6]+A[13]*B[8]+A[2]*B[18]+A[4]*B[19]+A[6]*B[10]-A[8]*B[12]-A[9]*B[14]);
		C[18] += (-A[1]*B[16]-A[10]*B[5]-A[11]*B[6]+A[13]*B[9]-A[2]*B[17]+A[5]*B[19]+A[6]*B[11]+A[7]*B[12]-A[9]*B[15]);
		C[19] += (-A[10]*B[7]-A[11]*B[8]-A[12]*B[9]-A[3]*B[16]-A[4]*B[17]-A[5]*B[18]+A[6]*B[13]+A[7]*B[14]+A[8]*B[15]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 3 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__2_3_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[9]-A[1]*B[8]+A[2]*B[7]+A[3]*B[6]-A[4]*B[5]+A[5]*B[4]-A[6]*B[3]+A[7]*B[2]-A[8]*B[1]+A[9]*B[0]);
		C[1] += (A[0]*B[15]-A[1]*B[14]-A[10]*B[3]+A[11]*B[2]-A[12]*B[1]+A[13]*B[0]+A[2]*B[13]+A[3]*B[12]-A[4]*B[11]+A[5]*B[10]);
		C[2] += (A[0]*B[18]-A[1]*B[17]-A[10]*B[6]+A[11]*B[5]-A[12]*B[4]+A[14]*B[0]+A[2]*B[16]+A[6]*B[12]-A[7]*B[11]+A[8]*B[10]);
		C[3] += (A[0]*B[19]-A[10]*B[8]+A[11]*B[7]-A[13]*B[4]+A[14]*B[1]-A[3]*B[17]+A[4]*B[16]+A[6]*B[14]-A[7]*B[13]+A[9]*B[10]);
		C[4] += (A[1]*B[19]-A[10]*B[9]+A[12]*B[7]-A[13]*B[5]+A[14]*B[2]-A[3]*B[18]+A[5]*B[16]+A[6]*B[15]-A[8]*B[13]+A[9]*B[11]);
		C[5] += (-A[11]*B[9]+A[12]*B[8]-A[13]*B[6]+A[14]*B[3]+A[2]*B[19]-A[4]*B[18]+A[5]*B[17]+A[7]*B[15]-A[8]*B[14]+A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__2_4_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[12]*B[5]-A[13]*B[6]-A[14]*B[9]-A[5]*B[0]-A[8]*B[1]-A[9]*B[2]);
		C[1] += (A[11]*B[5]-A[13]*B[7]-A[14]*B[10]+A[4]*B[0]+A[7]*B[1]-A[9]*B[3]);
		C[2] += (-A[10]*B[5]-A[13]*B[8]-A[14]*B[11]-A[3]*B[0]-A[6]*B[1]-A[9]*B[4]);
		C[3] += (A[11]*B[6]+A[12]*B[7]-A[14]*B[12]-A[2]*B[0]+A[7]*B[2]+A[8]*B[3]);
		C[4] += (A[1]*B[0]-A[10]*B[6]+A[12]*B[8]-A[14]*B[13]-A[6]*B[2]+A[8]*B[4]);
		C[5] += (-A[0]*B[0]-A[10]*B[7]-A[11]*B[8]-A[14]*B[14]-A[6]*B[3]-A[7]*B[4]);
		C[6] += (A[11]*B[9]+A[12]*B[10]+A[13]*B[12]-A[2]*B[1]-A[4]*B[2]-A[5]*B[3]);
		C[7] += (A[1]*B[1]-A[10]*B[9]+A[12]*B[11]+A[13]*B[13]+A[3]*B[2]-A[5]*B[4]);
		C[8] += (-A[0]*B[1]-A[10]*B[10]-A[11]*B[11]+A[13]*B[14]+A[3]*B[3]+A[4]*B[4]);
		C[9] += (-A[0]*B[2]-A[1]*B[3]-A[10]*B[12]-A[11]*B[13]-A[12]*B[14]-A[2]*B[4]);
		C[10] += (-A[2]*B[5]-A[4]*B[6]-A[5]*B[7]-A[7]*B[9]-A[8]*B[10]-A[9]*B[12]);
		C[11] += (A[1]*B[5]+A[3]*B[6]-A[5]*B[8]+A[6]*B[9]-A[8]*B[11]-A[9]*B[13]);
		C[12] += (-A[0]*B[5]+A[3]*B[7]+A[4]*B[8]+A[6]*B[10]+A[7]*B[11]-A[9]*B[14]);
		C[13] += (-A[0]*B[6]-A[1]*B[7]-A[2]*B[8]+A[6]*B[12]+A[7]*B[13]+A[8]*B[14]);
		C[14] += (-A[0]*B[9]-A[1]*B[10]-A[2]*B[11]-A[3]*B[12]-A[4]*B[13]-A[5]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__2_4_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[10]*B[8]+A[11]*B[7]-A[12]*B[6]+A[13]*B[5]-A[6]*B[4]+A[7]*B[3]-A[8]*B[2]+A[9]*B[1]);
		C[1] += (-A[10]*B[11]+A[11]*B[10]-A[12]*B[9]+A[14]*B[5]+A[3]*B[4]-A[4]*B[3]+A[5]*B[2]-A[9]*B[0]);
		C[2] += (-A[1]*B[4]-A[10]*B[13]+A[11]*B[12]-A[13]*B[9]+A[14]*B[6]+A[2]*B[3]-A[5]*B[1]+A[8]*B[0]);
		C[3] += (A[0]*B[4]-A[10]*B[14]+A[12]*B[12]-A[13]*B[10]+A[14]*B[7]-A[2]*B[2]+A[4]*B[1]-A[7]*B[0]);
		C[4] += (-A[0]*B[3]+A[1]*B[2]-A[11]*B[14]+A[12]*B[13]-A[13]*B[11]+A[14]*B[8]-A[3]*B[1]+A[6]*B[0]);
		C[5] += (-A[13]*B[0]-A[14]*B[1]+A[3]*B[8]-A[4]*B[7]+A[5]*B[6]+A[6]*B[11]-A[7]*B[10]+A[8]*B[9]);
		C[6] += (-A[1]*B[8]+A[12]*B[0]-A[14]*B[2]+A[2]*B[7]-A[5]*B[5]+A[6]*B[13]-A[7]*B[12]+A[9]*B[9]);
		C[7] += (A[0]*B[8]-A[11]*B[0]-A[14]*B[3]-A[2]*B[6]+A[4]*B[5]+A[6]*B[14]-A[8]*B[12]+A[9]*B[10]);
		C[8] += (-A[0]*B[7]+A[1]*B[6]+A[10]*B[0]-A[14]*B[4]-A[3]*B[5]+A[7]*B[14]-A[8]*B[13]+A[9]*B[11]);
		C[9] += (-A[1]*B[11]+A[12]*B[1]+A[13]*B[2]+A[2]*B[10]-A[3]*B[13]+A[4]*B[12]-A[8]*B[5]-A[9]*B[6]);
		C[10] += (A[0]*B[11]-A[11]*B[1]+A[13]*B[3]-A[2]*B[9]-A[3]*B[14]+A[5]*B[12]+A[7]*B[5]-A[9]*B[7]);
		C[11] += (-A[0]*B[10]+A[1]*B[9]+A[10]*B[1]+A[13]*B[4]-A[4]*B[14]+A[5]*B[13]-A[6]*B[5]-A[9]*B[8]);
		C[12] += (A[0]*B[13]+A[1]*B[14]-A[11]*B[2]-A[12]*B[3]-A[4]*B[9]-A[5]*B[10]+A[7]*B[6]+A[8]*B[7]);
		C[13] += (-A[0]*B[12]+A[10]*B[2]-A[12]*B[4]+A[2]*B[14]+A[3]*B[9]-A[5]*B[11]-A[6]*B[6]+A[8]*B[8]);
		C[14] += (-A[1]*B[12]+A[10]*B[3]+A[11]*B[4]-A[2]*B[13]+A[3]*B[10]+A[4]*B[11]-A[6]*B[7]-A[7]*B[8]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 4 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__2_4_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]-A[1]*B[13]+A[10]*B[4]-A[11]*B[3]+A[12]*B[2]-A[13]*B[1]+A[14]*B[0]+A[2]*B[12]+A[3]*B[11]-A[4]*B[10]+A[5]*B[9]-A[6]*B[8]+A[7]*B[7]-A[8]*B[6]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 5 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__2_5_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[13]*B[1]-A[14]*B[2]-A[9]*B[0]);
		C[1] += (A[12]*B[1]-A[14]*B[3]+A[8]*B[0]);
		C[2] += (-A[11]*B[1]-A[14]*B[4]-A[7]*B[0]);
		C[3] += (A[10]*B[1]-A[14]*B[5]+A[6]*B[0]);
		C[4] += (A[12]*B[2]+A[13]*B[3]-A[5]*B[0]);
		C[5] += (-A[11]*B[2]+A[13]*B[4]+A[4]*B[0]);
		C[6] += (A[10]*B[2]+A[13]*B[5]-A[3]*B[0]);
		C[7] += (-A[11]*B[3]-A[12]*B[4]-A[2]*B[0]);
		C[8] += (A[1]*B[0]+A[10]*B[3]-A[12]*B[5]);
		C[9] += (-A[0]*B[0]+A[10]*B[4]+A[11]*B[5]);
		C[10] += (-A[5]*B[1]-A[8]*B[2]-A[9]*B[3]);
		C[11] += (A[4]*B[1]+A[7]*B[2]-A[9]*B[4]);
		C[12] += (-A[3]*B[1]-A[6]*B[2]-A[9]*B[5]);
		C[13] += (-A[2]*B[1]+A[7]*B[3]+A[8]*B[4]);
		C[14] += (A[1]*B[1]-A[6]*B[3]+A[8]*B[5]);
		C[15] += (-A[0]*B[1]-A[6]*B[4]-A[7]*B[5]);
		C[16] += (-A[2]*B[2]-A[4]*B[3]-A[5]*B[4]);
		C[17] += (A[1]*B[2]+A[3]*B[3]-A[5]*B[5]);
		C[18] += (-A[0]*B[2]+A[3]*B[4]+A[4]*B[5]);
		C[19] += (-A[0]*B[3]-A[1]*B[4]-A[2]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 5 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__2_5_5(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[5]-A[11]*B[4]+A[12]*B[3]-A[13]*B[2]+A[14]*B[1]);
		C[1] += (-A[14]*B[0]-A[6]*B[5]+A[7]*B[4]-A[8]*B[3]+A[9]*B[2]);
		C[2] += (A[13]*B[0]+A[3]*B[5]-A[4]*B[4]+A[5]*B[3]-A[9]*B[1]);
		C[3] += (-A[1]*B[5]-A[12]*B[0]+A[2]*B[4]-A[5]*B[2]+A[8]*B[1]);
		C[4] += (A[0]*B[5]+A[11]*B[0]-A[2]*B[3]+A[4]*B[2]-A[7]*B[1]);
		C[5] += (-A[0]*B[4]+A[1]*B[3]-A[10]*B[0]-A[3]*B[2]+A[6]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 2  x  group 6 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__2_6_4(float[] A, float[] B, float[] C) {
		C[0] += -A[14]*B[0];
		C[1] += A[13]*B[0];
		C[2] += -A[12]*B[0];
		C[3] += A[11]*B[0];
		C[4] += -A[10]*B[0];
		C[5] += -A[9]*B[0];
		C[6] += A[8]*B[0];
		C[7] += -A[7]*B[0];
		C[8] += A[6]*B[0];
		C[9] += -A[5]*B[0];
		C[10] += A[4]*B[0];
		C[11] += -A[3]*B[0];
		C[12] += -A[2]*B[0];
		C[13] += A[1]*B[0];
		C[14] += -A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 0 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__3_0_3(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[0];
		C[1] += A[1]*B[0];
		C[2] += A[2]*B[0];
		C[3] += A[3]*B[0];
		C[4] += A[4]*B[0];
		C[5] += A[5]*B[0];
		C[6] += A[6]*B[0];
		C[7] += A[7]*B[0];
		C[8] += A[8]*B[0];
		C[9] += A[9]*B[0];
		C[10] += A[10]*B[0];
		C[11] += A[11]*B[0];
		C[12] += A[12]*B[0];
		C[13] += A[13]*B[0];
		C[14] += A[14]*B[0];
		C[15] += A[15]*B[0];
		C[16] += A[16]*B[0];
		C[17] += A[17]*B[0];
		C[18] += A[18]*B[0];
		C[19] += A[19]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__3_1_2(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[2]+A[1]*B[3]+A[10]*B[5]+A[4]*B[4]);
		C[1] += (-A[0]*B[1]+A[11]*B[5]+A[2]*B[3]+A[5]*B[4]);
		C[2] += (A[0]*B[0]+A[12]*B[5]+A[3]*B[3]+A[6]*B[4]);
		C[3] += (-A[1]*B[1]+A[13]*B[5]-A[2]*B[2]+A[7]*B[4]);
		C[4] += (A[1]*B[0]+A[14]*B[5]-A[3]*B[2]+A[8]*B[4]);
		C[5] += (A[15]*B[5]+A[2]*B[0]+A[3]*B[1]+A[9]*B[4]);
		C[6] += (A[16]*B[5]-A[4]*B[1]-A[5]*B[2]-A[7]*B[3]);
		C[7] += (A[17]*B[5]+A[4]*B[0]-A[6]*B[2]-A[8]*B[3]);
		C[8] += (A[18]*B[5]+A[5]*B[0]+A[6]*B[1]-A[9]*B[3]);
		C[9] += (A[19]*B[5]+A[7]*B[0]+A[8]*B[1]+A[9]*B[2]);
		C[10] += (-A[10]*B[1]-A[11]*B[2]-A[13]*B[3]-A[16]*B[4]);
		C[11] += (A[10]*B[0]-A[12]*B[2]-A[14]*B[3]-A[17]*B[4]);
		C[12] += (A[11]*B[0]+A[12]*B[1]-A[15]*B[3]-A[18]*B[4]);
		C[13] += (A[13]*B[0]+A[14]*B[1]+A[15]*B[2]-A[19]*B[4]);
		C[14] += (A[16]*B[0]+A[17]*B[1]+A[18]*B[2]+A[19]*B[3]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 1 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__3_1_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]-A[1]*B[2]+A[2]*B[1]-A[3]*B[0]);
		C[1] += (A[0]*B[4]-A[4]*B[2]+A[5]*B[1]-A[6]*B[0]);
		C[2] += (A[1]*B[4]-A[4]*B[3]+A[7]*B[1]-A[8]*B[0]);
		C[3] += (A[2]*B[4]-A[5]*B[3]+A[7]*B[2]-A[9]*B[0]);
		C[4] += (A[3]*B[4]-A[6]*B[3]+A[8]*B[2]-A[9]*B[1]);
		C[5] += (A[0]*B[5]-A[10]*B[2]+A[11]*B[1]-A[12]*B[0]);
		C[6] += (A[1]*B[5]-A[10]*B[3]+A[13]*B[1]-A[14]*B[0]);
		C[7] += (-A[11]*B[3]+A[13]*B[2]-A[15]*B[0]+A[2]*B[5]);
		C[8] += (-A[12]*B[3]+A[14]*B[2]-A[15]*B[1]+A[3]*B[5]);
		C[9] += (-A[10]*B[4]+A[16]*B[1]-A[17]*B[0]+A[4]*B[5]);
		C[10] += (-A[11]*B[4]+A[16]*B[2]-A[18]*B[0]+A[5]*B[5]);
		C[11] += (-A[12]*B[4]+A[17]*B[2]-A[18]*B[1]+A[6]*B[5]);
		C[12] += (-A[13]*B[4]+A[16]*B[3]-A[19]*B[0]+A[7]*B[5]);
		C[13] += (-A[14]*B[4]+A[17]*B[3]-A[19]*B[1]+A[8]*B[5]);
		C[14] += (-A[15]*B[4]+A[18]*B[3]-A[19]*B[2]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__3_2_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[2]-A[1]*B[4]-A[10]*B[11]-A[11]*B[12]-A[13]*B[13]-A[16]*B[14]-A[2]*B[5]-A[4]*B[7]-A[5]*B[8]-A[7]*B[9]);
		C[1] += (A[0]*B[1]+A[1]*B[3]+A[10]*B[10]-A[12]*B[12]-A[14]*B[13]-A[17]*B[14]-A[3]*B[5]+A[4]*B[6]-A[6]*B[8]-A[8]*B[9]);
		C[2] += (-A[0]*B[0]+A[11]*B[10]+A[12]*B[11]-A[15]*B[13]-A[18]*B[14]+A[2]*B[3]+A[3]*B[4]+A[5]*B[6]+A[6]*B[7]-A[9]*B[9]);
		C[3] += (-A[1]*B[0]+A[13]*B[10]+A[14]*B[11]+A[15]*B[12]-A[19]*B[14]-A[2]*B[1]-A[3]*B[2]+A[7]*B[6]+A[8]*B[7]+A[9]*B[8]);
		C[4] += (A[16]*B[10]+A[17]*B[11]+A[18]*B[12]+A[19]*B[13]-A[4]*B[0]-A[5]*B[1]-A[6]*B[2]-A[7]*B[3]-A[8]*B[4]-A[9]*B[5]);
		C[5] += (-A[10]*B[0]-A[11]*B[1]-A[12]*B[2]-A[13]*B[3]-A[14]*B[4]-A[15]*B[5]-A[16]*B[6]-A[17]*B[7]-A[18]*B[8]-A[19]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__3_2_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[1]*B[5]-A[10]*B[12]+A[11]*B[11]-A[12]*B[10]+A[2]*B[4]-A[3]*B[3]-A[4]*B[8]+A[5]*B[7]-A[6]*B[6]);
		C[1] += (A[0]*B[5]-A[10]*B[13]+A[13]*B[11]-A[14]*B[10]-A[2]*B[2]+A[3]*B[1]-A[4]*B[9]+A[7]*B[7]-A[8]*B[6]);
		C[2] += (-A[0]*B[4]+A[1]*B[2]-A[11]*B[13]+A[13]*B[12]-A[15]*B[10]-A[3]*B[0]-A[5]*B[9]+A[7]*B[8]-A[9]*B[6]);
		C[3] += (A[0]*B[3]-A[1]*B[1]-A[12]*B[13]+A[14]*B[12]-A[15]*B[11]+A[2]*B[0]-A[6]*B[9]+A[8]*B[8]-A[9]*B[7]);
		C[4] += (A[0]*B[8]+A[1]*B[9]-A[10]*B[14]+A[16]*B[11]-A[17]*B[10]-A[5]*B[2]+A[6]*B[1]-A[7]*B[4]+A[8]*B[3]);
		C[5] += (-A[0]*B[7]-A[11]*B[14]+A[16]*B[12]-A[18]*B[10]+A[2]*B[9]+A[4]*B[2]-A[6]*B[0]-A[7]*B[5]+A[9]*B[3]);
		C[6] += (A[0]*B[6]-A[12]*B[14]+A[17]*B[12]-A[18]*B[11]+A[3]*B[9]-A[4]*B[1]+A[5]*B[0]-A[8]*B[5]+A[9]*B[4]);
		C[7] += (-A[1]*B[7]-A[13]*B[14]+A[16]*B[13]-A[19]*B[10]-A[2]*B[8]+A[4]*B[4]+A[5]*B[5]-A[8]*B[0]-A[9]*B[1]);
		C[8] += (A[1]*B[6]-A[14]*B[14]+A[17]*B[13]-A[19]*B[11]-A[3]*B[8]-A[4]*B[3]+A[6]*B[5]+A[7]*B[0]-A[9]*B[2]);
		C[9] += (-A[15]*B[14]+A[18]*B[13]-A[19]*B[12]+A[2]*B[6]+A[3]*B[7]-A[5]*B[3]-A[6]*B[4]+A[7]*B[1]+A[8]*B[2]);
		C[10] += (A[0]*B[12]+A[1]*B[13]-A[11]*B[2]+A[12]*B[1]-A[13]*B[4]+A[14]*B[3]-A[16]*B[7]+A[17]*B[6]+A[4]*B[14]);
		C[11] += (-A[0]*B[11]+A[10]*B[2]-A[12]*B[0]-A[13]*B[5]+A[15]*B[3]-A[16]*B[8]+A[18]*B[6]+A[2]*B[13]+A[5]*B[14]);
		C[12] += (A[0]*B[10]-A[10]*B[1]+A[11]*B[0]-A[14]*B[5]+A[15]*B[4]-A[17]*B[8]+A[18]*B[7]+A[3]*B[13]+A[6]*B[14]);
		C[13] += (-A[1]*B[11]+A[10]*B[4]+A[11]*B[5]-A[14]*B[0]-A[15]*B[1]-A[16]*B[9]+A[19]*B[6]-A[2]*B[12]+A[7]*B[14]);
		C[14] += (A[1]*B[10]-A[10]*B[3]+A[12]*B[5]+A[13]*B[0]-A[15]*B[2]-A[17]*B[9]+A[19]*B[7]-A[3]*B[12]+A[8]*B[14]);
		C[15] += (-A[11]*B[3]-A[12]*B[4]+A[13]*B[1]+A[14]*B[2]-A[18]*B[9]+A[19]*B[8]+A[2]*B[10]+A[3]*B[11]+A[9]*B[14]);
		C[16] += (A[10]*B[7]+A[11]*B[8]+A[13]*B[9]-A[17]*B[0]-A[18]*B[1]-A[19]*B[3]-A[4]*B[11]-A[5]*B[12]-A[7]*B[13]);
		C[17] += (-A[10]*B[6]+A[12]*B[8]+A[14]*B[9]+A[16]*B[0]-A[18]*B[2]-A[19]*B[4]+A[4]*B[10]-A[6]*B[12]-A[8]*B[13]);
		C[18] += (-A[11]*B[6]-A[12]*B[7]+A[15]*B[9]+A[16]*B[1]+A[17]*B[2]-A[19]*B[5]+A[5]*B[10]+A[6]*B[11]-A[9]*B[13]);
		C[19] += (-A[13]*B[6]-A[14]*B[7]-A[15]*B[8]+A[16]*B[3]+A[17]*B[4]+A[18]*B[5]+A[7]*B[10]+A[8]*B[11]+A[9]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 2 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__3_2_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[9]-A[1]*B[8]+A[2]*B[7]-A[3]*B[6]+A[4]*B[5]-A[5]*B[4]+A[6]*B[3]+A[7]*B[2]-A[8]*B[1]+A[9]*B[0]);
		C[1] += (A[0]*B[13]-A[1]*B[12]+A[10]*B[5]-A[11]*B[4]+A[12]*B[3]+A[13]*B[2]-A[14]*B[1]+A[15]*B[0]+A[2]*B[11]-A[3]*B[10]);
		C[2] += (A[0]*B[14]+A[10]*B[8]-A[11]*B[7]+A[12]*B[6]+A[16]*B[2]-A[17]*B[1]+A[18]*B[0]-A[4]*B[12]+A[5]*B[11]-A[6]*B[10]);
		C[3] += (A[1]*B[14]+A[10]*B[9]-A[13]*B[7]+A[14]*B[6]+A[16]*B[4]-A[17]*B[3]+A[19]*B[0]-A[4]*B[13]+A[7]*B[11]-A[8]*B[10]);
		C[4] += (A[11]*B[9]-A[13]*B[8]+A[15]*B[6]+A[16]*B[5]-A[18]*B[3]+A[19]*B[1]+A[2]*B[14]-A[5]*B[13]+A[7]*B[12]-A[9]*B[10]);
		C[5] += (A[12]*B[9]-A[14]*B[8]+A[15]*B[7]+A[17]*B[5]-A[18]*B[4]+A[19]*B[2]+A[3]*B[14]-A[6]*B[13]+A[8]*B[12]-A[9]*B[11]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__3_3_0(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[0]-A[1]*B[1]-A[10]*B[10]-A[11]*B[11]-A[12]*B[12]-A[13]*B[13]-A[14]*B[14]-A[15]*B[15]-A[16]*B[16]-A[17]*B[17]-A[18]*B[18]-A[19]*B[19]-A[2]*B[2]-A[3]*B[3]-A[4]*B[4]-A[5]*B[5]-A[6]*B[6]-A[7]*B[7]-A[8]*B[8]-A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__3_3_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[11]*B[12]+A[12]*B[11]-A[13]*B[14]+A[14]*B[13]-A[16]*B[17]+A[17]*B[16]-A[2]*B[3]+A[3]*B[2]-A[5]*B[6]+A[6]*B[5]-A[7]*B[8]+A[8]*B[7]);
		C[1] += (A[1]*B[3]+A[10]*B[12]-A[12]*B[10]-A[13]*B[15]+A[15]*B[13]-A[16]*B[18]+A[18]*B[16]-A[3]*B[1]+A[4]*B[6]-A[6]*B[4]-A[7]*B[9]+A[9]*B[7]);
		C[2] += (-A[1]*B[2]-A[10]*B[11]+A[11]*B[10]-A[14]*B[15]+A[15]*B[14]-A[17]*B[18]+A[18]*B[17]+A[2]*B[1]-A[4]*B[5]+A[5]*B[4]-A[8]*B[9]+A[9]*B[8]);
		C[3] += (-A[0]*B[3]+A[10]*B[14]+A[11]*B[15]-A[14]*B[10]-A[15]*B[11]-A[16]*B[19]+A[19]*B[16]+A[3]*B[0]+A[4]*B[8]+A[5]*B[9]-A[8]*B[4]-A[9]*B[5]);
		C[4] += (A[0]*B[2]-A[10]*B[13]+A[12]*B[15]+A[13]*B[10]-A[15]*B[12]-A[17]*B[19]+A[19]*B[17]-A[2]*B[0]-A[4]*B[7]+A[6]*B[9]+A[7]*B[4]-A[9]*B[6]);
		C[5] += (-A[0]*B[1]+A[1]*B[0]-A[11]*B[13]-A[12]*B[14]+A[13]*B[11]+A[14]*B[12]-A[18]*B[19]+A[19]*B[18]-A[5]*B[7]-A[6]*B[8]+A[7]*B[5]+A[8]*B[6]);
		C[6] += (-A[0]*B[6]-A[1]*B[8]+A[10]*B[17]+A[11]*B[18]+A[13]*B[19]-A[17]*B[10]-A[18]*B[11]-A[19]*B[13]-A[2]*B[9]+A[6]*B[0]+A[8]*B[1]+A[9]*B[2]);
		C[7] += (A[0]*B[5]+A[1]*B[7]-A[10]*B[16]+A[12]*B[18]+A[14]*B[19]+A[16]*B[10]-A[18]*B[12]-A[19]*B[14]-A[3]*B[9]-A[5]*B[0]-A[7]*B[1]+A[9]*B[3]);
		C[8] += (-A[0]*B[4]-A[11]*B[16]-A[12]*B[17]+A[15]*B[19]+A[16]*B[11]+A[17]*B[12]-A[19]*B[15]+A[2]*B[7]+A[3]*B[8]+A[4]*B[0]-A[7]*B[2]-A[8]*B[3]);
		C[9] += (-A[1]*B[4]-A[13]*B[16]-A[14]*B[17]-A[15]*B[18]+A[16]*B[13]+A[17]*B[14]+A[18]*B[15]-A[2]*B[5]-A[3]*B[6]+A[4]*B[1]+A[5]*B[2]+A[6]*B[3]);
		C[10] += (-A[0]*B[12]-A[1]*B[14]+A[12]*B[0]+A[14]*B[1]+A[15]*B[2]+A[17]*B[4]+A[18]*B[5]+A[19]*B[7]-A[2]*B[15]-A[4]*B[17]-A[5]*B[18]-A[7]*B[19]);
		C[11] += (A[0]*B[11]+A[1]*B[13]-A[11]*B[0]-A[13]*B[1]+A[15]*B[3]-A[16]*B[4]+A[18]*B[6]+A[19]*B[8]-A[3]*B[15]+A[4]*B[16]-A[6]*B[18]-A[8]*B[19]);
		C[12] += (-A[0]*B[10]+A[10]*B[0]-A[13]*B[2]-A[14]*B[3]-A[16]*B[5]-A[17]*B[6]+A[19]*B[9]+A[2]*B[13]+A[3]*B[14]+A[5]*B[16]+A[6]*B[17]-A[9]*B[19]);
		C[13] += (-A[1]*B[10]+A[10]*B[1]+A[11]*B[2]+A[12]*B[3]-A[16]*B[7]-A[17]*B[8]-A[18]*B[9]-A[2]*B[11]-A[3]*B[12]+A[7]*B[16]+A[8]*B[17]+A[9]*B[18]);
		C[14] += (A[10]*B[4]+A[11]*B[5]+A[12]*B[6]+A[13]*B[7]+A[14]*B[8]+A[15]*B[9]-A[4]*B[10]-A[5]*B[11]-A[6]*B[12]-A[7]*B[13]-A[8]*B[14]-A[9]*B[15]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__3_3_4(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[15]-A[11]*B[14]+A[12]*B[13]+A[13]*B[12]-A[14]*B[11]+A[15]*B[10]+A[4]*B[9]-A[5]*B[8]+A[6]*B[7]+A[7]*B[6]-A[8]*B[5]+A[9]*B[4]);
		C[1] += (-A[1]*B[9]+A[10]*B[18]-A[11]*B[17]+A[12]*B[16]+A[16]*B[12]-A[17]*B[11]+A[18]*B[10]+A[2]*B[8]-A[3]*B[7]-A[7]*B[3]+A[8]*B[2]-A[9]*B[1]);
		C[2] += (A[0]*B[9]+A[10]*B[19]-A[13]*B[17]+A[14]*B[16]+A[16]*B[14]-A[17]*B[13]+A[19]*B[10]-A[2]*B[6]+A[3]*B[5]+A[5]*B[3]-A[6]*B[2]+A[9]*B[0]);
		C[3] += (-A[0]*B[8]+A[1]*B[6]+A[11]*B[19]-A[13]*B[18]+A[15]*B[16]+A[16]*B[15]-A[18]*B[13]+A[19]*B[11]-A[3]*B[4]-A[4]*B[3]+A[6]*B[1]-A[8]*B[0]);
		C[4] += (A[0]*B[7]-A[1]*B[5]+A[12]*B[19]-A[14]*B[18]+A[15]*B[17]+A[17]*B[15]-A[18]*B[14]+A[19]*B[12]+A[2]*B[4]+A[4]*B[2]-A[5]*B[1]+A[7]*B[0]);
		C[5] += (-A[1]*B[15]-A[13]*B[3]+A[14]*B[2]-A[15]*B[1]-A[16]*B[6]+A[17]*B[5]-A[18]*B[4]+A[2]*B[14]-A[3]*B[13]-A[4]*B[18]+A[5]*B[17]-A[6]*B[16]);
		C[6] += (A[0]*B[15]+A[11]*B[3]-A[12]*B[2]+A[15]*B[0]-A[16]*B[8]+A[17]*B[7]-A[19]*B[4]-A[2]*B[12]+A[3]*B[11]-A[4]*B[19]+A[7]*B[17]-A[8]*B[16]);
		C[7] += (-A[0]*B[14]+A[1]*B[12]-A[10]*B[3]+A[12]*B[1]-A[14]*B[0]-A[16]*B[9]+A[18]*B[7]-A[19]*B[5]-A[3]*B[10]-A[5]*B[19]+A[7]*B[18]-A[9]*B[16]);
		C[8] += (A[0]*B[13]-A[1]*B[11]+A[10]*B[2]-A[11]*B[1]+A[13]*B[0]-A[17]*B[9]+A[18]*B[8]-A[19]*B[6]+A[2]*B[10]-A[6]*B[19]+A[8]*B[18]-A[9]*B[17]);
		C[9] += (A[0]*B[18]+A[1]*B[19]+A[11]*B[6]-A[12]*B[5]+A[13]*B[8]-A[14]*B[7]+A[18]*B[0]+A[19]*B[1]-A[5]*B[12]+A[6]*B[11]-A[7]*B[14]+A[8]*B[13]);
		C[10] += (-A[0]*B[17]-A[10]*B[6]+A[12]*B[4]+A[13]*B[9]-A[15]*B[7]-A[17]*B[0]+A[19]*B[2]+A[2]*B[19]+A[4]*B[12]-A[6]*B[10]-A[7]*B[15]+A[9]*B[13]);
		C[11] += (A[0]*B[16]+A[10]*B[5]-A[11]*B[4]+A[14]*B[9]-A[15]*B[8]+A[16]*B[0]+A[19]*B[3]+A[3]*B[19]-A[4]*B[11]+A[5]*B[10]-A[8]*B[15]+A[9]*B[14]);
		C[12] += (-A[1]*B[17]-A[10]*B[8]-A[11]*B[9]+A[14]*B[4]+A[15]*B[5]-A[17]*B[1]-A[18]*B[2]-A[2]*B[18]+A[4]*B[14]+A[5]*B[15]-A[8]*B[10]-A[9]*B[11]);
		C[13] += (A[1]*B[16]+A[10]*B[7]-A[12]*B[9]-A[13]*B[4]+A[15]*B[6]+A[16]*B[1]-A[18]*B[3]-A[3]*B[18]-A[4]*B[13]+A[6]*B[15]+A[7]*B[10]-A[9]*B[12]);
		C[14] += (A[11]*B[7]+A[12]*B[8]-A[13]*B[5]-A[14]*B[6]+A[16]*B[2]+A[17]*B[3]+A[2]*B[16]+A[3]*B[17]-A[5]*B[13]-A[6]*B[14]+A[7]*B[11]+A[8]*B[12]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 3 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__3_3_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[19]-A[1]*B[18]-A[10]*B[9]+A[11]*B[8]-A[12]*B[7]-A[13]*B[6]+A[14]*B[5]-A[15]*B[4]+A[16]*B[3]-A[17]*B[2]+A[18]*B[1]-A[19]*B[0]+A[2]*B[17]-A[3]*B[16]+A[4]*B[15]-A[5]*B[14]+A[6]*B[13]+A[7]*B[12]-A[8]*B[11]+A[9]*B[10]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__3_4_1(float[] A, float[] B, float[] C) {
		C[0] += (A[12]*B[5]+A[14]*B[6]+A[15]*B[7]+A[17]*B[9]+A[18]*B[10]+A[19]*B[12]+A[3]*B[0]+A[6]*B[1]+A[8]*B[2]+A[9]*B[3]);
		C[1] += (-A[11]*B[5]-A[13]*B[6]+A[15]*B[8]-A[16]*B[9]+A[18]*B[11]+A[19]*B[13]-A[2]*B[0]-A[5]*B[1]-A[7]*B[2]+A[9]*B[4]);
		C[2] += (A[1]*B[0]+A[10]*B[5]-A[13]*B[7]-A[14]*B[8]-A[16]*B[10]-A[17]*B[11]+A[19]*B[14]+A[4]*B[1]-A[7]*B[3]-A[8]*B[4]);
		C[3] += (-A[0]*B[0]+A[10]*B[6]+A[11]*B[7]+A[12]*B[8]-A[16]*B[12]-A[17]*B[13]-A[18]*B[14]+A[4]*B[2]+A[5]*B[3]+A[6]*B[4]);
		C[4] += (-A[0]*B[1]-A[1]*B[2]+A[10]*B[9]+A[11]*B[10]+A[12]*B[11]+A[13]*B[12]+A[14]*B[13]+A[15]*B[14]-A[2]*B[3]-A[3]*B[4]);
		C[5] += (-A[0]*B[5]-A[1]*B[6]-A[2]*B[7]-A[3]*B[8]-A[4]*B[9]-A[5]*B[10]-A[6]*B[11]-A[7]*B[12]-A[8]*B[13]-A[9]*B[14]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__3_4_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[13]*B[8]+A[14]*B[7]-A[15]*B[6]-A[16]*B[11]+A[17]*B[10]-A[18]*B[9]-A[7]*B[4]+A[8]*B[3]-A[9]*B[2]);
		C[1] += (A[11]*B[8]-A[12]*B[7]+A[15]*B[5]-A[16]*B[13]+A[17]*B[12]-A[19]*B[9]+A[5]*B[4]-A[6]*B[3]+A[9]*B[1]);
		C[2] += (-A[10]*B[8]+A[12]*B[6]-A[14]*B[5]-A[16]*B[14]+A[18]*B[12]-A[19]*B[10]-A[4]*B[4]+A[6]*B[2]-A[8]*B[1]);
		C[3] += (A[10]*B[7]-A[11]*B[6]+A[13]*B[5]-A[17]*B[14]+A[18]*B[13]-A[19]*B[11]+A[4]*B[3]-A[5]*B[2]+A[7]*B[1]);
		C[4] += (A[11]*B[11]-A[12]*B[10]+A[13]*B[13]-A[14]*B[12]+A[18]*B[5]+A[19]*B[6]-A[2]*B[4]+A[3]*B[3]-A[9]*B[0]);
		C[5] += (A[1]*B[4]-A[10]*B[11]+A[12]*B[9]+A[13]*B[14]-A[15]*B[12]-A[17]*B[5]+A[19]*B[7]-A[3]*B[2]+A[8]*B[0]);
		C[6] += (-A[1]*B[3]+A[10]*B[10]-A[11]*B[9]+A[14]*B[14]-A[15]*B[13]+A[16]*B[5]+A[19]*B[8]+A[2]*B[2]-A[7]*B[0]);
		C[7] += (-A[0]*B[4]-A[10]*B[13]-A[11]*B[14]+A[14]*B[9]+A[15]*B[10]-A[17]*B[6]-A[18]*B[7]+A[3]*B[1]-A[6]*B[0]);
		C[8] += (A[0]*B[3]+A[10]*B[12]-A[12]*B[14]-A[13]*B[9]+A[15]*B[11]+A[16]*B[6]-A[18]*B[8]-A[2]*B[1]+A[5]*B[0]);
		C[9] += (-A[0]*B[2]+A[1]*B[1]+A[11]*B[12]+A[12]*B[13]-A[13]*B[10]-A[14]*B[11]+A[16]*B[7]+A[17]*B[8]-A[4]*B[0]);
		C[10] += (-A[15]*B[0]-A[18]*B[1]-A[19]*B[2]-A[2]*B[8]+A[3]*B[7]-A[5]*B[11]+A[6]*B[10]-A[7]*B[13]+A[8]*B[12]);
		C[11] += (A[1]*B[8]+A[14]*B[0]+A[17]*B[1]-A[19]*B[3]-A[3]*B[6]+A[4]*B[11]-A[6]*B[9]-A[7]*B[14]+A[9]*B[12]);
		C[12] += (-A[1]*B[7]-A[13]*B[0]-A[16]*B[1]-A[19]*B[4]+A[2]*B[6]-A[4]*B[10]+A[5]*B[9]-A[8]*B[14]+A[9]*B[13]);
		C[13] += (-A[0]*B[8]-A[12]*B[0]+A[17]*B[2]+A[18]*B[3]+A[3]*B[5]+A[4]*B[13]+A[5]*B[14]-A[8]*B[9]-A[9]*B[10]);
		C[14] += (A[0]*B[7]+A[11]*B[0]-A[16]*B[2]+A[18]*B[4]-A[2]*B[5]-A[4]*B[12]+A[6]*B[14]+A[7]*B[9]-A[9]*B[11]);
		C[15] += (-A[0]*B[6]+A[1]*B[5]-A[10]*B[0]-A[16]*B[3]-A[17]*B[4]-A[5]*B[12]-A[6]*B[13]+A[7]*B[10]+A[8]*B[11]);
		C[16] += (-A[0]*B[11]-A[1]*B[13]-A[12]*B[1]-A[14]*B[2]-A[15]*B[3]-A[2]*B[14]+A[6]*B[5]+A[8]*B[6]+A[9]*B[7]);
		C[17] += (A[0]*B[10]+A[1]*B[12]+A[11]*B[1]+A[13]*B[2]-A[15]*B[4]-A[3]*B[14]-A[5]*B[5]-A[7]*B[6]+A[9]*B[8]);
		C[18] += (-A[0]*B[9]-A[10]*B[1]+A[13]*B[3]+A[14]*B[4]+A[2]*B[12]+A[3]*B[13]+A[4]*B[5]-A[7]*B[7]-A[8]*B[8]);
		C[19] += (-A[1]*B[9]-A[10]*B[2]-A[11]*B[3]-A[12]*B[4]-A[2]*B[10]-A[3]*B[11]+A[4]*B[6]+A[5]*B[7]+A[6]*B[8]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 4 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__3_4_5(float[] A, float[] B, float[] C) {
		C[0] += (-A[10]*B[14]+A[11]*B[13]-A[12]*B[12]-A[13]*B[11]+A[14]*B[10]-A[15]*B[9]+A[16]*B[8]-A[17]*B[7]+A[18]*B[6]-A[19]*B[5]);
		C[1] += (-A[16]*B[4]+A[17]*B[3]-A[18]*B[2]+A[19]*B[1]+A[4]*B[14]-A[5]*B[13]+A[6]*B[12]+A[7]*B[11]-A[8]*B[10]+A[9]*B[9]);
		C[2] += (-A[1]*B[14]+A[13]*B[4]-A[14]*B[3]+A[15]*B[2]-A[19]*B[0]+A[2]*B[13]-A[3]*B[12]-A[7]*B[8]+A[8]*B[7]-A[9]*B[6]);
		C[3] += (A[0]*B[14]-A[11]*B[4]+A[12]*B[3]-A[15]*B[1]+A[18]*B[0]-A[2]*B[11]+A[3]*B[10]+A[5]*B[8]-A[6]*B[7]+A[9]*B[5]);
		C[4] += (-A[0]*B[13]+A[1]*B[11]+A[10]*B[4]-A[12]*B[2]+A[14]*B[1]-A[17]*B[0]-A[3]*B[9]-A[4]*B[8]+A[6]*B[6]-A[8]*B[5]);
		C[5] += (A[0]*B[12]-A[1]*B[10]-A[10]*B[3]+A[11]*B[2]-A[13]*B[1]+A[16]*B[0]+A[2]*B[9]+A[4]*B[7]-A[5]*B[6]+A[7]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 5 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__3_5_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[15]*B[1]-A[18]*B[2]-A[19]*B[3]-A[9]*B[0]);
		C[1] += (A[14]*B[1]+A[17]*B[2]-A[19]*B[4]+A[8]*B[0]);
		C[2] += (-A[13]*B[1]-A[16]*B[2]-A[19]*B[5]-A[7]*B[0]);
		C[3] += (-A[12]*B[1]+A[17]*B[3]+A[18]*B[4]-A[6]*B[0]);
		C[4] += (A[11]*B[1]-A[16]*B[3]+A[18]*B[5]+A[5]*B[0]);
		C[5] += (-A[10]*B[1]-A[16]*B[4]-A[17]*B[5]-A[4]*B[0]);
		C[6] += (-A[12]*B[2]-A[14]*B[3]-A[15]*B[4]+A[3]*B[0]);
		C[7] += (A[11]*B[2]+A[13]*B[3]-A[15]*B[5]-A[2]*B[0]);
		C[8] += (A[1]*B[0]-A[10]*B[2]+A[13]*B[4]+A[14]*B[5]);
		C[9] += (-A[0]*B[0]-A[10]*B[3]-A[11]*B[4]-A[12]*B[5]);
		C[10] += (A[3]*B[1]+A[6]*B[2]+A[8]*B[3]+A[9]*B[4]);
		C[11] += (-A[2]*B[1]-A[5]*B[2]-A[7]*B[3]+A[9]*B[5]);
		C[12] += (A[1]*B[1]+A[4]*B[2]-A[7]*B[4]-A[8]*B[5]);
		C[13] += (-A[0]*B[1]+A[4]*B[3]+A[5]*B[4]+A[6]*B[5]);
		C[14] += (-A[0]*B[2]-A[1]*B[3]-A[2]*B[4]-A[3]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 5 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__3_5_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[16]*B[5]+A[17]*B[4]-A[18]*B[3]+A[19]*B[2]);
		C[1] += (A[13]*B[5]-A[14]*B[4]+A[15]*B[3]-A[19]*B[1]);
		C[2] += (-A[11]*B[5]+A[12]*B[4]-A[15]*B[2]+A[18]*B[1]);
		C[3] += (A[10]*B[5]-A[12]*B[3]+A[14]*B[2]-A[17]*B[1]);
		C[4] += (-A[10]*B[4]+A[11]*B[3]-A[13]*B[2]+A[16]*B[1]);
		C[5] += (A[19]*B[0]-A[7]*B[5]+A[8]*B[4]-A[9]*B[3]);
		C[6] += (-A[18]*B[0]+A[5]*B[5]-A[6]*B[4]+A[9]*B[2]);
		C[7] += (A[17]*B[0]-A[4]*B[5]+A[6]*B[3]-A[8]*B[2]);
		C[8] += (-A[16]*B[0]+A[4]*B[4]-A[5]*B[3]+A[7]*B[2]);
		C[9] += (A[15]*B[0]-A[2]*B[5]+A[3]*B[4]-A[9]*B[1]);
		C[10] += (A[1]*B[5]-A[14]*B[0]-A[3]*B[3]+A[8]*B[1]);
		C[11] += (-A[1]*B[4]+A[13]*B[0]+A[2]*B[3]-A[7]*B[1]);
		C[12] += (-A[0]*B[5]+A[12]*B[0]+A[3]*B[2]-A[6]*B[1]);
		C[13] += (A[0]*B[4]-A[11]*B[0]-A[2]*B[2]+A[5]*B[1]);
		C[14] += (-A[0]*B[3]+A[1]*B[2]+A[10]*B[0]-A[4]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 3  x  group 6 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__3_6_3(float[] A, float[] B, float[] C) {
		C[0] += A[19]*B[0];
		C[1] += -A[18]*B[0];
		C[2] += A[17]*B[0];
		C[3] += -A[16]*B[0];
		C[4] += A[15]*B[0];
		C[5] += -A[14]*B[0];
		C[6] += A[13]*B[0];
		C[7] += A[12]*B[0];
		C[8] += -A[11]*B[0];
		C[9] += A[10]*B[0];
		C[10] += -A[9]*B[0];
		C[11] += A[8]*B[0];
		C[12] += -A[7]*B[0];
		C[13] += -A[6]*B[0];
		C[14] += A[5]*B[0];
		C[15] += -A[4]*B[0];
		C[16] += A[3]*B[0];
		C[17] += -A[2]*B[0];
		C[18] += A[1]*B[0];
		C[19] += -A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 0 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__4_0_4(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__2_0_2(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__4_1_3(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[3]+A[1]*B[4]+A[5]*B[5]);
		C[1] += (-A[0]*B[2]+A[2]*B[4]+A[6]*B[5]);
		C[2] += (A[0]*B[1]+A[3]*B[4]+A[7]*B[5]);
		C[3] += (-A[0]*B[0]+A[4]*B[4]+A[8]*B[5]);
		C[4] += (-A[1]*B[2]-A[2]*B[3]+A[9]*B[5]);
		C[5] += (A[1]*B[1]+A[10]*B[5]-A[3]*B[3]);
		C[6] += (-A[1]*B[0]+A[11]*B[5]-A[4]*B[3]);
		C[7] += (A[12]*B[5]+A[2]*B[1]+A[3]*B[2]);
		C[8] += (A[13]*B[5]-A[2]*B[0]+A[4]*B[2]);
		C[9] += (A[14]*B[5]-A[3]*B[0]-A[4]*B[1]);
		C[10] += (-A[5]*B[2]-A[6]*B[3]-A[9]*B[4]);
		C[11] += (-A[10]*B[4]+A[5]*B[1]-A[7]*B[3]);
		C[12] += (-A[11]*B[4]-A[5]*B[0]-A[8]*B[3]);
		C[13] += (-A[12]*B[4]+A[6]*B[1]+A[7]*B[2]);
		C[14] += (-A[13]*B[4]-A[6]*B[0]+A[8]*B[2]);
		C[15] += (-A[14]*B[4]-A[7]*B[0]-A[8]*B[1]);
		C[16] += (A[10]*B[2]+A[12]*B[3]+A[9]*B[1]);
		C[17] += (A[11]*B[2]+A[13]*B[3]-A[9]*B[0]);
		C[18] += (-A[10]*B[0]-A[11]*B[1]+A[14]*B[3]);
		C[19] += (-A[12]*B[0]-A[13]*B[1]-A[14]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 1 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__4_1_5(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]-A[1]*B[3]+A[2]*B[2]-A[3]*B[1]+A[4]*B[0]);
		C[1] += (A[0]*B[5]-A[5]*B[3]+A[6]*B[2]-A[7]*B[1]+A[8]*B[0]);
		C[2] += (A[1]*B[5]-A[10]*B[1]+A[11]*B[0]-A[5]*B[4]+A[9]*B[2]);
		C[3] += (-A[12]*B[1]+A[13]*B[0]+A[2]*B[5]-A[6]*B[4]+A[9]*B[3]);
		C[4] += (A[10]*B[3]-A[12]*B[2]+A[14]*B[0]+A[3]*B[5]-A[7]*B[4]);
		C[5] += (A[11]*B[3]-A[13]*B[2]+A[14]*B[1]+A[4]*B[5]-A[8]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__4_2_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[5]-A[1]*B[8]-A[2]*B[9]-A[5]*B[12]-A[6]*B[13]-A[9]*B[14]);
		C[1] += (A[0]*B[4]+A[1]*B[7]-A[10]*B[14]-A[3]*B[9]+A[5]*B[11]-A[7]*B[13]);
		C[2] += (-A[0]*B[3]-A[1]*B[6]-A[11]*B[14]-A[4]*B[9]-A[5]*B[10]-A[8]*B[13]);
		C[3] += (-A[0]*B[2]-A[12]*B[14]+A[2]*B[7]+A[3]*B[8]+A[6]*B[11]+A[7]*B[12]);
		C[4] += (A[0]*B[1]-A[13]*B[14]-A[2]*B[6]+A[4]*B[8]-A[6]*B[10]+A[8]*B[12]);
		C[5] += (-A[0]*B[0]-A[14]*B[14]-A[3]*B[6]-A[4]*B[7]-A[7]*B[10]-A[8]*B[11]);
		C[6] += (-A[1]*B[2]+A[10]*B[12]+A[12]*B[13]-A[2]*B[4]-A[3]*B[5]+A[9]*B[11]);
		C[7] += (A[1]*B[1]+A[11]*B[12]+A[13]*B[13]+A[2]*B[3]-A[4]*B[5]-A[9]*B[10]);
		C[8] += (-A[1]*B[0]-A[10]*B[10]-A[11]*B[11]+A[14]*B[13]+A[3]*B[3]+A[4]*B[4]);
		C[9] += (-A[12]*B[10]-A[13]*B[11]-A[14]*B[12]-A[2]*B[0]-A[3]*B[1]-A[4]*B[2]);
		C[10] += (-A[10]*B[8]-A[12]*B[9]-A[5]*B[2]-A[6]*B[4]-A[7]*B[5]-A[9]*B[7]);
		C[11] += (-A[11]*B[8]-A[13]*B[9]+A[5]*B[1]+A[6]*B[3]-A[8]*B[5]+A[9]*B[6]);
		C[12] += (A[10]*B[6]+A[11]*B[7]-A[14]*B[9]-A[5]*B[0]+A[7]*B[3]+A[8]*B[4]);
		C[13] += (A[12]*B[6]+A[13]*B[7]+A[14]*B[8]-A[6]*B[0]-A[7]*B[1]-A[8]*B[2]);
		C[14] += (-A[10]*B[1]-A[11]*B[2]-A[12]*B[3]-A[13]*B[4]-A[14]*B[5]-A[9]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__4_2_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[1]*B[9]+A[2]*B[8]-A[3]*B[7]+A[4]*B[6]-A[5]*B[13]+A[6]*B[12]-A[7]*B[11]+A[8]*B[10]);
		C[1] += (A[0]*B[9]-A[10]*B[11]+A[11]*B[10]-A[2]*B[5]+A[3]*B[4]-A[4]*B[3]-A[5]*B[14]+A[9]*B[12]);
		C[2] += (-A[0]*B[8]+A[1]*B[5]-A[12]*B[11]+A[13]*B[10]-A[3]*B[2]+A[4]*B[1]-A[6]*B[14]+A[9]*B[13]);
		C[3] += (A[0]*B[7]-A[1]*B[4]+A[10]*B[13]-A[12]*B[12]+A[14]*B[10]+A[2]*B[2]-A[4]*B[0]-A[7]*B[14]);
		C[4] += (-A[0]*B[6]+A[1]*B[3]+A[11]*B[13]-A[13]*B[12]+A[14]*B[11]-A[2]*B[1]+A[3]*B[0]-A[8]*B[14]);
		C[5] += (A[0]*B[13]+A[1]*B[14]+A[10]*B[7]-A[11]*B[6]-A[6]*B[5]+A[7]*B[4]-A[8]*B[3]-A[9]*B[8]);
		C[6] += (-A[0]*B[12]+A[12]*B[7]-A[13]*B[6]+A[2]*B[14]+A[5]*B[5]-A[7]*B[2]+A[8]*B[1]-A[9]*B[9]);
		C[7] += (A[0]*B[11]-A[10]*B[9]+A[12]*B[8]-A[14]*B[6]+A[3]*B[14]-A[5]*B[4]+A[6]*B[2]-A[8]*B[0]);
		C[8] += (-A[0]*B[10]-A[11]*B[9]+A[13]*B[8]-A[14]*B[7]+A[4]*B[14]+A[5]*B[3]-A[6]*B[1]+A[7]*B[0]);
		C[9] += (-A[1]*B[12]-A[10]*B[2]+A[11]*B[1]-A[12]*B[4]+A[13]*B[3]-A[2]*B[13]+A[5]*B[8]+A[6]*B[9]);
		C[10] += (A[1]*B[11]-A[11]*B[0]-A[12]*B[5]+A[14]*B[3]-A[3]*B[13]-A[5]*B[7]+A[7]*B[9]+A[9]*B[2]);
		C[11] += (-A[1]*B[10]+A[10]*B[0]-A[13]*B[5]+A[14]*B[4]-A[4]*B[13]+A[5]*B[6]+A[8]*B[9]-A[9]*B[1]);
		C[12] += (A[10]*B[5]-A[13]*B[0]-A[14]*B[1]+A[2]*B[11]+A[3]*B[12]-A[6]*B[7]-A[7]*B[8]+A[9]*B[4]);
		C[13] += (A[11]*B[5]+A[12]*B[0]-A[14]*B[2]-A[2]*B[10]+A[4]*B[12]+A[6]*B[6]-A[8]*B[8]-A[9]*B[3]);
		C[14] += (-A[10]*B[3]-A[11]*B[4]+A[12]*B[1]+A[13]*B[2]-A[3]*B[10]-A[4]*B[11]+A[7]*B[6]+A[8]*B[7]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 2 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__4_2_6(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[14]-A[1]*B[13]-A[10]*B[4]+A[11]*B[3]+A[12]*B[2]-A[13]*B[1]+A[14]*B[0]+A[2]*B[12]-A[3]*B[11]+A[4]*B[10]+A[5]*B[9]-A[6]*B[8]+A[7]*B[7]-A[8]*B[6]+A[9]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__4_3_1(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[3]-A[1]*B[6]-A[10]*B[18]-A[12]*B[19]-A[2]*B[8]-A[3]*B[9]-A[5]*B[12]-A[6]*B[14]-A[7]*B[15]-A[9]*B[17]);
		C[1] += (A[0]*B[2]+A[1]*B[5]-A[11]*B[18]-A[13]*B[19]+A[2]*B[7]-A[4]*B[9]+A[5]*B[11]+A[6]*B[13]-A[8]*B[15]+A[9]*B[16]);
		C[2] += (-A[0]*B[1]-A[1]*B[4]+A[10]*B[16]+A[11]*B[17]-A[14]*B[19]+A[3]*B[7]+A[4]*B[8]-A[5]*B[10]+A[7]*B[13]+A[8]*B[14]);
		C[3] += (A[0]*B[0]+A[12]*B[16]+A[13]*B[17]+A[14]*B[18]-A[2]*B[4]-A[3]*B[5]-A[4]*B[6]-A[6]*B[10]-A[7]*B[11]-A[8]*B[12]);
		C[4] += (A[1]*B[0]-A[10]*B[11]-A[11]*B[12]-A[12]*B[13]-A[13]*B[14]-A[14]*B[15]+A[2]*B[1]+A[3]*B[2]+A[4]*B[3]-A[9]*B[10]);
		C[5] += (A[10]*B[5]+A[11]*B[6]+A[12]*B[7]+A[13]*B[8]+A[14]*B[9]+A[5]*B[0]+A[6]*B[1]+A[7]*B[2]+A[8]*B[3]+A[9]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__4_3_3(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[17]-A[11]*B[16]-A[2]*B[9]+A[3]*B[8]-A[4]*B[7]-A[6]*B[15]+A[7]*B[14]-A[8]*B[13]-A[9]*B[18]);
		C[1] += (A[1]*B[9]+A[12]*B[17]-A[13]*B[16]-A[3]*B[6]+A[4]*B[5]+A[5]*B[15]-A[7]*B[12]+A[8]*B[11]-A[9]*B[19]);
		C[2] += (-A[1]*B[8]-A[10]*B[19]+A[12]*B[18]-A[14]*B[16]+A[2]*B[6]-A[4]*B[4]-A[5]*B[14]+A[6]*B[12]-A[8]*B[10]);
		C[3] += (A[1]*B[7]-A[11]*B[19]+A[13]*B[18]-A[14]*B[17]-A[2]*B[5]+A[3]*B[4]+A[5]*B[13]-A[6]*B[11]+A[7]*B[10]);
		C[4] += (-A[0]*B[9]-A[10]*B[12]+A[11]*B[11]-A[12]*B[14]+A[13]*B[13]+A[3]*B[3]-A[4]*B[2]+A[5]*B[18]+A[6]*B[19]);
		C[5] += (A[0]*B[8]-A[11]*B[10]-A[12]*B[15]+A[14]*B[13]-A[2]*B[3]+A[4]*B[1]-A[5]*B[17]+A[7]*B[19]+A[9]*B[12]);
		C[6] += (-A[0]*B[7]+A[10]*B[10]-A[13]*B[15]+A[14]*B[14]+A[2]*B[2]-A[3]*B[1]+A[5]*B[16]+A[8]*B[19]-A[9]*B[11]);
		C[7] += (-A[0]*B[6]+A[1]*B[3]+A[10]*B[15]-A[13]*B[10]-A[14]*B[11]-A[4]*B[0]-A[6]*B[17]-A[7]*B[18]+A[9]*B[14]);
		C[8] += (A[0]*B[5]-A[1]*B[2]+A[11]*B[15]+A[12]*B[10]-A[14]*B[12]+A[3]*B[0]+A[6]*B[16]-A[8]*B[18]-A[9]*B[13]);
		C[9] += (-A[0]*B[4]+A[1]*B[1]-A[10]*B[13]-A[11]*B[14]+A[12]*B[11]+A[13]*B[12]-A[2]*B[0]+A[7]*B[16]+A[8]*B[17]);
		C[10] += (-A[0]*B[15]-A[1]*B[18]+A[10]*B[6]-A[11]*B[5]+A[12]*B[8]-A[13]*B[7]-A[2]*B[19]+A[7]*B[3]-A[8]*B[2]);
		C[11] += (A[0]*B[14]+A[1]*B[17]+A[11]*B[4]+A[12]*B[9]-A[14]*B[7]-A[3]*B[19]-A[6]*B[3]+A[8]*B[1]-A[9]*B[6]);
		C[12] += (-A[0]*B[13]-A[1]*B[16]-A[10]*B[4]+A[13]*B[9]-A[14]*B[8]-A[4]*B[19]+A[6]*B[2]-A[7]*B[1]+A[9]*B[5]);
		C[13] += (-A[0]*B[12]-A[10]*B[9]+A[13]*B[4]+A[14]*B[5]+A[2]*B[17]+A[3]*B[18]+A[5]*B[3]-A[8]*B[0]-A[9]*B[8]);
		C[14] += (A[0]*B[11]-A[11]*B[9]-A[12]*B[4]+A[14]*B[6]-A[2]*B[16]+A[4]*B[18]-A[5]*B[2]+A[7]*B[0]+A[9]*B[7]);
		C[15] += (-A[0]*B[10]+A[10]*B[7]+A[11]*B[8]-A[12]*B[5]-A[13]*B[6]-A[3]*B[16]-A[4]*B[17]+A[5]*B[1]-A[6]*B[0]);
		C[16] += (-A[1]*B[12]-A[11]*B[0]-A[13]*B[1]-A[14]*B[2]-A[2]*B[14]-A[3]*B[15]+A[5]*B[6]+A[6]*B[8]+A[7]*B[9]);
		C[17] += (A[1]*B[11]+A[10]*B[0]+A[12]*B[1]-A[14]*B[3]+A[2]*B[13]-A[4]*B[15]-A[5]*B[5]-A[6]*B[7]+A[8]*B[9]);
		C[18] += (-A[1]*B[10]+A[12]*B[2]+A[13]*B[3]+A[3]*B[13]+A[4]*B[14]+A[5]*B[4]-A[7]*B[7]-A[8]*B[8]-A[9]*B[0]);
		C[19] += (-A[10]*B[2]-A[11]*B[3]-A[2]*B[10]-A[3]*B[11]-A[4]*B[12]+A[6]*B[4]+A[7]*B[5]+A[8]*B[6]-A[9]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 3 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__4_3_5(float[] A, float[] B, float[] C) {
		C[0] += (-A[10]*B[14]+A[11]*B[13]+A[12]*B[12]-A[13]*B[11]+A[14]*B[10]+A[5]*B[19]-A[6]*B[18]+A[7]*B[17]-A[8]*B[16]+A[9]*B[15]);
		C[1] += (-A[1]*B[19]+A[10]*B[8]-A[11]*B[7]-A[12]*B[6]+A[13]*B[5]-A[14]*B[4]+A[2]*B[18]-A[3]*B[17]+A[4]*B[16]-A[9]*B[9]);
		C[2] += (A[0]*B[19]+A[12]*B[3]-A[13]*B[2]+A[14]*B[1]-A[2]*B[15]+A[3]*B[14]-A[4]*B[13]+A[6]*B[9]-A[7]*B[8]+A[8]*B[7]);
		C[3] += (-A[0]*B[18]+A[1]*B[15]-A[10]*B[3]+A[11]*B[2]-A[14]*B[0]-A[3]*B[12]+A[4]*B[11]-A[5]*B[9]+A[7]*B[6]-A[8]*B[5]);
		C[4] += (A[0]*B[17]-A[1]*B[14]-A[11]*B[1]+A[13]*B[0]+A[2]*B[12]-A[4]*B[10]+A[5]*B[8]-A[6]*B[6]+A[8]*B[4]+A[9]*B[3]);
		C[5] += (-A[0]*B[16]+A[1]*B[13]+A[10]*B[1]-A[12]*B[0]-A[2]*B[11]+A[3]*B[10]-A[5]*B[7]+A[6]*B[5]-A[7]*B[4]-A[9]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__4_4_0(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[0]+A[1]*B[1]+A[10]*B[10]+A[11]*B[11]+A[12]*B[12]+A[13]*B[13]+A[14]*B[14]+A[2]*B[2]+A[3]*B[3]+A[4]*B[4]+A[5]*B[5]+A[6]*B[6]+A[7]*B[7]+A[8]*B[8]+A[9]*B[9]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__4_4_2(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[11]-A[11]*B[10]+A[12]*B[13]-A[13]*B[12]+A[3]*B[4]-A[4]*B[3]+A[7]*B[8]-A[8]*B[7]);
		C[1] += (A[11]*B[9]+A[12]*B[14]-A[14]*B[12]-A[2]*B[4]+A[4]*B[2]-A[6]*B[8]+A[8]*B[6]-A[9]*B[11]);
		C[2] += (-A[10]*B[9]+A[13]*B[14]-A[14]*B[13]+A[2]*B[3]-A[3]*B[2]+A[6]*B[7]-A[7]*B[6]+A[9]*B[10]);
		C[3] += (A[1]*B[4]-A[10]*B[14]+A[13]*B[9]+A[14]*B[10]-A[4]*B[1]+A[5]*B[8]-A[8]*B[5]-A[9]*B[13]);
		C[4] += (-A[1]*B[3]-A[11]*B[14]-A[12]*B[9]+A[14]*B[11]+A[3]*B[1]-A[5]*B[7]+A[7]*B[5]+A[9]*B[12]);
		C[5] += (A[1]*B[2]+A[10]*B[12]+A[11]*B[13]-A[12]*B[10]-A[13]*B[11]-A[2]*B[1]+A[5]*B[6]-A[6]*B[5]);
		C[6] += (-A[0]*B[4]-A[11]*B[5]-A[13]*B[6]-A[14]*B[7]+A[4]*B[0]+A[5]*B[11]+A[6]*B[13]+A[7]*B[14]);
		C[7] += (A[0]*B[3]+A[10]*B[5]+A[12]*B[6]-A[14]*B[8]-A[3]*B[0]-A[5]*B[10]-A[6]*B[12]+A[8]*B[14]);
		C[8] += (-A[0]*B[2]+A[12]*B[7]+A[13]*B[8]+A[2]*B[0]+A[5]*B[9]-A[7]*B[12]-A[8]*B[13]-A[9]*B[5]);
		C[9] += (A[0]*B[1]-A[1]*B[0]-A[10]*B[7]-A[11]*B[8]+A[6]*B[9]+A[7]*B[10]+A[8]*B[11]-A[9]*B[6]);
		C[10] += (-A[0]*B[8]-A[1]*B[11]+A[11]*B[1]+A[13]*B[2]+A[14]*B[3]-A[2]*B[13]-A[3]*B[14]+A[8]*B[0]);
		C[11] += (A[0]*B[7]+A[1]*B[10]-A[10]*B[1]-A[12]*B[2]+A[14]*B[4]+A[2]*B[12]-A[4]*B[14]-A[7]*B[0]);
		C[12] += (-A[0]*B[6]-A[1]*B[9]-A[12]*B[3]-A[13]*B[4]+A[3]*B[12]+A[4]*B[13]+A[6]*B[0]+A[9]*B[1]);
		C[13] += (A[0]*B[5]+A[10]*B[3]+A[11]*B[4]-A[2]*B[9]-A[3]*B[10]-A[4]*B[11]-A[5]*B[0]+A[9]*B[2]);
		C[14] += (A[1]*B[5]+A[2]*B[6]+A[3]*B[7]+A[4]*B[8]-A[5]*B[1]-A[6]*B[2]-A[7]*B[3]-A[8]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 4 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__4_4_4(float[] A, float[] B, float[] C) {
		C[0] += (A[10]*B[13]-A[11]*B[12]-A[12]*B[11]+A[13]*B[10]-A[14]*B[9]-A[9]*B[14]);
		C[1] += (A[12]*B[8]-A[13]*B[7]+A[14]*B[6]+A[6]*B[14]-A[7]*B[13]+A[8]*B[12]);
		C[2] += (-A[10]*B[8]+A[11]*B[7]-A[14]*B[5]-A[5]*B[14]+A[7]*B[11]-A[8]*B[10]);
		C[3] += (-A[11]*B[6]+A[13]*B[5]+A[5]*B[13]-A[6]*B[11]+A[8]*B[9]+A[9]*B[8]);
		C[4] += (A[10]*B[6]-A[12]*B[5]-A[5]*B[12]+A[6]*B[10]-A[7]*B[9]-A[9]*B[7]);
		C[5] += (-A[12]*B[4]+A[13]*B[3]-A[14]*B[2]-A[2]*B[14]+A[3]*B[13]-A[4]*B[12]);
		C[6] += (A[1]*B[14]+A[10]*B[4]-A[11]*B[3]+A[14]*B[1]-A[3]*B[11]+A[4]*B[10]);
		C[7] += (-A[1]*B[13]+A[11]*B[2]-A[13]*B[1]+A[2]*B[11]-A[4]*B[9]-A[9]*B[4]);
		C[8] += (A[1]*B[12]-A[10]*B[2]+A[12]*B[1]-A[2]*B[10]+A[3]*B[9]+A[9]*B[3]);
		C[9] += (-A[0]*B[14]-A[14]*B[0]+A[3]*B[8]-A[4]*B[7]-A[7]*B[4]+A[8]*B[3]);
		C[10] += (A[0]*B[13]+A[13]*B[0]-A[2]*B[8]+A[4]*B[6]+A[6]*B[4]-A[8]*B[2]);
		C[11] += (-A[0]*B[12]-A[12]*B[0]+A[2]*B[7]-A[3]*B[6]-A[6]*B[3]+A[7]*B[2]);
		C[12] += (-A[0]*B[11]+A[1]*B[8]-A[11]*B[0]-A[4]*B[5]-A[5]*B[4]+A[8]*B[1]);
		C[13] += (A[0]*B[10]-A[1]*B[7]+A[10]*B[0]+A[3]*B[5]+A[5]*B[3]-A[7]*B[1]);
		C[14] += (-A[0]*B[9]+A[1]*B[6]-A[2]*B[5]-A[5]*B[2]+A[6]*B[1]-A[9]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 5 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__4_5_1(float[] A, float[] B, float[] C) {
		C[0] += (A[11]*B[2]+A[13]*B[3]+A[14]*B[4]+A[4]*B[0]+A[8]*B[1]);
		C[1] += (-A[10]*B[2]-A[12]*B[3]+A[14]*B[5]-A[3]*B[0]-A[7]*B[1]);
		C[2] += (-A[12]*B[4]-A[13]*B[5]+A[2]*B[0]+A[6]*B[1]+A[9]*B[2]);
		C[3] += (-A[1]*B[0]+A[10]*B[4]+A[11]*B[5]-A[5]*B[1]+A[9]*B[3]);
		C[4] += (A[0]*B[0]-A[5]*B[2]-A[6]*B[3]-A[7]*B[4]-A[8]*B[5]);
		C[5] += (A[0]*B[1]+A[1]*B[2]+A[2]*B[3]+A[3]*B[4]+A[4]*B[5]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 5 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__4_5_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[12]*B[5]+A[13]*B[4]-A[14]*B[3]);
		C[1] += (A[10]*B[5]-A[11]*B[4]+A[14]*B[2]);
		C[2] += (A[11]*B[3]-A[13]*B[2]-A[9]*B[5]);
		C[3] += (-A[10]*B[3]+A[12]*B[2]+A[9]*B[4]);
		C[4] += (-A[14]*B[1]-A[7]*B[5]+A[8]*B[4]);
		C[5] += (A[13]*B[1]+A[6]*B[5]-A[8]*B[3]);
		C[6] += (-A[12]*B[1]-A[6]*B[4]+A[7]*B[3]);
		C[7] += (-A[11]*B[1]-A[5]*B[5]+A[8]*B[2]);
		C[8] += (A[10]*B[1]+A[5]*B[4]-A[7]*B[2]);
		C[9] += (-A[5]*B[3]+A[6]*B[2]-A[9]*B[1]);
		C[10] += (A[14]*B[0]+A[3]*B[5]-A[4]*B[4]);
		C[11] += (-A[13]*B[0]-A[2]*B[5]+A[4]*B[3]);
		C[12] += (A[12]*B[0]+A[2]*B[4]-A[3]*B[3]);
		C[13] += (A[1]*B[5]+A[11]*B[0]-A[4]*B[2]);
		C[14] += (-A[1]*B[4]-A[10]*B[0]+A[3]*B[2]);
		C[15] += (A[1]*B[3]-A[2]*B[2]+A[9]*B[0]);
		C[16] += (-A[0]*B[5]+A[4]*B[1]-A[8]*B[0]);
		C[17] += (A[0]*B[4]-A[3]*B[1]+A[7]*B[0]);
		C[18] += (-A[0]*B[3]+A[2]*B[1]-A[6]*B[0]);
		C[19] += (A[0]*B[2]-A[1]*B[1]+A[5]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 4  x  group 6 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__4_6_2(float[] A, float[] B, float[] C) {
		C[0] += A[14]*B[0];
		C[1] += -A[13]*B[0];
		C[2] += A[12]*B[0];
		C[3] += A[11]*B[0];
		C[4] += -A[10]*B[0];
		C[5] += A[9]*B[0];
		C[6] += -A[8]*B[0];
		C[7] += A[7]*B[0];
		C[8] += -A[6]*B[0];
		C[9] += A[5]*B[0];
		C[10] += A[4]*B[0];
		C[11] += -A[3]*B[0];
		C[12] += A[2]*B[0];
		C[13] += -A[1]*B[0];
		C[14] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 0 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__5_0_5(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__1_0_1(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 1 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__5_1_4(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]+A[1]*B[5]);
		C[1] += (-A[0]*B[3]+A[2]*B[5]);
		C[2] += (A[0]*B[2]+A[3]*B[5]);
		C[3] += (-A[0]*B[1]+A[4]*B[5]);
		C[4] += (A[0]*B[0]+A[5]*B[5]);
		C[5] += (-A[1]*B[3]-A[2]*B[4]);
		C[6] += (A[1]*B[2]-A[3]*B[4]);
		C[7] += (-A[1]*B[1]-A[4]*B[4]);
		C[8] += (A[1]*B[0]-A[5]*B[4]);
		C[9] += (A[2]*B[2]+A[3]*B[3]);
		C[10] += (-A[2]*B[1]+A[4]*B[3]);
		C[11] += (A[2]*B[0]+A[5]*B[3]);
		C[12] += (-A[3]*B[1]-A[4]*B[2]);
		C[13] += (A[3]*B[0]-A[5]*B[2]);
		C[14] += (A[4]*B[0]+A[5]*B[1]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 1 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__5_1_6(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__1_5_6(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 2 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__5_2_3(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[9]-A[1]*B[13]-A[2]*B[14]);
		C[1] += (A[0]*B[8]+A[1]*B[12]-A[3]*B[14]);
		C[2] += (-A[0]*B[7]-A[1]*B[11]-A[4]*B[14]);
		C[3] += (A[0]*B[6]+A[1]*B[10]-A[5]*B[14]);
		C[4] += (-A[0]*B[5]+A[2]*B[12]+A[3]*B[13]);
		C[5] += (A[0]*B[4]-A[2]*B[11]+A[4]*B[13]);
		C[6] += (-A[0]*B[3]+A[2]*B[10]+A[5]*B[13]);
		C[7] += (-A[0]*B[2]-A[3]*B[11]-A[4]*B[12]);
		C[8] += (A[0]*B[1]+A[3]*B[10]-A[5]*B[12]);
		C[9] += (-A[0]*B[0]+A[4]*B[10]+A[5]*B[11]);
		C[10] += (-A[1]*B[5]-A[2]*B[8]-A[3]*B[9]);
		C[11] += (A[1]*B[4]+A[2]*B[7]-A[4]*B[9]);
		C[12] += (-A[1]*B[3]-A[2]*B[6]-A[5]*B[9]);
		C[13] += (-A[1]*B[2]+A[3]*B[7]+A[4]*B[8]);
		C[14] += (A[1]*B[1]-A[3]*B[6]+A[5]*B[8]);
		C[15] += (-A[1]*B[0]-A[4]*B[6]-A[5]*B[7]);
		C[16] += (-A[2]*B[2]-A[3]*B[4]-A[4]*B[5]);
		C[17] += (A[2]*B[1]+A[3]*B[3]-A[5]*B[5]);
		C[18] += (-A[2]*B[0]+A[4]*B[3]+A[5]*B[4]);
		C[19] += (-A[3]*B[0]-A[4]*B[1]-A[5]*B[2]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 2 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__5_2_5(float[] A, float[] B, float[] C) {
		C[0] += (-A[1]*B[14]+A[2]*B[13]-A[3]*B[12]+A[4]*B[11]-A[5]*B[10]);
		C[1] += (A[0]*B[14]-A[2]*B[9]+A[3]*B[8]-A[4]*B[7]+A[5]*B[6]);
		C[2] += (-A[0]*B[13]+A[1]*B[9]-A[3]*B[5]+A[4]*B[4]-A[5]*B[3]);
		C[3] += (A[0]*B[12]-A[1]*B[8]+A[2]*B[5]-A[4]*B[2]+A[5]*B[1]);
		C[4] += (-A[0]*B[11]+A[1]*B[7]-A[2]*B[4]+A[3]*B[2]-A[5]*B[0]);
		C[5] += (A[0]*B[10]-A[1]*B[6]+A[2]*B[3]-A[3]*B[1]+A[4]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 3 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__5_3_2(float[] A, float[] B, float[] C) {
		C[0] += (-A[0]*B[9]-A[1]*B[15]-A[2]*B[18]-A[3]*B[19]);
		C[1] += (A[0]*B[8]+A[1]*B[14]+A[2]*B[17]-A[4]*B[19]);
		C[2] += (-A[0]*B[7]-A[1]*B[13]-A[2]*B[16]-A[5]*B[19]);
		C[3] += (-A[0]*B[6]-A[1]*B[12]+A[3]*B[17]+A[4]*B[18]);
		C[4] += (A[0]*B[5]+A[1]*B[11]-A[3]*B[16]+A[5]*B[18]);
		C[5] += (-A[0]*B[4]-A[1]*B[10]-A[4]*B[16]-A[5]*B[17]);
		C[6] += (A[0]*B[3]-A[2]*B[12]-A[3]*B[14]-A[4]*B[15]);
		C[7] += (-A[0]*B[2]+A[2]*B[11]+A[3]*B[13]-A[5]*B[15]);
		C[8] += (A[0]*B[1]-A[2]*B[10]+A[4]*B[13]+A[5]*B[14]);
		C[9] += (-A[0]*B[0]-A[3]*B[10]-A[4]*B[11]-A[5]*B[12]);
		C[10] += (A[1]*B[3]+A[2]*B[6]+A[3]*B[8]+A[4]*B[9]);
		C[11] += (-A[1]*B[2]-A[2]*B[5]-A[3]*B[7]+A[5]*B[9]);
		C[12] += (A[1]*B[1]+A[2]*B[4]-A[4]*B[7]-A[5]*B[8]);
		C[13] += (-A[1]*B[0]+A[3]*B[4]+A[4]*B[5]+A[5]*B[6]);
		C[14] += (-A[2]*B[0]-A[3]*B[1]-A[4]*B[2]-A[5]*B[3]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 3 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__5_3_4(float[] A, float[] B, float[] C) {
		C[0] += (-A[2]*B[19]+A[3]*B[18]-A[4]*B[17]+A[5]*B[16]);
		C[1] += (A[1]*B[19]-A[3]*B[15]+A[4]*B[14]-A[5]*B[13]);
		C[2] += (-A[1]*B[18]+A[2]*B[15]-A[4]*B[12]+A[5]*B[11]);
		C[3] += (A[1]*B[17]-A[2]*B[14]+A[3]*B[12]-A[5]*B[10]);
		C[4] += (-A[1]*B[16]+A[2]*B[13]-A[3]*B[11]+A[4]*B[10]);
		C[5] += (-A[0]*B[19]+A[3]*B[9]-A[4]*B[8]+A[5]*B[7]);
		C[6] += (A[0]*B[18]-A[2]*B[9]+A[4]*B[6]-A[5]*B[5]);
		C[7] += (-A[0]*B[17]+A[2]*B[8]-A[3]*B[6]+A[5]*B[4]);
		C[8] += (A[0]*B[16]-A[2]*B[7]+A[3]*B[5]-A[4]*B[4]);
		C[9] += (-A[0]*B[15]+A[1]*B[9]-A[4]*B[3]+A[5]*B[2]);
		C[10] += (A[0]*B[14]-A[1]*B[8]+A[3]*B[3]-A[5]*B[1]);
		C[11] += (-A[0]*B[13]+A[1]*B[7]-A[3]*B[2]+A[4]*B[1]);
		C[12] += (-A[0]*B[12]+A[1]*B[6]-A[2]*B[3]+A[5]*B[0]);
		C[13] += (A[0]*B[11]-A[1]*B[5]+A[2]*B[2]-A[4]*B[0]);
		C[14] += (-A[0]*B[10]+A[1]*B[4]-A[2]*B[1]+A[3]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 4 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__5_4_1(float[] A, float[] B, float[] C) {
		C[0] += (A[0]*B[4]+A[1]*B[8]+A[2]*B[11]+A[3]*B[13]+A[4]*B[14]);
		C[1] += (-A[0]*B[3]-A[1]*B[7]-A[2]*B[10]-A[3]*B[12]+A[5]*B[14]);
		C[2] += (A[0]*B[2]+A[1]*B[6]+A[2]*B[9]-A[4]*B[12]-A[5]*B[13]);
		C[3] += (-A[0]*B[1]-A[1]*B[5]+A[3]*B[9]+A[4]*B[10]+A[5]*B[11]);
		C[4] += (A[0]*B[0]-A[2]*B[5]-A[3]*B[6]-A[4]*B[7]-A[5]*B[8]);
		C[5] += (A[1]*B[0]+A[2]*B[1]+A[3]*B[2]+A[4]*B[3]+A[5]*B[4]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 4 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__5_4_3(float[] A, float[] B, float[] C) {
		C[0] += (A[3]*B[14]-A[4]*B[13]+A[5]*B[12]);
		C[1] += (-A[2]*B[14]+A[4]*B[11]-A[5]*B[10]);
		C[2] += (A[2]*B[13]-A[3]*B[11]+A[5]*B[9]);
		C[3] += (-A[2]*B[12]+A[3]*B[10]-A[4]*B[9]);
		C[4] += (A[1]*B[14]-A[4]*B[8]+A[5]*B[7]);
		C[5] += (-A[1]*B[13]+A[3]*B[8]-A[5]*B[6]);
		C[6] += (A[1]*B[12]-A[3]*B[7]+A[4]*B[6]);
		C[7] += (A[1]*B[11]-A[2]*B[8]+A[5]*B[5]);
		C[8] += (-A[1]*B[10]+A[2]*B[7]-A[4]*B[5]);
		C[9] += (A[1]*B[9]-A[2]*B[6]+A[3]*B[5]);
		C[10] += (-A[0]*B[14]+A[4]*B[4]-A[5]*B[3]);
		C[11] += (A[0]*B[13]-A[3]*B[4]+A[5]*B[2]);
		C[12] += (-A[0]*B[12]+A[3]*B[3]-A[4]*B[2]);
		C[13] += (-A[0]*B[11]+A[2]*B[4]-A[5]*B[1]);
		C[14] += (A[0]*B[10]-A[2]*B[3]+A[4]*B[1]);
		C[15] += (-A[0]*B[9]+A[2]*B[2]-A[3]*B[1]);
		C[16] += (A[0]*B[8]-A[1]*B[4]+A[5]*B[0]);
		C[17] += (-A[0]*B[7]+A[1]*B[3]-A[4]*B[0]);
		C[18] += (A[0]*B[6]-A[1]*B[2]+A[3]*B[0]);
		C[19] += (-A[0]*B[5]+A[1]*B[1]-A[2]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 5 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__5_5_0(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__1_1_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 5 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__5_5_2(float[] A, float[] B, float[] C) {
		C[0] += (A[4]*B[5]-A[5]*B[4]);
		C[1] += (-A[3]*B[5]+A[5]*B[3]);
		C[2] += (A[3]*B[4]-A[4]*B[3]);
		C[3] += (A[2]*B[5]-A[5]*B[2]);
		C[4] += (-A[2]*B[4]+A[4]*B[2]);
		C[5] += (A[2]*B[3]-A[3]*B[2]);
		C[6] += (-A[1]*B[5]+A[5]*B[1]);
		C[7] += (A[1]*B[4]-A[4]*B[1]);
		C[8] += (-A[1]*B[3]+A[3]*B[1]);
		C[9] += (A[1]*B[2]-A[2]*B[1]);
		C[10] += (A[0]*B[5]-A[5]*B[0]);
		C[11] += (-A[0]*B[4]+A[4]*B[0]);
		C[12] += (A[0]*B[3]-A[3]*B[0]);
		C[13] += (-A[0]*B[2]+A[2]*B[0]);
		C[14] += (A[0]*B[1]-A[1]*B[0]);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 5  x  group 6 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__5_6_1(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__1_6_5(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 0 -> group 6)
	 */
	protected final static void gp__internal_euclidean_metric__6_0_6(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__0_0_0(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 1 -> group 5)
	 */
	protected final static void gp__internal_euclidean_metric__6_1_5(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[5];
		C[1] += -A[0]*B[4];
		C[2] += A[0]*B[3];
		C[3] += -A[0]*B[2];
		C[4] += A[0]*B[1];
		C[5] += -A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 2 -> group 4)
	 */
	protected final static void gp__internal_euclidean_metric__6_2_4(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[14];
		C[1] += A[0]*B[13];
		C[2] += -A[0]*B[12];
		C[3] += A[0]*B[11];
		C[4] += -A[0]*B[10];
		C[5] += -A[0]*B[9];
		C[6] += A[0]*B[8];
		C[7] += -A[0]*B[7];
		C[8] += A[0]*B[6];
		C[9] += -A[0]*B[5];
		C[10] += A[0]*B[4];
		C[11] += -A[0]*B[3];
		C[12] += -A[0]*B[2];
		C[13] += A[0]*B[1];
		C[14] += -A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 3 -> group 3)
	 */
	protected final static void gp__internal_euclidean_metric__6_3_3(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[19];
		C[1] += A[0]*B[18];
		C[2] += -A[0]*B[17];
		C[3] += A[0]*B[16];
		C[4] += -A[0]*B[15];
		C[5] += A[0]*B[14];
		C[6] += -A[0]*B[13];
		C[7] += -A[0]*B[12];
		C[8] += A[0]*B[11];
		C[9] += -A[0]*B[10];
		C[10] += A[0]*B[9];
		C[11] += -A[0]*B[8];
		C[12] += A[0]*B[7];
		C[13] += A[0]*B[6];
		C[14] += -A[0]*B[5];
		C[15] += A[0]*B[4];
		C[16] += -A[0]*B[3];
		C[17] += A[0]*B[2];
		C[18] += -A[0]*B[1];
		C[19] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 4 -> group 2)
	 */
	protected final static void gp__internal_euclidean_metric__6_4_2(float[] A, float[] B, float[] C) {
		C[0] += A[0]*B[14];
		C[1] += -A[0]*B[13];
		C[2] += A[0]*B[12];
		C[3] += A[0]*B[11];
		C[4] += -A[0]*B[10];
		C[5] += A[0]*B[9];
		C[6] += -A[0]*B[8];
		C[7] += A[0]*B[7];
		C[8] += -A[0]*B[6];
		C[9] += A[0]*B[5];
		C[10] += A[0]*B[4];
		C[11] += -A[0]*B[3];
		C[12] += A[0]*B[2];
		C[13] += -A[0]*B[1];
		C[14] += A[0]*B[0];
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 5 -> group 1)
	 */
	protected final static void gp__internal_euclidean_metric__6_5_1(float[] A, float[] B, float[] C) {
		gp__internal_euclidean_metric__6_1_5(A, B, C);
	}
	/**
	 * Computes the partial geometric product of two multivectors (group 6  x  group 6 -> group 0)
	 */
	protected final static void gp__internal_euclidean_metric__6_6_0(float[] A, float[] B, float[] C) {
		C[0] += -A[0]*B[0];
	}
	/**
	 * copies coordinates of group 0
	 */
	protected final static void copyGroup_0(float[] A, float[] C) {
		C[0] = A[0];
	}
	/**
	 * copies and multiplies (by s) coordinates of group 0
	 */
	protected final static void copyMul_0(float[] A, float[] C, float s) {
		C[0] = A[0]*s;
	}
	/**
	 * copies and divides (by s) coordinates of group 0
	 */
	protected final static void copyDiv_0(float[] A, float[] C, float s) {
		C[0] = A[0]/s;
	}
	/**
	 * adds coordinates of group 0 from variable A to C
	 */
	protected final static void add_0(float[] A, float[] C) {
		C[0] += A[0];
	}
	/**
	 * subtracts coordinates of group 0 in variable A from C
	 */
	protected final static void sub_0(float[] A, float[] C) {
		C[0] -= A[0];
	}
	/**
	 * negate coordinates of group 0 of variable A
	 */
	protected final static void neg_0(float[] A, float[] C) {
		C[0] = -A[0];
	}
	/**
	 * adds coordinates of group 0 of variables A and B
	 */
	protected final static void add2_0_0(float[] A, float[] B, float[] C) {
		C[0] = (A[0]+B[0]);
	}
	/**
	 * subtracts coordinates of group 0 of variables A from B
	 */
	protected final static void sub2_0_0(float[] A, float[] B, float[] C) {
		C[0] = (A[0]-B[0]);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 0 of variables A and B
	 */
	protected final static void hp_0_0(float[] A, float[] B, float[] C) {
		C[0] = A[0]*B[0];
	}
	/**
	 * performs coordinate-wise division of coordinates of group 0 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_0_0(float[] A, float[] B, float[] C) {
		C[0] = A[0]/((B[0]));
	}
	/**
	 * check for equality up to eps of coordinates of group 0 of variables A and B
	 */
	protected final static boolean equals_0_0(float[] A, float[] B, float eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
	return true;
	}
	/**
	 * checks if coordinates of group 0 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_0(float[] A, float eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		return true;
	}
	/**
	 * copies coordinates of group 1
	 */
	protected final static void copyGroup_1(float[] A, float[] C) {
		C[0] = A[0];
		C[1] = A[1];
		C[2] = A[2];
		C[3] = A[3];
		C[4] = A[4];
		C[5] = A[5];
	}
	/**
	 * copies and multiplies (by s) coordinates of group 1
	 */
	protected final static void copyMul_1(float[] A, float[] C, float s) {
		C[0] = A[0]*s;
		C[1] = A[1]*s;
		C[2] = A[2]*s;
		C[3] = A[3]*s;
		C[4] = A[4]*s;
		C[5] = A[5]*s;
	}
	/**
	 * copies and divides (by s) coordinates of group 1
	 */
	protected final static void copyDiv_1(float[] A, float[] C, float s) {
		C[0] = A[0]/s;
		C[1] = A[1]/s;
		C[2] = A[2]/s;
		C[3] = A[3]/s;
		C[4] = A[4]/s;
		C[5] = A[5]/s;
	}
	/**
	 * adds coordinates of group 1 from variable A to C
	 */
	protected final static void add_1(float[] A, float[] C) {
		C[0] += A[0];
		C[1] += A[1];
		C[2] += A[2];
		C[3] += A[3];
		C[4] += A[4];
		C[5] += A[5];
	}
	/**
	 * subtracts coordinates of group 1 in variable A from C
	 */
	protected final static void sub_1(float[] A, float[] C) {
		C[0] -= A[0];
		C[1] -= A[1];
		C[2] -= A[2];
		C[3] -= A[3];
		C[4] -= A[4];
		C[5] -= A[5];
	}
	/**
	 * negate coordinates of group 1 of variable A
	 */
	protected final static void neg_1(float[] A, float[] C) {
		C[0] = -A[0];
		C[1] = -A[1];
		C[2] = -A[2];
		C[3] = -A[3];
		C[4] = -A[4];
		C[5] = -A[5];
	}
	/**
	 * adds coordinates of group 1 of variables A and B
	 */
	protected final static void add2_1_1(float[] A, float[] B, float[] C) {
		C[0] = (A[0]+B[0]);
		C[1] = (A[1]+B[1]);
		C[2] = (A[2]+B[2]);
		C[3] = (A[3]+B[3]);
		C[4] = (A[4]+B[4]);
		C[5] = (A[5]+B[5]);
	}
	/**
	 * subtracts coordinates of group 1 of variables A from B
	 */
	protected final static void sub2_1_1(float[] A, float[] B, float[] C) {
		C[0] = (A[0]-B[0]);
		C[1] = (A[1]-B[1]);
		C[2] = (A[2]-B[2]);
		C[3] = (A[3]-B[3]);
		C[4] = (A[4]-B[4]);
		C[5] = (A[5]-B[5]);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 1 of variables A and B
	 */
	protected final static void hp_1_1(float[] A, float[] B, float[] C) {
		C[0] = A[0]*B[0];
		C[1] = A[1]*B[1];
		C[2] = A[2]*B[2];
		C[3] = A[3]*B[3];
		C[4] = A[4]*B[4];
		C[5] = A[5]*B[5];
	}
	/**
	 * performs coordinate-wise division of coordinates of group 1 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_1_1(float[] A, float[] B, float[] C) {
		C[0] = A[0]/((B[0]));
		C[1] = A[1]/((B[1]));
		C[2] = A[2]/((B[2]));
		C[3] = A[3]/((B[3]));
		C[4] = A[4]/((B[4]));
		C[5] = A[5]/((B[5]));
	}
	/**
	 * check for equality up to eps of coordinates of group 1 of variables A and B
	 */
	protected final static boolean equals_1_1(float[] A, float[] B, float eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
		if (((A[1] - B[1]) < -eps) || ((A[1] - B[1]) > eps)) return false;
		if (((A[2] - B[2]) < -eps) || ((A[2] - B[2]) > eps)) return false;
		if (((A[3] - B[3]) < -eps) || ((A[3] - B[3]) > eps)) return false;
		if (((A[4] - B[4]) < -eps) || ((A[4] - B[4]) > eps)) return false;
		if (((A[5] - B[5]) < -eps) || ((A[5] - B[5]) > eps)) return false;
	return true;
	}
	/**
	 * checks if coordinates of group 1 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_1(float[] A, float eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		if ((A[1] < -eps) || (A[1] > eps)) return false;
		if ((A[2] < -eps) || (A[2] > eps)) return false;
		if ((A[3] < -eps) || (A[3] > eps)) return false;
		if ((A[4] < -eps) || (A[4] > eps)) return false;
		if ((A[5] < -eps) || (A[5] > eps)) return false;
		return true;
	}
	/**
	 * copies coordinates of group 2
	 */
	protected final static void copyGroup_2(float[] A, float[] C) {
		C[0] = A[0];
		C[1] = A[1];
		C[2] = A[2];
		C[3] = A[3];
		C[4] = A[4];
		C[5] = A[5];
		C[6] = A[6];
		C[7] = A[7];
		C[8] = A[8];
		C[9] = A[9];
		C[10] = A[10];
		C[11] = A[11];
		C[12] = A[12];
		C[13] = A[13];
		C[14] = A[14];
	}
	/**
	 * copies and multiplies (by s) coordinates of group 2
	 */
	protected final static void copyMul_2(float[] A, float[] C, float s) {
		C[0] = A[0]*s;
		C[1] = A[1]*s;
		C[2] = A[2]*s;
		C[3] = A[3]*s;
		C[4] = A[4]*s;
		C[5] = A[5]*s;
		C[6] = A[6]*s;
		C[7] = A[7]*s;
		C[8] = A[8]*s;
		C[9] = A[9]*s;
		C[10] = A[10]*s;
		C[11] = A[11]*s;
		C[12] = A[12]*s;
		C[13] = A[13]*s;
		C[14] = A[14]*s;
	}
	/**
	 * copies and divides (by s) coordinates of group 2
	 */
	protected final static void copyDiv_2(float[] A, float[] C, float s) {
		C[0] = A[0]/s;
		C[1] = A[1]/s;
		C[2] = A[2]/s;
		C[3] = A[3]/s;
		C[4] = A[4]/s;
		C[5] = A[5]/s;
		C[6] = A[6]/s;
		C[7] = A[7]/s;
		C[8] = A[8]/s;
		C[9] = A[9]/s;
		C[10] = A[10]/s;
		C[11] = A[11]/s;
		C[12] = A[12]/s;
		C[13] = A[13]/s;
		C[14] = A[14]/s;
	}
	/**
	 * adds coordinates of group 2 from variable A to C
	 */
	protected final static void add_2(float[] A, float[] C) {
		C[0] += A[0];
		C[1] += A[1];
		C[2] += A[2];
		C[3] += A[3];
		C[4] += A[4];
		C[5] += A[5];
		C[6] += A[6];
		C[7] += A[7];
		C[8] += A[8];
		C[9] += A[9];
		C[10] += A[10];
		C[11] += A[11];
		C[12] += A[12];
		C[13] += A[13];
		C[14] += A[14];
	}
	/**
	 * subtracts coordinates of group 2 in variable A from C
	 */
	protected final static void sub_2(float[] A, float[] C) {
		C[0] -= A[0];
		C[1] -= A[1];
		C[2] -= A[2];
		C[3] -= A[3];
		C[4] -= A[4];
		C[5] -= A[5];
		C[6] -= A[6];
		C[7] -= A[7];
		C[8] -= A[8];
		C[9] -= A[9];
		C[10] -= A[10];
		C[11] -= A[11];
		C[12] -= A[12];
		C[13] -= A[13];
		C[14] -= A[14];
	}
	/**
	 * negate coordinates of group 2 of variable A
	 */
	protected final static void neg_2(float[] A, float[] C) {
		C[0] = -A[0];
		C[1] = -A[1];
		C[2] = -A[2];
		C[3] = -A[3];
		C[4] = -A[4];
		C[5] = -A[5];
		C[6] = -A[6];
		C[7] = -A[7];
		C[8] = -A[8];
		C[9] = -A[9];
		C[10] = -A[10];
		C[11] = -A[11];
		C[12] = -A[12];
		C[13] = -A[13];
		C[14] = -A[14];
	}
	/**
	 * adds coordinates of group 2 of variables A and B
	 */
	protected final static void add2_2_2(float[] A, float[] B, float[] C) {
		C[0] = (A[0]+B[0]);
		C[1] = (A[1]+B[1]);
		C[2] = (A[2]+B[2]);
		C[3] = (A[3]+B[3]);
		C[4] = (A[4]+B[4]);
		C[5] = (A[5]+B[5]);
		C[6] = (A[6]+B[6]);
		C[7] = (A[7]+B[7]);
		C[8] = (A[8]+B[8]);
		C[9] = (A[9]+B[9]);
		C[10] = (A[10]+B[10]);
		C[11] = (A[11]+B[11]);
		C[12] = (A[12]+B[12]);
		C[13] = (A[13]+B[13]);
		C[14] = (A[14]+B[14]);
	}
	/**
	 * subtracts coordinates of group 2 of variables A from B
	 */
	protected final static void sub2_2_2(float[] A, float[] B, float[] C) {
		C[0] = (A[0]-B[0]);
		C[1] = (A[1]-B[1]);
		C[2] = (A[2]-B[2]);
		C[3] = (A[3]-B[3]);
		C[4] = (A[4]-B[4]);
		C[5] = (A[5]-B[5]);
		C[6] = (A[6]-B[6]);
		C[7] = (A[7]-B[7]);
		C[8] = (A[8]-B[8]);
		C[9] = (A[9]-B[9]);
		C[10] = (A[10]-B[10]);
		C[11] = (A[11]-B[11]);
		C[12] = (A[12]-B[12]);
		C[13] = (A[13]-B[13]);
		C[14] = (A[14]-B[14]);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 2 of variables A and B
	 */
	protected final static void hp_2_2(float[] A, float[] B, float[] C) {
		C[0] = A[0]*B[0];
		C[1] = A[1]*B[1];
		C[2] = A[2]*B[2];
		C[3] = A[3]*B[3];
		C[4] = A[4]*B[4];
		C[5] = A[5]*B[5];
		C[6] = A[6]*B[6];
		C[7] = A[7]*B[7];
		C[8] = A[8]*B[8];
		C[9] = A[9]*B[9];
		C[10] = A[10]*B[10];
		C[11] = A[11]*B[11];
		C[12] = A[12]*B[12];
		C[13] = A[13]*B[13];
		C[14] = A[14]*B[14];
	}
	/**
	 * performs coordinate-wise division of coordinates of group 2 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_2_2(float[] A, float[] B, float[] C) {
		C[0] = A[0]/((B[0]));
		C[1] = A[1]/((B[1]));
		C[2] = A[2]/((B[2]));
		C[3] = A[3]/((B[3]));
		C[4] = A[4]/((B[4]));
		C[5] = A[5]/((B[5]));
		C[6] = A[6]/((B[6]));
		C[7] = A[7]/((B[7]));
		C[8] = A[8]/((B[8]));
		C[9] = A[9]/((B[9]));
		C[10] = A[10]/((B[10]));
		C[11] = A[11]/((B[11]));
		C[12] = A[12]/((B[12]));
		C[13] = A[13]/((B[13]));
		C[14] = A[14]/((B[14]));
	}
	/**
	 * check for equality up to eps of coordinates of group 2 of variables A and B
	 */
	protected final static boolean equals_2_2(float[] A, float[] B, float eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
		if (((A[1] - B[1]) < -eps) || ((A[1] - B[1]) > eps)) return false;
		if (((A[2] - B[2]) < -eps) || ((A[2] - B[2]) > eps)) return false;
		if (((A[3] - B[3]) < -eps) || ((A[3] - B[3]) > eps)) return false;
		if (((A[4] - B[4]) < -eps) || ((A[4] - B[4]) > eps)) return false;
		if (((A[5] - B[5]) < -eps) || ((A[5] - B[5]) > eps)) return false;
		if (((A[6] - B[6]) < -eps) || ((A[6] - B[6]) > eps)) return false;
		if (((A[7] - B[7]) < -eps) || ((A[7] - B[7]) > eps)) return false;
		if (((A[8] - B[8]) < -eps) || ((A[8] - B[8]) > eps)) return false;
		if (((A[9] - B[9]) < -eps) || ((A[9] - B[9]) > eps)) return false;
		if (((A[10] - B[10]) < -eps) || ((A[10] - B[10]) > eps)) return false;
		if (((A[11] - B[11]) < -eps) || ((A[11] - B[11]) > eps)) return false;
		if (((A[12] - B[12]) < -eps) || ((A[12] - B[12]) > eps)) return false;
		if (((A[13] - B[13]) < -eps) || ((A[13] - B[13]) > eps)) return false;
		if (((A[14] - B[14]) < -eps) || ((A[14] - B[14]) > eps)) return false;
	return true;
	}
	/**
	 * checks if coordinates of group 2 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_2(float[] A, float eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		if ((A[1] < -eps) || (A[1] > eps)) return false;
		if ((A[2] < -eps) || (A[2] > eps)) return false;
		if ((A[3] < -eps) || (A[3] > eps)) return false;
		if ((A[4] < -eps) || (A[4] > eps)) return false;
		if ((A[5] < -eps) || (A[5] > eps)) return false;
		if ((A[6] < -eps) || (A[6] > eps)) return false;
		if ((A[7] < -eps) || (A[7] > eps)) return false;
		if ((A[8] < -eps) || (A[8] > eps)) return false;
		if ((A[9] < -eps) || (A[9] > eps)) return false;
		if ((A[10] < -eps) || (A[10] > eps)) return false;
		if ((A[11] < -eps) || (A[11] > eps)) return false;
		if ((A[12] < -eps) || (A[12] > eps)) return false;
		if ((A[13] < -eps) || (A[13] > eps)) return false;
		if ((A[14] < -eps) || (A[14] > eps)) return false;
		return true;
	}
	/**
	 * copies coordinates of group 3
	 */
	protected final static void copyGroup_3(float[] A, float[] C) {
		C[0] = A[0];
		C[1] = A[1];
		C[2] = A[2];
		C[3] = A[3];
		C[4] = A[4];
		C[5] = A[5];
		C[6] = A[6];
		C[7] = A[7];
		C[8] = A[8];
		C[9] = A[9];
		C[10] = A[10];
		C[11] = A[11];
		C[12] = A[12];
		C[13] = A[13];
		C[14] = A[14];
		C[15] = A[15];
		C[16] = A[16];
		C[17] = A[17];
		C[18] = A[18];
		C[19] = A[19];
	}
	/**
	 * copies and multiplies (by s) coordinates of group 3
	 */
	protected final static void copyMul_3(float[] A, float[] C, float s) {
		C[0] = A[0]*s;
		C[1] = A[1]*s;
		C[2] = A[2]*s;
		C[3] = A[3]*s;
		C[4] = A[4]*s;
		C[5] = A[5]*s;
		C[6] = A[6]*s;
		C[7] = A[7]*s;
		C[8] = A[8]*s;
		C[9] = A[9]*s;
		C[10] = A[10]*s;
		C[11] = A[11]*s;
		C[12] = A[12]*s;
		C[13] = A[13]*s;
		C[14] = A[14]*s;
		C[15] = A[15]*s;
		C[16] = A[16]*s;
		C[17] = A[17]*s;
		C[18] = A[18]*s;
		C[19] = A[19]*s;
	}
	/**
	 * copies and divides (by s) coordinates of group 3
	 */
	protected final static void copyDiv_3(float[] A, float[] C, float s) {
		C[0] = A[0]/s;
		C[1] = A[1]/s;
		C[2] = A[2]/s;
		C[3] = A[3]/s;
		C[4] = A[4]/s;
		C[5] = A[5]/s;
		C[6] = A[6]/s;
		C[7] = A[7]/s;
		C[8] = A[8]/s;
		C[9] = A[9]/s;
		C[10] = A[10]/s;
		C[11] = A[11]/s;
		C[12] = A[12]/s;
		C[13] = A[13]/s;
		C[14] = A[14]/s;
		C[15] = A[15]/s;
		C[16] = A[16]/s;
		C[17] = A[17]/s;
		C[18] = A[18]/s;
		C[19] = A[19]/s;
	}
	/**
	 * adds coordinates of group 3 from variable A to C
	 */
	protected final static void add_3(float[] A, float[] C) {
		C[0] += A[0];
		C[1] += A[1];
		C[2] += A[2];
		C[3] += A[3];
		C[4] += A[4];
		C[5] += A[5];
		C[6] += A[6];
		C[7] += A[7];
		C[8] += A[8];
		C[9] += A[9];
		C[10] += A[10];
		C[11] += A[11];
		C[12] += A[12];
		C[13] += A[13];
		C[14] += A[14];
		C[15] += A[15];
		C[16] += A[16];
		C[17] += A[17];
		C[18] += A[18];
		C[19] += A[19];
	}
	/**
	 * subtracts coordinates of group 3 in variable A from C
	 */
	protected final static void sub_3(float[] A, float[] C) {
		C[0] -= A[0];
		C[1] -= A[1];
		C[2] -= A[2];
		C[3] -= A[3];
		C[4] -= A[4];
		C[5] -= A[5];
		C[6] -= A[6];
		C[7] -= A[7];
		C[8] -= A[8];
		C[9] -= A[9];
		C[10] -= A[10];
		C[11] -= A[11];
		C[12] -= A[12];
		C[13] -= A[13];
		C[14] -= A[14];
		C[15] -= A[15];
		C[16] -= A[16];
		C[17] -= A[17];
		C[18] -= A[18];
		C[19] -= A[19];
	}
	/**
	 * negate coordinates of group 3 of variable A
	 */
	protected final static void neg_3(float[] A, float[] C) {
		C[0] = -A[0];
		C[1] = -A[1];
		C[2] = -A[2];
		C[3] = -A[3];
		C[4] = -A[4];
		C[5] = -A[5];
		C[6] = -A[6];
		C[7] = -A[7];
		C[8] = -A[8];
		C[9] = -A[9];
		C[10] = -A[10];
		C[11] = -A[11];
		C[12] = -A[12];
		C[13] = -A[13];
		C[14] = -A[14];
		C[15] = -A[15];
		C[16] = -A[16];
		C[17] = -A[17];
		C[18] = -A[18];
		C[19] = -A[19];
	}
	/**
	 * adds coordinates of group 3 of variables A and B
	 */
	protected final static void add2_3_3(float[] A, float[] B, float[] C) {
		C[0] = (A[0]+B[0]);
		C[1] = (A[1]+B[1]);
		C[2] = (A[2]+B[2]);
		C[3] = (A[3]+B[3]);
		C[4] = (A[4]+B[4]);
		C[5] = (A[5]+B[5]);
		C[6] = (A[6]+B[6]);
		C[7] = (A[7]+B[7]);
		C[8] = (A[8]+B[8]);
		C[9] = (A[9]+B[9]);
		C[10] = (A[10]+B[10]);
		C[11] = (A[11]+B[11]);
		C[12] = (A[12]+B[12]);
		C[13] = (A[13]+B[13]);
		C[14] = (A[14]+B[14]);
		C[15] = (A[15]+B[15]);
		C[16] = (A[16]+B[16]);
		C[17] = (A[17]+B[17]);
		C[18] = (A[18]+B[18]);
		C[19] = (A[19]+B[19]);
	}
	/**
	 * subtracts coordinates of group 3 of variables A from B
	 */
	protected final static void sub2_3_3(float[] A, float[] B, float[] C) {
		C[0] = (A[0]-B[0]);
		C[1] = (A[1]-B[1]);
		C[2] = (A[2]-B[2]);
		C[3] = (A[3]-B[3]);
		C[4] = (A[4]-B[4]);
		C[5] = (A[5]-B[5]);
		C[6] = (A[6]-B[6]);
		C[7] = (A[7]-B[7]);
		C[8] = (A[8]-B[8]);
		C[9] = (A[9]-B[9]);
		C[10] = (A[10]-B[10]);
		C[11] = (A[11]-B[11]);
		C[12] = (A[12]-B[12]);
		C[13] = (A[13]-B[13]);
		C[14] = (A[14]-B[14]);
		C[15] = (A[15]-B[15]);
		C[16] = (A[16]-B[16]);
		C[17] = (A[17]-B[17]);
		C[18] = (A[18]-B[18]);
		C[19] = (A[19]-B[19]);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 3 of variables A and B
	 */
	protected final static void hp_3_3(float[] A, float[] B, float[] C) {
		C[0] = A[0]*B[0];
		C[1] = A[1]*B[1];
		C[2] = A[2]*B[2];
		C[3] = A[3]*B[3];
		C[4] = A[4]*B[4];
		C[5] = A[5]*B[5];
		C[6] = A[6]*B[6];
		C[7] = A[7]*B[7];
		C[8] = A[8]*B[8];
		C[9] = A[9]*B[9];
		C[10] = A[10]*B[10];
		C[11] = A[11]*B[11];
		C[12] = A[12]*B[12];
		C[13] = A[13]*B[13];
		C[14] = A[14]*B[14];
		C[15] = A[15]*B[15];
		C[16] = A[16]*B[16];
		C[17] = A[17]*B[17];
		C[18] = A[18]*B[18];
		C[19] = A[19]*B[19];
	}
	/**
	 * performs coordinate-wise division of coordinates of group 3 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_3_3(float[] A, float[] B, float[] C) {
		C[0] = A[0]/((B[0]));
		C[1] = A[1]/((B[1]));
		C[2] = A[2]/((B[2]));
		C[3] = A[3]/((B[3]));
		C[4] = A[4]/((B[4]));
		C[5] = A[5]/((B[5]));
		C[6] = A[6]/((B[6]));
		C[7] = A[7]/((B[7]));
		C[8] = A[8]/((B[8]));
		C[9] = A[9]/((B[9]));
		C[10] = A[10]/((B[10]));
		C[11] = A[11]/((B[11]));
		C[12] = A[12]/((B[12]));
		C[13] = A[13]/((B[13]));
		C[14] = A[14]/((B[14]));
		C[15] = A[15]/((B[15]));
		C[16] = A[16]/((B[16]));
		C[17] = A[17]/((B[17]));
		C[18] = A[18]/((B[18]));
		C[19] = A[19]/((B[19]));
	}
	/**
	 * check for equality up to eps of coordinates of group 3 of variables A and B
	 */
	protected final static boolean equals_3_3(float[] A, float[] B, float eps) {
		if (((A[0] - B[0]) < -eps) || ((A[0] - B[0]) > eps)) return false;
		if (((A[1] - B[1]) < -eps) || ((A[1] - B[1]) > eps)) return false;
		if (((A[2] - B[2]) < -eps) || ((A[2] - B[2]) > eps)) return false;
		if (((A[3] - B[3]) < -eps) || ((A[3] - B[3]) > eps)) return false;
		if (((A[4] - B[4]) < -eps) || ((A[4] - B[4]) > eps)) return false;
		if (((A[5] - B[5]) < -eps) || ((A[5] - B[5]) > eps)) return false;
		if (((A[6] - B[6]) < -eps) || ((A[6] - B[6]) > eps)) return false;
		if (((A[7] - B[7]) < -eps) || ((A[7] - B[7]) > eps)) return false;
		if (((A[8] - B[8]) < -eps) || ((A[8] - B[8]) > eps)) return false;
		if (((A[9] - B[9]) < -eps) || ((A[9] - B[9]) > eps)) return false;
		if (((A[10] - B[10]) < -eps) || ((A[10] - B[10]) > eps)) return false;
		if (((A[11] - B[11]) < -eps) || ((A[11] - B[11]) > eps)) return false;
		if (((A[12] - B[12]) < -eps) || ((A[12] - B[12]) > eps)) return false;
		if (((A[13] - B[13]) < -eps) || ((A[13] - B[13]) > eps)) return false;
		if (((A[14] - B[14]) < -eps) || ((A[14] - B[14]) > eps)) return false;
		if (((A[15] - B[15]) < -eps) || ((A[15] - B[15]) > eps)) return false;
		if (((A[16] - B[16]) < -eps) || ((A[16] - B[16]) > eps)) return false;
		if (((A[17] - B[17]) < -eps) || ((A[17] - B[17]) > eps)) return false;
		if (((A[18] - B[18]) < -eps) || ((A[18] - B[18]) > eps)) return false;
		if (((A[19] - B[19]) < -eps) || ((A[19] - B[19]) > eps)) return false;
	return true;
	}
	/**
	 * checks if coordinates of group 3 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_3(float[] A, float eps) {
		if ((A[0] < -eps) || (A[0] > eps)) return false;
		if ((A[1] < -eps) || (A[1] > eps)) return false;
		if ((A[2] < -eps) || (A[2] > eps)) return false;
		if ((A[3] < -eps) || (A[3] > eps)) return false;
		if ((A[4] < -eps) || (A[4] > eps)) return false;
		if ((A[5] < -eps) || (A[5] > eps)) return false;
		if ((A[6] < -eps) || (A[6] > eps)) return false;
		if ((A[7] < -eps) || (A[7] > eps)) return false;
		if ((A[8] < -eps) || (A[8] > eps)) return false;
		if ((A[9] < -eps) || (A[9] > eps)) return false;
		if ((A[10] < -eps) || (A[10] > eps)) return false;
		if ((A[11] < -eps) || (A[11] > eps)) return false;
		if ((A[12] < -eps) || (A[12] > eps)) return false;
		if ((A[13] < -eps) || (A[13] > eps)) return false;
		if ((A[14] < -eps) || (A[14] > eps)) return false;
		if ((A[15] < -eps) || (A[15] > eps)) return false;
		if ((A[16] < -eps) || (A[16] > eps)) return false;
		if ((A[17] < -eps) || (A[17] > eps)) return false;
		if ((A[18] < -eps) || (A[18] > eps)) return false;
		if ((A[19] < -eps) || (A[19] > eps)) return false;
		return true;
	}
	/**
	 * copies coordinates of group 4
	 */
	protected final static void copyGroup_4(float[] A, float[] C) {
		copyGroup_2(A, C);
	}
	/**
	 * copies and multiplies (by s) coordinates of group 4
	 */
	protected final static void copyMul_4(float[] A, float[] C, float s) {
		copyMul_2(A, C, s);
	}
	/**
	 * copies and divides (by s) coordinates of group 4
	 */
	protected final static void copyDiv_4(float[] A, float[] C, float s) {
		copyDiv_2(A, C, s);
	}
	/**
	 * adds coordinates of group 4 from variable A to C
	 */
	protected final static void add_4(float[] A, float[] C) {
		add_2(A, C);
	}
	/**
	 * subtracts coordinates of group 4 in variable A from C
	 */
	protected final static void sub_4(float[] A, float[] C) {
		sub_2(A, C);
	}
	/**
	 * negate coordinates of group 4 of variable A
	 */
	protected final static void neg_4(float[] A, float[] C) {
		neg_2(A, C);
	}
	/**
	 * adds coordinates of group 4 of variables A and B
	 */
	protected final static void add2_4_4(float[] A, float[] B, float[] C) {
		add2_2_2(A, B, C);
	}
	/**
	 * subtracts coordinates of group 4 of variables A from B
	 */
	protected final static void sub2_4_4(float[] A, float[] B, float[] C) {
		sub2_2_2(A, B, C);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 4 of variables A and B
	 */
	protected final static void hp_4_4(float[] A, float[] B, float[] C) {
		hp_2_2(A, B, C);
	}
	/**
	 * performs coordinate-wise division of coordinates of group 4 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_4_4(float[] A, float[] B, float[] C) {
		ihp_2_2(A, B, C);
	}
	/**
	 * check for equality up to eps of coordinates of group 4 of variables A and B
	 */
	protected final static boolean equals_4_4(float[] A, float[] B, float eps) {
		return equals_2_2(A, B, eps);
	}
	/**
	 * checks if coordinates of group 4 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_4(float[] A, float eps) {
		return zeroGroup_2(A, eps);
	}
	/**
	 * copies coordinates of group 5
	 */
	protected final static void copyGroup_5(float[] A, float[] C) {
		copyGroup_1(A, C);
	}
	/**
	 * copies and multiplies (by s) coordinates of group 5
	 */
	protected final static void copyMul_5(float[] A, float[] C, float s) {
		copyMul_1(A, C, s);
	}
	/**
	 * copies and divides (by s) coordinates of group 5
	 */
	protected final static void copyDiv_5(float[] A, float[] C, float s) {
		copyDiv_1(A, C, s);
	}
	/**
	 * adds coordinates of group 5 from variable A to C
	 */
	protected final static void add_5(float[] A, float[] C) {
		add_1(A, C);
	}
	/**
	 * subtracts coordinates of group 5 in variable A from C
	 */
	protected final static void sub_5(float[] A, float[] C) {
		sub_1(A, C);
	}
	/**
	 * negate coordinates of group 5 of variable A
	 */
	protected final static void neg_5(float[] A, float[] C) {
		neg_1(A, C);
	}
	/**
	 * adds coordinates of group 5 of variables A and B
	 */
	protected final static void add2_5_5(float[] A, float[] B, float[] C) {
		add2_1_1(A, B, C);
	}
	/**
	 * subtracts coordinates of group 5 of variables A from B
	 */
	protected final static void sub2_5_5(float[] A, float[] B, float[] C) {
		sub2_1_1(A, B, C);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 5 of variables A and B
	 */
	protected final static void hp_5_5(float[] A, float[] B, float[] C) {
		hp_1_1(A, B, C);
	}
	/**
	 * performs coordinate-wise division of coordinates of group 5 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_5_5(float[] A, float[] B, float[] C) {
		ihp_1_1(A, B, C);
	}
	/**
	 * check for equality up to eps of coordinates of group 5 of variables A and B
	 */
	protected final static boolean equals_5_5(float[] A, float[] B, float eps) {
		return equals_1_1(A, B, eps);
	}
	/**
	 * checks if coordinates of group 5 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_5(float[] A, float eps) {
		return zeroGroup_1(A, eps);
	}
	/**
	 * copies coordinates of group 6
	 */
	protected final static void copyGroup_6(float[] A, float[] C) {
		copyGroup_0(A, C);
	}
	/**
	 * copies and multiplies (by s) coordinates of group 6
	 */
	protected final static void copyMul_6(float[] A, float[] C, float s) {
		copyMul_0(A, C, s);
	}
	/**
	 * copies and divides (by s) coordinates of group 6
	 */
	protected final static void copyDiv_6(float[] A, float[] C, float s) {
		copyDiv_0(A, C, s);
	}
	/**
	 * adds coordinates of group 6 from variable A to C
	 */
	protected final static void add_6(float[] A, float[] C) {
		add_0(A, C);
	}
	/**
	 * subtracts coordinates of group 6 in variable A from C
	 */
	protected final static void sub_6(float[] A, float[] C) {
		sub_0(A, C);
	}
	/**
	 * negate coordinates of group 6 of variable A
	 */
	protected final static void neg_6(float[] A, float[] C) {
		neg_0(A, C);
	}
	/**
	 * adds coordinates of group 6 of variables A and B
	 */
	protected final static void add2_6_6(float[] A, float[] B, float[] C) {
		add2_0_0(A, B, C);
	}
	/**
	 * subtracts coordinates of group 6 of variables A from B
	 */
	protected final static void sub2_6_6(float[] A, float[] B, float[] C) {
		sub2_0_0(A, B, C);
	}
	/**
	 * performs coordinate-wise multiplication of coordinates of group 6 of variables A and B
	 */
	protected final static void hp_6_6(float[] A, float[] B, float[] C) {
		hp_0_0(A, B, C);
	}
	/**
	 * performs coordinate-wise division of coordinates of group 6 of variables A and B
	 * (no checks for divide by zero are made)
	 */
	protected final static void ihp_6_6(float[] A, float[] B, float[] C) {
		ihp_0_0(A, B, C);
	}
	/**
	 * check for equality up to eps of coordinates of group 6 of variables A and B
	 */
	protected final static boolean equals_6_6(float[] A, float[] B, float eps) {
		return equals_0_0(A, B, eps);
	}
	/**
	 * checks if coordinates of group 6 of variable A are zero up to eps
	 */
	protected final static boolean zeroGroup_6(float[] A, float eps) {
		return zeroGroup_0(A, eps);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_0_6(float[] A, float[] C) {
		C[0] = A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_0_6(float[] A, float[] C) {
		dual_default_0_6(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_1_5(float[] A, float[] C) {
		C[0] = -A[1];
		C[1] = A[0];
		C[2] = -A[2];
		C[3] = A[3];
		C[4] = -A[5];
		C[5] = A[4];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_1_5(float[] A, float[] C) {
		dual_default_1_5(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_2_4(float[] A, float[] C) {
		C[0] = -A[0];
		C[1] = -A[2];
		C[2] = A[4];
		C[3] = -A[11];
		C[4] = A[7];
		C[5] = A[1];
		C[6] = -A[3];
		C[7] = A[10];
		C[8] = -A[6];
		C[9] = A[5];
		C[10] = -A[12];
		C[11] = A[8];
		C[12] = A[13];
		C[13] = -A[9];
		C[14] = -A[14];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_2_4(float[] A, float[] C) {
		dual_default_2_4(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_3_3(float[] A, float[] C) {
		C[0] = A[0];
		C[1] = -A[1];
		C[2] = A[10];
		C[3] = -A[4];
		C[4] = -A[3];
		C[5] = A[12];
		C[6] = -A[6];
		C[7] = -A[14];
		C[8] = A[8];
		C[9] = A[17];
		C[10] = A[2];
		C[11] = -A[11];
		C[12] = A[5];
		C[13] = A[13];
		C[14] = -A[7];
		C[15] = -A[16];
		C[16] = -A[15];
		C[17] = A[9];
		C[18] = A[18];
		C[19] = -A[19];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_3_3(float[] A, float[] C) {
		dual_default_3_3(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_4_2(float[] A, float[] C) {
		C[0] = -A[0];
		C[1] = A[5];
		C[2] = -A[1];
		C[3] = -A[6];
		C[4] = A[2];
		C[5] = A[9];
		C[6] = -A[8];
		C[7] = A[4];
		C[8] = A[11];
		C[9] = -A[13];
		C[10] = A[7];
		C[11] = -A[3];
		C[12] = -A[10];
		C[13] = A[12];
		C[14] = -A[14];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_4_2(float[] A, float[] C) {
		dual_default_4_2(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_5_1(float[] A, float[] C) {
		C[0] = A[1];
		C[1] = -A[0];
		C[2] = -A[2];
		C[3] = A[3];
		C[4] = A[5];
		C[5] = -A[4];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_5_1(float[] A, float[] C) {
		dual_default_5_1(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual_default_6_0(float[] A, float[] C) {
		dual_default_0_6(A, C);
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual_default_6_0(float[] A, float[] C) {
		dual_default_0_6(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__0_6(float[] A, float[] C) {
		C[0] = -A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__0_6(float[] A, float[] C) {
		dual_default_0_6(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__1_5(float[] A, float[] C) {
		C[0] = A[5];
		C[1] = -A[4];
		C[2] = A[3];
		C[3] = -A[2];
		C[4] = A[1];
		C[5] = -A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__1_5(float[] A, float[] C) {
		C[0] = -A[5];
		C[1] = A[4];
		C[2] = -A[3];
		C[3] = A[2];
		C[4] = -A[1];
		C[5] = A[0];
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__2_4(float[] A, float[] C) {
		C[0] = A[14];
		C[1] = -A[13];
		C[2] = A[12];
		C[3] = -A[11];
		C[4] = A[10];
		C[5] = A[9];
		C[6] = -A[8];
		C[7] = A[7];
		C[8] = -A[6];
		C[9] = A[5];
		C[10] = -A[4];
		C[11] = A[3];
		C[12] = A[2];
		C[13] = -A[1];
		C[14] = A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__2_4(float[] A, float[] C) {
		C[0] = -A[14];
		C[1] = A[13];
		C[2] = -A[12];
		C[3] = A[11];
		C[4] = -A[10];
		C[5] = -A[9];
		C[6] = A[8];
		C[7] = -A[7];
		C[8] = A[6];
		C[9] = -A[5];
		C[10] = A[4];
		C[11] = -A[3];
		C[12] = -A[2];
		C[13] = A[1];
		C[14] = -A[0];
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__3_3(float[] A, float[] C) {
		C[0] = -A[19];
		C[1] = A[18];
		C[2] = -A[17];
		C[3] = A[16];
		C[4] = -A[15];
		C[5] = A[14];
		C[6] = -A[13];
		C[7] = -A[12];
		C[8] = A[11];
		C[9] = -A[10];
		C[10] = A[9];
		C[11] = -A[8];
		C[12] = A[7];
		C[13] = A[6];
		C[14] = -A[5];
		C[15] = A[4];
		C[16] = -A[3];
		C[17] = A[2];
		C[18] = -A[1];
		C[19] = A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__3_3(float[] A, float[] C) {
		C[0] = A[19];
		C[1] = -A[18];
		C[2] = A[17];
		C[3] = -A[16];
		C[4] = A[15];
		C[5] = -A[14];
		C[6] = A[13];
		C[7] = A[12];
		C[8] = -A[11];
		C[9] = A[10];
		C[10] = -A[9];
		C[11] = A[8];
		C[12] = -A[7];
		C[13] = -A[6];
		C[14] = A[5];
		C[15] = -A[4];
		C[16] = A[3];
		C[17] = -A[2];
		C[18] = A[1];
		C[19] = -A[0];
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__4_2(float[] A, float[] C) {
		C[0] = -A[14];
		C[1] = A[13];
		C[2] = -A[12];
		C[3] = -A[11];
		C[4] = A[10];
		C[5] = -A[9];
		C[6] = A[8];
		C[7] = -A[7];
		C[8] = A[6];
		C[9] = -A[5];
		C[10] = -A[4];
		C[11] = A[3];
		C[12] = -A[2];
		C[13] = A[1];
		C[14] = -A[0];
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__4_2(float[] A, float[] C) {
		C[0] = A[14];
		C[1] = -A[13];
		C[2] = A[12];
		C[3] = A[11];
		C[4] = -A[10];
		C[5] = A[9];
		C[6] = -A[8];
		C[7] = A[7];
		C[8] = -A[6];
		C[9] = A[5];
		C[10] = A[4];
		C[11] = -A[3];
		C[12] = A[2];
		C[13] = -A[1];
		C[14] = A[0];
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__5_1(float[] A, float[] C) {
		dual__internal_euclidean_metric__1_5(A, C);
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__5_1(float[] A, float[] C) {
		undual__internal_euclidean_metric__1_5(A, C);
	}
	/**
	 * Computes the partial dual (w.r.t. full space) of a multivector.
	 */
	protected final static void dual__internal_euclidean_metric__6_0(float[] A, float[] C) {
		dual_default_0_6(A, C);
	}
	/**
	 * Computes the partial undual (w.r.t. full space) of a multivector.
	 */
	protected final static void undual__internal_euclidean_metric__6_0(float[] A, float[] C) {
		dual__internal_euclidean_metric__0_6(A, C);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_1_1(om O, float[] A, float[] C) {
		C[0] = (A[0]*O.m_m1[0]+A[1]*O.m_m1[1]+A[2]*O.m_m1[2]+A[3]*O.m_m1[3]+A[4]*O.m_m1[4]+A[5]*O.m_m1[5]);
		C[1] = (A[0]*O.m_m1[6]+A[1]*O.m_m1[7]+A[2]*O.m_m1[8]+A[3]*O.m_m1[9]+A[4]*O.m_m1[10]+A[5]*O.m_m1[11]);
		C[2] = (A[0]*O.m_m1[12]+A[1]*O.m_m1[13]+A[2]*O.m_m1[14]+A[3]*O.m_m1[15]+A[4]*O.m_m1[16]+A[5]*O.m_m1[17]);
		C[3] = (A[0]*O.m_m1[18]+A[1]*O.m_m1[19]+A[2]*O.m_m1[20]+A[3]*O.m_m1[21]+A[4]*O.m_m1[22]+A[5]*O.m_m1[23]);
		C[4] = (A[0]*O.m_m1[24]+A[1]*O.m_m1[25]+A[2]*O.m_m1[26]+A[3]*O.m_m1[27]+A[4]*O.m_m1[28]+A[5]*O.m_m1[29]);
		C[5] = (A[0]*O.m_m1[30]+A[1]*O.m_m1[31]+A[2]*O.m_m1[32]+A[3]*O.m_m1[33]+A[4]*O.m_m1[34]+A[5]*O.m_m1[35]);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_2_2(om O, float[] A, float[] C) {
		C[0] = (A[0]*O.m_m2[0]+A[1]*O.m_m2[1]+A[10]*O.m_m2[10]+A[11]*O.m_m2[11]+A[12]*O.m_m2[12]+A[13]*O.m_m2[13]+A[14]*O.m_m2[14]+A[2]*O.m_m2[2]+A[3]*O.m_m2[3]+A[4]*O.m_m2[4]+A[5]*O.m_m2[5]+A[6]*O.m_m2[6]+A[7]*O.m_m2[7]+A[8]*O.m_m2[8]+A[9]*O.m_m2[9]);
		C[1] = (A[0]*O.m_m2[15]+A[1]*O.m_m2[16]+A[10]*O.m_m2[25]+A[11]*O.m_m2[26]+A[12]*O.m_m2[27]+A[13]*O.m_m2[28]+A[14]*O.m_m2[29]+A[2]*O.m_m2[17]+A[3]*O.m_m2[18]+A[4]*O.m_m2[19]+A[5]*O.m_m2[20]+A[6]*O.m_m2[21]+A[7]*O.m_m2[22]+A[8]*O.m_m2[23]+A[9]*O.m_m2[24]);
		C[2] = (A[0]*O.m_m2[30]+A[1]*O.m_m2[31]+A[10]*O.m_m2[40]+A[11]*O.m_m2[41]+A[12]*O.m_m2[42]+A[13]*O.m_m2[43]+A[14]*O.m_m2[44]+A[2]*O.m_m2[32]+A[3]*O.m_m2[33]+A[4]*O.m_m2[34]+A[5]*O.m_m2[35]+A[6]*O.m_m2[36]+A[7]*O.m_m2[37]+A[8]*O.m_m2[38]+A[9]*O.m_m2[39]);
		C[3] = (A[0]*O.m_m2[45]+A[1]*O.m_m2[46]+A[10]*O.m_m2[55]+A[11]*O.m_m2[56]+A[12]*O.m_m2[57]+A[13]*O.m_m2[58]+A[14]*O.m_m2[59]+A[2]*O.m_m2[47]+A[3]*O.m_m2[48]+A[4]*O.m_m2[49]+A[5]*O.m_m2[50]+A[6]*O.m_m2[51]+A[7]*O.m_m2[52]+A[8]*O.m_m2[53]+A[9]*O.m_m2[54]);
		C[4] = (A[0]*O.m_m2[60]+A[1]*O.m_m2[61]+A[10]*O.m_m2[70]+A[11]*O.m_m2[71]+A[12]*O.m_m2[72]+A[13]*O.m_m2[73]+A[14]*O.m_m2[74]+A[2]*O.m_m2[62]+A[3]*O.m_m2[63]+A[4]*O.m_m2[64]+A[5]*O.m_m2[65]+A[6]*O.m_m2[66]+A[7]*O.m_m2[67]+A[8]*O.m_m2[68]+A[9]*O.m_m2[69]);
		C[5] = (A[0]*O.m_m2[75]+A[1]*O.m_m2[76]+A[10]*O.m_m2[85]+A[11]*O.m_m2[86]+A[12]*O.m_m2[87]+A[13]*O.m_m2[88]+A[14]*O.m_m2[89]+A[2]*O.m_m2[77]+A[3]*O.m_m2[78]+A[4]*O.m_m2[79]+A[5]*O.m_m2[80]+A[6]*O.m_m2[81]+A[7]*O.m_m2[82]+A[8]*O.m_m2[83]+A[9]*O.m_m2[84]);
		C[6] = (A[0]*O.m_m2[90]+A[1]*O.m_m2[91]+A[10]*O.m_m2[100]+A[11]*O.m_m2[101]+A[12]*O.m_m2[102]+A[13]*O.m_m2[103]+A[14]*O.m_m2[104]+A[2]*O.m_m2[92]+A[3]*O.m_m2[93]+A[4]*O.m_m2[94]+A[5]*O.m_m2[95]+A[6]*O.m_m2[96]+A[7]*O.m_m2[97]+A[8]*O.m_m2[98]+A[9]*O.m_m2[99]);
		C[7] = (A[0]*O.m_m2[105]+A[1]*O.m_m2[106]+A[10]*O.m_m2[115]+A[11]*O.m_m2[116]+A[12]*O.m_m2[117]+A[13]*O.m_m2[118]+A[14]*O.m_m2[119]+A[2]*O.m_m2[107]+A[3]*O.m_m2[108]+A[4]*O.m_m2[109]+A[5]*O.m_m2[110]+A[6]*O.m_m2[111]+A[7]*O.m_m2[112]+A[8]*O.m_m2[113]+A[9]*O.m_m2[114]);
		C[8] = (A[0]*O.m_m2[120]+A[1]*O.m_m2[121]+A[10]*O.m_m2[130]+A[11]*O.m_m2[131]+A[12]*O.m_m2[132]+A[13]*O.m_m2[133]+A[14]*O.m_m2[134]+A[2]*O.m_m2[122]+A[3]*O.m_m2[123]+A[4]*O.m_m2[124]+A[5]*O.m_m2[125]+A[6]*O.m_m2[126]+A[7]*O.m_m2[127]+A[8]*O.m_m2[128]+A[9]*O.m_m2[129]);
		C[9] = (A[0]*O.m_m2[135]+A[1]*O.m_m2[136]+A[10]*O.m_m2[145]+A[11]*O.m_m2[146]+A[12]*O.m_m2[147]+A[13]*O.m_m2[148]+A[14]*O.m_m2[149]+A[2]*O.m_m2[137]+A[3]*O.m_m2[138]+A[4]*O.m_m2[139]+A[5]*O.m_m2[140]+A[6]*O.m_m2[141]+A[7]*O.m_m2[142]+A[8]*O.m_m2[143]+A[9]*O.m_m2[144]);
		C[10] = (A[0]*O.m_m2[150]+A[1]*O.m_m2[151]+A[10]*O.m_m2[160]+A[11]*O.m_m2[161]+A[12]*O.m_m2[162]+A[13]*O.m_m2[163]+A[14]*O.m_m2[164]+A[2]*O.m_m2[152]+A[3]*O.m_m2[153]+A[4]*O.m_m2[154]+A[5]*O.m_m2[155]+A[6]*O.m_m2[156]+A[7]*O.m_m2[157]+A[8]*O.m_m2[158]+A[9]*O.m_m2[159]);
		C[11] = (A[0]*O.m_m2[165]+A[1]*O.m_m2[166]+A[10]*O.m_m2[175]+A[11]*O.m_m2[176]+A[12]*O.m_m2[177]+A[13]*O.m_m2[178]+A[14]*O.m_m2[179]+A[2]*O.m_m2[167]+A[3]*O.m_m2[168]+A[4]*O.m_m2[169]+A[5]*O.m_m2[170]+A[6]*O.m_m2[171]+A[7]*O.m_m2[172]+A[8]*O.m_m2[173]+A[9]*O.m_m2[174]);
		C[12] = (A[0]*O.m_m2[180]+A[1]*O.m_m2[181]+A[10]*O.m_m2[190]+A[11]*O.m_m2[191]+A[12]*O.m_m2[192]+A[13]*O.m_m2[193]+A[14]*O.m_m2[194]+A[2]*O.m_m2[182]+A[3]*O.m_m2[183]+A[4]*O.m_m2[184]+A[5]*O.m_m2[185]+A[6]*O.m_m2[186]+A[7]*O.m_m2[187]+A[8]*O.m_m2[188]+A[9]*O.m_m2[189]);
		C[13] = (A[0]*O.m_m2[195]+A[1]*O.m_m2[196]+A[10]*O.m_m2[205]+A[11]*O.m_m2[206]+A[12]*O.m_m2[207]+A[13]*O.m_m2[208]+A[14]*O.m_m2[209]+A[2]*O.m_m2[197]+A[3]*O.m_m2[198]+A[4]*O.m_m2[199]+A[5]*O.m_m2[200]+A[6]*O.m_m2[201]+A[7]*O.m_m2[202]+A[8]*O.m_m2[203]+A[9]*O.m_m2[204]);
		C[14] = (A[0]*O.m_m2[210]+A[1]*O.m_m2[211]+A[10]*O.m_m2[220]+A[11]*O.m_m2[221]+A[12]*O.m_m2[222]+A[13]*O.m_m2[223]+A[14]*O.m_m2[224]+A[2]*O.m_m2[212]+A[3]*O.m_m2[213]+A[4]*O.m_m2[214]+A[5]*O.m_m2[215]+A[6]*O.m_m2[216]+A[7]*O.m_m2[217]+A[8]*O.m_m2[218]+A[9]*O.m_m2[219]);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_3_3(om O, float[] A, float[] C) {
		C[0] = (A[0]*O.m_m3[0]+A[1]*O.m_m3[1]+A[10]*O.m_m3[10]+A[11]*O.m_m3[11]+A[12]*O.m_m3[12]+A[13]*O.m_m3[13]+A[14]*O.m_m3[14]+A[15]*O.m_m3[15]+A[16]*O.m_m3[16]+A[17]*O.m_m3[17]+A[18]*O.m_m3[18]+A[19]*O.m_m3[19]+A[2]*O.m_m3[2]+A[3]*O.m_m3[3]+A[4]*O.m_m3[4]+A[5]*O.m_m3[5]+A[6]*O.m_m3[6]+A[7]*O.m_m3[7]+A[8]*O.m_m3[8]+A[9]*O.m_m3[9]);
		C[1] = (A[0]*O.m_m3[20]+A[1]*O.m_m3[21]+A[10]*O.m_m3[30]+A[11]*O.m_m3[31]+A[12]*O.m_m3[32]+A[13]*O.m_m3[33]+A[14]*O.m_m3[34]+A[15]*O.m_m3[35]+A[16]*O.m_m3[36]+A[17]*O.m_m3[37]+A[18]*O.m_m3[38]+A[19]*O.m_m3[39]+A[2]*O.m_m3[22]+A[3]*O.m_m3[23]+A[4]*O.m_m3[24]+A[5]*O.m_m3[25]+A[6]*O.m_m3[26]+A[7]*O.m_m3[27]+A[8]*O.m_m3[28]+A[9]*O.m_m3[29]);
		C[2] = (A[0]*O.m_m3[40]+A[1]*O.m_m3[41]+A[10]*O.m_m3[50]+A[11]*O.m_m3[51]+A[12]*O.m_m3[52]+A[13]*O.m_m3[53]+A[14]*O.m_m3[54]+A[15]*O.m_m3[55]+A[16]*O.m_m3[56]+A[17]*O.m_m3[57]+A[18]*O.m_m3[58]+A[19]*O.m_m3[59]+A[2]*O.m_m3[42]+A[3]*O.m_m3[43]+A[4]*O.m_m3[44]+A[5]*O.m_m3[45]+A[6]*O.m_m3[46]+A[7]*O.m_m3[47]+A[8]*O.m_m3[48]+A[9]*O.m_m3[49]);
		C[3] = (A[0]*O.m_m3[60]+A[1]*O.m_m3[61]+A[10]*O.m_m3[70]+A[11]*O.m_m3[71]+A[12]*O.m_m3[72]+A[13]*O.m_m3[73]+A[14]*O.m_m3[74]+A[15]*O.m_m3[75]+A[16]*O.m_m3[76]+A[17]*O.m_m3[77]+A[18]*O.m_m3[78]+A[19]*O.m_m3[79]+A[2]*O.m_m3[62]+A[3]*O.m_m3[63]+A[4]*O.m_m3[64]+A[5]*O.m_m3[65]+A[6]*O.m_m3[66]+A[7]*O.m_m3[67]+A[8]*O.m_m3[68]+A[9]*O.m_m3[69]);
		C[4] = (A[0]*O.m_m3[80]+A[1]*O.m_m3[81]+A[10]*O.m_m3[90]+A[11]*O.m_m3[91]+A[12]*O.m_m3[92]+A[13]*O.m_m3[93]+A[14]*O.m_m3[94]+A[15]*O.m_m3[95]+A[16]*O.m_m3[96]+A[17]*O.m_m3[97]+A[18]*O.m_m3[98]+A[19]*O.m_m3[99]+A[2]*O.m_m3[82]+A[3]*O.m_m3[83]+A[4]*O.m_m3[84]+A[5]*O.m_m3[85]+A[6]*O.m_m3[86]+A[7]*O.m_m3[87]+A[8]*O.m_m3[88]+A[9]*O.m_m3[89]);
		C[5] = (A[0]*O.m_m3[100]+A[1]*O.m_m3[101]+A[10]*O.m_m3[110]+A[11]*O.m_m3[111]+A[12]*O.m_m3[112]+A[13]*O.m_m3[113]+A[14]*O.m_m3[114]+A[15]*O.m_m3[115]+A[16]*O.m_m3[116]+A[17]*O.m_m3[117]+A[18]*O.m_m3[118]+A[19]*O.m_m3[119]+A[2]*O.m_m3[102]+A[3]*O.m_m3[103]+A[4]*O.m_m3[104]+A[5]*O.m_m3[105]+A[6]*O.m_m3[106]+A[7]*O.m_m3[107]+A[8]*O.m_m3[108]+A[9]*O.m_m3[109]);
		C[6] = (A[0]*O.m_m3[120]+A[1]*O.m_m3[121]+A[10]*O.m_m3[130]+A[11]*O.m_m3[131]+A[12]*O.m_m3[132]+A[13]*O.m_m3[133]+A[14]*O.m_m3[134]+A[15]*O.m_m3[135]+A[16]*O.m_m3[136]+A[17]*O.m_m3[137]+A[18]*O.m_m3[138]+A[19]*O.m_m3[139]+A[2]*O.m_m3[122]+A[3]*O.m_m3[123]+A[4]*O.m_m3[124]+A[5]*O.m_m3[125]+A[6]*O.m_m3[126]+A[7]*O.m_m3[127]+A[8]*O.m_m3[128]+A[9]*O.m_m3[129]);
		C[7] = (A[0]*O.m_m3[140]+A[1]*O.m_m3[141]+A[10]*O.m_m3[150]+A[11]*O.m_m3[151]+A[12]*O.m_m3[152]+A[13]*O.m_m3[153]+A[14]*O.m_m3[154]+A[15]*O.m_m3[155]+A[16]*O.m_m3[156]+A[17]*O.m_m3[157]+A[18]*O.m_m3[158]+A[19]*O.m_m3[159]+A[2]*O.m_m3[142]+A[3]*O.m_m3[143]+A[4]*O.m_m3[144]+A[5]*O.m_m3[145]+A[6]*O.m_m3[146]+A[7]*O.m_m3[147]+A[8]*O.m_m3[148]+A[9]*O.m_m3[149]);
		C[8] = (A[0]*O.m_m3[160]+A[1]*O.m_m3[161]+A[10]*O.m_m3[170]+A[11]*O.m_m3[171]+A[12]*O.m_m3[172]+A[13]*O.m_m3[173]+A[14]*O.m_m3[174]+A[15]*O.m_m3[175]+A[16]*O.m_m3[176]+A[17]*O.m_m3[177]+A[18]*O.m_m3[178]+A[19]*O.m_m3[179]+A[2]*O.m_m3[162]+A[3]*O.m_m3[163]+A[4]*O.m_m3[164]+A[5]*O.m_m3[165]+A[6]*O.m_m3[166]+A[7]*O.m_m3[167]+A[8]*O.m_m3[168]+A[9]*O.m_m3[169]);
		C[9] = (A[0]*O.m_m3[180]+A[1]*O.m_m3[181]+A[10]*O.m_m3[190]+A[11]*O.m_m3[191]+A[12]*O.m_m3[192]+A[13]*O.m_m3[193]+A[14]*O.m_m3[194]+A[15]*O.m_m3[195]+A[16]*O.m_m3[196]+A[17]*O.m_m3[197]+A[18]*O.m_m3[198]+A[19]*O.m_m3[199]+A[2]*O.m_m3[182]+A[3]*O.m_m3[183]+A[4]*O.m_m3[184]+A[5]*O.m_m3[185]+A[6]*O.m_m3[186]+A[7]*O.m_m3[187]+A[8]*O.m_m3[188]+A[9]*O.m_m3[189]);
		C[10] = (A[0]*O.m_m3[200]+A[1]*O.m_m3[201]+A[10]*O.m_m3[210]+A[11]*O.m_m3[211]+A[12]*O.m_m3[212]+A[13]*O.m_m3[213]+A[14]*O.m_m3[214]+A[15]*O.m_m3[215]+A[16]*O.m_m3[216]+A[17]*O.m_m3[217]+A[18]*O.m_m3[218]+A[19]*O.m_m3[219]+A[2]*O.m_m3[202]+A[3]*O.m_m3[203]+A[4]*O.m_m3[204]+A[5]*O.m_m3[205]+A[6]*O.m_m3[206]+A[7]*O.m_m3[207]+A[8]*O.m_m3[208]+A[9]*O.m_m3[209]);
		C[11] = (A[0]*O.m_m3[220]+A[1]*O.m_m3[221]+A[10]*O.m_m3[230]+A[11]*O.m_m3[231]+A[12]*O.m_m3[232]+A[13]*O.m_m3[233]+A[14]*O.m_m3[234]+A[15]*O.m_m3[235]+A[16]*O.m_m3[236]+A[17]*O.m_m3[237]+A[18]*O.m_m3[238]+A[19]*O.m_m3[239]+A[2]*O.m_m3[222]+A[3]*O.m_m3[223]+A[4]*O.m_m3[224]+A[5]*O.m_m3[225]+A[6]*O.m_m3[226]+A[7]*O.m_m3[227]+A[8]*O.m_m3[228]+A[9]*O.m_m3[229]);
		C[12] = (A[0]*O.m_m3[240]+A[1]*O.m_m3[241]+A[10]*O.m_m3[250]+A[11]*O.m_m3[251]+A[12]*O.m_m3[252]+A[13]*O.m_m3[253]+A[14]*O.m_m3[254]+A[15]*O.m_m3[255]+A[16]*O.m_m3[256]+A[17]*O.m_m3[257]+A[18]*O.m_m3[258]+A[19]*O.m_m3[259]+A[2]*O.m_m3[242]+A[3]*O.m_m3[243]+A[4]*O.m_m3[244]+A[5]*O.m_m3[245]+A[6]*O.m_m3[246]+A[7]*O.m_m3[247]+A[8]*O.m_m3[248]+A[9]*O.m_m3[249]);
		C[13] = (A[0]*O.m_m3[260]+A[1]*O.m_m3[261]+A[10]*O.m_m3[270]+A[11]*O.m_m3[271]+A[12]*O.m_m3[272]+A[13]*O.m_m3[273]+A[14]*O.m_m3[274]+A[15]*O.m_m3[275]+A[16]*O.m_m3[276]+A[17]*O.m_m3[277]+A[18]*O.m_m3[278]+A[19]*O.m_m3[279]+A[2]*O.m_m3[262]+A[3]*O.m_m3[263]+A[4]*O.m_m3[264]+A[5]*O.m_m3[265]+A[6]*O.m_m3[266]+A[7]*O.m_m3[267]+A[8]*O.m_m3[268]+A[9]*O.m_m3[269]);
		C[14] = (A[0]*O.m_m3[280]+A[1]*O.m_m3[281]+A[10]*O.m_m3[290]+A[11]*O.m_m3[291]+A[12]*O.m_m3[292]+A[13]*O.m_m3[293]+A[14]*O.m_m3[294]+A[15]*O.m_m3[295]+A[16]*O.m_m3[296]+A[17]*O.m_m3[297]+A[18]*O.m_m3[298]+A[19]*O.m_m3[299]+A[2]*O.m_m3[282]+A[3]*O.m_m3[283]+A[4]*O.m_m3[284]+A[5]*O.m_m3[285]+A[6]*O.m_m3[286]+A[7]*O.m_m3[287]+A[8]*O.m_m3[288]+A[9]*O.m_m3[289]);
		C[15] = (A[0]*O.m_m3[300]+A[1]*O.m_m3[301]+A[10]*O.m_m3[310]+A[11]*O.m_m3[311]+A[12]*O.m_m3[312]+A[13]*O.m_m3[313]+A[14]*O.m_m3[314]+A[15]*O.m_m3[315]+A[16]*O.m_m3[316]+A[17]*O.m_m3[317]+A[18]*O.m_m3[318]+A[19]*O.m_m3[319]+A[2]*O.m_m3[302]+A[3]*O.m_m3[303]+A[4]*O.m_m3[304]+A[5]*O.m_m3[305]+A[6]*O.m_m3[306]+A[7]*O.m_m3[307]+A[8]*O.m_m3[308]+A[9]*O.m_m3[309]);
		C[16] = (A[0]*O.m_m3[320]+A[1]*O.m_m3[321]+A[10]*O.m_m3[330]+A[11]*O.m_m3[331]+A[12]*O.m_m3[332]+A[13]*O.m_m3[333]+A[14]*O.m_m3[334]+A[15]*O.m_m3[335]+A[16]*O.m_m3[336]+A[17]*O.m_m3[337]+A[18]*O.m_m3[338]+A[19]*O.m_m3[339]+A[2]*O.m_m3[322]+A[3]*O.m_m3[323]+A[4]*O.m_m3[324]+A[5]*O.m_m3[325]+A[6]*O.m_m3[326]+A[7]*O.m_m3[327]+A[8]*O.m_m3[328]+A[9]*O.m_m3[329]);
		C[17] = (A[0]*O.m_m3[340]+A[1]*O.m_m3[341]+A[10]*O.m_m3[350]+A[11]*O.m_m3[351]+A[12]*O.m_m3[352]+A[13]*O.m_m3[353]+A[14]*O.m_m3[354]+A[15]*O.m_m3[355]+A[16]*O.m_m3[356]+A[17]*O.m_m3[357]+A[18]*O.m_m3[358]+A[19]*O.m_m3[359]+A[2]*O.m_m3[342]+A[3]*O.m_m3[343]+A[4]*O.m_m3[344]+A[5]*O.m_m3[345]+A[6]*O.m_m3[346]+A[7]*O.m_m3[347]+A[8]*O.m_m3[348]+A[9]*O.m_m3[349]);
		C[18] = (A[0]*O.m_m3[360]+A[1]*O.m_m3[361]+A[10]*O.m_m3[370]+A[11]*O.m_m3[371]+A[12]*O.m_m3[372]+A[13]*O.m_m3[373]+A[14]*O.m_m3[374]+A[15]*O.m_m3[375]+A[16]*O.m_m3[376]+A[17]*O.m_m3[377]+A[18]*O.m_m3[378]+A[19]*O.m_m3[379]+A[2]*O.m_m3[362]+A[3]*O.m_m3[363]+A[4]*O.m_m3[364]+A[5]*O.m_m3[365]+A[6]*O.m_m3[366]+A[7]*O.m_m3[367]+A[8]*O.m_m3[368]+A[9]*O.m_m3[369]);
		C[19] = (A[0]*O.m_m3[380]+A[1]*O.m_m3[381]+A[10]*O.m_m3[390]+A[11]*O.m_m3[391]+A[12]*O.m_m3[392]+A[13]*O.m_m3[393]+A[14]*O.m_m3[394]+A[15]*O.m_m3[395]+A[16]*O.m_m3[396]+A[17]*O.m_m3[397]+A[18]*O.m_m3[398]+A[19]*O.m_m3[399]+A[2]*O.m_m3[382]+A[3]*O.m_m3[383]+A[4]*O.m_m3[384]+A[5]*O.m_m3[385]+A[6]*O.m_m3[386]+A[7]*O.m_m3[387]+A[8]*O.m_m3[388]+A[9]*O.m_m3[389]);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_4_4(om O, float[] A, float[] C) {
		C[0] = (A[0]*O.m_m4[0]+A[1]*O.m_m4[1]+A[10]*O.m_m4[10]+A[11]*O.m_m4[11]+A[12]*O.m_m4[12]+A[13]*O.m_m4[13]+A[14]*O.m_m4[14]+A[2]*O.m_m4[2]+A[3]*O.m_m4[3]+A[4]*O.m_m4[4]+A[5]*O.m_m4[5]+A[6]*O.m_m4[6]+A[7]*O.m_m4[7]+A[8]*O.m_m4[8]+A[9]*O.m_m4[9]);
		C[1] = (A[0]*O.m_m4[15]+A[1]*O.m_m4[16]+A[10]*O.m_m4[25]+A[11]*O.m_m4[26]+A[12]*O.m_m4[27]+A[13]*O.m_m4[28]+A[14]*O.m_m4[29]+A[2]*O.m_m4[17]+A[3]*O.m_m4[18]+A[4]*O.m_m4[19]+A[5]*O.m_m4[20]+A[6]*O.m_m4[21]+A[7]*O.m_m4[22]+A[8]*O.m_m4[23]+A[9]*O.m_m4[24]);
		C[2] = (A[0]*O.m_m4[30]+A[1]*O.m_m4[31]+A[10]*O.m_m4[40]+A[11]*O.m_m4[41]+A[12]*O.m_m4[42]+A[13]*O.m_m4[43]+A[14]*O.m_m4[44]+A[2]*O.m_m4[32]+A[3]*O.m_m4[33]+A[4]*O.m_m4[34]+A[5]*O.m_m4[35]+A[6]*O.m_m4[36]+A[7]*O.m_m4[37]+A[8]*O.m_m4[38]+A[9]*O.m_m4[39]);
		C[3] = (A[0]*O.m_m4[45]+A[1]*O.m_m4[46]+A[10]*O.m_m4[55]+A[11]*O.m_m4[56]+A[12]*O.m_m4[57]+A[13]*O.m_m4[58]+A[14]*O.m_m4[59]+A[2]*O.m_m4[47]+A[3]*O.m_m4[48]+A[4]*O.m_m4[49]+A[5]*O.m_m4[50]+A[6]*O.m_m4[51]+A[7]*O.m_m4[52]+A[8]*O.m_m4[53]+A[9]*O.m_m4[54]);
		C[4] = (A[0]*O.m_m4[60]+A[1]*O.m_m4[61]+A[10]*O.m_m4[70]+A[11]*O.m_m4[71]+A[12]*O.m_m4[72]+A[13]*O.m_m4[73]+A[14]*O.m_m4[74]+A[2]*O.m_m4[62]+A[3]*O.m_m4[63]+A[4]*O.m_m4[64]+A[5]*O.m_m4[65]+A[6]*O.m_m4[66]+A[7]*O.m_m4[67]+A[8]*O.m_m4[68]+A[9]*O.m_m4[69]);
		C[5] = (A[0]*O.m_m4[75]+A[1]*O.m_m4[76]+A[10]*O.m_m4[85]+A[11]*O.m_m4[86]+A[12]*O.m_m4[87]+A[13]*O.m_m4[88]+A[14]*O.m_m4[89]+A[2]*O.m_m4[77]+A[3]*O.m_m4[78]+A[4]*O.m_m4[79]+A[5]*O.m_m4[80]+A[6]*O.m_m4[81]+A[7]*O.m_m4[82]+A[8]*O.m_m4[83]+A[9]*O.m_m4[84]);
		C[6] = (A[0]*O.m_m4[90]+A[1]*O.m_m4[91]+A[10]*O.m_m4[100]+A[11]*O.m_m4[101]+A[12]*O.m_m4[102]+A[13]*O.m_m4[103]+A[14]*O.m_m4[104]+A[2]*O.m_m4[92]+A[3]*O.m_m4[93]+A[4]*O.m_m4[94]+A[5]*O.m_m4[95]+A[6]*O.m_m4[96]+A[7]*O.m_m4[97]+A[8]*O.m_m4[98]+A[9]*O.m_m4[99]);
		C[7] = (A[0]*O.m_m4[105]+A[1]*O.m_m4[106]+A[10]*O.m_m4[115]+A[11]*O.m_m4[116]+A[12]*O.m_m4[117]+A[13]*O.m_m4[118]+A[14]*O.m_m4[119]+A[2]*O.m_m4[107]+A[3]*O.m_m4[108]+A[4]*O.m_m4[109]+A[5]*O.m_m4[110]+A[6]*O.m_m4[111]+A[7]*O.m_m4[112]+A[8]*O.m_m4[113]+A[9]*O.m_m4[114]);
		C[8] = (A[0]*O.m_m4[120]+A[1]*O.m_m4[121]+A[10]*O.m_m4[130]+A[11]*O.m_m4[131]+A[12]*O.m_m4[132]+A[13]*O.m_m4[133]+A[14]*O.m_m4[134]+A[2]*O.m_m4[122]+A[3]*O.m_m4[123]+A[4]*O.m_m4[124]+A[5]*O.m_m4[125]+A[6]*O.m_m4[126]+A[7]*O.m_m4[127]+A[8]*O.m_m4[128]+A[9]*O.m_m4[129]);
		C[9] = (A[0]*O.m_m4[135]+A[1]*O.m_m4[136]+A[10]*O.m_m4[145]+A[11]*O.m_m4[146]+A[12]*O.m_m4[147]+A[13]*O.m_m4[148]+A[14]*O.m_m4[149]+A[2]*O.m_m4[137]+A[3]*O.m_m4[138]+A[4]*O.m_m4[139]+A[5]*O.m_m4[140]+A[6]*O.m_m4[141]+A[7]*O.m_m4[142]+A[8]*O.m_m4[143]+A[9]*O.m_m4[144]);
		C[10] = (A[0]*O.m_m4[150]+A[1]*O.m_m4[151]+A[10]*O.m_m4[160]+A[11]*O.m_m4[161]+A[12]*O.m_m4[162]+A[13]*O.m_m4[163]+A[14]*O.m_m4[164]+A[2]*O.m_m4[152]+A[3]*O.m_m4[153]+A[4]*O.m_m4[154]+A[5]*O.m_m4[155]+A[6]*O.m_m4[156]+A[7]*O.m_m4[157]+A[8]*O.m_m4[158]+A[9]*O.m_m4[159]);
		C[11] = (A[0]*O.m_m4[165]+A[1]*O.m_m4[166]+A[10]*O.m_m4[175]+A[11]*O.m_m4[176]+A[12]*O.m_m4[177]+A[13]*O.m_m4[178]+A[14]*O.m_m4[179]+A[2]*O.m_m4[167]+A[3]*O.m_m4[168]+A[4]*O.m_m4[169]+A[5]*O.m_m4[170]+A[6]*O.m_m4[171]+A[7]*O.m_m4[172]+A[8]*O.m_m4[173]+A[9]*O.m_m4[174]);
		C[12] = (A[0]*O.m_m4[180]+A[1]*O.m_m4[181]+A[10]*O.m_m4[190]+A[11]*O.m_m4[191]+A[12]*O.m_m4[192]+A[13]*O.m_m4[193]+A[14]*O.m_m4[194]+A[2]*O.m_m4[182]+A[3]*O.m_m4[183]+A[4]*O.m_m4[184]+A[5]*O.m_m4[185]+A[6]*O.m_m4[186]+A[7]*O.m_m4[187]+A[8]*O.m_m4[188]+A[9]*O.m_m4[189]);
		C[13] = (A[0]*O.m_m4[195]+A[1]*O.m_m4[196]+A[10]*O.m_m4[205]+A[11]*O.m_m4[206]+A[12]*O.m_m4[207]+A[13]*O.m_m4[208]+A[14]*O.m_m4[209]+A[2]*O.m_m4[197]+A[3]*O.m_m4[198]+A[4]*O.m_m4[199]+A[5]*O.m_m4[200]+A[6]*O.m_m4[201]+A[7]*O.m_m4[202]+A[8]*O.m_m4[203]+A[9]*O.m_m4[204]);
		C[14] = (A[0]*O.m_m4[210]+A[1]*O.m_m4[211]+A[10]*O.m_m4[220]+A[11]*O.m_m4[221]+A[12]*O.m_m4[222]+A[13]*O.m_m4[223]+A[14]*O.m_m4[224]+A[2]*O.m_m4[212]+A[3]*O.m_m4[213]+A[4]*O.m_m4[214]+A[5]*O.m_m4[215]+A[6]*O.m_m4[216]+A[7]*O.m_m4[217]+A[8]*O.m_m4[218]+A[9]*O.m_m4[219]);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_5_5(om O, float[] A, float[] C) {
		C[0] = (A[0]*O.m_m5[0]+A[1]*O.m_m5[1]+A[2]*O.m_m5[2]+A[3]*O.m_m5[3]+A[4]*O.m_m5[4]+A[5]*O.m_m5[5]);
		C[1] = (A[0]*O.m_m5[6]+A[1]*O.m_m5[7]+A[2]*O.m_m5[8]+A[3]*O.m_m5[9]+A[4]*O.m_m5[10]+A[5]*O.m_m5[11]);
		C[2] = (A[0]*O.m_m5[12]+A[1]*O.m_m5[13]+A[2]*O.m_m5[14]+A[3]*O.m_m5[15]+A[4]*O.m_m5[16]+A[5]*O.m_m5[17]);
		C[3] = (A[0]*O.m_m5[18]+A[1]*O.m_m5[19]+A[2]*O.m_m5[20]+A[3]*O.m_m5[21]+A[4]*O.m_m5[22]+A[5]*O.m_m5[23]);
		C[4] = (A[0]*O.m_m5[24]+A[1]*O.m_m5[25]+A[2]*O.m_m5[26]+A[3]*O.m_m5[27]+A[4]*O.m_m5[28]+A[5]*O.m_m5[29]);
		C[5] = (A[0]*O.m_m5[30]+A[1]*O.m_m5[31]+A[2]*O.m_m5[32]+A[3]*O.m_m5[33]+A[4]*O.m_m5[34]+A[5]*O.m_m5[35]);
	}
	/**
	 * Computes the partial application of a general outermorphism to a general multivector
	 */
	protected static void applyGomGmv_6_6(om O, float[] A, float[] C) {
		C[0] = A[0]*O.m_m6[0];
	}
/**
 * Returns mv + mv.
 */
public final static mv add(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		if (bc[0] != null) {
			add2_0_0(ac[0], bc[0], cc[0]);
		}
		else copyGroup_0(ac[0], cc[0]);
	}
	else if (bc[0] != null) {
		cc[0] = new float[1];
		copyGroup_0(bc[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		if (bc[1] != null) {
			add2_1_1(ac[1], bc[1], cc[1]);
		}
		else copyGroup_1(ac[1], cc[1]);
	}
	else if (bc[1] != null) {
		cc[1] = new float[6];
		copyGroup_1(bc[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		if (bc[2] != null) {
			add2_2_2(ac[2], bc[2], cc[2]);
		}
		else copyGroup_2(ac[2], cc[2]);
	}
	else if (bc[2] != null) {
		cc[2] = new float[15];
		copyGroup_2(bc[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		if (bc[3] != null) {
			add2_3_3(ac[3], bc[3], cc[3]);
		}
		else copyGroup_3(ac[3], cc[3]);
	}
	else if (bc[3] != null) {
		cc[3] = new float[20];
		copyGroup_3(bc[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		if (bc[4] != null) {
			add2_4_4(ac[4], bc[4], cc[4]);
		}
		else copyGroup_4(ac[4], cc[4]);
	}
	else if (bc[4] != null) {
		cc[4] = new float[15];
		copyGroup_4(bc[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		if (bc[5] != null) {
			add2_5_5(ac[5], bc[5], cc[5]);
		}
		else copyGroup_5(ac[5], cc[5]);
	}
	else if (bc[5] != null) {
		cc[5] = new float[6];
		copyGroup_5(bc[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		if (bc[6] != null) {
			add2_6_6(ac[6], bc[6], cc[6]);
		}
		else copyGroup_6(ac[6], cc[6]);
	}
	else if (bc[6] != null) {
		cc[6] = new float[1];
		copyGroup_6(bc[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns mv - mv.
 */
public final static mv subtract(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		if (bc[0] != null) {
			sub2_0_0(ac[0], bc[0], cc[0]);
		}
		else copyGroup_0(ac[0], cc[0]);
	}
	else if (bc[0] != null) {
		cc[0] = new float[1];
		neg_0(bc[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		if (bc[1] != null) {
			sub2_1_1(ac[1], bc[1], cc[1]);
		}
		else copyGroup_1(ac[1], cc[1]);
	}
	else if (bc[1] != null) {
		cc[1] = new float[6];
		neg_1(bc[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		if (bc[2] != null) {
			sub2_2_2(ac[2], bc[2], cc[2]);
		}
		else copyGroup_2(ac[2], cc[2]);
	}
	else if (bc[2] != null) {
		cc[2] = new float[15];
		neg_2(bc[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		if (bc[3] != null) {
			sub2_3_3(ac[3], bc[3], cc[3]);
		}
		else copyGroup_3(ac[3], cc[3]);
	}
	else if (bc[3] != null) {
		cc[3] = new float[20];
		neg_3(bc[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		if (bc[4] != null) {
			sub2_4_4(ac[4], bc[4], cc[4]);
		}
		else copyGroup_4(ac[4], cc[4]);
	}
	else if (bc[4] != null) {
		cc[4] = new float[15];
		neg_4(bc[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		if (bc[5] != null) {
			sub2_5_5(ac[5], bc[5], cc[5]);
		}
		else copyGroup_5(ac[5], cc[5]);
	}
	else if (bc[5] != null) {
		cc[5] = new float[6];
		neg_5(bc[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		if (bc[6] != null) {
			sub2_6_6(ac[6], bc[6], cc[6]);
		}
		else copyGroup_6(ac[6], cc[6]);
	}
	else if (bc[6] != null) {
		cc[6] = new float[1];
		neg_6(bc[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns om * mv.
 */
public final static mv applyOM(final om a, final mv_if b)
{
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (bc[0] != null) {
	}
	
	if (bc[1] != null) {
		if (cc[1] == null) cc[1] = new float[6];
		applyGomGmv_1_1(a, bc[1], cc[1]);
	}
	
	if (bc[2] != null) {
		if (cc[2] == null) cc[2] = new float[15];
		applyGomGmv_2_2(a, bc[2], cc[2]);
	}
	
	if (bc[3] != null) {
		if (cc[3] == null) cc[3] = new float[20];
		applyGomGmv_3_3(a, bc[3], cc[3]);
	}
	
	if (bc[4] != null) {
		if (cc[4] == null) cc[4] = new float[15];
		applyGomGmv_4_4(a, bc[4], cc[4]);
	}
	
	if (bc[5] != null) {
		if (cc[5] == null) cc[5] = new float[6];
		applyGomGmv_5_5(a, bc[5], cc[5]);
	}
	
	if (bc[6] != null) {
		if (cc[6] == null) cc[6] = new float[1];
		applyGomGmv_6_6(a, bc[6], cc[6]);
	}
	
	return new mv(cc);
}
/**
 * Returns a * b * inverse(a) using default metric.
 */
public final static mv applyVersor(final mv_if a, final mv_if b)
{
	return extractGrade(gp(gp(a, b), versorInverse(a)), b.to_mv().gu());
}
/**
 * Returns a * b * reverse(a) using default metric. Only gives the correct result when the versor has a positive squared norm.
 * 
 */
public final static mv applyUnitVersor(final mv_if a, final mv_if b)
{
	return extractGrade(gp(gp(a, b), reverse(a)), b.to_mv().gu());
}
/**
 * Returns a * b * reverse(a) using default metric. Only gives the correct result when the versor has a positive squared norm.
 * 
 */
public final static mv applyVersorWI(final mv_if a, final mv_if b, final mv_if c)
{
	return extractGrade(gp(gp(a, b), c), b.to_mv().gu());
}
/**
 * Returns dual of mv using default metric.
 */
public final static mv dual(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (cc[6] == null) cc[6] = new float[1];
		dual_default_0_6(ac[0], cc[6]);
	}
	
	if (ac[1] != null) {
		if (cc[5] == null) cc[5] = new float[6];
		dual_default_1_5(ac[1], cc[5]);
	}
	
	if (ac[2] != null) {
		if (cc[4] == null) cc[4] = new float[15];
		dual_default_2_4(ac[2], cc[4]);
	}
	
	if (ac[3] != null) {
		if (cc[3] == null) cc[3] = new float[20];
		dual_default_3_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		if (cc[2] == null) cc[2] = new float[15];
		dual_default_4_2(ac[4], cc[2]);
	}
	
	if (ac[5] != null) {
		if (cc[1] == null) cc[1] = new float[6];
		dual_default_5_1(ac[5], cc[1]);
	}
	
	if (ac[6] != null) {
		if (cc[0] == null) cc[0] = new float[1];
		dual_default_6_0(ac[6], cc[0]);
	}
	
	return new mv(cc);
}
/**
 * Returns undual of mv using default metric.
 */
public final static mv undual(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (cc[6] == null) cc[6] = new float[1];
		undual_default_0_6(ac[0], cc[6]);
	}
	
	if (ac[1] != null) {
		if (cc[5] == null) cc[5] = new float[6];
		undual_default_1_5(ac[1], cc[5]);
	}
	
	if (ac[2] != null) {
		if (cc[4] == null) cc[4] = new float[15];
		undual_default_2_4(ac[2], cc[4]);
	}
	
	if (ac[3] != null) {
		if (cc[3] == null) cc[3] = new float[20];
		undual_default_3_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		if (cc[2] == null) cc[2] = new float[15];
		undual_default_4_2(ac[4], cc[2]);
	}
	
	if (ac[5] != null) {
		if (cc[1] == null) cc[1] = new float[6];
		undual_default_5_1(ac[5], cc[1]);
	}
	
	if (ac[6] != null) {
		if (cc[0] == null) cc[0] = new float[1];
		undual_default_6_0(ac[6], cc[0]);
	}
	
	return new mv(cc);
}
/**
 * Returns whether input multivectors are equal up to an epsilon c.
 */
public final static boolean equals(final mv_if a, final mv_if b, final float c)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (!equals_0_0(ac[0], bc[0], c)) return false;
		}
		else if (!zeroGroup_0(ac[0], c)) return false;
	}
		else if (bc[0] != null) {
		if (!zeroGroup_0(bc[0], c)) return false;
	}
	
	if (ac[1] != null) {
		if (bc[1] != null) {
			if (!equals_1_1(ac[1], bc[1], c)) return false;
		}
		else if (!zeroGroup_1(ac[1], c)) return false;
	}
		else if (bc[1] != null) {
		if (!zeroGroup_1(bc[1], c)) return false;
	}
	
	if (ac[2] != null) {
		if (bc[2] != null) {
			if (!equals_2_2(ac[2], bc[2], c)) return false;
		}
		else if (!zeroGroup_2(ac[2], c)) return false;
	}
		else if (bc[2] != null) {
		if (!zeroGroup_2(bc[2], c)) return false;
	}
	
	if (ac[3] != null) {
		if (bc[3] != null) {
			if (!equals_3_3(ac[3], bc[3], c)) return false;
		}
		else if (!zeroGroup_3(ac[3], c)) return false;
	}
		else if (bc[3] != null) {
		if (!zeroGroup_3(bc[3], c)) return false;
	}
	
	if (ac[4] != null) {
		if (bc[4] != null) {
			if (!equals_4_4(ac[4], bc[4], c)) return false;
		}
		else if (!zeroGroup_4(ac[4], c)) return false;
	}
		else if (bc[4] != null) {
		if (!zeroGroup_4(bc[4], c)) return false;
	}
	
	if (ac[5] != null) {
		if (bc[5] != null) {
			if (!equals_5_5(ac[5], bc[5], c)) return false;
		}
		else if (!zeroGroup_5(ac[5], c)) return false;
	}
		else if (bc[5] != null) {
		if (!zeroGroup_5(bc[5], c)) return false;
	}
	
	if (ac[6] != null) {
		if (bc[6] != null) {
			if (!equals_6_6(ac[6], bc[6], c)) return false;
		}
		else if (!zeroGroup_6(ac[6], c)) return false;
	}
		else if (bc[6] != null) {
		if (!zeroGroup_6(bc[6], c)) return false;
	}
	return true;
}
/**
 * Returns grade groupBitmap of  mv.
 */
public final static mv extractGrade(final mv_if a, final int groupBitmap)
{
	int gu = a.to_mv().gu() & groupBitmap;
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if ((gu & GroupBitmap.GROUP_0) != 0) {
		cc[0] = new float[1];
		copyGroup_0(ac[0], cc[0]);
	}
	
	if ((gu & GroupBitmap.GROUP_1) != 0) {
		cc[1] = new float[6];
		copyGroup_1(ac[1], cc[1]);
	}
	
	if ((gu & GroupBitmap.GROUP_2) != 0) {
		cc[2] = new float[15];
		copyGroup_2(ac[2], cc[2]);
	}
	
	if ((gu & GroupBitmap.GROUP_3) != 0) {
		cc[3] = new float[20];
		copyGroup_3(ac[3], cc[3]);
	}
	
	if ((gu & GroupBitmap.GROUP_4) != 0) {
		cc[4] = new float[15];
		copyGroup_4(ac[4], cc[4]);
	}
	
	if ((gu & GroupBitmap.GROUP_5) != 0) {
		cc[5] = new float[6];
		copyGroup_5(ac[5], cc[5]);
	}
	
	if ((gu & GroupBitmap.GROUP_6) != 0) {
		cc[6] = new float[1];
		copyGroup_6(ac[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns geometric product of mv and mv.
 */
public final static mv gp(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_0_1_1(ac[0], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_0_2_2(ac[0], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_0_3_3(ac[0], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_0_4_4(ac[0], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_0_5_5(ac[0], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_0_6_6(ac[0], bc[6], cc[6]);
		}
	}
	if (ac[1] != null) {
		if (bc[0] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_0_1(ac[1], bc[0], cc[1]);
		}
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_1_2(ac[1], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_2_1(ac[1], bc[2], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_2_3(ac[1], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_3_2(ac[1], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_3_4(ac[1], bc[3], cc[4]);
		}
		if (bc[4] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_4_3(ac[1], bc[4], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_4_5(ac[1], bc[4], cc[5]);
		}
		if (bc[5] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_5_4(ac[1], bc[5], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_1_5_6(ac[1], bc[5], cc[6]);
		}
		if (bc[6] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_6_5(ac[1], bc[6], cc[5]);
		}
	}
	if (ac[2] != null) {
		if (bc[0] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_0_2(ac[2], bc[0], cc[2]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_1_1(ac[2], bc[1], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_1_3(ac[2], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_2_2(ac[2], bc[2], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_2_4(ac[2], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_3_1(ac[2], bc[3], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_3_3(ac[2], bc[3], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_2_3_5(ac[2], bc[3], cc[5]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_4_2(ac[2], bc[4], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_4_4(ac[2], bc[4], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_2_4_6(ac[2], bc[4], cc[6]);
		}
		if (bc[5] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_5_3(ac[2], bc[5], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_2_5_5(ac[2], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_6_4(ac[2], bc[6], cc[4]);
		}
	}
	if (ac[3] != null) {
		if (bc[0] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_0_3(ac[3], bc[0], cc[3]);
		}
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_1_2(ac[3], bc[1], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_3_1_4(ac[3], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_2_1(ac[3], bc[2], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_2_3(ac[3], bc[2], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_3_2_5(ac[3], bc[2], cc[5]);
		}
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_3_2(ac[3], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_3_3_4(ac[3], bc[3], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_3_3_6(ac[3], bc[3], cc[6]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_4_1(ac[3], bc[4], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_4_3(ac[3], bc[4], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_3_4_5(ac[3], bc[4], cc[5]);
		}
		if (bc[5] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_5_2(ac[3], bc[5], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_3_5_4(ac[3], bc[5], cc[4]);
		}
		if (bc[6] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_6_3(ac[3], bc[6], cc[3]);
		}
	}
	if (ac[4] != null) {
		if (bc[0] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_0_4(ac[4], bc[0], cc[4]);
		}
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_1_3(ac[4], bc[1], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_4_1_5(ac[4], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_2_2(ac[4], bc[2], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_2_4(ac[4], bc[2], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_4_2_6(ac[4], bc[2], cc[6]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_3_1(ac[4], bc[3], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_3_3(ac[4], bc[3], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_4_3_5(ac[4], bc[3], cc[5]);
		}
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_4_2(ac[4], bc[4], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_4_4(ac[4], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_5_1(ac[4], bc[5], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_5_3(ac[4], bc[5], cc[3]);
		}
		if (bc[6] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_6_2(ac[4], bc[6], cc[2]);
		}
	}
	if (ac[5] != null) {
		if (bc[0] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_0_5(ac[5], bc[0], cc[5]);
		}
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_5_1_4(ac[5], bc[1], cc[4]);
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_5_1_6(ac[5], bc[1], cc[6]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_5_2_3(ac[5], bc[2], cc[3]);
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_2_5(ac[5], bc[2], cc[5]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_5_3_2(ac[5], bc[3], cc[2]);
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_5_3_4(ac[5], bc[3], cc[4]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_4_1(ac[5], bc[4], cc[1]);
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_5_4_3(ac[5], bc[4], cc[3]);
		}
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_5_5_2(ac[5], bc[5], cc[2]);
		}
		if (bc[6] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_6_1(ac[5], bc[6], cc[1]);
		}
	}
	if (ac[6] != null) {
		if (bc[0] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_6_0_6(ac[6], bc[0], cc[6]);
		}
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_6_1_5(ac[6], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_6_2_4(ac[6], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_6_3_3(ac[6], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_6_4_2(ac[6], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_6_5_1(ac[6], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
/**
 * Returns Hadamard product (coordinate-wise multiplication) of mv and mv.
 */
public final static mv hp(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		if (bc[0] != null) {
			cc[0] = new float[1];
			hp_0_0(ac[0], bc[0], cc[0]);
		}
	}
	
	if (ac[1] != null) {
		if (bc[1] != null) {
			cc[1] = new float[6];
			hp_1_1(ac[1], bc[1], cc[1]);
		}
	}
	
	if (ac[2] != null) {
		if (bc[2] != null) {
			cc[2] = new float[15];
			hp_2_2(ac[2], bc[2], cc[2]);
		}
	}
	
	if (ac[3] != null) {
		if (bc[3] != null) {
			cc[3] = new float[20];
			hp_3_3(ac[3], bc[3], cc[3]);
		}
	}
	
	if (ac[4] != null) {
		if (bc[4] != null) {
			cc[4] = new float[15];
			hp_4_4(ac[4], bc[4], cc[4]);
		}
	}
	
	if (ac[5] != null) {
		if (bc[5] != null) {
			cc[5] = new float[6];
			hp_5_5(ac[5], bc[5], cc[5]);
		}
	}
	
	if (ac[6] != null) {
		if (bc[6] != null) {
			cc[6] = new float[1];
			hp_6_6(ac[6], bc[6], cc[6]);
		}
	}
	return new mv(cc);
}
/**
 * Returns Hadamard product (coordinate-wise multiplication) of mv and mv.
 */
public final static mv ihp(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		if (bc[0] != null) {
			cc[0] = new float[1];
			ihp_0_0(ac[0], bc[0], cc[0]);
		}
	}
	
	if (ac[1] != null) {
		if (bc[1] != null) {
			cc[1] = new float[6];
			ihp_1_1(ac[1], bc[1], cc[1]);
		}
	}
	
	if (ac[2] != null) {
		if (bc[2] != null) {
			cc[2] = new float[15];
			ihp_2_2(ac[2], bc[2], cc[2]);
		}
	}
	
	if (ac[3] != null) {
		if (bc[3] != null) {
			cc[3] = new float[20];
			ihp_3_3(ac[3], bc[3], cc[3]);
		}
	}
	
	if (ac[4] != null) {
		if (bc[4] != null) {
			cc[4] = new float[15];
			ihp_4_4(ac[4], bc[4], cc[4]);
		}
	}
	
	if (ac[5] != null) {
		if (bc[5] != null) {
			cc[5] = new float[6];
			ihp_5_5(ac[5], bc[5], cc[5]);
		}
	}
	
	if (ac[6] != null) {
		if (bc[6] != null) {
			cc[6] = new float[1];
			ihp_6_6(ac[6], bc[6], cc[6]);
		}
	}
	return new mv(cc);
}
/**
 * Returns a * versorInverse(b).
 */
public final static mv igp(final mv_if a, final mv_if b)
{
	
	float _N2_ = norm2_returns_scalar(b.to_mv());
	return div_dont_mangle_1(
		gp(a, reverse(b)),
		_N2_);
}
/**
 * Returns (a + 1).
 */
public final static mv increment(final mv_if a)
{
	mv _dst = new mv(a.to_mv());
	float val = _dst.get_scalar() + 1.0f;
	_dst.set_scalar(val);
	return _dst;
}
/**
 * Returns (a - 1).
 */
public final static mv decrement(final mv_if a)
{
	mv _dst = new mv(a.to_mv());
	float val = _dst.get_scalar() - 1.0f;
	_dst.set_scalar(val);
	return _dst;
}
/**
 * Returns Hestenes inner product of mv and mv.
 */
public final static mv hip(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[1] != null) {
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_2_1(ac[1], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_3_2(ac[1], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_4_3(ac[1], bc[4], cc[3]);
		}
		if (bc[5] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_5_4(ac[1], bc[5], cc[4]);
		}
		if (bc[6] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_6_5(ac[1], bc[6], cc[5]);
		}
	}
	if (ac[2] != null) {
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_1_1(ac[2], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_3_1(ac[2], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_4_2(ac[2], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_5_3(ac[2], bc[5], cc[3]);
		}
		if (bc[6] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_6_4(ac[2], bc[6], cc[4]);
		}
	}
	if (ac[3] != null) {
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_1_2(ac[3], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_2_1(ac[3], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_4_1(ac[3], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_5_2(ac[3], bc[5], cc[2]);
		}
		if (bc[6] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_6_3(ac[3], bc[6], cc[3]);
		}
	}
	if (ac[4] != null) {
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_1_3(ac[4], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_2_2(ac[4], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_3_1(ac[4], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_5_1(ac[4], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_6_2(ac[4], bc[6], cc[2]);
		}
	}
	if (ac[5] != null) {
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_5_1_4(ac[5], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_5_2_3(ac[5], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_5_3_2(ac[5], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_4_1(ac[5], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
		}
		if (bc[6] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_6_1(ac[5], bc[6], cc[1]);
		}
	}
	if (ac[6] != null) {
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_6_1_5(ac[6], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_6_2_4(ac[6], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_6_3_3(ac[6], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_6_4_2(ac[6], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_6_5_1(ac[6], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
/**
 * Returns Modified Hestenes inner product of mv and mv.
 */
public final static mv mhip(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_0_1_1(ac[0], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_0_2_2(ac[0], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_0_3_3(ac[0], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_0_4_4(ac[0], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_0_5_5(ac[0], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_0_6_6(ac[0], bc[6], cc[6]);
		}
	}
	if (ac[1] != null) {
		if (bc[0] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_0_1(ac[1], bc[0], cc[1]);
		}
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_2_1(ac[1], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_3_2(ac[1], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_4_3(ac[1], bc[4], cc[3]);
		}
		if (bc[5] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_5_4(ac[1], bc[5], cc[4]);
		}
		if (bc[6] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_6_5(ac[1], bc[6], cc[5]);
		}
	}
	if (ac[2] != null) {
		if (bc[0] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_0_2(ac[2], bc[0], cc[2]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_1_1(ac[2], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_3_1(ac[2], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_4_2(ac[2], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_5_3(ac[2], bc[5], cc[3]);
		}
		if (bc[6] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_6_4(ac[2], bc[6], cc[4]);
		}
	}
	if (ac[3] != null) {
		if (bc[0] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_0_3(ac[3], bc[0], cc[3]);
		}
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_1_2(ac[3], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_2_1(ac[3], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_4_1(ac[3], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_5_2(ac[3], bc[5], cc[2]);
		}
		if (bc[6] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_6_3(ac[3], bc[6], cc[3]);
		}
	}
	if (ac[4] != null) {
		if (bc[0] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_0_4(ac[4], bc[0], cc[4]);
		}
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_1_3(ac[4], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_2_2(ac[4], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_3_1(ac[4], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_5_1(ac[4], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_6_2(ac[4], bc[6], cc[2]);
		}
	}
	if (ac[5] != null) {
		if (bc[0] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_0_5(ac[5], bc[0], cc[5]);
		}
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_5_1_4(ac[5], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_5_2_3(ac[5], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_5_3_2(ac[5], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_4_1(ac[5], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
		}
		if (bc[6] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_6_1(ac[5], bc[6], cc[1]);
		}
	}
	if (ac[6] != null) {
		if (bc[0] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_6_0_6(ac[6], bc[0], cc[6]);
		}
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_6_1_5(ac[6], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_6_2_4(ac[6], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_6_3_3(ac[6], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_6_4_2(ac[6], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_6_5_1(ac[6], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
/**
 * Returns left contraction of mv and mv.
 */
public final static mv lc(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_0_1_1(ac[0], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_0_2_2(ac[0], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_0_3_3(ac[0], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_0_4_4(ac[0], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_0_5_5(ac[0], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_0_6_6(ac[0], bc[6], cc[6]);
		}
	}
	if (ac[1] != null) {
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_2_1(ac[1], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_3_2(ac[1], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_4_3(ac[1], bc[4], cc[3]);
		}
		if (bc[5] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_5_4(ac[1], bc[5], cc[4]);
		}
		if (bc[6] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_6_5(ac[1], bc[6], cc[5]);
		}
	}
	if (ac[2] != null) {
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_3_1(ac[2], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_4_2(ac[2], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_5_3(ac[2], bc[5], cc[3]);
		}
		if (bc[6] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_6_4(ac[2], bc[6], cc[4]);
		}
	}
	if (ac[3] != null) {
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_4_1(ac[3], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_5_2(ac[3], bc[5], cc[2]);
		}
		if (bc[6] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_6_3(ac[3], bc[6], cc[3]);
		}
	}
	if (ac[4] != null) {
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_5_1(ac[4], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_6_2(ac[4], bc[6], cc[2]);
		}
	}
	if (ac[5] != null) {
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
		}
		if (bc[6] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_6_1(ac[5], bc[6], cc[1]);
		}
	}
	if (ac[6] != null) {
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
/**
 * Returns right contraction of mv and mv.
 */
public final static mv rc(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
	}
	if (ac[1] != null) {
		if (bc[0] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_0_1(ac[1], bc[0], cc[1]);
		}
		if (bc[1] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
		}
	}
	if (ac[2] != null) {
		if (bc[0] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_0_2(ac[2], bc[0], cc[2]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_2_1_1(ac[2], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
		}
	}
	if (ac[3] != null) {
		if (bc[0] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_0_3(ac[3], bc[0], cc[3]);
		}
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_3_1_2(ac[3], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_3_2_1(ac[3], bc[2], cc[1]);
		}
		if (bc[3] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
		}
	}
	if (ac[4] != null) {
		if (bc[0] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_0_4(ac[4], bc[0], cc[4]);
		}
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_4_1_3(ac[4], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_4_2_2(ac[4], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_4_3_1(ac[4], bc[3], cc[1]);
		}
		if (bc[4] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
		}
	}
	if (ac[5] != null) {
		if (bc[0] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_0_5(ac[5], bc[0], cc[5]);
		}
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_5_1_4(ac[5], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_5_2_3(ac[5], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_5_3_2(ac[5], bc[3], cc[2]);
		}
		if (bc[4] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_5_4_1(ac[5], bc[4], cc[1]);
		}
		if (bc[5] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
		}
	}
	if (ac[6] != null) {
		if (bc[0] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_6_0_6(ac[6], bc[0], cc[6]);
		}
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_6_1_5(ac[6], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_6_2_4(ac[6], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_6_3_3(ac[6], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_6_4_2(ac[6], bc[4], cc[2]);
		}
		if (bc[5] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_6_5_1(ac[6], bc[5], cc[1]);
		}
		if (bc[6] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return new mv(cc);
}
/**
 * Returns scalar product of mv and mv.
 */
public final static float sp(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	cc[0] = new float[1];
	if (ac[0] != null) {
		if (bc[0] != null) {
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
	}
	if (ac[1] != null) {
		if (bc[1] != null) {
			gp_default_1_1_0(ac[1], bc[1], cc[0]);
		}
	}
	if (ac[2] != null) {
		if (bc[2] != null) {
			gp_default_2_2_0(ac[2], bc[2], cc[0]);
		}
	}
	if (ac[3] != null) {
		if (bc[3] != null) {
			gp_default_3_3_0(ac[3], bc[3], cc[0]);
		}
	}
	if (ac[4] != null) {
		if (bc[4] != null) {
			gp_default_4_4_0(ac[4], bc[4], cc[0]);
		}
	}
	if (ac[5] != null) {
		if (bc[5] != null) {
			gp_default_5_5_0(ac[5], bc[5], cc[0]);
		}
	}
	if (ac[6] != null) {
		if (bc[6] != null) {
			gp_default_6_6_0(ac[6], bc[6], cc[0]);
		}
	}
	return cc[0][0];
}
/**
 * Returns norm of mv using default metric.
 */
public final static float norm(final mv_if a)
{
	float n2 = 0.0f;
	float[] c = new float[1];
	float[][] ac = a.to_mv().c();
	if (ac[0] != null) { /* group 0 (grade 0) */
		c[0] = 0.0f;
			gp_default_0_0_0(ac[0], ac[0], c);
		n2 += c[0];
	}
	if (ac[1] != null) { /* group 1 (grade 1) */
		c[0] = 0.0f;
			gp_default_1_1_0(ac[1], ac[1], c);
		n2 += c[0];
	}
	if (ac[2] != null) { /* group 2 (grade 2) */
		c[0] = 0.0f;
			gp_default_2_2_0(ac[2], ac[2], c);
		n2 -= c[0];
	}
	if (ac[3] != null) { /* group 3 (grade 3) */
		c[0] = 0.0f;
			gp_default_3_3_0(ac[3], ac[3], c);
		n2 -= c[0];
	}
	if (ac[4] != null) { /* group 4 (grade 4) */
		c[0] = 0.0f;
			gp_default_4_4_0(ac[4], ac[4], c);
		n2 += c[0];
	}
	if (ac[5] != null) { /* group 5 (grade 5) */
		c[0] = 0.0f;
			gp_default_5_5_0(ac[5], ac[5], c);
		n2 += c[0];
	}
	if (ac[6] != null) { /* group 6 (grade 6) */
		c[0] = 0.0f;
			gp_default_6_6_0(ac[6], ac[6], c);
		n2 -= c[0];
	}
	return ((n2 < 0.0f) ? (float)Math.sqrt(-n2) : (float)Math.sqrt(n2));
}
/**
 * internal conversion function
 */
public final static float norm_returns_scalar(final mv a) {
	return norm(a);
}
/**
 * Returns norm2 of mv using default metric.
 */
public final static float norm2(final mv_if a)
{
	float n2 = 0.0f;
	float[] c = new float[1];
	float[][] ac = a.to_mv().c();
	if (ac[0] != null) { /* group 0 (grade 0) */
		c[0] = 0.0f;
			gp_default_0_0_0(ac[0], ac[0], c);
		n2 += c[0];
	}
	if (ac[1] != null) { /* group 1 (grade 1) */
		c[0] = 0.0f;
			gp_default_1_1_0(ac[1], ac[1], c);
		n2 += c[0];
	}
	if (ac[2] != null) { /* group 2 (grade 2) */
		c[0] = 0.0f;
			gp_default_2_2_0(ac[2], ac[2], c);
		n2 -= c[0];
	}
	if (ac[3] != null) { /* group 3 (grade 3) */
		c[0] = 0.0f;
			gp_default_3_3_0(ac[3], ac[3], c);
		n2 -= c[0];
	}
	if (ac[4] != null) { /* group 4 (grade 4) */
		c[0] = 0.0f;
			gp_default_4_4_0(ac[4], ac[4], c);
		n2 += c[0];
	}
	if (ac[5] != null) { /* group 5 (grade 5) */
		c[0] = 0.0f;
			gp_default_5_5_0(ac[5], ac[5], c);
		n2 += c[0];
	}
	if (ac[6] != null) { /* group 6 (grade 6) */
		c[0] = 0.0f;
			gp_default_6_6_0(ac[6], ac[6], c);
		n2 -= c[0];
	}
	return n2;
}
/**
 * internal conversion function
 */
public final static float norm2_returns_scalar(final mv a) {
	return norm2(a);
}
/**
 * Returns outer product of mv and mv.
 */
public final static mv op(final mv_if a, final mv_if b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = b.to_mv().c();
	float[][] cc = new float[7][];
	if (ac[0] != null) {
		if (bc[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
		}
		if (bc[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_0_1_1(ac[0], bc[1], cc[1]);
		}
		if (bc[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_0_2_2(ac[0], bc[2], cc[2]);
		}
		if (bc[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_0_3_3(ac[0], bc[3], cc[3]);
		}
		if (bc[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_0_4_4(ac[0], bc[4], cc[4]);
		}
		if (bc[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_0_5_5(ac[0], bc[5], cc[5]);
		}
		if (bc[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_0_6_6(ac[0], bc[6], cc[6]);
		}
	}
	if (ac[1] != null) {
		if (bc[0] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_0_1(ac[1], bc[0], cc[1]);
		}
		if (bc[1] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_1_1_2(ac[1], bc[1], cc[2]);
		}
		if (bc[2] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_1_2_3(ac[1], bc[2], cc[3]);
		}
		if (bc[3] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_1_3_4(ac[1], bc[3], cc[4]);
		}
		if (bc[4] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_1_4_5(ac[1], bc[4], cc[5]);
		}
		if (bc[5] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_1_5_6(ac[1], bc[5], cc[6]);
		}
	}
	if (ac[2] != null) {
		if (bc[0] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_0_2(ac[2], bc[0], cc[2]);
		}
		if (bc[1] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_2_1_3(ac[2], bc[1], cc[3]);
		}
		if (bc[2] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_2_2_4(ac[2], bc[2], cc[4]);
		}
		if (bc[3] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_2_3_5(ac[2], bc[3], cc[5]);
		}
		if (bc[4] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_2_4_6(ac[2], bc[4], cc[6]);
		}
	}
	if (ac[3] != null) {
		if (bc[0] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_0_3(ac[3], bc[0], cc[3]);
		}
		if (bc[1] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_3_1_4(ac[3], bc[1], cc[4]);
		}
		if (bc[2] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_3_2_5(ac[3], bc[2], cc[5]);
		}
		if (bc[3] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_3_3_6(ac[3], bc[3], cc[6]);
		}
	}
	if (ac[4] != null) {
		if (bc[0] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_0_4(ac[4], bc[0], cc[4]);
		}
		if (bc[1] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_4_1_5(ac[4], bc[1], cc[5]);
		}
		if (bc[2] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_4_2_6(ac[4], bc[2], cc[6]);
		}
	}
	if (ac[5] != null) {
		if (bc[0] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_0_5(ac[5], bc[0], cc[5]);
		}
		if (bc[1] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_5_1_6(ac[5], bc[1], cc[6]);
		}
	}
	if (ac[6] != null) {
		if (bc[0] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_6_0_6(ac[6], bc[0], cc[6]);
		}
	}
	return new mv(cc);
}
/**
 * Returns float b * mv a + float c.
 */
public final static mv sas(final mv_if a, final float b, final float c)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyMul_0(ac[0], cc[0], b);
		cc[0][0] += c;
	}
	else if (c != 0.0) {
		cc[0] = new float[1];
	cc[0][0] = c;
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		copyMul_1(ac[1], cc[1], b);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		copyMul_2(ac[2], cc[2], b);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		copyMul_3(ac[3], cc[3], b);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyMul_4(ac[4], cc[4], b);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		copyMul_5(ac[5], cc[5], b);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		copyMul_6(ac[6], cc[6], b);
	}
	return new mv(cc);
}

/**
 * Computes exponential of mv up to 12th term.
 * 
 */
public final static mv exp(final mv x) {
	return exp(x, 12);
}

/**
 * Computes exponential of mv.
 * 
 */
public final static mv exp(final mv x, final int order) {
   
	{ // First try special cases: check if (x * x) is scalar
		mv xSquared = gp(x, x);
		float s_xSquared = xSquared.get_scalar();
		if ((norm2_returns_scalar(xSquared) - s_xSquared * s_xSquared) < 1E-06f) {
			// OK (x * x == ~scalar), so use special cases:
			if (s_xSquared < 0.0f) {
				float a = (float)Math.sqrt(-s_xSquared);
				return sas(x, (float)Math.sin(a) / a, (float)Math.cos(a));
			}
			else if (s_xSquared > 0.0f) {
				float a = (float)Math.sqrt(s_xSquared);
				return sas(x, (float)Math.sinh(a) / a, (float)Math.cosh(a));
			}
			else {
				return sas(x, 1.0f, 1.0f);
			}
		}
	}

	// else do general series eval . . .

	// result = 1 + ....	
	mv result = new mv(1.0f);
	if (order == 0) return result;

	// find scale (power of 2) such that its norm is < 1
	long maxC = (long)x.largestCoordinate();
	int scale = 1;
	if (maxC > 1) scale <<= 1;
	while (maxC != 0)
	{
		maxC >>= 1;
		scale <<= 1;
	}

	// scale
	mv xScaled = gp_dont_mangle_2(x, 1.0f / (float)scale); 

	// taylor series approximation
	mv xPow1 = new mv(1.0f); 
	for (int i = 1; i <= order; i++) {
		mv xPow2 = gp(xPow1, xScaled);
		xPow1 = gp_dont_mangle_2(xPow2, 1.0f / (float)i);
		
		result = add(result, xPow1); // result2 = result1 + xPow1
    }

	// undo scaling
	while (scale > 1)
	{
		result = gp(result, result);
		scale >>= 1;
	}
    
    return result;
} // end of exp()


/**
 * Computes sine of mv up to 12th term.
 * 
 */
public final static mv sin(final mv x) {
	return sin(x, 12);
}

/**
 * Computes sine of mv.
 * 
 */
public final static mv sin(final mv x, final int order) {
   
	{ // First try special cases: check if (x * x) is scalar
		mv xSquared = gp(x, x);
		float s_xSquared = xSquared.get_scalar();
		if ((norm2_returns_scalar(xSquared) - s_xSquared * s_xSquared) < 1E-06f) {
			// OK (x * x == ~scalar), so use special cases:
			if (s_xSquared < 0.0f) {
				float a = (float)Math.sqrt(-s_xSquared);
				return sas(x, (float)Math.sinh(a) / a, 0.0f);
			}
			else if (s_xSquared > 0.0f) {
				float a = (float)Math.sqrt(s_xSquared);
				return sas(x, (float)Math.sin(a) / a, 0.0f);
			}
			else {
				return x;
			}
		}
	}

	// else do general series eval . . .

	// result = A -  ....	+ ... - ...
	mv result = new mv(); // result = 0;
    if (order == 0) return result;
    	
	// taylor series approximation
	mv xPow1 = new mv(1.0f); // xPow1 = 1.0
	for (int i = 1; i <= order; i++) {
		mv xPow2 = gp(xPow1, x); // xPow2 = xPow1 * x
		
		xPow1 = gp_dont_mangle_2(xPow2, 1.0f / (float)i); // xPow1 = xScaled^i / i! 
		
		if ((i % 4) == 3)
		{
			result = subtract(result, xPow1); // result = result - xPow1
		}
		else if ((i % 4) == 1) 
		{
			result = add(result, xPow1); // result = result + xPow1
		}
	}

	return result;
} // end of sin()


/**
 * Computes cosine of mv up to 12th term.
 * 
 */
public final static mv cos(final mv x) {
	return cos(x, 12);
}

/**
 * Computes cosine of mv.
 * 
 */
public final static mv cos(final mv x, final int order) {
	{ // First try special cases: check if (x * x) is scalar
		mv xSquared = gp(x, x);
		float s_xSquared = xSquared.get_scalar();
		if ((norm2_returns_scalar(xSquared) - s_xSquared * s_xSquared) < 1E-06f) {
			// OK (x * x == ~scalar), so use special cases:
			if (s_xSquared > 0.0f) {
				return new mv((float)Math.cos((float)Math.sqrt(s_xSquared)));
			}
			else if (s_xSquared < 0.0f) {
				return new mv((float)Math.cosh((float)Math.sqrt(-s_xSquared)));
			}
			else {
				return new mv(1.0f);
			}
		}
	}

	// else do general series eval . . .


	mv result = new mv(1.0f);
	if (order == 0) return result;

	// taylor series approximation
	mv xPow1 = new mv(1.0f); // xPow1 = 1.0
	for (int i = 1; i <= order; i++) {
		mv xPow2 = gp(xPow1, x); // xPow2 = xPow1 * x
		xPow1 = gp_dont_mangle_2(xPow2, 1.0f / (float)i); // xPow1 = xScaled^i / i! 
		
		if ((i % 4) == 2)
		{
			result = subtract(result, xPow1); // result2 = result1 - xPow1
		}
		else if ((i % 4) == 0) 
		{
			result = add(result, xPow1); // result2 = result1 + xPow1
		}		
    }

	return result;
} // end of cos()

/**
 * Computes hyperbolic sine of mv up to 12th term.
 * 
 */
public final static mv sinh(final mv x) {
	return sinh(x, 12);
}

/**
 * Computes hyperbolic sine of mv.
 * 
 */
public final static mv sinh(final mv x, final int order) {
   
	{ // First try special cases: check if (x * x) is scalar
		mv xSquared = gp(x, x);
		float s_xSquared = xSquared.get_scalar();
		if ((norm2_returns_scalar(xSquared) - s_xSquared * s_xSquared) < 1E-06f) {
			// OK (x * x == ~scalar), so use special cases:
			if (s_xSquared < 0.0f) {
				float a = (float)Math.sqrt(-s_xSquared);
				return sas(x, (float)Math.sin(a) / a, 0.0f);
			}
			else if (s_xSquared > 0.0f) {
				float a = (float)Math.sqrt(s_xSquared);
				return sas(x, (float)Math.sinh(a) / a, 0.0f);
			}
			else {
				return x;
			}
		}
	}

	// else do general series eval . . .

	// result = A +  A^3/3! + A^5/5!
	mv result = new mv(); // result = 0
    if (order == 0) return result;
    	
	// taylor series approximation
	mv xPow1 = new mv(1.0f);
	for (int i = 1; i <= order; i++) {
		mv xPow2 = gp(xPow1, x); // xPow2 = xPow1 * x
		xPow1 = gp_dont_mangle_2(xPow2, 1.0f / (float)i); // xPow1 = xScaled^i / i! 
		
		if ((i % 2) == 1) {
			result = add(result, xPow1); 
		}
	}

    return result;
} // end of sinh()

/**
 * Computes hyperbolic cosine of mv up to 12th term.
 * 
 */
public final static mv cosh(final mv x) {
	return cosh(x, 12);
}

/**
 * Computes hyperbolic cosine of mv.
 * 
 */
public final static mv cosh(final mv x, final int order) {
   
	{ // First try special cases: check if (x * x) is scalar
		mv xSquared = gp(x, x);
		float s_xSquared = xSquared.get_scalar();
		if ((norm2_returns_scalar(xSquared) - s_xSquared * s_xSquared) < 1E-06f) {
			// OK (x * x == ~scalar), so use special cases:
			if (s_xSquared > 0.0f) {
				return new mv((float)Math.cosh((float)Math.sqrt(s_xSquared)));
			}
			else if (s_xSquared < 0.0f) {
				return new mv((float)Math.cos((float)Math.sqrt(-s_xSquared)));
			}
			else {
				return new mv(1.0f);
			}
		}
	}

	// else do general series eval . . .


	mv result = new mv(1.0f);
	if (order == 0) return result;

	// taylor series approximation
	mv xPow1 = new mv(1.0f);
	for (int i = 1; i <= order; i++) {
		mv xPow2 = gp(xPow1, x);
		xPow1 = gp_dont_mangle_2(xPow2, 1.0f / (float)i); // xPow1 = xScaled^i / i! 
		
		if ((i % 2) == 0) {
			result = add(result, xPow1); 
		}
    }

    return result;
} // end of cosh()
/**
 * Returns negation of mv.
 */
public final static mv negate(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		neg_0(ac[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		neg_1(ac[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		neg_2(ac[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		neg_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		neg_4(ac[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		neg_5(ac[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		neg_6(ac[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns reverse of mv.
 */
public final static mv reverse(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyGroup_0(ac[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		copyGroup_1(ac[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		neg_2(ac[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		neg_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyGroup_4(ac[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		copyGroup_5(ac[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		neg_6(ac[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns Clifford conjugate of mv.
 */
public final static mv cliffordConjugate(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyGroup_0(ac[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		neg_1(ac[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		neg_2(ac[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		copyGroup_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyGroup_4(ac[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		neg_5(ac[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		neg_6(ac[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns grade involution of mv.
 */
public final static mv gradeInvolution(final mv_if a)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyGroup_0(ac[0], cc[0]);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		neg_1(ac[1], cc[1]);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		copyGroup_2(ac[2], cc[2]);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		neg_3(ac[3], cc[3]);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyGroup_4(ac[4], cc[4]);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		neg_5(ac[5], cc[5]);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		copyGroup_6(ac[6], cc[6]);
	}
	return new mv(cc);
}
/**
 * Returns unit of mv using default metric.
 */
public final static mv unit(final mv_if a)
{
	float n = norm_returns_scalar(a.to_mv());
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyDiv_0(ac[0], cc[0], n);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		copyDiv_1(ac[1], cc[1], n);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		copyDiv_2(ac[2], cc[2], n);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		copyDiv_3(ac[3], cc[3], n);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyDiv_4(ac[4], cc[4], n);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		copyDiv_5(ac[5], cc[5], n);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		copyDiv_6(ac[6], cc[6], n);
	}
	return new mv(cc);
}
/**
 * Returns versor inverse of a using default metric.
 */
public final static mv versorInverse(final mv_if a)
{
	float n2 = norm2_returns_scalar(a.to_mv());
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyDiv_0(ac[0], cc[0], n2);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		copyDiv_1(ac[1], cc[1], n2);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		copyDiv_2(ac[2], cc[2], -n2);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		copyDiv_3(ac[3], cc[3], -n2);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyDiv_4(ac[4], cc[4], n2);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		copyDiv_5(ac[5], cc[5], n2);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		copyDiv_6(ac[6], cc[6], -n2);
	}
	return new mv(cc);
}
/**
 * Returns true if all coordinates of a are abs <= b
 */
public final static boolean zero(final mv_if a, final float b)
{
	float[][] ac = a.to_mv().c();
	
	if (ac[0] != null) {
		if (!zeroGroup_0(ac[0], b)) return false;
	}
	
	if (ac[1] != null) {
		if (!zeroGroup_1(ac[1], b)) return false;
	}
	
	if (ac[2] != null) {
		if (!zeroGroup_2(ac[2], b)) return false;
	}
	
	if (ac[3] != null) {
		if (!zeroGroup_3(ac[3], b)) return false;
	}
	
	if (ac[4] != null) {
		if (!zeroGroup_4(ac[4], b)) return false;
	}
	
	if (ac[5] != null) {
		if (!zeroGroup_5(ac[5], b)) return false;
	}
	
	if (ac[6] != null) {
		if (!zeroGroup_6(ac[6], b)) return false;
	}
	return true;
}
/**
 * Returns a / b
 */
public final static mv div_dont_mangle_1(final mv_if a, final float b)
{
	float[][] ac = a.to_mv().c();
	float[][] cc = new float[7][];
	
	if (ac[0] != null) {
		cc[0] = new float[1];
		copyDiv_0(ac[0], cc[0], b);
	}
	
	if (ac[1] != null) {
		cc[1] = new float[6];
		copyDiv_1(ac[1], cc[1], b);
	}
	
	if (ac[2] != null) {
		cc[2] = new float[15];
		copyDiv_2(ac[2], cc[2], b);
	}
	
	if (ac[3] != null) {
		cc[3] = new float[20];
		copyDiv_3(ac[3], cc[3], b);
	}
	
	if (ac[4] != null) {
		cc[4] = new float[15];
		copyDiv_4(ac[4], cc[4], b);
	}
	
	if (ac[5] != null) {
		cc[5] = new float[6];
		copyDiv_5(ac[5], cc[5], b);
	}
	
	if (ac[6] != null) {
		cc[6] = new float[1];
		copyDiv_6(ac[6], cc[6], b);
	}
	return new mv(cc);
}
/**
 * Returns geometric product of mv and float.
 */
public final static mv gp_dont_mangle_2(final mv_if a, final float b)
{
	float[][] ac = a.to_mv().c();
	float[][] bc = new float[][]{new float[]{b}};
	float[][] cc = new float[7][];
	if (ac[0] != null) {
			if (cc[0] == null) cc[0] = new float[1];
			gp_default_0_0_0(ac[0], bc[0], cc[0]);
	}
	if (ac[1] != null) {
			if (cc[1] == null) cc[1] = new float[6];
			gp_default_1_0_1(ac[1], bc[0], cc[1]);
	}
	if (ac[2] != null) {
			if (cc[2] == null) cc[2] = new float[15];
			gp_default_2_0_2(ac[2], bc[0], cc[2]);
	}
	if (ac[3] != null) {
			if (cc[3] == null) cc[3] = new float[20];
			gp_default_3_0_3(ac[3], bc[0], cc[3]);
	}
	if (ac[4] != null) {
			if (cc[4] == null) cc[4] = new float[15];
			gp_default_4_0_4(ac[4], bc[0], cc[4]);
	}
	if (ac[5] != null) {
			if (cc[5] == null) cc[5] = new float[6];
			gp_default_5_0_5(ac[5], bc[0], cc[5]);
	}
	if (ac[6] != null) {
			if (cc[6] == null) cc[6] = new float[1];
			gp_default_6_0_6(ac[6], bc[0], cc[6]);
	}
	return new mv(cc);
}
} // end of class pl3ga
