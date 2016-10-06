/* 
 * pipe_command.c  :  deal with pipes
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"

#define STD_OUTPUT 1
#define STD_INPUT  0

void pipe_and_exec(char **myArgv) {
  	int pipe_argv_index = pipe_present(myArgv);
  	int pipefds[2];
	char **left_argv;
	char **right_argv;

    pid_t pid;
    int i;
    int status;
  	switch (pipe_argv_index) {

    	case -1:	/* Pipe at beginning or at end of argv;  See pipe_present(). */
      		fputs ("Missing command next to pipe in commandline.\n", stderr);
      		errno = EINVAL;	/* Note this is NOT shell exit. */
      		break;

    	case 0:	/* No pipe found in argv array or at end of argv array.
			See pipe_present().  Exec with whole given argv array. */
          DEBUG("No pipe found in argv\n");
          execvp(myArgv[0], myArgv);
      		break;

    	default:	/* Pipe in the middle of argv array.  See pipe_present(). */

      		/* Split arg vector into two where the pipe symbol was found.
       		 * Terminate first half of vector.
			 *
       		 * Fill in code. */
          DEBUG("Pipe in the middle of argv array\n");
          i = 0;
          left_argv = (char**)malloc(sizeof(char*)*(i+1));
          left_argv[i] = (char*)malloc(sizeof(char)*(strlen(myArgv[i])+1));
          strcpy(left_argv[i],myArgv[i]);
          i++;

          while (i < pipe_argv_index)
          {
            left_argv = (char**)realloc(left_argv, sizeof(char*)*(i+1));
            left_argv[i] = (char*)malloc(sizeof(char)*(strlen(myArgv[i])+1));
            strcpy(left_argv[i],myArgv[i]);
            i++;
          }

          left_argv = (char**)realloc(left_argv, sizeof(char*)*(i+1));
          left_argv[i] = '\0';

      		/* Create a pipe to bridge the left and right halves of the vector. 
			 *
			 * Fill in code. */
          pipe(pipefds); // same as pipe(&pipefds[0]);

      		/* Create a new process for the right side of the pipe.
       		 * (The left side is the running "parent".)
       		 *
			 * Fill in code to replace the underline. */
          
      		switch(pid = fork()) {

        		case -1 :
	  				break;

        		/* Talking parent.  Remember this is a child forked from shell. */
        		default :

	  				/* - Redirect output of "parent" through the pipe.
	  				 * - Don't need read side of pipe open.  Write side dup'ed to stdout.
	 	 			 * - Exec the left command.
					 *
					 * Fill in code. */
            close(pipefds[0]); // process 1 does not need to read from pipe
            dup2(pipefds[1], STD_OUTPUT); // instead standard output by pipefds[1]
            close(pipefds[1]); // this file descriptor not needed any more
            execvp(left_argv[0], left_argv);
	  				break;

        		/* Listening child. */
        		case 0 :

	  				/* - Redirect input of "child" through pipe.
					  * - Don't need write side of pipe. Read side dup'ed to stdin.
				  	 * - Exec command on right side of pipe and recursively deal with other pipes
					 *
					 * Fill in code. */
            waitpid(-1, &status,0);

            i = 0;
            while (left_argv[i] != '\0')
            {
              DEBUG("left_argv[%d] : %s ", i, left_argv[i]);
              free(left_argv[i]);
              DEBUG("free\n", i);
              i++;
            }

            free(left_argv);

            close(pipefds[1]); // process 2 does not need to write to pipe
            dup2(pipefds[0], STD_INPUT); // instead standard input by pipefds[0]
            close(pipefds[0]); // this file descriptor not needed any more
            pipe_and_exec(&myArgv[pipe_argv_index+1]);
			}
	}
	perror("Couldn't fork or exec child process");
  exit(errno);
}
