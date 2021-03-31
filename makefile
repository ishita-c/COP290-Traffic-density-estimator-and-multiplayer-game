default:subtask1.cpp subtask2.cpp
	g++ subtask1.cpp -o sub1 -Wall `pkg-config --cflags --libs opencv`
	g++ subtask2.cpp -o sub2 -Wall `pkg-config --cflags --libs opencv`
	
subtask1: subtask1.cpp
	g++ subtask1.cpp -o sub1 -Wall `pkg-config --cflags --libs opencv`
	
subtask2:
	g++ subtask2.cpp -o sub2 -Wall `pkg-config --cflags --libs opencv`
	
subtask3:subtask3.cpp
	g++ subtask3.cpp -o sub3 -Wall -pthread `pkg-config --cflags --libs opencv`
	
subtask3.1:subtask3_1.cpp
	g++ subtask3_1.cpp -o sub3.1 -Wall `pkg-config --cflags --libs opencv`
	
subtask3.2:subtask3_2.cpp
	g++ subtask3_2.cpp -o sub3.2 -Wall `pkg-config --cflags --libs opencv`
	
subtask3.3:subtask3_3.cpp
	g++ subtask3_3.cpp -o sub3.3 -Wall -pthread `pkg-config --cflags --libs opencv`
	
subtask3.4:subtask3_4.cpp
	g++ subtask3_4.cpp -o sub3.4 -Wall -pthread `pkg-config --cflags --libs opencv`
	
clean:
	rm sub1 sub2 cropped.jpg transformed.jpg
