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
/**
 * This class can hold a general multivector.
 * 
 * The coordinates are stored in type float.
 * 
 * There are 7 coordinate groups:
 * group 0:1  (grade 0).
 * group 1:e01, e02, e03, e12, e23, e31  (grade 1).
 * group 2:e01^e02, e01^e03, e02^e03, e01^e12, e02^e12, e03^e12, e01^e23, e02^e23, e03^e23, e12^e23, e01^e31, e02^e31, e03^e31, e12^e31, e23^e31  (grade 2).
 * group 3:e01^e02^e03, e01^e02^e12, e01^e03^e12, e02^e03^e12, e01^e02^e23, e01^e03^e23, e02^e03^e23, e01^e12^e23, e02^e12^e23, e03^e12^e23, e01^e02^e31, e01^e03^e31, e02^e03^e31, e01^e12^e31, e02^e12^e31, e03^e12^e31, e01^e23^e31, e02^e23^e31, e03^e23^e31, e12^e23^e31  (grade 3).
 * group 4:e01^e02^e03^e12, e01^e02^e03^e23, e01^e02^e12^e23, e01^e03^e12^e23, e02^e03^e12^e23, e01^e02^e03^e31, e01^e02^e12^e31, e01^e03^e12^e31, e02^e03^e12^e31, e01^e02^e23^e31, e01^e03^e23^e31, e02^e03^e23^e31, e01^e12^e23^e31, e02^e12^e23^e31, e03^e12^e23^e31  (grade 4).
 * group 5:e01^e02^e03^e12^e23, e01^e02^e03^e12^e31, e01^e02^e03^e23^e31, e01^e02^e12^e23^e31, e01^e03^e12^e23^e31, e02^e03^e12^e23^e31  (grade 5).
 * group 6:e01^e02^e03^e12^e23^e31  (grade 6).
 * 
 * 64 floats are allocated inside the struct.
 * 
 */
public class mv  implements  mv_if
{ 

    /** the coordinates */
	protected float[][] m_c = new float[7][]; 
	


    /**
	* Constructs a new mv with value 0.
     */
	public mv() {set();}

    /**
	 * Copy constructor.
     */
	public mv(final mv A) {set(A);}


    /**
	 * Constructs a new mv with scalar value 'scalar'.
     */
	public mv(final float scalar) {set(scalar);}

    /** 
     * Constructs a new mv from compressed 'coordinates'.
 	 * @param gu bitwise OR of the GRADEs or GROUPs that are non-zero.
	 * @param coordinates compressed coordinates.
     */
	public mv(final int gu, final float[] coordinates) {set(gu, coordinates);}

    /** 
     * Constructs a new mv from array of array of 'coordinates'.
	 * @param coordinates The coordinates, one array for each group/grade. Make sure the
	 * array length match the size of the groups. Entries may be null.
     */
	public mv(final float[][] coordinates) {set(coordinates);}
	
    /** Converts a e01_t to a mv. */
	public mv(final e01_t A) {set(A);}
    /** Converts a e02_t to a mv. */
	public mv(final e02_t A) {set(A);}
    /** Converts a e03_t to a mv. */
	public mv(final e03_t A) {set(A);}
    /** Converts a e12_t to a mv. */
	public mv(final e12_t A) {set(A);}
    /** Converts a e23_t to a mv. */
	public mv(final e23_t A) {set(A);}
    /** Converts a e31_t to a mv. */
	public mv(final e31_t A) {set(A);}
    /** Converts a I3r_t to a mv. */
	public mv(final I3r_t A) {set(A);}
    /** Converts a I3i_t to a mv. */
	public mv(final I3i_t A) {set(A);}
    /** Converts a I6_t to a mv. */
	public mv(final I6_t A) {set(A);}
    /** Converts a line to a mv. */
	public mv(final line A) {set(A);}
    /** Converts a idealLine to a mv. */
	public mv(final idealLine A) {set(A);}
    /** Converts a pencil to a mv. */
	public mv(final pencil A) {set(A);}
    /** Converts a idealPencil to a mv. */
	public mv(final idealPencil A) {set(A);}
    /** Converts a mixedPencil to a mv. */
	public mv(final mixedPencil A) {set(A);}
    /** Converts a pseudoscalar to a mv. */
	public mv(final pseudoscalar A) {set(A);}
    /** Converts a evenVersor to a mv. */
	public mv(final evenVersor A) {set(A);}
    /** Converts a oddVersor to a mv. */
	public mv(final oddVersor A) {set(A);}


	/** returns group usage bitmap. */
	public final int gu() {
		return 
			((m_c[0] == null) ? 0 : GroupBitmap.GROUP_0) |
			((m_c[1] == null) ? 0 : GroupBitmap.GROUP_1) |
			((m_c[2] == null) ? 0 : GroupBitmap.GROUP_2) |
			((m_c[3] == null) ? 0 : GroupBitmap.GROUP_3) |
			((m_c[4] == null) ? 0 : GroupBitmap.GROUP_4) |
			((m_c[5] == null) ? 0 : GroupBitmap.GROUP_5) |
			((m_c[6] == null) ? 0 : GroupBitmap.GROUP_6) |
			0;
	}
	
    /**
	 * Returns array of array of coordinates.
	 * Each entry contain the coordinates for one group/grade.
     */
	public final float[][] c() { return m_c; }
	
