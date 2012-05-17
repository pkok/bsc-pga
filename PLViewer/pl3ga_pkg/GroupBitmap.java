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
public interface GroupBitmap {
	public static final int GROUP_0  = 1; // 1
	public static final int GROUP_1  = 2; // e01, e02, e03, e12, e23, e31
	public static final int GROUP_2  = 4; // e01^e02, e01^e03, e02^e03, e01^e12, e02^e12, e03^e12, e01^e23, e02^e23, e03^e23, e12^e23, e01^e31, e02^e31, e03^e31, e12^e31, e23^e31
	public static final int GROUP_3  = 8; // e01^e02^e03, e01^e02^e12, e01^e03^e12, e02^e03^e12, e01^e02^e23, e01^e03^e23, e02^e03^e23, e01^e12^e23, e02^e12^e23, e03^e12^e23, e01^e02^e31, e01^e03^e31, e02^e03^e31, e01^e12^e31, e02^e12^e31, e03^e12^e31, e01^e23^e31, e02^e23^e31, e03^e23^e31, e12^e23^e31
	public static final int GROUP_4  = 16; // e01^e02^e03^e12, e01^e02^e03^e23, e01^e02^e12^e23, e01^e03^e12^e23, e02^e03^e12^e23, e01^e02^e03^e31, e01^e02^e12^e31, e01^e03^e12^e31, e02^e03^e12^e31, e01^e02^e23^e31, e01^e03^e23^e31, e02^e03^e23^e31, e01^e12^e23^e31, e02^e12^e23^e31, e03^e12^e23^e31
	public static final int GROUP_5  = 32; // e01^e02^e03^e12^e23, e01^e02^e03^e12^e31, e01^e02^e03^e23^e31, e01^e02^e12^e23^e31, e01^e03^e12^e23^e31, e02^e03^e12^e23^e31
	public static final int GROUP_6  = 64; // e01^e02^e03^e12^e23^e31

	public static final int ALL_GROUPS = 127; // all groups

	public static final int GRADE_0 = 1;
	public static final int GRADE_1 = 2;
	public static final int GRADE_2 = 4;
	public static final int GRADE_3 = 8;
	public static final int GRADE_4 = 16;
	public static final int GRADE_5 = 32;
	public static final int GRADE_6 = 64;

	public static final int ALL_GRADES = 127; // all grades

}
