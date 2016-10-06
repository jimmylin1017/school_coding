/*
 * run_command.c :    do the fork, exec stuff, call other functions
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include "shell.h"

void run_command(char **myArgv) {
  	pid_t pid;
  	int stat;
  	int run_in_background;
    int i;

  	/*
   	* Check for background processing.
   	* Do this before fork() as the "&" is removed from the argv array
   	* as a side effect.
   	*/
  	run_in_background = is_background(myArgv);

    DEBUG("is_background %d\n", run_in_background);

  	switch(pid = fork()) {

    	/* Error. */
    	case -1 :
      		perror("fork");
      		exit(errno);

    	/* Parent. */
    	default :
      		if (!run_in_background) {
        		waitpid(pid,&stat,0);	/* Wait for child to terminate. */

        		if (WIFEXITED(stat) && WEXITSTATUS(stat)) {
          			fprintf(stderr, "Child %d exited with error status %d: %s\n",
	      				pid, WEXITSTATUS(stat), (char*)strerror(WEXITSTATUS(stat)));

        		} else if (WIFSIGNALED(stat) && WTERMSIG(stat)) {
	  				fprintf (stderr, "Child %d exited due to signal %d: %s\n",
	      				pid, WTERMSIG(stat), (char*)strsignal(WTERMSIG(stat)));
        		}
      		}
      		return;

    	/* Child. */
    	case 0 :

      		/* Redirect input and update argv. */
          if(redirect_in(myArgv) == -1)
          {
            perror("redirect_in");
            exit(1);
          }
          DEBUG("redirect_in finish\n");
          

      		/* Redirect output and update argv. */
          if(redirect_out(myArgv) == -1)
          {
            perror("redirect_out");
            exit(1);
          }
          DEBUG("redirect_out finish\n");

          if(run_in_background == TRUE)
          {
              int i = 0;
              while (myArgv[i] != '\0') i++;
              if (!strcmp(myArgv[i-1], "&")) myArgv[i-1] = '\0';
          }
          
      		pipe_and_exec(myArgv);
      		exit(errno);
	}
}
