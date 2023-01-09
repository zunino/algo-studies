CC = g++
CCFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

perceptron: random.o data.o perceptron.o io.o bmp.o pgm.o main.o
	$(CC) $(CCFLAGS) -o $@ $^

main.o: main.cpp data.hpp perceptron.hpp
	$(CC) $(CCFLAGS) -c main.cpp

%.o : %.cpp %.hpp
	$(CC) $(CCFLAGS) -c $<

clean:
	rm -f perceptron
	rm -f *.o
