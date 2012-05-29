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
 * This class can hold a specialized multivector of type pseudoscalar.
 * 
 * The coordinates are stored in type float.
 * 
 * The variable non-zero coordinates are:
 *   - coordinate e01^e02^e03^e12^e23^e31  (array index: E01_E02_E03_E12_E23_E31 = 0)
 * 
 * The type has no constant coordinates.
 * 
 * 
 */
public class pseudoscalar  implements  mv_if
{ 
	/**
	 * The e01^e02^e03^e12^e23^e31 coordinate.
	 */
	protected float m_e01_e02_e03_e12_e23_e31;
	/**
	 * Array indices of pseudoscalar coordinates.
	 */

	/**
	 * index of coordinate for e01^e02^e03^e12^e23^e31 in pseudoscalar
	 */
	public static final int E01_E02_E03_E12_E23_E31 = 0;

	/**
	 * The order of coordinates (this is the type of the first argument of coordinate-handling functions.
	 */
	private enum CoordinateOrder {
		coord_e01e02e03e12e23e31
	};
	public static final CoordinateOrder coord_e01e02e03e12e23e31 = CoordinateOrder.coord_e01e02e03e12e23e31;

	public final mv to_mv() {
		return new mv(this);
	}

    /** Constructs a new pseudoscalar with variable coordinates set to 0. */
	public pseudoscalar() {set();}

    /** Copy constructor. */
	public pseudoscalar(final pseudoscalar A) {set(A);}



	/** Constructs a new pseudoscalar from mv.
	 *  @param A The value to copy. Coordinates that cannot be represented
	 *  are silently dropped.
	 */
	public pseudoscalar(final mv A /*, final int filler */) {set(A);}

	/** Constructs a new pseudoscalar. Coordinate values come from 'A'. */
	public pseudoscalar(final CoordinateOrder co, final float[] A) {set(co, A);}
	
	/** Constructs a new pseudoscalar with each coordinate specified. */
	public pseudoscalar(final CoordinateOrder co,  final float e01_e02_e03_e12_e23_e31) {
		set(co, e01_e02_e03_e12_e23_e31);
	}

public final void set()
{
	m_e01_e02_e03_e12_e23_e31 = 0.0f;

}

public final void set(final float scalarVal)
{
	m_e01_e02_e03_e12_e23_e31 = 0.0f;

}

public final void set(final CoordinateOrder co, final float _e01_e02_e03_e12_e23_e31)
{
	m_e01_e02_e03_e12_e23_e31 = _e01_e02_e03_e12_e23_e31;

}

public final void set(final CoordinateOrder co, final float[] A)
{
	m_e01_e02_e03_e12_e23_e31 = A[0];

}

public final void set(final pseudoscalar a)
{
	m_e01_e02_e03_e12_e23_e31 = a.m_e01_e02_e03_e12_e23_e31;

}
	public final void set(final mv src) {
		if (src.c()[6] != null) {
			float[] ptr = src.c()[6];
			m_e01_e02_e03_e12_e23_e31 = ptr[0];
		}
		else {
			m_e01_e02_e03_e12_e23_e31 = 0.0f;
		}
	}

	/**
	 * Returns the absolute largest coordinate.
	 */
	public final float largestCoordinate() {
		float maxValue = Math.abs(m_e01_e02_e03_e12_e23_e31);
		return maxValue;
	}
	/**
	 * Returns the absolute largest coordinate,
	 * and the corresponding basis blade bitmap.
	 */
	public final float[] largestBasisBlade()  {
		int bm;
		float maxValue = Math.abs(m_e01_e02_e03_e12_e23_e31);
		bm = 0;
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
	 * Returns the e01^e02^e03^e12^e23^e31 coordinate.
	 */
	public final float get_e01_e02_e03_e12_e23_e31() { return m_e01_e02_e03_e12_e23_e31;}
	/**
	 * Sets the e01^e02^e03^e12^e23^e31 coordinate.
	 */
	public final void set_e01_e02_e03_e12_e23_e31(float e01_e02_e03_e12_e23_e31) { m_e01_e02_e03_e12_e23_e31 = e01_e02_e03_e12_e23_e31;}
	/**
	 * Returns the scalar coordinate (which is always 0).
	 */
	public final float get_scalar() { return 0.0f;}
} // end of class pseudoscalar
