SRCS1 = aclapi.c
SRCS2 = aclapi2.c
EXT = .c
OBJS1 = $(SRCS1:$(EXT)=.o)
OBJS2 = $(SRCS2:$(EXT)=.o)
EXEC1 = aclapi
EXEC2 = aclapi2
CXX = gcc
#CXXFLAGS = -Wall -D _DEBUG
CXXFLAGS = -Wall

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS1) -lacl

$(EXEC2): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS2) -lacl

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $< -ggdb

cleanall:clean cleanexe

clean:
	rm -f $(OBJS1) $(OBJS2)

cleanexe:
	rm -f $(EXEC1) $(EXEC2)
