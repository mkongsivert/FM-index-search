CXX = clang++

CXX_FLAGS = -g -std=c++11 -pedantic -Wall -Wextra

bitvector: bitvector.cpp bitvector.hpp
	$(CXX) bitvector.cpp -o bitvector $(CXX_FLAGS) -lncurses

clean:
	rm -rf *.o bitvector