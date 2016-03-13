#CXX=g++
CXX=clang++                                                                             

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -g  

#CXXFLAGS = -std=c++11 -Wall -Wextra -Werror                                             


BINARIES = test01

all: ${BINARIES}

main: Graph.o Main.o
	${CXX} $^ -o $@

<<<<<<< HEAD
test01: BTree.o test.o
	${CXX} $^ -o $@
=======
tree: BTree.o Main.o TreeNode.o
	${CXX} $^ -o $@

#test02: test02.o Student.o HashTable.o
#	${CXX} $^ -o $@
>>>>>>> 96e1ae88c70378ca2eab9df830ee8b4a0313dd7e

tests:${BINARIES}
	./test01
#	./main


LEAKTESTS=test01

leaktests: ${LEAKTESTS}

leaktest01: main
	- valgrind -q --dsymutil=yes --leak-check=full ./main

clean:
	/bin/rm -f ${BINARIES} *.o

