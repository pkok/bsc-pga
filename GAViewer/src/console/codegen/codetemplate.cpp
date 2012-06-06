/*
Gaigen, Copyright (c) 2001-2003, University of Amsterdam

Copying, use and development for education and research purposes 
permitted as long as this license is not removed from the files.

All rights for commercial use reserved; for more information
contact Daniel Fontijne (fontijne@science.uva.nl)

This software is unsupported.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codetemplate.h"
//#include "gaspec.h"

codeTemplate::codeTemplate(const char *name) {
	initToNothing();

	m_name = (char*)malloc(strlen(name) + 1);
	strcpy(m_name, name);
}

codeTemplate::~codeTemplate() {
	free(m_name);
	initToNothing();
}

void codeTemplate::initToNothing() {
	m_nbEntries = m_maxEntries = 0;
	m_entry = NULL;
	m_name = NULL;
}

int codeTemplate::print(FILE *F, codeTemplateContainer *con) {
	int i, type;
	char *e;
	const char *var;

	for (i = 0; i < m_nbEntries; i++) {
		e = m_entry[i];
		type = e[0];
		e++;
		switch (type) {
		case CT_CHAR:
			fwrite(e, 1, strlen(e), F);	// don't use fprintf->fails trouble when 'e' contains '%d' or '%s' or whatever
			break;
		case CT_CR:
			fprintf(F, "\n");
			break;
		case CT_VAR:
			var = con->getLUTEntry(e);
			if (var == NULL) fprintf(F, "${%s}", e);
			else fprintf(F, var);
			break;
		default:
			fprintf(stderr, "codeTemplate::print(): invalid type '%d'\n", type);
			return -1;
		}
	}
	return 0;
}

int codeTemplate::addEntry(char *entry) {
	m_nbEntries++;
//	printf("Add entry of type %d\n", entry[0]);
	if (m_nbEntries >= m_maxEntries) {
		m_maxEntries = m_nbEntries * 2;
		if ( (m_entry = (char**)realloc(m_entry, m_maxEntries * sizeof(char*))) == NULL)
			return -1;
	}
	if ( (m_entry[m_nbEntries-1] = (char *)calloc(1, strlen(entry) + 1)) == NULL)
		return -1;
	strcpy(m_entry[m_nbEntries-1], entry);
	return 0;
}



codeTemplateContainer::codeTemplateContainer() {
	initToNothing();
}

codeTemplateContainer::~codeTemplateContainer() {
	int i;

	for (i = 0; i < m_nbLUTEntries; i++)
		if (m_LUTEntry[i]) free(m_LUTEntry[i]);
	if (m_LUTEntry) free(m_LUTEntry);

	flushTemplates();

	initToNothing();
}

void codeTemplateContainer::initToNothing() {
	m_nbLUTEntries = m_maxLUTEntries = 0;
	m_LUTEntry = NULL;
	m_nbCodeTemplates = 0;
	m_codeTemplate = NULL;
}

char *codeTemplateContainer::getLUTEntry(const char *name) {
	int i;

	for (i = 0; i < m_nbLUTEntries; i++)
		if (!strcmp(name, m_LUTEntry[i]))
			return m_LUTEntry[i] + strlen(m_LUTEntry[i]) + 1;

	return NULL;
}

int codeTemplateContainer::setLUTEntry(const char *name, const char *value) {
	int i, oldMax, l = (int)strlen(name) + (int)strlen(value) + 2;

	for (i = 0; i < m_nbLUTEntries; i++) {	// check if an entry with name 'name' is already present
		if (!strcmp(name, m_LUTEntry[i]))
			break;
	}

	if (i == m_nbLUTEntries) {	// we should create a new entry
		m_nbLUTEntries++;
		if (m_nbLUTEntries >= m_maxLUTEntries) { // allocate more memory
			oldMax = m_maxLUTEntries;
			m_maxLUTEntries = m_nbLUTEntries * 2;
			if ( (m_LUTEntry = (char**)realloc(m_LUTEntry, sizeof(char*) * m_maxLUTEntries)) == NULL)
				return -1;
			memset(m_LUTEntry + oldMax, 0, (m_maxLUTEntries - oldMax) * sizeof(char*));
		}
	}

	if ( (m_LUTEntry[i] = (char*)realloc(m_LUTEntry[i], l)) == NULL)
		return -1;

//	printf("Set lut entry %s -> %s, %d\n", name, value, m_nbLUTEntries);

	sprintf(m_LUTEntry[i], "%s%c%s", name, '\0', value);
	return 0;
}

int codeTemplateContainer::setLUTEntry(const char *name, int value) {
	char buf[256];
	sprintf(buf, "%d", value);
	return setLUTEntry(name, buf);
}

int codeTemplateContainer::setLUTEntry(const char *name, float value) {
	char buf[256];
	sprintf(buf, "%f", value);
	return setLUTEntry(name, buf);
}




int codeTemplateContainer::addCodeTemplate(codeTemplate *bl) {
	codeTemplate *tmpBl;
	if (getCodeTemplate(bl->m_name, &tmpBl) == 0) {
		fprintf(stderr, "codeTemplateContainer::addCodeTemplate(): codetemplate '%s' is already defined\n", bl->m_name);
		return 0;
	}

	if ( (m_codeTemplate = (codeTemplate**)realloc(m_codeTemplate, sizeof(codeTemplate*) * (m_nbCodeTemplates+1))) == NULL)
		return -1;

	m_codeTemplate[m_nbCodeTemplates] = bl;
	m_nbCodeTemplates++;

	return 0;
}

int codeTemplateContainer::getCodeTemplate(const char *name, codeTemplate **bl) {
	int i;
	*bl = NULL;
	for (i = 0; i < m_nbCodeTemplates; i++)
		if (!strcmp(m_codeTemplate[i]->m_name, name)) {
			*bl = m_codeTemplate[i];
			return 0;
		}
	return -1;
}

int codeTemplateContainer::printCodeTemplate(FILE *F, const char *name) {
	codeTemplate *bl;
	int err;
	if (err = getCodeTemplate(name, &bl)) {
		fprintf(stderr, "codeTemplateContainer::printCodeTemplate(): can not find codetemplate '%s'\n", name);
		return err;
	}
	return bl->print(F, this);
}

static int readline(FILE *F, char *line, int maxLen) {
	int i = 0;
	char *ptr;

	// read characters from the file until the end of the file is reached, a error occurs, or the end of the line is reached
	while (i < maxLen) {
		ptr = fgets(line + i, 2, F);
		i++;
		if ((ptr == NULL) && ferror(F)) return -1;
		else if (ptr == NULL) {i--; break;}
		if (*ptr == 0x0a) break;
	}

	if (i == 0) return -1;
	else if ((i > 1) && (line[i-2] == 0x0d)) {	// take care of dos-style carriage returns
		line[i-2] = 0x0a;
		i--;
	}

	if (line[i-1] != 0x0a) line[i++] = 0x0a; // make sure a cr appears at the end of the line

	line[i] = 0; // line ends with a zero

	return 0;
}

int codeTemplateContainer::readTemplateFile(const char *templateFilename) {
	FILE *F;
	int linenumber = 1;
	int err;
	const int maxLineLength = 1024;
	char line[maxLineLength];
	char str[maxLineLength];
	char codetemplatename[maxLineLength];
	int i, j, l;
	codeTemplate *bl = NULL;

	if ( (F = fopen(templateFilename, "rb")) == NULL) {
		fprintf(stderr, "codeTemplateContainer::readTemplateFile(): can not open '%s'\n", templateFilename);
		return -1;
	}

	// read lines and build codeTemplates until the end of the file is reached
	while (!(err = readline(F, line, maxLineLength-1))) {
		i = 0;
		j = 1;
		while (line[i]) {
			if (((line[i] == '$') && (line[i + 1] == '{')) || (line[i] == 0x0a)) {	// end of normal string part?
				if (j > 1) { // code
					str[0] = CT_CHAR;
					str[j] = 0;
					if (bl) bl->addEntry(str);
					else {
						for (j = 1; str[j]; j++)
							if (str[j] > 32) {// if not white space, tabs, etc...
								fprintf(stderr, "codeTemplateContainer::readTemplateFile(): warningcode outside codetemplate at line %d\n", linenumber);
								break;
							}
					}
					j = 1;
				}
				if (line[i] == 0x0a) {	// end of line
					str[0] = CT_CR;
					str[1] = 0;
					if (bl) bl->addEntry(str);
					j = 1;
				}
				else {	// scan for end of ${VAR} block
					i += 2;
					j = 1;
					while (line[i] && (line[i] != '}'))
						str[j++] = line[i++];

					if (!line[i]) {
						fprintf(stderr, "codeTemplateContainer::readTemplateFile(): error parsing ${VARIABLE} at line %d\n", linenumber);
						fclose(F);
						delete bl;
						return -1;
					}
					else { // process new variable or start/end of codetemplate
						str[j] = 0;
						str[0] = CT_VAR;
						l = (int)strlen("CODEBLOCK");
						if (strstr(str + 1, "CODEBLOCK") == (str + 1)) {	// start of codetemplate
							if (str[1 + l] != ' ')
								fprintf(stderr, "codeTemplateContainer::readTemplateFile(): illegal codetemplate start at line %d\n", linenumber);
							strcpy(codetemplatename, str + 2 + l);

							if (bl) {	// check to see if other codetemplate is still open...
								fprintf(stderr, "codeTemplateContainer::readTemplateFile(): illegal start of codetemplate '%s' at line '%d' (codetemplate '%s' is still open)\n", codetemplatename, linenumber, bl->m_name);
								fclose(F);
								delete bl;
								return -1;
							}
							bl = new codeTemplate(codetemplatename);
						}
						else if (strstr(str + 1, "ENDCODEBLOCK") == (str + 1)) {
							if (err = addCodeTemplate(bl)) return err;
							bl = NULL;
						}
						else { // normal entry
							bl->addEntry(str);
						}
					}
					j = 1;
				}
			}
			else str[j++] = line[i];

			i++;

		}

		linenumber++;
	}


	if (!feof(F)) fprintf(stderr, "codeTemplateContainer::readTemplateFile(): error reading '%s'\n", templateFilename);
	fclose(F);

	return 0;
}

int codeTemplateContainer::flushTemplates() {
	int i;

	for (i = 0; i < m_nbCodeTemplates; i++)
		if (m_codeTemplate[i]) delete m_codeTemplate[i];
	if (m_codeTemplate) delete m_codeTemplate;
	m_codeTemplate= NULL;
	m_nbCodeTemplates = 0;

	return 0;
}
