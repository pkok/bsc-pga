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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fontparse.h"

//int g_nbFPAllocated = 0;


fpNode *fpNodeAlloc(int type, int nbChildren) {
	fpNode *node = (fpNode *)calloc(sizeof(fpNode), 1);
	if (node == NULL) return NULL;

	node->type = type;

//	g_nbFPAllocated ++;

	if (fpSetNbChildren(node, nbChildren)) {
		free(node);
		return NULL;
	}
	return node;
}

void fpNodeFree(fpNode *node) {
	int i;
	if (node) {
//		g_nbFPAllocated --;
		if (node->child) {
			for (i = 0; i < node->nbChildren; i++)
				if (node->child[i])
					fpNodeFree(node->child[i]);
			free(node->child);
		}

		if (node->str) free(node->str);

		memset(node, 0, sizeof(fpNode));
		free(node);
	}
	else printf("fpNodeFree(): attempt to free() NULL node.\n");
}


int fpSetNbChildren(fpNode *node, int nbChildren) {
	int i;
	if (nbChildren) {
		node->child = (fpNode**)realloc(node->child, sizeof(fpNode*) * nbChildren);
	}
	else if (node->child) {
		free(node->child);
		node->child = NULL;
	}

	if (nbChildren && (node->child == NULL)) return -1;
//	printf("Setting %08X to NULL from %d to %d\n", node, node->nbChildren, nbChildren);
	for (i = node->nbChildren; i < nbChildren; i++) node->child[i] = NULL;
	node->nbChildren = nbChildren;
	return 0;
}

int fpSetChild(fpNode *parent, fpNode *child, int idx) {
//	printf("Set child %08p->%d to %08p\n", parent, idx, child);
	if ((parent == NULL) || (child == NULL) || (idx < 0) || (idx >= parent->nbChildren)) {
		printf("fpSetChild(): invalid input %08p %08p %d\n", parent, child, idx);
		return -1;
	}
	parent->child[idx] = child;
	child->parent = parent;
	return 0;
}

struct fpNode_s *fpDescentLeft(struct fpNode_s *node) {
	while (node->nbChildren && (node->child[0])) node = node->child[0];
	return node;
}

static void fpNodePrintTabs(int depth) {
	int i;
//	printf("Print %d tabs\n", depth);
	for (i = 0; i < depth; i++)
		printf("  ");
}

static int fpNodePrintInternal(const fpNode *node, int depth) {
//	printf("At node type %d\n", node->type);
	fpNodePrintTabs(depth);

	switch(node->type) {
	case fpnSentence:
		printf("sentence, %d children\n", (node->child[0] != NULL) + (node->child[1] != NULL));
		if (node->child[0])	fpNodePrintInternal(node->child[0], depth + 1);
		if (node->child[1])	fpNodePrintInternal(node->child[1], depth + 1);
		break;
	case fpnOption:
		printf("option {\n");
		fpNodePrintInternal(node->child[0], depth + 1);
		fpNodePrintTabs(depth); printf("}\n");
		break;
	case fpnOptionList:
		printf("optionlist, %d children\n", (node->child[0] != NULL) + (node->child[1] != NULL));
		if (node->child[0])	fpNodePrintInternal(node->child[0], depth + 1);
		if (node->child[1])	fpNodePrintInternal(node->child[1], depth + 1);
		break;
	case fpnWordWord:
		printf("word: %s\n", node->str);
		break;
	case fpnWordWhiteSpace:
		printf("whitespace: %d characters\n", node->nb);
		break;
	case fpnWordNumber:
		printf("number: %s\n", node->str);
		break;
	case fpnWordCommand:
		printf("command: '%s' {\n", node->str + 1);
		fpNodePrintInternal(node->child[0], depth + 1);
		fpNodePrintTabs(depth); printf("}\n");
		break;
	case fpnWordCommandNoOption:
		printf("optionless command: '%s'\n", node->str + 1);
		break;
	case fpnWordSpecialChar:
		printf("specialchar: %d\n", node->nb);
		break;
	case fpnWordSuperscript:
		printf("superscript:\n");
		fpNodePrintInternal(node->child[0], depth + 1);
		break;
	case fpnWordSubscript:
		printf("subscript:\n");
		fpNodePrintInternal(node->child[0], depth + 1);
		break;
	default:
		printf("fpNodePrintInternal(): unknown node type '%d'\n", node->type);
		return -1;
	}

	return 0;
}

