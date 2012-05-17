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
 * This class can hold a specialized multivector of type oddVersor.
 * 
 * The coordinates are stored in type float.
 * 
 * The variable non-zero coordinates are:
 *   - coordinate e01  (array index: E01 = 0)
 *   - coordinate e02  (array index: E02 = 1)
 *   - coordinate e03  (array index: E03 = 2)
 *   - coordinate e12  (array index: E12 = 3)
 *   - coordinate e23  (array index: E23 = 4)
 *   - coordinate e31  (array index: E31 = 5)
 *   - coordinate e01^e02^e03  (array index: E01_E02_E03 = 6)
 *   - coordinate e01^e02^e12  (array index: E01_E02_E12 = 7)
 *   - coordinate e01^e02^e23  (array index: E01_E02_E23 = 8)
 *   - coordinate e01^e02^e31  (array index: E01_E02_E31 = 9)
 *   - coordinate e01^e03^e12  (array index: E01_E03_E12 = 10)
 *   - coordinate e01^e03^e23  (array index: E01_E03_E23 = 11)
 *   - coordinate e01^e03^e31  (array index: E01_E03_E31 = 12)
 *   - coordinate e01^e12^e23  (array index: E01_E12_E23 = 13)
 *   - coordinate e01^e12^e31  (array index: E01_E12_E31 = 14)
 *   - coordinate e01^e23^e31  (array index: E01_E23_E31 = 15)
 *   - coordinate e02^e03^e12  (array index: E02_E03_E12 = 16)
 *   - coordinate e02^e03^e23  (array index: E02_E03_E23 = 17)
 *   - coordinate e02^e03^e31  (array index: E02_E03_E31 = 18)
 *   - coordinate e02^e12^e23  (array index: E02_E12_E23 = 19)
 *   - coordinate e02^e12^e31  (array index: E02_E12_E31 = 20)
 *   - coordinate e02^e23^e31  (array index: E02_E23_E31 = 21)
 *   - coordinate e03^e12^e23  (array index: E03_E12_E23 = 22)
 *   - coordinate e03^e12^e31  (array index: E03_E12_E31 = 23)
 *   - coordinate e03^e23^e31  (array index: E03_E23_E31 = 24)
 *   - coordinate e12^e23^e31  (array index: E12_E23_E31 = 25)
 *   - coordinate e01^e02^e03^e12^e23  (array index: E01_E02_E03_E12_E23 = 26)
 *   - coordinate e01^e02^e03^e12^e31  (array index: E01_E02_E03_E12_E31 = 27)
 *   - coordinate e01^e02^e03^e23^e31  (array index: E01_E02_E03_E23_E31 = 28)
 *   - coordinate e01^e02^e12^e23^e31  (array index: E01_E02_E12_E23_E31 = 29)
 *   - coordinate e01^e03^e12^e23^e31  (array index: E01_E03_E12_E23_E31 = 30)
 *   - coordinate e02^e03^e12^e23^e31  (array index: E02_E03_E12_E23_E31 = 31)
 * 
 * The type has no constant coordinates.
 * 
 * 
 */
public class oddVersor  implements  mv_if
{ 
	/**
	 * The e01 coordinate.
	 */
	protected float m_e01;
	/**
	 * The e02 coordinate.
	 */
	protected float m_e02;
	/**
	 * The e03 coordinate.
	 */
	protected float m_e03;
	/**
	 * The e12 coordinate.
	 */
	protected float m_e12;
	/**
	 * The e23 coordinate.
	 */
	protected float m_e23;
	/**
	 * The e31 coordinate.
	 */
	protected float m_e31;
	/**
	 * The e01^e02^e03 coordinate.
	 */
	protected float m_e01_e02_e03;
	/**
	 * The e01^e02^e12 coordinate.
	 */
	protected float m_e01_e02_e12;
	/**
	 * The e01^e02^e23 coordinate.
	 */
	protected float m_e01_e02_e23;
	/**
	 * The e01^e02^e31 coordinate.
	 */
	protected float m_e01_e02_e31;
	/**
	 * The e01^e03^e12 coordinate.
	 */
	protected float m_e01_e03_e12;
	/**
	 * The e01^e03^e23 coordinate.
	 */
	protected float m_e01_e03_e23;
	/**
	 * The e01^e03^e31 coordinate.
	 */
	protected float m_e01_e03_e31;
	/**
	 * The e01^e12^e23 coordinate.
	 */
	protected float m_e01_e12_e23;
	/**
	 * The e01^e12^e31 coordinate.
	 */
	protected float m_e01_e12_e31;
	/**
	 * The e01^e23^e31 coordinate.
	 */
	protected float m_e01_e23_e31;
	/**
	 * The e02^e03^e12 coordinate.
	 */
	protected float m_e02_e03_e12;
	/**
	 * The e02^e03^e23 coordinate.
	 */
	protected float m_e02_e03_e23;
	/**
	 * The e02^e03^e31 coordinate.
	 */
	protected float m_e02_e03_e31;
	/**
	 * The e02^e12^e23 coordinate.
	 */
	protected float m_e02_e12_e23;
	/**
	 * The e02^e12^e31 coordinate.
	 */
	protected float m_e02_e12_e31;
	/**
	 * The e02^e23^e31 coordinate.
	 */
	protected float m_e02_e23_e31;
	/**
	 * The e03^e12^e23 coordinate.
	 */
	protected float m_e03_e12_e23;
	/**
	 * The e03^e12^e31 coordinate.
	 */
	protected float m_e03_e12_e31;
	/**
	 * The e03^e23^e31 coordinate.
	 */
	protected float m_e03_e23_e31;
	/**
	 * The e12^e23^e31 coordinate.
	 */
	protected float m_e12_e23_e31;
	/**
	 * The e01^e02^e03^e12^e23 coordinate.
	 */
	protected float m_e01_e02_e03_e12_e23;
	/**
	 * The e01^e02^e03^e12^e31 coordinate.
	 */
	protected float m_e01_e02_e03_e12_e31;
	/**
	 * The e01^e02^e03^e23^e31 coordinate.
	 */
	protected float m_e01_e02_e03_e23_e31;
	/**
	 * The e01^e02^e12^e23^e31 coordinate.
	 */
	protected float m_e01_e02_e12_e23_e31;
	/**
	 * The e01^e03^e12^e23^e31 coordinate.
	 */
	protected float m_e01_e03_e12_e23_e31;
	/**
	 * The e02^e03^e12^e23^e31 coordinate.
	 */
	protected float m_e02_e03_e12_e23_e31;
	/**
	 * Array indices of oddVersor coordinates.
	 */

