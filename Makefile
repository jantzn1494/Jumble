jumble: jumble.o
	g++ -std=c++11 -o jumble jumble.o

jumble.o: jumble.cpp jumble.h
	g++ -std=c++11 -c jumble.cpp

clean:
	rm jumble.o
