/* shell.h : function prototypes for all functions in shell exercise */

#define FALSE 0
#define TRUE (!FALSE)
#ifdef _DEBUG
	#define DEBUG(format, args...) printf("[%s:%d] "format, __FILE__, __LINE__, ##args)
#else
	#define DEBUG(format, args...)
#endif

char ** parse(char *);		/* tokenise a string */
void free_argv(char **);	/* free argv array. */
void run_command(char **);	/* do the fork, exec stuff */
int is_background(char **);	/* check for & at end */
int is_builtin(char *);		/* check for in-built keywords */
int do_builtin(char **);	/* and then do them */
int redirect_out(char **);
int redirect_in(char **);
int pipe_present(char **);
void pipe_and_exec(char **);
