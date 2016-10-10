
compile: 1730ed

run: 1730ed
	./1730ed

p2.o: p2.cpp
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors myFile.cpp
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors p2.cpp
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors WindowMenu.cpp 
	g++ -Wall -std=c++14 -c -lncurses -g -O0 -pedantic-errors fileHandler.cpp

1730ed: p2.o
	g++ -Wall -lncurses -g -o 1730ed p2.o myFile.o WindowMenu.o fileHandler.o

clean: 
	rm -f 1730ed
	rm -f *.o
	rm -f *~