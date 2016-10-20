#ifdef _DEBUG
	#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> 
#include <dirent.h>

void movefile(char *dir_path, char *srcfile, char *destfile);

int main( int argc, char* argv[] ) {

	if(argc != 3)
	{
		printf("input error!");
		exit(1);
	}

	char *buf = NULL;
    buf = getcwd((char *)NULL, 0);

    if(buf == NULL)
    {
    	perror("getcwd error!");
    	exit(1);
    }

    movefile(buf, argv[1], argv[2]);

	return 0;
}


void movefile(char *dir_path, char *srcfile, char *destfile)
{
    int srcfind, destfind, is_dir;
    srcfind = destfind = is_dir = 0;

    //DIR * dp = opendir(dir_path);

    //struct dirent *entry;

    /*if (dp == NULL)
    {
        printf("Couldn't open directory\n");
        return;
    }*/

    if(chdir(dir_path) == -1)
    {
        printf("Couldn't change directory\n");
        return;
    }

    if(access(srcfile, F_OK) == 0)
    {
        srcfind = 1;
        DEBUG("find srcfile\n");
    }

    if(access(destfile, F_OK) == 0)
    {
        destfind = 1;
        DEBUG("find destfile\n");
    }

    if(srcfind == 0)
    {
        printf("srcfile not found!\n");
        return;
    }

    if(destfind)
    {
        struct stat statbuf;
        if(stat(destfile, &statbuf) == -1)
        {
            perror("stat error!");
            exit(1);
        }

        if(S_ISDIR(statbuf.st_mode))
        {
            is_dir = 1;
        }
    }

    if(is_dir)
    {
        FILE *file1, *file2;
        char content [100];

        file1 = fopen (srcfile , "r");
        
        if(chdir(destfile) == -1)
        {
            printf("Couldn't change to destination directory\n");
            return;
        }
        file2 = fopen (srcfile , "w");

        while(fgets(content, 100, file1) != NULL)
        {
            fprintf(file2, "%s", content);
        }

        fclose(file1);
        fclose(file2);

        chdir(dir_path);
        if(remove(srcfile) != 0)
        {
            perror("remove error!");
        }
    }
    else if(destfind)
    {
        char c;
        printf("mymv: overwrite '%s'?", destfile);
        
        scanf("%c", &c);
        if(c == 'Y' || c == 'y')
        {
            rename(srcfile, destfile);
        }
        else
        {
            printf("not overwrite!\n");
        }
    }
    else
    {
        if(rename(srcfile, destfile))
        {
            perror("rename error!");
        }
    }
}

//void movefile(char *dir_path, char *srcfile, char *destfile)
//{
    /*
    char* destfile_path = NULL;
    char* srcfile_path = NULL;
    int len = strlen(dir_path);

    srcfile_path = (char*)malloc(sizeof(char)*(len+1));
    strcpy(srcfile_path, dir_path);
    strcat(srcfile_path, "/");
    strcat(srcfile_path, srcfile);

    destfile_path = (char*)malloc(sizeof(char)*(len+1));
    strcpy(destfile_path, dir_path);
    strcat(destfile_path, "/");
    strcat(destfile_path, destfile);
    
    DEBUG("%s\n", dir_path);
    DEBUG("%s\n", srcfile_path);
    DEBUG("%s\n", destfile_path);
    */

    /*int srcfind, destfind, is_dir;
    srcfind = destfind = is_dir = 0;

    DIR * dp = opendir(dir_path);

    struct dirent *entry;

    if (dp == NULL)
    {
        printf("Couldn't open directory\n");
        return;
    }

    if(chdir(dir_path) == -1)
    {
        printf("Couldn't change directory\n");
        return;
    }

    while((entry = readdir(dp)) != NULL)
    {
        if(!strcmp(entry->d_name, destfile))
        {
            destfind = 1;
        }

        if(!strcmp(entry->d_name, srcfile))
        {
            srcfind = 1;
        }

        DEBUG("%s\n", entry->d_name);
    }

    if(srcfind == 0)
    {
        printf("srcfile not found!\n");
        return;
    }

    if(destfind)
    {
        struct stat statbuf;
        if(stat(destfile, &statbuf) == -1)
        {
            perror("stat error!");
            exit(1);
        }

        if(S_ISDIR(statbuf.st_mode))
        {
            is_dir = 1;
        }
    }

    if(is_dir)
    {
        FILE *file1, *file2;
        char content [100];

        file1 = fopen (srcfile , "r");
        
        chdir(destfile);
        file2 = fopen (srcfile , "w");

        while(fgets(content, 100, file1) != NULL)
        {
            fprintf(file2, "%s", content);
        }

        fclose(file1);
        fclose(file2);

        chdir(dir_path);
        if(remove(srcfile) != 0)
        {
            perror("remove error!");
        }
    }
    else if(destfind)
    {
        char c;
        printf("mymv: overwrite '%s'?", destfile);
        
        scanf("%c", &c);
        if(c == 'Y' || c == 'y')
        {
            rename(srcfile, destfile);
        }
        else
        {
            printf("not overwrite!\n");
        }
    }
    else
    {
        if(rename(srcfile, destfile))
        {
            perror("rename error!");
        }
    }
}*/