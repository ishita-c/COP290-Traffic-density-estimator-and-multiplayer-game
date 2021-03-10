default:subtask1.cpp subtask2.cpp
	g++ subtask1.cpp -o sub1 -Wall `pkg-config --cflags --libs opencv`
	g++ subtask2.cpp -o sub2 -Wall `pkg-config --cflags --libs opencv`
	
subtask1: subtask1.cpp
	g++ subtask1.cpp -o sub1 -Wall `pkg-config --cflags --libs opencv`
	
subtask2:
	g++ subtask2.cpp -o sub2 -Wall `pkg-config --cflags --libs opencv`
	
clean:
	rm sub1 sub2 cropped.jpg transformed.jpg
