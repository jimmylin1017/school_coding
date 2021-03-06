/*
 * builtin.c : check for shell built-in commands
 * structure of file is
 * 1. definition of builtin functions
 * 2. lookup-table
 * 3. definition of is_builtin and do_builtin
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"




/****************************************************************************/
/* builtin function definitions                                             */
/****************************************************************************/

/* "echo" command.  Does not print final <CR> if "-n" encountered. */
static void bi_echo(char **argv) {
  	/* Fill in code. */

	if (!strcmp(argv[1], "-n"))
	{
		int num = atoi(argv[2]);

		int count = 0;
		while (argv[count] != '\0') count++;

		if (num > 0 && count-3 >= num)
			printf("%s\n", argv[2+num]);
		else
			printf("input error!\n");
	}
	else
	{
		int i = 1;
		while (argv[i] != '\0')
		{
			printf("%s ", argv[i++]);
		}
		printf("\n");
	}
}
/* Fill in code. */
void bi_finish(char **argv)
{
	free_argv(argv);
	exit(0);
}



/****************************************************************************/
/* lookup table                                                             */
/****************************************************************************/

static struct cmd {
	char * keyword;				/* When this field is argv[0] ... */
	void (* do_it)(char **);	/* ... this function is executed. */
} inbuilts[] = {

	/* Fill in code. */

	{ "echo", bi_echo },		/* When "echo" is typed, bi_echo() executes.  */
	{ "exit", bi_finish},
	{ "quit", bi_finish},
	{ "logout", bi_finish},
	{ "bye", bi_finish},
	{ NULL, NULL }				/* NULL terminated. */
};




/****************************************************************************/
/* is_builtin and do_builtin                                                */
/****************************************************************************/

static struct cmd * this; 		/* close coupling between is_builtin & do_builtin */

/* Check to see if command is in the inbuilts table above.
Hold handle to it if it is. */
int is_builtin(char *cmd) {
  	struct cmd *tableCommand;

  	for (tableCommand = inbuilts ; tableCommand->keyword != NULL; tableCommand++)
    	if (strcmp(tableCommand->keyword,cmd) == 0) {
			this = tableCommand;
			return 1;
		}
  	return 0;
}


/* Execute the function corresponding to the builtin cmd found by is_builtin. */
int do_builtin(char **argv) {
  	this->do_it(argv);
}
