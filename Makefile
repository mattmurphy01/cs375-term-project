CXX = g++
CFLAGS = -Wall -g

all: test

# Link main test program to algorithm programs
test: test.o bellmanFord.o aStar.o graph.o
	$(CXX) $(CFLAGS) -o test test.o bellmanFord.o aStar.o

# Compile test.cpp 
test.o: test.cpp test.h
	$(CXX) $(CFLAGS) -c test.cpp

# Compile bellmanFord.cpp 
bellmanFord.o: bellmanFord.cpp test.h
	$(CXX) $(CFLAGS) -c bellmanFord.cpp

# Compile aStar.cpp 
aStar.o: aStar.cpp test.h
	$(CXX) $(CFLAGS) -c aStar.cpp

# Compile graph.cpp
graph.o: graph.cpp test.h
	$(CXX) $(CFLAGS) -c graph.cpp

# Clean 
clean:
	rm -f *.o test