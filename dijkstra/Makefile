CC = g++
CFLAGS = -std=c++2a -g3

dijkstra: dijkstra.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f dijkstra
	rm -f *.o
