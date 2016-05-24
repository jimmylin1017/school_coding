SRCS1 = readmap.c
SRCS2 = writemap.c
EXT = .c
OBJS1 = $(SRCS1:$(EXT)=.o)
OBJS2 = $(SRCS2:$(EXT)=.o)
EXEC1 = read
EXEC2 = write
CXX = gcc
CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g -D _DEBUG
#CXXFLAGS = -D_XOPEN_SOURCE=500 -std=c99 -Wall -g
DEP = dep

all: $(EXEC1) $(EXEC2) clean

$(EXEC1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(COBJS) $(OBJS1)

$(EXEC2): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(COBJS) $(OBJS2)

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $<

dep:
	$(CXX) $(CXXFLAGS) -M ${SRCS1} ${SRCS2} > ${DEP}

clean:
	rm -rf $(OBJS1) $(OBJS2) $(DEP)
