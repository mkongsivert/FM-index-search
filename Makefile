CXX = clang++

CXX_FLAGS = -g -std=c++11 -pedantic -Wall -Wextra

bitvector: bitvector.cpp bitvector.o
	$(CXX) bitvector.cpp -o bitvector $(CXX_FLAGS) bitvector.o -lncurses

bitvector.o: bitvector.cpp bitvector.hpp
	$(CXX) bitvector.cpp -o bitvector.o -c $(CXX_FLAGS)

clean:
	rm -rf *.o bitvector