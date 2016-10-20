/*
 *  pipe_present.c :  check for |
 */

#include "shell.h"

/*
 * Return index offset into argv of where "|" is,
 * -1 if in an illegal position (first or last index in the array),
 * or 0 if not present.
 */
int pipe_present(char ** myCurrentArgv) {
	int index = -1;

  	/* Search through myCurrentArgv for a match on "|". */
    int i = 0;

    while (myCurrentArgv[i] != '\0')
    {
      if(index == -1 && !strcmp(myCurrentArgv[i], "|"))
      {
        index = i;
      }

      i++;
    }

    DEBUG("counter i %d\n", i);
    DEBUG("pipe index %d\n", index);

  	if (index == 0 || index == i-1)
    {
      /* At the beginning or at the end. */
    	return -1;
  	}
    else if (index == -1)
    {
      /* Off the end. */
    	return 0;
  	}
    else
    {
    	/* In the middle. */
    	return index;
  	}
}
