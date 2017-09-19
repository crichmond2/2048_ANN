CXX = g++
CXXFLAGS = -g -std=c++11 
2048: listen.o grid.o ann_V2.o
	$(CXX) -o 2048 listen.o grid.o ann_V2.o

listen.o: listen.cpp

grid.o: grid.cpp grid.h ann_V2.h

ann_V2.o: ann_V2.cpp ann_V2.h

clean:
	rm -f *.o 2048
