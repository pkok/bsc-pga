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
 * This class can hold a specialized multivector of type mixedPencil.
 * 
 * The coordinates are stored in type float.
 * 
 * The variable non-zero coordinates are:
 *   - coordinate e01^e12  (array index: E01_E12 = 0)
 *   - coordinate e01^e23  (array index: E01_E23 = 1)
 *   - coordinate e01^e31  (array index: E01_E31 = 2)
 *   - coordinate e02^e12  (array index: E02_E12 = 3)
 *   - coordinate e02^e23  (array index: E02_E23 = 4)
 *   - coordinate e02^e31  (array index: E02_E31 = 5)
 *   - coordinate e03^e12  (array index: E03_E12 = 6)
 *   - coordinate e03^e23  (array index: E03_E23 = 7)
 *   - coordinate e03^e31  (array index: E03_E31 = 8)
 * 
 * The type has no constant coordinates.
 * 
 * 
 */
public class mixedPencil  implements  mv_if
{ 
	/**
	 * The e01^e12 coordinate.
	 */
	protected float m_e01_e12;
	/**
	 * The e01^e23 coordinate.
	 */
	protected float m_e01_e23;
	/**
	 * The e01^e31 coordinate.
	 */
	protected float m_e01_e31;
	/**
	 * The e02^e12 coordinate.
	 */
	protected float m_e02_e12;
	/**
	 * The e02^e23 coordinate.
	 */
	protected float m_e02_e23;
	/**
	 * The e02^e31 coordinate.
	 */
	protected float m_e02_e31;
	/**
	 * The e03^e12 coordinate.
	 */
	protected float m_e03_e12;
	/**
	 * The e03^e23 coordinate.
	 */
	protected float m_e03_e23;
	/**
	 * The e03^e31 coordinate.
	 */
	protected float m_e03_e31;
	/**
	 * Array indices of mixedPencil coordinates.
	 */

	/**
	 * index of coordinate for e01^e12 in mixedPencil
	 */
	public static final int E01_E12 = 0;

	/**
	 * index of coordinate for e01^e23 in mixedPencil
	 */
	public static final int E01_E23 = 1;

	/**
	 * index of coordinate for e01^e31 in mixedPencil
	 */
	public static final int E01_E31 = 2;

	/**
	 * index of coordinate for e02^e12 in mixedPencil
	 */
	public static final int E02_E12 = 3;

	/**
	 * index of coordinate for e02^e23 in mixedPencil
	 */
	public static final int E02_E23 = 4;

	/**
	 * index of coordinate for e02^e31 in mixedPencil
	 */
	public static final int E02_E31 = 5;

	/**
	 * index of coordinate for e03^e12 in mixedPencil
	 */
	public static final int E03_E12 = 6;

	/**
	 * index of coordinate for e03^e23 in mixedPencil
	 */
	public static final int E03_E23 = 7;

	/**
	 * index of coordinate for e03^e31 in mixedPencil
	 */
	public static final int E03_E31 = 8;

	/**
	 * The order of coordinates (this is the type of the first argument of coordinate-handling functions.
	 */
	private enum CoordinateOrder {
		coord_e01e12_e01e23_e01e31_e02e12_e02e23_e02e31_e03e12_e03e23_e03e31
	};
	public static final CoordinateOrder coord_e01e12_e01e23_e01e31_e02e12_e02e23_e02e31_e03e12_e03e23_e03e31 = CoordinateOrder.coord_e01e12_e01e23_e01e31_e02e12_e02e23_e02e31_e03e12_e03e23_e03e31;

	public final mv to_mv() {
		return new mv(this);
	}

    /** Constructs a new mixedPencil with variable coordinates set to 0. */
	public mixedPencil() {set();}

    /** Copy constructor. */
	public mixedPencil(final mixedPencil A) {set(A);}



	/** Constructs a new mixedPencil from mv.
	 *  @param A The value to copy. Coordinates that cannot be represented
	 *  are silently dropped.
	 */
	public mixedPencil(final mv A /*, final int filler */) {set(A);}

	/** Constructs a new mixedPencil. Coordinate values come from 'A'. */
	public mixedPencil(final CoordinateOrder co, final float[] A) {set(co, A);}
	
