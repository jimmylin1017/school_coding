# source file
SRCS = main.cpp header.cpp tcp.cpp threeway.cpp data_swap.cpp fourway.cpp
# source file format [.cpp]
SRCF  = .cpp
# convert source file format to [.o]
OBJS = $(SRCS:$(SRCF)=.o)
# execute file name
EXEC = main
# compiler
CXX  = g++
# compile flag with debug
#CXXFLAGS = -std=c++11 -ggdb -pthread -D _DEBUG
# compile flag c++11 and gdb
CXXFLAGS = -std=c++11 -ggdb -pthread

all: $(EXEC) clean

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)

%.o: %$(SRCF)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -rf $(OBJS)