int fpNodePrint(const fpNode *node) {
	return fpNodePrintInternal(node, 0);
}


fpNode *fpNodeDuplicate(const fpNode *node) {
	int err, i;
	fpNode *dupl, *duplChild;
	
	// allocate new node
	if ( (dupl = fpNodeAlloc(node->type, node->nbChildren)) == NULL)
		return NULL;

	// copy/duplicate attributes
	dupl->parent = NULL;
	dupl->str = (node->str) ? strdup(node->str) : NULL;
	dupl->nb = node->nb;
	dupl->flags = node->flags;
	dupl->inputIdx = node->inputIdx;
	// IMPORTANT: todo: other attributes when introduced...

	// duplicate children
	err = 0;
	for (i = 0; i < dupl->nbChildren; i++) {
		if (node->child[i]) {
			if ( (duplChild = fpNodeDuplicate(node->child[i])) == NULL) {
				printf("fpNodeDuplicate(): node duplication error\n");
				err = -1;
				break;
			}
			if (err = fpSetChild(dupl, duplChild, i))
				break;
		}
		else node->child[i] = NULL;
	}

	// error checking
	if (err || (node->str && (dupl->str == NULL))) {
		fpNodeFree(dupl);
		return NULL;
	}

	return dupl;
}

int fpNodeSetInputIdx(fpNode *node, int idx) {
	int i, err = 0;
	if (node == NULL) return 0;
	node->inputIdx = idx;
	for (i = 0; i < node->nbChildren; i++)
		err |= fpNodeSetInputIdx(node->child[i], idx);
	return err;
}


int fpNodeSubstituteCustomCommandArguments(
		struct fpNode_s *node, int nbOptions, struct fpNode_s *option[],
		const char *cmdStr) {
	int i, err;
	struct fpNode_s *argNode, *lastArgNode;
	struct fpNode_s *parentNode;


	if ((node->type == fpnWordCommandArg) && 
		(parentNode = node->parent) &&
		(parentNode->type == fpnSentence)) {
		// check if we have the right argument
		if ((node->nb < 1) || (node->nb > nbOptions) ||
			(option[node->nb-1] == NULL) || (option[node->nb-1]->child[0] == NULL)) {
			printf("fpNodeSubstituteCustomCommandArguments(): argument '%d' not supplied for custom command '%s'\n", node->nb, cmdStr);
			return 0;
		}

		// duplicate option
		if ( (argNode = fpNodeDuplicate(option[node->nb-1]->child[0])) == NULL)
			return -1;
		lastArgNode = fpDescentLeft(argNode);

		// insert option into tree
		lastArgNode->child[0] = parentNode->child[0];
		if (parentNode->child[0])
			parentNode->child[0]->parent = lastArgNode;
		argNode->parent = parentNode;
		parentNode->child[0] = argNode;
		parentNode->child[1] = NULL;

		// free the node
		fpNodeFree(node);		
		return 0;
	}

	for (i = 0; i < node->nbChildren; i++) {
		if (node->child[i]) {
			if (err = fpNodeSubstituteCustomCommandArguments(node->child[i], nbOptions, option, cmdStr))
				return err;
		}
	}

	return 0;
}

int fpNodeFindTypeStr(const fpNode *node, int type, const char *str) {
	int i;
	if (node == NULL) return 0;
	if ((node->type == type) && (!strcmp(node->str, str))) return 1;
	for (i = 0; i < node->nbChildren; i++)
		if (fpNodeFindTypeStr(node->child[i], type, str)) return 1;
	return 0;
}
