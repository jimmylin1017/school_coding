SRCS = mymv_B033040006.c
EXT = .c
OBJS = $(SRCS:$(EXT)=.o)
EXEC = mymv
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

