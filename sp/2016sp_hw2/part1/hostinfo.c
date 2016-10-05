#include <sys/utsname.h>
#include <sys/unistd.h> // gethostid()
#include <stdio.h>
#include <stdlib.h>

int main()
{
	struct utsname uts;

	if(uname(&uts) == -1)
	{
		perror("uname");
		exit(1);
	}

	printf("hostname: %s\n", uts.nodename);
	printf("%s %s\n", uts.sysname, uts.release);
	printf("hostid: %ld\n", gethostid());

	return 0;
}