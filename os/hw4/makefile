SRCS = mm.c main.c
EXT  = .c
OBJS = $(SRCS:$(EXT)=.o)
EXEC = main
CXX  = gcc
#CXXFLAGS = -std=c99 -Wall -g -D _DEBUG
CXXFLAGS = -std=c99 -Wall -g
DEP  = dep

all:$(EXEC) clean

$(EXEC):$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $<

dep:
	$(CXX) $(CXXFLAGS) -M $(SRCS) > $(DEP)

clean:
	rm -rf $(OBJS) $(DEP)
