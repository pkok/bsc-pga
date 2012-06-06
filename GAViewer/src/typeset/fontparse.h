// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

// Copyright 2002-2009, Daniel Fontijne, University of Amsterdam -- fontijne@science.uva.nl

#ifndef _FONTPARSE_H_
#define _FONTPARSE_H_


// the #ifndef WIN32 is a quick fix for some windows compile probs...
//#ifndef WIN32
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
//#endif /* WIN32 */

extern int fontParseParse();
extern int fontParseSetInputBuf(const char*buf, int l);
extern struct fpNode_s *fontParse(const char *str, const char *mode);
extern int fontParsePrintInput(int inputIdx, int chrBefore, int chrAfter);

enum {
	fpnSentence, 
	fpnOption,
	fpnOptionList,
	fpnWordWord,
	fpnWordWhiteSpace,
	fpnWordNumber,
	fpnWordCommand,
	fpnWordCommandNoOption, 
	fpnWordCommandArg, 
	fpnWordSpecialChar,
	fpnWordSuperscript,
	fpnWordSubscript
};

enum {
	fpfPopFont = 1, // when this node has been processed, pop font from state
	fpfPopMode = 2, // when this node has been processed, pop mode from state
	fpfPopAlign = 4, // when this node has been processed, pop alignment from state
	fpfPopSize = 8, // when this node has been processed, pop font size from state
	fpfPopColor = 16, // when this node has been processed, pop font size from state
	fpfSubscript = 256, // subscript is present (is this constant used?)
	fpfSuperscript = 512 // subsuperscript is present (is this constant used?)
};

typedef struct fpNode_s {
	int type; // fpnXXX
	struct fpNode_s *parent;
	struct fpNode_s **child;
	int nbChildren;
//	YYSTYPE yAttribute; // yacc attribbyte
	char *str;
	int nb;
	int flags; //fpfXXX
	// other attributes
	int inputIdx; // index in input string
} fpNode;

fpNode *fpNodeAlloc(int type, int nbChildren);
void fpNodeFree(fpNode *node);
int fpSetNbChildren(fpNode *node, int nbChildren);
int fpSetChild(fpNode *parent, fpNode *child, int idx);
fpNode *fpNodeDuplicate(const fpNode *node); // returns an exact duplicate of 'node' (all memory allocated); used for implementing user commands
int fpNodeSetInputIdx(fpNode *node, int idx); // set the input idx of node & children to 'idx' (used for command substitution)

// returns the left-most (grand) child of node
struct fpNode_s *fpDescentLeft(struct fpNode_s *node); 

// substitutes all \1, \2 ... \9's with the 'option[]' supplied
int fpNodeSubstituteCustomCommandArguments(
		struct fpNode_s *node, int nbOptions, struct fpNode_s *option[],
		const char *cmdStr);



int fpNodePrint(const fpNode *node);

// returns true if a node is found in the tree that has type 'type' and whose string is 'str'
int fpNodeFindTypeStr(const fpNode *node, int type, const char *str);
	
//#ifndef WIN32
#ifdef __cplusplus
}
#endif /* __cplusplus */
//#endif /* WIN32 */

#endif /* _FONTPARSE_H_ */
