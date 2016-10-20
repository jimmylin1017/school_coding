/*
 * lookup1 : straight linear search through a local file
 * 	         of fixed length records. The file name is passed
 *	         as resource.
 */

#include "dict.h"

int lookup(Dictrec * sought, const char * resource) {
	Dictrec dr;
	static FILE * in;
	static int first_time = 1;

	if (first_time) { 
		first_time = 0;
		/* open up the file
		 *
		 * Fill in code. */
		if ((in = fopen(resource,"r")) == NULL)
		{
			DIE(resource);
		}
	}

	/* read from top of file, looking for match
	 *
	 * Fill in code. */
	rewind(in);
	
	while(!feof(in)) {
		/* Fill in code. */
		fread(&dr, sizeof(Dictrec), 1, in);
		if(!strcmp(dr.word, (*sought).word))
		{
			strcpy((*sought).text, dr.text);
			return FOUND;
		}
	}

	return NOTFOUND;
}