	/**
	 * sets this to 0.
	 */
	public void set() {
		m_c[0] = null;
		m_c[1] = null;
		m_c[2] = null;
		m_c[3] = null;
		m_c[4] = null;
		m_c[5] = null;
		m_c[6] = null;
	}
	/**
	 * sets this to scalar value.
	 */
	public void set(float val) {
		allocateGroups(GroupBitmap.GROUP_0);
		m_c[0][0] = val;
	}
	/**
	 * sets this coordinates in 'arr'.
	 * @param gu bitwise or of the GROUPs and GRADEs which are present in 'arr'.
	 * @param arr compressed coordinates.
	 */
	public void set(int gu, float[] arr) {
		allocateGroups(gu);
		int idx = 0;
		if ((gu & GroupBitmap.GROUP_0) != 0) {
			for (int i = 0; i < 1; i++)
				m_c[0][i] = arr[idx + i];
			idx += 1;
		}
		if ((gu & GroupBitmap.GROUP_1) != 0) {
			for (int i = 0; i < 6; i++)
				m_c[1][i] = arr[idx + i];
			idx += 6;
		}
		if ((gu & GroupBitmap.GROUP_2) != 0) {
			for (int i = 0; i < 15; i++)
				m_c[2][i] = arr[idx + i];
			idx += 15;
		}
		if ((gu & GroupBitmap.GROUP_3) != 0) {
			for (int i = 0; i < 20; i++)
				m_c[3][i] = arr[idx + i];
			idx += 20;
		}
		if ((gu & GroupBitmap.GROUP_4) != 0) {
			for (int i = 0; i < 15; i++)
				m_c[4][i] = arr[idx + i];
			idx += 15;
		}
		if ((gu & GroupBitmap.GROUP_5) != 0) {
			for (int i = 0; i < 6; i++)
				m_c[5][i] = arr[idx + i];
			idx += 6;
		}
		if ((gu & GroupBitmap.GROUP_6) != 0) {
			for (int i = 0; i < 1; i++)
				m_c[6][i] = arr[idx + i];
			idx += 1;
		}
	}
	/**
	 * sets this coordinates in 'arr'. 
	 * 'arr' is kept, so changes to 'arr' will be reflected in the value of this multivector. Make sure 'arr' has length 7 and each subarray has the length of the respective group/grade
	 * @param arr coordinates.
	 */
	public void set(float[][] arr) {
		m_c = arr;
	}
	/**
	 * sets this to multivector value.
	 */
	public void set(mv src) {
		allocateGroups(src.gu());
		if (m_c[0] != null) {
			pl3ga.copy_1(m_c[0], src.m_c[0]);
		}
		if (m_c[1] != null) {
			pl3ga.copy_6(m_c[1], src.m_c[1]);
		}
		if (m_c[2] != null) {
			pl3ga.copy_15(m_c[2], src.m_c[2]);
		}
		if (m_c[3] != null) {
			pl3ga.copy_N(m_c[3], src.m_c[3], 20);
		}
		if (m_c[4] != null) {
			pl3ga.copy_15(m_c[4], src.m_c[4]);
		}
		if (m_c[5] != null) {
			pl3ga.copy_6(m_c[5], src.m_c[5]);
		}
		if (m_c[6] != null) {
			pl3ga.copy_1(m_c[6], src.m_c[6]);
		}
	}

	/**
	 * sets this to e01_t value.
	 */
	public void set(e01_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = 1.0f;
		ptr[1] = ptr[2] = ptr[3] = ptr[4] = ptr[5] = 0.0f;
	}

	/**
	 * sets this to e02_t value.
	 */
	public void set(e02_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[2] = ptr[3] = ptr[4] = ptr[5] = 0.0f;
		ptr[1] = 1.0f;
	}

	/**
	 * sets this to e03_t value.
	 */
	public void set(e03_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[1] = ptr[3] = ptr[4] = ptr[5] = 0.0f;
		ptr[2] = 1.0f;
	}

	/**
	 * sets this to e12_t value.
	 */
	public void set(e12_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[1] = ptr[2] = ptr[4] = ptr[5] = 0.0f;
		ptr[3] = 1.0f;
	}

	/**
	 * sets this to e23_t value.
	 */
	public void set(e23_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[1] = ptr[2] = ptr[3] = ptr[5] = 0.0f;
		ptr[4] = 1.0f;
	}

	/**
	 * sets this to e31_t value.
	 */
	public void set(e31_t src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[1] = ptr[2] = ptr[3] = ptr[4] = 0.0f;
		ptr[5] = 1.0f;
	}

	/**
	 * sets this to I3r_t value.
	 */
	public void set(I3r_t src) {
		allocateGroups(GroupBitmap.GROUP_3);
		float[] ptr;

		ptr = m_c[3];
		ptr[0] = 1.0f;
		ptr[1] = ptr[2] = ptr[3] = ptr[4] = ptr[5] = ptr[6] = ptr[7] = ptr[8] = ptr[9] = ptr[10] = ptr[11] = ptr[12] = ptr[13] = ptr[14] = ptr[15] = ptr[16] = ptr[17] = ptr[18] = ptr[19] = 0.0f;
	}

