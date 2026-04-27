CXX      = g++
CXXFLAGS = -std=c++20 -O2 -Wall

all: unit_tests main

unit_tests: unit_tests.cpp fractions.h bigint.h
	$(CXX) $(CXXFLAGS) unit_tests.cpp -o unit_tests

main: main.cpp fractions.h bigint.h
	$(CXX) $(CXXFLAGS) main.cpp -o main

test: unit_tests
	./unit_tests

run: main
	./main

clean:
	rm -f unit_tests main
