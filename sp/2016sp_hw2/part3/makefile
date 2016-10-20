SRCS1 = convert.c
SRCS2 = lookup1.c main.c
EXT = .c
OBJS1 = $(SRCS1:$(EXT)=.o)
OBJS2 = $(SRCS2:$(EXT)=.o)
EXEC1 = convert
EXEC2 = file_lookup
CXX = gcc
CXXFLAGS = -Wall
#CXXFLAGS = -Wall -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS1)

$(EXEC2): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS2)

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $< -ggdb

cleanall:clean cleanexe

clean:
	rm -f $(OBJS1) $(OBJS2)

cleanexe:
	rm -f $(EXEC1) $(EXEC2)

