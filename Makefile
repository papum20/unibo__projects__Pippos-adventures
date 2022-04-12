main: main.o level.o room.o
	g++ main.o level.o room.o -lncurses -o main

main.o: main.cpp main.h
	g++ -c main.cpp

level.o: level.cpp level.h
	g++ -c level.cpp

room.o: room.cpp room.h
	g++ -c room.cpp



clean:
	rm *.o main main.exe