/*
 *
 * Gaigen, Copyright (c) 2001-2004, University of Amsterdam
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *      * Redistributions of source code must retain the above copyright 
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright 
 *        notice, this list of conditions and the following disclaimer in 
 *        the documentation and/or other materials provided with the 
 *        distribution. 
 *      * Neither the name of the University of Amsterdam nor the names of its 
 *        contributors may be used to endorse or promote products derived 
 *        from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _CODETEMPLATE_H_
#define _CODETEMPLATE_H_

#include <stdio.h> 

class codeTemplateContainer;

#define CT_CHAR 1
#define CT_CR 2
#define CT_VAR 3



class codeTemplate {
public:
	codeTemplate(const char *name);
	~codeTemplate();

	void initToNothing();

	int print(FILE *F, codeTemplateContainer *con);

	int addEntry(char *entry);

	char *m_name;

	int m_nbEntries, m_maxEntries;
	char **m_entry;
};

class codeTemplateContainer {
public:
	codeTemplateContainer();
	~codeTemplateContainer();

	void initToNothing();

	/* lookup table for strings for templates */
	int m_nbLUTEntries, m_maxLUTEntries;
	char **m_LUTEntry;	// array of pointers to arrays of characters; each character array contains two concatenated ASCIIZ strings
	char *getLUTEntry(const char *name);
	int setLUTEntry(const char *name, const char *value);
	int setLUTEntry(const char *name, int value);
	int setLUTEntry(const char *name, float value);

	/* codetemplates */
	int m_nbCodeTemplates;
	codeTemplate **m_codeTemplate;
	int addCodeTemplate(codeTemplate *bl);
	int getCodeTemplate(const char *name, codeTemplate **bl);
	int printCodeTemplate(FILE *F, const char *name);	// prints a codetemplate using the current lookup table string definitions

	/* reading/parsing template files */
	int readTemplateFile(const char *templateFilename);
	int flushTemplates();
};

#endif /* _CODETEMPLATE_H_ */
