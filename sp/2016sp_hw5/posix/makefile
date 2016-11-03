SRCS1 = consumer.c
SRCS2 = producer.c
EXT = .c
OBJS1 = $(SRCS1:$(EXT)=.o)
OBJS2 = $(SRCS2:$(EXT)=.o)
EXEC1 = consumer
EXEC2 = producer
CXX = gcc -std=c99 -D_XOPEN_SOURCE=500
#CXXFLAGS = -Wall -D _DEBUG
CXXFLAGS = -Wall

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS1) -lrt

$(EXEC2): $(OBJS2)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS2) -lrt

%.o:%$(EXT)
	$(CXX) $(CXXFLAGS) -c $< -ggdb

cleanall:clean cleanexe

clean:
	rm -f $(OBJS1) $(OBJS2)

cleanexe:
	rm -f $(EXEC1) $(EXEC2)

