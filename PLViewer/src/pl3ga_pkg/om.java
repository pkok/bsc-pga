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
 * This class can hold a general outermorphism.
 * 
 * The coordinates are stored in type float.
 * 
 * There are 7 matrices, one for each grade.
 * The columns of these matrices are the range of the outermorphism.
 * Matrices are stored in row-major order. So the coordinates of rows are stored contiguously.
 * Domain grade 1: e01, e02, e03, e12, e23, e31.
 * Domain grade 2: e01^e02, e01^e03, e02^e03, e01^e12, e02^e12, e03^e12, e01^e23, e02^e23, e03^e23, e12^e23, e01^e31, e02^e31, e03^e31, e12^e31, e23^e31.
 * Domain grade 3: e01^e02^e03, e01^e02^e12, e01^e03^e12, e02^e03^e12, e01^e02^e23, e01^e03^e23, e02^e03^e23, e01^e12^e23, e02^e12^e23, e03^e12^e23, e01^e02^e31, e01^e03^e31, e02^e03^e31, e01^e12^e31, e02^e12^e31, e03^e12^e31, e01^e23^e31, e02^e23^e31, e03^e23^e31, e12^e23^e31.
 * Domain grade 4: e01^e02^e03^e12, e01^e02^e03^e23, e01^e02^e12^e23, e01^e03^e12^e23, e02^e03^e12^e23, e01^e02^e03^e31, e01^e02^e12^e31, e01^e03^e12^e31, e02^e03^e12^e31, e01^e02^e23^e31, e01^e03^e23^e31, e02^e03^e23^e31, e01^e12^e23^e31, e02^e12^e23^e31, e03^e12^e23^e31.
 * Domain grade 5: e01^e02^e03^e12^e23, e01^e02^e03^e12^e31, e01^e02^e03^e23^e31, e01^e02^e12^e23^e31, e01^e03^e12^e23^e31, e02^e03^e12^e23^e31.
 * Domain grade 6: e01^e02^e03^e12^e23^e31.
 * 
 * The range and domain are equal.
 * 
 */
public class om 
{ 
	/**
	 * Matrix for grade 1; the size is 6 x 6
	 */
	protected float[] m_m1 = new float[36];
	/**
	 * Matrix for grade 2; the size is 15 x 15
	 */
	protected float[] m_m2 = new float[225];
	/**
	 * Matrix for grade 3; the size is 20 x 20
	 */
	protected float[] m_m3 = new float[400];
	/**
	 * Matrix for grade 4; the size is 15 x 15
	 */
	protected float[] m_m4 = new float[225];
	/**
	 * Matrix for grade 5; the size is 6 x 6
	 */
	protected float[] m_m5 = new float[36];
	/**
	 * Matrix for grade 6; the size is 1 x 1
	 */
	protected float[] m_m6 = new float[1];

	/** Constructs a new om, set to identity. */
	public om() { setIdentity(); }

	/** Copy constructor. */
	public om(final om M) { set(M); }

	/** Constructor from matrix. */
	public om(final float[] M) { set(M); }

	/** Constructor from images of basis vectors. */
	public om(final  oddVersor ie01,  oddVersor ie02,  oddVersor ie03,  oddVersor ie12,  oddVersor ie23,  oddVersor ie31)
		{ set(ie01, ie02, ie03, ie12, ie23, ie31); }


	public final void setIdentity() {
		pl3ga.zero_N(m_m1, 36);

		pl3ga.zero_N(m_m2, 225);

		pl3ga.zero_N(m_m3, 400);

		pl3ga.zero_N(m_m4, 225);

		pl3ga.zero_N(m_m5, 36);

		pl3ga.zero_1(m_m6);

		m_m1[0] = m_m1[7] = m_m1[14] = m_m1[21] = m_m1[28] = m_m1[35] = m_m2[0] = m_m2[16] = 
			m_m2[32] = m_m2[48] = m_m2[64] = m_m2[80] = m_m2[96] = m_m2[112] = m_m2[128] = m_m2[144] = 
			m_m2[160] = m_m2[176] = m_m2[192] = m_m2[208] = m_m2[224] = m_m3[0] = m_m3[21] = m_m3[42] = 
			m_m3[63] = m_m3[84] = m_m3[105] = m_m3[126] = m_m3[147] = m_m3[168] = m_m3[189] = m_m3[210] = 
			m_m3[231] = m_m3[252] = m_m3[273] = m_m3[294] = m_m3[315] = m_m3[336] = m_m3[357] = m_m3[378] = 
			m_m3[399] = m_m4[0] = m_m4[16] = m_m4[32] = m_m4[48] = m_m4[64] = m_m4[80] = m_m4[96] = 
			m_m4[112] = m_m4[128] = m_m4[144] = m_m4[160] = m_m4[176] = m_m4[192] = m_m4[208] = m_m4[224] = 
			m_m5[0] = m_m5[7] = m_m5[14] = m_m5[21] = m_m5[28] = m_m5[35] = m_m6[0] = 1.0f;
	}

