/*
 * convert.c : take a file in the form 
 *  word1
 *  multiline definition of word1
 *  stretching over several lines, 
 * followed by a blank line
 * word2....etc
 * convert into a file of fixed-length records
 */

#include "dict.h"

#define BIGLINE 512

int main(int argc, char **argv) {
	FILE *in;
	FILE *out;        /* defaults */
	char line[BIGLINE];
	static Dictrec dr;//, blank;
	
	/* If args are supplied, argv[1] is for input, argv[2] for output */
	if (argc==3) {
		if ((in =fopen(argv[1],"r")) == NULL){DIE(argv[1]);}
		if ((out =fopen(argv[2],"w")) == NULL){DIE(argv[2]);}	
	}
	else{
		printf("Usage: convert [input file] [output file].\n");
		return -1;
	}

	/* Main reading loop : read word first, then definition into dr */

	/* Loop through the whole file. */
	while (!feof(in)) {
		
		/* Create and fill in a new blank record.
		 * First get a word and put it in the word field, then get the definition
		 * and put it in the text field at the right offset.  Pad the unused chars
		 * in both fields with nulls.
		 */

		int counter = 1;
		int len = 0;

		memset(dr.word, '\0', sizeof(dr.word));
		memset(dr.text, '\0', sizeof(dr.text));

		while(1)
		{
			fgets(line, BIGLINE, in);
			line[strlen(line)-1] = '\0';

			if(line[0] == '\0') break;

			if(counter)
			{
				strcpy(dr.word,line);
				counter = 0;
			}
			else
			{
				strcpy(dr.text+len,line);
				len = len + strlen(line);
				DEBUG("%d\n", len);
			}
		}
		
		DEBUG("%s\n", dr.text);
			

		/* Read word and put in record.  Truncate at the end of the "word" field.
		 *
		 * Fill in code. */


		/* Read definition, line by line, and put in record.
		 *
		 * Fill in code. */

		/* Write record out to file.
		 *
		 * Fill in code. */
		if(dr.word[0] != '\0')
		{
			fwrite(dr.word , sizeof(char), sizeof(dr.word), out);
			fwrite(dr.text , sizeof(char), sizeof(dr.text), out);
			//fprintf(out, "%s\n%s\n", dr.word, dr.text);
		}
			
	}

	fclose(in);
	fclose(out);
	return 0;
}