	/**
	 * sets this to I3i_t value.
	 */
	public void set(I3i_t src) {
		allocateGroups(GroupBitmap.GROUP_3);
		float[] ptr;

		ptr = m_c[3];
		ptr[0] = ptr[1] = ptr[2] = ptr[3] = ptr[4] = ptr[5] = ptr[6] = ptr[7] = ptr[8] = ptr[9] = ptr[10] = ptr[11] = ptr[12] = ptr[13] = ptr[14] = ptr[15] = ptr[16] = ptr[17] = ptr[18] = 0.0f;
		ptr[19] = 1.0f;
	}

	/**
	 * sets this to I6_t value.
	 */
	public void set(I6_t src) {
		allocateGroups(GroupBitmap.GROUP_6);
		float[] ptr;

		ptr = m_c[6];
		ptr[0] = 1.0f;
	}

	/**
	 * sets this to line value.
	 */
	public void set(line src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = src.m_e01;
		ptr[1] = src.m_e02;
		ptr[2] = src.m_e03;
		ptr[3] = ptr[4] = ptr[5] = 0.0f;
	}

	/**
	 * sets this to idealLine value.
	 */
	public void set(idealLine src) {
		allocateGroups(GroupBitmap.GROUP_1);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = ptr[1] = ptr[2] = 0.0f;
		ptr[3] = src.m_e12;
		ptr[4] = src.m_e23;
		ptr[5] = src.m_e31;
	}

	/**
	 * sets this to pencil value.
	 */
	public void set(pencil src) {
		allocateGroups(GroupBitmap.GROUP_2);
		float[] ptr;

		ptr = m_c[2];
		ptr[0] = src.m_e01_e02;
		ptr[1] = -src.m_e03_e01;
		ptr[2] = src.m_e02_e03;
		ptr[3] = ptr[4] = ptr[5] = ptr[6] = ptr[7] = ptr[8] = ptr[9] = ptr[10] = ptr[11] = ptr[12] = ptr[13] = ptr[14] = 0.0f;
	}

	/**
	 * sets this to idealPencil value.
	 */
	public void set(idealPencil src) {
		allocateGroups(GroupBitmap.GROUP_2);
		float[] ptr;

		ptr = m_c[2];
		ptr[0] = ptr[1] = ptr[2] = ptr[3] = ptr[4] = ptr[5] = ptr[6] = ptr[7] = ptr[8] = ptr[10] = ptr[11] = ptr[12] = 0.0f;
		ptr[9] = src.m_e12_e23;
		ptr[13] = -src.m_e31_e12;
		ptr[14] = src.m_e23_e31;
	}

	/**
	 * sets this to mixedPencil value.
	 */
	public void set(mixedPencil src) {
		allocateGroups(GroupBitmap.GROUP_2);
		float[] ptr;

		ptr = m_c[2];
		ptr[0] = ptr[1] = ptr[2] = ptr[9] = ptr[13] = ptr[14] = 0.0f;
		ptr[3] = src.m_e01_e12;
		ptr[4] = src.m_e02_e12;
		ptr[5] = src.m_e03_e12;
		ptr[6] = src.m_e01_e23;
		ptr[7] = src.m_e02_e23;
		ptr[8] = src.m_e03_e23;
		ptr[10] = src.m_e01_e31;
		ptr[11] = src.m_e02_e31;
		ptr[12] = src.m_e03_e31;
	}

	/**
	 * sets this to pseudoscalar value.
	 */
	public void set(pseudoscalar src) {
		allocateGroups(GroupBitmap.GROUP_6);
		float[] ptr;

		ptr = m_c[6];
		ptr[0] = src.m_e01_e02_e03_e12_e23_e31;
	}

	/**
	 * sets this to evenVersor value.
	 */
	public void set(evenVersor src) {
		allocateGroups(GroupBitmap.GROUP_0|GroupBitmap.GROUP_2|GroupBitmap.GROUP_4|GroupBitmap.GROUP_6);
		float[] ptr;

		ptr = m_c[0];
		ptr[0] = src.m_scalar;

		ptr = m_c[2];
		ptr[0] = src.m_e01_e02;
		ptr[1] = -src.m_e03_e01;
		ptr[2] = src.m_e02_e03;
		ptr[3] = src.m_e01_e12;
		ptr[4] = src.m_e02_e12;
		ptr[5] = src.m_e03_e12;
		ptr[6] = src.m_e01_e23;
		ptr[7] = src.m_e02_e23;
		ptr[8] = src.m_e03_e23;
		ptr[9] = src.m_e12_e23;
		ptr[10] = src.m_e01_e31;
		ptr[11] = src.m_e02_e31;
		ptr[12] = src.m_e03_e31;
		ptr[13] = -src.m_e31_e12;
		ptr[14] = src.m_e23_e31;

		ptr = m_c[4];
		ptr[0] = src.m_e01_e02_e03_e12;
		ptr[1] = src.m_e01_e02_e03_e23;
		ptr[2] = src.m_e01_e02_e12_e23;
		ptr[3] = src.m_e01_e03_e12_e23;
		ptr[4] = src.m_e02_e03_e12_e23;
		ptr[5] = src.m_e01_e02_e03_e31;
		ptr[6] = src.m_e01_e02_e12_e31;
		ptr[7] = src.m_e01_e03_e12_e31;
		ptr[8] = src.m_e02_e03_e12_e31;
		ptr[9] = src.m_e01_e02_e23_e31;
		ptr[10] = src.m_e01_e03_e23_e31;
		ptr[11] = src.m_e02_e03_e23_e31;
		ptr[12] = src.m_e01_e12_e23_e31;
		ptr[13] = src.m_e02_e12_e23_e31;
		ptr[14] = src.m_e03_e12_e23_e31;

		ptr = m_c[6];
		ptr[0] = src.m_e01_e02_e03_e12_e23_e31;
	}

