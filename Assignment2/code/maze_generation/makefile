all:dot

dot:maze.o moving_dot.cpp
	g++ moving_dot.cpp maze.o -lSDL2 -lSDL2_image -o dot

disp:display.cpp maze.o
	g++ display.cpp maze.o -o disp -lSDL2
maze.o:maze.cpp maze.h output.h
	g++ -c maze.cpp -o maze.o
	
clean:
	rm *.o maze disp
