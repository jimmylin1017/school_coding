/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {

  	static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;

  	/* Nothing entered. */
  	if (line == NULL) {
    	return NULL;
  	}

  	/* Init strtok with commandline, then get first token.
     * Return NULL if no tokens in line.
	 *
	 * Fill in code.
     */
	token = strtok(line,delim);
	if(token == NULL)
		return NULL;
	 

  	/* Create array with room for first token.
  	 *
	 * Fill in code.
	 */
	count++;
	newArgv = (char**)malloc(sizeof(char*)*count);
	newArgv[count-1] = (char*)malloc(sizeof(char)*(strlen(token)+1));
	//The  strcpy()  function  copies the string pointed to by src, including the terminating null byte ('\0')
	strcpy(newArgv[count-1],token);


  	/* While there are more tokens...
	 *
	 *  - Get next token.
	 *	- Resize array.
	 *  - Give token its own memory, then install it.
	 * 
  	 * Fill in code.
	 */
  	while(token != NULL)
  	{
  		if ((token = strtok(NULL,delim)) == NULL) break;
  		count++;
		newArgv = (char**)realloc(newArgv, sizeof(char*)*count);
		newArgv[count-1] = (char*)malloc(sizeof(char)*(strlen(token)+1));
		strcpy(newArgv[count-1],token);
  	}

  	/* Null terminate the array and return it.
	 *
  	 * Fill in code.
	 */
	int i = 0;
	newArgv = (char**)realloc(newArgv, sizeof(char*)*(count+1));
	newArgv[count] = '\0';

	while (newArgv[i] != '\0')
	{
		printf("[%d] : %s\n",i,newArgv[i]);
		i++;
	}
	
  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;

	/* Free each string hanging off the array.
	 * Free the oldArgv array itself.
	 *
	 * Fill in code.
	 */
	while (oldArgv[i] != '\0')
	{
		free(oldArgv[i]);
		i++;
	}
	//free(oldArgv[i]);

	free(oldArgv);
}
