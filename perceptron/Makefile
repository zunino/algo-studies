CC = g++
CCFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

perceptron: random.o data.o perceptron.o main.o
	$(CC) $(CCFLAGS) -o $@ $^

random.o: random.hpp random.cpp
	$(CC) $(CCFLAGS) -c random.cpp

data.o: data.hpp data.cpp
	$(CC) $(CCFLAGS) -c data.cpp

perceptron.o: perceptron.hpp perceptron.cpp data.hpp
	$(CC) $(CCFLAGS) -c perceptron.cpp

main.o: main.cpp data.hpp perceptron.hpp
	$(CC) $(CCFLAGS) -c main.cpp

clean:
	rm -f perceptron
	rm -f *.o
