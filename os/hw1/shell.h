#ifndef __SHELL__
#define __SHELL__

typedef int bool;

enum
{
  INPUT_SIZE = 100,
  COMMAND_SIZE = 10,
  RUN_BACK_PID = 1
};

void run_shell();
void reset_all();
void type_prompt();
void read_command();
void create_pipe();

#endif