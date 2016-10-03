output: p2.o Window.o WindowMenu.o fileHandler.o
	g++ -Wall -lncurses -std=c++14 -g -O0 -pedantic-errors p2.o Window.o WindowMenu.o fileHandler.o -o output

p2.o: p2.cpp
	g++ -Wall -lncurses -std=c++14 -g -O0 -pedantic-errors -c p2.cpp

Window.o: Window.cpp Window.h
	g++ -Wall -lncurses -std=c++14 -g -O0 -pedantic-errors -c Window.cpp

WindowMenu.o: WindowMenu.cpp WindowMenu.h
	g++ -Wall -lncurses -std=c++14 -g -O0 -pedantic-errors -c WindowMenu.cpp

fileHandler.o: fileHandler.cpp fileHandler.h
	g++ -Wall -lncurses -std=c++14 -g -O0 -pedantic-errors -c fileHandler.cpp

clean:
	rm *.o output