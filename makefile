a.out: proj2.o e.o
	g++ -g -Wall -ansi -o test.out proj2.o e.o

proj2.o: proj2.cpp e.h
	g++ -g -Wall -ansi -c proj2.cpp

e.o: e.cpp e.h
	g++ -g -Wall -ansi -c e.cpp

