#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buf = NULL;

    buf = getcwd((char *)NULL, 0);

    if(buf == NULL)
    {
    	perror("getcwd");
    	exit(1);
    }

    printf("%s\n", buf);
    free(buf);
	
	return 0;
}