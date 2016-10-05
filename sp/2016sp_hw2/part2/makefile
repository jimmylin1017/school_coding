SRCS1 = builtin.c parse.c shell.c is_background.c pipe_command.c redirect_in.c redirect_out.c pipe_present.c run_command.c
EXT = .c
OBJS1 = $(SRCS1:$(EXT)=.o)
EXEC1 = myshell
CXX = gcc
#CXXFLAGS = -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g

all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(COBJS) $(OBJS1)

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $<

cleanall:clean cleanexe

clean:
	rm -f $(OBJS1)

cleanexe:
	rm -f $(EXEC1)