	/** Constructs a new mixedPencil with each coordinate specified. */
	public mixedPencil(final CoordinateOrder co,  final float e01_e12, final float e01_e23, final float e01_e31, final float e02_e12, final float e02_e23, final float e02_e31, final float e03_e12, final float e03_e23, final float e03_e31) {
		set(co, e01_e12, e01_e23, e01_e31, e02_e12, e02_e23, e02_e31, e03_e12, e03_e23, e03_e31);
	}

public final void set()
{
	m_e01_e12 = m_e01_e23 = m_e01_e31 = m_e02_e12 = m_e02_e23 = m_e02_e31 = m_e03_e12 = m_e03_e23 = m_e03_e31 = 0.0f;

}

public final void set(final float scalarVal)
{
	m_e01_e12 = m_e01_e23 = m_e01_e31 = m_e02_e12 = m_e02_e23 = m_e02_e31 = m_e03_e12 = m_e03_e23 = m_e03_e31 = 0.0f;

}

public final void set(final CoordinateOrder co, final float _e01_e12, final float _e01_e23, final float _e01_e31, final float _e02_e12, final float _e02_e23, final float _e02_e31, final float _e03_e12, final float _e03_e23, final float _e03_e31)
{
	m_e01_e12 = _e01_e12;
	m_e01_e23 = _e01_e23;
	m_e01_e31 = _e01_e31;
	m_e02_e12 = _e02_e12;
	m_e02_e23 = _e02_e23;
	m_e02_e31 = _e02_e31;
	m_e03_e12 = _e03_e12;
	m_e03_e23 = _e03_e23;
	m_e03_e31 = _e03_e31;

}

public final void set(final CoordinateOrder co, final float[] A)
{
	m_e01_e12 = A[0];
	m_e01_e23 = A[1];
	m_e01_e31 = A[2];
	m_e02_e12 = A[3];
	m_e02_e23 = A[4];
	m_e02_e31 = A[5];
	m_e03_e12 = A[6];
	m_e03_e23 = A[7];
	m_e03_e31 = A[8];

}

public final void set(final mixedPencil a)
{
	m_e01_e12 = a.m_e01_e12;
	m_e01_e23 = a.m_e01_e23;
	m_e01_e31 = a.m_e01_e31;
	m_e02_e12 = a.m_e02_e12;
	m_e02_e23 = a.m_e02_e23;
	m_e02_e31 = a.m_e02_e31;
	m_e03_e12 = a.m_e03_e12;
	m_e03_e23 = a.m_e03_e23;
	m_e03_e31 = a.m_e03_e31;

}
	public final void set(final mv src) {
		if (src.c()[2] != null) {
			float[] ptr = src.c()[2];
			m_e01_e12 = ptr[3];
			m_e01_e23 = ptr[6];
			m_e01_e31 = ptr[10];
			m_e02_e12 = ptr[4];
			m_e02_e23 = ptr[7];
			m_e02_e31 = ptr[11];
			m_e03_e12 = ptr[5];
			m_e03_e23 = ptr[8];
			m_e03_e31 = ptr[12];
		}
		else {
			m_e01_e12 = 0.0f;
			m_e01_e23 = 0.0f;
			m_e01_e31 = 0.0f;
			m_e02_e12 = 0.0f;
			m_e02_e23 = 0.0f;
			m_e02_e31 = 0.0f;
			m_e03_e12 = 0.0f;
			m_e03_e23 = 0.0f;
			m_e03_e31 = 0.0f;
		}
	}