	/**
	 * index of coordinate for e01 in oddVersor
	 */
	public static final int E01 = 0;

	/**
	 * index of coordinate for e02 in oddVersor
	 */
	public static final int E02 = 1;

	/**
	 * index of coordinate for e03 in oddVersor
	 */
	public static final int E03 = 2;

	/**
	 * index of coordinate for e12 in oddVersor
	 */
	public static final int E12 = 3;

	/**
	 * index of coordinate for e23 in oddVersor
	 */
	public static final int E23 = 4;

	/**
	 * index of coordinate for e31 in oddVersor
	 */
	public static final int E31 = 5;

	/**
	 * index of coordinate for e01^e02^e03 in oddVersor
	 */
	public static final int E01_E02_E03 = 6;

	/**
	 * index of coordinate for e01^e02^e12 in oddVersor
	 */
	public static final int E01_E02_E12 = 7;

	/**
	 * index of coordinate for e01^e02^e23 in oddVersor
	 */
	public static final int E01_E02_E23 = 8;

	/**
	 * index of coordinate for e01^e02^e31 in oddVersor
	 */
	public static final int E01_E02_E31 = 9;

	/**
	 * index of coordinate for e01^e03^e12 in oddVersor
	 */
	public static final int E01_E03_E12 = 10;

	/**
	 * index of coordinate for e01^e03^e23 in oddVersor
	 */
	public static final int E01_E03_E23 = 11;

	/**
	 * index of coordinate for e01^e03^e31 in oddVersor
	 */
	public static final int E01_E03_E31 = 12;

	/**
	 * index of coordinate for e01^e12^e23 in oddVersor
	 */
	public static final int E01_E12_E23 = 13;

	/**
	 * index of coordinate for e01^e12^e31 in oddVersor
	 */
	public static final int E01_E12_E31 = 14;

	/**
	 * index of coordinate for e01^e23^e31 in oddVersor
	 */
	public static final int E01_E23_E31 = 15;

	/**
	 * index of coordinate for e02^e03^e12 in oddVersor
	 */
	public static final int E02_E03_E12 = 16;

	/**
	 * index of coordinate for e02^e03^e23 in oddVersor
	 */
	public static final int E02_E03_E23 = 17;

	/**
	 * index of coordinate for e02^e03^e31 in oddVersor
	 */
	public static final int E02_E03_E31 = 18;

	/**
	 * index of coordinate for e02^e12^e23 in oddVersor
	 */
	public static final int E02_E12_E23 = 19;

	/**
	 * index of coordinate for e02^e12^e31 in oddVersor
	 */
	public static final int E02_E12_E31 = 20;

	/**
	 * index of coordinate for e02^e23^e31 in oddVersor
	 */
	public static final int E02_E23_E31 = 21;

	/**
	 * index of coordinate for e03^e12^e23 in oddVersor
	 */
	public static final int E03_E12_E23 = 22;

	/**
	 * index of coordinate for e03^e12^e31 in oddVersor
	 */
	public static final int E03_E12_E31 = 23;

	/**
	 * index of coordinate for e03^e23^e31 in oddVersor
	 */
	public static final int E03_E23_E31 = 24;

	/**
	 * index of coordinate for e12^e23^e31 in oddVersor
	 */
	public static final int E12_E23_E31 = 25;

	/**
	 * index of coordinate for e01^e02^e03^e12^e23 in oddVersor
	 */
	public static final int E01_E02_E03_E12_E23 = 26;

	/**
	 * index of coordinate for e01^e02^e03^e12^e31 in oddVersor
	 */
	public static final int E01_E02_E03_E12_E31 = 27;

	/**
	 * index of coordinate for e01^e02^e03^e23^e31 in oddVersor
	 */
	public static final int E01_E02_E03_E23_E31 = 28;

	/**
	 * index of coordinate for e01^e02^e12^e23^e31 in oddVersor
	 */
	public static final int E01_E02_E12_E23_E31 = 29;

	/**
	 * index of coordinate for e01^e03^e12^e23^e31 in oddVersor
	 */
	public static final int E01_E03_E12_E23_E31 = 30;

	/**
	 * index of coordinate for e02^e03^e12^e23^e31 in oddVersor
	 */
	public static final int E02_E03_E12_E23_E31 = 31;

