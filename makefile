CXX = g++
CXXFLAGS = -std=c++0x -Wall -g -w

P2: main.cpp scanner.cpp parser.cpp
	$(CXX) $(CXXFLAGS) -o frontEnd main.cpp parser.cpp scanner.cpp

clean:
	rm -f frontEnd *.o stdin.temp keyboard_input.txt