	/**
	 * Returns the absolute largest coordinate.
	 */
	public final float largestCoordinate() {
		float maxValue = Math.abs(m_e01_e12);
		if (Math.abs(m_e01_e23) > maxValue) { maxValue = Math.abs(m_e01_e23); }
		if (Math.abs(m_e01_e31) > maxValue) { maxValue = Math.abs(m_e01_e31); }
		if (Math.abs(m_e02_e12) > maxValue) { maxValue = Math.abs(m_e02_e12); }
		if (Math.abs(m_e02_e23) > maxValue) { maxValue = Math.abs(m_e02_e23); }
		if (Math.abs(m_e02_e31) > maxValue) { maxValue = Math.abs(m_e02_e31); }
		if (Math.abs(m_e03_e12) > maxValue) { maxValue = Math.abs(m_e03_e12); }
		if (Math.abs(m_e03_e23) > maxValue) { maxValue = Math.abs(m_e03_e23); }
		if (Math.abs(m_e03_e31) > maxValue) { maxValue = Math.abs(m_e03_e31); }
		return maxValue;
	}
	/**
	 * Returns the absolute largest coordinate,
	 * and the corresponding basis blade bitmap.
	 */
	public final float[] largestBasisBlade()  {
		int bm;
		float maxValue = Math.abs(m_e01_e12);
		bm = 0;
		if (Math.abs(m_e01_e23) > maxValue) { maxValue = Math.abs(m_e01_e23); bm = 17; }
		if (Math.abs(m_e01_e31) > maxValue) { maxValue = Math.abs(m_e01_e31); bm = 33; }
		if (Math.abs(m_e02_e12) > maxValue) { maxValue = Math.abs(m_e02_e12); bm = 10; }
		if (Math.abs(m_e02_e23) > maxValue) { maxValue = Math.abs(m_e02_e23); bm = 18; }
		if (Math.abs(m_e02_e31) > maxValue) { maxValue = Math.abs(m_e02_e31); bm = 34; }
		if (Math.abs(m_e03_e12) > maxValue) { maxValue = Math.abs(m_e03_e12); bm = 12; }
		if (Math.abs(m_e03_e23) > maxValue) { maxValue = Math.abs(m_e03_e23); bm = 20; }
		if (Math.abs(m_e03_e31) > maxValue) { maxValue = Math.abs(m_e03_e31); bm = 36; }
		return new float[]{maxValue, (float)bm};
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
	/**
	 * Returns the e01^e12 coordinate.
	 */
	public final float get_e01_e12() { return m_e01_e12;}
	/**
	 * Sets the e01^e12 coordinate.
	 */
	public final void set_e01_e12(float e01_e12) { m_e01_e12 = e01_e12;}
	/**
	 * Returns the e01^e23 coordinate.
	 */
	public final float get_e01_e23() { return m_e01_e23;}
	/**
	 * Sets the e01^e23 coordinate.
	 */
	public final void set_e01_e23(float e01_e23) { m_e01_e23 = e01_e23;}
	/**
	 * Returns the e01^e31 coordinate.
	 */
	public final float get_e01_e31() { return m_e01_e31;}
	/**
	 * Sets the e01^e31 coordinate.
	 */
	public final void set_e01_e31(float e01_e31) { m_e01_e31 = e01_e31;}
	/**
	 * Returns the e02^e12 coordinate.
	 */
	public final float get_e02_e12() { return m_e02_e12;}
	/**
	 * Sets the e02^e12 coordinate.
	 */
	public final void set_e02_e12(float e02_e12) { m_e02_e12 = e02_e12;}
	/**
	 * Returns the e02^e23 coordinate.
	 */
	public final float get_e02_e23() { return m_e02_e23;}
	/**
	 * Sets the e02^e23 coordinate.
	 */
	public final void set_e02_e23(float e02_e23) { m_e02_e23 = e02_e23;}
	/**
	 * Returns the e02^e31 coordinate.
	 */
	public final float get_e02_e31() { return m_e02_e31;}
	/**
	 * Sets the e02^e31 coordinate.
	 */
	public final void set_e02_e31(float e02_e31) { m_e02_e31 = e02_e31;}
	/**
	 * Returns the e03^e12 coordinate.
	 */
	public final float get_e03_e12() { return m_e03_e12;}
	/**
	 * Sets the e03^e12 coordinate.
	 */
	public final void set_e03_e12(float e03_e12) { m_e03_e12 = e03_e12;}
	/**
	 * Returns the e03^e23 coordinate.
	 */
	public final float get_e03_e23() { return m_e03_e23;}
	/**
	 * Sets the e03^e23 coordinate.
	 */
	public final void set_e03_e23(float e03_e23) { m_e03_e23 = e03_e23;}
	/**
	 * Returns the e03^e31 coordinate.
	 */
	public final float get_e03_e31() { return m_e03_e31;}
	/**
	 * Sets the e03^e31 coordinate.
	 */
	public final void set_e03_e31(float e03_e31) { m_e03_e31 = e03_e31;}
	/**
	 * Returns the scalar coordinate (which is always 0).
	 */
	public final float get_scalar() { return 0.0f;}
} // end of class mixedPencil