	/**
	 * The order of coordinates (this is the type of the first argument of coordinate-handling functions.
	 */
	private enum CoordinateOrder {
		coord_e01_e02_e03_e12_e23_e31_e01e02e03_e01e02e12_e01e02e23_e01e02e31_e01e03e12_e01e03e23_e01e03e31_e01e12e23_e01e12e31_e01e23e31_e02e03e12_e02e03e23_e02e03e31_e02e12e23_e02e12e31_e02e23e31_e03e12e23_e03e12e31_e03e23e31_e12e23e31_e01e02e03e12e23_e01e02e03e12e31_e01e02e03e23e31_e01e02e12e23e31_e01e03e12e23e31_e02e03e12e23e31
	};
	public static final CoordinateOrder coord_e01_e02_e03_e12_e23_e31_e01e02e03_e01e02e12_e01e02e23_e01e02e31_e01e03e12_e01e03e23_e01e03e31_e01e12e23_e01e12e31_e01e23e31_e02e03e12_e02e03e23_e02e03e31_e02e12e23_e02e12e31_e02e23e31_e03e12e23_e03e12e31_e03e23e31_e12e23e31_e01e02e03e12e23_e01e02e03e12e31_e01e02e03e23e31_e01e02e12e23e31_e01e03e12e23e31_e02e03e12e23e31 = CoordinateOrder.coord_e01_e02_e03_e12_e23_e31_e01e02e03_e01e02e12_e01e02e23_e01e02e31_e01e03e12_e01e03e23_e01e03e31_e01e12e23_e01e12e31_e01e23e31_e02e03e12_e02e03e23_e02e03e31_e02e12e23_e02e12e31_e02e23e31_e03e12e23_e03e12e31_e03e23e31_e12e23e31_e01e02e03e12e23_e01e02e03e12e31_e01e02e03e23e31_e01e02e12e23e31_e01e03e12e23e31_e02e03e12e23e31;

	public final mv to_mv() {
		return new mv(this);
	}

    /** Constructs a new oddVersor with variable coordinates set to 0. */
	public oddVersor() {set();}

    /** Copy constructor. */
	public oddVersor(final oddVersor A) {set(A);}



	/** Constructs a new oddVersor from mv.
	 *  @param A The value to copy. Coordinates that cannot be represented
	 *  are silently dropped.
	 */
	public oddVersor(final mv A /*, final int filler */) {set(A);}

	/** Constructs a new oddVersor. Coordinate values come from 'A'. */
	public oddVersor(final CoordinateOrder co, final float[] A) {set(co, A);}
	
