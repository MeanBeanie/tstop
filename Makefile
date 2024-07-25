CC = g++
CXXFLAGS = -o tstop -std=c++20 -lncurses

all:
	$(CC) *.cpp $(CXXFLAGS)
