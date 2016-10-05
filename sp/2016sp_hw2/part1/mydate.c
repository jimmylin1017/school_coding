#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%b %d(%a), %Y %I:%M %p", timeinfo);
	puts (buffer);

	return 0;
}