	/** Constructs a new oddVersor with each coordinate specified. */
	public oddVersor(final CoordinateOrder co,  final float e01, final float e02, final float e03, final float e12, final float e23, final float e31, final float e01_e02_e03, final float e01_e02_e12, final float e01_e02_e23, final float e01_e02_e31, final float e01_e03_e12, final float e01_e03_e23, final float e01_e03_e31, final float e01_e12_e23, final float e01_e12_e31, final float e01_e23_e31, final float e02_e03_e12, final float e02_e03_e23, final float e02_e03_e31, final float e02_e12_e23, final float e02_e12_e31, final float e02_e23_e31, final float e03_e12_e23, final float e03_e12_e31, final float e03_e23_e31, final float e12_e23_e31, final float e01_e02_e03_e12_e23, final float e01_e02_e03_e12_e31, final float e01_e02_e03_e23_e31, final float e01_e02_e12_e23_e31, final float e01_e03_e12_e23_e31, final float e02_e03_e12_e23_e31) {
		set(co, e01, e02, e03, e12, e23, e31, e01_e02_e03, e01_e02_e12, e01_e02_e23, e01_e02_e31, e01_e03_e12, e01_e03_e23, e01_e03_e31, e01_e12_e23, e01_e12_e31, e01_e23_e31, e02_e03_e12, e02_e03_e23, e02_e03_e31, e02_e12_e23, e02_e12_e31, e02_e23_e31, e03_e12_e23, e03_e12_e31, e03_e23_e31, e12_e23_e31, e01_e02_e03_e12_e23, e01_e02_e03_e12_e31, e01_e02_e03_e23_e31, e01_e02_e12_e23_e31, e01_e03_e12_e23_e31, e02_e03_e12_e23_e31);
	}

public final void set()
{
	m_e01 = m_e02 = m_e03 = m_e12 = m_e23 = m_e31 = m_e01_e02_e03 = m_e01_e02_e12 = m_e01_e02_e23 = m_e01_e02_e31 = m_e01_e03_e12 = m_e01_e03_e23 = m_e01_e03_e31 = m_e01_e12_e23 = m_e01_e12_e31 = m_e01_e23_e31 = m_e02_e03_e12 = m_e02_e03_e23 = m_e02_e03_e31 = m_e02_e12_e23 = m_e02_e12_e31 = m_e02_e23_e31 = m_e03_e12_e23 = m_e03_e12_e31 = m_e03_e23_e31 = m_e12_e23_e31 = m_e01_e02_e03_e12_e23 = m_e01_e02_e03_e12_e31 = m_e01_e02_e03_e23_e31 = m_e01_e02_e12_e23_e31 = m_e01_e03_e12_e23_e31 = m_e02_e03_e12_e23_e31 = 0.0f;

}

public final void set(final float scalarVal)
{
	m_e01 = m_e02 = m_e03 = m_e12 = m_e23 = m_e31 = m_e01_e02_e03 = m_e01_e02_e12 = m_e01_e02_e23 = m_e01_e02_e31 = m_e01_e03_e12 = m_e01_e03_e23 = m_e01_e03_e31 = m_e01_e12_e23 = m_e01_e12_e31 = m_e01_e23_e31 = m_e02_e03_e12 = m_e02_e03_e23 = m_e02_e03_e31 = m_e02_e12_e23 = m_e02_e12_e31 = m_e02_e23_e31 = m_e03_e12_e23 = m_e03_e12_e31 = m_e03_e23_e31 = m_e12_e23_e31 = m_e01_e02_e03_e12_e23 = m_e01_e02_e03_e12_e31 = m_e01_e02_e03_e23_e31 = m_e01_e02_e12_e23_e31 = m_e01_e03_e12_e23_e31 = m_e02_e03_e12_e23_e31 = 0.0f;

}

public final void set(final CoordinateOrder co, final float _e01, final float _e02, final float _e03, final float _e12, final float _e23, final float _e31, final float _e01_e02_e03, final float _e01_e02_e12, final float _e01_e02_e23, final float _e01_e02_e31, final float _e01_e03_e12, final float _e01_e03_e23, final float _e01_e03_e31, final float _e01_e12_e23, final float _e01_e12_e31, final float _e01_e23_e31, final float _e02_e03_e12, final float _e02_e03_e23, final float _e02_e03_e31, final float _e02_e12_e23, final float _e02_e12_e31, final float _e02_e23_e31, final float _e03_e12_e23, final float _e03_e12_e31, final float _e03_e23_e31, final float _e12_e23_e31, final float _e01_e02_e03_e12_e23, final float _e01_e02_e03_e12_e31, final float _e01_e02_e03_e23_e31, final float _e01_e02_e12_e23_e31, final float _e01_e03_e12_e23_e31, final float _e02_e03_e12_e23_e31)
{
	m_e01 = _e01;
	m_e02 = _e02;
	m_e03 = _e03;
	m_e12 = _e12;
	m_e23 = _e23;
	m_e31 = _e31;
	m_e01_e02_e03 = _e01_e02_e03;
	m_e01_e02_e12 = _e01_e02_e12;
	m_e01_e02_e23 = _e01_e02_e23;
	m_e01_e02_e31 = _e01_e02_e31;
	m_e01_e03_e12 = _e01_e03_e12;
	m_e01_e03_e23 = _e01_e03_e23;
	m_e01_e03_e31 = _e01_e03_e31;
	m_e01_e12_e23 = _e01_e12_e23;
	m_e01_e12_e31 = _e01_e12_e31;
	m_e01_e23_e31 = _e01_e23_e31;
	m_e02_e03_e12 = _e02_e03_e12;
	m_e02_e03_e23 = _e02_e03_e23;
	m_e02_e03_e31 = _e02_e03_e31;
	m_e02_e12_e23 = _e02_e12_e23;
	m_e02_e12_e31 = _e02_e12_e31;
	m_e02_e23_e31 = _e02_e23_e31;
	m_e03_e12_e23 = _e03_e12_e23;
	m_e03_e12_e31 = _e03_e12_e31;
	m_e03_e23_e31 = _e03_e23_e31;
	m_e12_e23_e31 = _e12_e23_e31;
	m_e01_e02_e03_e12_e23 = _e01_e02_e03_e12_e23;
	m_e01_e02_e03_e12_e31 = _e01_e02_e03_e12_e31;
	m_e01_e02_e03_e23_e31 = _e01_e02_e03_e23_e31;
	m_e01_e02_e12_e23_e31 = _e01_e02_e12_e23_e31;
	m_e01_e03_e12_e23_e31 = _e01_e03_e12_e23_e31;
	m_e02_e03_e12_e23_e31 = _e02_e03_e12_e23_e31;

}

public final void set(final CoordinateOrder co, final float[] A)
{
	m_e01 = A[0];
	m_e02 = A[1];
	m_e03 = A[2];
	m_e12 = A[3];
	m_e23 = A[4];
	m_e31 = A[5];
	m_e01_e02_e03 = A[6];
	m_e01_e02_e12 = A[7];
	m_e01_e02_e23 = A[8];
	m_e01_e02_e31 = A[9];
	m_e01_e03_e12 = A[10];
	m_e01_e03_e23 = A[11];
	m_e01_e03_e31 = A[12];
	m_e01_e12_e23 = A[13];
	m_e01_e12_e31 = A[14];
	m_e01_e23_e31 = A[15];
	m_e02_e03_e12 = A[16];
	m_e02_e03_e23 = A[17];
	m_e02_e03_e31 = A[18];
	m_e02_e12_e23 = A[19];
	m_e02_e12_e31 = A[20];
	m_e02_e23_e31 = A[21];
	m_e03_e12_e23 = A[22];
	m_e03_e12_e31 = A[23];
	m_e03_e23_e31 = A[24];
	m_e12_e23_e31 = A[25];
	m_e01_e02_e03_e12_e23 = A[26];
	m_e01_e02_e03_e12_e31 = A[27];
	m_e01_e02_e03_e23_e31 = A[28];
	m_e01_e02_e12_e23_e31 = A[29];
	m_e01_e03_e12_e23_e31 = A[30];
	m_e02_e03_e12_e23_e31 = A[31];

}

public final void set(final oddVersor a)
{
	m_e01 = a.m_e01;
	m_e02 = a.m_e02;
	m_e03 = a.m_e03;
	m_e12 = a.m_e12;
	m_e23 = a.m_e23;
	m_e31 = a.m_e31;
	m_e01_e02_e03 = a.m_e01_e02_e03;
	m_e01_e02_e12 = a.m_e01_e02_e12;
	m_e01_e02_e23 = a.m_e01_e02_e23;
	m_e01_e02_e31 = a.m_e01_e02_e31;
	m_e01_e03_e12 = a.m_e01_e03_e12;
	m_e01_e03_e23 = a.m_e01_e03_e23;
	m_e01_e03_e31 = a.m_e01_e03_e31;
	m_e01_e12_e23 = a.m_e01_e12_e23;
	m_e01_e12_e31 = a.m_e01_e12_e31;
	m_e01_e23_e31 = a.m_e01_e23_e31;
	m_e02_e03_e12 = a.m_e02_e03_e12;
	m_e02_e03_e23 = a.m_e02_e03_e23;
	m_e02_e03_e31 = a.m_e02_e03_e31;
	m_e02_e12_e23 = a.m_e02_e12_e23;
	m_e02_e12_e31 = a.m_e02_e12_e31;
	m_e02_e23_e31 = a.m_e02_e23_e31;
	m_e03_e12_e23 = a.m_e03_e12_e23;
	m_e03_e12_e31 = a.m_e03_e12_e31;
	m_e03_e23_e31 = a.m_e03_e23_e31;
	m_e12_e23_e31 = a.m_e12_e23_e31;
	m_e01_e02_e03_e12_e23 = a.m_e01_e02_e03_e12_e23;
	m_e01_e02_e03_e12_e31 = a.m_e01_e02_e03_e12_e31;
	m_e01_e02_e03_e23_e31 = a.m_e01_e02_e03_e23_e31;
	m_e01_e02_e12_e23_e31 = a.m_e01_e02_e12_e23_e31;
	m_e01_e03_e12_e23_e31 = a.m_e01_e03_e12_e23_e31;
	m_e02_e03_e12_e23_e31 = a.m_e02_e03_e12_e23_e31;

}
	public final void set(final mv src) {
		if (src.c()[1] != null) {
			float[] ptr = src.c()[1];
			m_e01 = ptr[0];
			m_e02 = ptr[1];
			m_e03 = ptr[2];
			m_e12 = ptr[3];
			m_e23 = ptr[4];
			m_e31 = ptr[5];
		}
		else {
			m_e01 = 0.0f;
			m_e02 = 0.0f;
			m_e03 = 0.0f;
			m_e12 = 0.0f;
			m_e23 = 0.0f;
			m_e31 = 0.0f;
		}
		if (src.c()[3] != null) {
			float[] ptr = src.c()[3];
			m_e01_e02_e03 = ptr[0];
			m_e01_e02_e12 = ptr[1];
			m_e01_e02_e23 = ptr[4];
			m_e01_e02_e31 = ptr[10];
			m_e01_e03_e12 = ptr[2];
			m_e01_e03_e23 = ptr[5];
			m_e01_e03_e31 = ptr[11];
			m_e01_e12_e23 = ptr[7];
			m_e01_e12_e31 = ptr[13];
			m_e01_e23_e31 = ptr[16];
			m_e02_e03_e12 = ptr[3];
			m_e02_e03_e23 = ptr[6];
			m_e02_e03_e31 = ptr[12];
			m_e02_e12_e23 = ptr[8];
			m_e02_e12_e31 = ptr[14];
			m_e02_e23_e31 = ptr[17];
			m_e03_e12_e23 = ptr[9];
			m_e03_e12_e31 = ptr[15];
			m_e03_e23_e31 = ptr[18];
			m_e12_e23_e31 = ptr[19];
		}
		else {
			m_e01_e02_e03 = 0.0f;
			m_e01_e02_e12 = 0.0f;
			m_e01_e02_e23 = 0.0f;
			m_e01_e02_e31 = 0.0f;
			m_e01_e03_e12 = 0.0f;
			m_e01_e03_e23 = 0.0f;
			m_e01_e03_e31 = 0.0f;
			m_e01_e12_e23 = 0.0f;
			m_e01_e12_e31 = 0.0f;
			m_e01_e23_e31 = 0.0f;
			m_e02_e03_e12 = 0.0f;
			m_e02_e03_e23 = 0.0f;
			m_e02_e03_e31 = 0.0f;
			m_e02_e12_e23 = 0.0f;
			m_e02_e12_e31 = 0.0f;
			m_e02_e23_e31 = 0.0f;
			m_e03_e12_e23 = 0.0f;
			m_e03_e12_e31 = 0.0f;
			m_e03_e23_e31 = 0.0f;
			m_e12_e23_e31 = 0.0f;
		}
		if (src.c()[5] != null) {
			float[] ptr = src.c()[5];
			m_e01_e02_e03_e12_e23 = ptr[0];
			m_e01_e02_e03_e12_e31 = ptr[1];
			m_e01_e02_e03_e23_e31 = ptr[2];
			m_e01_e02_e12_e23_e31 = ptr[3];
			m_e01_e03_e12_e23_e31 = ptr[4];
			m_e02_e03_e12_e23_e31 = ptr[5];
		}
		else {
			m_e01_e02_e03_e12_e23 = 0.0f;
			m_e01_e02_e03_e12_e31 = 0.0f;
			m_e01_e02_e03_e23_e31 = 0.0f;
			m_e01_e02_e12_e23_e31 = 0.0f;
			m_e01_e03_e12_e23_e31 = 0.0f;
			m_e02_e03_e12_e23_e31 = 0.0f;
		}
	}

