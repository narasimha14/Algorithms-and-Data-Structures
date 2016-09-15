CFLAGS  = -g -Wall -Weffc++ -Wextra -pedantic -std=c++11
LDFLAGS =

run:	test_suite
	./run
test_suite:	test_suite.o 
	g++ ${CFLAGS} -o run test_suite.o ${LDFLAGS}

test_suite.o:	test_suite.cpp range_query.h usertype.h compare.h
	g++ ${CFLAGS} -c test_suite.cpp

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf run a.out
