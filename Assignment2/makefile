all:disp

disp:display.cpp maze.o
	g++ display.cpp maze.o -o disp -lSDL2
maze.o:maze.cpp maze.h output.h
	g++ -c maze.cpp -o maze.o
	
clean:
	rm *.o maze disp
