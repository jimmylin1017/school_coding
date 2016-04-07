#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define TRUE 1
#define FALSE 0
#define STD_INPUT 0
#define STD_OUTPUT 1
#ifdef _DEBUG
	#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

static char input_command[INPUT_SIZE];
static char *process1[COMMAND_SIZE], *process2[COMMAND_SIZE];
static char *output_path = NULL, *input_path = NULL;
//static int back_pid[RUN_BACK_PID] = {0};
//static char* local_address = NULL;
static int status = 0;
static bool NEED_PIPE = FALSE;
static bool SHELL_EXIT = FALSE, OUTPUT_REDIRECTION = FALSE, INPUT_REDIRECTION = FALSE, RUN_BACK = FALSE;

void run_shell()
{
	printf("Shell Run!\n");
	while(TRUE)
	{
		type_prompt();
		reset_all();
		read_command();
		if(SHELL_EXIT)
		{
			printf("Shell Stop!\n");
			break;
		}

		if(!strcmp(process1[0], "cd"))
		{
			chdir(process1[1]);
			continue;
		}

		int pid = fork();

		if(pid == -1)
		{
			perror("fork() error!");
		}
		else if(pid != 0) // parent process
		{
			if(!RUN_BACK)
				waitpid(pid, &status, 0); //stop any child process, same as wait(&status)
			//DEBUG("close a child\n");
		}
		else
		{
			if(NEED_PIPE)
			{
				DEBUG("creat pipe\n");
				create_pipe();
			}
			else
			{
				if(OUTPUT_REDIRECTION && INPUT_REDIRECTION)
				{
					DEBUG("OUTPUT_REDIRECTION output_fd with no pipe\n");
					DEBUG("Input_REDIRECTION input_fd with no pipe\n");
					
					int output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					int input_fd = open(input_path, O_RDONLY);

					dup2(output_fd, STD_OUTPUT);
					dup2(input_fd, STD_INPUT);

					execvp(process1[0], process1);

					close(output_fd);
					close(input_fd);
				}
				else if(OUTPUT_REDIRECTION)
				{
					DEBUG("OUTPUT_REDIRECTION output_fd with no pipe\n");
					// creating the file if it does not already exist. If the file does exist, the system truncates the file to zero bytes. 
					int output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
					dup2(output_fd, STD_OUTPUT);
					execvp(process1[0], process1);
					close(output_fd);
				}
				else if(INPUT_REDIRECTION)
				{
					DEBUG("Input_REDIRECTION input_fd with no pipe\n");
					int input_fd = open(input_path, O_RDONLY);
					dup2(input_fd, STD_INPUT);
					execvp(process1[0], process1);
					close(input_fd);
				}
				else
					execvp(process1[0], process1);
			}
		}
	}
}

void reset_all()
{
	NEED_PIPE = SHELL_EXIT = OUTPUT_REDIRECTION = INPUT_REDIRECTION = RUN_BACK = FALSE;
	output_path = input_path = NULL;
	memset(input_command, 0, sizeof(input_command));
	memset(process1, 0, sizeof(process1));
	memset(process2, 0, sizeof(process2));
}

void read_command()
{
	int split_index = 0;
	//int proc1_start = 0, proc1_end = 0, proc2_start = 0, proc2_end = 0;
	int pipe_index = 0, has_filepath = 0;
	int i = 0;
	char *store_command[COMMAND_SIZE], *split_str;

	// read input command line
	fgets(input_command, sizeof(input_command), stdin);

	// instead '\n' by '\0'
	if(input_command[strlen(input_command) - 1] == '\n')
	{
		input_command[strlen(input_command) - 1] = '\0';
	}

	// exit shell
	if(!strcmp(input_command, "exit") || !strcmp(input_command, "EXIT"))
	{
		SHELL_EXIT = TRUE;
		return;
	}

	// split command
	split_str = strtok(input_command, " ");
	while(split_str != NULL)
	{
		store_command[split_index] = split_str;
		split_index++;
		split_str = strtok(NULL, " ");
	}

	for(i = 0; i < split_index; i++)
	{
		if(*store_command[i] == '|')
		{
			NEED_PIPE = TRUE;
			pipe_index = i;
			has_filepath = 0;
			continue;
		}

		// output
		if(*store_command[i] == '>')
		{
			OUTPUT_REDIRECTION = TRUE;
			output_path = store_command[i+1];
			has_filepath++;
			i++;
			continue;
		}

		// input
		if(*store_command[i] == '<')
		{
			INPUT_REDIRECTION = TRUE;
			input_path = store_command[i+1];
			has_filepath++;
			i++;
			continue;
		}

		// back run
		if(*store_command[i] == '&')
		{
			RUN_BACK = TRUE;
			break;
		}

		// store command into process
		if(NEED_PIPE)
		{
			process2[i - pipe_index - 1 - has_filepath] = store_command[i];
			DEBUG("process2 index %d : %s\n", i - pipe_index - 1, process2[i - pipe_index - 1 - has_filepath]);
		}
		else
		{
			process1[i - has_filepath] = store_command[i];
			DEBUG("process1 index %d : %s\n", i, process1[i - has_filepath]);
		}
	}

	DEBUG("output_path : %s\n", output_path);
	DEBUG("input_path : %s\n", input_path);
}

void type_prompt()
{
	printf(" $ ");
}

void create_pipe()
{
	int fd[2];
	pipe(fd); // same as pipe(&fd[0]);

	int pid = fork();

	if(pid == -1)
	{
		perror("pipe fork error!");
	}
	else if(pid == 0) // child process
	{
		close(fd[0]); // process 1 does not need to read from pipe
		dup2(fd[1], STD_OUTPUT); // instead standard output by fd[1]
		close(fd[1]); // this file descriptor not needed any more

		if(INPUT_REDIRECTION)
		{
			DEBUG("INPUT_REDIRECTION input_fd with pipe\n");
			int input_fd = open(input_path, O_RDONLY);
			dup2(input_fd, STD_INPUT);
			execvp(process1[0], process1);
			close(input_fd);
		}
		else
			execvp(process1[0], process1);
	}
	else // parent process
	{
		//waitpid(-1, &status, 0);
		close(fd[1]); // process 2 does not need to write to pipe
		dup2(fd[0], STD_INPUT); // instead standard input by fd[0]
		close(fd[0]); // this file descriptor not needed any more

		if(OUTPUT_REDIRECTION)
		{
			DEBUG("OUTPUT_REDIRECTION output_fd with pipe\n");
			// creating the file if it does not already exist. If the file does exist, the system truncates the file to zero bytes. 
			int output_fd = open(output_path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			dup2(output_fd, STD_OUTPUT);
			execvp(process2[0], process2);
			close(output_fd);
		}
		else
			execvp(process2[0], process2);
	}
}