#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STD_INPUT 0
#define STD_OUTPUT 1

int main()
{
    char *cmd_ls[] = {"ls", "-al", '\0'};
    char *cmd_cat[] = {"cat", '\0'};
    //char *cmd_grep[] = {"grep", "pipe",'\0'};

    int fd[2];
    pipe(fd); // same as pipe(&fd[0]);

    int pid = fork();

    switch(pid)
    {
        case -1:
            perror("pid");
            exit(1);
        case 0:
            close(fd[0]); // process 1 does not need to read from pipe
            dup2(fd[1], STD_OUTPUT); // instead standard output by fd[1]
            close(fd[1]); // this file descriptor not needed any more
            execvp("ls", cmd_ls);
        default:
            close(fd[1]); // process 2 does not need to write to pipe
            dup2(fd[0], STD_INPUT); // instead standard input by fd[0]
            close(fd[0]); // this file descriptor not needed any more
            execvp("cat", cmd_cat);
    }
	
	return 0;
}