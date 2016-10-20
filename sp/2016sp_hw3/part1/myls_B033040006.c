#ifdef _DEBUG
	#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

#define DIR_MAX 256

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <dirent.h>

void list_directory(char *dir_path, char *flag);

int main( int argc, char* argv[] ) {

	char *buf = NULL;
    buf = getcwd((char *)NULL, 0);

    if(buf == NULL)
    {
    	perror("getcwd error!\n");
    	exit(1);
    }

    if(argc == 1)
    {
    	list_directory(buf, NULL);
    }
    else if(argc == 2)
    {
    	if(argv[1][0] == '-')
    	{
    		list_directory(buf, argv[1]);
    	}
    	else
    	{
    		strcat(buf, "/");
			strcat(buf, argv[1]);
    		list_directory(buf, NULL);
    	}
    }
    else if(argc == 3)
    {
    	if(argv[1][0] == '-')
    	{
    		strcat(buf, "/");
			strcat(buf, argv[2]);

    		list_directory(buf, argv[1]);
    	}
    	else if(argv[2][0] == '-')
    	{
    		strcat(buf, "/");
			strcat(buf, argv[1]);

    		list_directory(buf, argv[2]);
    	}
    	else
    	{
    		printf("error command!\n");
    	}
    }

    free(buf);
	return 0;
}

void list_directory(char *dir_path, char *flag) {

	DIR * dp = opendir(dir_path);

	if (dp == NULL)
	{
		printf("Couldn't open directory\n");
		return;
	}

	int dir_count = 0;
	char dir_name_tmp[DIR_MAX][DIR_MAX] = {'\0'};

	struct dirent *entry;
	struct stat statbuf;

	int F, R;
	F = R = 0;

	if(flag != NULL)
	{
		for(int i=1;i<strlen(flag);i++)
		{
			if(flag[i] == 'F') F = 1;
			if(flag[i] == 'R') R = 1;
		}
	}

	printf("\n%s :\n", dir_path);

	if(chdir(dir_path) == -1)
	{
		printf("Couldn't change directory\n");
		return;
	}

	while((entry = readdir(dp)) != NULL)
	{
		if(stat(entry->d_name, &statbuf) == -1)
		{
			perror("stat error!\n");
			exit(1);
		}

		if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
		{
			if(statbuf.st_mode & S_IFDIR) //S_ISDIR(statbuf.st_mode)
			{
				strcpy(dir_name_tmp[dir_count], entry->d_name);
				dir_count++;
				
				if(F)
					printf("%s/\n", entry->d_name);
				else
					printf("%s\n", entry->d_name);
			}
			else if(F && ((statbuf.st_mode & S_IXUSR) || (statbuf.st_mode & S_IXGRP) || (statbuf.st_mode & S_IXOTH)))
			{
				printf("%s*\n", entry->d_name);

			}
			else
			{
				printf("%s\n", entry->d_name);
			}
		}	
	}

	if(R && dir_count > 0)
	{
		char *n_dir_path = NULL;
		int len = strlen(dir_path);

		for(int i=0;i<dir_count;i++)
		{
			n_dir_path = (char*)malloc(sizeof(char)*(len+1));
			strcpy(n_dir_path, dir_path);
			strcat(n_dir_path, "/");
			strcat(n_dir_path, dir_name_tmp[i]);
			list_directory(n_dir_path, flag);
			free(n_dir_path);
		}
	}	
}