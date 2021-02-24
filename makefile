sub1:subtask1.cpp
	g++ subtask1.cpp -o sub1 `pkg-config --cflags --libs opencv`
	
clean:
	rm sub1 cropped.jpg transformed.jpg