	void set(om src) {
		pl3ga.copy_N(m_m1, src.m_m1, 36);

		pl3ga.copy_N(m_m2, src.m_m2, 225);

		pl3ga.copy_N(m_m3, src.m_m3, 400);

		pl3ga.copy_N(m_m4, src.m_m4, 225);

		pl3ga.copy_N(m_m5, src.m_m5, 36);

		pl3ga.copy_1(m_m6, src.m_m6);

	}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_0()
{
	m_m2[0] = (m_m1[0]*m_m1[7]-m_m1[1]*m_m1[6]);
	m_m2[15] = (m_m1[0]*m_m1[13]-m_m1[1]*m_m1[12]);
	m_m2[30] = (-m_m1[12]*m_m1[7]+m_m1[13]*m_m1[6]);
	m_m2[45] = (m_m1[0]*m_m1[19]-m_m1[1]*m_m1[18]);
	m_m2[60] = (-m_m1[18]*m_m1[7]+m_m1[19]*m_m1[6]);
	m_m2[75] = (m_m1[12]*m_m1[19]-m_m1[13]*m_m1[18]);
	m_m2[90] = (m_m1[0]*m_m1[25]-m_m1[1]*m_m1[24]);
	m_m2[105] = (-m_m1[24]*m_m1[7]+m_m1[25]*m_m1[6]);
	m_m2[120] = (m_m1[12]*m_m1[25]-m_m1[13]*m_m1[24]);
	m_m2[135] = (m_m1[18]*m_m1[25]-m_m1[19]*m_m1[24]);
	m_m2[150] = (m_m1[0]*m_m1[31]-m_m1[1]*m_m1[30]);
	m_m2[165] = (-m_m1[30]*m_m1[7]+m_m1[31]*m_m1[6]);
	m_m2[180] = (m_m1[12]*m_m1[31]-m_m1[13]*m_m1[30]);
	m_m2[195] = (m_m1[18]*m_m1[31]-m_m1[19]*m_m1[30]);
	m_m2[210] = (m_m1[24]*m_m1[31]-m_m1[25]*m_m1[30]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_1()
{
	m_m2[1] = (m_m1[0]*m_m1[8]-m_m1[2]*m_m1[6]);
	m_m2[16] = (m_m1[0]*m_m1[14]-m_m1[12]*m_m1[2]);
	m_m2[31] = (-m_m1[12]*m_m1[8]+m_m1[14]*m_m1[6]);
	m_m2[46] = (m_m1[0]*m_m1[20]-m_m1[18]*m_m1[2]);
	m_m2[61] = (-m_m1[18]*m_m1[8]+m_m1[20]*m_m1[6]);
	m_m2[76] = (m_m1[12]*m_m1[20]-m_m1[14]*m_m1[18]);
	m_m2[91] = (m_m1[0]*m_m1[26]-m_m1[2]*m_m1[24]);
	m_m2[106] = (-m_m1[24]*m_m1[8]+m_m1[26]*m_m1[6]);
	m_m2[121] = (m_m1[12]*m_m1[26]-m_m1[14]*m_m1[24]);
	m_m2[136] = (m_m1[18]*m_m1[26]-m_m1[20]*m_m1[24]);
	m_m2[151] = (m_m1[0]*m_m1[32]-m_m1[2]*m_m1[30]);
	m_m2[166] = (-m_m1[30]*m_m1[8]+m_m1[32]*m_m1[6]);
	m_m2[181] = (m_m1[12]*m_m1[32]-m_m1[14]*m_m1[30]);
	m_m2[196] = (m_m1[18]*m_m1[32]-m_m1[20]*m_m1[30]);
	m_m2[211] = (m_m1[24]*m_m1[32]-m_m1[26]*m_m1[30]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_2()
{
	m_m2[2] = (m_m1[1]*m_m1[8]-m_m1[2]*m_m1[7]);
	m_m2[17] = (m_m1[1]*m_m1[14]-m_m1[13]*m_m1[2]);
	m_m2[32] = (-m_m1[13]*m_m1[8]+m_m1[14]*m_m1[7]);
	m_m2[47] = (m_m1[1]*m_m1[20]-m_m1[19]*m_m1[2]);
	m_m2[62] = (-m_m1[19]*m_m1[8]+m_m1[20]*m_m1[7]);
	m_m2[77] = (m_m1[13]*m_m1[20]-m_m1[14]*m_m1[19]);
	m_m2[92] = (m_m1[1]*m_m1[26]-m_m1[2]*m_m1[25]);
	m_m2[107] = (-m_m1[25]*m_m1[8]+m_m1[26]*m_m1[7]);
	m_m2[122] = (m_m1[13]*m_m1[26]-m_m1[14]*m_m1[25]);
	m_m2[137] = (m_m1[19]*m_m1[26]-m_m1[20]*m_m1[25]);
	m_m2[152] = (m_m1[1]*m_m1[32]-m_m1[2]*m_m1[31]);
	m_m2[167] = (-m_m1[31]*m_m1[8]+m_m1[32]*m_m1[7]);
	m_m2[182] = (m_m1[13]*m_m1[32]-m_m1[14]*m_m1[31]);
	m_m2[197] = (m_m1[19]*m_m1[32]-m_m1[20]*m_m1[31]);
	m_m2[212] = (m_m1[25]*m_m1[32]-m_m1[26]*m_m1[31]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_3()
{
	m_m2[3] = (m_m1[0]*m_m1[9]-m_m1[3]*m_m1[6]);
	m_m2[18] = (m_m1[0]*m_m1[15]-m_m1[12]*m_m1[3]);
	m_m2[33] = (-m_m1[12]*m_m1[9]+m_m1[15]*m_m1[6]);
	m_m2[48] = (m_m1[0]*m_m1[21]-m_m1[18]*m_m1[3]);
	m_m2[63] = (-m_m1[18]*m_m1[9]+m_m1[21]*m_m1[6]);
	m_m2[78] = (m_m1[12]*m_m1[21]-m_m1[15]*m_m1[18]);
	m_m2[93] = (m_m1[0]*m_m1[27]-m_m1[24]*m_m1[3]);
	m_m2[108] = (-m_m1[24]*m_m1[9]+m_m1[27]*m_m1[6]);
	m_m2[123] = (m_m1[12]*m_m1[27]-m_m1[15]*m_m1[24]);
	m_m2[138] = (m_m1[18]*m_m1[27]-m_m1[21]*m_m1[24]);
	m_m2[153] = (m_m1[0]*m_m1[33]-m_m1[3]*m_m1[30]);
	m_m2[168] = (-m_m1[30]*m_m1[9]+m_m1[33]*m_m1[6]);
	m_m2[183] = (m_m1[12]*m_m1[33]-m_m1[15]*m_m1[30]);
	m_m2[198] = (m_m1[18]*m_m1[33]-m_m1[21]*m_m1[30]);
	m_m2[213] = (m_m1[24]*m_m1[33]-m_m1[27]*m_m1[30]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_4()
{
	m_m2[4] = (m_m1[1]*m_m1[9]-m_m1[3]*m_m1[7]);
	m_m2[19] = (m_m1[1]*m_m1[15]-m_m1[13]*m_m1[3]);
	m_m2[34] = (-m_m1[13]*m_m1[9]+m_m1[15]*m_m1[7]);
	m_m2[49] = (m_m1[1]*m_m1[21]-m_m1[19]*m_m1[3]);
	m_m2[64] = (-m_m1[19]*m_m1[9]+m_m1[21]*m_m1[7]);
	m_m2[79] = (m_m1[13]*m_m1[21]-m_m1[15]*m_m1[19]);
	m_m2[94] = (m_m1[1]*m_m1[27]-m_m1[25]*m_m1[3]);
	m_m2[109] = (-m_m1[25]*m_m1[9]+m_m1[27]*m_m1[7]);
	m_m2[124] = (m_m1[13]*m_m1[27]-m_m1[15]*m_m1[25]);
	m_m2[139] = (m_m1[19]*m_m1[27]-m_m1[21]*m_m1[25]);
	m_m2[154] = (m_m1[1]*m_m1[33]-m_m1[3]*m_m1[31]);
	m_m2[169] = (-m_m1[31]*m_m1[9]+m_m1[33]*m_m1[7]);
	m_m2[184] = (m_m1[13]*m_m1[33]-m_m1[15]*m_m1[31]);
	m_m2[199] = (m_m1[19]*m_m1[33]-m_m1[21]*m_m1[31]);
	m_m2[214] = (m_m1[25]*m_m1[33]-m_m1[27]*m_m1[31]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_5()
{
	m_m2[5] = (m_m1[2]*m_m1[9]-m_m1[3]*m_m1[8]);
	m_m2[20] = (-m_m1[14]*m_m1[3]+m_m1[15]*m_m1[2]);
	m_m2[35] = (-m_m1[14]*m_m1[9]+m_m1[15]*m_m1[8]);
	m_m2[50] = (m_m1[2]*m_m1[21]-m_m1[20]*m_m1[3]);
	m_m2[65] = (-m_m1[20]*m_m1[9]+m_m1[21]*m_m1[8]);
	m_m2[80] = (m_m1[14]*m_m1[21]-m_m1[15]*m_m1[20]);
	m_m2[95] = (m_m1[2]*m_m1[27]-m_m1[26]*m_m1[3]);
	m_m2[110] = (-m_m1[26]*m_m1[9]+m_m1[27]*m_m1[8]);
	m_m2[125] = (m_m1[14]*m_m1[27]-m_m1[15]*m_m1[26]);
	m_m2[140] = (m_m1[20]*m_m1[27]-m_m1[21]*m_m1[26]);
	m_m2[155] = (m_m1[2]*m_m1[33]-m_m1[3]*m_m1[32]);
	m_m2[170] = (-m_m1[32]*m_m1[9]+m_m1[33]*m_m1[8]);
	m_m2[185] = (m_m1[14]*m_m1[33]-m_m1[15]*m_m1[32]);
	m_m2[200] = (m_m1[20]*m_m1[33]-m_m1[21]*m_m1[32]);
	m_m2[215] = (m_m1[26]*m_m1[33]-m_m1[27]*m_m1[32]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_6()
{
	m_m2[6] = (m_m1[0]*m_m1[10]-m_m1[4]*m_m1[6]);
	m_m2[21] = (m_m1[0]*m_m1[16]-m_m1[12]*m_m1[4]);
	m_m2[36] = (-m_m1[10]*m_m1[12]+m_m1[16]*m_m1[6]);
	m_m2[51] = (m_m1[0]*m_m1[22]-m_m1[18]*m_m1[4]);
	m_m2[66] = (-m_m1[10]*m_m1[18]+m_m1[22]*m_m1[6]);
	m_m2[81] = (m_m1[12]*m_m1[22]-m_m1[16]*m_m1[18]);
	m_m2[96] = (m_m1[0]*m_m1[28]-m_m1[24]*m_m1[4]);
	m_m2[111] = (-m_m1[10]*m_m1[24]+m_m1[28]*m_m1[6]);
	m_m2[126] = (m_m1[12]*m_m1[28]-m_m1[16]*m_m1[24]);
	m_m2[141] = (m_m1[18]*m_m1[28]-m_m1[22]*m_m1[24]);
	m_m2[156] = (m_m1[0]*m_m1[34]-m_m1[30]*m_m1[4]);
	m_m2[171] = (-m_m1[10]*m_m1[30]+m_m1[34]*m_m1[6]);
	m_m2[186] = (m_m1[12]*m_m1[34]-m_m1[16]*m_m1[30]);
	m_m2[201] = (m_m1[18]*m_m1[34]-m_m1[22]*m_m1[30]);
	m_m2[216] = (m_m1[24]*m_m1[34]-m_m1[28]*m_m1[30]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_7()
{
	m_m2[7] = (m_m1[1]*m_m1[10]-m_m1[4]*m_m1[7]);
	m_m2[22] = (m_m1[1]*m_m1[16]-m_m1[13]*m_m1[4]);
	m_m2[37] = (-m_m1[10]*m_m1[13]+m_m1[16]*m_m1[7]);
	m_m2[52] = (m_m1[1]*m_m1[22]-m_m1[19]*m_m1[4]);
	m_m2[67] = (-m_m1[10]*m_m1[19]+m_m1[22]*m_m1[7]);
	m_m2[82] = (m_m1[13]*m_m1[22]-m_m1[16]*m_m1[19]);
	m_m2[97] = (m_m1[1]*m_m1[28]-m_m1[25]*m_m1[4]);
	m_m2[112] = (-m_m1[10]*m_m1[25]+m_m1[28]*m_m1[7]);
	m_m2[127] = (m_m1[13]*m_m1[28]-m_m1[16]*m_m1[25]);
	m_m2[142] = (m_m1[19]*m_m1[28]-m_m1[22]*m_m1[25]);
	m_m2[157] = (m_m1[1]*m_m1[34]-m_m1[31]*m_m1[4]);
	m_m2[172] = (-m_m1[10]*m_m1[31]+m_m1[34]*m_m1[7]);
	m_m2[187] = (m_m1[13]*m_m1[34]-m_m1[16]*m_m1[31]);
	m_m2[202] = (m_m1[19]*m_m1[34]-m_m1[22]*m_m1[31]);
	m_m2[217] = (m_m1[25]*m_m1[34]-m_m1[28]*m_m1[31]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_8()
{
	m_m2[8] = (m_m1[10]*m_m1[2]-m_m1[4]*m_m1[8]);
	m_m2[23] = (-m_m1[14]*m_m1[4]+m_m1[16]*m_m1[2]);
	m_m2[38] = (-m_m1[10]*m_m1[14]+m_m1[16]*m_m1[8]);
	m_m2[53] = (m_m1[2]*m_m1[22]-m_m1[20]*m_m1[4]);
	m_m2[68] = (-m_m1[10]*m_m1[20]+m_m1[22]*m_m1[8]);
	m_m2[83] = (m_m1[14]*m_m1[22]-m_m1[16]*m_m1[20]);
	m_m2[98] = (m_m1[2]*m_m1[28]-m_m1[26]*m_m1[4]);
	m_m2[113] = (-m_m1[10]*m_m1[26]+m_m1[28]*m_m1[8]);
	m_m2[128] = (m_m1[14]*m_m1[28]-m_m1[16]*m_m1[26]);
	m_m2[143] = (m_m1[20]*m_m1[28]-m_m1[22]*m_m1[26]);
	m_m2[158] = (m_m1[2]*m_m1[34]-m_m1[32]*m_m1[4]);
	m_m2[173] = (-m_m1[10]*m_m1[32]+m_m1[34]*m_m1[8]);
	m_m2[188] = (m_m1[14]*m_m1[34]-m_m1[16]*m_m1[32]);
	m_m2[203] = (m_m1[20]*m_m1[34]-m_m1[22]*m_m1[32]);
	m_m2[218] = (m_m1[26]*m_m1[34]-m_m1[28]*m_m1[32]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_9()
{
	m_m2[9] = (m_m1[10]*m_m1[3]-m_m1[4]*m_m1[9]);
	m_m2[24] = (-m_m1[15]*m_m1[4]+m_m1[16]*m_m1[3]);
	m_m2[39] = (-m_m1[10]*m_m1[15]+m_m1[16]*m_m1[9]);
	m_m2[54] = (-m_m1[21]*m_m1[4]+m_m1[22]*m_m1[3]);
	m_m2[69] = (-m_m1[10]*m_m1[21]+m_m1[22]*m_m1[9]);
	m_m2[84] = (m_m1[15]*m_m1[22]-m_m1[16]*m_m1[21]);
	m_m2[99] = (-m_m1[27]*m_m1[4]+m_m1[28]*m_m1[3]);
	m_m2[114] = (-m_m1[10]*m_m1[27]+m_m1[28]*m_m1[9]);
	m_m2[129] = (m_m1[15]*m_m1[28]-m_m1[16]*m_m1[27]);
	m_m2[144] = (m_m1[21]*m_m1[28]-m_m1[22]*m_m1[27]);
	m_m2[159] = (m_m1[3]*m_m1[34]-m_m1[33]*m_m1[4]);
	m_m2[174] = (-m_m1[10]*m_m1[33]+m_m1[34]*m_m1[9]);
	m_m2[189] = (m_m1[15]*m_m1[34]-m_m1[16]*m_m1[33]);
	m_m2[204] = (m_m1[21]*m_m1[34]-m_m1[22]*m_m1[33]);
	m_m2[219] = (m_m1[27]*m_m1[34]-m_m1[28]*m_m1[33]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_10()
{
	m_m2[10] = (m_m1[0]*m_m1[11]-m_m1[5]*m_m1[6]);
	m_m2[25] = (m_m1[0]*m_m1[17]-m_m1[12]*m_m1[5]);
	m_m2[40] = (-m_m1[11]*m_m1[12]+m_m1[17]*m_m1[6]);
	m_m2[55] = (m_m1[0]*m_m1[23]-m_m1[18]*m_m1[5]);
	m_m2[70] = (-m_m1[11]*m_m1[18]+m_m1[23]*m_m1[6]);
	m_m2[85] = (m_m1[12]*m_m1[23]-m_m1[17]*m_m1[18]);
	m_m2[100] = (m_m1[0]*m_m1[29]-m_m1[24]*m_m1[5]);
	m_m2[115] = (-m_m1[11]*m_m1[24]+m_m1[29]*m_m1[6]);
	m_m2[130] = (m_m1[12]*m_m1[29]-m_m1[17]*m_m1[24]);
	m_m2[145] = (m_m1[18]*m_m1[29]-m_m1[23]*m_m1[24]);
	m_m2[160] = (m_m1[0]*m_m1[35]-m_m1[30]*m_m1[5]);
	m_m2[175] = (-m_m1[11]*m_m1[30]+m_m1[35]*m_m1[6]);
	m_m2[190] = (m_m1[12]*m_m1[35]-m_m1[17]*m_m1[30]);
	m_m2[205] = (m_m1[18]*m_m1[35]-m_m1[23]*m_m1[30]);
	m_m2[220] = (m_m1[24]*m_m1[35]-m_m1[29]*m_m1[30]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_11()
{
	m_m2[11] = (m_m1[1]*m_m1[11]-m_m1[5]*m_m1[7]);
	m_m2[26] = (m_m1[1]*m_m1[17]-m_m1[13]*m_m1[5]);
	m_m2[41] = (-m_m1[11]*m_m1[13]+m_m1[17]*m_m1[7]);
	m_m2[56] = (m_m1[1]*m_m1[23]-m_m1[19]*m_m1[5]);
	m_m2[71] = (-m_m1[11]*m_m1[19]+m_m1[23]*m_m1[7]);
	m_m2[86] = (m_m1[13]*m_m1[23]-m_m1[17]*m_m1[19]);
	m_m2[101] = (m_m1[1]*m_m1[29]-m_m1[25]*m_m1[5]);
	m_m2[116] = (-m_m1[11]*m_m1[25]+m_m1[29]*m_m1[7]);
	m_m2[131] = (m_m1[13]*m_m1[29]-m_m1[17]*m_m1[25]);
	m_m2[146] = (m_m1[19]*m_m1[29]-m_m1[23]*m_m1[25]);
	m_m2[161] = (m_m1[1]*m_m1[35]-m_m1[31]*m_m1[5]);
	m_m2[176] = (-m_m1[11]*m_m1[31]+m_m1[35]*m_m1[7]);
	m_m2[191] = (m_m1[13]*m_m1[35]-m_m1[17]*m_m1[31]);
	m_m2[206] = (m_m1[19]*m_m1[35]-m_m1[23]*m_m1[31]);
	m_m2[221] = (m_m1[25]*m_m1[35]-m_m1[29]*m_m1[31]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_12()
{
	m_m2[12] = (m_m1[11]*m_m1[2]-m_m1[5]*m_m1[8]);
	m_m2[27] = (-m_m1[14]*m_m1[5]+m_m1[17]*m_m1[2]);
	m_m2[42] = (-m_m1[11]*m_m1[14]+m_m1[17]*m_m1[8]);
	m_m2[57] = (m_m1[2]*m_m1[23]-m_m1[20]*m_m1[5]);
	m_m2[72] = (-m_m1[11]*m_m1[20]+m_m1[23]*m_m1[8]);
	m_m2[87] = (m_m1[14]*m_m1[23]-m_m1[17]*m_m1[20]);
	m_m2[102] = (m_m1[2]*m_m1[29]-m_m1[26]*m_m1[5]);
	m_m2[117] = (-m_m1[11]*m_m1[26]+m_m1[29]*m_m1[8]);
	m_m2[132] = (m_m1[14]*m_m1[29]-m_m1[17]*m_m1[26]);
	m_m2[147] = (m_m1[20]*m_m1[29]-m_m1[23]*m_m1[26]);
	m_m2[162] = (m_m1[2]*m_m1[35]-m_m1[32]*m_m1[5]);
	m_m2[177] = (-m_m1[11]*m_m1[32]+m_m1[35]*m_m1[8]);
	m_m2[192] = (m_m1[14]*m_m1[35]-m_m1[17]*m_m1[32]);
	m_m2[207] = (m_m1[20]*m_m1[35]-m_m1[23]*m_m1[32]);
	m_m2[222] = (m_m1[26]*m_m1[35]-m_m1[29]*m_m1[32]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_13()
{
	m_m2[13] = (m_m1[11]*m_m1[3]-m_m1[5]*m_m1[9]);
	m_m2[28] = (-m_m1[15]*m_m1[5]+m_m1[17]*m_m1[3]);
	m_m2[43] = (-m_m1[11]*m_m1[15]+m_m1[17]*m_m1[9]);
	m_m2[58] = (-m_m1[21]*m_m1[5]+m_m1[23]*m_m1[3]);
	m_m2[73] = (-m_m1[11]*m_m1[21]+m_m1[23]*m_m1[9]);
	m_m2[88] = (m_m1[15]*m_m1[23]-m_m1[17]*m_m1[21]);
	m_m2[103] = (-m_m1[27]*m_m1[5]+m_m1[29]*m_m1[3]);
	m_m2[118] = (-m_m1[11]*m_m1[27]+m_m1[29]*m_m1[9]);
	m_m2[133] = (m_m1[15]*m_m1[29]-m_m1[17]*m_m1[27]);
	m_m2[148] = (m_m1[21]*m_m1[29]-m_m1[23]*m_m1[27]);
	m_m2[163] = (m_m1[3]*m_m1[35]-m_m1[33]*m_m1[5]);
	m_m2[178] = (-m_m1[11]*m_m1[33]+m_m1[35]*m_m1[9]);
	m_m2[193] = (m_m1[15]*m_m1[35]-m_m1[17]*m_m1[33]);
	m_m2[208] = (m_m1[21]*m_m1[35]-m_m1[23]*m_m1[33]);
	m_m2[223] = (m_m1[27]*m_m1[35]-m_m1[29]*m_m1[33]);

}
/**
 * Sets grade 2 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_2_14()
{
	m_m2[14] = (-m_m1[10]*m_m1[5]+m_m1[11]*m_m1[4]);
	m_m2[29] = (-m_m1[16]*m_m1[5]+m_m1[17]*m_m1[4]);
	m_m2[44] = (m_m1[10]*m_m1[17]-m_m1[11]*m_m1[16]);
	m_m2[59] = (-m_m1[22]*m_m1[5]+m_m1[23]*m_m1[4]);
	m_m2[74] = (m_m1[10]*m_m1[23]-m_m1[11]*m_m1[22]);
	m_m2[89] = (m_m1[16]*m_m1[23]-m_m1[17]*m_m1[22]);
	m_m2[104] = (-m_m1[28]*m_m1[5]+m_m1[29]*m_m1[4]);
	m_m2[119] = (m_m1[10]*m_m1[29]-m_m1[11]*m_m1[28]);
	m_m2[134] = (m_m1[16]*m_m1[29]-m_m1[17]*m_m1[28]);
	m_m2[149] = (m_m1[22]*m_m1[29]-m_m1[23]*m_m1[28]);
	m_m2[164] = (-m_m1[34]*m_m1[5]+m_m1[35]*m_m1[4]);
	m_m2[179] = (m_m1[10]*m_m1[35]-m_m1[11]*m_m1[34]);
	m_m2[194] = (m_m1[16]*m_m1[35]-m_m1[17]*m_m1[34]);
	m_m2[209] = (m_m1[22]*m_m1[35]-m_m1[23]*m_m1[34]);
	m_m2[224] = (m_m1[28]*m_m1[35]-m_m1[29]*m_m1[34]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_0()
{
	m_m3[0] = (m_m1[0]*m_m2[32]+m_m1[12]*m_m2[2]-m_m1[6]*m_m2[17]);
	m_m3[20] = (m_m1[0]*m_m2[62]+m_m1[18]*m_m2[2]-m_m1[6]*m_m2[47]);
	m_m3[40] = (m_m1[0]*m_m2[77]-m_m1[12]*m_m2[47]+m_m1[18]*m_m2[17]);
	m_m3[60] = (-m_m1[12]*m_m2[62]+m_m1[18]*m_m2[32]+m_m1[6]*m_m2[77]);
	m_m3[80] = (m_m1[0]*m_m2[107]+m_m1[24]*m_m2[2]-m_m1[6]*m_m2[92]);
	m_m3[100] = (m_m1[0]*m_m2[122]-m_m1[12]*m_m2[92]+m_m1[24]*m_m2[17]);
	m_m3[120] = (-m_m1[12]*m_m2[107]+m_m1[24]*m_m2[32]+m_m1[6]*m_m2[122]);
	m_m3[140] = (m_m1[0]*m_m2[137]-m_m1[18]*m_m2[92]+m_m1[24]*m_m2[47]);
	m_m3[160] = (-m_m1[18]*m_m2[107]+m_m1[24]*m_m2[62]+m_m1[6]*m_m2[137]);
	m_m3[180] = (m_m1[12]*m_m2[137]-m_m1[18]*m_m2[122]+m_m1[24]*m_m2[77]);
	m_m3[200] = (m_m1[0]*m_m2[167]+m_m1[30]*m_m2[2]-m_m1[6]*m_m2[152]);
	m_m3[220] = (m_m1[0]*m_m2[182]-m_m1[12]*m_m2[152]+m_m1[30]*m_m2[17]);
	m_m3[240] = (-m_m1[12]*m_m2[167]+m_m1[30]*m_m2[32]+m_m1[6]*m_m2[182]);
	m_m3[260] = (m_m1[0]*m_m2[197]-m_m1[18]*m_m2[152]+m_m1[30]*m_m2[47]);
	m_m3[280] = (-m_m1[18]*m_m2[167]+m_m1[30]*m_m2[62]+m_m1[6]*m_m2[197]);
	m_m3[300] = (m_m1[12]*m_m2[197]-m_m1[18]*m_m2[182]+m_m1[30]*m_m2[77]);
	m_m3[320] = (m_m1[0]*m_m2[212]-m_m1[24]*m_m2[152]+m_m1[30]*m_m2[92]);
	m_m3[340] = (-m_m1[24]*m_m2[167]+m_m1[30]*m_m2[107]+m_m1[6]*m_m2[212]);
	m_m3[360] = (m_m1[12]*m_m2[212]-m_m1[24]*m_m2[182]+m_m1[30]*m_m2[122]);
	m_m3[380] = (m_m1[18]*m_m2[212]-m_m1[24]*m_m2[197]+m_m1[30]*m_m2[137]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_1()
{
	m_m3[1] = (m_m1[0]*m_m2[34]+m_m1[12]*m_m2[4]-m_m1[6]*m_m2[19]);
	m_m3[21] = (m_m1[0]*m_m2[64]+m_m1[18]*m_m2[4]-m_m1[6]*m_m2[49]);
	m_m3[41] = (m_m1[0]*m_m2[79]-m_m1[12]*m_m2[49]+m_m1[18]*m_m2[19]);
	m_m3[61] = (-m_m1[12]*m_m2[64]+m_m1[18]*m_m2[34]+m_m1[6]*m_m2[79]);
	m_m3[81] = (m_m1[0]*m_m2[109]+m_m1[24]*m_m2[4]-m_m1[6]*m_m2[94]);
	m_m3[101] = (m_m1[0]*m_m2[124]-m_m1[12]*m_m2[94]+m_m1[24]*m_m2[19]);
	m_m3[121] = (-m_m1[12]*m_m2[109]+m_m1[24]*m_m2[34]+m_m1[6]*m_m2[124]);
	m_m3[141] = (m_m1[0]*m_m2[139]-m_m1[18]*m_m2[94]+m_m1[24]*m_m2[49]);
	m_m3[161] = (-m_m1[18]*m_m2[109]+m_m1[24]*m_m2[64]+m_m1[6]*m_m2[139]);
	m_m3[181] = (m_m1[12]*m_m2[139]-m_m1[18]*m_m2[124]+m_m1[24]*m_m2[79]);
	m_m3[201] = (m_m1[0]*m_m2[169]+m_m1[30]*m_m2[4]-m_m1[6]*m_m2[154]);
	m_m3[221] = (m_m1[0]*m_m2[184]-m_m1[12]*m_m2[154]+m_m1[30]*m_m2[19]);
	m_m3[241] = (-m_m1[12]*m_m2[169]+m_m1[30]*m_m2[34]+m_m1[6]*m_m2[184]);
	m_m3[261] = (m_m1[0]*m_m2[199]-m_m1[18]*m_m2[154]+m_m1[30]*m_m2[49]);
	m_m3[281] = (-m_m1[18]*m_m2[169]+m_m1[30]*m_m2[64]+m_m1[6]*m_m2[199]);
	m_m3[301] = (m_m1[12]*m_m2[199]-m_m1[18]*m_m2[184]+m_m1[30]*m_m2[79]);
	m_m3[321] = (m_m1[0]*m_m2[214]-m_m1[24]*m_m2[154]+m_m1[30]*m_m2[94]);
	m_m3[341] = (-m_m1[24]*m_m2[169]+m_m1[30]*m_m2[109]+m_m1[6]*m_m2[214]);
	m_m3[361] = (m_m1[12]*m_m2[214]-m_m1[24]*m_m2[184]+m_m1[30]*m_m2[124]);
	m_m3[381] = (m_m1[18]*m_m2[214]-m_m1[24]*m_m2[199]+m_m1[30]*m_m2[139]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_2()
{
	m_m3[2] = (m_m1[0]*m_m2[35]+m_m1[12]*m_m2[5]-m_m1[6]*m_m2[20]);
	m_m3[22] = (m_m1[0]*m_m2[65]+m_m1[18]*m_m2[5]-m_m1[6]*m_m2[50]);
	m_m3[42] = (m_m1[0]*m_m2[80]-m_m1[12]*m_m2[50]+m_m1[18]*m_m2[20]);
	m_m3[62] = (-m_m1[12]*m_m2[65]+m_m1[18]*m_m2[35]+m_m1[6]*m_m2[80]);
	m_m3[82] = (m_m1[0]*m_m2[110]+m_m1[24]*m_m2[5]-m_m1[6]*m_m2[95]);
	m_m3[102] = (m_m1[0]*m_m2[125]-m_m1[12]*m_m2[95]+m_m1[24]*m_m2[20]);
	m_m3[122] = (-m_m1[12]*m_m2[110]+m_m1[24]*m_m2[35]+m_m1[6]*m_m2[125]);
	m_m3[142] = (m_m1[0]*m_m2[140]-m_m1[18]*m_m2[95]+m_m1[24]*m_m2[50]);
	m_m3[162] = (-m_m1[18]*m_m2[110]+m_m1[24]*m_m2[65]+m_m1[6]*m_m2[140]);
	m_m3[182] = (m_m1[12]*m_m2[140]-m_m1[18]*m_m2[125]+m_m1[24]*m_m2[80]);
	m_m3[202] = (m_m1[0]*m_m2[170]+m_m1[30]*m_m2[5]-m_m1[6]*m_m2[155]);
	m_m3[222] = (m_m1[0]*m_m2[185]-m_m1[12]*m_m2[155]+m_m1[30]*m_m2[20]);
	m_m3[242] = (-m_m1[12]*m_m2[170]+m_m1[30]*m_m2[35]+m_m1[6]*m_m2[185]);
	m_m3[262] = (m_m1[0]*m_m2[200]-m_m1[18]*m_m2[155]+m_m1[30]*m_m2[50]);
	m_m3[282] = (-m_m1[18]*m_m2[170]+m_m1[30]*m_m2[65]+m_m1[6]*m_m2[200]);
	m_m3[302] = (m_m1[12]*m_m2[200]-m_m1[18]*m_m2[185]+m_m1[30]*m_m2[80]);
	m_m3[322] = (m_m1[0]*m_m2[215]-m_m1[24]*m_m2[155]+m_m1[30]*m_m2[95]);
	m_m3[342] = (-m_m1[24]*m_m2[170]+m_m1[30]*m_m2[110]+m_m1[6]*m_m2[215]);
	m_m3[362] = (m_m1[12]*m_m2[215]-m_m1[24]*m_m2[185]+m_m1[30]*m_m2[125]);
	m_m3[382] = (m_m1[18]*m_m2[215]-m_m1[24]*m_m2[200]+m_m1[30]*m_m2[140]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_3()
{
	m_m3[3] = (m_m1[1]*m_m2[35]+m_m1[13]*m_m2[5]-m_m1[7]*m_m2[20]);
	m_m3[23] = (m_m1[1]*m_m2[65]+m_m1[19]*m_m2[5]-m_m1[7]*m_m2[50]);
	m_m3[43] = (m_m1[1]*m_m2[80]-m_m1[13]*m_m2[50]+m_m1[19]*m_m2[20]);
	m_m3[63] = (-m_m1[13]*m_m2[65]+m_m1[19]*m_m2[35]+m_m1[7]*m_m2[80]);
	m_m3[83] = (m_m1[1]*m_m2[110]+m_m1[25]*m_m2[5]-m_m1[7]*m_m2[95]);
	m_m3[103] = (m_m1[1]*m_m2[125]-m_m1[13]*m_m2[95]+m_m1[25]*m_m2[20]);
	m_m3[123] = (-m_m1[13]*m_m2[110]+m_m1[25]*m_m2[35]+m_m1[7]*m_m2[125]);
	m_m3[143] = (m_m1[1]*m_m2[140]-m_m1[19]*m_m2[95]+m_m1[25]*m_m2[50]);
	m_m3[163] = (-m_m1[19]*m_m2[110]+m_m1[25]*m_m2[65]+m_m1[7]*m_m2[140]);
	m_m3[183] = (m_m1[13]*m_m2[140]-m_m1[19]*m_m2[125]+m_m1[25]*m_m2[80]);
	m_m3[203] = (m_m1[1]*m_m2[170]+m_m1[31]*m_m2[5]-m_m1[7]*m_m2[155]);
	m_m3[223] = (m_m1[1]*m_m2[185]-m_m1[13]*m_m2[155]+m_m1[31]*m_m2[20]);
	m_m3[243] = (-m_m1[13]*m_m2[170]+m_m1[31]*m_m2[35]+m_m1[7]*m_m2[185]);
	m_m3[263] = (m_m1[1]*m_m2[200]-m_m1[19]*m_m2[155]+m_m1[31]*m_m2[50]);
	m_m3[283] = (-m_m1[19]*m_m2[170]+m_m1[31]*m_m2[65]+m_m1[7]*m_m2[200]);
	m_m3[303] = (m_m1[13]*m_m2[200]-m_m1[19]*m_m2[185]+m_m1[31]*m_m2[80]);
	m_m3[323] = (m_m1[1]*m_m2[215]-m_m1[25]*m_m2[155]+m_m1[31]*m_m2[95]);
	m_m3[343] = (-m_m1[25]*m_m2[170]+m_m1[31]*m_m2[110]+m_m1[7]*m_m2[215]);
	m_m3[363] = (m_m1[13]*m_m2[215]-m_m1[25]*m_m2[185]+m_m1[31]*m_m2[125]);
	m_m3[383] = (m_m1[19]*m_m2[215]-m_m1[25]*m_m2[200]+m_m1[31]*m_m2[140]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_4()
{
	m_m3[4] = (m_m1[0]*m_m2[37]+m_m1[12]*m_m2[7]-m_m1[6]*m_m2[22]);
	m_m3[24] = (m_m1[0]*m_m2[67]+m_m1[18]*m_m2[7]-m_m1[6]*m_m2[52]);
	m_m3[44] = (m_m1[0]*m_m2[82]-m_m1[12]*m_m2[52]+m_m1[18]*m_m2[22]);
	m_m3[64] = (-m_m1[12]*m_m2[67]+m_m1[18]*m_m2[37]+m_m1[6]*m_m2[82]);
	m_m3[84] = (m_m1[0]*m_m2[112]+m_m1[24]*m_m2[7]-m_m1[6]*m_m2[97]);
	m_m3[104] = (m_m1[0]*m_m2[127]-m_m1[12]*m_m2[97]+m_m1[24]*m_m2[22]);
	m_m3[124] = (-m_m1[12]*m_m2[112]+m_m1[24]*m_m2[37]+m_m1[6]*m_m2[127]);
	m_m3[144] = (m_m1[0]*m_m2[142]-m_m1[18]*m_m2[97]+m_m1[24]*m_m2[52]);
	m_m3[164] = (-m_m1[18]*m_m2[112]+m_m1[24]*m_m2[67]+m_m1[6]*m_m2[142]);
	m_m3[184] = (m_m1[12]*m_m2[142]-m_m1[18]*m_m2[127]+m_m1[24]*m_m2[82]);
	m_m3[204] = (m_m1[0]*m_m2[172]+m_m1[30]*m_m2[7]-m_m1[6]*m_m2[157]);
	m_m3[224] = (m_m1[0]*m_m2[187]-m_m1[12]*m_m2[157]+m_m1[30]*m_m2[22]);
	m_m3[244] = (-m_m1[12]*m_m2[172]+m_m1[30]*m_m2[37]+m_m1[6]*m_m2[187]);
	m_m3[264] = (m_m1[0]*m_m2[202]-m_m1[18]*m_m2[157]+m_m1[30]*m_m2[52]);
	m_m3[284] = (-m_m1[18]*m_m2[172]+m_m1[30]*m_m2[67]+m_m1[6]*m_m2[202]);
	m_m3[304] = (m_m1[12]*m_m2[202]-m_m1[18]*m_m2[187]+m_m1[30]*m_m2[82]);
	m_m3[324] = (m_m1[0]*m_m2[217]-m_m1[24]*m_m2[157]+m_m1[30]*m_m2[97]);
	m_m3[344] = (-m_m1[24]*m_m2[172]+m_m1[30]*m_m2[112]+m_m1[6]*m_m2[217]);
	m_m3[364] = (m_m1[12]*m_m2[217]-m_m1[24]*m_m2[187]+m_m1[30]*m_m2[127]);
	m_m3[384] = (m_m1[18]*m_m2[217]-m_m1[24]*m_m2[202]+m_m1[30]*m_m2[142]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_5()
{
	m_m3[5] = (m_m1[0]*m_m2[38]+m_m1[12]*m_m2[8]-m_m1[6]*m_m2[23]);
	m_m3[25] = (m_m1[0]*m_m2[68]+m_m1[18]*m_m2[8]-m_m1[6]*m_m2[53]);
	m_m3[45] = (m_m1[0]*m_m2[83]-m_m1[12]*m_m2[53]+m_m1[18]*m_m2[23]);
	m_m3[65] = (-m_m1[12]*m_m2[68]+m_m1[18]*m_m2[38]+m_m1[6]*m_m2[83]);
	m_m3[85] = (m_m1[0]*m_m2[113]+m_m1[24]*m_m2[8]-m_m1[6]*m_m2[98]);
	m_m3[105] = (m_m1[0]*m_m2[128]-m_m1[12]*m_m2[98]+m_m1[24]*m_m2[23]);
	m_m3[125] = (-m_m1[12]*m_m2[113]+m_m1[24]*m_m2[38]+m_m1[6]*m_m2[128]);
	m_m3[145] = (m_m1[0]*m_m2[143]-m_m1[18]*m_m2[98]+m_m1[24]*m_m2[53]);
	m_m3[165] = (-m_m1[18]*m_m2[113]+m_m1[24]*m_m2[68]+m_m1[6]*m_m2[143]);
	m_m3[185] = (m_m1[12]*m_m2[143]-m_m1[18]*m_m2[128]+m_m1[24]*m_m2[83]);
	m_m3[205] = (m_m1[0]*m_m2[173]+m_m1[30]*m_m2[8]-m_m1[6]*m_m2[158]);
	m_m3[225] = (m_m1[0]*m_m2[188]-m_m1[12]*m_m2[158]+m_m1[30]*m_m2[23]);
	m_m3[245] = (-m_m1[12]*m_m2[173]+m_m1[30]*m_m2[38]+m_m1[6]*m_m2[188]);
	m_m3[265] = (m_m1[0]*m_m2[203]-m_m1[18]*m_m2[158]+m_m1[30]*m_m2[53]);
	m_m3[285] = (-m_m1[18]*m_m2[173]+m_m1[30]*m_m2[68]+m_m1[6]*m_m2[203]);
	m_m3[305] = (m_m1[12]*m_m2[203]-m_m1[18]*m_m2[188]+m_m1[30]*m_m2[83]);
	m_m3[325] = (m_m1[0]*m_m2[218]-m_m1[24]*m_m2[158]+m_m1[30]*m_m2[98]);
	m_m3[345] = (-m_m1[24]*m_m2[173]+m_m1[30]*m_m2[113]+m_m1[6]*m_m2[218]);
	m_m3[365] = (m_m1[12]*m_m2[218]-m_m1[24]*m_m2[188]+m_m1[30]*m_m2[128]);
	m_m3[385] = (m_m1[18]*m_m2[218]-m_m1[24]*m_m2[203]+m_m1[30]*m_m2[143]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_6()
{
	m_m3[6] = (m_m1[1]*m_m2[38]+m_m1[13]*m_m2[8]-m_m1[7]*m_m2[23]);
	m_m3[26] = (m_m1[1]*m_m2[68]+m_m1[19]*m_m2[8]-m_m1[7]*m_m2[53]);
	m_m3[46] = (m_m1[1]*m_m2[83]-m_m1[13]*m_m2[53]+m_m1[19]*m_m2[23]);
	m_m3[66] = (-m_m1[13]*m_m2[68]+m_m1[19]*m_m2[38]+m_m1[7]*m_m2[83]);
	m_m3[86] = (m_m1[1]*m_m2[113]+m_m1[25]*m_m2[8]-m_m1[7]*m_m2[98]);
	m_m3[106] = (m_m1[1]*m_m2[128]-m_m1[13]*m_m2[98]+m_m1[25]*m_m2[23]);
	m_m3[126] = (-m_m1[13]*m_m2[113]+m_m1[25]*m_m2[38]+m_m1[7]*m_m2[128]);
	m_m3[146] = (m_m1[1]*m_m2[143]-m_m1[19]*m_m2[98]+m_m1[25]*m_m2[53]);
	m_m3[166] = (-m_m1[19]*m_m2[113]+m_m1[25]*m_m2[68]+m_m1[7]*m_m2[143]);
	m_m3[186] = (m_m1[13]*m_m2[143]-m_m1[19]*m_m2[128]+m_m1[25]*m_m2[83]);
	m_m3[206] = (m_m1[1]*m_m2[173]+m_m1[31]*m_m2[8]-m_m1[7]*m_m2[158]);
	m_m3[226] = (m_m1[1]*m_m2[188]-m_m1[13]*m_m2[158]+m_m1[31]*m_m2[23]);
	m_m3[246] = (-m_m1[13]*m_m2[173]+m_m1[31]*m_m2[38]+m_m1[7]*m_m2[188]);
	m_m3[266] = (m_m1[1]*m_m2[203]-m_m1[19]*m_m2[158]+m_m1[31]*m_m2[53]);
	m_m3[286] = (-m_m1[19]*m_m2[173]+m_m1[31]*m_m2[68]+m_m1[7]*m_m2[203]);
	m_m3[306] = (m_m1[13]*m_m2[203]-m_m1[19]*m_m2[188]+m_m1[31]*m_m2[83]);
	m_m3[326] = (m_m1[1]*m_m2[218]-m_m1[25]*m_m2[158]+m_m1[31]*m_m2[98]);
	m_m3[346] = (-m_m1[25]*m_m2[173]+m_m1[31]*m_m2[113]+m_m1[7]*m_m2[218]);
	m_m3[366] = (m_m1[13]*m_m2[218]-m_m1[25]*m_m2[188]+m_m1[31]*m_m2[128]);
	m_m3[386] = (m_m1[19]*m_m2[218]-m_m1[25]*m_m2[203]+m_m1[31]*m_m2[143]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_7()
{
	m_m3[7] = (m_m1[0]*m_m2[39]+m_m1[12]*m_m2[9]-m_m1[6]*m_m2[24]);
	m_m3[27] = (m_m1[0]*m_m2[69]+m_m1[18]*m_m2[9]-m_m1[6]*m_m2[54]);
	m_m3[47] = (m_m1[0]*m_m2[84]-m_m1[12]*m_m2[54]+m_m1[18]*m_m2[24]);
	m_m3[67] = (-m_m1[12]*m_m2[69]+m_m1[18]*m_m2[39]+m_m1[6]*m_m2[84]);
	m_m3[87] = (m_m1[0]*m_m2[114]+m_m1[24]*m_m2[9]-m_m1[6]*m_m2[99]);
	m_m3[107] = (m_m1[0]*m_m2[129]-m_m1[12]*m_m2[99]+m_m1[24]*m_m2[24]);
	m_m3[127] = (-m_m1[12]*m_m2[114]+m_m1[24]*m_m2[39]+m_m1[6]*m_m2[129]);
	m_m3[147] = (m_m1[0]*m_m2[144]-m_m1[18]*m_m2[99]+m_m1[24]*m_m2[54]);
	m_m3[167] = (-m_m1[18]*m_m2[114]+m_m1[24]*m_m2[69]+m_m1[6]*m_m2[144]);
	m_m3[187] = (m_m1[12]*m_m2[144]-m_m1[18]*m_m2[129]+m_m1[24]*m_m2[84]);
	m_m3[207] = (m_m1[0]*m_m2[174]+m_m1[30]*m_m2[9]-m_m1[6]*m_m2[159]);
	m_m3[227] = (m_m1[0]*m_m2[189]-m_m1[12]*m_m2[159]+m_m1[30]*m_m2[24]);
	m_m3[247] = (-m_m1[12]*m_m2[174]+m_m1[30]*m_m2[39]+m_m1[6]*m_m2[189]);
	m_m3[267] = (m_m1[0]*m_m2[204]-m_m1[18]*m_m2[159]+m_m1[30]*m_m2[54]);
	m_m3[287] = (-m_m1[18]*m_m2[174]+m_m1[30]*m_m2[69]+m_m1[6]*m_m2[204]);
	m_m3[307] = (m_m1[12]*m_m2[204]-m_m1[18]*m_m2[189]+m_m1[30]*m_m2[84]);
	m_m3[327] = (m_m1[0]*m_m2[219]-m_m1[24]*m_m2[159]+m_m1[30]*m_m2[99]);
	m_m3[347] = (-m_m1[24]*m_m2[174]+m_m1[30]*m_m2[114]+m_m1[6]*m_m2[219]);
	m_m3[367] = (m_m1[12]*m_m2[219]-m_m1[24]*m_m2[189]+m_m1[30]*m_m2[129]);
	m_m3[387] = (m_m1[18]*m_m2[219]-m_m1[24]*m_m2[204]+m_m1[30]*m_m2[144]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_8()
{
	m_m3[8] = (m_m1[1]*m_m2[39]+m_m1[13]*m_m2[9]-m_m1[7]*m_m2[24]);
	m_m3[28] = (m_m1[1]*m_m2[69]+m_m1[19]*m_m2[9]-m_m1[7]*m_m2[54]);
	m_m3[48] = (m_m1[1]*m_m2[84]-m_m1[13]*m_m2[54]+m_m1[19]*m_m2[24]);
	m_m3[68] = (-m_m1[13]*m_m2[69]+m_m1[19]*m_m2[39]+m_m1[7]*m_m2[84]);
	m_m3[88] = (m_m1[1]*m_m2[114]+m_m1[25]*m_m2[9]-m_m1[7]*m_m2[99]);
	m_m3[108] = (m_m1[1]*m_m2[129]-m_m1[13]*m_m2[99]+m_m1[25]*m_m2[24]);
	m_m3[128] = (-m_m1[13]*m_m2[114]+m_m1[25]*m_m2[39]+m_m1[7]*m_m2[129]);
	m_m3[148] = (m_m1[1]*m_m2[144]-m_m1[19]*m_m2[99]+m_m1[25]*m_m2[54]);
	m_m3[168] = (-m_m1[19]*m_m2[114]+m_m1[25]*m_m2[69]+m_m1[7]*m_m2[144]);
	m_m3[188] = (m_m1[13]*m_m2[144]-m_m1[19]*m_m2[129]+m_m1[25]*m_m2[84]);
	m_m3[208] = (m_m1[1]*m_m2[174]+m_m1[31]*m_m2[9]-m_m1[7]*m_m2[159]);
	m_m3[228] = (m_m1[1]*m_m2[189]-m_m1[13]*m_m2[159]+m_m1[31]*m_m2[24]);
	m_m3[248] = (-m_m1[13]*m_m2[174]+m_m1[31]*m_m2[39]+m_m1[7]*m_m2[189]);
	m_m3[268] = (m_m1[1]*m_m2[204]-m_m1[19]*m_m2[159]+m_m1[31]*m_m2[54]);
	m_m3[288] = (-m_m1[19]*m_m2[174]+m_m1[31]*m_m2[69]+m_m1[7]*m_m2[204]);
	m_m3[308] = (m_m1[13]*m_m2[204]-m_m1[19]*m_m2[189]+m_m1[31]*m_m2[84]);
	m_m3[328] = (m_m1[1]*m_m2[219]-m_m1[25]*m_m2[159]+m_m1[31]*m_m2[99]);
	m_m3[348] = (-m_m1[25]*m_m2[174]+m_m1[31]*m_m2[114]+m_m1[7]*m_m2[219]);
	m_m3[368] = (m_m1[13]*m_m2[219]-m_m1[25]*m_m2[189]+m_m1[31]*m_m2[129]);
	m_m3[388] = (m_m1[19]*m_m2[219]-m_m1[25]*m_m2[204]+m_m1[31]*m_m2[144]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_9()
{
	m_m3[9] = (m_m1[14]*m_m2[9]+m_m1[2]*m_m2[39]-m_m1[8]*m_m2[24]);
	m_m3[29] = (m_m1[2]*m_m2[69]+m_m1[20]*m_m2[9]-m_m1[8]*m_m2[54]);
	m_m3[49] = (-m_m1[14]*m_m2[54]+m_m1[2]*m_m2[84]+m_m1[20]*m_m2[24]);
	m_m3[69] = (-m_m1[14]*m_m2[69]+m_m1[20]*m_m2[39]+m_m1[8]*m_m2[84]);
	m_m3[89] = (m_m1[2]*m_m2[114]+m_m1[26]*m_m2[9]-m_m1[8]*m_m2[99]);
	m_m3[109] = (-m_m1[14]*m_m2[99]+m_m1[2]*m_m2[129]+m_m1[26]*m_m2[24]);
	m_m3[129] = (-m_m1[14]*m_m2[114]+m_m1[26]*m_m2[39]+m_m1[8]*m_m2[129]);
	m_m3[149] = (m_m1[2]*m_m2[144]-m_m1[20]*m_m2[99]+m_m1[26]*m_m2[54]);
	m_m3[169] = (-m_m1[20]*m_m2[114]+m_m1[26]*m_m2[69]+m_m1[8]*m_m2[144]);
	m_m3[189] = (m_m1[14]*m_m2[144]-m_m1[20]*m_m2[129]+m_m1[26]*m_m2[84]);
	m_m3[209] = (m_m1[2]*m_m2[174]+m_m1[32]*m_m2[9]-m_m1[8]*m_m2[159]);
	m_m3[229] = (-m_m1[14]*m_m2[159]+m_m1[2]*m_m2[189]+m_m1[32]*m_m2[24]);
	m_m3[249] = (-m_m1[14]*m_m2[174]+m_m1[32]*m_m2[39]+m_m1[8]*m_m2[189]);
	m_m3[269] = (m_m1[2]*m_m2[204]-m_m1[20]*m_m2[159]+m_m1[32]*m_m2[54]);
	m_m3[289] = (-m_m1[20]*m_m2[174]+m_m1[32]*m_m2[69]+m_m1[8]*m_m2[204]);
	m_m3[309] = (m_m1[14]*m_m2[204]-m_m1[20]*m_m2[189]+m_m1[32]*m_m2[84]);
	m_m3[329] = (m_m1[2]*m_m2[219]-m_m1[26]*m_m2[159]+m_m1[32]*m_m2[99]);
	m_m3[349] = (-m_m1[26]*m_m2[174]+m_m1[32]*m_m2[114]+m_m1[8]*m_m2[219]);
	m_m3[369] = (m_m1[14]*m_m2[219]-m_m1[26]*m_m2[189]+m_m1[32]*m_m2[129]);
	m_m3[389] = (m_m1[20]*m_m2[219]-m_m1[26]*m_m2[204]+m_m1[32]*m_m2[144]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_10()
{
	m_m3[10] = (m_m1[0]*m_m2[41]+m_m1[12]*m_m2[11]-m_m1[6]*m_m2[26]);
	m_m3[30] = (m_m1[0]*m_m2[71]+m_m1[18]*m_m2[11]-m_m1[6]*m_m2[56]);
	m_m3[50] = (m_m1[0]*m_m2[86]-m_m1[12]*m_m2[56]+m_m1[18]*m_m2[26]);
	m_m3[70] = (-m_m1[12]*m_m2[71]+m_m1[18]*m_m2[41]+m_m1[6]*m_m2[86]);
	m_m3[90] = (m_m1[0]*m_m2[116]+m_m1[24]*m_m2[11]-m_m1[6]*m_m2[101]);
	m_m3[110] = (m_m1[0]*m_m2[131]-m_m1[12]*m_m2[101]+m_m1[24]*m_m2[26]);
	m_m3[130] = (-m_m1[12]*m_m2[116]+m_m1[24]*m_m2[41]+m_m1[6]*m_m2[131]);
	m_m3[150] = (m_m1[0]*m_m2[146]-m_m1[18]*m_m2[101]+m_m1[24]*m_m2[56]);
	m_m3[170] = (-m_m1[18]*m_m2[116]+m_m1[24]*m_m2[71]+m_m1[6]*m_m2[146]);
	m_m3[190] = (m_m1[12]*m_m2[146]-m_m1[18]*m_m2[131]+m_m1[24]*m_m2[86]);
	m_m3[210] = (m_m1[0]*m_m2[176]+m_m1[30]*m_m2[11]-m_m1[6]*m_m2[161]);
	m_m3[230] = (m_m1[0]*m_m2[191]-m_m1[12]*m_m2[161]+m_m1[30]*m_m2[26]);
	m_m3[250] = (-m_m1[12]*m_m2[176]+m_m1[30]*m_m2[41]+m_m1[6]*m_m2[191]);
	m_m3[270] = (m_m1[0]*m_m2[206]-m_m1[18]*m_m2[161]+m_m1[30]*m_m2[56]);
	m_m3[290] = (-m_m1[18]*m_m2[176]+m_m1[30]*m_m2[71]+m_m1[6]*m_m2[206]);
	m_m3[310] = (m_m1[12]*m_m2[206]-m_m1[18]*m_m2[191]+m_m1[30]*m_m2[86]);
	m_m3[330] = (m_m1[0]*m_m2[221]-m_m1[24]*m_m2[161]+m_m1[30]*m_m2[101]);
	m_m3[350] = (-m_m1[24]*m_m2[176]+m_m1[30]*m_m2[116]+m_m1[6]*m_m2[221]);
	m_m3[370] = (m_m1[12]*m_m2[221]-m_m1[24]*m_m2[191]+m_m1[30]*m_m2[131]);
	m_m3[390] = (m_m1[18]*m_m2[221]-m_m1[24]*m_m2[206]+m_m1[30]*m_m2[146]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_11()
{
	m_m3[11] = (m_m1[0]*m_m2[42]+m_m1[12]*m_m2[12]-m_m1[6]*m_m2[27]);
	m_m3[31] = (m_m1[0]*m_m2[72]+m_m1[18]*m_m2[12]-m_m1[6]*m_m2[57]);
	m_m3[51] = (m_m1[0]*m_m2[87]-m_m1[12]*m_m2[57]+m_m1[18]*m_m2[27]);
	m_m3[71] = (-m_m1[12]*m_m2[72]+m_m1[18]*m_m2[42]+m_m1[6]*m_m2[87]);
	m_m3[91] = (m_m1[0]*m_m2[117]+m_m1[24]*m_m2[12]-m_m1[6]*m_m2[102]);
	m_m3[111] = (m_m1[0]*m_m2[132]-m_m1[12]*m_m2[102]+m_m1[24]*m_m2[27]);
	m_m3[131] = (-m_m1[12]*m_m2[117]+m_m1[24]*m_m2[42]+m_m1[6]*m_m2[132]);
	m_m3[151] = (m_m1[0]*m_m2[147]-m_m1[18]*m_m2[102]+m_m1[24]*m_m2[57]);
	m_m3[171] = (-m_m1[18]*m_m2[117]+m_m1[24]*m_m2[72]+m_m1[6]*m_m2[147]);
	m_m3[191] = (m_m1[12]*m_m2[147]-m_m1[18]*m_m2[132]+m_m1[24]*m_m2[87]);
	m_m3[211] = (m_m1[0]*m_m2[177]+m_m1[30]*m_m2[12]-m_m1[6]*m_m2[162]);
	m_m3[231] = (m_m1[0]*m_m2[192]-m_m1[12]*m_m2[162]+m_m1[30]*m_m2[27]);
	m_m3[251] = (-m_m1[12]*m_m2[177]+m_m1[30]*m_m2[42]+m_m1[6]*m_m2[192]);
	m_m3[271] = (m_m1[0]*m_m2[207]-m_m1[18]*m_m2[162]+m_m1[30]*m_m2[57]);
	m_m3[291] = (-m_m1[18]*m_m2[177]+m_m1[30]*m_m2[72]+m_m1[6]*m_m2[207]);
	m_m3[311] = (m_m1[12]*m_m2[207]-m_m1[18]*m_m2[192]+m_m1[30]*m_m2[87]);
	m_m3[331] = (m_m1[0]*m_m2[222]-m_m1[24]*m_m2[162]+m_m1[30]*m_m2[102]);
	m_m3[351] = (-m_m1[24]*m_m2[177]+m_m1[30]*m_m2[117]+m_m1[6]*m_m2[222]);
	m_m3[371] = (m_m1[12]*m_m2[222]-m_m1[24]*m_m2[192]+m_m1[30]*m_m2[132]);
	m_m3[391] = (m_m1[18]*m_m2[222]-m_m1[24]*m_m2[207]+m_m1[30]*m_m2[147]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_12()
{
	m_m3[12] = (m_m1[1]*m_m2[42]+m_m1[13]*m_m2[12]-m_m1[7]*m_m2[27]);
	m_m3[32] = (m_m1[1]*m_m2[72]+m_m1[19]*m_m2[12]-m_m1[7]*m_m2[57]);
	m_m3[52] = (m_m1[1]*m_m2[87]-m_m1[13]*m_m2[57]+m_m1[19]*m_m2[27]);
	m_m3[72] = (-m_m1[13]*m_m2[72]+m_m1[19]*m_m2[42]+m_m1[7]*m_m2[87]);
	m_m3[92] = (m_m1[1]*m_m2[117]+m_m1[25]*m_m2[12]-m_m1[7]*m_m2[102]);
	m_m3[112] = (m_m1[1]*m_m2[132]-m_m1[13]*m_m2[102]+m_m1[25]*m_m2[27]);
	m_m3[132] = (-m_m1[13]*m_m2[117]+m_m1[25]*m_m2[42]+m_m1[7]*m_m2[132]);
	m_m3[152] = (m_m1[1]*m_m2[147]-m_m1[19]*m_m2[102]+m_m1[25]*m_m2[57]);
	m_m3[172] = (-m_m1[19]*m_m2[117]+m_m1[25]*m_m2[72]+m_m1[7]*m_m2[147]);
	m_m3[192] = (m_m1[13]*m_m2[147]-m_m1[19]*m_m2[132]+m_m1[25]*m_m2[87]);
	m_m3[212] = (m_m1[1]*m_m2[177]+m_m1[31]*m_m2[12]-m_m1[7]*m_m2[162]);
	m_m3[232] = (m_m1[1]*m_m2[192]-m_m1[13]*m_m2[162]+m_m1[31]*m_m2[27]);
	m_m3[252] = (-m_m1[13]*m_m2[177]+m_m1[31]*m_m2[42]+m_m1[7]*m_m2[192]);
	m_m3[272] = (m_m1[1]*m_m2[207]-m_m1[19]*m_m2[162]+m_m1[31]*m_m2[57]);
	m_m3[292] = (-m_m1[19]*m_m2[177]+m_m1[31]*m_m2[72]+m_m1[7]*m_m2[207]);
	m_m3[312] = (m_m1[13]*m_m2[207]-m_m1[19]*m_m2[192]+m_m1[31]*m_m2[87]);
	m_m3[332] = (m_m1[1]*m_m2[222]-m_m1[25]*m_m2[162]+m_m1[31]*m_m2[102]);
	m_m3[352] = (-m_m1[25]*m_m2[177]+m_m1[31]*m_m2[117]+m_m1[7]*m_m2[222]);
	m_m3[372] = (m_m1[13]*m_m2[222]-m_m1[25]*m_m2[192]+m_m1[31]*m_m2[132]);
	m_m3[392] = (m_m1[19]*m_m2[222]-m_m1[25]*m_m2[207]+m_m1[31]*m_m2[147]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_13()
{
	m_m3[13] = (m_m1[0]*m_m2[43]+m_m1[12]*m_m2[13]-m_m1[6]*m_m2[28]);
	m_m3[33] = (m_m1[0]*m_m2[73]+m_m1[18]*m_m2[13]-m_m1[6]*m_m2[58]);
	m_m3[53] = (m_m1[0]*m_m2[88]-m_m1[12]*m_m2[58]+m_m1[18]*m_m2[28]);
	m_m3[73] = (-m_m1[12]*m_m2[73]+m_m1[18]*m_m2[43]+m_m1[6]*m_m2[88]);
	m_m3[93] = (m_m1[0]*m_m2[118]+m_m1[24]*m_m2[13]-m_m1[6]*m_m2[103]);
	m_m3[113] = (m_m1[0]*m_m2[133]-m_m1[12]*m_m2[103]+m_m1[24]*m_m2[28]);
	m_m3[133] = (-m_m1[12]*m_m2[118]+m_m1[24]*m_m2[43]+m_m1[6]*m_m2[133]);
	m_m3[153] = (m_m1[0]*m_m2[148]-m_m1[18]*m_m2[103]+m_m1[24]*m_m2[58]);
	m_m3[173] = (-m_m1[18]*m_m2[118]+m_m1[24]*m_m2[73]+m_m1[6]*m_m2[148]);
	m_m3[193] = (m_m1[12]*m_m2[148]-m_m1[18]*m_m2[133]+m_m1[24]*m_m2[88]);
	m_m3[213] = (m_m1[0]*m_m2[178]+m_m1[30]*m_m2[13]-m_m1[6]*m_m2[163]);
	m_m3[233] = (m_m1[0]*m_m2[193]-m_m1[12]*m_m2[163]+m_m1[30]*m_m2[28]);
	m_m3[253] = (-m_m1[12]*m_m2[178]+m_m1[30]*m_m2[43]+m_m1[6]*m_m2[193]);
	m_m3[273] = (m_m1[0]*m_m2[208]-m_m1[18]*m_m2[163]+m_m1[30]*m_m2[58]);
	m_m3[293] = (-m_m1[18]*m_m2[178]+m_m1[30]*m_m2[73]+m_m1[6]*m_m2[208]);
	m_m3[313] = (m_m1[12]*m_m2[208]-m_m1[18]*m_m2[193]+m_m1[30]*m_m2[88]);
	m_m3[333] = (m_m1[0]*m_m2[223]-m_m1[24]*m_m2[163]+m_m1[30]*m_m2[103]);
	m_m3[353] = (-m_m1[24]*m_m2[178]+m_m1[30]*m_m2[118]+m_m1[6]*m_m2[223]);
	m_m3[373] = (m_m1[12]*m_m2[223]-m_m1[24]*m_m2[193]+m_m1[30]*m_m2[133]);
	m_m3[393] = (m_m1[18]*m_m2[223]-m_m1[24]*m_m2[208]+m_m1[30]*m_m2[148]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_14()
{
	m_m3[14] = (m_m1[1]*m_m2[43]+m_m1[13]*m_m2[13]-m_m1[7]*m_m2[28]);
	m_m3[34] = (m_m1[1]*m_m2[73]+m_m1[19]*m_m2[13]-m_m1[7]*m_m2[58]);
	m_m3[54] = (m_m1[1]*m_m2[88]-m_m1[13]*m_m2[58]+m_m1[19]*m_m2[28]);
	m_m3[74] = (-m_m1[13]*m_m2[73]+m_m1[19]*m_m2[43]+m_m1[7]*m_m2[88]);
	m_m3[94] = (m_m1[1]*m_m2[118]+m_m1[25]*m_m2[13]-m_m1[7]*m_m2[103]);
	m_m3[114] = (m_m1[1]*m_m2[133]-m_m1[13]*m_m2[103]+m_m1[25]*m_m2[28]);
	m_m3[134] = (-m_m1[13]*m_m2[118]+m_m1[25]*m_m2[43]+m_m1[7]*m_m2[133]);
	m_m3[154] = (m_m1[1]*m_m2[148]-m_m1[19]*m_m2[103]+m_m1[25]*m_m2[58]);
	m_m3[174] = (-m_m1[19]*m_m2[118]+m_m1[25]*m_m2[73]+m_m1[7]*m_m2[148]);
	m_m3[194] = (m_m1[13]*m_m2[148]-m_m1[19]*m_m2[133]+m_m1[25]*m_m2[88]);
	m_m3[214] = (m_m1[1]*m_m2[178]+m_m1[31]*m_m2[13]-m_m1[7]*m_m2[163]);
	m_m3[234] = (m_m1[1]*m_m2[193]-m_m1[13]*m_m2[163]+m_m1[31]*m_m2[28]);
	m_m3[254] = (-m_m1[13]*m_m2[178]+m_m1[31]*m_m2[43]+m_m1[7]*m_m2[193]);
	m_m3[274] = (m_m1[1]*m_m2[208]-m_m1[19]*m_m2[163]+m_m1[31]*m_m2[58]);
	m_m3[294] = (-m_m1[19]*m_m2[178]+m_m1[31]*m_m2[73]+m_m1[7]*m_m2[208]);
	m_m3[314] = (m_m1[13]*m_m2[208]-m_m1[19]*m_m2[193]+m_m1[31]*m_m2[88]);
	m_m3[334] = (m_m1[1]*m_m2[223]-m_m1[25]*m_m2[163]+m_m1[31]*m_m2[103]);
	m_m3[354] = (-m_m1[25]*m_m2[178]+m_m1[31]*m_m2[118]+m_m1[7]*m_m2[223]);
	m_m3[374] = (m_m1[13]*m_m2[223]-m_m1[25]*m_m2[193]+m_m1[31]*m_m2[133]);
	m_m3[394] = (m_m1[19]*m_m2[223]-m_m1[25]*m_m2[208]+m_m1[31]*m_m2[148]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_15()
{
	m_m3[15] = (m_m1[14]*m_m2[13]+m_m1[2]*m_m2[43]-m_m1[8]*m_m2[28]);
	m_m3[35] = (m_m1[2]*m_m2[73]+m_m1[20]*m_m2[13]-m_m1[8]*m_m2[58]);
	m_m3[55] = (-m_m1[14]*m_m2[58]+m_m1[2]*m_m2[88]+m_m1[20]*m_m2[28]);
	m_m3[75] = (-m_m1[14]*m_m2[73]+m_m1[20]*m_m2[43]+m_m1[8]*m_m2[88]);
	m_m3[95] = (m_m1[2]*m_m2[118]+m_m1[26]*m_m2[13]-m_m1[8]*m_m2[103]);
	m_m3[115] = (-m_m1[14]*m_m2[103]+m_m1[2]*m_m2[133]+m_m1[26]*m_m2[28]);
	m_m3[135] = (-m_m1[14]*m_m2[118]+m_m1[26]*m_m2[43]+m_m1[8]*m_m2[133]);
	m_m3[155] = (m_m1[2]*m_m2[148]-m_m1[20]*m_m2[103]+m_m1[26]*m_m2[58]);
	m_m3[175] = (-m_m1[20]*m_m2[118]+m_m1[26]*m_m2[73]+m_m1[8]*m_m2[148]);
	m_m3[195] = (m_m1[14]*m_m2[148]-m_m1[20]*m_m2[133]+m_m1[26]*m_m2[88]);
	m_m3[215] = (m_m1[2]*m_m2[178]+m_m1[32]*m_m2[13]-m_m1[8]*m_m2[163]);
	m_m3[235] = (-m_m1[14]*m_m2[163]+m_m1[2]*m_m2[193]+m_m1[32]*m_m2[28]);
	m_m3[255] = (-m_m1[14]*m_m2[178]+m_m1[32]*m_m2[43]+m_m1[8]*m_m2[193]);
	m_m3[275] = (m_m1[2]*m_m2[208]-m_m1[20]*m_m2[163]+m_m1[32]*m_m2[58]);
	m_m3[295] = (-m_m1[20]*m_m2[178]+m_m1[32]*m_m2[73]+m_m1[8]*m_m2[208]);
	m_m3[315] = (m_m1[14]*m_m2[208]-m_m1[20]*m_m2[193]+m_m1[32]*m_m2[88]);
	m_m3[335] = (m_m1[2]*m_m2[223]-m_m1[26]*m_m2[163]+m_m1[32]*m_m2[103]);
	m_m3[355] = (-m_m1[26]*m_m2[178]+m_m1[32]*m_m2[118]+m_m1[8]*m_m2[223]);
	m_m3[375] = (m_m1[14]*m_m2[223]-m_m1[26]*m_m2[193]+m_m1[32]*m_m2[133]);
	m_m3[395] = (m_m1[20]*m_m2[223]-m_m1[26]*m_m2[208]+m_m1[32]*m_m2[148]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_16()
{
	m_m3[16] = (m_m1[0]*m_m2[44]+m_m1[12]*m_m2[14]-m_m1[6]*m_m2[29]);
	m_m3[36] = (m_m1[0]*m_m2[74]+m_m1[18]*m_m2[14]-m_m1[6]*m_m2[59]);
	m_m3[56] = (m_m1[0]*m_m2[89]-m_m1[12]*m_m2[59]+m_m1[18]*m_m2[29]);
	m_m3[76] = (-m_m1[12]*m_m2[74]+m_m1[18]*m_m2[44]+m_m1[6]*m_m2[89]);
	m_m3[96] = (m_m1[0]*m_m2[119]+m_m1[24]*m_m2[14]-m_m1[6]*m_m2[104]);
	m_m3[116] = (m_m1[0]*m_m2[134]-m_m1[12]*m_m2[104]+m_m1[24]*m_m2[29]);
	m_m3[136] = (-m_m1[12]*m_m2[119]+m_m1[24]*m_m2[44]+m_m1[6]*m_m2[134]);
	m_m3[156] = (m_m1[0]*m_m2[149]-m_m1[18]*m_m2[104]+m_m1[24]*m_m2[59]);
	m_m3[176] = (-m_m1[18]*m_m2[119]+m_m1[24]*m_m2[74]+m_m1[6]*m_m2[149]);
	m_m3[196] = (m_m1[12]*m_m2[149]-m_m1[18]*m_m2[134]+m_m1[24]*m_m2[89]);
	m_m3[216] = (m_m1[0]*m_m2[179]+m_m1[30]*m_m2[14]-m_m1[6]*m_m2[164]);
	m_m3[236] = (m_m1[0]*m_m2[194]-m_m1[12]*m_m2[164]+m_m1[30]*m_m2[29]);
	m_m3[256] = (-m_m1[12]*m_m2[179]+m_m1[30]*m_m2[44]+m_m1[6]*m_m2[194]);
	m_m3[276] = (m_m1[0]*m_m2[209]-m_m1[18]*m_m2[164]+m_m1[30]*m_m2[59]);
	m_m3[296] = (-m_m1[18]*m_m2[179]+m_m1[30]*m_m2[74]+m_m1[6]*m_m2[209]);
	m_m3[316] = (m_m1[12]*m_m2[209]-m_m1[18]*m_m2[194]+m_m1[30]*m_m2[89]);
	m_m3[336] = (m_m1[0]*m_m2[224]-m_m1[24]*m_m2[164]+m_m1[30]*m_m2[104]);
	m_m3[356] = (-m_m1[24]*m_m2[179]+m_m1[30]*m_m2[119]+m_m1[6]*m_m2[224]);
	m_m3[376] = (m_m1[12]*m_m2[224]-m_m1[24]*m_m2[194]+m_m1[30]*m_m2[134]);
	m_m3[396] = (m_m1[18]*m_m2[224]-m_m1[24]*m_m2[209]+m_m1[30]*m_m2[149]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_17()
{
	m_m3[17] = (m_m1[1]*m_m2[44]+m_m1[13]*m_m2[14]-m_m1[7]*m_m2[29]);
	m_m3[37] = (m_m1[1]*m_m2[74]+m_m1[19]*m_m2[14]-m_m1[7]*m_m2[59]);
	m_m3[57] = (m_m1[1]*m_m2[89]-m_m1[13]*m_m2[59]+m_m1[19]*m_m2[29]);
	m_m3[77] = (-m_m1[13]*m_m2[74]+m_m1[19]*m_m2[44]+m_m1[7]*m_m2[89]);
	m_m3[97] = (m_m1[1]*m_m2[119]+m_m1[25]*m_m2[14]-m_m1[7]*m_m2[104]);
	m_m3[117] = (m_m1[1]*m_m2[134]-m_m1[13]*m_m2[104]+m_m1[25]*m_m2[29]);
	m_m3[137] = (-m_m1[13]*m_m2[119]+m_m1[25]*m_m2[44]+m_m1[7]*m_m2[134]);
	m_m3[157] = (m_m1[1]*m_m2[149]-m_m1[19]*m_m2[104]+m_m1[25]*m_m2[59]);
	m_m3[177] = (-m_m1[19]*m_m2[119]+m_m1[25]*m_m2[74]+m_m1[7]*m_m2[149]);
	m_m3[197] = (m_m1[13]*m_m2[149]-m_m1[19]*m_m2[134]+m_m1[25]*m_m2[89]);
	m_m3[217] = (m_m1[1]*m_m2[179]+m_m1[31]*m_m2[14]-m_m1[7]*m_m2[164]);
	m_m3[237] = (m_m1[1]*m_m2[194]-m_m1[13]*m_m2[164]+m_m1[31]*m_m2[29]);
	m_m3[257] = (-m_m1[13]*m_m2[179]+m_m1[31]*m_m2[44]+m_m1[7]*m_m2[194]);
	m_m3[277] = (m_m1[1]*m_m2[209]-m_m1[19]*m_m2[164]+m_m1[31]*m_m2[59]);
	m_m3[297] = (-m_m1[19]*m_m2[179]+m_m1[31]*m_m2[74]+m_m1[7]*m_m2[209]);
	m_m3[317] = (m_m1[13]*m_m2[209]-m_m1[19]*m_m2[194]+m_m1[31]*m_m2[89]);
	m_m3[337] = (m_m1[1]*m_m2[224]-m_m1[25]*m_m2[164]+m_m1[31]*m_m2[104]);
	m_m3[357] = (-m_m1[25]*m_m2[179]+m_m1[31]*m_m2[119]+m_m1[7]*m_m2[224]);
	m_m3[377] = (m_m1[13]*m_m2[224]-m_m1[25]*m_m2[194]+m_m1[31]*m_m2[134]);
	m_m3[397] = (m_m1[19]*m_m2[224]-m_m1[25]*m_m2[209]+m_m1[31]*m_m2[149]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_18()
{
	m_m3[18] = (m_m1[14]*m_m2[14]+m_m1[2]*m_m2[44]-m_m1[8]*m_m2[29]);
	m_m3[38] = (m_m1[2]*m_m2[74]+m_m1[20]*m_m2[14]-m_m1[8]*m_m2[59]);
	m_m3[58] = (-m_m1[14]*m_m2[59]+m_m1[2]*m_m2[89]+m_m1[20]*m_m2[29]);
	m_m3[78] = (-m_m1[14]*m_m2[74]+m_m1[20]*m_m2[44]+m_m1[8]*m_m2[89]);
	m_m3[98] = (m_m1[2]*m_m2[119]+m_m1[26]*m_m2[14]-m_m1[8]*m_m2[104]);
	m_m3[118] = (-m_m1[14]*m_m2[104]+m_m1[2]*m_m2[134]+m_m1[26]*m_m2[29]);
	m_m3[138] = (-m_m1[14]*m_m2[119]+m_m1[26]*m_m2[44]+m_m1[8]*m_m2[134]);
	m_m3[158] = (m_m1[2]*m_m2[149]-m_m1[20]*m_m2[104]+m_m1[26]*m_m2[59]);
	m_m3[178] = (-m_m1[20]*m_m2[119]+m_m1[26]*m_m2[74]+m_m1[8]*m_m2[149]);
	m_m3[198] = (m_m1[14]*m_m2[149]-m_m1[20]*m_m2[134]+m_m1[26]*m_m2[89]);
	m_m3[218] = (m_m1[2]*m_m2[179]+m_m1[32]*m_m2[14]-m_m1[8]*m_m2[164]);
	m_m3[238] = (-m_m1[14]*m_m2[164]+m_m1[2]*m_m2[194]+m_m1[32]*m_m2[29]);
	m_m3[258] = (-m_m1[14]*m_m2[179]+m_m1[32]*m_m2[44]+m_m1[8]*m_m2[194]);
	m_m3[278] = (m_m1[2]*m_m2[209]-m_m1[20]*m_m2[164]+m_m1[32]*m_m2[59]);
	m_m3[298] = (-m_m1[20]*m_m2[179]+m_m1[32]*m_m2[74]+m_m1[8]*m_m2[209]);
	m_m3[318] = (m_m1[14]*m_m2[209]-m_m1[20]*m_m2[194]+m_m1[32]*m_m2[89]);
	m_m3[338] = (m_m1[2]*m_m2[224]-m_m1[26]*m_m2[164]+m_m1[32]*m_m2[104]);
	m_m3[358] = (-m_m1[26]*m_m2[179]+m_m1[32]*m_m2[119]+m_m1[8]*m_m2[224]);
	m_m3[378] = (m_m1[14]*m_m2[224]-m_m1[26]*m_m2[194]+m_m1[32]*m_m2[134]);
	m_m3[398] = (m_m1[20]*m_m2[224]-m_m1[26]*m_m2[209]+m_m1[32]*m_m2[149]);

}
/**
 * Sets grade 3 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_3_19()
{
	m_m3[19] = (m_m1[15]*m_m2[14]+m_m1[3]*m_m2[44]-m_m1[9]*m_m2[29]);
	m_m3[39] = (m_m1[21]*m_m2[14]+m_m1[3]*m_m2[74]-m_m1[9]*m_m2[59]);
	m_m3[59] = (-m_m1[15]*m_m2[59]+m_m1[21]*m_m2[29]+m_m1[3]*m_m2[89]);
	m_m3[79] = (-m_m1[15]*m_m2[74]+m_m1[21]*m_m2[44]+m_m1[9]*m_m2[89]);
	m_m3[99] = (m_m1[27]*m_m2[14]+m_m1[3]*m_m2[119]-m_m1[9]*m_m2[104]);
	m_m3[119] = (-m_m1[15]*m_m2[104]+m_m1[27]*m_m2[29]+m_m1[3]*m_m2[134]);
	m_m3[139] = (-m_m1[15]*m_m2[119]+m_m1[27]*m_m2[44]+m_m1[9]*m_m2[134]);
	m_m3[159] = (-m_m1[21]*m_m2[104]+m_m1[27]*m_m2[59]+m_m1[3]*m_m2[149]);
	m_m3[179] = (-m_m1[21]*m_m2[119]+m_m1[27]*m_m2[74]+m_m1[9]*m_m2[149]);
	m_m3[199] = (m_m1[15]*m_m2[149]-m_m1[21]*m_m2[134]+m_m1[27]*m_m2[89]);
	m_m3[219] = (m_m1[3]*m_m2[179]+m_m1[33]*m_m2[14]-m_m1[9]*m_m2[164]);
	m_m3[239] = (-m_m1[15]*m_m2[164]+m_m1[3]*m_m2[194]+m_m1[33]*m_m2[29]);
	m_m3[259] = (-m_m1[15]*m_m2[179]+m_m1[33]*m_m2[44]+m_m1[9]*m_m2[194]);
	m_m3[279] = (-m_m1[21]*m_m2[164]+m_m1[3]*m_m2[209]+m_m1[33]*m_m2[59]);
	m_m3[299] = (-m_m1[21]*m_m2[179]+m_m1[33]*m_m2[74]+m_m1[9]*m_m2[209]);
	m_m3[319] = (m_m1[15]*m_m2[209]-m_m1[21]*m_m2[194]+m_m1[33]*m_m2[89]);
	m_m3[339] = (-m_m1[27]*m_m2[164]+m_m1[3]*m_m2[224]+m_m1[33]*m_m2[104]);
	m_m3[359] = (-m_m1[27]*m_m2[179]+m_m1[33]*m_m2[119]+m_m1[9]*m_m2[224]);
	m_m3[379] = (m_m1[15]*m_m2[224]-m_m1[27]*m_m2[194]+m_m1[33]*m_m2[134]);
	m_m3[399] = (m_m1[21]*m_m2[224]-m_m1[27]*m_m2[209]+m_m1[33]*m_m2[149]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_0()
{
	m_m4[0] = (m_m1[0]*m_m3[63]+m_m1[12]*m_m3[23]-m_m1[18]*m_m3[3]-m_m1[6]*m_m3[43]);
	m_m4[15] = (m_m1[0]*m_m3[123]+m_m1[12]*m_m3[83]-m_m1[24]*m_m3[3]-m_m1[6]*m_m3[103]);
	m_m4[30] = (m_m1[0]*m_m3[163]+m_m1[18]*m_m3[83]-m_m1[24]*m_m3[23]-m_m1[6]*m_m3[143]);
	m_m4[45] = (m_m1[0]*m_m3[183]-m_m1[12]*m_m3[143]+m_m1[18]*m_m3[103]-m_m1[24]*m_m3[43]);
	m_m4[60] = (-m_m1[12]*m_m3[163]+m_m1[18]*m_m3[123]-m_m1[24]*m_m3[63]+m_m1[6]*m_m3[183]);
	m_m4[75] = (m_m1[0]*m_m3[243]+m_m1[12]*m_m3[203]-m_m1[30]*m_m3[3]-m_m1[6]*m_m3[223]);
	m_m4[90] = (m_m1[0]*m_m3[283]+m_m1[18]*m_m3[203]-m_m1[30]*m_m3[23]-m_m1[6]*m_m3[263]);
	m_m4[105] = (m_m1[0]*m_m3[303]-m_m1[12]*m_m3[263]+m_m1[18]*m_m3[223]-m_m1[30]*m_m3[43]);
	m_m4[120] = (-m_m1[12]*m_m3[283]+m_m1[18]*m_m3[243]-m_m1[30]*m_m3[63]+m_m1[6]*m_m3[303]);
	m_m4[135] = (m_m1[0]*m_m3[343]+m_m1[24]*m_m3[203]-m_m1[30]*m_m3[83]-m_m1[6]*m_m3[323]);
	m_m4[150] = (m_m1[0]*m_m3[363]-m_m1[12]*m_m3[323]+m_m1[24]*m_m3[223]-m_m1[30]*m_m3[103]);
	m_m4[165] = (-m_m1[12]*m_m3[343]+m_m1[24]*m_m3[243]-m_m1[30]*m_m3[123]+m_m1[6]*m_m3[363]);
	m_m4[180] = (m_m1[0]*m_m3[383]-m_m1[18]*m_m3[323]+m_m1[24]*m_m3[263]-m_m1[30]*m_m3[143]);
	m_m4[195] = (-m_m1[18]*m_m3[343]+m_m1[24]*m_m3[283]-m_m1[30]*m_m3[163]+m_m1[6]*m_m3[383]);
	m_m4[210] = (m_m1[12]*m_m3[383]-m_m1[18]*m_m3[363]+m_m1[24]*m_m3[303]-m_m1[30]*m_m3[183]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_1()
{
	m_m4[1] = (m_m1[0]*m_m3[66]+m_m1[12]*m_m3[26]-m_m1[18]*m_m3[6]-m_m1[6]*m_m3[46]);
	m_m4[16] = (m_m1[0]*m_m3[126]+m_m1[12]*m_m3[86]-m_m1[24]*m_m3[6]-m_m1[6]*m_m3[106]);
	m_m4[31] = (m_m1[0]*m_m3[166]+m_m1[18]*m_m3[86]-m_m1[24]*m_m3[26]-m_m1[6]*m_m3[146]);
	m_m4[46] = (m_m1[0]*m_m3[186]-m_m1[12]*m_m3[146]+m_m1[18]*m_m3[106]-m_m1[24]*m_m3[46]);
	m_m4[61] = (-m_m1[12]*m_m3[166]+m_m1[18]*m_m3[126]-m_m1[24]*m_m3[66]+m_m1[6]*m_m3[186]);
	m_m4[76] = (m_m1[0]*m_m3[246]+m_m1[12]*m_m3[206]-m_m1[30]*m_m3[6]-m_m1[6]*m_m3[226]);
	m_m4[91] = (m_m1[0]*m_m3[286]+m_m1[18]*m_m3[206]-m_m1[30]*m_m3[26]-m_m1[6]*m_m3[266]);
	m_m4[106] = (m_m1[0]*m_m3[306]-m_m1[12]*m_m3[266]+m_m1[18]*m_m3[226]-m_m1[30]*m_m3[46]);
	m_m4[121] = (-m_m1[12]*m_m3[286]+m_m1[18]*m_m3[246]-m_m1[30]*m_m3[66]+m_m1[6]*m_m3[306]);
	m_m4[136] = (m_m1[0]*m_m3[346]+m_m1[24]*m_m3[206]-m_m1[30]*m_m3[86]-m_m1[6]*m_m3[326]);
	m_m4[151] = (m_m1[0]*m_m3[366]-m_m1[12]*m_m3[326]+m_m1[24]*m_m3[226]-m_m1[30]*m_m3[106]);
	m_m4[166] = (-m_m1[12]*m_m3[346]+m_m1[24]*m_m3[246]-m_m1[30]*m_m3[126]+m_m1[6]*m_m3[366]);
	m_m4[181] = (m_m1[0]*m_m3[386]-m_m1[18]*m_m3[326]+m_m1[24]*m_m3[266]-m_m1[30]*m_m3[146]);
	m_m4[196] = (-m_m1[18]*m_m3[346]+m_m1[24]*m_m3[286]-m_m1[30]*m_m3[166]+m_m1[6]*m_m3[386]);
	m_m4[211] = (m_m1[12]*m_m3[386]-m_m1[18]*m_m3[366]+m_m1[24]*m_m3[306]-m_m1[30]*m_m3[186]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_2()
{
	m_m4[2] = (m_m1[0]*m_m3[68]+m_m1[12]*m_m3[28]-m_m1[18]*m_m3[8]-m_m1[6]*m_m3[48]);
	m_m4[17] = (m_m1[0]*m_m3[128]+m_m1[12]*m_m3[88]-m_m1[24]*m_m3[8]-m_m1[6]*m_m3[108]);
	m_m4[32] = (m_m1[0]*m_m3[168]+m_m1[18]*m_m3[88]-m_m1[24]*m_m3[28]-m_m1[6]*m_m3[148]);
	m_m4[47] = (m_m1[0]*m_m3[188]-m_m1[12]*m_m3[148]+m_m1[18]*m_m3[108]-m_m1[24]*m_m3[48]);
	m_m4[62] = (-m_m1[12]*m_m3[168]+m_m1[18]*m_m3[128]-m_m1[24]*m_m3[68]+m_m1[6]*m_m3[188]);
	m_m4[77] = (m_m1[0]*m_m3[248]+m_m1[12]*m_m3[208]-m_m1[30]*m_m3[8]-m_m1[6]*m_m3[228]);
	m_m4[92] = (m_m1[0]*m_m3[288]+m_m1[18]*m_m3[208]-m_m1[30]*m_m3[28]-m_m1[6]*m_m3[268]);
	m_m4[107] = (m_m1[0]*m_m3[308]-m_m1[12]*m_m3[268]+m_m1[18]*m_m3[228]-m_m1[30]*m_m3[48]);
	m_m4[122] = (-m_m1[12]*m_m3[288]+m_m1[18]*m_m3[248]-m_m1[30]*m_m3[68]+m_m1[6]*m_m3[308]);
	m_m4[137] = (m_m1[0]*m_m3[348]+m_m1[24]*m_m3[208]-m_m1[30]*m_m3[88]-m_m1[6]*m_m3[328]);
	m_m4[152] = (m_m1[0]*m_m3[368]-m_m1[12]*m_m3[328]+m_m1[24]*m_m3[228]-m_m1[30]*m_m3[108]);
	m_m4[167] = (-m_m1[12]*m_m3[348]+m_m1[24]*m_m3[248]-m_m1[30]*m_m3[128]+m_m1[6]*m_m3[368]);
	m_m4[182] = (m_m1[0]*m_m3[388]-m_m1[18]*m_m3[328]+m_m1[24]*m_m3[268]-m_m1[30]*m_m3[148]);
	m_m4[197] = (-m_m1[18]*m_m3[348]+m_m1[24]*m_m3[288]-m_m1[30]*m_m3[168]+m_m1[6]*m_m3[388]);
	m_m4[212] = (m_m1[12]*m_m3[388]-m_m1[18]*m_m3[368]+m_m1[24]*m_m3[308]-m_m1[30]*m_m3[188]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_3()
{
	m_m4[3] = (m_m1[0]*m_m3[69]+m_m1[12]*m_m3[29]-m_m1[18]*m_m3[9]-m_m1[6]*m_m3[49]);
	m_m4[18] = (m_m1[0]*m_m3[129]+m_m1[12]*m_m3[89]-m_m1[24]*m_m3[9]-m_m1[6]*m_m3[109]);
	m_m4[33] = (m_m1[0]*m_m3[169]+m_m1[18]*m_m3[89]-m_m1[24]*m_m3[29]-m_m1[6]*m_m3[149]);
	m_m4[48] = (m_m1[0]*m_m3[189]-m_m1[12]*m_m3[149]+m_m1[18]*m_m3[109]-m_m1[24]*m_m3[49]);
	m_m4[63] = (-m_m1[12]*m_m3[169]+m_m1[18]*m_m3[129]-m_m1[24]*m_m3[69]+m_m1[6]*m_m3[189]);
	m_m4[78] = (m_m1[0]*m_m3[249]+m_m1[12]*m_m3[209]-m_m1[30]*m_m3[9]-m_m1[6]*m_m3[229]);
	m_m4[93] = (m_m1[0]*m_m3[289]+m_m1[18]*m_m3[209]-m_m1[30]*m_m3[29]-m_m1[6]*m_m3[269]);
	m_m4[108] = (m_m1[0]*m_m3[309]-m_m1[12]*m_m3[269]+m_m1[18]*m_m3[229]-m_m1[30]*m_m3[49]);
	m_m4[123] = (-m_m1[12]*m_m3[289]+m_m1[18]*m_m3[249]-m_m1[30]*m_m3[69]+m_m1[6]*m_m3[309]);
	m_m4[138] = (m_m1[0]*m_m3[349]+m_m1[24]*m_m3[209]-m_m1[30]*m_m3[89]-m_m1[6]*m_m3[329]);
	m_m4[153] = (m_m1[0]*m_m3[369]-m_m1[12]*m_m3[329]+m_m1[24]*m_m3[229]-m_m1[30]*m_m3[109]);
	m_m4[168] = (-m_m1[12]*m_m3[349]+m_m1[24]*m_m3[249]-m_m1[30]*m_m3[129]+m_m1[6]*m_m3[369]);
	m_m4[183] = (m_m1[0]*m_m3[389]-m_m1[18]*m_m3[329]+m_m1[24]*m_m3[269]-m_m1[30]*m_m3[149]);
	m_m4[198] = (-m_m1[18]*m_m3[349]+m_m1[24]*m_m3[289]-m_m1[30]*m_m3[169]+m_m1[6]*m_m3[389]);
	m_m4[213] = (m_m1[12]*m_m3[389]-m_m1[18]*m_m3[369]+m_m1[24]*m_m3[309]-m_m1[30]*m_m3[189]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_4()
{
	m_m4[4] = (m_m1[1]*m_m3[69]+m_m1[13]*m_m3[29]-m_m1[19]*m_m3[9]-m_m1[7]*m_m3[49]);
	m_m4[19] = (m_m1[1]*m_m3[129]+m_m1[13]*m_m3[89]-m_m1[25]*m_m3[9]-m_m1[7]*m_m3[109]);
	m_m4[34] = (m_m1[1]*m_m3[169]+m_m1[19]*m_m3[89]-m_m1[25]*m_m3[29]-m_m1[7]*m_m3[149]);
	m_m4[49] = (m_m1[1]*m_m3[189]-m_m1[13]*m_m3[149]+m_m1[19]*m_m3[109]-m_m1[25]*m_m3[49]);
	m_m4[64] = (-m_m1[13]*m_m3[169]+m_m1[19]*m_m3[129]-m_m1[25]*m_m3[69]+m_m1[7]*m_m3[189]);
	m_m4[79] = (m_m1[1]*m_m3[249]+m_m1[13]*m_m3[209]-m_m1[31]*m_m3[9]-m_m1[7]*m_m3[229]);
	m_m4[94] = (m_m1[1]*m_m3[289]+m_m1[19]*m_m3[209]-m_m1[31]*m_m3[29]-m_m1[7]*m_m3[269]);
	m_m4[109] = (m_m1[1]*m_m3[309]-m_m1[13]*m_m3[269]+m_m1[19]*m_m3[229]-m_m1[31]*m_m3[49]);
	m_m4[124] = (-m_m1[13]*m_m3[289]+m_m1[19]*m_m3[249]-m_m1[31]*m_m3[69]+m_m1[7]*m_m3[309]);
	m_m4[139] = (m_m1[1]*m_m3[349]+m_m1[25]*m_m3[209]-m_m1[31]*m_m3[89]-m_m1[7]*m_m3[329]);
	m_m4[154] = (m_m1[1]*m_m3[369]-m_m1[13]*m_m3[329]+m_m1[25]*m_m3[229]-m_m1[31]*m_m3[109]);
	m_m4[169] = (-m_m1[13]*m_m3[349]+m_m1[25]*m_m3[249]-m_m1[31]*m_m3[129]+m_m1[7]*m_m3[369]);
	m_m4[184] = (m_m1[1]*m_m3[389]-m_m1[19]*m_m3[329]+m_m1[25]*m_m3[269]-m_m1[31]*m_m3[149]);
	m_m4[199] = (-m_m1[19]*m_m3[349]+m_m1[25]*m_m3[289]-m_m1[31]*m_m3[169]+m_m1[7]*m_m3[389]);
	m_m4[214] = (m_m1[13]*m_m3[389]-m_m1[19]*m_m3[369]+m_m1[25]*m_m3[309]-m_m1[31]*m_m3[189]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_5()
{
	m_m4[5] = (m_m1[0]*m_m3[72]+m_m1[12]*m_m3[32]-m_m1[18]*m_m3[12]-m_m1[6]*m_m3[52]);
	m_m4[20] = (m_m1[0]*m_m3[132]+m_m1[12]*m_m3[92]-m_m1[24]*m_m3[12]-m_m1[6]*m_m3[112]);
	m_m4[35] = (m_m1[0]*m_m3[172]+m_m1[18]*m_m3[92]-m_m1[24]*m_m3[32]-m_m1[6]*m_m3[152]);
	m_m4[50] = (m_m1[0]*m_m3[192]-m_m1[12]*m_m3[152]+m_m1[18]*m_m3[112]-m_m1[24]*m_m3[52]);
	m_m4[65] = (-m_m1[12]*m_m3[172]+m_m1[18]*m_m3[132]-m_m1[24]*m_m3[72]+m_m1[6]*m_m3[192]);
	m_m4[80] = (m_m1[0]*m_m3[252]+m_m1[12]*m_m3[212]-m_m1[30]*m_m3[12]-m_m1[6]*m_m3[232]);
	m_m4[95] = (m_m1[0]*m_m3[292]+m_m1[18]*m_m3[212]-m_m1[30]*m_m3[32]-m_m1[6]*m_m3[272]);
	m_m4[110] = (m_m1[0]*m_m3[312]-m_m1[12]*m_m3[272]+m_m1[18]*m_m3[232]-m_m1[30]*m_m3[52]);
	m_m4[125] = (-m_m1[12]*m_m3[292]+m_m1[18]*m_m3[252]-m_m1[30]*m_m3[72]+m_m1[6]*m_m3[312]);
	m_m4[140] = (m_m1[0]*m_m3[352]+m_m1[24]*m_m3[212]-m_m1[30]*m_m3[92]-m_m1[6]*m_m3[332]);
	m_m4[155] = (m_m1[0]*m_m3[372]-m_m1[12]*m_m3[332]+m_m1[24]*m_m3[232]-m_m1[30]*m_m3[112]);
	m_m4[170] = (-m_m1[12]*m_m3[352]+m_m1[24]*m_m3[252]-m_m1[30]*m_m3[132]+m_m1[6]*m_m3[372]);
	m_m4[185] = (m_m1[0]*m_m3[392]-m_m1[18]*m_m3[332]+m_m1[24]*m_m3[272]-m_m1[30]*m_m3[152]);
	m_m4[200] = (-m_m1[18]*m_m3[352]+m_m1[24]*m_m3[292]-m_m1[30]*m_m3[172]+m_m1[6]*m_m3[392]);
	m_m4[215] = (m_m1[12]*m_m3[392]-m_m1[18]*m_m3[372]+m_m1[24]*m_m3[312]-m_m1[30]*m_m3[192]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_6()
{
	m_m4[6] = (m_m1[0]*m_m3[74]+m_m1[12]*m_m3[34]-m_m1[18]*m_m3[14]-m_m1[6]*m_m3[54]);
	m_m4[21] = (m_m1[0]*m_m3[134]+m_m1[12]*m_m3[94]-m_m1[24]*m_m3[14]-m_m1[6]*m_m3[114]);
	m_m4[36] = (m_m1[0]*m_m3[174]+m_m1[18]*m_m3[94]-m_m1[24]*m_m3[34]-m_m1[6]*m_m3[154]);
	m_m4[51] = (m_m1[0]*m_m3[194]-m_m1[12]*m_m3[154]+m_m1[18]*m_m3[114]-m_m1[24]*m_m3[54]);
	m_m4[66] = (-m_m1[12]*m_m3[174]+m_m1[18]*m_m3[134]-m_m1[24]*m_m3[74]+m_m1[6]*m_m3[194]);
	m_m4[81] = (m_m1[0]*m_m3[254]+m_m1[12]*m_m3[214]-m_m1[30]*m_m3[14]-m_m1[6]*m_m3[234]);
	m_m4[96] = (m_m1[0]*m_m3[294]+m_m1[18]*m_m3[214]-m_m1[30]*m_m3[34]-m_m1[6]*m_m3[274]);
	m_m4[111] = (m_m1[0]*m_m3[314]-m_m1[12]*m_m3[274]+m_m1[18]*m_m3[234]-m_m1[30]*m_m3[54]);
	m_m4[126] = (-m_m1[12]*m_m3[294]+m_m1[18]*m_m3[254]-m_m1[30]*m_m3[74]+m_m1[6]*m_m3[314]);
	m_m4[141] = (m_m1[0]*m_m3[354]+m_m1[24]*m_m3[214]-m_m1[30]*m_m3[94]-m_m1[6]*m_m3[334]);
	m_m4[156] = (m_m1[0]*m_m3[374]-m_m1[12]*m_m3[334]+m_m1[24]*m_m3[234]-m_m1[30]*m_m3[114]);
	m_m4[171] = (-m_m1[12]*m_m3[354]+m_m1[24]*m_m3[254]-m_m1[30]*m_m3[134]+m_m1[6]*m_m3[374]);
	m_m4[186] = (m_m1[0]*m_m3[394]-m_m1[18]*m_m3[334]+m_m1[24]*m_m3[274]-m_m1[30]*m_m3[154]);
	m_m4[201] = (-m_m1[18]*m_m3[354]+m_m1[24]*m_m3[294]-m_m1[30]*m_m3[174]+m_m1[6]*m_m3[394]);
	m_m4[216] = (m_m1[12]*m_m3[394]-m_m1[18]*m_m3[374]+m_m1[24]*m_m3[314]-m_m1[30]*m_m3[194]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_7()
{
	m_m4[7] = (m_m1[0]*m_m3[75]+m_m1[12]*m_m3[35]-m_m1[18]*m_m3[15]-m_m1[6]*m_m3[55]);
	m_m4[22] = (m_m1[0]*m_m3[135]+m_m1[12]*m_m3[95]-m_m1[24]*m_m3[15]-m_m1[6]*m_m3[115]);
	m_m4[37] = (m_m1[0]*m_m3[175]+m_m1[18]*m_m3[95]-m_m1[24]*m_m3[35]-m_m1[6]*m_m3[155]);
	m_m4[52] = (m_m1[0]*m_m3[195]-m_m1[12]*m_m3[155]+m_m1[18]*m_m3[115]-m_m1[24]*m_m3[55]);
	m_m4[67] = (-m_m1[12]*m_m3[175]+m_m1[18]*m_m3[135]-m_m1[24]*m_m3[75]+m_m1[6]*m_m3[195]);
	m_m4[82] = (m_m1[0]*m_m3[255]+m_m1[12]*m_m3[215]-m_m1[30]*m_m3[15]-m_m1[6]*m_m3[235]);
	m_m4[97] = (m_m1[0]*m_m3[295]+m_m1[18]*m_m3[215]-m_m1[30]*m_m3[35]-m_m1[6]*m_m3[275]);
	m_m4[112] = (m_m1[0]*m_m3[315]-m_m1[12]*m_m3[275]+m_m1[18]*m_m3[235]-m_m1[30]*m_m3[55]);
	m_m4[127] = (-m_m1[12]*m_m3[295]+m_m1[18]*m_m3[255]-m_m1[30]*m_m3[75]+m_m1[6]*m_m3[315]);
	m_m4[142] = (m_m1[0]*m_m3[355]+m_m1[24]*m_m3[215]-m_m1[30]*m_m3[95]-m_m1[6]*m_m3[335]);
	m_m4[157] = (m_m1[0]*m_m3[375]-m_m1[12]*m_m3[335]+m_m1[24]*m_m3[235]-m_m1[30]*m_m3[115]);
	m_m4[172] = (-m_m1[12]*m_m3[355]+m_m1[24]*m_m3[255]-m_m1[30]*m_m3[135]+m_m1[6]*m_m3[375]);
	m_m4[187] = (m_m1[0]*m_m3[395]-m_m1[18]*m_m3[335]+m_m1[24]*m_m3[275]-m_m1[30]*m_m3[155]);
	m_m4[202] = (-m_m1[18]*m_m3[355]+m_m1[24]*m_m3[295]-m_m1[30]*m_m3[175]+m_m1[6]*m_m3[395]);
	m_m4[217] = (m_m1[12]*m_m3[395]-m_m1[18]*m_m3[375]+m_m1[24]*m_m3[315]-m_m1[30]*m_m3[195]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_8()
{
	m_m4[8] = (m_m1[1]*m_m3[75]+m_m1[13]*m_m3[35]-m_m1[19]*m_m3[15]-m_m1[7]*m_m3[55]);
	m_m4[23] = (m_m1[1]*m_m3[135]+m_m1[13]*m_m3[95]-m_m1[25]*m_m3[15]-m_m1[7]*m_m3[115]);
	m_m4[38] = (m_m1[1]*m_m3[175]+m_m1[19]*m_m3[95]-m_m1[25]*m_m3[35]-m_m1[7]*m_m3[155]);
	m_m4[53] = (m_m1[1]*m_m3[195]-m_m1[13]*m_m3[155]+m_m1[19]*m_m3[115]-m_m1[25]*m_m3[55]);
	m_m4[68] = (-m_m1[13]*m_m3[175]+m_m1[19]*m_m3[135]-m_m1[25]*m_m3[75]+m_m1[7]*m_m3[195]);
	m_m4[83] = (m_m1[1]*m_m3[255]+m_m1[13]*m_m3[215]-m_m1[31]*m_m3[15]-m_m1[7]*m_m3[235]);
	m_m4[98] = (m_m1[1]*m_m3[295]+m_m1[19]*m_m3[215]-m_m1[31]*m_m3[35]-m_m1[7]*m_m3[275]);
	m_m4[113] = (m_m1[1]*m_m3[315]-m_m1[13]*m_m3[275]+m_m1[19]*m_m3[235]-m_m1[31]*m_m3[55]);
	m_m4[128] = (-m_m1[13]*m_m3[295]+m_m1[19]*m_m3[255]-m_m1[31]*m_m3[75]+m_m1[7]*m_m3[315]);
	m_m4[143] = (m_m1[1]*m_m3[355]+m_m1[25]*m_m3[215]-m_m1[31]*m_m3[95]-m_m1[7]*m_m3[335]);
	m_m4[158] = (m_m1[1]*m_m3[375]-m_m1[13]*m_m3[335]+m_m1[25]*m_m3[235]-m_m1[31]*m_m3[115]);
	m_m4[173] = (-m_m1[13]*m_m3[355]+m_m1[25]*m_m3[255]-m_m1[31]*m_m3[135]+m_m1[7]*m_m3[375]);
	m_m4[188] = (m_m1[1]*m_m3[395]-m_m1[19]*m_m3[335]+m_m1[25]*m_m3[275]-m_m1[31]*m_m3[155]);
	m_m4[203] = (-m_m1[19]*m_m3[355]+m_m1[25]*m_m3[295]-m_m1[31]*m_m3[175]+m_m1[7]*m_m3[395]);
	m_m4[218] = (m_m1[13]*m_m3[395]-m_m1[19]*m_m3[375]+m_m1[25]*m_m3[315]-m_m1[31]*m_m3[195]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_9()
{
	m_m4[9] = (m_m1[0]*m_m3[77]+m_m1[12]*m_m3[37]-m_m1[18]*m_m3[17]-m_m1[6]*m_m3[57]);
	m_m4[24] = (m_m1[0]*m_m3[137]+m_m1[12]*m_m3[97]-m_m1[24]*m_m3[17]-m_m1[6]*m_m3[117]);
	m_m4[39] = (m_m1[0]*m_m3[177]+m_m1[18]*m_m3[97]-m_m1[24]*m_m3[37]-m_m1[6]*m_m3[157]);
	m_m4[54] = (m_m1[0]*m_m3[197]-m_m1[12]*m_m3[157]+m_m1[18]*m_m3[117]-m_m1[24]*m_m3[57]);
	m_m4[69] = (-m_m1[12]*m_m3[177]+m_m1[18]*m_m3[137]-m_m1[24]*m_m3[77]+m_m1[6]*m_m3[197]);
	m_m4[84] = (m_m1[0]*m_m3[257]+m_m1[12]*m_m3[217]-m_m1[30]*m_m3[17]-m_m1[6]*m_m3[237]);
	m_m4[99] = (m_m1[0]*m_m3[297]+m_m1[18]*m_m3[217]-m_m1[30]*m_m3[37]-m_m1[6]*m_m3[277]);
	m_m4[114] = (m_m1[0]*m_m3[317]-m_m1[12]*m_m3[277]+m_m1[18]*m_m3[237]-m_m1[30]*m_m3[57]);
	m_m4[129] = (-m_m1[12]*m_m3[297]+m_m1[18]*m_m3[257]-m_m1[30]*m_m3[77]+m_m1[6]*m_m3[317]);
	m_m4[144] = (m_m1[0]*m_m3[357]+m_m1[24]*m_m3[217]-m_m1[30]*m_m3[97]-m_m1[6]*m_m3[337]);
	m_m4[159] = (m_m1[0]*m_m3[377]-m_m1[12]*m_m3[337]+m_m1[24]*m_m3[237]-m_m1[30]*m_m3[117]);
	m_m4[174] = (-m_m1[12]*m_m3[357]+m_m1[24]*m_m3[257]-m_m1[30]*m_m3[137]+m_m1[6]*m_m3[377]);
	m_m4[189] = (m_m1[0]*m_m3[397]-m_m1[18]*m_m3[337]+m_m1[24]*m_m3[277]-m_m1[30]*m_m3[157]);
	m_m4[204] = (-m_m1[18]*m_m3[357]+m_m1[24]*m_m3[297]-m_m1[30]*m_m3[177]+m_m1[6]*m_m3[397]);
	m_m4[219] = (m_m1[12]*m_m3[397]-m_m1[18]*m_m3[377]+m_m1[24]*m_m3[317]-m_m1[30]*m_m3[197]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_10()
{
	m_m4[10] = (m_m1[0]*m_m3[78]+m_m1[12]*m_m3[38]-m_m1[18]*m_m3[18]-m_m1[6]*m_m3[58]);
	m_m4[25] = (m_m1[0]*m_m3[138]+m_m1[12]*m_m3[98]-m_m1[24]*m_m3[18]-m_m1[6]*m_m3[118]);
	m_m4[40] = (m_m1[0]*m_m3[178]+m_m1[18]*m_m3[98]-m_m1[24]*m_m3[38]-m_m1[6]*m_m3[158]);
	m_m4[55] = (m_m1[0]*m_m3[198]-m_m1[12]*m_m3[158]+m_m1[18]*m_m3[118]-m_m1[24]*m_m3[58]);
	m_m4[70] = (-m_m1[12]*m_m3[178]+m_m1[18]*m_m3[138]-m_m1[24]*m_m3[78]+m_m1[6]*m_m3[198]);
	m_m4[85] = (m_m1[0]*m_m3[258]+m_m1[12]*m_m3[218]-m_m1[30]*m_m3[18]-m_m1[6]*m_m3[238]);
	m_m4[100] = (m_m1[0]*m_m3[298]+m_m1[18]*m_m3[218]-m_m1[30]*m_m3[38]-m_m1[6]*m_m3[278]);
	m_m4[115] = (m_m1[0]*m_m3[318]-m_m1[12]*m_m3[278]+m_m1[18]*m_m3[238]-m_m1[30]*m_m3[58]);
	m_m4[130] = (-m_m1[12]*m_m3[298]+m_m1[18]*m_m3[258]-m_m1[30]*m_m3[78]+m_m1[6]*m_m3[318]);
	m_m4[145] = (m_m1[0]*m_m3[358]+m_m1[24]*m_m3[218]-m_m1[30]*m_m3[98]-m_m1[6]*m_m3[338]);
	m_m4[160] = (m_m1[0]*m_m3[378]-m_m1[12]*m_m3[338]+m_m1[24]*m_m3[238]-m_m1[30]*m_m3[118]);
	m_m4[175] = (-m_m1[12]*m_m3[358]+m_m1[24]*m_m3[258]-m_m1[30]*m_m3[138]+m_m1[6]*m_m3[378]);
	m_m4[190] = (m_m1[0]*m_m3[398]-m_m1[18]*m_m3[338]+m_m1[24]*m_m3[278]-m_m1[30]*m_m3[158]);
	m_m4[205] = (-m_m1[18]*m_m3[358]+m_m1[24]*m_m3[298]-m_m1[30]*m_m3[178]+m_m1[6]*m_m3[398]);
	m_m4[220] = (m_m1[12]*m_m3[398]-m_m1[18]*m_m3[378]+m_m1[24]*m_m3[318]-m_m1[30]*m_m3[198]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_11()
{
	m_m4[11] = (m_m1[1]*m_m3[78]+m_m1[13]*m_m3[38]-m_m1[19]*m_m3[18]-m_m1[7]*m_m3[58]);
	m_m4[26] = (m_m1[1]*m_m3[138]+m_m1[13]*m_m3[98]-m_m1[25]*m_m3[18]-m_m1[7]*m_m3[118]);
	m_m4[41] = (m_m1[1]*m_m3[178]+m_m1[19]*m_m3[98]-m_m1[25]*m_m3[38]-m_m1[7]*m_m3[158]);
	m_m4[56] = (m_m1[1]*m_m3[198]-m_m1[13]*m_m3[158]+m_m1[19]*m_m3[118]-m_m1[25]*m_m3[58]);
	m_m4[71] = (-m_m1[13]*m_m3[178]+m_m1[19]*m_m3[138]-m_m1[25]*m_m3[78]+m_m1[7]*m_m3[198]);
	m_m4[86] = (m_m1[1]*m_m3[258]+m_m1[13]*m_m3[218]-m_m1[31]*m_m3[18]-m_m1[7]*m_m3[238]);
	m_m4[101] = (m_m1[1]*m_m3[298]+m_m1[19]*m_m3[218]-m_m1[31]*m_m3[38]-m_m1[7]*m_m3[278]);
	m_m4[116] = (m_m1[1]*m_m3[318]-m_m1[13]*m_m3[278]+m_m1[19]*m_m3[238]-m_m1[31]*m_m3[58]);
	m_m4[131] = (-m_m1[13]*m_m3[298]+m_m1[19]*m_m3[258]-m_m1[31]*m_m3[78]+m_m1[7]*m_m3[318]);
	m_m4[146] = (m_m1[1]*m_m3[358]+m_m1[25]*m_m3[218]-m_m1[31]*m_m3[98]-m_m1[7]*m_m3[338]);
	m_m4[161] = (m_m1[1]*m_m3[378]-m_m1[13]*m_m3[338]+m_m1[25]*m_m3[238]-m_m1[31]*m_m3[118]);
	m_m4[176] = (-m_m1[13]*m_m3[358]+m_m1[25]*m_m3[258]-m_m1[31]*m_m3[138]+m_m1[7]*m_m3[378]);
	m_m4[191] = (m_m1[1]*m_m3[398]-m_m1[19]*m_m3[338]+m_m1[25]*m_m3[278]-m_m1[31]*m_m3[158]);
	m_m4[206] = (-m_m1[19]*m_m3[358]+m_m1[25]*m_m3[298]-m_m1[31]*m_m3[178]+m_m1[7]*m_m3[398]);
	m_m4[221] = (m_m1[13]*m_m3[398]-m_m1[19]*m_m3[378]+m_m1[25]*m_m3[318]-m_m1[31]*m_m3[198]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_12()
{
	m_m4[12] = (m_m1[0]*m_m3[79]+m_m1[12]*m_m3[39]-m_m1[18]*m_m3[19]-m_m1[6]*m_m3[59]);
	m_m4[27] = (m_m1[0]*m_m3[139]+m_m1[12]*m_m3[99]-m_m1[24]*m_m3[19]-m_m1[6]*m_m3[119]);
	m_m4[42] = (m_m1[0]*m_m3[179]+m_m1[18]*m_m3[99]-m_m1[24]*m_m3[39]-m_m1[6]*m_m3[159]);
	m_m4[57] = (m_m1[0]*m_m3[199]-m_m1[12]*m_m3[159]+m_m1[18]*m_m3[119]-m_m1[24]*m_m3[59]);
	m_m4[72] = (-m_m1[12]*m_m3[179]+m_m1[18]*m_m3[139]-m_m1[24]*m_m3[79]+m_m1[6]*m_m3[199]);
	m_m4[87] = (m_m1[0]*m_m3[259]+m_m1[12]*m_m3[219]-m_m1[30]*m_m3[19]-m_m1[6]*m_m3[239]);
	m_m4[102] = (m_m1[0]*m_m3[299]+m_m1[18]*m_m3[219]-m_m1[30]*m_m3[39]-m_m1[6]*m_m3[279]);
	m_m4[117] = (m_m1[0]*m_m3[319]-m_m1[12]*m_m3[279]+m_m1[18]*m_m3[239]-m_m1[30]*m_m3[59]);
	m_m4[132] = (-m_m1[12]*m_m3[299]+m_m1[18]*m_m3[259]-m_m1[30]*m_m3[79]+m_m1[6]*m_m3[319]);
	m_m4[147] = (m_m1[0]*m_m3[359]+m_m1[24]*m_m3[219]-m_m1[30]*m_m3[99]-m_m1[6]*m_m3[339]);
	m_m4[162] = (m_m1[0]*m_m3[379]-m_m1[12]*m_m3[339]+m_m1[24]*m_m3[239]-m_m1[30]*m_m3[119]);
	m_m4[177] = (-m_m1[12]*m_m3[359]+m_m1[24]*m_m3[259]-m_m1[30]*m_m3[139]+m_m1[6]*m_m3[379]);
	m_m4[192] = (m_m1[0]*m_m3[399]-m_m1[18]*m_m3[339]+m_m1[24]*m_m3[279]-m_m1[30]*m_m3[159]);
	m_m4[207] = (-m_m1[18]*m_m3[359]+m_m1[24]*m_m3[299]-m_m1[30]*m_m3[179]+m_m1[6]*m_m3[399]);
	m_m4[222] = (m_m1[12]*m_m3[399]-m_m1[18]*m_m3[379]+m_m1[24]*m_m3[319]-m_m1[30]*m_m3[199]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_13()
{
	m_m4[13] = (m_m1[1]*m_m3[79]+m_m1[13]*m_m3[39]-m_m1[19]*m_m3[19]-m_m1[7]*m_m3[59]);
	m_m4[28] = (m_m1[1]*m_m3[139]+m_m1[13]*m_m3[99]-m_m1[25]*m_m3[19]-m_m1[7]*m_m3[119]);
	m_m4[43] = (m_m1[1]*m_m3[179]+m_m1[19]*m_m3[99]-m_m1[25]*m_m3[39]-m_m1[7]*m_m3[159]);
	m_m4[58] = (m_m1[1]*m_m3[199]-m_m1[13]*m_m3[159]+m_m1[19]*m_m3[119]-m_m1[25]*m_m3[59]);
	m_m4[73] = (-m_m1[13]*m_m3[179]+m_m1[19]*m_m3[139]-m_m1[25]*m_m3[79]+m_m1[7]*m_m3[199]);
	m_m4[88] = (m_m1[1]*m_m3[259]+m_m1[13]*m_m3[219]-m_m1[31]*m_m3[19]-m_m1[7]*m_m3[239]);
	m_m4[103] = (m_m1[1]*m_m3[299]+m_m1[19]*m_m3[219]-m_m1[31]*m_m3[39]-m_m1[7]*m_m3[279]);
	m_m4[118] = (m_m1[1]*m_m3[319]-m_m1[13]*m_m3[279]+m_m1[19]*m_m3[239]-m_m1[31]*m_m3[59]);
	m_m4[133] = (-m_m1[13]*m_m3[299]+m_m1[19]*m_m3[259]-m_m1[31]*m_m3[79]+m_m1[7]*m_m3[319]);
	m_m4[148] = (m_m1[1]*m_m3[359]+m_m1[25]*m_m3[219]-m_m1[31]*m_m3[99]-m_m1[7]*m_m3[339]);
	m_m4[163] = (m_m1[1]*m_m3[379]-m_m1[13]*m_m3[339]+m_m1[25]*m_m3[239]-m_m1[31]*m_m3[119]);
	m_m4[178] = (-m_m1[13]*m_m3[359]+m_m1[25]*m_m3[259]-m_m1[31]*m_m3[139]+m_m1[7]*m_m3[379]);
	m_m4[193] = (m_m1[1]*m_m3[399]-m_m1[19]*m_m3[339]+m_m1[25]*m_m3[279]-m_m1[31]*m_m3[159]);
	m_m4[208] = (-m_m1[19]*m_m3[359]+m_m1[25]*m_m3[299]-m_m1[31]*m_m3[179]+m_m1[7]*m_m3[399]);
	m_m4[223] = (m_m1[13]*m_m3[399]-m_m1[19]*m_m3[379]+m_m1[25]*m_m3[319]-m_m1[31]*m_m3[199]);

}
/**
 * Sets grade 4 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_4_14()
{
	m_m4[14] = (m_m1[14]*m_m3[39]+m_m1[2]*m_m3[79]-m_m1[20]*m_m3[19]-m_m1[8]*m_m3[59]);
	m_m4[29] = (m_m1[14]*m_m3[99]+m_m1[2]*m_m3[139]-m_m1[26]*m_m3[19]-m_m1[8]*m_m3[119]);
	m_m4[44] = (m_m1[2]*m_m3[179]+m_m1[20]*m_m3[99]-m_m1[26]*m_m3[39]-m_m1[8]*m_m3[159]);
	m_m4[59] = (-m_m1[14]*m_m3[159]+m_m1[2]*m_m3[199]+m_m1[20]*m_m3[119]-m_m1[26]*m_m3[59]);
	m_m4[74] = (-m_m1[14]*m_m3[179]+m_m1[20]*m_m3[139]-m_m1[26]*m_m3[79]+m_m1[8]*m_m3[199]);
	m_m4[89] = (m_m1[14]*m_m3[219]+m_m1[2]*m_m3[259]-m_m1[32]*m_m3[19]-m_m1[8]*m_m3[239]);
	m_m4[104] = (m_m1[2]*m_m3[299]+m_m1[20]*m_m3[219]-m_m1[32]*m_m3[39]-m_m1[8]*m_m3[279]);
	m_m4[119] = (-m_m1[14]*m_m3[279]+m_m1[2]*m_m3[319]+m_m1[20]*m_m3[239]-m_m1[32]*m_m3[59]);
	m_m4[134] = (-m_m1[14]*m_m3[299]+m_m1[20]*m_m3[259]-m_m1[32]*m_m3[79]+m_m1[8]*m_m3[319]);
	m_m4[149] = (m_m1[2]*m_m3[359]+m_m1[26]*m_m3[219]-m_m1[32]*m_m3[99]-m_m1[8]*m_m3[339]);
	m_m4[164] = (-m_m1[14]*m_m3[339]+m_m1[2]*m_m3[379]+m_m1[26]*m_m3[239]-m_m1[32]*m_m3[119]);
	m_m4[179] = (-m_m1[14]*m_m3[359]+m_m1[26]*m_m3[259]-m_m1[32]*m_m3[139]+m_m1[8]*m_m3[379]);
	m_m4[194] = (m_m1[2]*m_m3[399]-m_m1[20]*m_m3[339]+m_m1[26]*m_m3[279]-m_m1[32]*m_m3[159]);
	m_m4[209] = (-m_m1[20]*m_m3[359]+m_m1[26]*m_m3[299]-m_m1[32]*m_m3[179]+m_m1[8]*m_m3[399]);
	m_m4[224] = (m_m1[14]*m_m3[399]-m_m1[20]*m_m3[379]+m_m1[26]*m_m3[319]-m_m1[32]*m_m3[199]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_0()
{
	m_m5[0] = (m_m1[0]*m_m4[64]+m_m1[12]*m_m4[34]-m_m1[18]*m_m4[19]+m_m1[24]*m_m4[4]-m_m1[6]*m_m4[49]);
	m_m5[6] = (m_m1[0]*m_m4[124]+m_m1[12]*m_m4[94]-m_m1[18]*m_m4[79]+m_m1[30]*m_m4[4]-m_m1[6]*m_m4[109]);
	m_m5[12] = (m_m1[0]*m_m4[169]+m_m1[12]*m_m4[139]-m_m1[24]*m_m4[79]+m_m1[30]*m_m4[19]-m_m1[6]*m_m4[154]);
	m_m5[18] = (m_m1[0]*m_m4[199]+m_m1[18]*m_m4[139]-m_m1[24]*m_m4[94]+m_m1[30]*m_m4[34]-m_m1[6]*m_m4[184]);
	m_m5[24] = (m_m1[0]*m_m4[214]-m_m1[12]*m_m4[184]+m_m1[18]*m_m4[154]-m_m1[24]*m_m4[109]+m_m1[30]*m_m4[49]);
	m_m5[30] = (-m_m1[12]*m_m4[199]+m_m1[18]*m_m4[169]-m_m1[24]*m_m4[124]+m_m1[30]*m_m4[64]+m_m1[6]*m_m4[214]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_1()
{
	m_m5[1] = (m_m1[0]*m_m4[68]+m_m1[12]*m_m4[38]-m_m1[18]*m_m4[23]+m_m1[24]*m_m4[8]-m_m1[6]*m_m4[53]);
	m_m5[7] = (m_m1[0]*m_m4[128]+m_m1[12]*m_m4[98]-m_m1[18]*m_m4[83]+m_m1[30]*m_m4[8]-m_m1[6]*m_m4[113]);
	m_m5[13] = (m_m1[0]*m_m4[173]+m_m1[12]*m_m4[143]-m_m1[24]*m_m4[83]+m_m1[30]*m_m4[23]-m_m1[6]*m_m4[158]);
	m_m5[19] = (m_m1[0]*m_m4[203]+m_m1[18]*m_m4[143]-m_m1[24]*m_m4[98]+m_m1[30]*m_m4[38]-m_m1[6]*m_m4[188]);
	m_m5[25] = (m_m1[0]*m_m4[218]-m_m1[12]*m_m4[188]+m_m1[18]*m_m4[158]-m_m1[24]*m_m4[113]+m_m1[30]*m_m4[53]);
	m_m5[31] = (-m_m1[12]*m_m4[203]+m_m1[18]*m_m4[173]-m_m1[24]*m_m4[128]+m_m1[30]*m_m4[68]+m_m1[6]*m_m4[218]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_2()
{
	m_m5[2] = (m_m1[0]*m_m4[71]+m_m1[12]*m_m4[41]-m_m1[18]*m_m4[26]+m_m1[24]*m_m4[11]-m_m1[6]*m_m4[56]);
	m_m5[8] = (m_m1[0]*m_m4[131]+m_m1[12]*m_m4[101]-m_m1[18]*m_m4[86]+m_m1[30]*m_m4[11]-m_m1[6]*m_m4[116]);
	m_m5[14] = (m_m1[0]*m_m4[176]+m_m1[12]*m_m4[146]-m_m1[24]*m_m4[86]+m_m1[30]*m_m4[26]-m_m1[6]*m_m4[161]);
	m_m5[20] = (m_m1[0]*m_m4[206]+m_m1[18]*m_m4[146]-m_m1[24]*m_m4[101]+m_m1[30]*m_m4[41]-m_m1[6]*m_m4[191]);
	m_m5[26] = (m_m1[0]*m_m4[221]-m_m1[12]*m_m4[191]+m_m1[18]*m_m4[161]-m_m1[24]*m_m4[116]+m_m1[30]*m_m4[56]);
	m_m5[32] = (-m_m1[12]*m_m4[206]+m_m1[18]*m_m4[176]-m_m1[24]*m_m4[131]+m_m1[30]*m_m4[71]+m_m1[6]*m_m4[221]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_3()
{
	m_m5[3] = (m_m1[0]*m_m4[73]+m_m1[12]*m_m4[43]-m_m1[18]*m_m4[28]+m_m1[24]*m_m4[13]-m_m1[6]*m_m4[58]);
	m_m5[9] = (m_m1[0]*m_m4[133]+m_m1[12]*m_m4[103]-m_m1[18]*m_m4[88]+m_m1[30]*m_m4[13]-m_m1[6]*m_m4[118]);
	m_m5[15] = (m_m1[0]*m_m4[178]+m_m1[12]*m_m4[148]-m_m1[24]*m_m4[88]+m_m1[30]*m_m4[28]-m_m1[6]*m_m4[163]);
	m_m5[21] = (m_m1[0]*m_m4[208]+m_m1[18]*m_m4[148]-m_m1[24]*m_m4[103]+m_m1[30]*m_m4[43]-m_m1[6]*m_m4[193]);
	m_m5[27] = (m_m1[0]*m_m4[223]-m_m1[12]*m_m4[193]+m_m1[18]*m_m4[163]-m_m1[24]*m_m4[118]+m_m1[30]*m_m4[58]);
	m_m5[33] = (-m_m1[12]*m_m4[208]+m_m1[18]*m_m4[178]-m_m1[24]*m_m4[133]+m_m1[30]*m_m4[73]+m_m1[6]*m_m4[223]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_4()
{
	m_m5[4] = (m_m1[0]*m_m4[74]+m_m1[12]*m_m4[44]-m_m1[18]*m_m4[29]+m_m1[24]*m_m4[14]-m_m1[6]*m_m4[59]);
	m_m5[10] = (m_m1[0]*m_m4[134]+m_m1[12]*m_m4[104]-m_m1[18]*m_m4[89]+m_m1[30]*m_m4[14]-m_m1[6]*m_m4[119]);
	m_m5[16] = (m_m1[0]*m_m4[179]+m_m1[12]*m_m4[149]-m_m1[24]*m_m4[89]+m_m1[30]*m_m4[29]-m_m1[6]*m_m4[164]);
	m_m5[22] = (m_m1[0]*m_m4[209]+m_m1[18]*m_m4[149]-m_m1[24]*m_m4[104]+m_m1[30]*m_m4[44]-m_m1[6]*m_m4[194]);
	m_m5[28] = (m_m1[0]*m_m4[224]-m_m1[12]*m_m4[194]+m_m1[18]*m_m4[164]-m_m1[24]*m_m4[119]+m_m1[30]*m_m4[59]);
	m_m5[34] = (-m_m1[12]*m_m4[209]+m_m1[18]*m_m4[179]-m_m1[24]*m_m4[134]+m_m1[30]*m_m4[74]+m_m1[6]*m_m4[224]);

}
/**
 * Sets grade 5 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_5_5()
{
	m_m5[5] = (m_m1[1]*m_m4[74]+m_m1[13]*m_m4[44]-m_m1[19]*m_m4[29]+m_m1[25]*m_m4[14]-m_m1[7]*m_m4[59]);
	m_m5[11] = (m_m1[1]*m_m4[134]+m_m1[13]*m_m4[104]-m_m1[19]*m_m4[89]+m_m1[31]*m_m4[14]-m_m1[7]*m_m4[119]);
	m_m5[17] = (m_m1[1]*m_m4[179]+m_m1[13]*m_m4[149]-m_m1[25]*m_m4[89]+m_m1[31]*m_m4[29]-m_m1[7]*m_m4[164]);
	m_m5[23] = (m_m1[1]*m_m4[209]+m_m1[19]*m_m4[149]-m_m1[25]*m_m4[104]+m_m1[31]*m_m4[44]-m_m1[7]*m_m4[194]);
	m_m5[29] = (m_m1[1]*m_m4[224]-m_m1[13]*m_m4[194]+m_m1[19]*m_m4[164]-m_m1[25]*m_m4[119]+m_m1[31]*m_m4[59]);
	m_m5[35] = (-m_m1[13]*m_m4[209]+m_m1[19]*m_m4[179]-m_m1[25]*m_m4[134]+m_m1[31]*m_m4[74]+m_m1[7]*m_m4[224]);

}
/**
 * Sets grade 6 part of outermorphism matrix based on lower grade parts.
 */
public final void set_grade_6_0()
{
	m_m6[0] = (m_m1[0]*m_m5[35]+m_m1[12]*m_m5[23]-m_m1[18]*m_m5[17]+m_m1[24]*m_m5[11]-m_m1[30]*m_m5[5]-m_m1[6]*m_m5[29]);

}
/**
 * Sets om from images of the domain vectors.
 */
public final void set(final oddVersor ie01, final oddVersor ie02, final oddVersor ie03, final oddVersor ie12, final oddVersor ie23, final oddVersor ie31)
{
	m_m1[0] = ie01.m_e01;
	m_m1[6] = ie01.m_e02;
	m_m1[12] = ie01.m_e03;
	m_m1[18] = ie01.m_e12;
	m_m1[24] = ie01.m_e23;
	m_m1[30] = ie01.m_e31;

	m_m1[1] = ie02.m_e01;
	m_m1[7] = ie02.m_e02;
	m_m1[13] = ie02.m_e03;
	m_m1[19] = ie02.m_e12;
	m_m1[25] = ie02.m_e23;
	m_m1[31] = ie02.m_e31;

	m_m1[2] = ie03.m_e01;
	m_m1[8] = ie03.m_e02;
	m_m1[14] = ie03.m_e03;
	m_m1[20] = ie03.m_e12;
	m_m1[26] = ie03.m_e23;
	m_m1[32] = ie03.m_e31;

	m_m1[3] = ie12.m_e01;
	m_m1[9] = ie12.m_e02;
	m_m1[15] = ie12.m_e03;
	m_m1[21] = ie12.m_e12;
	m_m1[27] = ie12.m_e23;
	m_m1[33] = ie12.m_e31;

	m_m1[4] = ie23.m_e01;
	m_m1[10] = ie23.m_e02;
	m_m1[16] = ie23.m_e03;
	m_m1[22] = ie23.m_e12;
	m_m1[28] = ie23.m_e23;
	m_m1[34] = ie23.m_e31;

	m_m1[5] = ie31.m_e01;
	m_m1[11] = ie31.m_e02;
	m_m1[17] = ie31.m_e03;
	m_m1[23] = ie31.m_e12;
	m_m1[29] = ie31.m_e23;
	m_m1[35] = ie31.m_e31;

	set_grade_2_0();
	set_grade_2_1();
	set_grade_2_2();
	set_grade_2_3();
	set_grade_2_4();
	set_grade_2_5();
	set_grade_2_6();
	set_grade_2_7();
	set_grade_2_8();
	set_grade_2_9();
	set_grade_2_10();
	set_grade_2_11();
	set_grade_2_12();
	set_grade_2_13();
	set_grade_2_14();
	set_grade_3_0();
	set_grade_3_1();
	set_grade_3_2();
	set_grade_3_3();
	set_grade_3_4();
	set_grade_3_5();
	set_grade_3_6();
	set_grade_3_7();
	set_grade_3_8();
	set_grade_3_9();
	set_grade_3_10();
	set_grade_3_11();
	set_grade_3_12();
	set_grade_3_13();
	set_grade_3_14();
	set_grade_3_15();
	set_grade_3_16();
	set_grade_3_17();
	set_grade_3_18();
	set_grade_3_19();
	set_grade_4_0();
	set_grade_4_1();
	set_grade_4_2();
	set_grade_4_3();
	set_grade_4_4();
	set_grade_4_5();
	set_grade_4_6();
	set_grade_4_7();
	set_grade_4_8();
	set_grade_4_9();
	set_grade_4_10();
	set_grade_4_11();
	set_grade_4_12();
	set_grade_4_13();
	set_grade_4_14();
	set_grade_5_0();
	set_grade_5_1();
	set_grade_5_2();
	set_grade_5_3();
	set_grade_5_4();
	set_grade_5_5();
	set_grade_6_0();
}
/**
 * Sets om from a matrix
 */
public final void set(final float[] M)
{
	m_m1[0] = M[0];
	m_m1[6] = M[6];
	m_m1[12] = M[12];
	m_m1[18] = M[18];
	m_m1[24] = M[24];
	m_m1[30] = M[30];

	m_m1[1] = M[1];
	m_m1[7] = M[7];
	m_m1[13] = M[13];
	m_m1[19] = M[19];
	m_m1[25] = M[25];
	m_m1[31] = M[31];

	m_m1[2] = M[2];
	m_m1[8] = M[8];
	m_m1[14] = M[14];
	m_m1[20] = M[20];
	m_m1[26] = M[26];
	m_m1[32] = M[32];

	m_m1[3] = M[3];
	m_m1[9] = M[9];
	m_m1[15] = M[15];
	m_m1[21] = M[21];
	m_m1[27] = M[27];
	m_m1[33] = M[33];

	m_m1[4] = M[4];
	m_m1[10] = M[10];
	m_m1[16] = M[16];
	m_m1[22] = M[22];
	m_m1[28] = M[28];
	m_m1[34] = M[34];

	m_m1[5] = M[5];
	m_m1[11] = M[11];
	m_m1[17] = M[17];
	m_m1[23] = M[23];
	m_m1[29] = M[29];
	m_m1[35] = M[35];

	set_grade_2_0();
	set_grade_2_1();
	set_grade_2_2();
	set_grade_2_3();
	set_grade_2_4();
	set_grade_2_5();
	set_grade_2_6();
	set_grade_2_7();
	set_grade_2_8();
	set_grade_2_9();
	set_grade_2_10();
	set_grade_2_11();
	set_grade_2_12();
	set_grade_2_13();
	set_grade_2_14();
	set_grade_3_0();
	set_grade_3_1();
	set_grade_3_2();
	set_grade_3_3();
	set_grade_3_4();
	set_grade_3_5();
	set_grade_3_6();
	set_grade_3_7();
	set_grade_3_8();
	set_grade_3_9();
	set_grade_3_10();
	set_grade_3_11();
	set_grade_3_12();
	set_grade_3_13();
	set_grade_3_14();
	set_grade_3_15();
	set_grade_3_16();
	set_grade_3_17();
	set_grade_3_18();
	set_grade_3_19();
	set_grade_4_0();
	set_grade_4_1();
	set_grade_4_2();
	set_grade_4_3();
	set_grade_4_4();
	set_grade_4_5();
	set_grade_4_6();
	set_grade_4_7();
	set_grade_4_8();
	set_grade_4_9();
	set_grade_4_10();
	set_grade_4_11();
	set_grade_4_12();
	set_grade_4_13();
	set_grade_4_14();
	set_grade_5_0();
	set_grade_5_1();
	set_grade_5_2();
	set_grade_5_3();
	set_grade_5_4();
	set_grade_5_5();
	set_grade_6_0();
}
} // end of class om