	/**
	 * sets this to oddVersor value.
	 */
	public void set(oddVersor src) {
		allocateGroups(GroupBitmap.GROUP_1|GroupBitmap.GROUP_3|GroupBitmap.GROUP_5);
		float[] ptr;

		ptr = m_c[1];
		ptr[0] = src.m_e01;
		ptr[1] = src.m_e02;
		ptr[2] = src.m_e03;
		ptr[3] = src.m_e12;
		ptr[4] = src.m_e23;
		ptr[5] = src.m_e31;

		ptr = m_c[3];
		ptr[0] = src.m_e01_e02_e03;
		ptr[1] = src.m_e01_e02_e12;
		ptr[2] = src.m_e01_e03_e12;
		ptr[3] = src.m_e02_e03_e12;
		ptr[4] = src.m_e01_e02_e23;
		ptr[5] = src.m_e01_e03_e23;
		ptr[6] = src.m_e02_e03_e23;
		ptr[7] = src.m_e01_e12_e23;
		ptr[8] = src.m_e02_e12_e23;
		ptr[9] = src.m_e03_e12_e23;
		ptr[10] = src.m_e01_e02_e31;
		ptr[11] = src.m_e01_e03_e31;
		ptr[12] = src.m_e02_e03_e31;
		ptr[13] = src.m_e01_e12_e31;
		ptr[14] = src.m_e02_e12_e31;
		ptr[15] = src.m_e03_e12_e31;
		ptr[16] = src.m_e01_e23_e31;
		ptr[17] = src.m_e02_e23_e31;
		ptr[18] = src.m_e03_e23_e31;
		ptr[19] = src.m_e12_e23_e31;

		ptr = m_c[5];
		ptr[0] = src.m_e01_e02_e03_e12_e23;
		ptr[1] = src.m_e01_e02_e03_e12_e31;
		ptr[2] = src.m_e01_e02_e03_e23_e31;
		ptr[3] = src.m_e01_e02_e12_e23_e31;
		ptr[4] = src.m_e01_e03_e12_e23_e31;
		ptr[5] = src.m_e02_e03_e12_e23_e31;
	}
	/**
	 * Returns the scalar coordinate of this mv
	 */
	public final float get_scalar()  {
		return (m_c[0] == null) ? 0.0f: m_c[0][0];
	}
	/**
	 * Returns the e01 coordinate of this mv
	 */
	public final float get_e01()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][0];
	}
	/**
	 * Returns the e02 coordinate of this mv
	 */
	public final float get_e02()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][1];
	}
	/**
	 * Returns the e03 coordinate of this mv
	 */
	public final float get_e03()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][2];
	}
	/**
	 * Returns the e12 coordinate of this mv
	 */
	public final float get_e12()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][3];
	}
	/**
	 * Returns the e23 coordinate of this mv
	 */
	public final float get_e23()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][4];
	}
	/**
	 * Returns the e31 coordinate of this mv
	 */
	public final float get_e31()  {
		return (m_c[1] == null) ? 0.0f: m_c[1][5];
	}
	/**
	 * Returns the e01_e02 coordinate of this mv
	 */
	public final float get_e01_e02()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][0];
	}
	/**
	 * Returns the e01_e03 coordinate of this mv
	 */
	public final float get_e01_e03()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][1];
	}
	/**
	 * Returns the e02_e03 coordinate of this mv
	 */
	public final float get_e02_e03()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][2];
	}
	/**
	 * Returns the e01_e12 coordinate of this mv
	 */
	public final float get_e01_e12()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][3];
	}
	/**
	 * Returns the e02_e12 coordinate of this mv
	 */
	public final float get_e02_e12()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][4];
	}
	/**
	 * Returns the e03_e12 coordinate of this mv
	 */
	public final float get_e03_e12()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][5];
	}
	/**
	 * Returns the e01_e23 coordinate of this mv
	 */
	public final float get_e01_e23()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][6];
	}
	/**
	 * Returns the e02_e23 coordinate of this mv
	 */
	public final float get_e02_e23()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][7];
	}
	/**
	 * Returns the e03_e23 coordinate of this mv
	 */
	public final float get_e03_e23()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][8];
	}
	/**
	 * Returns the e12_e23 coordinate of this mv
	 */
	public final float get_e12_e23()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][9];
	}
	/**
	 * Returns the e01_e31 coordinate of this mv
	 */
	public final float get_e01_e31()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][10];
	}
	/**
	 * Returns the e02_e31 coordinate of this mv
	 */
	public final float get_e02_e31()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][11];
	}
	/**
	 * Returns the e03_e31 coordinate of this mv
	 */
	public final float get_e03_e31()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][12];
	}
	/**
	 * Returns the e12_e31 coordinate of this mv
	 */
	public final float get_e12_e31()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][13];
	}
	/**
	 * Returns the e23_e31 coordinate of this mv
	 */
	public final float get_e23_e31()  {
		return (m_c[2] == null) ? 0.0f: m_c[2][14];
	}
	/**
	 * Returns the e01_e02_e03 coordinate of this mv
	 */
	public final float get_e01_e02_e03()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][0];
	}
	/**
	 * Returns the e01_e02_e12 coordinate of this mv
	 */
	public final float get_e01_e02_e12()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][1];
	}
	/**
	 * Returns the e01_e03_e12 coordinate of this mv
	 */
	public final float get_e01_e03_e12()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][2];
	}
	/**
	 * Returns the e02_e03_e12 coordinate of this mv
	 */
	public final float get_e02_e03_e12()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][3];
	}
	/**
	 * Returns the e01_e02_e23 coordinate of this mv
	 */
	public final float get_e01_e02_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][4];
	}
	/**
	 * Returns the e01_e03_e23 coordinate of this mv
	 */
	public final float get_e01_e03_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][5];
	}
	/**
	 * Returns the e02_e03_e23 coordinate of this mv
	 */
	public final float get_e02_e03_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][6];
	}
	/**
	 * Returns the e01_e12_e23 coordinate of this mv
	 */
	public final float get_e01_e12_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][7];
	}
	/**
	 * Returns the e02_e12_e23 coordinate of this mv
	 */
	public final float get_e02_e12_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][8];
	}
	/**
	 * Returns the e03_e12_e23 coordinate of this mv
	 */
	public final float get_e03_e12_e23()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][9];
	}
	/**
	 * Returns the e01_e02_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][10];
	}
	/**
	 * Returns the e01_e03_e31 coordinate of this mv
	 */
	public final float get_e01_e03_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][11];
	}
	/**
	 * Returns the e02_e03_e31 coordinate of this mv
	 */
	public final float get_e02_e03_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][12];
	}
	/**
	 * Returns the e01_e12_e31 coordinate of this mv
	 */
	public final float get_e01_e12_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][13];
	}
	/**
	 * Returns the e02_e12_e31 coordinate of this mv
	 */
	public final float get_e02_e12_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][14];
	}
	/**
	 * Returns the e03_e12_e31 coordinate of this mv
	 */
	public final float get_e03_e12_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][15];
	}
	/**
	 * Returns the e01_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e23_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][16];
	}
	/**
	 * Returns the e02_e23_e31 coordinate of this mv
	 */
	public final float get_e02_e23_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][17];
	}
	/**
	 * Returns the e03_e23_e31 coordinate of this mv
	 */
	public final float get_e03_e23_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][18];
	}
	/**
	 * Returns the e12_e23_e31 coordinate of this mv
	 */
	public final float get_e12_e23_e31()  {
		return (m_c[3] == null) ? 0.0f: m_c[3][19];
	}
	/**
	 * Returns the e01_e02_e03_e12 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e12()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][0];
	}
	/**
	 * Returns the e01_e02_e03_e23 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e23()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][1];
	}
	/**
	 * Returns the e01_e02_e12_e23 coordinate of this mv
	 */
	public final float get_e01_e02_e12_e23()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][2];
	}
	/**
	 * Returns the e01_e03_e12_e23 coordinate of this mv
	 */
	public final float get_e01_e03_e12_e23()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][3];
	}
	/**
	 * Returns the e02_e03_e12_e23 coordinate of this mv
	 */
	public final float get_e02_e03_e12_e23()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][4];
	}
	/**
	 * Returns the e01_e02_e03_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][5];
	}
	/**
	 * Returns the e01_e02_e12_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e12_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][6];
	}
	/**
	 * Returns the e01_e03_e12_e31 coordinate of this mv
	 */
	public final float get_e01_e03_e12_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][7];
	}
	/**
	 * Returns the e02_e03_e12_e31 coordinate of this mv
	 */
	public final float get_e02_e03_e12_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][8];
	}
	/**
	 * Returns the e01_e02_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][9];
	}
	/**
	 * Returns the e01_e03_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e03_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][10];
	}
	/**
	 * Returns the e02_e03_e23_e31 coordinate of this mv
	 */
	public final float get_e02_e03_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][11];
	}
	/**
	 * Returns the e01_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e12_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][12];
	}
	/**
	 * Returns the e02_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e02_e12_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][13];
	}
	/**
	 * Returns the e03_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e03_e12_e23_e31()  {
		return (m_c[4] == null) ? 0.0f: m_c[4][14];
	}
	/**
	 * Returns the e01_e02_e03_e12_e23 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e12_e23()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][0];
	}
	/**
	 * Returns the e01_e02_e03_e12_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e12_e31()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][1];
	}
	/**
	 * Returns the e01_e02_e03_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e23_e31()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][2];
	}
	/**
	 * Returns the e01_e02_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e12_e23_e31()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][3];
	}
	/**
	 * Returns the e01_e03_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e03_e12_e23_e31()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][4];
	}
	/**
	 * Returns the e02_e03_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e02_e03_e12_e23_e31()  {
		return (m_c[5] == null) ? 0.0f: m_c[5][5];
	}
	/**
	 * Returns the e01_e02_e03_e12_e23_e31 coordinate of this mv
	 */
	public final float get_e01_e02_e03_e12_e23_e31()  {
		return (m_c[6] == null) ? 0.0f: m_c[6][0];
	}

	/** 
	 * Reserves memory for the groups specified by 'gu'.
	 * Keeps old memory (and values) when possible. 
	 */
	private final void allocateGroups(final int gu) {
		for (int i = 0; (1 << i) <= gu; i++) {
			if (((1 << i) & gu) != 0) {
				if (m_c[i] == null)
					m_c[i] = new float[pl3ga.MvSize[1 << i]];
			}
			else m_c[i] = null;
		}		
	}

	/**
	 *  Reserves memory for coordinate GROUP_0.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_0() {
		if (m_c[0] == null) {
			m_c[0] = new float[1];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_1.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_1() {
		if (m_c[1] == null) {
			m_c[1] = new float[6];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_2.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_2() {
		if (m_c[2] == null) {
			m_c[2] = new float[15];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_3.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_3() {
		if (m_c[3] == null) {
			m_c[3] = new float[20];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_4.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_4() {
		if (m_c[4] == null) {
			m_c[4] = new float[15];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_5.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_5() {
		if (m_c[5] == null) {
			m_c[5] = new float[6];
		}
	}
	/**
	 *  Reserves memory for coordinate GROUP_6.
	 *  If the group is already present, nothing changes.
	 *  If the group is not present, memory is allocated for the new group,
	 *  and the coordinates for the group are set to zero.
	 */
	private final void reserveGroup_6() {
		if (m_c[6] == null) {
			m_c[6] = new float[1];
		}
	}
	/// Sets the scalar coordinate of this mv.
	public final void set_scalar(float val)  {
		reserveGroup_0();
		m_c[0][0] =  val;
	}
	/// Sets the e01 coordinate of this mv.
	public final void set_e01(float val)  {
		reserveGroup_1();
		m_c[1][0] =  val;
	}
	/// Sets the e02 coordinate of this mv.
	public final void set_e02(float val)  {
		reserveGroup_1();
		m_c[1][1] =  val;
	}
	/// Sets the e03 coordinate of this mv.
	public final void set_e03(float val)  {
		reserveGroup_1();
		m_c[1][2] =  val;
	}
	/// Sets the e12 coordinate of this mv.
	public final void set_e12(float val)  {
		reserveGroup_1();
		m_c[1][3] =  val;
	}
	/// Sets the e23 coordinate of this mv.
	public final void set_e23(float val)  {
		reserveGroup_1();
		m_c[1][4] =  val;
	}
	/// Sets the e31 coordinate of this mv.
	public final void set_e31(float val)  {
		reserveGroup_1();
		m_c[1][5] =  val;
	}
	/// Sets the e01_e02 coordinate of this mv.
	public final void set_e01_e02(float val)  {
		reserveGroup_2();
		m_c[2][0] =  val;
	}
	/// Sets the e01_e03 coordinate of this mv.
	public final void set_e01_e03(float val)  {
		reserveGroup_2();
		m_c[2][1] =  val;
	}
	/// Sets the e02_e03 coordinate of this mv.
	public final void set_e02_e03(float val)  {
		reserveGroup_2();
		m_c[2][2] =  val;
	}
	/// Sets the e01_e12 coordinate of this mv.
	public final void set_e01_e12(float val)  {
		reserveGroup_2();
		m_c[2][3] =  val;
	}
	/// Sets the e02_e12 coordinate of this mv.
	public final void set_e02_e12(float val)  {
		reserveGroup_2();
		m_c[2][4] =  val;
	}
	/// Sets the e03_e12 coordinate of this mv.
	public final void set_e03_e12(float val)  {
		reserveGroup_2();
		m_c[2][5] =  val;
	}
	/// Sets the e01_e23 coordinate of this mv.
	public final void set_e01_e23(float val)  {
		reserveGroup_2();
		m_c[2][6] =  val;
	}
	/// Sets the e02_e23 coordinate of this mv.
	public final void set_e02_e23(float val)  {
		reserveGroup_2();
		m_c[2][7] =  val;
	}
	/// Sets the e03_e23 coordinate of this mv.
	public final void set_e03_e23(float val)  {
		reserveGroup_2();
		m_c[2][8] =  val;
	}
	/// Sets the e12_e23 coordinate of this mv.
	public final void set_e12_e23(float val)  {
		reserveGroup_2();
		m_c[2][9] =  val;
	}
	/// Sets the e01_e31 coordinate of this mv.
	public final void set_e01_e31(float val)  {
		reserveGroup_2();
		m_c[2][10] =  val;
	}
	/// Sets the e02_e31 coordinate of this mv.
	public final void set_e02_e31(float val)  {
		reserveGroup_2();
		m_c[2][11] =  val;
	}
	/// Sets the e03_e31 coordinate of this mv.
	public final void set_e03_e31(float val)  {
		reserveGroup_2();
		m_c[2][12] =  val;
	}
	/// Sets the e12_e31 coordinate of this mv.
	public final void set_e12_e31(float val)  {
		reserveGroup_2();
		m_c[2][13] =  val;
	}
	/// Sets the e23_e31 coordinate of this mv.
	public final void set_e23_e31(float val)  {
		reserveGroup_2();
		m_c[2][14] =  val;
	}
	/// Sets the e01_e02_e03 coordinate of this mv.
	public final void set_e01_e02_e03(float val)  {
		reserveGroup_3();
		m_c[3][0] =  val;
	}
	/// Sets the e01_e02_e12 coordinate of this mv.
	public final void set_e01_e02_e12(float val)  {
		reserveGroup_3();
		m_c[3][1] =  val;
	}
	/// Sets the e01_e03_e12 coordinate of this mv.
	public final void set_e01_e03_e12(float val)  {
		reserveGroup_3();
		m_c[3][2] =  val;
	}
	/// Sets the e02_e03_e12 coordinate of this mv.
	public final void set_e02_e03_e12(float val)  {
		reserveGroup_3();
		m_c[3][3] =  val;
	}
	/// Sets the e01_e02_e23 coordinate of this mv.
	public final void set_e01_e02_e23(float val)  {
		reserveGroup_3();
		m_c[3][4] =  val;
	}
	/// Sets the e01_e03_e23 coordinate of this mv.
	public final void set_e01_e03_e23(float val)  {
		reserveGroup_3();
		m_c[3][5] =  val;
	}
	/// Sets the e02_e03_e23 coordinate of this mv.
	public final void set_e02_e03_e23(float val)  {
		reserveGroup_3();
		m_c[3][6] =  val;
	}
	/// Sets the e01_e12_e23 coordinate of this mv.
	public final void set_e01_e12_e23(float val)  {
		reserveGroup_3();
		m_c[3][7] =  val;
	}
	/// Sets the e02_e12_e23 coordinate of this mv.
	public final void set_e02_e12_e23(float val)  {
		reserveGroup_3();
		m_c[3][8] =  val;
	}
	/// Sets the e03_e12_e23 coordinate of this mv.
	public final void set_e03_e12_e23(float val)  {
		reserveGroup_3();
		m_c[3][9] =  val;
	}
	/// Sets the e01_e02_e31 coordinate of this mv.
	public final void set_e01_e02_e31(float val)  {
		reserveGroup_3();
		m_c[3][10] =  val;
	}
	/// Sets the e01_e03_e31 coordinate of this mv.
	public final void set_e01_e03_e31(float val)  {
		reserveGroup_3();
		m_c[3][11] =  val;
	}
	/// Sets the e02_e03_e31 coordinate of this mv.
	public final void set_e02_e03_e31(float val)  {
		reserveGroup_3();
		m_c[3][12] =  val;
	}
	/// Sets the e01_e12_e31 coordinate of this mv.
	public final void set_e01_e12_e31(float val)  {
		reserveGroup_3();
		m_c[3][13] =  val;
	}
	/// Sets the e02_e12_e31 coordinate of this mv.
	public final void set_e02_e12_e31(float val)  {
		reserveGroup_3();
		m_c[3][14] =  val;
	}
	/// Sets the e03_e12_e31 coordinate of this mv.
	public final void set_e03_e12_e31(float val)  {
		reserveGroup_3();
		m_c[3][15] =  val;
	}
	/// Sets the e01_e23_e31 coordinate of this mv.
	public final void set_e01_e23_e31(float val)  {
		reserveGroup_3();
		m_c[3][16] =  val;
	}
	/// Sets the e02_e23_e31 coordinate of this mv.
	public final void set_e02_e23_e31(float val)  {
		reserveGroup_3();
		m_c[3][17] =  val;
	}
	/// Sets the e03_e23_e31 coordinate of this mv.
	public final void set_e03_e23_e31(float val)  {
		reserveGroup_3();
		m_c[3][18] =  val;
	}
	/// Sets the e12_e23_e31 coordinate of this mv.
	public final void set_e12_e23_e31(float val)  {
		reserveGroup_3();
		m_c[3][19] =  val;
	}
	/// Sets the e01_e02_e03_e12 coordinate of this mv.
	public final void set_e01_e02_e03_e12(float val)  {
		reserveGroup_4();
		m_c[4][0] =  val;
	}
	/// Sets the e01_e02_e03_e23 coordinate of this mv.
	public final void set_e01_e02_e03_e23(float val)  {
		reserveGroup_4();
		m_c[4][1] =  val;
	}
	/// Sets the e01_e02_e12_e23 coordinate of this mv.
	public final void set_e01_e02_e12_e23(float val)  {
		reserveGroup_4();
		m_c[4][2] =  val;
	}
	/// Sets the e01_e03_e12_e23 coordinate of this mv.
	public final void set_e01_e03_e12_e23(float val)  {
		reserveGroup_4();
		m_c[4][3] =  val;
	}
	/// Sets the e02_e03_e12_e23 coordinate of this mv.
	public final void set_e02_e03_e12_e23(float val)  {
		reserveGroup_4();
		m_c[4][4] =  val;
	}
	/// Sets the e01_e02_e03_e31 coordinate of this mv.
	public final void set_e01_e02_e03_e31(float val)  {
		reserveGroup_4();
		m_c[4][5] =  val;
	}
	/// Sets the e01_e02_e12_e31 coordinate of this mv.
	public final void set_e01_e02_e12_e31(float val)  {
		reserveGroup_4();
		m_c[4][6] =  val;
	}
	/// Sets the e01_e03_e12_e31 coordinate of this mv.
	public final void set_e01_e03_e12_e31(float val)  {
		reserveGroup_4();
		m_c[4][7] =  val;
	}
	/// Sets the e02_e03_e12_e31 coordinate of this mv.
	public final void set_e02_e03_e12_e31(float val)  {
		reserveGroup_4();
		m_c[4][8] =  val;
	}
	/// Sets the e01_e02_e23_e31 coordinate of this mv.
	public final void set_e01_e02_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][9] =  val;
	}
	/// Sets the e01_e03_e23_e31 coordinate of this mv.
	public final void set_e01_e03_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][10] =  val;
	}
	/// Sets the e02_e03_e23_e31 coordinate of this mv.
	public final void set_e02_e03_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][11] =  val;
	}
	/// Sets the e01_e12_e23_e31 coordinate of this mv.
	public final void set_e01_e12_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][12] =  val;
	}
	/// Sets the e02_e12_e23_e31 coordinate of this mv.
	public final void set_e02_e12_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][13] =  val;
	}
	/// Sets the e03_e12_e23_e31 coordinate of this mv.
	public final void set_e03_e12_e23_e31(float val)  {
		reserveGroup_4();
		m_c[4][14] =  val;
	}
	/// Sets the e01_e02_e03_e12_e23 coordinate of this mv.
	public final void set_e01_e02_e03_e12_e23(float val)  {
		reserveGroup_5();
		m_c[5][0] =  val;
	}
	/// Sets the e01_e02_e03_e12_e31 coordinate of this mv.
	public final void set_e01_e02_e03_e12_e31(float val)  {
		reserveGroup_5();
		m_c[5][1] =  val;
	}
	/// Sets the e01_e02_e03_e23_e31 coordinate of this mv.
	public final void set_e01_e02_e03_e23_e31(float val)  {
		reserveGroup_5();
		m_c[5][2] =  val;
	}
	/// Sets the e01_e02_e12_e23_e31 coordinate of this mv.
	public final void set_e01_e02_e12_e23_e31(float val)  {
		reserveGroup_5();
		m_c[5][3] =  val;
	}
	/// Sets the e01_e03_e12_e23_e31 coordinate of this mv.
	public final void set_e01_e03_e12_e23_e31(float val)  {
		reserveGroup_5();
		m_c[5][4] =  val;
	}
	/// Sets the e02_e03_e12_e23_e31 coordinate of this mv.
	public final void set_e02_e03_e12_e23_e31(float val)  {
		reserveGroup_5();
		m_c[5][5] =  val;
	}
	/// Sets the e01_e02_e03_e12_e23_e31 coordinate of this mv.
	public final void set_e01_e02_e03_e12_e23_e31(float val)  {
		reserveGroup_6();
		m_c[6][0] =  val;
	}

	/** returns the absolute largest coordinate.*/
	public float largestCoordinate() {
		float maxValue = 0.0f, C;
		for (int g = 0; g < m_c.length; g++) {
			if (m_c[g] != null) {
				float[] Cg = m_c[g];
				for (int b = 0; b < Cg.length; b++) {
					C = Math.abs(Cg[b]);
					if (C > maxValue) {
						maxValue = C;
					}
				}
			}
		}
		return maxValue;
	}
	
	/** returns the absolute largest coordinate (entry [0]), and the corresponding basis blade bitmap (entry [1])  */
	public float[] largestBasisBlade() {
		float maxC = -1.0f, C;

		int idx = 0; // global index into coordinates (run from 0 to 64).
		int bm; // bitmap of basis blade
		bm = 0;
		
		for (int g = 0; g < m_c.length; g++) {
			if (m_c[g] != null) {
				float[] Cg = m_c[g];
				for (int b = 0; b < m_c[g].length; b++) {
					C = Math.abs(Cg[b]);
					if (C > maxC) {
						maxC = C;
						bm = pl3ga.BasisElementBitmapByIndex[idx];
					}
					idx++;
				}
			
			}
			else idx += pl3ga.GroupSize[g];
		}

		return new float[]{maxC, (float)bm};
	} // end of largestBasisBlade()
	
	/**
	 * Releases memory for (near-)zero groups/grades.
	 * This also speeds up subsequent operations, because those do not have to process the released groups/grades anymore.
	 * @param eps A positive threshold value.
	 * Coordinates which are smaller than epsilon are considered to be zero.
	 */
	public final void compress(float eps)  {
		if ((m_c[0] != null) && pl3ga.zeroGroup_0(m_c[0], eps))
			m_c[0] = null;
		if ((m_c[1] != null) && pl3ga.zeroGroup_1(m_c[1], eps))
			m_c[1] = null;
		if ((m_c[2] != null) && pl3ga.zeroGroup_2(m_c[2], eps))
			m_c[2] = null;
		if ((m_c[3] != null) && pl3ga.zeroGroup_3(m_c[3], eps))
			m_c[3] = null;
		if ((m_c[4] != null) && pl3ga.zeroGroup_4(m_c[4], eps))
			m_c[4] = null;
		if ((m_c[5] != null) && pl3ga.zeroGroup_5(m_c[5], eps))
			m_c[5] = null;
		if ((m_c[6] != null) && pl3ga.zeroGroup_6(m_c[6], eps))
			m_c[6] = null;
	}

	/**
	 * Returns this multivector, converted to a string.
	 * The floating point formatter is controlled via pl3ga.setStringFormat().
	 */
	public final String toString() {
		return pl3ga.string(this);
	}
	
	/**
	 * Returns this multivector, converted to a string.
	 * The floating point formatter is "%f".
	 */
	public final String toString_f() {
		return toString("%f");
	}
	
	/**
	 * Returns this multivector, converted to a string.
	 * The floating point formatter is "%e".
	 */
	public final String toString_e() {
		return toString("%e");
	}
	
	/**
	 * Returns this multivector, converted to a string.
	 * The floating point formatter is "%2.20e".
	 */
	public final String toString_e20() {
		return toString("%2.20e");
	}
	
	/**
	 * Returns this multivector, converted to a string.
	 * @param fp floating point format. Use 'null' for the default format (see pl3ga.setStringFormat()).
	 */
	public final String toString(final String fp) {
		return pl3ga.string(this, fp);
	}

	public final mv to_mv() {
		return this;
	}
} // end of class mv
