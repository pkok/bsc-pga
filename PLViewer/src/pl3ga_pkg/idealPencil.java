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
 * This class can hold a specialized multivector of type idealPencil.
 * 
 * The coordinates are stored in type float.
 * 
 * The variable non-zero coordinates are:
 *   - coordinate e12^e23  (array index: E12_E23 = 0)
 *   - coordinate e23^e31  (array index: E23_E31 = 1)
 *   - coordinate -1*e12^e31  (array index: E31_E12 = 2)
 * 
 * The type has no constant coordinates.
 * 
 * 
 */
public class idealPencil  implements  mv_if
{ 
	/**
	 * The e12^e23 coordinate.
	 */
	protected float m_e12_e23;
	/**
	 * The e23^e31 coordinate.
	 */
	protected float m_e23_e31;
	/**
	 * The -1*e12^e31 coordinate.
	 */
	protected float m_e31_e12;
	/**
	 * Array indices of idealPencil coordinates.
	 */

	/**
	 * index of coordinate for e12^e23 in idealPencil
	 */
	public static final int E12_E23 = 0;

	/**
	 * index of coordinate for e23^e31 in idealPencil
	 */
	public static final int E23_E31 = 1;

	/**
	 * index of coordinate for -1*e12^e31 in idealPencil
	 */
	public static final int E31_E12 = 2;

	/**
	 * The order of coordinates (this is the type of the first argument of coordinate-handling functions.
	 */
	private enum CoordinateOrder {
		coord_e12e23_e23e31_e31e12
	};
	public static final CoordinateOrder coord_e12e23_e23e31_e31e12 = CoordinateOrder.coord_e12e23_e23e31_e31e12;

	public final mv to_mv() {
		return new mv(this);
	}

    /** Constructs a new idealPencil with variable coordinates set to 0. */
	public idealPencil() {set();}

    /** Copy constructor. */
	public idealPencil(final idealPencil A) {set(A);}



	/** Constructs a new idealPencil from mv.
	 *  @param A The value to copy. Coordinates that cannot be represented
	 *  are silently dropped.
	 */
	public idealPencil(final mv A /*, final int filler */) {set(A);}

	/** Constructs a new idealPencil. Coordinate values come from 'A'. */
	public idealPencil(final CoordinateOrder co, final float[] A) {set(co, A);}
	
	/** Constructs a new idealPencil with each coordinate specified. */
	public idealPencil(final CoordinateOrder co,  final float e12_e23, final float e23_e31, final float e31_e12) {
		set(co, e12_e23, e23_e31, e31_e12);
	}

public final void set()
{
	m_e12_e23 = m_e23_e31 = m_e31_e12 = 0.0f;

}

public final void set(final float scalarVal)
{
	m_e12_e23 = m_e23_e31 = m_e31_e12 = 0.0f;

}

public final void set(final CoordinateOrder co, final float _e12_e23, final float _e23_e31, final float _e31_e12)
{
	m_e12_e23 = _e12_e23;
	m_e23_e31 = _e23_e31;
	m_e31_e12 = _e31_e12;

}

public final void set(final CoordinateOrder co, final float[] A)
{
	m_e12_e23 = A[0];
	m_e23_e31 = A[1];
	m_e31_e12 = A[2];

}

public final void set(final idealPencil a)
{
	m_e12_e23 = a.m_e12_e23;
	m_e23_e31 = a.m_e23_e31;
	m_e31_e12 = a.m_e31_e12;

}
	public final void set(final mv src) {
		if (src.c()[2] != null) {
			float[] ptr = src.c()[2];
			m_e12_e23 = ptr[9];
			m_e23_e31 = ptr[14];
			m_e31_e12 = -ptr[13];
		}
		else {
			m_e12_e23 = 0.0f;
			m_e23_e31 = 0.0f;
			m_e31_e12 = 0.0f;
		}
	}

	/**
	 * Returns the absolute largest coordinate.
	 */
	public final float largestCoordinate() {
		float maxValue = Math.abs(m_e12_e23);
		if (Math.abs(m_e23_e31) > maxValue) { maxValue = Math.abs(m_e23_e31); }
		if (Math.abs(m_e31_e12) > maxValue) { maxValue = Math.abs(m_e31_e12); }
		return maxValue;
	}
	/**
	 * Returns the absolute largest coordinate,
	 * and the corresponding basis blade bitmap.
	 */
	public final float[] largestBasisBlade()  {
		int bm;
		float maxValue = Math.abs(m_e12_e23);
		bm = 0;
		if (Math.abs(m_e23_e31) > maxValue) { maxValue = Math.abs(m_e23_e31); bm = 48; }
		if (Math.abs(m_e31_e12) > maxValue) { maxValue = Math.abs(m_e31_e12); bm = 40; }
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
	 * Returns the e12^e23 coordinate.
	 */
	public final float get_e12_e23() { return m_e12_e23;}
	/**
	 * Sets the e12^e23 coordinate.
	 */
	public final void set_e12_e23(float e12_e23) { m_e12_e23 = e12_e23;}
	/**
	 * Returns the e23^e31 coordinate.
	 */
	public final float get_e23_e31() { return m_e23_e31;}
	/**
	 * Sets the e23^e31 coordinate.
	 */
	public final void set_e23_e31(float e23_e31) { m_e23_e31 = e23_e31;}
	/**
	 * Returns the -1*e12^e31 coordinate.
	 */
	public final float get_e31_e12() { return m_e31_e12;}
	/**
	 * Sets the -1*e12^e31 coordinate.
	 */
	public final void set_e31_e12(float e31_e12) { m_e31_e12 = e31_e12;}
	/**
	 * Returns the scalar coordinate (which is always 0).
	 */
	public final float get_scalar() { return 0.0f;}
} // end of class idealPencil
