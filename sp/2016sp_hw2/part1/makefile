all:hostinfo mydate printdir mycat pipe_ls

hostinfo: hostinfo.o
	gcc -o hostinfo hostinfo.o 

mydate: mydate.o
	gcc -o mydate mydate.o

printdir: printdir.o
	gcc -o printdir printdir.o

mycat: mycat.o
	gcc -o mycat mycat.o

pipe_ls: pipe_ls.o
	gcc -o pipe_ls pipe_ls.o

%.o:%.c
	gcc -c $<

clean:
	rm *.o

cleanexe:
	rm hostinfo mydate printdir mycat pipe_ls