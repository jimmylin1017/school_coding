SRCS = builtin.c parse.c shell.c is_background.c pipe_command.c redirect_in.c redirect_out.c pipe_present.c run_command.c
EXT = .c
OBJS = $(SRCS:$(EXT)=.o)
EXEC = myshell
CXX = gcc
#CXXFLAGS = -Wall -D _DEBUG
CXXFLAGS = -Wall
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $< -ggdb

cleanall:clean cleanexe

clean:
	rm -f $(OBJS)

cleanexe:
	rm -f $(EXEC)

