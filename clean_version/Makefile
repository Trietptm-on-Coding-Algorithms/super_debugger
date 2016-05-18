#
# 	Makefile for sdb
#

CC = g++
CFLAGS = -g -std=c++11

# all the source files
SRCS = helpers.cpp sourcefile.cpp functdata.cpp printers.cpp allfunct.cpp objdump.cpp #ptrace.cpp

# all the object files
OBJS = $(SRCS:.cpp=.o)

all: sdb helloworld


helloworld: helloworld.cpp
	$(CC) $(CFLAGS) helloworld.cpp -o helloworld


sdb: $(OBJS) sdb.cpp
	$(CC) $(CFLAGS) sdb.cpp -o sdb $(OBJS)


# magic
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@


clean: 
	$(RM) *.o sdb helloworld
