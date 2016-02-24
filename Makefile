CXX=g++
#CXX=clang++                                                                             

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -g  

#CXXFLAGS = -std=c++11 -Wall -Wextra -Werror                                             


BINARIES = main

all: ${BINARIES}

main: Graph.o Main.o
	${CXX} $^ -o $@

#test02: test02.o Student.o HashTable.o
#	${CXX} $^ -o $@

tests:${BINARIES}
	./main
#	./test02

LEAKTESTS=test01

leaktests: ${LEAKTESTS}

leaktest01: main
	- valgrind -q --dsymutil=yes --leak-check=full ./main

clean:
	/bin/rm -f ${BINARIES} *.o

