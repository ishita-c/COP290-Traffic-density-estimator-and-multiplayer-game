FLAGS= -Wall `pkg-config --cflags --libs opencv`
FLAGST= -pthread -Wall `pkg-config --cflags --libs opencv`
RM3= sub3 sub3.1 sub3.2 sub3.3 sub3.4
	
default:subtask3_1.cpp subtask3_2.cpp subtask3_3.cpp subtask3_4.cpp
	g++ subtask3_1.cpp -o sub3.1 $(FLAGS)
	g++ subtask3_2.cpp -o sub3.2 $(FLAGS)
	g++ subtask3_3.cpp -o sub3.3 $(FLAGST)
	g++ subtask3_4.cpp -o sub3.4 $(FLAGST)
	
subtask3.1:subtask3_1.cpp
	g++ subtask3_1.cpp -o sub3.1 $(FLAGS)
	
subtask3.2:subtask3_2.cpp
	g++ subtask3_2.cpp -o sub3.2 $(FLAGS)
	
subtask3.3:subtask3_3.cpp
	g++ subtask3_3.cpp -o sub3.3 $(FLAGST)
	
subtask3.4:subtask3_4.cpp
	g++ subtask3_4.cpp -o sub3.4 $(FLAGST)
	
	
clean:
	rm $(RM3)
