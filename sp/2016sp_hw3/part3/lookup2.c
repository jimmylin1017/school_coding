/*
 * lookup2 : local file ; setup an in-memory index of words
 *             and pointers into the file. resource is file name
 *             use qsort & bsearch
 */

#include "dict.h"

typedef struct {
    char word[WORD];  /* The word to be looked up */
    long off;         /* Offset into file for word definition */
} Index;

/*
 * This ugly little function can be used by qsort & bsearch
 * It compares the word part of two structures of type Index
 */

int dict_cmp(const void *a,const void *b) {
	return strcmp(((Index *)a)->word,((Index *)b)->word);
}

int lookup(Dictrec * sought, const char * resource) {
	static Index * table;
	Dictrec dr;
	static int numrec;
	int i;
	Index * found,tmp;
	static FILE * in;
	static int first_time = 1;

	if (first_time) { /* set up index */
		first_time = 0;

		/* Open file.
		 *
		 * Fill in code. */
		if ((in = fopen(resource,"r")) == NULL)
		{
			DIE(resource);
		}

		/* Get number records in file by dividing ending file offset by recsize.
		 *
		 * Fill in code. */
		numrec = 0;
		while(fread(&dr, sizeof(Dictrec), 1, in) > 0)
		{
			numrec++;
		}

		/* Go to the beginning of the file.
		 *
		 * Fill in code. */
		rewind(in);

		/* Allocate zeroed-out memory: numrec elements of struct Index. */
		table = calloc(sizeof(Index),numrec);

		/* Read the file into the just-allocated array in memory.
		 *
		 * Fill in code. */
		for(i = 0;i < numrec;i++)
		{
			fread(&dr, sizeof(Dictrec), 1, in);
			strcpy(table[i].word, dr.word);
			table[i].off = i*(TEXT + WORD) + WORD;
			DEBUG("%s : %ld\n", table[i].word, table[i].off);
		}

		/* Sort the table of entry/offset Index structures. */
		qsort(table,numrec,sizeof(Index),dict_cmp);

	} /* end of first-time initialization */

	/* use bsearch to find word in the table; seek & read from file if found. */
	strcpy(tmp.word,sought->word);
	found = bsearch(&tmp,table,numrec,sizeof(Index),dict_cmp);

	/* If found, go to that place in the file, and read the record into the
	 * caller-supplied space. */
	if (found) {
		/* Fill in code. */
		fseek(in, found->off, SEEK_SET);
		DEBUG("%s : %ld\n", found->word, found->off);

		fread(sought->text, sizeof(sought->text), 1, in);

		return FOUND;
	}
	return NOTFOUND;
}
