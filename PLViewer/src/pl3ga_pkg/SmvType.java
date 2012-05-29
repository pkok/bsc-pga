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
public enum SmvType {
	PL3GA_MV(0, "mv"),
	PL3GA_FLOAT(1, "float"),
	PL3GA_E01_T(2, "e01_t"),
	PL3GA_E02_T(3, "e02_t"),
	PL3GA_E03_T(4, "e03_t"),
	PL3GA_E12_T(5, "e12_t"),
	PL3GA_E23_T(6, "e23_t"),
	PL3GA_E31_T(7, "e31_t"),
	PL3GA_I3R_T(8, "I3r_t"),
	PL3GA_I3I_T(9, "I3i_t"),
	PL3GA_I6_T(10, "I6_t"),
	PL3GA_LINE(11, "line"),
	PL3GA_IDEALLINE(12, "idealLine"),
	PL3GA_PENCIL(13, "pencil"),
	PL3GA_IDEALPENCIL(14, "idealPencil"),
	PL3GA_MIXEDPENCIL(15, "mixedPencil"),
	PL3GA_PSEUDOSCALAR(16, "pseudoscalar"),
	PL3GA_EVENVERSOR(17, "evenVersor"),
	PL3GA_ODDVERSOR(18, "oddVersor"),
	PL3GA_NONE(-1, "none");

	private final int id;
    private final String label;

    SmvType(final int id, final String label) {
        this.id = id;
        this.label = label;
    }
    
    public final int getId() {
        return id;
    }
 
    public final String toString() {
        return label;
    }
}