	/**
	 * Returns the absolute largest coordinate.
	 */
	public final float largestCoordinate() {
		float maxValue = Math.abs(m_e01);
		if (Math.abs(m_e02) > maxValue) { maxValue = Math.abs(m_e02); }
		if (Math.abs(m_e03) > maxValue) { maxValue = Math.abs(m_e03); }
		if (Math.abs(m_e12) > maxValue) { maxValue = Math.abs(m_e12); }
		if (Math.abs(m_e23) > maxValue) { maxValue = Math.abs(m_e23); }
		if (Math.abs(m_e31) > maxValue) { maxValue = Math.abs(m_e31); }
		if (Math.abs(m_e01_e02_e03) > maxValue) { maxValue = Math.abs(m_e01_e02_e03); }
		if (Math.abs(m_e01_e02_e12) > maxValue) { maxValue = Math.abs(m_e01_e02_e12); }
		if (Math.abs(m_e01_e02_e23) > maxValue) { maxValue = Math.abs(m_e01_e02_e23); }
		if (Math.abs(m_e01_e02_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e31); }
		if (Math.abs(m_e01_e03_e12) > maxValue) { maxValue = Math.abs(m_e01_e03_e12); }
		if (Math.abs(m_e01_e03_e23) > maxValue) { maxValue = Math.abs(m_e01_e03_e23); }
		if (Math.abs(m_e01_e03_e31) > maxValue) { maxValue = Math.abs(m_e01_e03_e31); }
		if (Math.abs(m_e01_e12_e23) > maxValue) { maxValue = Math.abs(m_e01_e12_e23); }
		if (Math.abs(m_e01_e12_e31) > maxValue) { maxValue = Math.abs(m_e01_e12_e31); }
		if (Math.abs(m_e01_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e23_e31); }
		if (Math.abs(m_e02_e03_e12) > maxValue) { maxValue = Math.abs(m_e02_e03_e12); }
		if (Math.abs(m_e02_e03_e23) > maxValue) { maxValue = Math.abs(m_e02_e03_e23); }
		if (Math.abs(m_e02_e03_e31) > maxValue) { maxValue = Math.abs(m_e02_e03_e31); }
		if (Math.abs(m_e02_e12_e23) > maxValue) { maxValue = Math.abs(m_e02_e12_e23); }
		if (Math.abs(m_e02_e12_e31) > maxValue) { maxValue = Math.abs(m_e02_e12_e31); }
		if (Math.abs(m_e02_e23_e31) > maxValue) { maxValue = Math.abs(m_e02_e23_e31); }
		if (Math.abs(m_e03_e12_e23) > maxValue) { maxValue = Math.abs(m_e03_e12_e23); }
		if (Math.abs(m_e03_e12_e31) > maxValue) { maxValue = Math.abs(m_e03_e12_e31); }
		if (Math.abs(m_e03_e23_e31) > maxValue) { maxValue = Math.abs(m_e03_e23_e31); }
		if (Math.abs(m_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e12_e23_e31); }
		if (Math.abs(m_e01_e02_e03_e12_e23) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e12_e23); }
		if (Math.abs(m_e01_e02_e03_e12_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e12_e31); }
		if (Math.abs(m_e01_e02_e03_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e23_e31); }
		if (Math.abs(m_e01_e02_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e12_e23_e31); }
		if (Math.abs(m_e01_e03_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e03_e12_e23_e31); }
		if (Math.abs(m_e02_e03_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e02_e03_e12_e23_e31); }
		return maxValue;
	}
	/**
	 * Returns the absolute largest coordinate,
	 * and the corresponding basis blade bitmap.
	 */
	public final float[] largestBasisBlade()  {
		int bm;
		float maxValue = Math.abs(m_e01);
		bm = 0;
		if (Math.abs(m_e02) > maxValue) { maxValue = Math.abs(m_e02); bm = 2; }
		if (Math.abs(m_e03) > maxValue) { maxValue = Math.abs(m_e03); bm = 4; }
		if (Math.abs(m_e12) > maxValue) { maxValue = Math.abs(m_e12); bm = 8; }
		if (Math.abs(m_e23) > maxValue) { maxValue = Math.abs(m_e23); bm = 16; }
		if (Math.abs(m_e31) > maxValue) { maxValue = Math.abs(m_e31); bm = 32; }
		if (Math.abs(m_e01_e02_e03) > maxValue) { maxValue = Math.abs(m_e01_e02_e03); bm = 7; }
		if (Math.abs(m_e01_e02_e12) > maxValue) { maxValue = Math.abs(m_e01_e02_e12); bm = 11; }
		if (Math.abs(m_e01_e02_e23) > maxValue) { maxValue = Math.abs(m_e01_e02_e23); bm = 19; }
		if (Math.abs(m_e01_e02_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e31); bm = 35; }
		if (Math.abs(m_e01_e03_e12) > maxValue) { maxValue = Math.abs(m_e01_e03_e12); bm = 13; }
		if (Math.abs(m_e01_e03_e23) > maxValue) { maxValue = Math.abs(m_e01_e03_e23); bm = 21; }
		if (Math.abs(m_e01_e03_e31) > maxValue) { maxValue = Math.abs(m_e01_e03_e31); bm = 37; }
		if (Math.abs(m_e01_e12_e23) > maxValue) { maxValue = Math.abs(m_e01_e12_e23); bm = 25; }
		if (Math.abs(m_e01_e12_e31) > maxValue) { maxValue = Math.abs(m_e01_e12_e31); bm = 41; }
		if (Math.abs(m_e01_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e23_e31); bm = 49; }
		if (Math.abs(m_e02_e03_e12) > maxValue) { maxValue = Math.abs(m_e02_e03_e12); bm = 14; }
		if (Math.abs(m_e02_e03_e23) > maxValue) { maxValue = Math.abs(m_e02_e03_e23); bm = 22; }
		if (Math.abs(m_e02_e03_e31) > maxValue) { maxValue = Math.abs(m_e02_e03_e31); bm = 38; }
		if (Math.abs(m_e02_e12_e23) > maxValue) { maxValue = Math.abs(m_e02_e12_e23); bm = 26; }
		if (Math.abs(m_e02_e12_e31) > maxValue) { maxValue = Math.abs(m_e02_e12_e31); bm = 42; }
		if (Math.abs(m_e02_e23_e31) > maxValue) { maxValue = Math.abs(m_e02_e23_e31); bm = 50; }
		if (Math.abs(m_e03_e12_e23) > maxValue) { maxValue = Math.abs(m_e03_e12_e23); bm = 28; }
		if (Math.abs(m_e03_e12_e31) > maxValue) { maxValue = Math.abs(m_e03_e12_e31); bm = 44; }
		if (Math.abs(m_e03_e23_e31) > maxValue) { maxValue = Math.abs(m_e03_e23_e31); bm = 52; }
		if (Math.abs(m_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e12_e23_e31); bm = 56; }
		if (Math.abs(m_e01_e02_e03_e12_e23) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e12_e23); bm = 31; }
		if (Math.abs(m_e01_e02_e03_e12_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e12_e31); bm = 47; }
		if (Math.abs(m_e01_e02_e03_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e03_e23_e31); bm = 55; }
		if (Math.abs(m_e01_e02_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e02_e12_e23_e31); bm = 59; }
		if (Math.abs(m_e01_e03_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e01_e03_e12_e23_e31); bm = 61; }
		if (Math.abs(m_e02_e03_e12_e23_e31) > maxValue) { maxValue = Math.abs(m_e02_e03_e12_e23_e31); bm = 62; }
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
	 * Returns the e01 coordinate.
	 */
	public final float get_e01() { return m_e01;}
	/**
	 * Sets the e01 coordinate.
	 */
	public final void set_e01(float e01) { m_e01 = e01;}
	/**
	 * Returns the e02 coordinate.
	 */
	public final float get_e02() { return m_e02;}
	/**
	 * Sets the e02 coordinate.
	 */
	public final void set_e02(float e02) { m_e02 = e02;}
	/**
	 * Returns the e03 coordinate.
	 */
	public final float get_e03() { return m_e03;}
	/**
	 * Sets the e03 coordinate.
	 */
	public final void set_e03(float e03) { m_e03 = e03;}
	/**
	 * Returns the e12 coordinate.
	 */
	public final float get_e12() { return m_e12;}
	/**
	 * Sets the e12 coordinate.
	 */
	public final void set_e12(float e12) { m_e12 = e12;}
	/**
	 * Returns the e23 coordinate.
	 */
	public final float get_e23() { return m_e23;}
	/**
	 * Sets the e23 coordinate.
	 */
	public final void set_e23(float e23) { m_e23 = e23;}
	/**
	 * Returns the e31 coordinate.
	 */
	public final float get_e31() { return m_e31;}
	/**
	 * Sets the e31 coordinate.
	 */
	public final void set_e31(float e31) { m_e31 = e31;}
	/**
	 * Returns the e01^e02^e03 coordinate.
	 */
	public final float get_e01_e02_e03() { return m_e01_e02_e03;}
	/**
	 * Sets the e01^e02^e03 coordinate.
	 */
	public final void set_e01_e02_e03(float e01_e02_e03) { m_e01_e02_e03 = e01_e02_e03;}
	/**
	 * Returns the e01^e02^e12 coordinate.
	 */
	public final float get_e01_e02_e12() { return m_e01_e02_e12;}
	/**
	 * Sets the e01^e02^e12 coordinate.
	 */
	public final void set_e01_e02_e12(float e01_e02_e12) { m_e01_e02_e12 = e01_e02_e12;}
	/**
	 * Returns the e01^e02^e23 coordinate.
	 */
	public final float get_e01_e02_e23() { return m_e01_e02_e23;}
	/**
	 * Sets the e01^e02^e23 coordinate.
	 */
	public final void set_e01_e02_e23(float e01_e02_e23) { m_e01_e02_e23 = e01_e02_e23;}
	/**
	 * Returns the e01^e02^e31 coordinate.
	 */
	public final float get_e01_e02_e31() { return m_e01_e02_e31;}
	/**
	 * Sets the e01^e02^e31 coordinate.
	 */
	public final void set_e01_e02_e31(float e01_e02_e31) { m_e01_e02_e31 = e01_e02_e31;}
	/**
	 * Returns the e01^e03^e12 coordinate.
	 */
	public final float get_e01_e03_e12() { return m_e01_e03_e12;}
	/**
	 * Sets the e01^e03^e12 coordinate.
	 */
	public final void set_e01_e03_e12(float e01_e03_e12) { m_e01_e03_e12 = e01_e03_e12;}
	/**
	 * Returns the e01^e03^e23 coordinate.
	 */
	public final float get_e01_e03_e23() { return m_e01_e03_e23;}
	/**
	 * Sets the e01^e03^e23 coordinate.
	 */
	public final void set_e01_e03_e23(float e01_e03_e23) { m_e01_e03_e23 = e01_e03_e23;}
	/**
	 * Returns the e01^e03^e31 coordinate.
	 */
	public final float get_e01_e03_e31() { return m_e01_e03_e31;}
	/**
	 * Sets the e01^e03^e31 coordinate.
	 */
	public final void set_e01_e03_e31(float e01_e03_e31) { m_e01_e03_e31 = e01_e03_e31;}
	/**
	 * Returns the e01^e12^e23 coordinate.
	 */
	public final float get_e01_e12_e23() { return m_e01_e12_e23;}
	/**
	 * Sets the e01^e12^e23 coordinate.
	 */
	public final void set_e01_e12_e23(float e01_e12_e23) { m_e01_e12_e23 = e01_e12_e23;}
	/**
	 * Returns the e01^e12^e31 coordinate.
	 */
	public final float get_e01_e12_e31() { return m_e01_e12_e31;}
	/**
	 * Sets the e01^e12^e31 coordinate.
	 */
	public final void set_e01_e12_e31(float e01_e12_e31) { m_e01_e12_e31 = e01_e12_e31;}
	/**
	 * Returns the e01^e23^e31 coordinate.
	 */
	public final float get_e01_e23_e31() { return m_e01_e23_e31;}
	/**
	 * Sets the e01^e23^e31 coordinate.
	 */
	public final void set_e01_e23_e31(float e01_e23_e31) { m_e01_e23_e31 = e01_e23_e31;}
	/**
	 * Returns the e02^e03^e12 coordinate.
	 */
	public final float get_e02_e03_e12() { return m_e02_e03_e12;}
	/**
	 * Sets the e02^e03^e12 coordinate.
	 */
	public final void set_e02_e03_e12(float e02_e03_e12) { m_e02_e03_e12 = e02_e03_e12;}
	/**
	 * Returns the e02^e03^e23 coordinate.
	 */
	public final float get_e02_e03_e23() { return m_e02_e03_e23;}
	/**
	 * Sets the e02^e03^e23 coordinate.
	 */
	public final void set_e02_e03_e23(float e02_e03_e23) { m_e02_e03_e23 = e02_e03_e23;}
	/**
	 * Returns the e02^e03^e31 coordinate.
	 */
	public final float get_e02_e03_e31() { return m_e02_e03_e31;}
	/**
	 * Sets the e02^e03^e31 coordinate.
	 */
	public final void set_e02_e03_e31(float e02_e03_e31) { m_e02_e03_e31 = e02_e03_e31;}
	/**
	 * Returns the e02^e12^e23 coordinate.
	 */
	public final float get_e02_e12_e23() { return m_e02_e12_e23;}
	/**
	 * Sets the e02^e12^e23 coordinate.
	 */
	public final void set_e02_e12_e23(float e02_e12_e23) { m_e02_e12_e23 = e02_e12_e23;}
	/**
	 * Returns the e02^e12^e31 coordinate.
	 */
	public final float get_e02_e12_e31() { return m_e02_e12_e31;}
	/**
	 * Sets the e02^e12^e31 coordinate.
	 */
	public final void set_e02_e12_e31(float e02_e12_e31) { m_e02_e12_e31 = e02_e12_e31;}
	/**
	 * Returns the e02^e23^e31 coordinate.
	 */
	public final float get_e02_e23_e31() { return m_e02_e23_e31;}
	/**
	 * Sets the e02^e23^e31 coordinate.
	 */
	public final void set_e02_e23_e31(float e02_e23_e31) { m_e02_e23_e31 = e02_e23_e31;}
	/**
	 * Returns the e03^e12^e23 coordinate.
	 */
	public final float get_e03_e12_e23() { return m_e03_e12_e23;}
	/**
	 * Sets the e03^e12^e23 coordinate.
	 */
	public final void set_e03_e12_e23(float e03_e12_e23) { m_e03_e12_e23 = e03_e12_e23;}
	/**
	 * Returns the e03^e12^e31 coordinate.
	 */
	public final float get_e03_e12_e31() { return m_e03_e12_e31;}
	/**
	 * Sets the e03^e12^e31 coordinate.
	 */
	public final void set_e03_e12_e31(float e03_e12_e31) { m_e03_e12_e31 = e03_e12_e31;}
	/**
	 * Returns the e03^e23^e31 coordinate.
	 */
	public final float get_e03_e23_e31() { return m_e03_e23_e31;}
	/**
	 * Sets the e03^e23^e31 coordinate.
	 */
	public final void set_e03_e23_e31(float e03_e23_e31) { m_e03_e23_e31 = e03_e23_e31;}
	/**
	 * Returns the e12^e23^e31 coordinate.
	 */
	public final float get_e12_e23_e31() { return m_e12_e23_e31;}
	/**
	 * Sets the e12^e23^e31 coordinate.
	 */
	public final void set_e12_e23_e31(float e12_e23_e31) { m_e12_e23_e31 = e12_e23_e31;}
	/**
	 * Returns the e01^e02^e03^e12^e23 coordinate.
	 */
	public final float get_e01_e02_e03_e12_e23() { return m_e01_e02_e03_e12_e23;}
	/**
	 * Sets the e01^e02^e03^e12^e23 coordinate.
	 */
	public final void set_e01_e02_e03_e12_e23(float e01_e02_e03_e12_e23) { m_e01_e02_e03_e12_e23 = e01_e02_e03_e12_e23;}
	/**
	 * Returns the e01^e02^e03^e12^e31 coordinate.
	 */
	public final float get_e01_e02_e03_e12_e31() { return m_e01_e02_e03_e12_e31;}
	/**
	 * Sets the e01^e02^e03^e12^e31 coordinate.
	 */
	public final void set_e01_e02_e03_e12_e31(float e01_e02_e03_e12_e31) { m_e01_e02_e03_e12_e31 = e01_e02_e03_e12_e31;}
	/**
	 * Returns the e01^e02^e03^e23^e31 coordinate.
	 */
	public final float get_e01_e02_e03_e23_e31() { return m_e01_e02_e03_e23_e31;}
	/**
	 * Sets the e01^e02^e03^e23^e31 coordinate.
	 */
	public final void set_e01_e02_e03_e23_e31(float e01_e02_e03_e23_e31) { m_e01_e02_e03_e23_e31 = e01_e02_e03_e23_e31;}
	/**
	 * Returns the e01^e02^e12^e23^e31 coordinate.
	 */
	public final float get_e01_e02_e12_e23_e31() { return m_e01_e02_e12_e23_e31;}
	/**
	 * Sets the e01^e02^e12^e23^e31 coordinate.
	 */
	public final void set_e01_e02_e12_e23_e31(float e01_e02_e12_e23_e31) { m_e01_e02_e12_e23_e31 = e01_e02_e12_e23_e31;}
	/**
	 * Returns the e01^e03^e12^e23^e31 coordinate.
	 */
	public final float get_e01_e03_e12_e23_e31() { return m_e01_e03_e12_e23_e31;}
	/**
	 * Sets the e01^e03^e12^e23^e31 coordinate.
	 */
	public final void set_e01_e03_e12_e23_e31(float e01_e03_e12_e23_e31) { m_e01_e03_e12_e23_e31 = e01_e03_e12_e23_e31;}
	/**
	 * Returns the e02^e03^e12^e23^e31 coordinate.
	 */
	public final float get_e02_e03_e12_e23_e31() { return m_e02_e03_e12_e23_e31;}
	/**
	 * Sets the e02^e03^e12^e23^e31 coordinate.
	 */
	public final void set_e02_e03_e12_e23_e31(float e02_e03_e12_e23_e31) { m_e02_e03_e12_e23_e31 = e02_e03_e12_e23_e31;}
	/**
	 * Returns the scalar coordinate (which is always 0).
	 */
	public final float get_scalar() { return 0.0f;}
} // end of class oddVersor
