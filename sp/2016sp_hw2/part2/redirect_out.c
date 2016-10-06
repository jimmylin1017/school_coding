/*
 * redirect_out.c   :   check for >
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for ">" in myArgv, then redirect output to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_out(char ** myArgv) {
	  int i = 0;
  	int fd;

    DEBUG("in redirect_out\n");

  	/* search forward for >
  	 * Fill in code. */
    while (myArgv[i] != '\0')
    {
      if(!strcmp(myArgv[i], ">")) break;

      i++;
    }

  	if (myArgv[i] != '\0' && !strcmp(myArgv[i], ">")) {	/* found ">" in vector. */

    	/* 1) Open file.
    	 * 2) Redirect to use it for output.
    	 * 3) Cleanup / close unneeded file descriptors.
    	 * 4) Remove the ">" and the filename from myArgv.
		 *
    	 * Fill in code. */
      DEBUG("find >\n");

      int fd = open(myArgv[i+1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
      if(dup2(fd, STD_OUTPUT) == -1)
      {
        errno = EBADFD;
        return -1;
      }

      while(1)
      {
        if(myArgv[i] != '\0' && myArgv[i+2] != '\0')
        {
          myArgv[i] = myArgv[i+1];
          myArgv[i+1] = myArgv[i+2];
          i+=2;
        }
        else
          break;
      }

      myArgv[i] = '\0';

      i = 0;
      while (myArgv[i] != '\0')
      {
        DEBUG("[%d] : %s\n",i,myArgv[i]);
        i++;
      }
  	}

    DEBUG("end of redirect_out\n");

  	return 0;
}
