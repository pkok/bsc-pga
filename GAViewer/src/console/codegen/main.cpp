/*
A little code generator for the console of GAViewer.

*/
#include <stdio.h>
#include <time.h>

#include "codetemplate.h"

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Usage: %s templates.txt output.cpp\n", argv[0]);
		return -1;
	}

	// open templates, output file
	codeTemplateContainer ctc;
	if (ctc.readTemplateFile(argv[1]) < 0) 
		return -1;

	FILE *F = fopen(argv[2], "w+");
	if (F == NULL) return -1;

	// output header info
	time_t t = time(NULL);
	fprintf(F, "// Generated on %s\n", ctime(&t));
	ctc.setLUTEntry("AFN", "${AFN}");
	ctc.setLUTEntry("AFNC", "${AFNC}");
	ctc.setLUTEntry("AFNFLC", "${AFNFLC}");
	ctc.setLUTEntry("ASN", "${ASN}");
	ctc.printCodeTemplate(F, "comments");
	ctc.printCodeTemplate(F, "includes");

	// define the algebras
	struct {
		const char *afn, *afnc, *afnflc, *asn;
	} algebras[] = {
		{"e3ga", "E3GA", "E3ga", "e"},
		{"p3ga", "P3GA", "P3ga", "p"},
		{"c3ga", "C3GA", "C3ga", "c"},
		{"c5ga", "C5GA", "C5ga", "c5"},
		{"i2ga", "I2GA", "I2ga", "i2"},

		{NULL, NULL, NULL}
	};
	
	int i, j;

	// output function bodies
	i = 0;
	while (algebras[i].afn) {
		ctc.setLUTEntry("AFN", algebras[i].afn);
		ctc.setLUTEntry("AFNC", algebras[i].afnc);
		ctc.setLUTEntry("AFNFLC", algebras[i].afnflc);
		ctc.setLUTEntry("ASN", algebras[i].asn);
		ctc.printCodeTemplate(F, "functionBodies");
		i++;
	}

	// output cast function bodies
	i = 0;
	while (algebras[i].afn) {
		j = 0;
		while (algebras[j].afn) {
			ctc.setLUTEntry("AFN", algebras[i].afn);
			ctc.setLUTEntry("AFNC", algebras[i].afnc);
			ctc.setLUTEntry("AFNFLC", algebras[i].afnflc);
			ctc.setLUTEntry("ASN", algebras[i].asn);
			ctc.setLUTEntry("AFN2", algebras[j].afn);
			ctc.setLUTEntry("AFNC2", algebras[j].afnc);
			ctc.setLUTEntry("AFNFLC2", algebras[j].afnflc);
			ctc.setLUTEntry("ASN2", algebras[j].asn);
			ctc.printCodeTemplate(F, "cast");
			j++;
		}
		i++;
	}

	ctc.printCodeTemplate(F, "point");

	ctc.printCodeTemplate(F, "transformation");

	ctc.printCodeTemplate(F, "draw_properties");

	ctc.printCodeTemplate(F, "bit_wise");

	ctc.printCodeTemplate(F, "system");

	ctc.printCodeTemplate(F, "help");
	
	ctc.printCodeTemplate(F, "functionsListHeader");

	// output function list
	i = 0;
	while (algebras[i].afn) {
		ctc.setLUTEntry("AFN", algebras[i].afn);
		ctc.setLUTEntry("AFNC", algebras[i].afnc);
		ctc.setLUTEntry("ASN", algebras[i].asn);
		ctc.printCodeTemplate(F, "functionList");
		i++;
	}

	// output cast function list
	i = 0;
	while (algebras[i].afn) {
		j = 0;
		while (algebras[j].afn) {
			ctc.setLUTEntry("AFN", algebras[i].afn);
			ctc.setLUTEntry("AFNC", algebras[i].afnc);
			ctc.setLUTEntry("AFNFLC", algebras[i].afnflc);
			ctc.setLUTEntry("ASN", algebras[i].asn);
			ctc.setLUTEntry("AFN2", algebras[j].afn);
			ctc.setLUTEntry("AFNC2", algebras[j].afnc);
			ctc.setLUTEntry("AFNFLC2", algebras[j].afnflc);
			ctc.setLUTEntry("ASN2", algebras[j].asn);
			ctc.printCodeTemplate(F, "functionListCast");
			j++;
		}
		i++;
	}


	ctc.printCodeTemplate(F, "functionsListTrailer");

	fclose(F);


	return 0;
}