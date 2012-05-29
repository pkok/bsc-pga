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
 * This class can hold a specialized multivector of type pencil.
 * 
 * The coordinates are stored in type float.
 * 
 * The variable non-zero coordinates are:
 *   - coordinate e01^e02  (array index: E01_E02 = 0)
 *   - coordinate e02^e03  (array index: E02_E03 = 1)
 *   - coordinate -1*e01^e03  (array index: E03_E01 = 2)
 * 
 * The type has no constant coordinates.
 * 
 * 
 */
public class pencil  implements  mv_if
{ 
	/**
	 * The e01^e02 coordinate.
	 */
	protected float m_e01_e02;
	/**
	 * The e02^e03 coordinate.
	 */
	protected float m_e02_e03;
	/**
	 * The -1*e01^e03 coordinate.
	 */
	protected float m_e03_e01;
	/**
	 * Array indices of pencil coordinates.
	 */

	/**
	 * index of coordinate for e01^e02 in pencil
	 */
	public static final int E01_E02 = 0;

	/**
	 * index of coordinate for e02^e03 in pencil
	 */
	public static final int E02_E03 = 1;

	/**
	 * index of coordinate for -1*e01^e03 in pencil
	 */
	public static final int E03_E01 = 2;

	/**
	 * The order of coordinates (this is the type of the first argument of coordinate-handling functions.
	 */
	private enum CoordinateOrder {
		coord_e01e02_e02e03_e03e01
	};
	public static final CoordinateOrder coord_e01e02_e02e03_e03e01 = CoordinateOrder.coord_e01e02_e02e03_e03e01;

	public final mv to_mv() {
		return new mv(this);
	}

    /** Constructs a new pencil with variable coordinates set to 0. */
	public pencil() {set();}

    /** Copy constructor. */
	public pencil(final pencil A) {set(A);}



	/** Constructs a new pencil from mv.
	 *  @param A The value to copy. Coordinates that cannot be represented
	 *  are silently dropped.
	 */
	public pencil(final mv A /*, final int filler */) {set(A);}

	/** Constructs a new pencil. Coordinate values come from 'A'. */
	public pencil(final CoordinateOrder co, final float[] A) {set(co, A);}
	
	/** Constructs a new pencil with each coordinate specified. */
	public pencil(final CoordinateOrder co,  final float e01_e02, final float e02_e03, final float e03_e01) {
		set(co, e01_e02, e02_e03, e03_e01);
	}

public final void set()
{
	m_e01_e02 = m_e02_e03 = m_e03_e01 = 0.0f;

}

public final void set(final float scalarVal)
{
	m_e01_e02 = m_e02_e03 = m_e03_e01 = 0.0f;

}

public final void set(final CoordinateOrder co, final float _e01_e02, final float _e02_e03, final float _e03_e01)
{
	m_e01_e02 = _e01_e02;
	m_e02_e03 = _e02_e03;
	m_e03_e01 = _e03_e01;

}

public final void set(final CoordinateOrder co, final float[] A)
{
	m_e01_e02 = A[0];
	m_e02_e03 = A[1];
	m_e03_e01 = A[2];

}

public final void set(final pencil a)
{
	m_e01_e02 = a.m_e01_e02;
	m_e02_e03 = a.m_e02_e03;
	m_e03_e01 = a.m_e03_e01;

}
	public final void set(final mv src) {
		if (src.c()[2] != null) {
			float[] ptr = src.c()[2];
			m_e01_e02 = ptr[0];
			m_e02_e03 = ptr[2];
			m_e03_e01 = -ptr[1];
		}
		else {
			m_e01_e02 = 0.0f;
			m_e02_e03 = 0.0f;
			m_e03_e01 = 0.0f;
		}
	}

	/**
	 * Returns the absolute largest coordinate.
	 */
	public final float largestCoordinate() {
		float maxValue = Math.abs(m_e01_e02);
		if (Math.abs(m_e02_e03) > maxValue) { maxValue = Math.abs(m_e02_e03); }
		if (Math.abs(m_e03_e01) > maxValue) { maxValue = Math.abs(m_e03_e01); }
		return maxValue;
	}
	/**
	 * Returns the absolute largest coordinate,
	 * and the corresponding basis blade bitmap.
	 */
	public final float[] largestBasisBlade()  {
		int bm;
		float maxValue = Math.abs(m_e01_e02);
		bm = 0;
		if (Math.abs(m_e02_e03) > maxValue) { maxValue = Math.abs(m_e02_e03); bm = 6; }
		if (Math.abs(m_e03_e01) > maxValue) { maxValue = Math.abs(m_e03_e01); bm = 5; }
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
	 * Returns the e01^e02 coordinate.
	 */
	public final float get_e01_e02() { return m_e01_e02;}
	/**
	 * Sets the e01^e02 coordinate.
	 */
	public final void set_e01_e02(float e01_e02) { m_e01_e02 = e01_e02;}
	/**
	 * Returns the e02^e03 coordinate.
	 */
	public final float get_e02_e03() { return m_e02_e03;}
	/**
	 * Sets the e02^e03 coordinate.
	 */
	public final void set_e02_e03(float e02_e03) { m_e02_e03 = e02_e03;}
	/**
	 * Returns the -1*e01^e03 coordinate.
	 */
	public final float get_e03_e01() { return m_e03_e01;}
	/**
	 * Sets the -1*e01^e03 coordinate.
	 */
	public final void set_e03_e01(float e03_e01) { m_e03_e01 = e03_e01;}
	/**
	 * Returns the scalar coordinate (which is always 0).
	 */
	public final float get_scalar() { return 0.0f;}
} // end of class pencil
