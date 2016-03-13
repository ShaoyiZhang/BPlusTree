CXX=g++
#CXX=clang++                                                                             

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -g  

#CXXFLAGS = -std=c++11 -Wall -Wextra -Werror                                             


BINARIES = test01

all: ${BINARIES}

main: Graph.o Main.o
	${CXX} $^ -o $@

test01: BTree.o test.o
	${CXX} $^ -o $@

tests:${BINARIES}
	./test01
#	./main


LEAKTESTS=test01

leaktests: ${LEAKTESTS}

leaktest01: main
	- valgrind -q --dsymutil=yes --leak-check=full ./main

clean:
	/bin/rm -f ${BINARIES} *.o

