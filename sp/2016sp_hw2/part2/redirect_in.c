/*
 * redirect_in.c  :  check for <
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for "<" in myArgv, then redirect input to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_in(char ** myArgv) {
  	int i = 0;
  	int fd;

    DEBUG("in redirect_in\n");

  	/* search forward for <
  	 *
	 * Fill in code. */
    while (myArgv[i] != '\0')
    {
      if(!strcmp(myArgv[i], "<")) break;

      i++;
    }

  	if (myArgv[i] != '\0' && !strcmp(myArgv[i], "<")) {	/* found "<" in vector. */

    	/* 1) Open file.
     	 * 2) Redirect stdin to use file for input.
   		 * 3) Cleanup / close unneeded file descriptors.
   		 * 4) Remove the "<" and the filename from myArgv.
		 *
   		 * Fill in code. */
      DEBUG("find <\n");

      fd = open(myArgv[i+1], O_RDONLY);
      if(dup2(fd, STD_INPUT) == -1)
      {
        errno = EBADFD;
        return -1;
      }

      // find < in end
      if(myArgv[i+2] == '\0')
      {
        myArgv[i+1] = '\0';
        myArgv[i] = '\0';
      }
      else
      {
        myArgv[i] = myArgv[i+2];
        myArgv[i+1] = myArgv[i+3];
        
        i+=4;
        while(1)
        {
          myArgv[i-2] = myArgv[i];

          if(myArgv[i] == '\0') break;
          else i++;
        }
      }
/*
      i = 0;
      while (myArgv[i] != '\0')
      {
        DEBUG("[%d] : %s\n",i,myArgv[i]);
        i++;
      }
*/
    }

    DEBUG("end of redirect_in\n");

  	return 0;
}
