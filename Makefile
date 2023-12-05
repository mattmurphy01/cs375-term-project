CXX = g++
CFLAGS = -Wall -g

all: test

# Link main test program to algorithm programs
test: test.o bellmanFord.o aStar.o
	$(CXX) $(CXXFLAGS) -o test test.o bellmanFord.o aStar.o

# Compile test.cpp 
test.o: test.cpp test.h
	$(CXX) $(CXXFLAGS) -c test.cpp

# Compile bellmanFord.cpp 
bellmanFord.o: bellmanFord.cpp test.h
	$(CXX) $(CXXFLAGS) -c bellmanFord.cpp

# Compile aStar.cpp 
aStar.o: aStar.cpp test.h
	$(CXX) $(CXXFLAGS) -c aStar.cpp

# Clean 
clean:
	rm -f *.o test