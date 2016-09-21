final:parse.o shell.o builtin.o run_command.o is_background.o
	gcc parse.o shell.o builtin.o run_command.o is_background.o -o final
parse.o:parse.c
	gcc -c parse.c -ggdb
shell.o:shell.c
	gcc -c shell.c -ggdb
builtin.o:builtin.c
	gcc -c builtin.c -ggdb
run_command.o:run_command.c
	gcc -c run_command.c -ggdb
is_background.o:is_background.c
	gcc -c is_background.c -ggdb
clean:
	rm -f parse.o shell.o builtin.o run_command.o is_background.o final
