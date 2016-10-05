#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: mycat filename\n");
        exit(1);
    }

    FILE *file;

    char content [100];

    file = fopen (argv[1] , "r");

    if (file == NULL)
    {
        perror("fopen");
        exit(1);
    }

    while(fgets(content, 100, file) != NULL)
    {
        printf("%s", content);
    }

    fclose (file);
	
	return 0;
}