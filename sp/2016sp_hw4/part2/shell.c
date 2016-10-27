/*
 * shell.c  : test harness for parse routine
 */

#define LONGLINE 255

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

int main(int argc, char* argv[]) {
	char line[LONGLINE];
	char **myArgv;

  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);

	fputs("myshell -> ",stdout);
	while (fgets(line,LONGLINE,stdin)) {
   
    set_timer();
  	/* Create argv array based on commandline. */
  	if ((myArgv = parse(line))!= NULL) {

    		/* If command is recognized as a builtin, do it. */
    		if (is_builtin(myArgv[0])) {

          DEBUG("is_builtin\n");
      		do_builtin(myArgv);

    		/* Non-builtin command. */
    		} else {
          DEBUG("run_command\n");
    			run_command(myArgv);
    		}

    		/* Free argv array. */
        DEBUG("call free_argv\n");
    		free_argv(myArgv);
    }
    stop_timer();

    fputs("myshell -> ",stdout);
	}

  exit(0);
}
